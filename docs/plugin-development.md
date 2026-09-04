# Plugin development with the virtual Windows builder

This guide is for **A:M 19.5 x64 command plugins** built from this repository.
It replaces the old compiler-setup recipe for this workflow, not the historical
API reference. The current platform is Windows; no macOS compatibility is claimed.

## The complete loop

```text
Read task and current repository state
    -> edit a feature branch
    -> review source and run helper tests
    -> build the chosen plugin on GitHub's Windows VM
    -> audit binary and verify package
    -> manually test that exact HXT in local A:M
    -> record the result, review and explicitly approve any merge
```

There are three distinct milestones: **compiled/audited**, **package verified**,
and **host tested**. Never use one as proof of the others. The compiler VM is
created for the job and discarded; it is not a persistent desktop or a licensed
A:M instance. The local test computer needs A:M, not a working C++ compiler.

GitHub's browser is sufficient for source edits and artifact download. Git and
GitHub CLI are useful for scripted development; Python can run helper tests.
See the [automation runbook](plugin-automation.md) for commands and permissions.

## Where things belong

| Path | Role |
| --- | --- |
| `tools/am-cloud/plugins/AMBuildSmoke/` | Baseline non-model-editing diagnostic |
| `tools/am-cloud/plugins/<PluginName>/` | A new plugin's source, project and usage notes |
| `tools/am-cloud/vendor/sdk195.zip` | Complete owner-approved SDK archive |
| `tools/am-cloud/sdk.lock.json` | Archive size, SHA-256 and provenance |
| `tools/am-cloud/toolchain.lock.json` | Reviewed MSVC/compiler/Windows SDK selections |
| `tools/am-cloud/build.py` | Native build, audit, receipt and package orchestration |
| `tools/am-cloud/build_support.py` | Validation and packaging helpers |
| `tools/am-cloud/tests/` | Helper, failure-path and project-contract regression tests |
| `.github/workflows/am-plugin-windows.yml` | Windows Release/Debug CI and manual dispatch |
| `tools/am-cloud/HOST-TEST.md` | Installation, reporting and rollback procedure |
| `tools/am-cloud/validation/known-good.json` | Exact earlier human-tested baseline |

The top-level `Include/`, `Lib/`, `Plugin/` and converted API pages are historical
reference material. The cloud builder deliberately extracts the locked archive
rather than mixing those files into the current SDK. Preserve original notices;
public repository access is not a blanket license grant for every included item.

## Starting a new command plugin

Check the current PR/base state first. While the foundation is still in draft,
use an explicitly agreed stacked branch or wait for its review; do not silently
start from a `main` which lacks the builder. After approval/merge, branch from
the current approved base. Keep one plugin/topic per feature PR.

Create a new directory under `tools/am-cloud/plugins/`. Use the reviewed
AMBuildSmoke project as a reference, but copy only the source inputs needed:
`.vcxproj`, `.cpp`, `.rc` and `StdAfx.h`. Do not copy outputs, SDK files, receipts,
`.user` settings or a stale validation claim. There is no automatic plugin
scaffolder in this revision; project creation is an explicit reviewed edit.

Give the project and source/resource filenames a unique name. Update the
project's file references and namespace and assign a new project GUID once.
Do not regenerate that GUID on every build. Keep the three exported HXT command
entry-point names and their SDK-declared signatures unchanged; renaming the
plugin does not mean renaming the host ABI.

Retain x64, dynamic MFC, MultiByte, C++20 and the reviewed SDK definitions.
Release must use `/MD` and the `_64` libraries; Debug must use `/MDd` and `_64d`
libraries. Preserve the property order: `.hxt`/`.hxtd` TargetExt overrides occur
**after Microsoft.Cpp.props**, and the linker writes `$(TargetPath)`. Use the x64
host tools. The exact standalone output names must be:

```text
<ProjectName>_64.hxt       Release
<ProjectName>_64d.hxtd     Debug
```

Keep compiler/toolchain selection in the locks and builder, not hard-coded
paths to an individual developer's computer. Do not weaken the audit for a
project that has different imports or exports; first define and review its
actual plugin-type contract. The initial builder rejects ProjectReference
build graphs sharing its output/intermediate directories.

Rename diagnostic UI/log labels for the new plugin so reports do not falsely
identify it as AMBuildSmoke. Document its purpose, supported host/context,
expected menu route, installation, data changes, failures and a minimal test.
Credit original code and AI assistance when used. Leave the baseline diagnostic
available for separating toolchain/loader faults from new plugin logic.

## Object context is part of the plugin contract

The HXT registration callback selects an **object type**, not simply a window.
The v2 diagnostic registers the following independently:

| SDK context | Diagnostic label |
| --- | --- |
| `HOT_MODEL` | Model |
| `HOT_GROUP` | Group |
| `HOT_CP` | CP |
| `HOT_CPINSTANCE` | CP instance |
| `HOT_ACTION` | Action |
| `HOT_CHOR` | Choreography |

`MC_WIZARD` places the sample command under **Plugins > Wizards** in the tested
installation. Its label is `A:M Cloud Build Test v2 - <context>`. A window's
empty-space menu need not supply the same context as a model or point selection.
The confirmed host test was **Group**, not every registered context.

A read-only diagnostic may tolerate a null object and use a built-in label.
Do not copy that tolerance blindly into an editing command: validate the actual
object, selection and supported operation before accessing model data. Follow
the SDK's ownership/lifetime rules; do not retain borrowed pointers across
scene changes. Keep MFC module-state management in callbacks that use MFC and
avoid heavy work during DLL initialization. Define error/exception boundaries
and undo behavior appropriate to the actual operation before expanding scope.

## Build the intended target, not just the sample

Run the helper tests from the repository root:

```powershell
python -m unittest discover -s tools/am-cloud/tests -v
```

The normal PR workflow builds **AMBuildSmoke**, in both Release and Debug.
Adding another `.vcxproj` does not add it to an automatic discovery matrix.
For a new plugin, after the dispatchable workflow is on the default branch,
select its project path using **Actions > Animation Master Windows Build >
Run workflow**, choose the feature branch, and request Both configurations.
The [automation runbook](plugin-automation.md) gives the CLI equivalent.

Before that workflow exists on the default branch, manual dispatch may not be
available. Use the open PR's existing trigger; for another target explicitly
review a workflow change selecting it or adding it alongside the baseline.
Do not merge unvalidated work merely to unlock the Run workflow button.
Never claim a new plugin was compiled based on the sample's green check.

## What the hardening enforces

The build verifies the committed archive before extraction. Unsafe/aliased
paths, collisions, special files, excessive expansion, corrupt members or
incomplete headers/libraries fail. There is no website fallback. It explicitly
selects the reviewed compiler and Windows SDK; missing versions require a
reviewed update rather than silent selection of another toolset.

Each native build has fresh intermediates outside Windows TEMP, no incremental
linking, bounded commands, and stage-specific failure diagnostics. Existing
caller output directories are refused, not deleted. Four exact, known C4244
warnings in the locked SDK remain visible; unreviewed numbered warnings fail.

Audits check basic PE/header bounds, AMD64 DLL, relocations, ASLR/NX, actual
command exports, and expected host/MFC imports without mixed Release/Debug
runtimes. They do not execute the plugin or resolve every dependency in A:M.
The package verifier is tested against intact output and a deliberately altered
copy; the altered copy is never published. Failed jobs publish diagnostics, not
an installable candidate. Details live in the [build-system guide][build-guide].

## Artifact handoff and host validation

Select the successful run for the exact source/project/configuration/attempt.
Download the **Package-Release** artifact for ordinary A:M, not Debug or
Diagnostics. The browser download contains the named inner ZIP and its checksum;
extract the inner ZIP for the HXT, matching PDB, receipt, verifier and guides.
CLI download already extracts the outer artifact, as explained in the runbook.

Check the receipt and every payload hash. Save the package with its PDB and
identity before retention expires. With A:M closed, back up the known-good HXT
outside scanned plugin folders, replace only the test HXT and restart. Do not
copy import libraries or debug runtimes into A:M. Follow [HOST-TEST.md][host-test]
for exact steps, context tests and rollback.

Record the new HXT hash, host version, context, menu appearance, command result,
resource status and application behavior. A previous successful source version
or binary does not validate a newly linked one. For editing plugins, additionally
exercise undo/redo, save/reload, invalid selections, object lifetime, cancellation
and relevant model regressions on disposable data.

Only reviewed human evidence promotes a binary to a known-good host record.
Merge and deployment remain explicit owner decisions. The build does not apply
branch protection; required PR/check rules are a separate repository setting.

## Maintenance and references

Update the archive and its lock together only after provenance and compatibility
review. Compiler/SDK upgrades need both native configurations and a new host test.
The hosted image and Python patch can change; receipts record them, and bitwise
reproducible binaries are not claimed. Recover accidental merges through a
reviewed revert/reapply workflow, not a shared-history reset.

See the [dated validation record](plugin-build-validation.md) for the concrete
baseline, hardening failures caught and the successful run. The [legacy API
reference](index.md) is preserved rather than silently relabeled as SDK 19.5.

[build-guide]: https://github.com/OpenAnimationLibrary/amsdk/blob/main/tools/am-cloud/README.md
[host-test]: https://github.com/OpenAnimationLibrary/amsdk/blob/main/tools/am-cloud/HOST-TEST.md

Repository-file links above target the default branch after merge; during PR
review, read the same paths on the PR head. This documentation does not deploy
itself to the public documentation site.
