"""Locked Windows core/MFC tests. Does not load an HXT or run Animation:Master."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

PLUGIN = Path(__file__).resolve().parents[1]
HERE = PLUGIN.parents[1]
sys.path.insert(0, str(HERE))
from build import visual_studio_environment, run


def main():
    logs = HERE / 'test-results/patch-draw'
    logs.mkdir(parents=True, exist_ok=True)
    scratch = HERE / '.work'
    scratch.mkdir(exist_ok=True)
    lock = json.loads((HERE / 'toolchain.lock.json').read_text())
    with tempfile.TemporaryDirectory(prefix='patch-tests-', dir=scratch) as directory:
        work = Path(directory).resolve()
        env, install = visual_studio_environment(work, lock)
        cl = install / 'VC/Tools/MSVC' / lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        core = work / 'CoreTests.exe'
        run([str(cl), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX',
             str(PLUGIN/'tests/CoreTests.cpp'), '/Fo'+str(work/'core.obj'), '/Fe'+str(core)],
            env, logs/'core-compile.log', timeout=90)
        fixtures = work/'fixtures'
        run([str(core), str(fixtures)], env, logs/'core-tests.log', timeout=60)
        # Validate EVERY exported 3x3 mask with the unchanged Script Builder Python validator.
        sys.path.insert(0, str(HERE/'plugins/AMScriptBuilder/runtime'))
        from ambridge import validate
        files = sorted(fixtures.glob('*.json'))
        if len(files) != 511:
            raise ValueError('Expected all 511 nonempty 3x3 masks')
        for file in files:
            validate(json.loads(file.read_text(encoding='utf-8')))
        (logs/'cross-language.log').write_text('PASS: all 511 nonempty 3x3 exports accepted by unchanged ambridge validator\n')
        # Use the actual native parser too; no reimplementation of its acceptance gate.
        verifier = work/'PlanTests.exe'
        run([str(cl), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX',
             str(HERE/'plugins/AMScriptBuilder/tests/PlanTests.cpp'),
             '/Fo'+str(work/'plan.obj'), '/Fe'+str(verifier)], env, logs/'plan-compile.log', timeout=90)
        for file in files:
            result = subprocess.run([str(verifier), str(file)], env=env, capture_output=True, timeout=10)
            if result.returncode:
                raise ValueError('Native plan rejection: '+file.name+' '+result.stderr.decode(errors='replace'))
        with (logs/'cross-language.log').open('a') as stream:
            stream.write('PASS: all 511 nonempty 3x3 exports accepted by unchanged native Script Builder parser\n')
        rc = shutil.which('rc.exe', path=env['PATH'])
        resource = work/'canvas.res'
        run([rc, '/nologo', '/fo'+str(resource), str(PLUGIN/'AMPatchDraw.rc')], env, logs/'ui-resource.log', timeout=60)
        ui = work/'WindowsTests.exe'
        # /W3 here matches the HXT project; the SDK-independent core uses /W4 /WX.
        run([str(cl), '/nologo', '/EHsc', '/std:c++20', '/W3', '/WX', '/utf-8', '/MD',
             '/D_AFXDLL', '/DNOMINMAX', '/D_WIN32_WINNT=0x0A00', '/DWINVER=0x0A00',
             str(PLUGIN/'tests/WindowsTests.cpp'), str(PLUGIN/'CanvasDialog.cpp'), str(resource),
             '/Fo'+work.as_posix()+'/', '/Fe'+str(ui), '/link', 'Comdlg32.lib'],
            env, logs/'ui-compile.log', timeout=90)
        run([str(ui), str(work)], env, logs/'windows-ui-tests.log', timeout=60)
        image = work/'canvas-preview.bmp'
        if image.is_file():
            shutil.copy2(image, logs/image.name)
    print('PASS: Patch Draw core, existing JSON validators, MFC canvas and Windows export tests')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
