"""Run FontWiz2's Windows API and GDI tests without loading A:M."""
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
    with tempfile.TemporaryDirectory(prefix='fontwiz2-test-', dir=parent) as directory:
        work = Path(directory).resolve()
        lock = json.loads((HERE / 'toolchain.lock.json').read_text(encoding='utf-8'))
        env, installation = visual_studio_environment(work, lock)
        compiler = installation / 'VC/Tools/MSVC' / lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        folder = HERE / 'plugins/FontWiz2'
        executable = work / 'fontwiz2-tests.exe'
        runtime = '/MDd' if os.environ.get('AM_CONFIGURATION') == 'Debug' else '/MD'
        subprocess.run([str(compiler), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX', runtime,
                        str(folder / 'NativeTests.cpp'), str(folder / 'GlyphOutline.cpp'),
                        '/Fo' + work.as_posix() + '/', '/Fe' + str(executable),
                        '/link', 'gdi32.lib', 'user32.lib'], env=env, cwd=work, check=True, timeout=60)
        subprocess.run([str(executable)], env=env, cwd=work, check=True, timeout=30)


if __name__ == '__main__':
    main()
