"""Build/run the real bounded protocol parser using the locked Windows compiler."""
import json
from pathlib import Path
import sys
import tempfile
PLUGIN=Path(__file__).resolve().parents[1]
HERE=PLUGIN.parents[1]
sys.path.insert(0,str(HERE))
from build import visual_studio_environment,run
from native_checks import check

def main():
    logs=HERE/'test-results/studio';logs.mkdir(parents=True,exist_ok=True)
    scratch=HERE/'.work';scratch.mkdir(exist_ok=True)
    lock=json.loads((HERE/'toolchain.lock.json').read_text())
    with tempfile.TemporaryDirectory(prefix='studio-tests-',dir=scratch) as td:
        work=Path(td).resolve();env,install=visual_studio_environment(work,lock)
        cl=install/'VC/Tools/MSVC'/lock['vc_tools_version']/'bin/Hostx64/x64/cl.exe'
        exe=work/'PlanCheck.exe'
        run([str(cl),'/nologo','/EHsc','/std:c++20','/W4','/WX',str(PLUGIN/'tests/PlanCheck.cpp'),'/Fo'+str(work/'plan.obj'),'/Fe'+str(exe)],env,logs/'parser-compile.log',timeout=90)
        check(exe,work)
    print('PASS: native protocol checks; A:M host construction is NOT tested')

if __name__=='__main__':main()
