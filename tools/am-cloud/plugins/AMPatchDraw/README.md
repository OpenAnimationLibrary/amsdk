# AMPatchDraw v0.1 — canvas and JSON export

**Stage B candidate.** Paint where surface should exist, inspect its proposed
quad layout, and export a JSON plan for the existing AMScriptBuilder. This HXT
makes **no A:M model changes**. It has no Build New Model button yet. Direct
construction and exact native-face readback are the next gate, not hidden in
this canvas milestone.

Rodney reported that `patch_draw_ring_probe.json` works in A:M in this session.
That is human evidence for that ring probe, not a claim that this new HXT, every
mask, native face identity, normals, smooth CPs, or save/reopen have been tested.

## Install and first drawing

Verify the Release package. With A:M closed, copy only `AMPatchDraw_64.hxt` into
the active HXT folder. It sits alongside AMScriptBuilder and the report/smoke
plugins; it does not replace them or the installed Terrain Wizard. Keep the
PDB, instructions and receipt outside scanned HXT folders. Restart A:M.

Right-click a model or Objects entry in the Project Workspace (Group context
also registers) and choose **Plugins > Wizards > A:M Patch Draw v0.1 - Canvas**.
The selected object is never read as geometry, edited or retained.

Choose **3** cells per side, leave Cell size at **10**, and click **New Drawing**.
Use the default **0.5-cell diameter** brush. Click the eight perimeter cells,
leaving the center unpainted. Expected preview: **8 painted cells, 32 proposed
quads, 48 logical points, 16 splines, 96 CP records, 1 component, 1 hole**.

Select **Export Plan...** and choose a NEW `.json` filename in your working
folder. Existing files are never overwritten. Close the canvas and import that
JSON using **A:M Script Builder v1 - New Model** from its corrected run #19 (or
a later separately verified compatible version). No Python is needed for
painting, exporting, or importing JSON. Native geometry is created only when
you subsequently confirm Build in Script Builder.

## Controls and boundaries

Draw adds occupied cells; Erase removes them. No duplicate layers accumulate.
The thin lines within each painted cell show its four proposed native patches.
Colors distinguish connected components for preview only; they are not A:M
materials/groups. The larger grid shows the coarser drawing-cell boundary.

Brush diameter (0.5, 1, 2 or 4 drawing cells) controls stroke width independently
of resolution. The displayed model-space brush diameter is cell size multiplied
by this setting. Cell size is an integer 1-1000 in raw model units. Grid sizes
are 3, 4, 8, 12 and 16. Grid and cell-size controls configure the NEXT drawing;
**New Drawing** explicitly replaces the session and resets its history, with a
discard prompt when needed. They never resample the current mask silently.

Output is centered in XY with Z=0, matching the displayed upward Y direction.
It is planar and grid-aligned: no contour fitting, pressure, height painting,
noise generation, five-point layout or freehand spline tracing is implemented.
The current Script Builder imports peaked splines; this canvas does not silently
change its shaping policy. Native smooth-mode validation remains future work.

A completed stroke is one undo step. **Undo/Redo** buttons always work outside
a stroke; **Ctrl+Z/Ctrl+Y** also work while the canvas has keyboard focus. Clear
is undoable. At most 128 committed changes are retained; dropped older history
is disclosed in the status line. A no-op stroke does not consume history.

**Escape during a stroke cancels only that stroke.** Mouse capture loss,
activation loss, resize, cancel mode, or detected missing button-up also discard
the provisional stroke. Normal button-up, including outside the canvas,
commits before releasing capture. A repeated capture-loss event cannot undo a
completed stroke. Export and document controls are disabled during painting.

Close prompts about unexported coverage; exported plans remain on disk. The
canvas session itself is not saved. Exported model JSON is NOT a reloadable
painting recipe. Save/Load Drawing and the separate `.patchdraw.json` schema
remain in Gate C; this version deliberately has no arbitrary JSON import UI.

## Topology contract

Each drawing cell expands uniformly into a 2x2 block of intended quads. Shared
edges reuse topological vertices. Incident faces that touch only at a corner
receive separate local fan identities, even when connected elsewhere by a path.
Maximal horizontal and vertical edge runs become open splines, with exactly two
spline CP occurrences for every logical vertex. No proximity-based welding.

The compiler keeps an internal intended-face table with stable fine-cell IDs,
components and a planar Euler hole count. Preview uses this compiled topology.
These are graph checks, not claims of native patch recognition. The exported
`am_plan: 1` contract remains exactly **am_plan, name, points, splines**: no
undocumented fields are added to Script Builder.

The canvas accepts up to 16x16 drawing cells. Export separately enforces the
existing v1 limits: **1024 logical points, 128 splines, 2048 CP occurrences,
256 indices per spline and 256 KiB**. A fully occupied 16x16 drawing needs 1089
points and 2178 CP records, so it is previewable but not exportable to v1.
Fragmented masks can exceed the spline limit earlier. The summary explains the
limit and disables export. Nothing is truncated and no existing validator is
weakened. Use a smaller drawing/fewer separated islands for this stage.

## Export behavior

Export validates the entire generated plan before file creation. The Windows
writer requires a `.json` extension and uses CREATE_NEW with exclusive sharing.
It cannot replace an existing plan/model or follow an existing output alias.
Write/flush failures attempt deletion of only the just-created file by handle.
Power loss or process termination can still leave an incomplete new file; no
atomic-replacement guarantee is claimed. There is no automatic install or save
into the user's A:M folders. The native model must be saved through A:M later.

## Tests and automation

See `tests/run_tests.py`. The dedicated `Patch Draw Canvas` workflow builds this
actual project in both Release and Debug using the existing SDK/toolchain locks.
It leaves all baseline projects, workflows, SDK files and known-good records
unchanged. The added workflow watches its own files and relevant shared build
inputs; baseline workflows may also run under their existing path filters.

Core tests independently compare face-edge/spline-graph sets on all 512 3x3
masks plus 512 seeded 4x4 masks, check diagonal/pinched topology, Euler counts,
maximal dimensions and fragmentation, brush borders/sweeps/tangency, stroke
history/cancellation and export limits. Local GCC AddressSanitizer and Undefined
BehaviorSanitizer tests are separate from Windows results.

Windows tests generate 511 nonempty mask exports and pass ALL of them through
both unchanged Script Builder validators. A standalone MFC harness uses the
actual dialog/canvas/resources to exercise synthetic mouse capture, outside
release, Escape, stolen capture, resize, missing button-up, undo/redo and ring
preview; it checks GDI object counts after warmup/repeated painting. It is NOT
A:M and not a physical stylus, multi-monitor or accessibility test.

The final distribution is verified intact, then modified HXT and README copies
are rejected. Build receipts stay `runtime_tested: false`. Manual host results
belong in the PR and `HOST-TEST.md`, not in edited package receipts.

## Provenance and follow-up

This is a new bounded canvas implementation informed by Terrain Wizard's modal
painting interaction, not a copy of its legacy raster/noise/height routines.
Reviewed reference: `Plugin/HXT/Terrain/{Entry.cpp,Terrain.cpp,WizardDialog.cpp,
WizardDialog.h,Evaluate.cpp}` at commit
`2aef54165a47a05f25f83e4a9e4a10a1e1716878`. Existing notices/SDK rights are unchanged.
The local-fan/refinement design is recorded in `docs/patch-draw-design.md`.

Next gate: a small native adapter that consumes the accepted face-aware plan
and verifies actual face identities, adjacency, normals and persistence. Canvas
success does not itself prove those operations. Continue to use disposable
projects when testing exported plans; Script Builder's partial-model and
whole-build Undo limitations still apply.

Developed with AI assistance from ChatGPT. No merge, installation, release,
API connection, paid resource or automatic known-good promotion is performed.
