# AMBuildSmoke diagnostic v2

The run #7 Release binary was successfully invoked by Rodney in **A:M 19.5g,
Group context**. Its dialog showed an object supplied, resource present and an
SDK call returning. See [the exact baseline](../../validation/known-good.json).
The hardening work leaves this C++ source unchanged, but rebuilt binaries still
require a host test. Debug and the other contexts are not yet host-validated.

The command registers Model, Group, CP, CP instance, Action and Choreography
separately. A context is an object registration, not simply the name of the
window. Look under **Plugins > Wizards > A:M Cloud Build Test v2 - <context>**.
The Group entry is the confirmed case; a model's Project Workspace entry is
another intended test route. It does not dereference, edit or save the object.

V2 uses a built-in menu label rather than hiding when a resource lookup fails.
The resource is checked at invocation. The successful Group invocation makes
the original CP-only registration a plausible cause of the missing v1 command,
not a proven sole cause: multiple changes were made together.

Logging is attempted at `%TEMP%\AMBuildSmoke-v2-<PID>.log` after exported callbacks
are reached. Each context/stage is logged once per process: registration, menu
entry, menu return, command entry and SDK return. The header includes the host
executable and HXT paths. It contains no models, license data or environment dump.
There is no network activity or custom loader-lock initialization logging. Review
personal paths before sharing. Log creation was not proven by the success
screenshot. No log does not by itself prove a DLL failed to load.

Use [HOST-TEST.md](../../HOST-TEST.md) for package verification, closed-host manual
replacement, test reporting and rollback. Do not retain duplicate copies of the
same test HXT in scanned plugin folders. Keep its matched PDB with the package
for diagnostics, not in A:M's HXT folder. No automatic installer is supplied.
