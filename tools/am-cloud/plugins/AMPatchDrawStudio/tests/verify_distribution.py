"""Exercise the shipped PowerShell verifier against intact and altered payloads."""
from pathlib import Path
import subprocess,tempfile,zipfile
ROOT=Path(__file__).resolve().parents[1]; HERE=ROOT.parents[1]
packages=list((HERE/'artifacts/studio-packages').glob('*.zip'))
if len(packages)!=1: raise ValueError('Expected one sealed Studio package')
with tempfile.TemporaryDirectory(prefix='studio-verify-',dir=HERE/'.work') as td:
    folder=Path(td)
    with zipfile.ZipFile(packages[0]) as z:z.extractall(folder)
    verifier=folder/'Verify-Package.ps1'
    def verify(ok,label):
        run=subprocess.run(['pwsh','-NoProfile','-File',str(verifier)],capture_output=True,text=True,timeout=45)
        (HERE/'artifacts/diagnostics'/f'studio-{label}.log').write_text(run.stdout+run.stderr,encoding='utf-8')
        if (run.returncode==0)!=ok:raise AssertionError(label)
    verify(True,'intact')
    hxt=[p for p in folder.iterdir() if p.suffix in ('.hxt','.hxtd')]
    if len(hxt)!=1:raise AssertionError('Expected one native HXT')
    for path in [hxt[0],folder/'runtime/patch_draw_studio.py',folder/'runtime/quickdecal-1.1-studio.zip',folder/'PATCH-DRAW-STUDIO.md']:
        original=path.read_bytes();path.write_bytes(original+b'altered')
        verify(False,'rejected-'+path.name.replace('.','-'))
        path.write_bytes(original)
    verify(True,'restored')
print('PASS: intact/restored packages accepted; altered HXT, Python, painter source and documentation rejected')
