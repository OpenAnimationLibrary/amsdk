"""Run FontWiz2's Windows API and GDI tests without loading A:M."""
import json
import os
import shutil
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
        resource = work / 'fontwiz2-tests.res'
        # CreateProcess resolves executable names using the parent's PATH, not
        # the replacement environment. Resolve the selected SDK tool explicitly.
        resource_compiler = shutil.which('rc.exe', path=env['PATH'])
        if not resource_compiler:
            raise RuntimeError('Locked Windows SDK resource compiler is absent.')
        subprocess.run([resource_compiler, '/nologo', '/I' + str(folder), '/fo' + str(resource),
                        str(folder / 'FontWiz2.rc')], env=env, cwd=work, check=True, timeout=30)
        runtime = '/MDd' if os.environ.get('AM_CONFIGURATION') == 'Debug' else '/MD'
        subprocess.run([str(compiler), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX', runtime,
                        *[str(folder / name) for name in ('NativeTests.cpp', 'GlyphOutline.cpp',
                                                          'Settings.cpp', 'SettingsTests.cpp',
                                                          'Wizard.cpp', 'WizardTests.cpp', 'Inspector.cpp', 'InspectorTests.cpp', 'ModelCopy.cpp')],
                        '/Fo' + work.as_posix() + '/', '/Fe' + str(executable),
                        '/link', str(resource), 'gdi32.lib', 'user32.lib', 'comdlg32.lib'],
                       env=env, cwd=work, check=True, timeout=60)
        subprocess.run([str(executable)], env=env, cwd=work, check=True, timeout=30)


if __name__ == '__main__':
    main()
