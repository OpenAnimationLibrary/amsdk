# A:M Windows plugin build system

Develop a command HXT in GitHub, build it on a fresh Windows VM, download a
verified test package, and test it in the local A:M application. The local
computer does not need a C++ compiler. The VM is ephemeral, not a remote desktop
or an activated installation of Animation:Master.

## Proven baseline and current review

The complete owner-approved SDK is **already committed** as
`vendor/sdk195.zip`. Do not upload it again or create a private repository.
Windows run **#7** built diagnostic v2 from PR head `378fb80`. Rodney executed
that binary in **A:M 19.5g, Group context**: object supplied, resource present,
SDK call returned, and MFC message displayed. Exact identity and the limited
scope of that result are recorded in [validation/known-good.json](validation/known-good.json).
The other contexts, Debug host behavior, and model-changing SDK operations
were not established by that test.

The hardening revision changes the build/packaging process, not v2's C++ source.
New binaries still need a new host test. PR #3 on **build/am-plugins-sdk195**
remains the review location after the earlier merge/rollback; leave `main`
untouched until review. The prior diagnostic/private-repository launchers have
been removed because there is now one supported, committed-SDK route.

## Normal development loop

Edit a standalone command plugin below `tools/am-cloud/plugins/` in a branch,
then open/update its PR. Matching pull-request changes automatically run
**Windows Release** and **Windows Debug** independently. Debug compilation is
useful coverage, not authorization to install Debug output in ordinary A:M.
The default project is AMBuildSmoke. After the workflow is on the default
branch, **Run workflow** can choose another standalone `.vcxproj` in that
folder and Release, Debug or Both. Never merge just to start a build.

Each configuration runs helper/failure-path tests, validates the SDK, selects
the locked toolchain, compiles and links in a new directory, audits the binary,
creates a package, and tests the shipped package verifier against both the
intact plugin and a deliberately modified copy. The modified copy is never
published. A verification failure prevents the installable artifact upload.
Diagnostics are still uploaded on ordinary failures.

Only run trusted projects: MSBuild executes project code. A path check is not a
sandbox for a hostile `.vcxproj`. The workflow uses pull_request, not
pull_request_target; repository permissions are read-only, checkout credentials
are not persisted, and actions are pinned to full commit SHAs. No A:M license,
secrets, SDK upload, release publishing or automatic installation is involved.

## Locks and build contract

`sdk.lock.json` fixes the complete archive's SHA-256 and size. The URL is a
provenance reference, **not a download fallback**. Missing/mismatched archives
stop the build before the compiler. Extraction checks paths, Windows aliases,
case collisions, special files, expansion limits, CRCs, header layout and the
four configuration-matched x64 libraries. SDK bytes are not altered.

`toolchain.lock.json` selects VS 2022's **MSVC 14.44.35207**, compiler patch
**19.44.35228**, and **Windows SDK 10.0.26100.0**, based on run #7. Selection is
explicit in both the developer environment and MSBuild. A runner update which
removes or changes that compiler fails visibly instead of silently changing
our toolchain. Review the lock change, both builds and a new Release host test
before adopting an update. `windows-2022` is maintained by GitHub; it is not an
immutable VM image. Python's 3.11 patch is recorded, not frozen. Rebuilds are not
claimed to be byte-for-byte reproducible.

The project uses x64, v143, C++20, dynamic MFC, MultiByte, DEFAULT_INITIALIZED,
and explicit Windows 10 target macros. Release uses `/MD` and `_64` libraries;
Debug uses `/MDd` and `_64d` libraries. Both produce a PDB. Standalone HXT
projects only: no shared-output ProjectReference graphs. Other plugin types
need a separate export/dependency contract rather than weakening this one.

The compiler-version probe compiles a real trivial x64 source; its result must
succeed. Scratch outputs live in a fresh ignored checkout-local `.work/`
directory, not Windows TEMP, with consistent output/target/linker paths and
incremental linking disabled. Every native process has a timeout; failures keep
its partial log and a stage-tagged receipt. Only internally allocated scratch
directories are deleted. The requested output directory must not already exist.

The warning policy retains the four known C4244 conversions in the **locked**
SDK's `Include/FileCons.h` lines 83-86. These remain visible in logs/receipts;
they are not fixed or globally suppressed. Any other numbered compiler/linker/
MSBuild warning fails validation. New SDKs require a deliberate policy review.

The binary audit checks basic PE/header/section bounds, AMD64 DLL, ASLR/NX and
relocations, actual command export rows, and required host/MFC dependency names.
It rejects mixed Release/Debug imports, including numbered debug VC runtimes.
It does not load the DLL or resolve every transitive dependency in a real host.
There is no `/FORCE` link or architecture/checksum bypass.

## Artifacts and provenance

**Package** artifacts (30 days) contain an inner ZIP and outer ZIP checksum.
The inner ZIP contains only the expected HXT, matching PDB in `symbols/`, an
identified receipt, `READ-ME-FIRST.txt`, [HOST-TEST.md](HOST-TEST.md), the read-only
PowerShell verifier and an all-payload SHA-256 manifest. Every package name
includes configuration, run ID, attempt and checkout commit. Debug packages
are prominently labeled debug-host-only.

**Diagnostics** artifacts (14 days) contain helper-test output, MSBuild,
compiler/export/dependency logs, package checks and a JSON receipt. They are not
installable. The job summary distinguishes build/binary audit from host testing.
Receipts identify actual checkout commit/tree, PR head/base, dirty local source,
run/attempt, SDK hash, selected tool versions, Python, runner image and HXT hash.
PR checkout merge refs are test refs, **not evidence that the PR was merged**.
The package's receipt cannot contain the enclosing ZIP's own hash; the outer
checksum and diagnostics receipt record it separately. Hashes establish
integrity, not authenticity or safe behavior of untrusted code.

Download trusted, validated outputs before expiration. Keep the host-tested
binary and its PDB/receipt together as a local rollback backup, outside scanned
HXT directories. We do not automatically promote builds to Releases or change
repository rules. A maintainer may require PR review and both **Windows Release**
and **Windows Debug** checks through repository branch rules. That is recommended
for preventing another premature merge; a draft label is not an access control.

Follow [HOST-TEST.md](HOST-TEST.md) for installation, the context menu, validation
and rollback. No administrator installer or automatic copying into A:M is used.

## Local or persistent-VM reproduction

On a separately configured Windows machine with Git, Python 3.10+ and the locked
VS/MFC/Windows SDK components, run from a Git checkout **outside Windows TEMP**:

```powershell
python -m unittest discover -s tools/am-cloud/tests -v
python tools/am-cloud/build.py --configuration Release --output C:\AMDev\build-001
```

`build-001` must be new. The default SDK is the committed archive; `--sdk-zip`
accepts another local copy only with the same size and digest. Dirty local source
is recorded in the receipt; a dirty CI checkout is rejected. The environment is
not installed/modified by these scripts. No paid VM is provisioned.

## Primary references

- MSVC environment vs MSBuild selection: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line
- Output locations: https://learn.microsoft.com/en-us/visualstudio/msbuild/errors/msb8029
- Matching target/output properties: https://learn.microsoft.com/en-us/visualstudio/msbuild/errors/msb8012
- PE fields: https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
- GitHub workflow security: https://docs.github.com/en/actions/reference/security/secure-use

Infrastructure was developed with AI assistance. Existing Hash/third-party
SDK rights and notices are unchanged. This is not an A:M compatibility guarantee.
