"""Exercise the production coordinate parser and endpoint guard in native C++."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(HERE))
from build import visual_studio_environment


class MakeaBoneTests(unittest.TestCase):
    def test_coordinates_native(self):
        work_root = HERE / '.work'
        work_root.mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=work_root) as directory:
            work = Path(directory)
            source = HERE / 'plugins/MakeaBone/CoordinatesTests.cpp'
            if os.name == 'nt':
                lock = json.loads((HERE / 'toolchain.lock.json').read_text())
                env, _ = visual_studio_environment(work, lock)
                compiler = shutil.which('cl.exe', path=env['PATH'])
                executable = work / 'coordinate-tests.exe'
                command = [compiler, '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX',
                           str(source), '/Fe:' + str(executable), '/Fo:' + str(work / 'tests.obj')]
            else:
                env = None
                compiler = shutil.which('g++') or shutil.which('clang++')
                if not compiler:
                    self.skipTest('Native C++ compiler unavailable')
                executable = work / 'coordinate-tests'
                command = [compiler, '-std=c++20', '-Wall', '-Wextra', '-Werror',
                           str(source), '-o', str(executable)]
            result = subprocess.run(command, cwd=work, env=env, capture_output=True,
                                    text=True, timeout=90)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], cwd=work, env=env,
                                    capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
