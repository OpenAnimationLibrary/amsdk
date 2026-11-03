# Setbiaser 0.1.0-preview

A compact, native, modeless bias editor for Animation:Master 19.5 Windows x64.
Inspired by Emilio Le Roux's Setbias; this is a new implementation, not recovered
original source or a compatibility claim. Developed with AI assistance.

**Host-test candidate, not a validated production release. Use disposable models.**
A successful Windows build does not establish A:M runtime behavior or native undo
grouping. The initial implementation deliberately uses explicit selection binding
and commit-on-release instead of unverified selection notifications/live writes.

## Install and open

With A:M completely closed, back up any previous Setbiaser binary outside all
scanned plugin folders. Copy only Release `Setbiaser_64.hxt` into the intended
A:M installation's `HXT` folder, then restart A:M. Do not install the Debug
`.hxtd`, SDK import libraries or PDB in that folder. Keep the PDB and receipt with
the archived package for diagnostics. Restart A:M before replacing this binary:
the modeless module deliberately remains pinned until process exit.

Open a **Model window**, select CPs, then use the selection context menu:
**Plugins > Wizards > Setbiaser...**. Model/Group/CP menu contexts are registered.
Exact menu visibility must be confirmed in the installed A:M host.

Re-run Setbiaser on a different selection to **rebind the existing palette**.
Selection does not follow viewport changes automatically in this preview.
The title identifies the bound model. A Model-context launch initially has no
bound selection; explicitly choose **Entire model** for a whole-model edit.
Empty selection never silently becomes the whole model.

## Editing

All six fields remain visible: In/Out magnitude, alpha and gamma. Type a value
and press Enter or Tab. Escape cancels; moving focus elsewhere cancels unfinished
text. Drag the adjacent `<>` button horizontally and release to commit. Shift is
fine adjustment; Up/Down steps the focused value; Options offers three sensitivity
levels. Double-click the caption to roll the palette up/down.

- **Set value:** assign the entered display value to the touched component.
  Mixed values remain `Mixed`. For mixed input, type a definite Set value or use
  Add offset; a mixed Set field cannot be scrubbed.
- **Add offset:** add the entered amount to each original value. Magnitudes use
  percentage points, angles degrees. The idle offset resets to zero.
- **Scale magnitude:** multiply each original magnitude by a nonnegative factor;
  the idle factor resets to one. Angular controls are disabled.

Link In/Out starts off and never changes data by itself. Set with linking writes
one common value to the pair; Offset/Scale apply to each side's own baseline and
preserve asymmetry. No preview operation compounds earlier pointer movement.
Only the touched component(s) are written. Full underlying float precision is
retained; display formatting is not silently written back.

**The model changes only on release/Enter/Tab, not during the drag.** Options >
Reset all six biases is explicitly confirmed and uses 100% magnitudes/zero angles.
There are no pretend plugin-local Undo/Redo buttons. The implementation calls
A:M's native `SaveAllToUndo()` once before each meaningful batch commit. Verify
actual Undo/Redo grouping and persistence in the host before trusting it.

Click Refresh after ordinary A:M edits. Topology changes, renamed/deleted models,
project replacement and a changed detectable MDI model window invalidate binding;
re-run the plugin. No SDK pointer from an earlier callback is dereferenced until
it has been reacquired through the live project/model traversal.

## Scope and conservative limitations

Targets are distinct CP occurrences on splines, not only attached-stack heads.
Selecting one positional CP expands to its eligible attached spline occurrences.
The count shows positional CPs and affected occurrences; skipped count is reported.
Whole-model scope includes hidden editable occurrences. Bound-selection scope
excludes hidden points. Locked CPs, constrained hooks/hook bases and open-spline
endpoints are skipped in this first candidate. Smooth/peaked state, positions,
topology, materials and rig data are not intentionally changed.

Only base-model editing is supported. Actions, poses, choreographies and CP
instances are not supported editing contexts. Automatic selection following,
continuous live preview, endpoint/hook edits and palette native Undo/Redo routing
remain follow-up work after host verification. Dense-model performance and Windows
DPI behavior are not measured. Palette dimensions follow native dialog font units.
Numeric entry uses a dot decimal separator. Window placement/sensitivity are saved
under HKCU\Software\OpenAnimationLibrary\Setbiaser; no CP handles are persisted.

## Implementation and numeric conversion

`BiasCore.h` contains SDK-independent Set/Offset/Scale/mixed-value arithmetic.
`Adapter.cpp` obtains display factors and native limits from the actual host's
`HBiasPropertyInfo` / `HFloatPropertyInfo` metadata. Production does not assume
radians or a magnitude scaling constant. The temporary parent property-info object
is released; native sub-property infos are only read. Known-value comparisons in
A:M are still required to confirm presentation and signs.

Every commit rechecks model identity, topology, target eligibility, exact native
biases, base positions and smooth/peaked/flip flags. The entire result batch is
validated before the native undo snapshot and first write. No-op edits create no
snapshot and do not mark the model changed. SDK writes and one final refresh run
synchronously on A:M's UI thread; no host message pumping occurs mid-commit.

`Setbiaser.cpp` owns the Win32 modeless dialog inside the MFC plugin. Its UI-thread
message hook routes only its own controls/dropdowns, following the repository's
FontWiz2 modeless input approach. It is not a system-wide input hook.

## Build and tests

From the SDK repository branch containing the reviewed builder:

```powershell
python -m unittest discover -s tools/am-cloud/tests -v
python tools/am-cloud/build.py --configuration Release --project tools/am-cloud/plugins/Setbiaser/Setbiaser.vcxproj
```

The separate Setbiaser PR workflow builds Release and Debug, compiles/runs the
native core tests, uses the locked SDK/toolchain, audits the HXT, and tests package
verification on intact and deliberately altered output. It does not launch A:M.
Sources and usage notes are included in a separate artifact.

Standalone arithmetic tests, without A:M or its SDK:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror CoreTests.cpp -o core-tests
./core-tests
```

Initial local result: 6,253 checks passed. See CI for the exact Windows commit,
compiler result and package identity. Existing SDK and repository notices remain
unchanged; this source does not relicense the SDK.

## Required host test before production use

Record exact HXT SHA-256, package receipt, A:M About version and Windows scaling.
On a copy of a simple model: open the palette, type/drag every component, compare
native values, test linked mixed values, zero/no-op, invalid text and Escape.
Check one commit/Undo/Redo with ordinary A:M edits interleaved. Save/reopen the
model and project, compare values, patch shape and unrelated model data. Test
empty selection, entire model, hidden/locked points, attached crossings, closed
loops, open endpoints and hooks. Rebind after selection/Undo/topology changes;
close/switch model/project with the palette open and during uncommitted input.
Test caption roll-up, keyboard routing, 100/150/200% scaling and a dense model.
No item on this host test list is claimed as passed by the automated build.
