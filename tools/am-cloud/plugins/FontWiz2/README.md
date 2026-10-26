# FontWiz2 and Pass text to FontWiz2

Independent Windows x64 command plugins for Animation:Master 19.5. FontWiz2 has
its own HXT filename, command label, dialog resources (31001-31034), API and
session settings. The launcher uses resource IDs 32001-32004. Neither loads the
original Font HXT or reads/writes its settings. Standard Windows OK/Cancel IDs
and the three required A:M callback names keep their standard meanings.

## Install and use

For standalone use, close A:M and copy `FontWiz2_64.hxt` from its verified Release
package into the active HXT folder. Keep the original Font plugin installed.
Restart A:M and open a disposable model. The text launcher remains optional;
peer-to-peer host testing is deferred while the standalone wizard is developed.

Under **Plugins > Wizards**, the Model node/Model selection contexts offer:

- **FontWiz2...**: open the new wizard directly.
- **Pass text to FontWiz2...**: enter text and click **Open FontWiz2...**. The
  text appears in the new wizard. Finish or cancel; the launcher resumes and
  displays the result. Completed calls return the actual processed text too.

FontWiz2 provides multiline text, native font/style selection, a font preview,
em height and extrusion in cm, front/back caps and sides, bevel controls and edge
subdivision. **Create a new model** is off initially, so text appends to the original
Model context. **Keep window open** is on initially. Check Create a new model
when each stamp should become a separate model; without a target model the
wizard forces that option on. The launcher keeps that original target until closed.
Font/geometry settings are remembered for the A:M session. The original wizard's
preferences remain independent. Files are written only when Save Settings is used.

The standalone command opens a modeless wizard and returns immediately to A:M.
You can select, move, rotate and scale the generated text in the modeling window
while FontWiz2 stays open. A thread-local input hook delivers mouse/keyboard messages to the wizard
controls before host pretranslation, including its subdivision drop-down.
Dialog navigation still uses IsDialogMessage. Each input is dispatched once;
model-window input and other messages remain with A:M's normal message loop.

## Save Settings and Load Settings

**Save Settings...** writes the current dialog values to a human-readable UTF-8
`.json` text file. It includes text, full font/style properties, em height and
extrusion (cm), caps/sides, bevel controls and amount (mm), subdivision, Create a
new model, Keep window open and the optional surface color. It captures the current controls, including edits
made since the last stamp. Blank text and unfinished checkbox combinations can
be saved as drafts; creating geometry still performs its normal validation.

**Load Settings...** reads and validates the complete versioned file before
populating the controls and font preview. Cancelling the file picker or loading
an invalid/incompatible file leaves the current controls unchanged. Loading does
not create geometry. Numeric ranges match the UI; files are limited to 64 KiB.
An imported append preference is overridden when no target model is available.

New files identify themselves with `"format": "FontWiz2.Settings"` and `"version": 2`.
Version 1 files still load, with surface color disabled.
Text is a JSON string; font, geometry and bevel are named objects. Units appear
in the numeric field names. The JSON contains no model pointers or host handles.
Saving writes a complete temporary file in the selected folder before replacing
the destination, preserving the old file if validation/writing/replacement fails.

## Keep window open

With **Keep window open** checked, each **Create Text** action generates a stamp
and leaves the wizard open with the text selected for quick replacement. Change
the text, font or geometry settings and stamp again. Click into A:M to reposition
the selected text between stamps. New text starts at the model origin; it does
not use a mouse click as a placement cursor. Leave **Create a new model**
checked to make a separate model for every stamp, or uncheck it to append to the
original Model context. Clear Keep window open to close after the next stamp.

Before any successful stamp, Cancel discards the operation. After one or more
stamps the button reads Close; closing preserves those models and reports a
completed operation. Errors leave the dialog open for correction. Both Save and
Load remain available between stamps. Saving/loading settings never stamps text. Appending preserves the current view
zoom; only newly created models are zoomed to fit. Before every stamp, the target
is resolved from the current project rather than dereferencing a cached model.
If the project changes or an append target disappears, reopen the wizard from
the intended Model context. Changing the active view does not retarget append.

## Text groups and surface color

Every stamp creates a persistent named group containing its generated control
points, as well as selecting those points for positioning. Names use up to the
first twenty text characters, with line breaks/tabs replaced by spaces and leading
whitespace removed. Repeated names receive a numeric suffix, shortening the text
prefix to keep the complete name within twenty characters. A:M's group-name API
uses the Windows ANSI code page, so group names can substitute characters that
that code page cannot represent; this does not change the Unicode model text.

**Apply surface color** is off initially. When enabled, **Choose Color...**
sets the new named text group's diffuse surface property. Each stamp can have
its own color; the Model surface and earlier groups keep their existing values.
With the option off, the new group receives no surface override.

After geometry is finalized, the group's diffuse property is enabled and receives
normalized (0–1) RGB components using
`HColorProperty::StoreValue(Time(), color, TRUE)`. This preserves the write path
confirmed in the temporary Model-color test and matches the SDK
`Plugin/HXT/RenderPasses/worker.cpp` group edit example. Existing animation keys
are not deleted. The group/model are marked modified and visible instances are
refreshed. JSON checkbox/RGB fields now apply to the new group; Load Settings
alone never recolors geometry.

Text is limited to 512 UTF-16 code units. BMP glyphs and accented text are
supported; supplementary characters/emoji are rejected. Complex script shaping,
bidirectional layout and kerning are not implemented. Missing glyphs produce a
clear error instead of silent substitution. Invalid text, cancelled dialogs and
rejected outline geometry do not add model data. Geometry is staged before host
mutation; a failure during host insertion is not claimed to be transactional.

## Interim save workaround

Enable **Save model copy after creation** to show a `.mdl` Save dialog after
each successful stamp. The option starts off and is included in JSON settings;
older v1/v2 settings default it off. **Save Model Copy...** also saves on demand,
including retrying a cancelled or failed save without stamping again. Saving
uses the last stamped model, or the original Model context before any stamp.
The Save dialog asks for a filename each time and confirms overwriting.

The SDK serializes the complete current model to memory with the destination
filename as its context. Its original bytes are written to an adjacent temporary
file, flushed, then atomically moved over the chosen destination. Incomplete
model-file wrappers or failed writes leave an existing destination untouched.
No extra property inspection is performed. The SDK's ANSI filename limitation
applies when the system code page cannot represent a chosen path.

This is a model-copy export, not the native A:M Save command. It does not change
the open model's filename, embedded/modified status, identity or wizard target.
Cancelling or failing to save preserves the completed stamp and keeps the wizard
open even if Keep window open was cleared. The standalone and receiving paths
use the same behavior; the V1 ABI is unchanged. Model copies have a 256 MiB limit.

The SDK exposes serialization but no direct reload-in-place operation. If the
copy save does not refresh the visible color, use A:M's normal Save, close that
model, reopen its `.mdl`, then reopen FontWiz2 from it. This workaround does not
automatically replace models, retarget choreography instances, or clear Undo.
Native Save was reported to repair appearance; whether this SDK export has the
same effect and whether its output reopens correctly require an A:M test.

## Inspect the current model

**Inspect Model...** captures the last model stamped by this wizard, or the
original Model context before any stamp. The left pane initially shows live
Model/group stored diffuse values and null flags, group CP IDs, and patch corner
CP IDs. Patch surface handles are not read; driver/key/default and normalized
color queries are also omitted following a colored-model inspection crash. This getter-only report runs before serialization;
it does not call Save, FindPatches, Update, interpolation or refresh operations.
SDK getters may still evaluate internal data lazily; this is not a raw memory dump.

**Capture model code** appends ASCII model text produced by
`HModelCache::ExportModel` into a `MemoryStream`. No model file is written and
no model is reloaded. The SDK serializer may normalize data; the original live
report remains above it. This output need not be byte-identical to an ordinary
A:M Save, and cannot expose every internal cache.

**Save snapshot...** writes only the captured text to a separate UTF-8 `.txt`
file. **Open saved model...** reads a `.mdl` or text file into the right pane;
it never imports it into A:M. Both panes support selection and Ctrl+C.
The viewer and file reader have a 16 MiB limit and reject binary/compressed data.
Only explicit Save snapshot writes a file; no diagnostic data is uploaded.
The inspector is modal while open; close it to interact with A:M.

To compare: stamp colored text, open Inspect Model before saving, and save the
live report. Optionally capture model code and save a second snapshot, noting
whether that action changes visible color. Close the inspector, save the model
normally, reopen Inspect Model and save an after report. Repeat after reload if
needed (reopen FontWiz2 from that model). Load the saved `.mdl` in the right pane
or compare the before/after snapshots externally. Project/target changes are
checked again before each capture; deleted targets produce an error.

## Public interface

`FontWiz2Api.h` defines the independently versioned `FontWiz2RunV1` export. The
caller supplies fixed-size, caller-owned request/reply structures, initial text,
a borrowed `HModelCache*` (optional for new models), and its dialog HWND. The call
must run synchronously on A:M's UI thread. The V1 ABI is unchanged. With Keep window
open, the call returns only after the wizard finally closes. Completed means at
least one stamp finished; the reply contains the total spline count and the last
successful model/text. Cancelled means the dialog closed before any stamp. No C++
objects, allocations or exceptions cross the ABI.
The synchronous V1 adapter pumps messages until the same modeless wizard closes;
it temporarily enables a caller-disabled A:M frame and restores its prior state.
The standalone command needs no nested loop. Caller structures must stay alive
through the V1 call. If the last generated model has since been deleted, the
completed reply has a null model pointer. The result model remains owned by A:M.
Do not retain borrowed pointers across project/model changes. The launcher resolves only this new V1 export in FontWiz2.

## Validation and host test

CI builds each plugin in Release and Debug with the locked SDK/toolchain, audits
PE/dependencies/exports and warnings, and verifies packages and modified-package
rejection. Native tests exercise request validation and **real Windows GDI**
outline extraction, holes, curves, multiple lines and accented text without A:M.
Settings tests cover Unicode/escaped text, every stored option, actual JSON file
round trips, invalid files, replacement and preservation on failed save/load.
Native modeless-dialog tests use the real wizard resource and a mock generation
callback to exercise cancel, single creation, two successive stamps with changed
text/size/color, an enabled owner receiving input between stamps, immediate
return from the standalone window opener, cleanup and WM_QUIT preservation.
Naming tests cover twenty-character truncation, whitespace and repeat suffixes.
Defaults are checked in the real dialog and JSON round trips; byte-to-normalized
RGB conversion is tested for black, white, red and a mixed color. Actual group
color composition/rendering requires an A:M host test. A filtered-host
regression test queues actual control mouse/key messages (not direct command
notifications): typing, checkbox/button clicks, subdivision selection, two
stamps, host edit input, Tab and Escape. Its simulated host discards unhandled
wizard input to expose the Esc-only interaction failure reported in run 7.
This models a possible host pretranslation conflict; an A:M retest is required
to establish the actual host result. They do not run actual A:M insertion, cap quality or Undo.

Before promotion, test the exact Release binaries in A:M and record their hashes:

1. Both new commands appear; the original Font command remains usable.
2. Enter `FontWiz2` in the launcher; confirm exact text reaches the wizard.
3. Create text in a new model, then confirm the launcher resumes and remains usable.
4. Cancel at the wizard; confirm no model/geometry was added and control returns.
5. Try `AB8`, accented text and two lines with caps, sides and small bevels.
6. On a disposable model, uncheck New model: test append, Undo/Redo, selection,
   saved/reloaded geometry and repeated calls. A snapshot is requested before
   append; one-step Undo and selection restoration require host validation.
7. Try empty text, a missing glyph, an excessive bevel, absent FontWiz2 HXT and
   repeated opens/closes. Confirm explicit errors and no unwanted model edits.
8. Change every option, Save Settings, change them again and Load Settings. Confirm
   all controls/preview restore, including Keep window open. Saved checkbox values
   override the new-session defaults. Try cancelling both
   file dialogs and loading invalid JSON; current data must stay unchanged.
9. Keep window open: stamp two different words into new models, change settings
   between stamps, and Close. Confirm both models persist and the wizard did not
   close between stamps. Click into the modeling window and move/rotate/scale the
   selected text, use host shortcuts, then stamp again. Confirm append does not
   reset the zoom. Repeat with append/Undo on disposable data.
10. Confirm each stamp has its own persistent group, correct membership and a
    distinct name of at most twenty characters. Save/reload and Undo/Redo the groups.
11. In a fresh/disposable model, note its Model surface color. Enable Apply
    surface color and append red text; move it aside, then append green and a
    mixed RGB color. Verify each group's diffuse value and immediate shaded
    appearance, including after deselection, without saving first. Confirm the
    Model surface and earlier text/geometry retain their colors. Disable color
    and stamp again: its new group must have no diffuse override. Save/reload
    and Undo/Redo; check membership, group colors and the Model surface again.
    Save/Load both the enabled and disabled color setting. A Model color assigned
    by an earlier diagnostic build remains in that model; test on fresh data or
    restore that property manually when comparing inheritance.
12. Close/delete the original model, switch projects and close the application
    while the wizard is open. Confirm stale targets are rejected and dialog/hook
    cleanup leaves A:M usable. Test the synchronous caller separately when peer
    testing resumes.

Keep generated receipts at `runtime_tested: false` until independent host evidence
is recorded. Debug `.hxtd` packages require the matching debug A:M host. Removing
only these two new HXT files with A:M closed rolls back this experiment.

## Attribution and source scope

New wizard, launcher, Unicode GDI parsing and API code: Open Animation Library,
with AI assistance. Spline conversion and geometry/extrusion/triangulation kernels
are adapted from Hash's Font wizard in this repository (including Noel's 2002
conversion code). Original notices/comments are retained. The independent kernel
copy fixes mismatched array deletion and double deletion of owned polygon areas;
debug tracing uses the debugger instead of a hard-coded file path. Original Font
sources and binaries are unchanged.

The complete locked SDK is used unchanged. Six exact C4244 locations in its
RGBByte.h compound float-to-byte operators are explicitly reviewed alongside the
existing four FileCons.h warnings. Other locations/codes still fail the build.

JSON parsing/serialization uses picojson v1.3.0. Its license and source identity
are retained in `THIRD-PARTY-NOTICES.txt`, included in the generated package.

The owner reported that the supplied run 13 Release candidate displayed its
chosen color immediately after changing the write from SetValue to StoreValue.
That candidate temporarily targeted the Model surface. Its HXT SHA-256 was
`be96ecd361b7b917857ac1995aec23ff868570ee34ae39388ef66c2ef4461d58`;
PR head `ee21238d64fe29decfca1320058a1225f11cd11a`, checkout
`0af23e9cb0b82c96693857f6d12f04e3469ab051`, run `40292468212`, attempt 1.
This is limited owner-reported color evidence, not complete host validation;
the host version and remaining checklist were not reconfirmed. This revision
restores the new named group as the color target and needs its own host test.
Build receipts remain unmodified at `runtime_tested: false`.

The owner reports that run 14's group diffuse property is set but color still
fails to display immediately. That candidate's Release HXT SHA-256 was
`d32f0ea1ec2cbf030de2b450794b70385e379dbacc10bb8d8f2a1c8e712cbb9f`
(run `40305369804`, attempt 1). This revision adds inspection without changing
the group color write path. Inspector UI/file handling has native mock tests;
actual live capture, SDK serialization and visible color require A:M testing.

The owner reports run 15 crashes when inspecting a model created with color
enabled, while uncolored inspection works. The supplied A:M 19.5g uncolored
snapshot contains 620 CPs in the named group and 189 patches whose own/composited
attributes are absent; it never exercises a populated patch surface handle.
This does not identify the faulting SDK call. Snapshot v2 removes patch attribute
access altogether, plus driver/key/default/normalized-color queries. Group/model
reads are limited to null flags and the stored RGB vector. The color assignment
and optional serializer are unchanged; this is a crash-isolation candidate,
not a confirmed runtime repair. Capture the live report before using the separate
Capture model code action, and note which action fails if a problem remains.

Development is paused on the group-color root cause in favor of the optional
save-copy workaround above. Native tests cover byte preservation, replacement,
failed replacement retaining the original file, settings compatibility and a
cancelled post-stamp save followed by a manual retry without duplicate geometry
(mock generation/save callbacks). SDK export and host reload remain untested.
