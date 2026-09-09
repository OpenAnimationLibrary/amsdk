# AMGLBImport 0.1.6 native host acceptance — pending

Record the exact HXT SHA-256 from the original receipt, A:M version, Release/Debug
host type, OS, menu context and results. Keep `runtime_tested: false` in the
build-generated receipt; append independent host evidence in a reviewed update.

New option checks, in addition to the default-behavior checks below:

- Verify the dialog title is 0.1.6. Target `0` and omission off preserve 0.1.5
  conversion counts. Changing either option disables Import until Update preview.
  Enter/Import must never use stale results. Reject invalid/out-of-range targets.
- Set a lower patch budget on a dense curved mesh. Review target versus actual,
  inspect shape/detail and color boundaries, then import. A protected cube at a
  target of 1 should stay at 6 patches and explicitly report the target was not
  reached. A larger budget should not add density. Test lower-density inputs
  with sharp edges, multiple material regions, Mirror Z and a changed scale.
- Enable omission for `triangle.glb`: zero patches, Import disabled, no new model.
  `mixed_region.glb`: one quad, the triangle area empty. Original sword: 1,398
  quads, 932 omitted triangles, two omitted parts. Check actual counts and holes.
  Test a triangle enclosed by quads: the surrounding quads must remain and the
  hole must stay empty after Find Patches, save/reload and rendering.
- Combine a lower target with omission. Toggle options back to full density;
  the original source must be reused, without cumulative simplification/deletion.
  Cancel after preview, including after a preview error, and confirm no edits.
  Inspect neutral Seam points groups and independent attachments at cutouts.

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
5. Color regression: `two_color_parts.glb` must show one red square and one blue
   square. Both part selection groups must show Surface as Not Set. The separate material
   groups must show their red/blue surface colors. Check specular size **80%**,
   intensity **20%**, reflectivity **0%** and transparency **0%**. In the saved
   MDL, the first two must be `SpecularSize=80` and `SpecularIntensity=20`, not
   the 0.1.2 values 8000 and 2000. Inspect both shaded appearance and a render.
   For an alpha-blended source at alpha 0.25, verify transparency **75%**;
   an opaque source must remain at **0%**, regardless of its alpha factor.
   Selecting, renaming or reordering groups must not turn either patch white. Verify
   these colors after saving/reloading. No unused Default/catch-all color group
   should appear. `color_boundary.glb` must show eight red squares around a blue
   center; the blue center must stay blue after group reordering and save/reload.
   Import must finish without the 0.1.1 “missing patch surface” error.
6. `curved_quad_sphere.glb`: 96 four-sided patches, no subdivision, no junction
   with more than two spline CPs. Inspect eight three-edge junctions and curved
   patch interiors. Default scale gives bounds -100..100 cm on each axis.
   Repeat with Mirror Z and changed scale. `shallow_fan.glb` must produce three
   quads from six triangles; its center must have only two spline CP records.
   `crowded_pole.glb` must reach the preview and import 24 quads. The original
   `simple_sword.glb` must reach the preview and import 5,544 quads, 13 material
   groups, and seams in nine parts. Neither should show the 0.1.4 crowded-junction
   refusal. Check matching seam sides in shaded/wireframe views, preserved colors,
   and the reported seam counts. `Part / Seam points` selection groups must remain
   Surface = Not Set and include every copy of each separated point. Move only one
   seam-side CP to demonstrate its independent attachment, then undo that edit.
   Seams may open under deformation; do not interpret them as welded continuity.
   Repeat with Mirror Z and changed scale, and with an existing model selected;
   existing work must remain intact. Cancel at the seam preview and verify no edits.
7. Confirm four distinct native corner CP heads per patch; no three/five-point
   patches, orphan geometry, unintended patches, missing surfaces or merged parts.
   At each generated three-way center, check one through-spline plus one ending
   spline, with only two attached CP records. Check continuous grid lines and
   closed paths. The plugin verifies native positions, edges and CP counts, but
   this cannot certify shading, patch interiors or interactive editing.
   Three/four-edge attachments are allowed; five or more edges on one attachment
   are not. Separate attachments may share a spatial position along fallback seams.
8. Save the new model, close/reopen it and the project; counts, groups, appearance
   and dimensions should survive. Render a frame. Repeated import should create
   separate models without changing earlier models or corrupting lifetime/ownership.
9. Test Undo/Redo and deletion of the new model. Record actual behavior: this
   version creates a new model and does not promise a single atomic Undo entry.
   Existing models must remain unchanged. If conversion fails, a named incomplete
   model may remain; it must remain inspectable/removable without a crash.
10. Close A:M, restore the prior binary (or remove this new HXT), restart and verify
   the rollback. Do not install the Debug artifact in ordinary A:M.

Release and Debug CI results alone leave all these runtime checks pending.

## Earlier owner evidence

The owner supplied two saved A:M 19.5 PC models after reporting white imports.
Both have empty `<MATERIALS>` lists and correct red/blue group diffuse values
and CP lists. Both also retain specular size 8000 and intensity 2000; a newly
added working group sets only green diffuse color. This establishes a percentage
unit error in the imported groups, not a missing color assignment. The exact
installed HXT hash is unknown. The owner subsequently reported the 0.1.3 fix
working. The owner then reported 0.1.4 rejecting the original sword at its
two-spline topology preflight. This is the regression addressed by 0.1.5; acceptance
of the new binary, including its unwelded seams, remains pending.
The owner subsequently described 0.1.5 as "Much improved" and requested density
and omission options. That feedback does not establish acceptance of this new
0.1.6 HXT or its option-specific behavior; its exact host test remains pending.
