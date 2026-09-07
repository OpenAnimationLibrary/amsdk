# MakeaBone 0.1.0

A simple native command for Animation:Master 19.5 x64 on Windows.

Close A:M and copy `plugin/MakeaBone_64.hxt` from the release kit into your
installation's `HXT` folder. Restart A:M. In a Model Window, right-click and
choose **Plugins > Wizards > MakeaBone...**. Model, group, control-point and
bone selections are registered. The model entry in the Project Workspace also
offers the command. Action and Choreography instances are excluded.

Enter start/origin X, Y, Z and end X, Y, Z, then click **Create**. Coordinates
are absolute model coordinates in **centimeters**, regardless of A:M's display
units. Use a period for decimals. Defaults: `(0, 0, 0)` to `(0, 10, 0)`.
Cancel, Escape and the dialog's close button leave the model unchanged.

Each invocation adds one top-level bone named `MakeaBone`, `MakeaBone 2`, etc.
Existing bone names, including nested bones, are checked to avoid duplicates.
It does not assign control points. The dialog closes after Create. The model
is marked changed and its views refreshed. A whole-model undo snapshot is
taken immediately before creation; Undo/Redo still require host validation.

Coordinates must be finite, within +/-1,000,000 cm, and produce a bone at
least 0.00001 cm long after conversion to the SDK's float representation.

## Visual Studio project and solution

The release kit includes `source/MakeaBone.sln`, `MakeaBone.vcxproj`, all C++
and resource inputs, and the complete locked `sdk195.zip` with its notices.
No Python runtime is required to use the plugin.

For a local build, install Visual Studio 2022's C++ desktop workload, v143 MFC
for x64/x86, and Windows SDK 10.0.26100.0. The cloud build uses MSVC
14.44.35207 (compiler 19.44.35228); `toolchain.lock.json` records these versions.

1. Verify `sdk195.zip` against `sdk.lock.json` (SHA-256
   `0e917a67d9ac386ea3ad512ce97518f764cddc032957682717c862e64c112977`).
2. Extract that ZIP into a `sdk` directory beside `source`. It should create
   `sdk/SDK/V19_5/Include` and `sdk/SDK/V19_5/Lib`.
3. Open `source/MakeaBone.sln`. Select **Release | x64**, then Build Solution.
   Output: `source/bin/x64/Release/MakeaBone_64.hxt`.

For an SDK elsewhere, set the `AMSdkRoot` environment variable to the directory
containing `Include` and `Lib` **before starting Visual Studio**, or pass
`/p:AMSdkRoot=C:\path\SDK\V19_5` to MSBuild. Both Release and Debug projects
are included. Debug produces `MakeaBone_64d.hxtd` and requires a debug A:M host.
Do not copy SDK libraries into the HXT directory.

For the audited virtual build, use the repository's
`.github/workflows/am-makeabone-windows.yml`. Its Release kit preserves the
native package, receipt and matching PDB under `plugin/`; the original verifier
runs from that directory. `KIT-SHA256SUMS.txt` covers the entire release kit.
`CoordinatesTests.cpp` tests the same parser and length guard used by the dialog.

## Host test for this exact binary

The Windows compiler VM has no running A:M application. A successful build
and package audit leave `runtime_tested: false` in the receipt.

- Confirm the menu and six fields in a Model Window (also with group, CP and
  bone selections). Verify there is no command on Action/Chor instances.
- Cancel, Escape and close the dialog: bone count, dirty state and Undo remain
  unchanged. Enter invalid text and coincident endpoints: the dialog stays open.
- Create the default bone, then a negative-coordinate diagonal bone, and bones
  along each positive and negative axis. In Bones mode, check the exact rest
  origin/end, direction and length in A:M's properties.
- Confirm exactly one new top-level bone per Create, unique names on repeats,
  and unchanged existing rig hierarchy, CP assignments and geometry.
- Undo and Redo each creation; save and reload the model and check coordinates.
  Repeat with two different model windows to confirm correct ownership.
- Keep the matching PDB and receipt with the binary. Report the A:M version,
  HXT SHA-256, menu context and the results actually exercised.

Developed for Rodney Baker with OpenAI Codex assistance. SDK entry registration
and bone-property usage follow Hash's Terrain, MirrorBone and E_Rebuild examples.
Existing Hash and third-party SDK rights/notices remain with their owners.
