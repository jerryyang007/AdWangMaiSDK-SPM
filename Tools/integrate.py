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


def _digest(path, include_empty=False, control=None):
    # 路径长度、类型和固定长度内容摘要分开编码，避免不同目录结构拼成相同字节串。
    path = Path(path)
    if path.is_symlink(): raise ValueError('资源包不能是符号链接：' + str(path))
    entries = sorted(path.rglob('*'))
    nonempty = set()
    for p in entries:
        if control: control.check()
        if p.is_symlink(): raise ValueError('资源包不能包含符号链接：' + str(p))
        if p.is_file(): nonempty.update(p.parents)
    h = hashlib.sha256()
    for p in entries:
        if control: control.check()
        # Xcode 为历史/新增输出预建空目录，它们不代表资源内容变更；真实文件及其目录结构仍参与摘要。
        # include_empty 只尝试匹配可验证的旧摘要；无法确认旧内容时拒绝覆盖并要求清理构建。
        if p.is_dir() and not include_empty and p not in nonempty: continue
        relative = p.relative_to(path).as_posix().encode()
        h.update(b'F' if p.is_file() else b'D')
        h.update(len(relative).to_bytes(8, 'big'))
        h.update(relative)
        if p.is_file():
            content = hashlib.sha256()
            with p.open('rb') as stream:
                # 网页导出可取消；独立宿主脚本不传 control，摘要格式与旧版本完全一致。
                for chunk in iter(lambda: stream.read(1024 * 1024), b''):
                    if control: control.check()
                    content.update(chunk)
            h.update(content.digest())
    return h.hexdigest()


def sync_resources(spec, products, app):
    """暂存后提交并记录意图；非空旧输出按哈希确认所有权，宿主内容只借用。"""
    def empty_directory_tree(path):
        # Xcode 会在脚本执行前为已声明的输出创建父目录；这些空目录尚不是宿主资源。
        # 只接受不含任何文件或符号链接的目录树；不可读目录直接失败，不能当作空目录。
        pending = [path]
        while pending:
            with os.scandir(pending.pop()) as entries:
                for entry in entries:
                    if entry.is_symlink() or not entry.is_dir(follow_symlinks=False): return False
                    pending.append(entry.path)
        return True

    products, app = Path(products).resolve(), Path(app).resolve()
    marker = app / '.xad-spm-resources.json'
    stage = app / '.xad-spm-stage'
    if marker.is_symlink() or stage.is_symlink(): raise ValueError('资源事务路径不能是符号链接')
    old = json.loads(marker.read_text()) if marker.exists() else {}
    def ownership_error(name):
        message = '受管资源已被宿主替换或摘要无法确认：' + name
        if old.get('digest_format', 1) < 2:
            message += '；旧版摘要若包含空目录，请执行 Xcode Product > Clean Build Folder 后重新构建'
        return ValueError(message)
    managed = dict(old.get('managed', {}))
    borrowed = dict(old.get('borrowed', {}))
    pending = old.get('pending', {})
    previous = {n: {h} for n, h in managed.items()}
    for n, h in pending.get('managed', {}).items(): previous.setdefault(n, set()).add(h)
    retired = set(old.get('retired', []))
    if any(not isinstance(n, str) or Path(n).name != n or not n.endswith('.bundle') for n in retired):
        raise ValueError('历史受管资源清单不合法')
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
                if actual != digest and empty_directory_tree(dest):
                    # 冷构建和提交中断后的重试都可能先得到 Xcode 预建的空输出目录。
                    next_managed[name] = digest
                elif name in previous:
                    if actual not in previous[name] | {digest} and _digest(dest, include_empty=True) not in previous[name]:
                        raise ownership_error(name)
                    next_managed[name] = digest
                else:
                    if actual == digest: next_borrowed[name] = digest
                    else: raise ValueError('宿主存在同名资源，拒绝覆盖：' + name)
            else: next_managed[name] = digest
            planned[name] = (source, digest)
    for name, hashes in previous.items():
        if name in planned: continue
        dest = app / name
        if dest.is_symlink() or (dest.exists() and not empty_directory_tree(dest)
                                 and _digest(dest) not in hashes and _digest(dest, include_empty=True) not in hashes):
            raise ownership_error(name)
    # 只记住真正由脚本管理过的资源，借用的宿主同名资源永不进入持续清理清单。
    retired = (retired | previous.keys()) - planned.keys()
    for name in retired:
        if (app / name).is_symlink(): raise ValueError('历史资源不能是符号链接：' + name)
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
    save({'managed': managed, 'borrowed': borrowed, 'wrappers': old.get('wrappers', {}), 'retired': sorted(retired),
          'digest_format': old.get('digest_format', 1),
          'pending': {'managed': next_managed, 'borrowed': next_borrowed, 'wrappers': wrappers}})
    for name in next_managed:
        dest = app / name
        if dest.exists(): os.replace(dest, stage / ('previous-' + name))
        os.replace(stage / name, dest)
    for name in previous.keys() - planned.keys():
        dest = app / name
        if dest.exists(): os.replace(dest, stage / ('removed-' + name))
    # 历史输出权限必须保留到升级/撤销重试完成；后续增量构建会重新预建空父目录，需持续清理。
    # 非空目录说明宿主已有实际文件，不能按历史名称删除。
    for name in retired:
        dest = app / name
        if dest.exists() and empty_directory_tree(dest): shutil.rmtree(dest)
    # 只移除外层资源 bundle 中的嵌套副本，保留 Xcode 所拥有的外层目录和 Info.plist。
    for wrapper, names in wrappers.items():
        for name in names:
            nested = app / wrapper / name
            if nested.exists(): shutil.rmtree(nested)
    save({'managed': next_managed, 'borrowed': next_borrowed, 'wrappers': wrappers, 'retired': sorted(retired), 'digest_format': 2})
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


def _resource_file_lists(meta, package, spec, previous_outputs):
    """逐项声明资源树与事务路径；目录节点本身不能授予沙箱对子文件的访问。"""
    products = '$(BUILT_PRODUCTS_DIR)/'
    app = '$(TARGET_BUILD_DIR)/$(UNLOCALIZED_RESOURCES_FOLDER_PATH)/'
    inputs = []
    outputs = list(previous_outputs) + [app + '.xad-spm-resources.json', app + '.xad-spm-stage',
                                        app + '.xad-spm-stage/marker.json']
    for target, names in meta['resources'].items():
        wrapper = 'AdWangMaiSDK_' + target + '.bundle'
        for name in names:
            selected = name in spec.get(target, [])
            if selected:
                # SwiftPM 的 App 资源复制可能与脚本融合调度；显式等待外层 bundle 复制完成再去重。
                # 仅依赖 BUILT_PRODUCTS_DIR 中的素材无法约束最终 App 的 Copy 任务。
                inputs.append(app + wrapper)
            if not selected and app + name not in previous_outputs:
                continue
            if Path(name).name != name or not name.endswith('.bundle'):
                raise ValueError('资源名称不合法：' + name)
            source = Path(package) / 'Sources' / target / 'Resources' / name
            if not source.is_dir():
                if selected: raise ValueError('包内资源缺失：' + str(source))
                continue
            # 旧安装阶段只有 bundle 目录声明；首次迁移时也补齐其清理所需的目录内容。
            entries = [source, *sorted(source.rglob('*'))]
            for path in entries:
                if path.is_symlink(): raise ValueError('资源包不能包含符号链接：' + str(path))
                suffix = '' if path == source else '/' + path.relative_to(source).as_posix()
                if '\n' in suffix or '\r' in suffix: raise ValueError('资源路径不能包含换行')
                if selected: inputs.append(products + wrapper + '/' + name + suffix)
                outputs.extend([app + name + suffix, app + wrapper + '/' + name + suffix])
    # 保留历史文件声明，使升级、撤销适配器及中断重试仍可读取、移动和清理旧资源。
    # 暂存区内的新副本、previous-*、removed-* 都使用同一相对目录清单。
    for output in list(outputs):
        if not output.startswith(app): continue
        relative = output[len(app):]
        first = relative.split('/', 1)[0]
        if not first.endswith('.bundle') or first.startswith('AdWangMaiSDK_'): continue
        for prefix in ('', 'previous-', 'removed-'):
            outputs.append(app + '.xad-spm-stage/' + prefix + relative)
    return list(dict.fromkeys(inputs)), list(dict.fromkeys(outputs))


def _write_file_list(path, entries):
    """将共享清单原子写入宿主工程；重复集成不改写相同内容，也不跟随符号链接。"""
    if path.is_symlink() or path.parent.is_symlink() or path.parent.parent.is_symlink():
        raise ValueError('资源文件清单不能是符号链接：' + str(path))
    text = ''.join(entry + '\n' for entry in entries)
    if path.exists() and path.read_text() == text: return
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix='.xad-spm-', dir=path.parent)
    try:
        with os.fdopen(fd, 'w') as stream: stream.write(text)
        os.replace(temporary, path)
    finally:
        if Path(temporary).exists(): Path(temporary).unlink()


def install(project, target, package, adapters):
    """幂等安装指定 Target 的阶段和共享文件清单，保持其他 Target、已有 flags 与沙箱设置。"""
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
    list_directory = 'xcshareddata/XAdSPM/'
    input_list = project / list_directory / (phase_id + '-inputs.xcfilelist')
    output_list = project / list_directory / (phase_id + '-outputs.xcfilelist')
    previous_outputs = list(existing.value.get('outputPaths', [])) if existing else []
    if output_list.is_symlink(): raise ValueError('资源文件清单不能是符号链接')
    if existing and output_list.exists(): previous_outputs.extend(output_list.read_text().splitlines())
    inputs, outputs = _resource_file_lists(meta, package, spec, previous_outputs)
    # 文件清单由 Xcode 展开，不为每个路径导出一个环境变量，避免完整资源树触及参数长度上限。
    phase = {'isa': 'PBXShellScriptBuildPhase', 'buildActionMask': '2147483647', 'files': [],
             'inputPaths': [], 'outputPaths': [],
             'inputFileListPaths': ['$(PROJECT_FILE_PATH)/' + list_directory + input_list.name],
             'outputFileListPaths': ['$(PROJECT_FILE_PATH)/' + list_directory + output_list.name],
             'name': 'XAdSPM 自动资源',
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
    if path.read_text() != original: raise ValueError('工程被并发修改，拒绝覆盖')
    _write_file_list(input_list, inputs)
    _write_file_list(output_list, outputs)
    if text == original: return
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
