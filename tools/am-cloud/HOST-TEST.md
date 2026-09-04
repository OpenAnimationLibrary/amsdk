# Test a cloud-built command plugin in A:M

**A green workflow is a build/binary/package check, not a host test.**
A test of an older binary does not automatically validate a new binary, even
when the plugin source is unchanged. Start with Release x64 for ordinary A:M.
Debug `.hxtd` needs matching debug A:M and debug runtimes: do not install it in
the ordinary application. No debugger or compiler is needed for the Release test.

## Before installation

Download the **Package-Release** artifact from a successful run. GitHub's outer
artifact archive contains the specifically named plugin package ZIP and its
`.zip.sha256`. Extract the outer archive, then the inner package ZIP. Do not
confuse either ZIP with `sdk195.zip`, which is never an installable plugin.

Read `READ-ME-FIRST.txt`. It identifies configuration, exact plugin file and
SHA-256, checked-out commit, PR head, workflow run and attempt. Compare these
with the intended run. `symbols/` contains its matching PDB for later debugging.
The **Diagnostics** artifact is separate and is not for installation.

The inner package includes a read-only `Verify-Package.ps1`. From that extracted
folder, use `powershell -NoProfile -File .\Verify-Package.ps1` to check every
payload hash and receipt/configuration consistency. It does not load a DLL,
install anything, or change system settings. When local script policy blocks
execution, do not weaken policy: compare the HXT with the receipt using
`Get-FileHash .\AMBuildSmoke_64.hxt -Algorithm SHA256` and inspect the manifest.
Checksums detect corruption/mismatches; they are not a signature or proof that
code from an untrusted branch is safe. Trust the source/run separately.

Close A:M completely. Move the previous test HXT to a backup folder **outside all
scanned plugin directories**, noting its run and hash. Copy **only the new HXT**
into the active installation's HXT directory. Do not overwrite another plugin,
copy SDK import libraries into A:M, or scatter duplicate test HXT files into
multiple installations. Restart the intended A:M installation.

## Default smoke-test command

For AMBuildSmoke v2, look under **Plugins > Wizards**. Entries are suffixed with
Model, Group, CP, CP instance, Action or Choreography. These are independently
registered object contexts, not a promise of a command on every empty-space
menu in every window. Right-click a model entry in the Project Workspace for
the Model context, or a model selection for the Group/CP contexts.

Rodney's previously confirmed test was **Group**, on A:M **19.5g**. The dialog
showed an object supplied, resource present, and an SDK call returning. Other
contexts and versions are separate test cases. Open a disposable model for
repeat tests; do not begin with production work.

Run the test, check the reported context/version/resource result, close its
dialog, and confirm A:M remains usable. For the default smoke plugin no model
is edited by its code. Plugins which change models need separate undo,
save/reload, malformed-input and regression tests before use on real work.

## Missing entry or a failure

For v2, inspect the newest `%TEMP%\AMBuildSmoke-v2-<PID>.log`. It is attempted
only after exported callbacks are reached, once per stage/context/process.
Registration proves the host reached this DLL's export; menu-return means the
callback offered an entry. No log is inconclusive: discovery, dependency/loader,
callback or log-write failure is possible. The old CP-only failure has not been
isolated conclusively. Keep the exact About version and installed HXT path.

Logs can contain personal paths. Review them before posting. No log creation
was established by the original successful screenshot. Do not download random
DLL replacements, change the SDK hash or disable system security.

To roll back, close A:M, remove only the new test HXT and restore the saved HXT
to its original location. Restart and verify. This does not require reverting
repository history. Never promote a failing binary to the known-good record.

## Record the result in the PR

Copy this form into a PR comment; test only the rows you actually exercised:

```text
Package/run/attempt:
PR head / checkout commit:
HXT SHA-256:
Configuration / architecture:
A:M About version / Windows version:
Object context / menu route:
Menu appears:
Command executes / reported version:
Object supplied / resource result:
A:M usable after closing dialog:
Log found and inspected (yes/no):
Other tests or failures:
```

A reviewer records a successful result in `validation/known-good.json` together
with the exact HXT hash and scope. CI never marks `runtime_tested` true on its
own. Keep the PR draft until build checks, package checks and the intended host
check are reviewed. Merge through a PR; do not merge simply to trigger a build.
