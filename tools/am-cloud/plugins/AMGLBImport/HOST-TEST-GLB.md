# AMGLBImport native host acceptance — not yet performed

Record the exact HXT SHA-256 from the original receipt, A:M version, Release/Debug
host type, OS, menu context and results. Keep `runtime_tested: false` in the
build-generated receipt; append independent host evidence in a reviewed update.

1. With A:M closed, back up the old binary. Verify and install the Release HXT
   in the known working HXT folder. Keep the previous file available for rollback.
2. Registration: Objects, Model and model Group show Import → GLB as Quad Patches.
   Action/Chor instances and invalid/null contexts must not redirect edits into a
   source model. Repeat opening menus, launching, closing and reopening the plugin.
3. Cancel the file chooser and preview separately; no model, group or dirty flag
   should be added. A malformed, external-buffer or oversized file should fail
   before creating a new model. Test a missing/unreadable file.
4. `square.glb`: one four-sided patch. `triangle.glb`: three quads.
   `mixed_region.glb`: seven quads, no cracks. `cube.glb`: six patches, correct
   inside/outside normals and no internal accidental patches. Inspect both shaded
   and wireframe views. CPs should be peaked; move a shared CP to verify connectivity.
5. `simple_sword.glb`: 13 named parts; 5,202 quads. At default 100 cm/unit, bounds
   are approximately X -19..19 cm, Y 1.082623..132.700002 cm, Z -2.5..2.5 cm.
   Verify blade/guard/grip orientation, sharp silhouette, materials and open accents.
   Repeat with Mirror Z and a changed scale. Verify per-part and per-material groups.
6. Confirm four distinct native corner CP heads per patch; no three/five-point
   patches, orphan geometry, unintended patches, missing surfaces or merged parts.
   The plugin verifies corner positions/count, but this cannot certify tangent
   behavior, patch interiors, winding, material assignment or interactive editing.
7. Save the new model, close/reopen it and the project; counts, groups, appearance
   and dimensions should survive. Render a frame. Repeated import should create
   separate models without changing earlier models or corrupting lifetime/ownership.
8. Test Undo/Redo and deletion of the new model. Record actual behavior: this
   version creates a new model and does not promise a single atomic Undo entry.
   Existing models must remain unchanged. If conversion fails, a named incomplete
   model may remain; it must remain inspectable/removable without a crash.
9. Close A:M, restore the prior binary (or remove this new HXT), restart and verify
   the rollback. Do not install the Debug artifact in ordinary A:M.

Release and Debug CI results alone leave all these runtime checks pending.
