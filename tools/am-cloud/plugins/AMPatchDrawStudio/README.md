# A:M Patch Draw Studio 0.2 — exploratory host-test candidate

A persistent Python drawing/painting window plus a small modeless native A:M
receiver. Draw and paint a draft, send it as a new named group into an explicitly
chosen model, move/edit that group in A:M, and send another shape without closing
Studio. Existing sent geometry and paint snapshots are never replaced by later
draft edits. This is a side-by-side successor, not an overwrite of Patch Draw
0.1 or Script Builder. It does not change the Script Builder JSON contract.

**Build tests do not validate A:M host behavior. Use a disposable model first.**
Native group selection, smooth surfaces, decal orientation, undo, repeated sends,
closing/changing projects and save/reopen remain explicit manual test gates.

## Start here

1. Extract the complete Release package. Run `Verify-Package.ps1` in PowerShell
   to check every packaged file against `SHA256SUMS.txt`. This is an integrity
   check, not a signature or a security sandbox.
2. Close A:M. Copy only `AMPatchDrawStudio_64.hxt` into the same HXT folder used
   for your working plugins. Leave the older Patch Draw and Script Builder in
   place. Do not copy import libraries or install Debug output into ordinary A:M.
3. Studio needs Python with Tkinter and Pillow. The tested Windows interpreter
   is 64-bit CPython 3.12; the dependency is pinned in `requirements.txt`. Run
   `Install_Dependencies.cmd` only when Pillow is missing. It asks before pip
   changes your selected Python. No installation happens when Studio starts.
4. Run `Run_Studio.cmd`. To select another installed Python explicitly:
   `Run_Studio.cmd "C:\Path\To\Python312\python.exe"`. The optional
   `PATCHDRAW_PYTHON` environment variable is another explicit choice.
5. Choose a **persistent folder beside your A:M project**, not a temporary
   directory. Studio creates a fresh session folder there. Each native paint
   decal refers to a PNG in this folder; retain it with the model.
6. In A:M open/name a disposable model. Invoke its model-context command
   **Plugins / Wizards / A:M Patch Draw Studio v0.2 - Connect**. Invocation from
   one of its groups is also supported. This is not an Action/Choreography
   instance command. Use Studio's **Copy connection path** button and paste
   that path into the receiver's file chooser.
7. Studio displays the bound model name. Draw a small shape, enter its name,
   apply the shape settings, and press **Send to A:M**. Confirm the target in
   A:M. The next send is enabled after acknowledgement. Both windows stay open.

The destination is deliberately **bound**, not silently switched when focus
changes. Disconnect the small receiver and reconnect from another model to
retarget it. A fresh project lookup and per-send confirmation avoid retaining
borrowed SDK handles across window events. Rename, close or Save As the project
and reconnect when requested. Models with duplicate destination names are
rejected. Names/paths are not persistent object IDs; the confirmation remains
important when a project/model was replaced with another of the same name.

## Drawing and real curved splines

Draw/Erase paints occupied cells. Wheel zooms; middle drag pans; Fit resets the
view. Escape, capture loss or focus loss cancels an unfinished drawing stroke.
Draw Undo/Redo is independent of painting history and A:M undo.

Grid choices range from 3 to 64 cells per side. **Refine x2** preserves world size
and the draft's painted coverage; it resets drawing undo history. Width/Height
change model-space size, not pixel density. A source cell expands into four
native quadrilateral patches, preserving the tested hole/diagonal-contact
construction. A full 64-by-64 sheet has 16,384 intended patches, 16,641 logical
points, 258 open splines and 33,282 native CP occurrences. Fragmented masks have
different counts; the status line shows actual complexity before sending.

Profiles are Flat, Arch X, Arch Y, Dome and Saddle. Rise can be positive or
negative. XY/XZ/YZ chooses the construction plane; Origin positions the draft
in the model. These are patch sheets, not automatically thickened solids.

**Native Smooth splines** calls the real SDK `HCP::SetSmooth()`; unchecking it
uses `SetPeaked()`. Unlike Script Builder v1, Studio is not limited to peaked
approximations. A flat straight grid remains straight even with Smooth enabled;
choose a curved profile or edit its control points in A:M to see curvature.
**Soften draft outline** is a separate mild boundary relaxation. It does not
change connectivity or turn every painted stair-step into a fitted vector path.
Holes, disconnected islands and original cell membership are retained.

## Named groups and repeated sends

Every Send creates one new CP group: `PD_<shape name>_001`, `_002`, and so on,
without reusing a case-insensitively matching name. The group includes both
spline occurrences of each logical point and is highlighted in the Project
Workspace after a successful send. Select the group in A:M to move/edit the
shape. All islands in one submitted draft belong to that one group; use separate
sends for separately selectable shapes. Names use 1–40 ASCII characters: start
with a letter/digit; remaining characters may include spaces, dot, underscore
and hyphen. Existing groups are not renamed or recolored.

New geometry is not welded to pre-existing CPs merely because positions match.
Later sends do not inherit manual changes made to earlier sent geometry.
The current implementation has no live replacement, automatic group deletion,
extrusion, hooks, bones, materials editor or explicit five-point patch creation.

## Patch Paint — integrated QuickDecal Painter

The second tab reuses the earlier Python **QuickDecal Painter 1.1** texture
canvas, projected-patch painting, selection, brush, eraser, color picker, patch
fill and undo/redo. `vendor-provenance.json` identifies the recovered source;
`vendor-depth-hook.patch` documents its one extension hook. The bundled ZIP is
ordinary inspectable Python source, imported with Python's zipimport; it is not
an executable binary. It contains no earlier sample meshes or images.

Paint in the texture atlas or on the projected patch preview. **One patch**
constrains a stroke to its selected patch. The eraser restores the baseline
image, not alpha transparency; Edit can set current paint as the new baseline.
Textures are RGB, with 256/512/1024/2048 pixels per side. Texture density is
independent of native topology density. File / Resize draft texture resamples
paint and clears paint undo; use the highest resolution only when useful.

The Python model view is explicitly a **corner-triangle proxy**, not an A:M
curved-patch renderer or exact depth buffer. Overlapping/folded projections can
be ambiguous: use atlas selection/painting for an exact UV edit. Above 4,096
patches automatic model-preview updates pause; atlas painting remains available.
Use Update preview to inspect, or re-enable Live for projected painting. Paused
previews cannot be used for stale hit-testing. The inspector lists the first
2,048 patches; all patches remain accessible through the atlas.

Paint undo is bounded to approximately 48 MiB of retained image snapshots
(maximum 32 steps; three at 2048 pixels). Patch-mask caching holds at most four
masks. Loss of paint-canvas focus finishes the stroke as one undo step.

## Save, send and retain assets

**Save Draft** writes a `.patchdraw` ZIP containing coverage/settings and the
current PNG. Load validates it before replacing the working draft. Reopening
uses the saved PNG as the eraser baseline; undo history is not serialized.
Closing prompts for unsaved drawing/paint changes. Saving a draft is not saving
the native model: use A:M's own Save for that.

With **Include a paint snapshot** checked, Send writes a fresh PNG named with
the session ID and sequence number. The receiver assigns UVs by matched native
patch corner identity, never by assuming patch enumeration order. The decal is
named after the new group. The snapshot is not silently overwritten or removed
on exit. Exporting draft paint is separate and does not update old A:M decals.

Retain/copy the whole session folder with the A:M project, or use A:M's normal
asset relocation tools. The first version does not package/rebase A:M's external
texture references for you. Paths unrepresentable by the legacy SDK's Windows
code page are rejected before geometry mutation; use a compatible folder or
send without paint. UTF-8 Windows ACP is handled separately.

## Interrupted sends and undo

Only one request may be pending. A receiver exclusively owns its session. It
claims a journal entry before mutation and never automatically retries an
unacknowledged operation. A:M confirms each target. Native construction runs on
the host UI thread, not a background SDK thread; large sends can briefly block
A:M. Existing host modal operations defer pending requests.

A failure after creation starts may leave a partial group. **Do not blindly
resend, delete journals or assume rollback.** Inspect the named group and A:M's
undo state. Save the draft, disconnect, and create a new Studio session only
after resolving the partial output. All texture snapshots/journals remain.
`SaveAllToUndo()` is called, but one-step atomic undo of geometry/groups/decals/
image clips is NOT claimed until the exact host tests pass. No speculative
SDK object deletion was introduced.

## Development and validation

The native project is `AMPatchDrawStudio.vcxproj`; build through the repository's
locked `tools/am-cloud/build.py`. Windows CI runs the existing build-helper
regressions, portable topology/recipe tests, the actual C++ protocol parser,
real Tk/Pillow GUI tests, Release/Debug native builds, PE/import/export/warning
audits and whole-package integrity/tamper checks. Fake receiver results in GUI
tests exercise frontend transfer state only, not native A:M mutation.

Keep `runtime_tested: false` in generated receipts. Record real host results
separately using `HOST-TEST.md`. This source/build is AI-assisted development;
review and human host validation remain required before merge or normal use.
