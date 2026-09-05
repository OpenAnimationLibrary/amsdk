# Offline Python model plans: AMScriptBuilder v1

This first slice deliberately avoids a broad Python-to-SDK binding. A reviewed
Python script returns a bounded plan with four fields: version, name, logical
points and ordered open splines. The HXT independently validates it, then asks
before creating a NEW native model. Importing the equivalent JSON works without
Python, providing a useful replay/test route.

This feature lives in a separate, initially stacked draft PR after the tested
model/selection reports. It does not merge or replace the foundation, reports
or their known-good records. Native creation remains subject to A:M host tests.

## Use and script authoring

See `tools/am-cloud/plugins/AMScriptBuilder/README.md` on the feature branch for
the exact protocol, three-method ModelPlan API, examples, limits, process model
and security boundaries. `HOST-TEST.md` in that directory defines the expected
counts, native patch result, save/reopen, cancellation and failure checks.
These two documents are shipped inside each successful test package.

Menu: **Plugins > Wizards > A:M Script Builder v1 - New Model** on a model or
Objects entry in the Project Workspace, or on a Group context. The context
object is not a mutation target. Choose a trusted .py or a data-only .json.

Start with three_point_spline.json, then grid.json. The .py variants calculate
the same plans. Edit constants in a script copy and rerun without compiling an
HXT. Script execution requires an explicitly chosen CPython 3.11 python.exe;
JSON import does not. No packages, API credentials or network service required.

## Deliberate exclusions

No editing of current selections/models, automatic regeneration/replacement,
API connection, embedded CPython DLL, general SDK console, smooth/bias controls,
closed splines, hooks, explicit five-point patches, groups, materials or bones.
At most two spline-specific CP occurrences share one logical point. Equal
coordinates do not imply attachment; shared indices do. Coordinates are raw
model-space units. A:M performs patch discovery after native spline creation.

A separate process is NOT a sandbox. Only run scripts you trust. Python -I/-S,
quoted explicit executable/arguments, job limits, bounded output and cancellation
address reliability; they do not revoke your account's file/network permissions.

This prototype is NEW-MODEL-only partly because a generic SDK transaction/rollback
contract has not been established. No whole-build Undo is promised. Validation
failures precede creation; failure inside native SDK operations can leave a
partial new model, which must be removed through A:M. Production use waits for
operation-specific tests. The reversible CP-translation experiment remains a
separate editing/undo work item, not an implicit capability of Script Builder.

## Automation contract

The dedicated `Offline A:M Script Builder` workflow selects this project in
Release and Debug. It reuses the locked SDK/compiler, strict warning/binary
audits and read-only permissions without changing those gates. It additionally
runs Python plan/runner tests, native parser tests, cross-language fixtures and
real Windows process timeout/output/cancel tests. Embedded runtime resources
are verified as data, not executed as an HXT on the runner. Final package hashes
cover examples/docs as well as the HXT and PDB; tampering with either HXT or an
example must be rejected before candidate publication.

An actual host test is still needed to establish spline attachments, discovered
patches, new-object handling and save/reload. Read [the automation runbook](plugin-automation.md)
and [development guide](plugin-development.md) before modifying this feature.
Do not merge to start a build, weaken SDK/warning checks, publish partial output,
run unreviewed scripts, install Debug output into ordinary A:M, or label CI as
host validation. No optional AI adapter is implemented in this first slice.

Developed with AI assistance. Existing SDK rights and notices remain unchanged.
