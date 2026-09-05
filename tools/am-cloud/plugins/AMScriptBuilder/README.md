# AMScriptBuilder v1: offline, plan-based, new model only

One HXT turns a small Python model plan into native A:M splines. Edit a script,
not C++, to make another shape using the supported vocabulary. The runtime
helper and runner are embedded resources in the HXT: no Python DLL is loaded
into A:M, and no companion folder needs to be installed in the HXT directory.

This is an exploratory model-creation candidate, not yet an A:M-host-validated
transaction system. Use a disposable project until the host tests pass.
The existing smoke/report plugins, their workflows, SDK and build locks remain
unchanged. No merge, installation or known-good promotion is automatic.

## First test: no Python needed

With A:M closed, install only the Release **AMScriptBuilder_64.hxt** alongside
existing plugins. Keep this package's examples, documentation and symbols in
a separate working folder. Restart A:M, open a disposable project and right-click
a model or the Objects container in the Project Workspace:

**Plugins > Wizards > A:M Script Builder v1 - New Model**

The Group context also registers this same command for easier discovery. The
context object is never an editing target: every invocation builds a NEW model.

Select `examples/three_point_spline.json`. Review the counts, then confirm
creation. It describes one open peaked spline with three points and no
attachments. The new model opens and zooms to fit; save it manually and reopen
it to check persistence. Importing JSON does not invoke Python or evaluate code.

Next select `examples/grid.json`: nine logical points, six splines, 18 CP
occurrences and nine explicit attachments. Four planar quad patches are the
intended native result, not something the JSON validator can certify by itself.

## Run a Python script

Choose `examples/grid.py` in the same command. Select an installed **CPython
3.11 python.exe** (not py.exe, pythonw.exe or a Store launcher). The chooser
remembers that path for this A:M session but asks again; it does not search PATH,
install an interpreter or change registry settings. Runtime version is checked.
The CPython 3.11 patch is not frozen in this prototype. No pip packages required.

Confirm that you trust the selected script/interpreter. A separate Python
process calculates the plan while a modal progress dialog offers Cancel. Python
receives a snapshot of that script, not the live A:M model or any SDK pointers.
The native plugin independently validates the returned plan and asks for a
second confirmation before creating any native geometry.

Edit ROWS, COLUMNS or SPACING in a copy of `grid.py`, save, and invoke the command
again. The new script does not require recompiling the HXT. Changing the protocol
or embedded bridge/runner does require rebuilding it.

## Small script API

```python
from ambridge import ModelPlan

def build():
    plan = ModelPlan('My Shape')
    a = plan.point(0, 0, 0)
    b = plan.point(10, 10, 0)
    c = plan.point(20, 0, 0)
    plan.spline([a, b, c])
    return plan
```

Define `build()` with no arguments, returning ModelPlan or the equivalent dict.
Constants in the script are the v1 parameter interface. This version has no
editor, parameter UI, watcher, live replacement, selection modification,
network/API connection, packages installed on demand or arbitrary SDK console.
The runner adds only its embedded bridge directory to Python's import path;
standard library modules are available, but script sibling modules and user
site packages are not automatically imported. Debug prints go to stderr, not
the model protocol. Model names are deliberately restricted to simple ASCII.

## Model-plan v1 contract

Only these four JSON fields are accepted, exactly once, in any order:

```json
{"am_plan":1,"name":"Example","points":[[0,0,0],[10,0,0]],"splines":[[0,1]]}
```

Points use raw A:M model-space units, independently of displayed units.
Every spline is open and peaked. Indices are zero-based logical points. Reusing
an index in two DIFFERENT splines explicitly requests native CP attachment;
coincident positions with different indices are not welded. Reusing an index
inside the same spline is rejected: loops are out of scope in v1.

Limits: 256 KiB script/plan; 2-1024 points; 1-128 splines; 2-256 indices per
spline; 2048 total CP occurrences; at most two occurrences per logical point;
finite coordinates within +/-100000, representable as nonzero SDK floats when
nonzero. All points must be used. Repeated logical edges and consecutive positions
that collapse to the same SDK float vector are rejected. No hooks, bias controls,
smoothing options, explicit five-point patches, groups, bones or materials.
A:M patch discovery is requested once after building/attaching the splines.

The native parser accepts a deliberately limited JSON dialect: no BOM,
comments, escaped string characters, non-ASCII strings, unknown/duplicate fields,
trailing data, boolean indices or noninteger version/indices. The shipped
runner emits the accepted dialect. JSON is data; the HXT never evaluates it.

To generate a replayable JSON outside A:M using the packaged runtime sources:

```powershell
# Run from the extracted package, using your explicitly selected Python path.
& 'C:\Path\To\Python311\python.exe' -I -S -B -X utf8 runtime\runner.py examples\grid.py | Set-Content -Encoding ascii grid-plan.json
if ($LASTEXITCODE -ne 0) { throw 'Script failed: do not import its output.' }
```

Use a new output name to avoid overwriting a plan. Keep accepted script, constants,
resulting JSON and HXT receipt together. The HXT itself does not automatically
save scripts/plans or overwrite existing files.

## Failure, cancellation and security boundaries

Native validation happens before creating any model. File selection Cancel,
script failure, timeout, malformed output or declining the final confirmation
means no native creation is entered. The Python worker is supervised with a
15-second wall deadline, a 512 MiB process-memory cap, one active process, bounded
256 KiB stdout/16 KiB stderr, explicit executable/argument quoting, and a limited
inherited-handle list. It is created suspended, assigned to a kill-on-close job,
then started. Cancel/timeout/failure stops the worker without waiting for Python
to cooperate. The UI pumps its modal timer; SDK calls occur only afterward on
the command thread, not in the worker. Native SDK calls cannot be safely
preempted by the worker's time limit; there is no Cancel during native creation.

**These are reliability controls, not a security sandbox.** A trusted script
still runs with your Windows account's access to files, environment and network.
The plugin/bridge make no API/network requests, but arbitrary Python code can.
Do not run unreviewed or AI-generated scripts automatically. No API key is
required, read or submitted by the built-in workflow. Python isolation flags
are module-path controls, not security authorization.

Script/runner/bridge are copied into a unique, private-name TEMP directory for
each invocation. On exit only those three known files are removed, without
recursive deletion. A script that creates other files may leave that directory
behind; paths are local and are not uploaded. There is no output receipt/log
publication from a user's A:M session.

**Native creation is not transactional in this prototype.** It never targets
existing geometry, but SDK failure after HModelCache::New can leave a partial
NEW model. The user is warned and must delete it through A:M before retrying.
Do not use `delete` on an SDK handle as a substitute for deleting its model:
that is not an established ownership/rollback contract. No whole-build Undo/Redo
promise is made. Remove the generated model to discard it, and verify save/reload.
The earlier reversible CP-translation/undo test remains separate future work.

## Development and automation

Source: `tools/am-cloud/plugins/AMScriptBuilder/`.
Workflow: `.github/workflows/am-script-builder.yml`.
Builds Release and Debug with the existing locked builder. It runs the existing
helper tests, new Python tests, native parser tests and real Windows worker
success/failure/output/timeout/cancellation tests. It checks runner-generated
fixtures through the native parser, checks embedded resources against source
using LoadLibraryEx DATAFILE (no DllMain), then seals a plugin-specific package.
The original native build receipt is preserved; distribution-receipt.json records
its original ZIP hash and the verified Python resource hashes. The final shipped
verifier must accept the intact package and reject modified HXT/example copies.

No local C++ compiler or private repository is required to test a successful
Release candidate. A Debug HXT needs a matching Debug A:M host. Native CI never
sets runtime_tested true. Record actual host results using HOST-TEST.md.

Primary implementation references:
- https://docs.python.org/3.11/using/cmdline.html
- https://learn.microsoft.com/en-us/windows/win32/procthread/job-objects
- https://learn.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-createpipe
- SDK 19.5: HModel.h (New, StartSpline, AttachCPs, Update, FindPatches, OpenView),
  HPatch.h (CreateCPAtTail), HCP.h (SetPeaked), HProject.h (UpdateAllViews).

Developed with AI assistance. Existing Hash SDK and third-party notices and
rights are unchanged; no new interpreter distribution is bundled by this PR.
