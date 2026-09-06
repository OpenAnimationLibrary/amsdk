"""Seal the exact audited Studio HXT together with its runtime and source."""
import json
from pathlib import Path
import shutil
import sys
import tempfile
import zipfile

ROOT=Path(__file__).resolve().parent
HERE=ROOT.parents[1]
sys.path.insert(0,str(HERE))
from build_support import archive_name, seal_package, sha256, write_json


def main():
    packages=list((HERE/'artifacts/packages').glob('*.zip'))
    if len(packages)!=1: raise ValueError('Expected one freshly audited native package')
    original=packages[0]
    if sha256(original)!=original.with_suffix('.zip.sha256').read_text().split()[0]:
        raise ValueError('Native archive checksum mismatch')
    with tempfile.TemporaryDirectory(prefix='studio-package-',dir=HERE/'.work') as temp:
        folder=Path(temp)
        with zipfile.ZipFile(original) as z:
            entries=z.infolist(); names=[str(archive_name(e.filename)) for e in entries]
            if len(entries)>32 or sum(e.file_size for e in entries)>64*1024*1024 or len(set(n.casefold() for n in names))!=len(names):
                raise ValueError('Unexpected native archive payload')
            if z.testzip(): raise ValueError('Native ZIP integrity failure')
            z.extractall(folder)
        manifest=folder/'SHA256SUMS.txt'; seen=set()
        for line in manifest.read_text().splitlines():
            digest,name=line.split('  ',1); name=str(archive_name(name))
            if name in seen or sha256(folder/name)!=digest: raise ValueError('Native payload checksum mismatch')
            seen.add(name)
        if seen!={p.relative_to(folder).as_posix() for p in folder.rglob('*') if p.is_file() and p!=manifest}:
            raise ValueError('Unmanifested native payload')
        receipt=json.loads((folder/'build-receipt.json').read_text())
        if receipt['status']!='passed' or receipt['project']!='tools/am-cloud/plugins/AMPatchDrawStudio/AMPatchDrawStudio.vcxproj':
            raise ValueError('Wrong or failed native project')
        if sha256(folder/receipt['plugin']['file'])!=receipt['plugin']['sha256']: raise ValueError('HXT/receipt mismatch')
        for name in ('Run_Studio.cmd','Install_Dependencies.cmd','requirements.txt','HOST-TEST.md','vendor-provenance.json','vendor-depth-hook.patch'):
            shutil.copy2(ROOT/name,folder/name)
        shutil.copy2(ROOT/'README.md',folder/'PATCH-DRAW-STUDIO.md')
        runtime=folder/'runtime';runtime.mkdir()
        for name in ('patch_draw_studio.py','studio_core.py','quickdecal-1.1-studio.zip'):
            shutil.copy2(ROOT/'runtime'/name,runtime/name)
        provenance=json.loads((ROOT/'vendor-provenance.json').read_text())
        if sha256(runtime/'quickdecal-1.1-studio.zip')!=provenance['source_zip_sha256']:
            raise ValueError('Bundled painter source changed')
        # A complete plugin source archive permits local review without shipping
        # the SDK, old sample models, cached bytecode or local user workspaces.
        paths=[p for p in ROOT.iterdir() if p.is_file()]
        paths += [ROOT/'runtime'/name for name in ('patch_draw_studio.py','studio_core.py','quickdecal-1.1-studio.zip')]
        paths += list((ROOT/'tests').glob('*.py'))+list((ROOT/'tests').glob('*.cpp'))
        with zipfile.ZipFile(folder/'Studio-Source.zip','w',zipfile.ZIP_DEFLATED) as z:
            for path in sorted(paths): z.write(path,path.relative_to(ROOT).as_posix())
        write_json(folder/'distribution-receipt.json',{
            'native_package':original.name,'native_package_sha256':sha256(original),'source':receipt['source'],
            'scope':'persistent drawing/paint frontend and named-group native receiver',
            'runtime_tested':False,'python_target':'3.12','paint_dependency':'Pillow 12.3.0',
            'manual_host_gate':'HOST-TEST.md; not performed by CI'})
        (folder/'READ-ME-FIRST.txt').write_text(
            'A:M PATCH DRAW STUDIO 0.2 — EXPLORATORY HOST-TEST CANDIDATE\n\n'
            f"Configuration: {receipt['configuration']} x64\nPlugin: {receipt['plugin']['file']}\n"
            f"HXT SHA-256: {receipt['plugin']['sha256']}\nCheckout: {receipt['source']['checkout_commit']}\n\n"
            'Read PATCH-DRAW-STUDIO.md before testing. CI is NOT an A:M host test.\n'
            'Run Verify-Package.ps1, then install ONLY the new HXT with A:M closed.\n'
            'Keep the older Patch Draw and Script Builder plugins.\n'
            'Run_Studio.cmd starts the persistent Python drawing and painting window.\n'
            'Install_Dependencies.cmd is an EXPLICIT optional Pillow installation.\n'
            'Choose a persistent project-side folder; sent PNG snapshots must be kept.\n'
            'Connect from the intended model with the v0.2 Studio Connect wizard.\n'
            'Each Send adds a NEW named group. Neither window closes after a send.\n'
            'Test small shapes first. Do not assume one-step atomic undo or rollback.\n'
            + ('\nDEBUG HOST ONLY — NOT FOR ORDINARY A:M.\n' if receipt['configuration']=='Debug' else ''),encoding='utf-8')
        manifest.unlink()
        destination=HERE/'artifacts/studio-packages'/original.name
        digest=seal_package(folder,destination)
        write_json(HERE/'artifacts/diagnostics/studio-package.json',{'file':destination.name,'sha256':digest})
        print('PASS: audited HXT unchanged; Studio runtime/source/instructions sealed')

if __name__=='__main__':main()
