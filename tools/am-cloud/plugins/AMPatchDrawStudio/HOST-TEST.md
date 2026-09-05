# Studio 0.2 — required A:M host validation

Status: **NOT RUN by the automated build.** Start on a disposable A:M 19.5 x64
project. Record exact A:M version, Windows version, HXT SHA-256, package/run/head
identities from build-receipt.json, and the result of each check below. Never
edit a sealed build receipt to claim a host pass.

## Minimum acceptance sequence

1. Keep old Patch Draw/Script Builder installed; add only the new Release HXT
   with A:M closed. Launch the Python Studio, choose a persistent test folder,
   open/name a model and connect from its context menu. Both A:M and Studio
   must stay interactive. Duplicate Connect must focus the existing receiver.
2. Use a 3-by-3 grid with a one-cell-center ring. Start with paint off. Send:
   expect 32 quads, 48 logical points and an OPEN hole. Group PD_Ring_001 must
   select the entire shape, including attached CP occurrences. Move that group.
3. In the still-open Studio, use a small full sheet and Arch X with nonzero Rise,
   Native Smooth enabled. Send as PD_Arch_001. Inspect actual CP Smooth state and
   surface continuity in A:M, not just the projected preview. Compare Peaked.
   Test Flat, Arch Y, Dome, Saddle and each construction plane with small grids.
4. Paint four distinct corners and a central patch in the atlas. Send with paint
   enabled. Verify all colors, vertical orientation, shared edges and patch
   alignment in A:M shaded/rendered views. Test after normal reversal on XY/XZ/YZ.
   Move the new group: its paint must move with it. The ring hole must remain open.
5. Edit paint/draft, send again with the same name. Expect a new numbered group
   and distinct decal/PNG. The moved/edited earlier group and its texture must
   remain unchanged. Repeat at least ten small sends without closing Studio.
6. Native undo/redo: test geometry, group, decal and clip creation separately and
   together. Document the actual number of steps and any orphan groups/decals/
   clips. Do not call this transactional until all affected objects restore.
   Studio Draw Undo/Paint Undo must never invoke A:M undo or change prior sends.
7. Save A:M, close it, reopen the project and model with the session folder kept.
   Recheck group membership, smooth flags, every hole/patch identity, paint and
   transform state. Save/reopen native validity is essential.

## Lifetime, cancellation and error gates

- Cancel A:M destination confirmation: no geometry/group/decal/clip is added.
  Change focus/current model: the bound target remains explicit, never silently
  switches. Rename/close target, Save As project, load another project and retry:
  require a safe stop/reconnect, with no stale-handle crash.
- Close the receiver while idle; A:M remains usable and Studio goes disconnected.
  Close/reopen Studio; use its NEW connection file. A second A:M process cannot
  connect to an already locked session. Close A:M while Studio remains open.
- Interrupt a pending send deliberately in a disposable project. `processing.json`
  and snapshots stay intact; no automatic duplicate appears. Inspect partial
  group manually before starting a new session. Exercise disk-full/read-only
  workspace and unavailable PNG. Preflight errors must not mutate geometry.
- Draw quickly, release outside canvas, switch focus/capture, press Escape,
  resize and test 100/150/200% DPI. All controls remain reachable using the
  sidebar scrollbar. Paint focus loss finishes one undoable stroke. Test
  smallest supported window on the actual Windows desktop.
- Test per-send name collisions including case-only differences and unnamed/
  duplicate model names. Nothing pre-existing is overwritten or accidentally
  selected into the new group.

## Resolution/performance ramp

After the minimum sequence passes: 8, 16, 32, then 64 cells per side. Test both
full sheet and checkerboard/disconnected islands; retain a ring/hole fixture.
Record send time, native patch count, UI pause, group-select time and memory.
Full 64 grid: 16,384 quads / 16,641 logical CPs / 258 splines / 33,282 CP records.
64 checkerboard: 8,192 quads / 18,432 logical CPs / 12,288 splines / 36,864 CP
records. Do not infer host responsiveness from portable compiler test speed.

At each stage save/reopen and repeat. Test 256/1024/2048 textures, group movement
and repeated sends. Increase limits further only with measured host evidence.

## Rollback

Close A:M before removing/replacing the new HXT. Keep the old working plugin and
native project backups. Receiver DLL is intentionally pinned for the process
lifetime, so a full A:M restart is required for a binary replacement. Never
remove a session folder still referenced by a saved project's paint decals.
