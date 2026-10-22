"""一次安装宿主资源阶段，之后每次构建自动恢复厂商原来的根目录资源契约。"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil
import tempfile

try:
    from .project_settings import parse_project, serialize, target_configurations
except ImportError:
    from _project_settings import parse_project, serialize, target_configurations


def _digest(path):
    # 路径长度、类型和固定长度内容摘要分开编码，避免不同目录结构拼成相同字节串。
    path = Path(path)
    if path.is_symlink(): raise ValueError('资源包不能是符号链接：' + str(path))
    h = hashlib.sha256()
    for p in sorted(path.rglob('*')):
        if p.is_symlink(): raise ValueError('资源包不能包含符号链接：' + str(p))
        relative = p.relative_to(path).as_posix().encode()
        h.update(b'F' if p.is_file() else b'D')
        h.update(len(relative).to_bytes(8, 'big'))
        h.update(relative)
        if p.is_file():
            content = hashlib.sha256()
            with p.open('rb') as stream:
                for chunk in iter(lambda: stream.read(1024 * 1024), b''): content.update(chunk)
            h.update(content.digest())
    return h.hexdigest()


def sync_resources(spec, products, app):
    """暂存后提交并记录意图；重试只接管哈希匹配的受管输出，宿主文件只借用。"""
    products, app = Path(products).resolve(), Path(app).resolve()
    marker = app / '.xad-spm-resources.json'
    stage = app / '.xad-spm-stage'
    if marker.is_symlink() or stage.is_symlink(): raise ValueError('资源事务路径不能是符号链接')
    old = json.loads(marker.read_text()) if marker.exists() else {}
    managed = dict(old.get('managed', {}))
    borrowed = dict(old.get('borrowed', {}))
    pending = old.get('pending', {})
    previous = {n: {h} for n, h in managed.items()}
    for n, h in pending.get('managed', {}).items(): previous.setdefault(n, set()).add(h)
    wrappers = dict(old.get('wrappers', {}))
    wrappers.update(pending.get('wrappers', {}))
    for mapping in (managed, borrowed, pending.get('managed', {}), pending.get('borrowed', {})):
        if not isinstance(mapping, dict) or any(not isinstance(n, str) or Path(n).name != n or not n.endswith('.bundle') for n in mapping):
            raise ValueError('受管资源清单不合法')
    planned, next_managed, next_borrowed = {}, {}, {}
    for target, names in spec.items():
        wrapper = 'AdWangMaiSDK_' + target + '.bundle'
        wrappers[wrapper] = names
        for name in names:
            if Path(name).name != name or not name.endswith('.bundle'): raise ValueError('资源名称不合法：' + name)
            source = products / wrapper / name
            if not source.is_dir() or not source.resolve().is_relative_to(products):
                raise ValueError('SPM 资源缺失：' + str(source) + '；请确认宿主已添加对应 Package 产品')
            digest = _digest(source)
            if name in planned and planned[name][1] != digest: raise ValueError('重复资源不一致：' + name)
            dest = app / name
            if dest.is_symlink(): raise ValueError('输出资源不能是符号链接：' + name)
            if dest.exists():
                actual = _digest(dest)
                if name in previous:
                    if actual not in previous[name] | {digest}: raise ValueError('受管资源已被宿主替换：' + name)
                    next_managed[name] = digest
                else:
                    if actual != digest: raise ValueError('宿主存在同名资源，拒绝覆盖：' + name)
                    next_borrowed[name] = digest
            else: next_managed[name] = digest
            planned[name] = (source, digest)
    for name, hashes in previous.items():
        if name in planned: continue
        dest = app / name
        if dest.is_symlink() or (dest.exists() and _digest(dest) not in hashes):
            raise ValueError('待清理资源已被宿主替换：' + name)
    # 外层目录由 Xcode 创建，不能沿宿主符号链接清理包外目录；所有校验先于事务提交。
    for wrapper, names in wrappers.items():
        if Path(wrapper).name != wrapper or not wrapper.startswith('AdWangMaiSDK_'): raise ValueError('资源包装名称不合法')
        if (app / wrapper).is_symlink(): raise ValueError('资源包装不能是符号链接')
        for name in names:
            if Path(name).name != name or not name.endswith('.bundle'): raise ValueError('嵌套资源名称不合法')
            if (app / wrapper / name).is_symlink(): raise ValueError('嵌套资源不能是符号链接')
    app.mkdir(parents=True, exist_ok=True)
    if stage.exists(): shutil.rmtree(stage)
    stage.mkdir()
    # 所有目录复制完成后才接触最终输出；复制中断只留下可安全丢弃的专用暂存目录。
    for name in next_managed: shutil.copytree(planned[name][0], stage / name)
    def save(record):
        temp = stage / 'marker.json'
        temp.write_text(json.dumps(record, sort_keys=True) + '\n')
        os.replace(temp, marker)
    save({'managed': managed, 'borrowed': borrowed, 'wrappers': old.get('wrappers', {}),
          'pending': {'managed': next_managed, 'borrowed': next_borrowed, 'wrappers': wrappers}})
    for name in next_managed:
        dest = app / name
        if dest.exists(): os.replace(dest, stage / ('previous-' + name))
        os.replace(stage / name, dest)
    for name in previous.keys() - planned.keys():
        dest = app / name
        if dest.exists(): os.replace(dest, stage / ('removed-' + name))
    # 只移除外层资源 bundle 中的嵌套副本，保留 Xcode 所拥有的外层目录和 Info.plist。
    for wrapper, names in wrappers.items():
        for name in names:
            nested = app / wrapper / name
            if nested.exists(): shutil.rmtree(nested)
    save({'managed': next_managed, 'borrowed': next_borrowed, 'wrappers': wrappers})
    shutil.rmtree(stage)


def _script(spec):
    # 脚本自包含，不依赖 SDK 下载缓存的绝对路径或 CocoaPods/Ruby。
    import inspect
    body = '\n'.join(inspect.getsource(x) for x in (_digest, sync_resources))
    return ('set -eu\n/usr/bin/python3 - <<\'XAD_SPM_RESOURCES\'\n'
            'import hashlib, json, os, shutil\nfrom pathlib import Path\n' + body + '\n'
            'sync_resources(' + repr(spec) + ', os.environ["BUILT_PRODUCTS_DIR"], '
            'Path(os.environ["TARGET_BUILD_DIR"]) / os.environ["UNLOCALIZED_RESOURCES_FOLDER_PATH"])\n'
            'XAD_SPM_RESOURCES\n')


def install(project, target, package, adapters):
    """幂等编辑指定 Target；其他 Target、已有 flags 和用户工程内容保持。"""
    project = Path(project)
    path = project / 'project.pbxproj'
    if path.is_symlink(): raise ValueError('工程文件不能是符号链接')
    meta = json.loads((Path(package) / 'SPMIntegration.json').read_text())
    if meta.get('format') != 1 or set(adapters) - set(meta['adapters']): raise ValueError('包版本或适配器选择不匹配')
    selected = ['AdWangMaiSDKSupport', *(x + 'Support' for x in adapters)]
    spec = {k: meta['resources'][k] for k in selected if meta['resources'].get(k)}
    original = text = path.read_text()
    root = parse_project(text)
    objects = root.members['objects']
    matches = [(k, n) for k, n in objects.members.items() if n.value.get('isa') == 'PBXNativeTarget' and n.value.get('name') == target]
    if len(matches) != 1: raise ValueError('不能唯一定位宿主 Target：' + target)
    tid, node = matches[0]
    phase_id = hashlib.sha256(('XAdSPM:' + tid).encode()).hexdigest()[:24].upper()
    existing = objects.members.get(phase_id)
    if existing and existing.value.get('name') != 'XAdSPM 自动资源': raise ValueError('工程对象 ID 冲突')
    inputs = ['$(BUILT_PRODUCTS_DIR)/AdWangMaiSDK_' + x + '.bundle' for x in spec]
    names = sorted({n for ns in spec.values() for n in ns})
    outputs = ['$(TARGET_BUILD_DIR)/$(UNLOCALIZED_RESOURCES_FOLDER_PATH)/' + x for x in [*names, '.xad-spm-resources.json', '.xad-spm-stage', *['AdWangMaiSDK_' + x + '.bundle/' + n for x, ns in spec.items() for n in ns]]]
    if existing:
        outputs = list(dict.fromkeys([*existing.value.get('outputPaths', []), *outputs]))
    phase = {'isa': 'PBXShellScriptBuildPhase', 'buildActionMask': '2147483647', 'files': [],
             'inputPaths': inputs, 'outputPaths': outputs, 'name': 'XAdSPM 自动资源',
             'shellPath': '/bin/sh', 'shellScript': _script(spec), 'alwaysOutOfDate': '1',
             'showEnvVarsInLog': '0', 'runOnlyForDeploymentPostprocessing': '0'}
    rendered = '{\n' + ''.join('\t' + serialize(k) + ' = ' + serialize(v) + ';\n' for k, v in phase.items()) + '}'
    edits = []
    if existing: edits.append((existing.start, existing.end, rendered))
    else: edits.append((objects.end - 1, objects.end - 1, '\n' + phase_id + ' = ' + rendered + ';\n'))
    phases = node.members.get('buildPhases')
    if phases is None: raise ValueError('宿主 Target 缺少 buildPhases')
    ids = [x for x in phases.value if x != phase_id] + [phase_id]
    edits.append((phases.start, phases.end, serialize(ids)))
    for config in target_configurations(root, target):
        settings = config.members['buildSettings']
        old = settings.members.get('OTHER_LDFLAGS')
        flags = old.value if old else ['$(inherited)']
        if isinstance(flags, str): flags = shlex.split(flags)
        flags = [*flags] + ([] if '-ObjC' in flags else ['-ObjC'])
        if old: edits.append((old.start, old.end, serialize(flags)))
        else: edits.append((settings.end - 1, settings.end - 1, '\nOTHER_LDFLAGS = ' + serialize(flags) + ';\n'))
    for start, end, value in sorted(edits, reverse=True): text = text[:start] + value + text[end:]
    parse_project(text)
    if text == original: return
    if path.read_text() != original: raise ValueError('工程被并发修改，拒绝覆盖')
    fd, temporary = tempfile.mkstemp(prefix='.xad-spm-', dir=path.parent)
    try:
        with os.fdopen(fd, 'w') as stream: stream.write(text)
        os.replace(temporary, path)
    finally:
        if Path(temporary).exists(): Path(temporary).unlink()


def main():
    parser = argparse.ArgumentParser(description='自动安装 SPM 资源阶段和 -ObjC，无需手动添加 bundle')
    parser.add_argument('--project', required=True)
    parser.add_argument('--target', required=True)
    parser.add_argument('--package', default=str(Path(__file__).resolve().parent.parent))
    parser.add_argument('--adapters', nargs='*', default=[])
    args = parser.parse_args()
    install(args.project, args.target, args.package, args.adapters)
    print('已安装自动资源阶段；后续构建无需手动添加资源。')


if __name__ == '__main__': main()
