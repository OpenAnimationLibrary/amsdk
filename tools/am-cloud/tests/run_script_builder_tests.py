"""Use the locked Windows tools for parser and Python-process integration tests."""
import json
from pathlib import Path
import sys
import tempfile

HERE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(HERE))
from build import visual_studio_environment, run


def main():
    logs = HERE / 'test-results'; logs.mkdir(exist_ok=True)
    scratch = HERE / '.work'; scratch.mkdir(exist_ok=True)
    lock = json.loads((HERE/'toolchain.lock.json').read_text())
    plugin = HERE / 'plugins/AMScriptBuilder'
    with tempfile.TemporaryDirectory(prefix='script-tests-', dir=scratch) as folder:
        work = Path(folder).resolve()
        env, install = visual_studio_environment(work, lock)
        compiler = install / 'VC/Tools/MSVC' / lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        for name in ('PlanTests', 'WorkerTests'):
            exe = work / (name + '.exe')
            run([str(compiler), '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX', '/utf-8',
                 '/D_WIN32_WINNT=0x0A00', str(plugin/'tests'/(name+'.cpp')),
                 '/Fo'+str(work/(name+'.obj')), '/Fe'+str(exe)], env, logs/(name+'-compile.log'), timeout=60)
            arguments = [str(exe)]
            if name == 'WorkerTests': arguments += [sys.executable, str(work)]
            run(arguments, env, logs/(name+'.log'), timeout=30)
            if name == 'PlanTests':
                for fixture in ('three_point_spline', 'grid'):
                    # Cross-language check: real Python output also passes native parser.
                    generated = work/(fixture+'.json')
                    import subprocess
                    result = subprocess.run([sys.executable, '-I', '-S', '-B', '-X', 'utf8',
                        str(plugin/'runtime/runner.py'), str(plugin/'examples'/(fixture+'.py'))],
                        capture_output=True, timeout=5, check=True)
                    generated.write_bytes(result.stdout)
                    actual = run([str(exe), str(generated)], env, logs/(fixture+'-native-plan.log'), timeout=10).strip()
                    expected = '3 1 3 0' if fixture == 'three_point_spline' else '9 6 18 9'
                    if actual != expected: raise ValueError('Cross-language fixture totals disagree: ' + actual)
    return 0


if __name__ == '__main__': raise SystemExit(main())
