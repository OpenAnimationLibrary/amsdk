# A:M virtual Windows build system

Build Animation:Master 19.5 x64 plugins without installing a compiler on the
computer running A:M. The first target, **AMBuildSmoke**, only displays a message:
it does not change a model or write files.

## Architecture

Source code lives in GitHub. The `Animation Master Windows Build` workflow
creates a clean `windows-2022` VM for each job, discovers Visual Studio 2022 with
MSVC v143 and MFC, downloads and verifies SDK 19.5, compiles, and publishes a
short-lived build artifact. The VM is discarded after the job. It is **not** a
persistent Windows desktop, RDP session, or installation of A:M.

The existing repository `Include/`, `Lib/`, and `Plugin/` remain unchanged. They
are not the dependency used by this build. The SDK archive's checksum is locked
to the separately supplied `sdk195.zip`; the vendor download must match it.
Neither the SDK archive nor A:M license files are committed by this setup.

## First build and runtime check

1. Open the setup pull request and its **Checks** tab. The pull-request workflow
   starts a Release x64 build. An approval may be needed if repository policy
   requires it. After merging, the workflow also appears under **Actions** with
   a **Run workflow** button, configuration choice and project-path input.
2. Open the successful run and download `AMBuild-Release-x64-<run number>` from
   **Artifacts**. Extract it and inspect `build-receipt.json`. A successful build
   includes `AMBuildSmoke_64.hxt`, a PDB, a checksum, and build/inspection logs.
   Failed runs publish available diagnostics, not a valid plugin.
3. Close A:M. Copy **only the release .hxt** into the HXT plugin directory of
   the A:M 19.5 64-bit installation being tested. Do not replace another plugin,
   copy SDK import libraries into A:M, or place debug output in a release host.
4. Start A:M and open a disposable test model. Select a control point, open its
   context menu and look under **Wizards** for **A:M Cloud Build Test**. Run it.
   Seeing its message confirms menu/resource loading, an SDK call and MFC UI in
   the actual host. A successful compiler run alone does not establish this.
5. Close A:M before replacing/removing the plugin. Record the exact A:M version
   and runtime result in the PR. A later SDK/host/toolchain change needs retesting.

## Development loop

Edit plugin sources in a branch and open a PR. Changes under `tools/am-cloud/`
run the Release smoke build. For another plugin, add its sources/project under
`tools/am-cloud/plugins/`, retaining the matching SDK include/library settings.
After merging this workflow, choose its `.vcxproj` path with **Run workflow**.
The builder accepts one plugin project and expects one HXT output with the three
command-plugin exports. Texture, image-format and other plugin types need a
separate audit contract; this initial setup intentionally targets HXT commands.

A manual dispatch project path must refer to a project in the selected branch.
The workflow is a build system and executes project build steps: only run code
you trust. It has read-only repository permissions, does not persist Git checkout
credentials, and does not use secrets or install an A:M license.

## Build contract and diagnostics

- Windows x64, Visual Studio **2022** (`vswhere` range `[17.0,18.0)`), MSVC v143,
  C++20, dynamic MFC, MultiByte character set, `DEFAULT_INITIALIZED`.
- Release: `/MD`, release `_64` SDK libraries, `_64.hxt`.
- Debug: `/MDd`, debug `_64d` SDK libraries, `_64d.hxtd`; requires a matching
  debug A:M environment and is not a substitute for Release runtime testing.
- The binary audit checks PE32+/AMD64/DLL, all three HXT command exports, and
  rejects common debug-runtime dependencies in Release. It never loads the DLL.
- Receipt records source commit (on Actions), SDK SHA-256, exact selected VC/SDK
  versions and runner image version. `windows-2022` is a maintained image label,
  not an immutable disk snapshot; tool updates can require revalidation.
- Only generated output/diagnostics are uploaded, retained for seven days. The
  SDK and complete process environment are not uploaded.

There are 11 platform-independent helper tests covering digest validation,
unsafe archive paths/symlinks/layout, and basic binary architecture checking.
They are **not** an MSVC build or A:M compatibility certification.

## Reuse on a persistent Windows VM

The same code works on a separately provisioned Windows x64 VM with VS 2022,
Python 3.10+, and Git. `windows.vsconfig` lists compiler/MFC/Windows SDK components
for import through Visual Studio Installer. Provisioning/operating-system and
Visual Studio licensing, VM billing and any A:M activation must be handled
separately. This change does not purchase or provision such a VM, change local
Visual Studio, or connect a self-hosted runner.

Run from the repository root:

```powershell
python -m unittest discover -s tools/am-cloud/tests -v
python tools/am-cloud/build.py --sdk-zip C:\AMDev\sdk195.zip --output C:\AMDev\build-001
```

The output directory must be empty; choose a new directory for each build.
Omit `--sdk-zip` to download the vendor archive with the same checksum check.
To build a different command plugin:

```powershell
python tools/am-cloud/build.py --project tools/am-cloud/plugins/MyPlugin/MyPlugin.vcxproj --sdk-zip C:\AMDev\sdk195.zip --output C:\AMDev\build-002
```

## Failure boundaries

**SDK download blocked or checksum mismatch:** preserve the error. The original
archive can be supplied with `--sdk-zip` on a Windows machine/VM. Do not weaken the
checksum, silently switch to this repository's older SDK, or publish proprietary
SDK/application files as a workaround. Review any vendor archive change before
updating the lock. An HTTP error is a dependency-delivery failure, not an MSVC
failure.

**Missing MFC, crtdbg.h, rc.exe or mt.exe:** the preflight reports the missing
component before compilation. On a persistent VM import `windows.vsconfig` into
VS 2022; the script does not modify the installation itself.

**Link failure:** examine `msbuild.log` for mismatched architecture, missing SDK
symbols or CRT/MFC incompatibility. Do not hide failures with `/FORCE`, disable
architecture checks or relabel a 32-bit DLL as a 64-bit plugin.

**Plugin does not appear or crashes:** check the exact A:M version/architecture,
release-vs-debug pairing, HXT directory and `dependencies.log`. Remove this test
plugin with A:M closed. A clean build is necessary but not sufficient for host
compatibility. Test model-changing plugins on copies in a separate step.

## Source references

- Hash v19.5E release / official SDK link:
  https://forums.animationmaster.com/topic/53766-v195e/
- GitHub Windows 2022 image (VS 2022 and MFC inventory):
  https://github.com/actions/runner-images/blob/main/images/windows/Windows2022-Readme.md
- GitHub hosted runner model:
  https://docs.github.com/en/actions/reference/runners/github-hosted-runners
- Codespaces are Linux development environments, not Windows MSVC hosts:
  https://docs.github.com/en/codespaces/overview

Build infrastructure and the new smoke test were developed with AI assistance.
Hash SDK/application rights are unchanged. SDK headers, libraries and license
files are not included in this new directory.
