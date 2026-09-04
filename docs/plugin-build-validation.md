# Plugin build validation record

**Dated evidence: September 4, 2026. Not live CI status.** Recheck the current PR,
head and run before deciding a later candidate is ready. This record preserves
what the initial setup and hardening actually established, without implying
that a newer package or every A:M context has been tested.

## Human-confirmed baseline: diagnostic v2, run #7

Rodney supplied a screenshot and reported success in the development conversation.
The dialog displayed **A:M 19.5g**, **Group** context, object supplied **yes**,
menu resource **present**, and the SDK call returning with the MFC message shown.
The screenshot itself is not copied into the repository.

| Identity | Value |
| --- | --- |
| PR head | `378fb806d29b6bf45343578453575ac4f42e50fa` |
| Checked-out PR test ref | `2c4c2423ba3099c04214b36947fa48fa8f4f1c2d` |
| Run | [33928660776 / #7](https://github.com/OpenAnimationLibrary/amsdk/actions/runs/33928660776) |
| HXT | `AMBuildSmoke_64.hxt`, Release x64 |
| HXT SHA-256 | `6f0c04b7a7a65abd21f7789b5271e7af5501eb0cab57baa3fc317913f0ff790a` |

The machine-readable counterpart is
`tools/am-cloud/validation/known-good.json`. This was one Group invocation, not
coverage of Model, CP, CP instance, Action, Choreography, Debug hosts or every SDK
function. Log writing was attempted but not verified by the screenshot. The
command is non-model-editing by design; no independent model diff was performed.

## Hardened pipeline: run #10, attempt 1

[Run 33930591381 / #10](https://github.com/OpenAnimationLibrary/amsdk/actions/runs/33930591381)
passed both **Windows Release** and **Windows Debug**. PR head was
`4d790889b627e2b566551489bdfe6be428877986`; checkout was
`035e62887b95765432bc968f3a7d591ffff9bc89`. The checkout is a GitHub PR test merge
ref, not a merge into `main`.

| Gate | Release x64 | Debug x64 |
| --- | --- | --- |
| 57 helper/failure-path/project-contract tests | Passed | Passed |
| Complete SDK and locked compiler checks | Passed | Passed |
| Compile, resources and link | Passed | Passed |
| Warning policy and binary audit | Passed | Passed |
| Shipped verifier accepts intact package | Passed | Passed |
| Shipped verifier rejects modified HXT copy | Passed | Passed |
| Separate package/diagnostic uploads | Passed | Passed |
| Execute this new binary in A:M | Not yet recorded | Not tested |

Release HXT: **57,856 bytes**;
SHA-256 `0fdf07ba57e627e932afba472c5392baa0337627459b9524b0615788bb9261b9`.
Debug HXT: **114,688 bytes**;
SHA-256 `631af1f61d1e4f801c084a16e56ad35e7a0a9821178affb8adcb63a136d40759`.
Do not install the Debug HXT into ordinary A:M.

The Release artifact was independently downloaded and checked against GitHub's
artifact digest, its inner ZIP digest, all payload manifest hashes, receipt/HXT
identity and basic PE checks. Both downloaded diagnostic artifacts confirmed
57 tests, intact/tampered verifier behavior, four known SDK warnings and zero
build errors. The original path warnings MSB8012/MSB8029 and source-less compiler
probe's D8003 were absent. The four SDK C4244 warnings remain visible and were
not fixed or globally suppressed.

SDK SHA-256:
`0e917a67d9ac386ea3ad512ce97518f764cddc032957682717c862e64c112977`.
Toolset **14.44.35207**, compiler **19.44.35228**, Windows SDK **10.0.26100.0**,
MSBuild **17.14.51.32402**, Python **3.11.9**, runner image **20260830.290.1**.
The checks select/record these components; they do not freeze the entire hosted
image or establish byte-for-byte reproducible output.

The hardening left the v2 C++ source, resource, StdAfx.h and complete SDK ZIP
unchanged. Link/build settings changed, so run #10 is still a distinct candidate
requiring a repeat host test. It does not replace run #7's human evidence.

## Failures caught during hardening

[Run #8](https://github.com/OpenAnimationLibrary/amsdk/actions/runs/33930116106)
stopped on a Windows short-path/long-path comparison in the warning-policy test.
The correction resolves both filenames before exact comparison; it does not
widen the four-warning allowlist.

[Run #9](https://github.com/OpenAnimationLibrary/amsdk/actions/runs/33930438940)
compiled but rejected the unexpected `.dll` output after imported C++ properties
reset an early TargetExt. The project now sets HXT extensions after
Microsoft.Cpp.props, uses consistent output properties and explicitly selects
x64 host tools. Regression tests protect that order/selection. Both failed
runs published diagnostics rather than installable packages.

Earlier vendor-download checks found an incomplete website archive. The complete
owner-approved SDK was committed, its original digest retained, and the website
fallback removed. No mismatched SDK, architecture relabeling or checksum bypass
was accepted to achieve the successful build.

## Preserving and extending the evidence

Package retention is configured for 30 days; diagnostics for 14 days. Archive a
trusted host-tested HXT, PDB, receipt and hashes together before they expire.
The run links identify historical evidence, not permanent artifact availability.

After testing a new candidate, add the exact run/attempt, HXT hash, version,
context and observed behavior using the host-test form. Keep earlier records
in version history and distinguish additional contexts from untested ones.
A green CI result never silently updates the known-good host record.

[Development process](plugin-development.md) · [Automation runbook](plugin-automation.md)
