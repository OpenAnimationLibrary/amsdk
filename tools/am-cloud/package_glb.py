"""Make a source + Visual Studio + SDK kit around an unchanged audited package."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import zipfile

from build_support import archive_name, sha256, verify_hash

HERE = Path(__file__).resolve().parent
REPOSITORY = HERE.parent.parent



def package(native_zip: Path, output: Path) -> Path:
    if output.exists():
        raise ValueError('Choose a new kit output directory.')
    expected = native_zip.with_suffix('.zip.sha256').read_text().split()[0]
    verify_hash(native_zip, expected)
    with tempfile.TemporaryDirectory() as temporary:
        root = Path(temporary) / 'AMGLBImport-0.1.5'
        native = root / 'plugin'
        native.mkdir(parents=True)
        with zipfile.ZipFile(native_zip) as archive:
            for member in archive.infolist():
                relative = archive_name(member.filename)
                destination = native.joinpath(*relative.parts)
                if member.is_dir():
                    destination.mkdir(parents=True, exist_ok=True)
                else:
                    destination.parent.mkdir(parents=True, exist_ok=True)
                    with archive.open(member) as src, destination.open('xb') as dst:
                        shutil.copyfileobj(src, dst)
        receipt = json.loads((native / 'build-receipt.json').read_text())
        commit = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=REPOSITORY,
                                         text=True).strip()
        if (receipt['status'] != 'passed' or receipt['configuration'] != 'Release' or
                receipt['plugin']['file'] != 'AMGLBImport_64.hxt' or
                receipt['source']['checkout_commit'] != commit):
            raise ValueError('Expected this checkout\'s audited AMGLBImport Release package.')
        verify_hash(native / 'AMGLBImport_64.hxt', receipt['plugin']['sha256'])
        source = root / 'source'
        source.mkdir()
        plugin_source = HERE / 'plugins/AMGLBImport'
        tracked = subprocess.check_output(['git', 'ls-files', '--', str(plugin_source.relative_to(REPOSITORY))], cwd=REPOSITORY, text=True).splitlines()
        for relative in tracked:
            path = REPOSITORY / relative
            destination = source / path.relative_to(plugin_source)
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(path, destination)
        shutil.copy2(HERE / 'test-results/tests.log', root / 'CORE-AND-BUILDER-TESTS.log')
        shutil.copy2(source / 'HOST-TEST-GLB.md', root / 'HOST-TEST-GLB.md')
        shutil.copy2(source / 'README.md', root / 'README.md')
        sdk_lock = json.loads((HERE / 'sdk.lock.json').read_text())
        verify_hash(HERE / 'vendor/sdk195.zip', sdk_lock['sha256'])
        shutil.copy2(HERE / 'vendor/sdk195.zip', root / 'sdk195.zip')
        for name in ('sdk.lock.json', 'toolchain.lock.json'):
            shutil.copy2(HERE / name, root / name)
        (root / 'KIT-SHA256SUMS.txt').write_text(''.join(
            f'{sha256(path)}  {path.relative_to(root).as_posix()}\n'
            for path in sorted(root.rglob('*')) if path.is_file()), encoding='utf-8')
        output.mkdir(parents=True)
        run = receipt['source']['run_id'] or 'local'
        kit = output / f'AMGLBImport-0.1.5-Release-x64-r{run}-{commit[:12]}-kit.zip'
        with zipfile.ZipFile(kit, 'x', zipfile.ZIP_DEFLATED) as archive:
            for path in sorted(root.rglob('*')):
                if path.is_file():
                    archive.write(path, path.relative_to(root.parent).as_posix())
        kit.with_suffix('.zip.sha256').write_text(f'{sha256(kit)}  {kit.name}\n', encoding='utf-8')
        return kit


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('native_zip', type=Path)
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    print(package(args.native_zip, args.output))
