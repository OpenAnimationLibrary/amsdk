# FontWiz2 and Pass text to FontWiz2

Independent Windows x64 command plugins for Animation:Master 19.5. FontWiz2 has
its own HXT filename, command label, dialog resources (31001-31022), API and
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
subdivision. **Create a new model** is checked initially. Uncheck it to append to
the original Model context. The launcher keeps that original target until closed.
Font/geometry settings are remembered for the A:M session. The original wizard's
preferences remain independent. Files are written only when Save Settings is used.

## Save Settings and Load Settings

**Save Settings...** writes the current dialog values to a human-readable UTF-8
`.json` text file. It includes text, full font/style properties, em height and
extrusion (cm), caps/sides, bevel controls and amount (mm), subdivision, Create a
new model and Keep window open. It captures the current controls, including edits
made since the last stamp. Blank text and unfinished checkbox combinations can
be saved as drafts; creating geometry still performs its normal validation.

**Load Settings...** reads and validates the complete versioned file before
populating the controls and font preview. Cancelling the file picker or loading
an invalid/incompatible file leaves the current controls unchanged. Loading does
not create geometry. Numeric ranges match the UI; files are limited to 64 KiB.
An imported append preference is overridden when no target model is available.

The schema identifies itself with `"format": "FontWiz2.Settings"` and `"version": 1`.
Text is a JSON string; font, geometry and bevel are named objects. Units appear
in the numeric field names. The JSON contains no model pointers or host handles.
Saving writes a complete temporary file in the selected folder before replacing
the destination, preserving the old file if validation/writing/replacement fails.

## Keep window open

With **Keep window open** checked, each **Create Text** action generates a stamp
and leaves the wizard open with the text selected for quick replacement. Change
the text, font or geometry settings and stamp again. Leave **Create a new model**
checked to make a separate model for every stamp, or uncheck it to append to the
original Model context. Clear Keep window open to close after the next stamp.

Before any successful stamp, Cancel discards the operation. After one or more
stamps the button reads Close; closing preserves those models and reports a
completed operation. Errors leave the dialog open for correction. Both Save and
Load remain available between stamps. Saving/loading settings never stamps text.

Text is limited to 512 UTF-16 code units. BMP glyphs and accented text are
supported; supplementary characters/emoji are rejected. Complex script shaping,
bidirectional layout and kerning are not implemented. Missing glyphs produce a
clear error instead of silent substitution. Invalid text, cancelled dialogs and
rejected outline geometry do not add model data. Geometry is staged before host
mutation; a failure during host insertion is not claimed to be transactional.

## Public interface

`FontWiz2Api.h` defines the independently versioned `FontWiz2RunV1` export. The
caller supplies fixed-size, caller-owned request/reply structures, initial text,
a borrowed `HModelCache*` (optional for new models), and its dialog HWND. The call
must run synchronously on A:M's UI thread. The V1 ABI is unchanged. With Keep window
open, the call returns only after the wizard finally closes. Completed means at
least one stamp finished; the reply contains the total spline count and the last
successful model/text. Cancelled means the dialog closed before any stamp. No C++
objects, allocations or exceptions cross the ABI.
The result model remains owned by A:M. Do not retain borrowed pointers across
project/model changes. The launcher resolves only this new V1 export in FontWiz2.

## Validation and host test

CI builds each plugin in Release and Debug with the locked SDK/toolchain, audits
PE/dependencies/exports and warnings, and verifies packages and modified-package
rejection. Native tests exercise request validation and **real Windows GDI**
outline extraction, holes, curves, multiple lines and accented text without A:M.
Settings tests cover Unicode/escaped text, every stored option, actual JSON file
round trips, invalid files, replacement and preservation on failed save/load.
Native modal-dialog tests use the real wizard resource and a mock generation
callback to exercise cancel, single creation and two successive stamps with
changed text/size. They do not run actual A:M insertion, cap quality or Undo.

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
   all controls/preview restore, including Keep window open. Try cancelling both
   file dialogs and loading invalid JSON; current data must stay unchanged.
9. Keep window open: stamp two different words into new models, change settings
   between stamps, and Close. Confirm both models persist and the wizard did not
   close between stamps. Repeat with append/Undo on disposable data.

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
