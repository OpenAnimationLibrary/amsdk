"""Compile and execute the shared message protocol on the locked Windows toolchain."""
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
    with tempfile.TemporaryDirectory(prefix='message-protocol-', dir=parent) as directory:
        work = Path(directory).resolve()
        lock = json.loads((HERE / 'toolchain.lock.json').read_text(encoding='utf-8'))
        env, installation = visual_studio_environment(work, lock)
        compiler = installation / 'VC/Tools/MSVC' / lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        source = HERE / 'plugins/MessageExchange/ProtocolTests.cpp'
        executable = work / 'protocol-tests.exe'
        runtime = '/MDd' if os.environ.get('AM_CONFIGURATION') == 'Debug' else '/MD'
        subprocess.run([str(compiler), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX',
                        runtime, str(source), '/Fo' + str(work / 'protocol-tests.obj'),
                        '/Fe' + str(executable)], env=env, cwd=work, check=True, timeout=60)
        subprocess.run([str(executable)], env=env, cwd=work, check=True, timeout=30)


if __name__ == '__main__':
    main()
