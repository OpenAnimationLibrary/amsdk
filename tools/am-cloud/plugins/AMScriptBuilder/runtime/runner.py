"""Run one explicitly trusted local script; emit one bounded model plan.

Called with CPython 3.11: python.exe -I -S -B -X utf8 runner.py script.py
Isolation flags prevent accidental module-path injection, NOT malicious scripts.
The HXT supervises time/memory/output and validates all returned data again.
"""
from __future__ import annotations
import contextlib
import json
from pathlib import Path
import sys
import traceback


def main() -> int:
    if sys.version_info[:2] != (3, 11) or sys.implementation.name != 'cpython':
        raise RuntimeError('This prototype requires CPython 3.11. Select its python.exe.')
    if len(sys.argv) != 2:
        raise RuntimeError('Expected exactly one script path.')
    # Only the packaged bridge is added. User script sibling directories and
    # user site packages are not implicitly imported.
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from ambridge import ModelPlan, validate, MAX_BYTES
    script = Path(sys.argv[1])
    source = script.read_bytes()
    if not source or len(source) > MAX_BYTES:
        raise ValueError('Script must be nonempty and at most 256 KiB.')
    namespace = {'__name__': 'am_user_script', '__file__': str(script)}
    # Keep stdout reserved for the protocol. Debug prints go to bounded stderr.
    with contextlib.redirect_stdout(sys.stderr):
        exec(compile(source, str(script), 'exec'), namespace)
        entry = namespace.get('build')
        if not callable(entry):
            raise ValueError('Script must define build() returning ModelPlan or a plan dict.')
        result = entry()
        result = result.to_dict() if isinstance(result, ModelPlan) else validate(result)
    data = json.dumps(result, ensure_ascii=True, allow_nan=False, separators=(',', ':')).encode('ascii')
    if len(data) > MAX_BYTES:
        raise ValueError('Plan exceeds 256 KiB.')
    sys.stdout.buffer.write(data)
    sys.stdout.buffer.flush()
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except Exception:
        traceback.print_exc(limit=6, file=sys.stderr)
        raise SystemExit(1)
