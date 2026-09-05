"""Run one explicitly trusted local script; emit one bounded model plan.

Supported interpreters: CPython 3.11 or 3.12 x64, launched as a separate process.
Isolation flags prevent accidental module-path injection, NOT malicious scripts.
The HXT supervises time/memory/output and validates all returned data again.
"""
from __future__ import annotations
import contextlib
import json
from pathlib import Path
import struct
import sys
import traceback

SUPPORTED = {(3, 11), (3, 12)}


def main() -> int:
    version = sys.version_info[:2]
    if (version not in SUPPORTED or sys.implementation.name != 'cpython'
            or struct.calcsize('P') * 8 != 64):
        raise RuntimeError('Requires 64-bit CPython 3.11 or 3.12. Select its python.exe.')
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
