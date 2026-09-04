# A:M virtual Windows build system

Build Animation:Master 19.5 x64 command plugins on GitHub Actions without a
working local C++ compiler. Test the resulting plugin in your local A:M.
This is a fresh Windows build VM per job, not a persistent remote desktop.

## Recovery after the rollback

PR #1 introduced this setup and was merged before validation. PR #2 reverted
that merge. This setup is now reapplied as new work based on the post-rollback
`main`, on branch **build/am-plugins-sdk195**. No history is rewritten, and the
original `build/virtual-windows-am-plugins` branch is not reused.

**Keep the new PR in draft and do not merge it yet.** The next required step
is uploading the complete SDK to this new branch, followed by cloud compilation
and testing the produced plugin in A:M.

## Upload the SDK - no private repository or local compiler required

The repository owner has authorized adding the complete Library SDK to this
public repository. Open the **vendor** directory beside this README on branch
**build/am-plugins-sdk195**, choose **Add file / Upload files**, and upload only
**sdk195.zip**, leaving that archive zipped. Commit to the same new branch.

Required path: `tools/am-cloud/vendor/sdk195.zip`.
Expected size: **6,529,791 bytes**.
Expected SHA-256:

```text
0e917a67d9ac386ea3ad512ce97518f764cddc032957682717c862e64c112977
```

The workflow already detects this path and supplies the archive to `build.py`.
Its checksum must match `sdk.lock.json`; no check is bypassed. The new ignore
rules permit this one approved archive while still ignoring other vendor files.
The `vendor/README.md` placeholder itself does not mean the ZIP is uploaded.
Do not upload A:M application, activation/license files or personal settings.

**The earlier private-build launcher is not needed for this repository.** It is
retained as optional infrastructure, not an instruction to create another repo.

## Validation status

The original two Windows jobs found VS 2022, MSVC 19.44.35228, MFC and the
required tools/headers, and passed all 11 helper tests. They stopped before
MSBuild because the vendor download differed from the complete Library SDK
and lacked the SDK/Imath header subdirectories. No plugin binary or A:M runtime
success was established by those runs.

The restored helper tests pass locally; the project XML and workflow YAML parse.
The complete archive in the handoff package matches the lock and passes ZIP
integrity checking. These checks are not a Windows compile or runtime test.

Until `vendor/sdk195.zip` is committed, the unchanged workflow falls back to
the vendor download and is expected to encounter the same checksum failure.
Uploading the correct ZIP to this draft PR triggers another Windows build;
do not merge merely to start it.

## Build contract

- `windows-2022`, Visual Studio 2022, MSVC v143, C++20, x64, dynamic MFC,
  MultiByte character set and `DEFAULT_INITIALIZED`.
- Release uses `/MD`, the `_64` SDK libraries and a `_64.hxt` output.
- Debug uses `/MDd`, `_64d` libraries and `_64d.hxtd`; it needs a matching debug
  A:M environment and must not be installed into an ordinary Release host.
- Binary auditing checks x64 PE32+/DLL, the three HXT command entry points,
  and common debug-runtime dependency names in Release. It never loads the DLL.

The repository's pre-existing `Include`, `Lib`, `Plugin` and documentation files
remain unchanged; the verified archive supplies this build's SDK dependency.
The workflow uses read-only repository permissions and does not persist checkout
credentials. Only generated output/diagnostics are uploaded, retained seven days.
A receipt records source commit, SDK digest, toolchain/runner details and result.
The maintained runner label is not an immutable disk snapshot.

## First plugin test

After a successful build, retrieve `AMBuild-Release-x64-<run number>` from the
run's Artifacts and inspect `build-receipt.json`. Success should include
`AMBuildSmoke_64.hxt`, a PDB, checksum and logs. Failed artifacts are diagnostics,
not a usable plugin.

Close A:M, copy only the Release `.hxt` into the HXT plugin directory of the
A:M 19.5 x64 installation being tested, and restart. On a disposable model,
select a control point and look under its context menu's **Wizards** for
**A:M Cloud Build Test**. Its message exercises a compiled resource, an SDK
call and MFC UI without changing the model. Record the exact A:M version and
result. Close A:M before replacing/removing the plugin. A successful compile
alone does not prove host compatibility.

## Further development

Edit sources in a branch and open a PR. The initial target is a command HXT;
other plugin types need their own audit contract. After this workflow is merged,
its manual Run workflow option accepts another command-plugin `.vcxproj` path
and Release/Debug selection. Only build trusted projects: project steps execute
code on the runner.

The same builder also works on a separately configured Windows VM with VS 2022
and Python 3.10+. `windows.vsconfig` describes its required components:

```powershell
python tools/am-cloud/build.py --sdk-zip C:\AMDev\sdk195.zip --output C:\AMDev\build-001
```

Use an empty output directory for each build. This setup does not provision a
paid VM, install or activate A:M, or change the local compiler installation.
SDK/application rights and existing notices remain unchanged.

Build infrastructure and the new smoke test were developed with AI assistance.
