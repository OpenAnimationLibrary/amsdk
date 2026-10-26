# FontWiz2 and Pass text to FontWiz2

Independent Windows x64 command plugins for Animation:Master 19.5. FontWiz2 has
its own HXT filename, command label, dialog resources (31001-31018), API and
session settings. The launcher uses resource IDs 32001-32004. Neither loads the
original Font HXT or reads/writes its settings. Standard Windows OK/Cancel IDs
and the three required A:M callback names keep their standard meanings.

## Install and use

Close A:M and copy **only** `FontWiz2_64.hxt` and `PassTextToFontWiz_64.hxt` from
their verified Release packages into the same active HXT folder. Keep the original
Font plugin installed. Restart A:M and open a disposable model.

Under **Plugins > Wizards**, the Model node/Model selection contexts offer:

- **FontWiz2...**: open the new wizard directly.
- **Pass text to FontWiz2...**: enter text and click **Open FontWiz2...**. The
  text appears in the new wizard. Finish or cancel; the launcher resumes and
  displays the result. Completed calls return the actual processed text too.

FontWiz2 provides multiline text, native font/style selection, a font preview,
em height and extrusion in cm, front/back caps and sides, bevel controls and edge
subdivision. **Create a new model** is checked initially. Uncheck it to append to
the original Model context. The launcher keeps that original target until closed.
Font/geometry settings are remembered for the A:M session; no registry or settings
files are used. The original wizard's preferences remain independent.

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
must run synchronously on A:M's UI thread. It returns Completed only after text
generation and host insertion finish, or a distinct Cancelled/Invalid/Failed/
Busy/Wrong-thread status. No C++ objects, allocations or exceptions cross the ABI.
The result model remains owned by A:M. Do not retain borrowed pointers across
project/model changes. The launcher resolves only this new V1 export in FontWiz2.

## Validation and host test

CI builds each plugin in Release and Debug with the locked SDK/toolchain, audits
PE/dependencies/exports and warnings, and verifies packages and modified-package
rejection. Native tests exercise request validation and **real Windows GDI**
outline extraction, holes, curves, multiple lines and accented text without A:M.
They do not run model insertion, extrusion/cap quality, the dialogs or Undo in A:M.

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
