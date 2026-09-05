# Patch Draw stage-B host test

Use Release `AMPatchDraw_64.hxt` in ordinary A:M. Close A:M before installing or
removing it. It coexists with the corrected AMScriptBuilder and does not replace
Terrain Wizard, smoke or report plugins. Keep the PDB and package receipt.

The new HXT is a canvas/export candidate, not a native-model builder. Python is
not required. No code in this stage edits the selected model or creates a model.
Keep this PR draft until actual canvas behavior is checked in A:M.

1. Open via a Project Workspace model or Objects entry > Plugins > Wizards >
   **A:M Patch Draw v0.1 - Canvas**. Group context is also registered. Confirm
   the top/session labels identify this plugin and the actual host version.
2. Set 3 cells per side and Cell size 10, click New Drawing. Click eight cells
   around the center with the 0.5-cell brush. Expect 8 cells / 32 quads / 48
   logical points / 16 splines / 96 CP records / 1 component / 1 hole.
3. Draw quickly across several cells: no isolated event-stamp gaps. Release
   outside the canvas: stroke ends. Undo once removes the whole last stroke;
   Redo restores it. Repeated painting must not stack duplicate faces.
4. During a stroke press Escape, switch applications, resize, or otherwise
   lose capture. Only the unfinished stroke should disappear; no stuck drawing.
   Normal release must not cancel the committed stroke. Test all four borders.
5. Test Erase, Clear and Undo/Redo, plus Ctrl+Z/Ctrl+Y with canvas focus. Edit a
   value in its field: shortcuts must not silently change the drawing instead.
   A new stroke after Undo drops Redo; no-op strokes add no history item.
6. Export into a NEW .json path with spaces/Unicode. Retrying an existing name
   must fail without changing its bytes. Canceling the chooser writes nothing.
   Close/reopen: the old canvas session is gone (recipe loading is not present).
7. In a disposable project import the export using corrected Script Builder.
   That is the separate step which creates a new model. Inspect the open center,
   shared-edge movement, diagonal separation, and save/reopen. Do not infer
   these results from counts or from the reported earlier ring success.
8. Paint two diagonally touching cells: preview two components and 8 quads.
   Adjacent cells: one component and 8 quads. Compare to the imported model.
9. Try a full 16x16 drawing and a fragmented mask. Over-v1 exports must be
   disabled with an explanation, never silently truncated. Smaller exports
   remain available. New Drawing resets the session, not an existing A:M model.
10. Test resize, display scaling and moving between monitors in the real host.
    The plugin inherits host DPI policy and never changes global DPI awareness.
    Physical stylus mouse input, UI scaling, and A:M integration are manual gates;
    the CI MFC harness is not a substitute for these tests.

Record: package/run/attempt, HXT SHA-256, A:M/Windows version, context, performed
cases, counts, exported JSON, scaling/monitor setup, native import result,
save/reopen and any failures. Report only exercised cases. No native face-set,
normal, whole-build Undo, automatic rollback or maximum-size host guarantee is
established by a working preview. Exported files are not erased by canvas Cancel.

Rollback: close A:M and remove only AMPatchDraw_64.hxt. Other plugins and model
files are unaffected. Reopen A:M and verify normal operation.
