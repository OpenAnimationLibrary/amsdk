# AMScriptBuilder v1 host validation

CI checks the build, parser, Python worker and package, NOT creation inside A:M.
Do not infer a pass from a previous smoke/report plugin. Keep the PR draft until
these creation cases are tested on disposable data. Ordinary A:M uses Release.

## Install and recover

Verify the package using Verify-Package.ps1 (respect local script policy), or
compare the plugin hash with build-receipt.json and the manifest. Close A:M,
back up any previous AMScriptBuilder HXT outside scanned folders and install
ONLY AMScriptBuilder_64.hxt. Keep examples/runtime/PDB/docs in a separate folder.
Restart A:M. No SDK or C++ compiler is required. Script execution supports
64-bit CPython 3.11 or 3.12; importing supplied JSON does not require Python.

Menu: model/Objects entry in Project Workspace > Plugins > Wizards >
**A:M Script Builder v1 - New Model**. A Group selection also exposes this
same new-model command, not an edit-selection command.

Every successful run adds a new model; it never replaces an old result.
Existing geometry is not an input/target, but the project does gain an object
and the active view may change. Save any valuable project first and test in a
new disposable project. No full-build Undo or atomic rollback is promised.
A native error can leave a partial new model; delete it through A:M before retrying.
Close A:M before replacing/removing this HXT to roll back a plugin version.

## Known-input tests (record only what was actually exercised)

1. Import examples/three_point_spline.json. Confirm three logical/three spline
   CPs, one open peaked spline, no attachments/patches, bounds (-10,0,0) to
   (10,10,0). Save the model manually, close/reopen and verify geometry persists.
2. Import examples/grid.json. Confirm six splines, 18 CP records and nine shared
   logical points. The corrected build treats AttachCPs()'s Boolean as
   `second CP deleted during attachment`, not success/failure. The intended native
   result is four quad patches, bounds (0,0,0) to (20,20,0). Use AMModelReport as
   an additional check, not a substitute for inspection.
3. Import examples/five_point_candidate.json. Before creation the dialog should
   report exactly one five-point topology candidate with boundary [0,1,2,3,4].
   After A:M FindPatches(), record the actual HPatch5 count shown. A candidate is
   only a topology prediction; a count mismatch is diagnostic, not a plugin error.
4. Run the matching .py examples with either supported 64-bit CPython 3.11 or
   3.12. They should describe the same geometry as their JSON fixtures. Record the
   exact interpreter version and both native/script route results.
5. Edit a COPY of grid.py: SPACING=5.0; rerun without rebuilding/replacing HXT.
   New grid bounds should be (0,0,0) to (10,10,0); previous models stay unchanged.
6. Decline trust confirmation; cancel a file chooser; decline Build after
   validation. No new model should appear. Cancel the Python progress dialog
   with a trusted test script containing `while True: pass`; no model is created.
7. Let that loop reach its timeout. Confirm error and responsive A:M afterward.
   Test syntax error/missing build() and a JSON copy with an invalid point index.
   None should enter native creation. Do not raise limits to make failures pass.
8. Rerun twice. Confirm separate results rather than replacement; remove each
   generated model through A:M to discard. Confirm the application remains usable.

Undo/Redo for the multi-step build, automatic deletion after partial native
failure, complex surfaces, other A:M versions and Debug host execution are NOT
established by this test. Do not deliberately corrupt live native pointers.

## Report

Package/run/attempt and HXT SHA-256:
PR head / tested checkout:
A:M About version / Windows version:
JSON fixture / script and any changed constants:
Python version/path (script route):
Menu context:
Validated counts / five-point candidate count:
Resulting spline, point, attachment, standard-patch and HPatch5 counts:
Visible bounds / peaked shape:
Save/reopen:
No changes to previous models:
Cancel / timeout / bad-plan behavior:
Application usable afterward:
Unexpected partial model / other errors:

No automatic host-success promotion or merge. Preserve the tested HXT, PDB,
accepted script/JSON and receipts together; package artifacts expire.
