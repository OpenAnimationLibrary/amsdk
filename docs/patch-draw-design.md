# Patch Draw design and stage boundaries

This records the adopted decisions from the `AM_Patch_Draw_Design.md` study,
reviewed against source commit `2aef54165a47a05f25f83e4a9e4a10a1e1716878`.
See [current stage-B implementation](plugin-patch-draw.md). No original Terrain
Wizard or Script Builder behavior is changed by this separate plugin.

## Drawing means coverage, not displacement

Terrain Wizard's dialog paints a 200x200 grayscale image and samples it as a
height field while constructing a complete crossing-spline grid. Patch Draw
instead paints WHERE a surface exists. Erased cells mean absent faces, not
black material, lowered geometry or hidden CPs. Height is a separate future
channel. The first result is planar, stepped and grid-aligned, not fitted to
a smooth organic contour. Three/five-point-rich layouts need another compiler.

Reuse the modal stage separation and brush interaction, not the old unchecked
7x7 raster indexing, fixed pixel offsets, or integer displacement sampler.
The new canvas clips a swept disk/capsule against bounded cells, quantizes
pointer coordinates to 1/1024 cell, commits a stroke on release and discards an
unfinished stroke on Escape/capture loss. Tangency alone is not coverage.
Mouse events cannot reconstruct an unsampled curved trajectory; only a given
polyline's collinear subdivision is expected to have the same result.

## Why every painted cell proposes four patches

For an eight-cell ring, a naive one-quad-per-cell edge graph retains four edges
around the blank center and therefore contains nine four-cycles. Omitting a
face from the mask does not remove that inferred surface boundary.

Uniform 2x2 refinement makes each painted cell four fine quads. An unpainted
cell contributes no internal edges, leaving an eight-segment ring opening.
Graph tests compare intended faces with ALL four-cycles, not only their counts.
The original study checked all 512 3x3 masks: the naive ring was the sole mismatch;
the refined construction had no mismatches. Rodney subsequently reported the
refined ring works in A:M. That is not a claim that every native mask, exact
face identity, normals, smoothing and save/reopen were tested.

At every grid vertex split incident faces into edge-connected local fans.
Diagonal-only contact does not weld, even if the two fans connect elsewhere
through a distant path. Shared edges remain shared. Chain maximal horizontal
and vertical edge runs into open splines; each logical point occurs in both
families. Keep stable intended fine-cell face IDs alongside the spline plan.

| Case | Logical points | Splines | CP records | Intended quads |
| --- | ---: | ---: | ---: | ---: |
| Single painted cell | 9 | 6 | 18 | 4 |
| Two edge-adjacent cells | 15 | 8 | 30 | 8 |
| Two diagonal cells | 18 | 12 | 36 | 8 |
| Eight-cell ring | 48 | 16 | 96 | 32 |
| Full 3x3 mask | 49 | 14 | 98 | 36 |

## Staged implementation

**A — native topology proof.** Ring success allows the isolated canvas work to
start. Keep exact native face identity/adjacency, normals, smooth-vs-peaked and
save/reopen on the checklist. Stop promotion when holes fill or connections fail;
do not hide unwanted faces with transparency.

**B — canvas and bounded export (current).** Separate HXT, ordinary document
mask, component/quad preview, swept brush, capture handling, 128-step undo/redo,
Clear and explicit new drawing. No model editing. Export to existing
`am_plan: 1` JSON for testing through Script Builder. Respect its 1024-point,
128-spline, 2048-CP-record and 256-KiB bounds. Large/fragmented drawings may be
previewable but not exportable; reject visibly without truncation. The canvas
supports at most 16x16 coarse cells. Full occupancy implies 1024 quads, 1089
vertices and 2178 CP records and therefore exceeds v1's export limits.

**C — native adapter and drawing recipes (future).** Add explicit Build New
Model, preserving the intended-face table for SDK readback. Compare face
signatures and orientation, not just totals. Honor AttachCPs' second-CP-deleted
Boolean; never dereference a deleted CP. Invalid input/cancel before build must
not allocate native geometry. Whole-build Undo/atomic rollback are not assumed.
A partial native failure must preserve the drawing and identify the new model.

Use a separately versioned drawing recipe for mask/plane/scale and compiler
version. It is not the generated model, and loading it cannot replace hand edits
in an old native result. No raw host pointers, scripts, machine paths or keys in
recipes. The current stage-B export is model JSON, not this future recipe.

**D — package and host evidence (per milestone).** Locked SDK/MSVC, explicit
Release/Debug target jobs, failure diagnostics, package checks and tamper
rejection. CI does not run the A:M host. Receipts retain runtime_tested=false;
human evidence is recorded separately. No automatic merge/install/promotion.

## Source references

- Terrain: `Plugin/HXT/Terrain/{Entry.cpp,Terrain.cpp,WizardDialog.cpp,WizardDialog.h,Evaluate.cpp}` at the reviewed commit above.
- Existing four-field contract: `tools/am-cloud/plugins/AMScriptBuilder/Plan.h` and `runtime/ambridge.py` at that commit.
- Microsoft capture-loss behavior: https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-capturechanged
- Repository rules: [development](plugin-development.md), [automation](plugin-automation.md), `AGENTS.md`.

Source review and new design/code were developed with AI assistance. Existing
Hash SDK and third-party notices/rights are unchanged. No legacy noise/painting
implementation is redistributed as part of the new canvas core.
