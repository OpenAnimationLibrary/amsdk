"""Compile/run SDK-independent report math tests with the locked Windows tools."""
import json
from pathlib import Path
import sys
import tempfile

HERE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(HERE))
from build import visual_studio_environment, run


def main() -> int:
    logs = HERE / 'test-results'
    logs.mkdir(exist_ok=True)
    scratch = HERE / '.work'
    scratch.mkdir(exist_ok=True)
    lock = json.loads((HERE / 'toolchain.lock.json').read_text(encoding='utf-8'))
    with tempfile.TemporaryDirectory(prefix='report-math-', dir=scratch) as name:
        work = Path(name).resolve()
        env, install = visual_studio_environment(work, lock)
        compiler = install / 'VC/Tools/MSVC' / lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        source = HERE / 'plugins/ReadOnlyReports/ReportMathTests.cpp'
        exe = work / 'report-math-tests.exe'
        run([str(compiler), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX',
             str(source), '/Fo' + str(work / 'report-math-tests.obj'),
             '/Fe' + str(exe)], env, logs / 'report-math-compile.log', timeout=60)
        run([str(exe)], env, logs / 'report-math-tests.log', timeout=30)
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except Exception as error:
        print('Report math tests failed: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
