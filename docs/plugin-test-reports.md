# First read-only test plugins

These are experimental SDK-access tests, not certified model validators. They
are separate HXTs and do not replace AMBuildSmoke. Build/host status belongs in
the PR and the receipt; no host success is presumed from CI.

## A:M Model Report v1

Release file: **AMModelReport_64.hxt**.
Open a model directly, then right-click its **Project Workspace model entry >
Plugins > Wizards > A:M Model Report v1 (read-only)**. The command is disabled
for a model instance rather than silently switching to its underlying cache.

It reports spline records, distinct CP records, distinct attachment-head
pointers, group-container entries, SDK GetPatchCount()/CountBones() values,
and raw model-space bounds/mean for finite attachment-head positions. Patch
counts are read as returned; FindPatches/Update/MakeCurrent are never called.
Do not equate this value to an independently recomputed render-mesh total.

## A:M Selection Report v1

Release file: **AMSelectionReport_64.hxt**.
Select points or a named group and use **Plugins > Wizards > A:M Selection
Report v1 - Group (read-only)**. CP and CP instance contexts have their own
suffixed entries. The Group route builds on the context verified with the
baseline diagnostic, but this new plugin still needs its own test.

It distinguishes temporary selection groups from named groups and reports
membership records, distinct CP records and distinct attachment heads, plus
raw model-space bounds/mean. Attached spline CP records can share a head;
these counts need not equal each other or the user's perceived vertex count.
The mean is an arithmetic point mean, not a volume/area centroid. CP-instance
reports deliberately use raw model coordinates, not the animated/world pose.

## Safety and limits

Both commands validate the supplied context before casting, query rather than
edit, and keep borrowed SDK pointers only during the invocation. They do not
save files, modify the clipboard, write logs, call modeling operations or make
network requests. A dialog displays the SDK modified flag before/after; that
flag is not a complete proof of unchanged model data.

Traversal checks stop on unexpected cycles, more than 100,000 traversal steps,
or over two seconds between checks. A check cannot preempt a slow SDK call.
If traversal stops, the command reports failure rather than presenting partial
counts as complete. Null/missing data and nonfinite coordinates are distinguished;
invalid coordinates are excluded from bounds. C++/MFC exceptions are reported;
this does not guarantee recovery from access violations or arbitrary host faults.
No message pumping occurs during traversal. No pointers are kept for later use.

## Build and test

The dedicated **Read-only A:M Report Plugins** workflow explicitly builds both
report projects in Release and Debug. It runs the existing helper tests plus
project guardrails, native SDK-independent bounds/mean tests, the locked builder,
binary audits and intact/tampered package verification. Its project/configuration
names distinguish packages. The original **Animation Master Windows Build**
workflow still builds AMBuildSmoke unchanged; no automatic project discovery is
implied by either workflow.

Use the Release packages and the foundation's `tools/am-cloud/HOST-TEST.md`
verification/closed-host installation/rollback procedure. The generic packaged
host-test guide describes the baseline diagnostic; use the report-specific menu
names above for these two new HXTs. Keep each matching PDB and receipt with its
package. Do not put Debug output or SDK libraries into ordinary A:M.

On disposable data, test an empty model, one simple unjoined three-point spline,
a one-/multi-point selection, a named group, attached spline points, and a closed
spline. Compare reported counts to that deliberately simple construction rather
than asserting a complex production model's totals. For the unjoined three-point
spline, expect one spline and three CP records/attachment heads; validate this
expectation in the actual host. Check the modified flags and that A:M remains
usable after dismissing the report. Save/reload comparisons are separate tests.

Record plugin/run/hash, exact A:M version, context, object construction, results
and any failure. Test Model and Selection separately; one success does not certify
the other. Keep the foundation and report PRs unmerged until their intended tests
and review are complete. Test plugins that edit data (including extrusion) come
after this read-only SDK-access baseline, with explicit undo/rollback design.

Source API reference: the checksum-locked SDK's Include/SDK/HModel.h, HCP.h,
HPatch.h, HHashobj.h and Entry.h. New code and instructions were developed with
AI assistance. Existing SDK/third-party rights are unchanged.
