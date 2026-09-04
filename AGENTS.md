# Instructions for repository automation

These instructions apply to human-assisted scripts and coding agents working
in `OpenAnimationLibrary/amsdk`. They are project workflow rules, not permission
to access unrelated accounts, disclose credentials, or override higher-priority
instructions. An authorized development task does not by itself authorize a
merge, installation, release, repository-visibility change or paid resource.

## Read before editing

Read [the development guide](docs/plugin-development.md),
[automation runbook](docs/plugin-automation.md), [build guide](tools/am-cloud/README.md)
and [host-test protocol](tools/am-cloud/HOST-TEST.md). Inspect the actual target
PR, branch head, source files and relevant workflow runs before writing.
Chat history and a green badge from a different commit are not source evidence.

During the initial foundation review the working PR is #3 on
`build/am-plugins-sdk195`. Verify its current state; do not assume that this
historic branch is still the right base after it has merged or been deleted.

## Preserve these boundaries

- Work on the authorized feature/PR branch. Use its current head as the parent,
  fast-forward only, and stop when concurrent changes invalidate that parent.
  Do not merge, force-push, reset shared history, delete branches or enable
  auto-merge without a separate explicit instruction.
- Preserve the complete committed SDK and `sdk.lock.json`. Do not fall back to
  the website archive, the historical top-level libraries, fabricated headers,
  `/FORCE`, or renamed wrong-architecture binaries. SDK/toolchain updates need
  provenance review, matching headers/libraries, new CI and a new host test.
- Keep AMBuildSmoke as the baseline diagnostic. Add real plugins in separate
  directories under `tools/am-cloud/plugins/`. Do not replace the baseline with
  unrelated functionality. The initial builder supports standalone command
  HXTs, not arbitrary DLL types or ProjectReference graphs.
- Keep credentials in supported authentication stores. Never print tokens,
  upload the process environment, A:M activation data, personal settings or
  production models. Review local diagnostic paths before sharing a log.
- Treat MSBuild projects and downloaded plugins as executable code. Path and
  hash checks are not a sandbox or a signature. Build only trusted sources;
  do not broaden workflow permissions or use pull_request_target to bypass a
  failed build or an authorization restriction.

## Required validation and reporting

Run the helper tests and inspect the requested project's actual native build,
not just the default AMBuildSmoke job. The default PR workflow does **not**
automatically discover and build every `.vcxproj` in the repository.

For each handoff record PR head, actual checkout commit, run ID/attempt,
project/configuration, toolchain/SDK identity, HXT hash and the individual gate
results. Preserve failure diagnostics; never offer a failed/partial package as
installable. Report blocked, skipped or unperformed work accurately.

Build-generated package receipts retain `runtime_tested: false`. Record independent
host evidence separately; do not edit a published package to change this field.
Do not rewrite the host-tested baseline merely because a newer artifact exists.
Record an explicit human test of the exact HXT, version and context in a reviewed
validation update. Retain the earlier tested record in history.

A new binary remains a candidate even if its source is unchanged. Supply the
Release package for ordinary A:M, preserve its PDB and receipt, and follow the
closed-host backup/replace/test/rollback procedure. Never automatically install
Debug output into ordinary A:M or copy SDK import libraries into HXT folders.

## Definition of done

A development change has documented scope and attribution, relevant regression
tests, identified Release/Debug build results, verified package identity, and a
clear host-test status. A model-changing plugin also needs operation-specific
undo, save/reload, ownership/lifetime, invalid-selection and cancellation tests.
CI cannot approve that behavior. Leave merge/deployment decisions to the owner.

For a documentation-only edit, validate new links and examples, distinguish
historical evidence from current status, and say when native CI was not retriggered.
Do not hide legacy API pages by replacing the existing auto-generated MkDocs nav.
