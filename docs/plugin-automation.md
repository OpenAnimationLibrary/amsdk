# Plugin automation runbook

This is the operating procedure for scripts, GitHub-connected assistants and
human developers. It documents the existing builder, not an unattended plugin
installer or an implemented source-code generator. Read the [development guide](plugin-development.md) and repository `AGENTS.md` before a write.

## Task inputs and permission boundary

Record repository, intended base/feature branch, plugin project path, requested
change, build configurations, target A:M version/context and acceptance tests.
Resolve those from current repository data where possible. Ask only for genuine
missing requirements, not for an SDK already present in the repository.

A useful handoff specification is:

```yaml
repository: OpenAnimationLibrary/amsdk
operation: prepare-draft-pr
base: verify-current-approved-base
project: tools/am-cloud/plugins/MyPlugin/MyPlugin.vcxproj
configurations: [Release, Debug]
host_test: required-before-known-good-promotion
automatic_merge: false
automatic_install: false
preserve_baseline: true
```

`MyPlugin` is a future example, not an existing project. A development request
permits the scoped source/PR work, not unrelated uploads, token disclosure,
paid VMs, SDK substitutions, release publication or bypassing access controls.
Use the existing GitHub connection or authenticated CLI. Never ask for a token
in a chat or commit a credential. MSBuild executes project code: trust/review
sources before running them, even with read-only workflow permissions.

## Read, change, validate, report

1. Read the repository, PR state, head/base commits, workflow and target files.
   Inspect existing CI instead of relying on a remembered commit count. Confirm
   the target branch contains the builder and complete locked SDK.
2. Make the smallest reviewed change on the authorized branch. Preserve the
   diagnostic baseline and unrelated SDK/reference files. Re-read the head
   before committing; stop if concurrent edits make the intended parent stale.
3. Run helper tests and the intended plugin's native jobs. Read individual job
   steps, logs and receipts; a workflow name or green check alone is insufficient.
4. Match artifacts to source, target, configuration, run and attempt. Verify
   checksums and offer only an audited, intact candidate for manual host testing.
5. Report exact commits/files, completed/failed/skipped gates, artifact identity
   and remaining host work. Record human evidence separately; leave merge and
   installation to an explicit owner instruction.

For a merged/reverted PR, inspect the new `main` and create a fresh branch with
an explicit reapplication when needed. Do not attempt to reopen a merged PR,
blindly re-merge a reverted branch, or reset public history.

## Browser workflow

Edit the intended branch and open/update its draft PR. Changes matching the
workflow's paths trigger the default Release/Debug smoke builds automatically.
Documentation-only changes outside those paths do not necessarily retrigger
native jobs; say so rather than claiming a new native result.

After the dispatchable workflow exists on the default branch, open **Actions >
Animation Master Windows Build > Run workflow**, select the feature branch,
configuration and repository-relative project path. Select the resulting run
and inspect its jobs and artifacts. A:M itself is not running in that VM.

**Before that default-branch workflow exists, use PR-triggered jobs. Do not
merge an unvalidated foundation to get a manual build button.** The initial PR
workflow builds AMBuildSmoke only. For a different plugin, either dispatch its
explicit project after the foundation is approved, or review a PR workflow
change selecting that project/adding it alongside the baseline.

## CLI examples: inspect first

Commands below use an already authenticated `gh` and Git checkout. Browser or
connector access remains sufficient when local CLI tools are not installed.
Replace example branch/project values for an actual task. Check every native
command's exit code in unattended scripts; PowerShell does not universally
turn a nonzero native exit into a terminating exception.

```powershell
$Repo = 'OpenAnimationLibrary/amsdk'
gh pr view 3 --repo $Repo --json number,state,isDraft,baseRefName,headRefName,headRefOid,url
if ($LASTEXITCODE -ne 0) { throw 'Cannot read PR state.' }
gh pr checks 3 --repo $Repo
# This may be nonzero for pending/failed checks. Inspect, do not treat it as success.
```

Use `gh pr diff` or the connector's changed-file/patch actions to review the
actual change. Do not write to `main` just because it is the repository default.
Before publishing local commits, inspect `git status`, `git diff --check` and
`git diff --cached`; stage intended paths rather than unrelated personal files.
Use a normal branch push, never `--force` as routine automation.

## CLI examples: explicit manual dispatch

This section applies **only after** the workflow is available on the default
branch. For the existing sample:

```powershell
$Repo = 'OpenAnimationLibrary/amsdk'
$Branch = 'build/am-plugins-sdk195' # Verify the intended branch still exists.
$Project = 'tools/am-cloud/plugins/AMBuildSmoke/AMBuildSmoke.vcxproj'
$Ref = [uri]::EscapeDataString($Branch)
$Head = gh api "repos/$Repo/commits/$Ref" --jq '.sha'
if ($LASTEXITCODE -ne 0) { throw 'Cannot resolve branch head.' }
gh workflow run am-plugin-windows.yml --repo $Repo --ref $Branch -f configuration=Both -f "project=$Project"
if ($LASTEXITCODE -ne 0) { throw 'Workflow dispatch failed.' }
gh run list --repo $Repo --workflow am-plugin-windows.yml --branch $Branch --commit $Head --event workflow_dispatch --limit 20 --json databaseId,headSha,number,attempt,status,conclusion,url
if ($LASTEXITCODE -ne 0) { throw 'Cannot list runs.' }
```

A run may take time to become visible. Use the returned dispatch URL when
available, or select the matching run ID after checking creation time and
source. Do not take the newest successful run across the repository. Multiple
dispatches can share a head SHA; confirm project/configuration from the receipt
as well. A branch moving during dispatch means the requested `$Head` may no
longer match: resolve that explicitly, not by silently taking another build.

Record the numeric run ID. This read-only example uses historical run #10;
substitute the selected run for new work:

```powershell
$Run = 33930591381
$Status = gh run view $Run --repo $Repo --json databaseId,headSha,headBranch,event,number,attempt,status,conclusion,jobs,url
if ($LASTEXITCODE -ne 0) { throw 'Cannot inspect the selected run.' }
$Status | ConvertFrom-Json | Format-List
# For a running job, gh run watch $Run --repo $Repo --exit-status can wait.
# Check its exit code; some authentication types cannot use watch.
```

When watch is unavailable, inspect `gh run view` or use bounded status polling
with an explicit timeout. Do not broaden token permissions or loop indefinitely.
For PR events, the checked-out merge test ref may differ from the PR head; the
receipt records both. That synthetic ref is not evidence of a merge into main.

## CLI examples: download the exact package

For the historical Release package from run #10:

```powershell
$Artifact = 'AMBuild-Package-Release-x64-r10-a1'
$Destination = Join-Path $PWD 'downloads/run-10-release-a1'
if (Test-Path -LiteralPath $Destination) { throw 'Choose a new download directory.' }
gh run download $Run --repo $Repo --name $Artifact --dir $Destination
if ($LASTEXITCODE -ne 0) { throw 'Artifact download failed.' }
```

For new runs use the actual artifact name/attempt, not the historical example.
Artifacts expire; a missing historical artifact is not a new build failure.
`gh run download` extracts the outer artifact for you. The destination contains
the named inner package ZIP and its `.zip.sha256`; compare the inner ZIP hash,
extract it to a fresh folder, and read its receipt and `READ-ME-FIRST.txt`.
Do not repackage files or rename a Debug `.hxtd` into a Release `.hxt`.

Run the included `Verify-Package.ps1` only from a trusted source package. It
checks payload hashes/receipt consistency without loading a DLL. Respect local
script policy; use manual `Get-FileHash` verification rather than weakening
policy when scripts are blocked. Verify the project, configuration, HXT hash,
source identities and run/attempt against the requested build. The matching
PDB belongs with the archived package, not the active HXT directory.

Only after those gates pass should a human follow `tools/am-cloud/HOST-TEST.md`.
Release packages are candidates for ordinary A:M; Debug packages require a
matching debug host. Never interpret download/verification as installation or
runtime success. No credential, A:M activation, or local compiler is required
to load the Release test in the user's existing installation.

## GitHub connector equivalent

Use the connection's repository/PR/file reads first. Inspect changed paths and
current SHAs; create a commit on the current authorized branch with a normal
fast-forward update. Inspect workflow runs for that commit, then the exact job
steps/logs and artifact IDs. Download the selected artifact via the connector's
artifact action. Confirm the returned file's actual local path before offering
a download link. Cap status polling and distinguish access/tool errors from
compiler errors. Do not route around a denied action or invent completion.

A connector may not expose workflow dispatch, branch administration or every
write API. Use an available authorized equivalent or report the specific limit;
do not pretend a workflow was started or a branch rule was installed. Do not
make a user repeat an SDK upload that the repository already contains.

## Stop conditions and handoff

Stop promotion on an unexpected SDK/compiler, dirty CI tree, failed/skipped
required job, unexpected artifact identity, new unreviewed warning, checksum
failure, expired/missing candidate, or a failed host test. Keep logs and the
last known-good package. Diagnose/rebuild on the feature branch rather than
changing checks to accept the failure.

A handoff should identify: PR/head, run/attempt, project/configuration, HXT hash,
helper tests, native compile/link, binary audit, intact/tampered package checks,
download verification, host result, and exact next action. Say **not tested**
for omitted stages. Automated receipts keep `runtime_tested: false`; human
validation updates are separate reviewed evidence, not fabricated CI success.

Use the [validation record](plugin-build-validation.md) and the host-test form
as examples. Re-run relevant tests after fixes, preserve prior evidence and
obtain explicit approval before merging or deploying.

## Primary references

- [Manual workflow prerequisites](https://docs.github.com/en/actions/how-tos/manage-workflow-runs/manually-run-a-workflow)
- [gh workflow run](https://cli.github.com/manual/gh_workflow_run)
- [gh run list](https://cli.github.com/manual/gh_run_list)
- [gh run view](https://cli.github.com/manual/gh_run_view)
- [gh run watch](https://cli.github.com/manual/gh_run_watch)
- [gh run download](https://cli.github.com/manual/gh_run_download)

CLI recipes were checked against these command references; they are not a
claim that every manual-dispatch path or authentication mode has been exercised
in this repository. The concrete native results are in the validation record.
