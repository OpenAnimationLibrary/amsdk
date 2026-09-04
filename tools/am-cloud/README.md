# A:M virtual Windows build system

Develop Animation:Master 19.5 x64 command plugins without a local C++ compiler.
The Windows build runs on GitHub Actions. Testing the resulting plugin in A:M
is a separate step. The initial `AMBuildSmoke` plugin is intended only to display
a message; it does not edit a model or write files.

## Verified status - September 4, 2026

Two actual `windows-2022` jobs discovered VS 2022, MSVC 19.44.35228 and MFC,
and passed all 11 helper tests. **Neither job compiled a plugin.** The current
Hash SDK download is a valid ZIP but lacks `Include/SDK` and
`Include/3rdParty/Imath`. Its four x64 Release library fingerprints match the
supplied complete SDK. Do not substitute the repository's older libraries.

Run 33922068138 received 6,374,782 bytes with SHA-256
`bbab3856d5cdf85e64764f87574f5fe139c6f4034454b1065304a496ffe39dfd`.
The supplied complete SDK is 6,529,791 bytes, with the digest in `sdk.lock.json`.
**Checksum verification stopped both runs; the lock has not been weakened.**
MSBuild compilation, linking, binary auditing and A:M runtime validation are
still pending. The public setup PR remains blocked on complete-SDK delivery.

## Private cloud-build route

The workflow accepts a complete SDK at `tools/am-cloud/vendor/sdk195.zip`, using
the same checksum. That directory is ignored by Git to prevent accidental
publication. The public PR and source-only ZIP do not include SDK files.
The separately supplied private kit includes the owner's original archive.
Keep that kit private; SDK/application rights are unchanged.

Use Python 3.10+, Git and the GitHub CLI (`gh`) on your Windows computer.
No local Visual Studio, MFC, Windows SDK or working C++ compiler is needed.
From the extracted kit's root:

```powershell
gh auth login --hostname github.com --git-protocol https --web --scopes workflow
python tools/am-cloud/start_private_build.py
```

Type `CREATE` when prompted. The launcher creates a new private repository
`<your-login>/am-plugin-build` and a working copy at `~/AMDev/am-plugin-build`.
It verifies the remote is private before pushing build sources and the SDK.
It never reuses an existing repository or overwrites an existing directory.
Failures leave created resources in place; nothing is deleted automatically.

The push triggers a Windows build. Inspect its result under **Actions**; this is
not a promise that the as-yet-untested plugin will compile or load. Private hosted
builds consume the owner's Actions allowance and can incur overage charges.
Review the account's Actions budget first. No paid VM or A:M activation is
provisioned. No A:M license is uploaded. Allow the new private repository in the
GitHub app connection for ChatGPT to participate in development there.

Use `--repository OWNER/NAME` for a different unused name, `--destination PATH`
for a new working directory, or `--sdk-zip C:\path\to\sdk195.zip` with the
source-only kit. Install GitHub CLI separately if `gh` is not recognized.

## Build architecture and development loop

Each job receives a fresh Windows Server 2022 VM with Visual Studio 2022/v143
and MFC. The script checks the required tools and headers, verifies/extracts the
SDK in a temporary directory, builds with MSBuild and audits the resulting DLL.
The VM is discarded after the job. This is not a persistent desktop, RDP session
or installation of A:M. The public repository's existing `Include`, `Lib` and
`Plugin` files are unchanged and are not used as the build dependency.

Edit sources in a branch and open a PR. Changes under `tools/am-cloud/`
run the Release smoke build. A workflow on the default branch also offers **Run workflow**,
with configuration and project-path choices. Add another command plugin under
`tools/am-cloud/plugins/` and select its `.vcxproj` path for a manual build.
The builder currently expects one HXT with three command exports; texture,
image-format and other plugin types require a different audit contract.

Build projects execute code. Run only trusted project sources. The workflow has
read-only repository permissions, does not persist checkout credentials and
uploads only generated diagnostics/output, not the SDK or process environment.
Actions artifacts are retained seven days.

## Build and binary contract

- VS 2022 (`vswhere` range `[17.0,18.0)`), x64, v143, C++20, dynamic MFC,
  MultiByte, `DEFAULT_INITIALIZED`.
- Release: `/MD`, release `_64` SDK libraries, `_64.hxt` output.
- Debug: `/MDd`, debug `_64d` SDK libraries, `_64d.hxtd`; matching debug A:M
  is required. Debug output is not a substitute for Release runtime testing.
- Audit: PE32+/AMD64/DLL, `HxtLoadCommandEntry`, `HxtOnAddCommandMenu`,
  `HxtOnCommand`, and no common debug-runtime dependencies in Release.
  The audit does not load the plugin.
- A build receipt records source commit on Actions, SDK digest, selected
  compiler/Windows SDK versions, runner image, result and plugin checksum.
  The runner label is maintained, not an immutable disk snapshot.

The 11 helper tests check checksum validation, unsafe archive paths/symlinks,
SDK layout and binary architecture. They do not certify MSVC or A:M compatibility.

## First successful build and runtime check

Resolve complete-SDK delivery before expecting a plugin artifact. After a
successful run, download `AMBuild-Release-x64-<run number>` from **Artifacts**.
Inspect `build-receipt.json`; successful outputs include `AMBuildSmoke_64.hxt`,
a PDB, checksum and logs. Failed jobs contain diagnostics, not a valid plugin.

Close A:M and copy only the Release `.hxt` into the HXT plugin directory of the
A:M 19.5 x64 installation being tested. Do not overwrite another plugin or copy
SDK libraries/debug output into a Release installation. Start A:M, open a
disposable model, select a control point and look under the context menu's
**Wizards** for **A:M Cloud Build Test**. Its message tests resource loading,
an SDK call and MFC UI in the actual host. Record the exact A:M version/result.
Close A:M before replacing or removing the plugin. A clean compile alone does
not establish host compatibility; model-changing plugins need separate tests.

## Reuse on a separately provisioned Windows VM

`windows.vsconfig` lists compiler/MFC/Windows SDK components for VS Installer.
VM/OS/Visual Studio licensing and A:M activation remain separate. This setup
does not provision a persistent VM or change your local compiler installation.
On a Windows VM with VS 2022 and Python, run from the repository root:

```powershell
python -m unittest discover -s tools/am-cloud/tests -v
python tools/am-cloud/build.py --sdk-zip C:\AMDev\sdk195.zip --output C:\AMDev\build-001
```

The output directory must be empty. Select a new directory for each build.
Use `--project` to select another command-plugin `.vcxproj`.

## Failure boundaries

An SDK checksum mismatch or missing header folder must not be bypassed. Supply
the complete archive; do not silently replace it with another SDK. Review any
vendor archive change before updating the lock. `diagnose_sdk.py` reports vendor
response metadata/fingerprints after failure, without extracting or trusting it.

Missing MFC, `crtdbg.h`, `rc.exe` or `mt.exe` is a toolchain-preflight failure.
Link errors belong in `msbuild.log`; do not hide them with `/FORCE`. A plugin
that fails to appear/load requires host-version, architecture, Release/Debug,
installation-path and dependency checks. Remove it with A:M closed.

## Primary references

- Hash SDK release: https://forums.animationmaster.com/topic/53766-v195e/
- Windows image: https://github.com/actions/runner-images/blob/main/images/windows/Windows2022-Readme.md
- Hosted VMs: https://docs.github.com/en/actions/reference/runners/github-hosted-runners
- Private repo creation: https://cli.github.com/manual/gh_repo_create
- Billing: https://docs.github.com/en/billing/concepts/product-billing/github-actions

Build infrastructure and the new smoke test were developed with AI assistance.
No SDK headers, libraries or A:M license files are added by the public setup PR.
