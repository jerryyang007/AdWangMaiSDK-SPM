"""按目标的配置列表编辑 OpenStep 工程，保留无关对象、注释和字符串。"""
from dataclasses import dataclass,field
import json
import os
from pathlib import Path
import re
import tempfile


TOKENS=re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|[{}()=;,]|[^\s{}()=;,]+')


@dataclass
class Node:
    start:int
    end:int
    value:object
    members:dict=field(default_factory=dict)


def parse_project(text):
    """记录值的精确区间；大括号出现在字符串或注释中时不参与结构匹配。"""
    tokens=[m for m in TOKENS.finditer(text) if not m.group().startswith(('//','/*'))];pos=0
    def take(expected=None):
        nonlocal pos
        if pos>=len(tokens):raise ValueError('工程配置结构不完整')
        token=tokens[pos];pos+=1
        if expected is not None and token.group()!=expected:raise ValueError('工程配置分隔符错误')
        return token
    def value():
        token=take();raw=token.group()
        if raw=='{':
            members={}
            while pos<len(tokens) and tokens[pos].group()!='}':
                key=take().group();key=json.loads(key) if key.startswith('"') else key
                if key in members:raise ValueError('工程配置包含重复字段：'+key)
                take('=');members[key]=value();take(';')
            end=take('}').end();return Node(token.start(),end,{k:v.value for k,v in members.items()},members)
        if raw=='(':
            values=[]
            while pos<len(tokens) and tokens[pos].group()!=')':
                values.append(value().value)
                if tokens[pos].group()!=')':take(',')
            return Node(token.start(),take(')').end(),values)
        if raw in '}=;,)' :raise ValueError('工程配置值错误')
        try:decoded=json.loads(raw) if raw.startswith('"') else raw
        except ValueError as error:raise ValueError('工程配置字符串错误') from error
        return Node(token.start(),token.end(),decoded)
    try:root=value()
    except (IndexError,KeyError,TypeError) as error:raise ValueError('无法解析工程配置') from error
    if pos!=len(tokens) or not isinstance(root.value,dict):raise ValueError('不是完整的 Xcode 工程配置')
    return root


def target_configurations(root,scheme):
    try:
        objects=root.members['objects'].members
        targets=[n for n in objects.values() if n.value.get('isa')=='PBXNativeTarget' and n.value.get('name')==scheme]
        if len(targets)!=1:raise ValueError('无法唯一定位工程 Target：'+scheme)
        ids=objects[targets[0].value['buildConfigurationList']].value['buildConfigurations']
        configs=[objects[key] for key in ids]
        if not configs or any(n.value.get('isa')!='XCBuildConfiguration' or not isinstance(n.value.get('buildSettings'),dict) for n in configs):
            raise ValueError('Target 构建配置不完整')
        return configs
    except (KeyError,TypeError,AttributeError) as error:raise ValueError('Target 配置引用不完整：'+scheme) from error


def read_settings(path,scheme):
    root=parse_project(Path(path).read_text())
    return {node.value['name']:node.value['buildSettings'] for node in target_configurations(root,scheme)}


def serialize(value):
    if isinstance(value,(tuple,list)):return '('+','.join(json.dumps(str(x),ensure_ascii=False) for x in value)+(',' if value else '')+')'
    return json.dumps(str(value),ensure_ascii=False)


def persist_settings(path,scheme,updates,prepend_paths=False):
    """写入目标所有配置；路径前置保留已有搜索目录，排除项同时覆盖旧条件项。"""
    path=Path(path)
    if path.is_symlink():raise ValueError('工程文件不能是符号链接')
    text=original=path.read_text();root=parse_project(text);edits=[]
    for config in target_configurations(root,scheme):
        settings=config.members['buildSettings'];desired=dict(updates)
        if 'EXCLUDED_ARCHS' in desired:
            desired.update({key:'' for key in settings.members if key.startswith('EXCLUDED_ARCHS[')})
        additions=[]
        for key,new in desired.items():
            old=settings.members.get(key)
            if prepend_paths and key.endswith('SEARCH_PATHS'):
                previous=old.value if old else []
                if not isinstance(previous,list):previous=[previous]
                new=list(dict.fromkeys([*new,*previous]))
            if old and old.value==new:continue
            rendered=serialize(new)
            if old:edits.append((old.start,old.end,rendered))
            else:additions.append('\n\t\t\t\t'+json.dumps(key)+' = '+rendered+';')
        if additions:edits.append((settings.end-1,settings.end-1,''.join(additions)+'\n\t\t\t'))
    for start,end,replacement in sorted(edits,reverse=True):text=text[:start]+replacement+text[end:]
    if not edits:return
    # 先复核生成后的结构再替换，解析失败不能留下半个工程文件。
    target_configurations(parse_project(text),scheme)
    if path.read_text()!=original:raise ValueError('工程文件被并发修改，拒绝覆盖')
    # 排他创建随机临时文件，不能沿用仓库里可预置为外部符号链接的固定文件名。
    descriptor,temporary=tempfile.mkstemp(prefix='.wm-project-',dir=path.parent)
    temporary=Path(temporary)
    try:
        with os.fdopen(descriptor,'w') as stream:
            stream.write(text);stream.flush();os.fsync(stream.fileno())
        temporary.replace(path)
    finally:temporary.unlink(missing_ok=True)
