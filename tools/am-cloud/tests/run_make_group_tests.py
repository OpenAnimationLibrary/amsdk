"""Compile and test Make Group's cube data with the locked Windows toolchain."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

HERE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(HERE))
from build import visual_studio_environment

def main():
    parent = HERE / '.work'
    parent.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='make-group-test-', dir=parent) as directory:
        work = Path(directory).resolve()
        lock = json.loads((HERE / 'toolchain.lock.json').read_text(encoding='utf-8'))
        env, installation = visual_studio_environment(work, lock)
        compiler = installation / 'VC/Tools/MSVC' / lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        folder = HERE / 'plugins/MakeGroup'
        executable = work / 'cube-tests.exe'
        runtime = '/MDd' if os.environ.get('AM_CONFIGURATION') == 'Debug' else '/MD'
        log = HERE / 'test-results/make-group-native.log'
        log.parent.mkdir(exist_ok=True)
        for args, timeout in [
            ([str(compiler), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX', runtime,
              str(folder / 'CubeTests.cpp'), '/Fo' + work.as_posix() + '/',
              '/Fe' + str(executable)], 60),
            ([str(executable)], 10)
        ]:
            result = subprocess.run(args, cwd=work, env=env, capture_output=True,
                                    text=True, timeout=timeout)
            with log.open('a', encoding='utf-8') as output:
                output.write(result.stdout + result.stderr)
            print(result.stdout + result.stderr, end='')
            result.check_returncode()

if __name__ == '__main__':
    main()
