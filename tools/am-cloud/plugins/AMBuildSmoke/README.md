# AMBuildSmoke diagnostic v2

This is a non-model-editing test plugin for A:M 19.5 x64. It is not an importer,
modeling operation, or background service. It writes a small local diagnostic
log when A:M reaches its exported callbacks; it makes no network requests.

Build #6 compiled and passed its binary audit, but Rodney reported no test entry
in **Plugins > Wizards**. That screenshot confirms the submenu exists, not which
object type A:M passed or whether Windows loaded this particular HXT. The cause
is not yet proven. Do not report v2 as a confirmed loader fix before testing.

## What changed

- Register Model, Group, CP, CP instance, Action and Choreography separately.
  No object is dereferenced, cast, edited or saved by this command.
- Show `A:M Cloud Build Test v2 - <context>` with a built-in label. The command
  no longer disappears when a menu resource is missing or the object is null.
- Log registration, menu entry/return, command entry and the SDK call returning.
- Use MFC module-state management in callbacks that use MFC, while keeping the
  enum-only registration callback independent of MFC, as in the SDK examples.
- Check the original compiled menu resource on invocation and show its status,
  the registered context and the host's reported A:M version in the message.

## Install and test

Close A:M. Replace the previous **AMBuildSmoke_64.hxt** with this build's file in
the same active HXT plugin directory. Do not retain two copies of this test HXT
in different scanned plugin folders; do not replace other installed plugins.
Do not copy SDK libraries or the PDB into A:M. Start A:M again.

First right-click the **model's entry in the Project Workspace**, then inspect
**Plugins > Wizards** for **A:M Cloud Build Test v2 - Model**. This removes the
need to get a single-CP selection exactly right. Model-window selection menus
may instead show Group or CP; the suffix identifies the registered callback.
Action and Choreography object contexts are also registered, but this does not
promise an entry on every empty-space menu in those windows.

Run the command and report the context, A:M version and resource status shown.
The message is an actual host test; successful CI alone is not one.

## Diagnostic log

After starting A:M and opening those menus, enter `%TEMP%` in File Explorer and
look for **AMBuildSmoke-v2-<process ID>.log** from this session. Each stage/context
is logged once per process to avoid logging every menu open. Old logs may remain;
use the latest one. It contains the host executable and loaded plugin paths and
callback stages. Review those paths before sharing; no models, license data or
environment-variable dump are collected. Delete the log after diagnosis.

- `registration`: A:M has reached this DLL's command-registration export.
- `menu-enter` and `menu-return-true`: the menu callback ran and offered an entry
  for the named context. This is stronger evidence than seeing other plugins.
- `command-enter`: the user selected this diagnostic command.
- `sdk-returned; showing-message`: the SDK call returned before the UI message.

No log does **not** prove a missing DLL. The HXT might not be discovered, a DLL
or import might fail to load, the host might not reach registration, or the local
log write might fail. Logging is deliberately not performed from DllMain or
CWinApp initialization. It cannot observe failures before the first callback.
Do not install random DLLs, disable security software, or change the SDK checksum.

When still absent, the useful evidence is the latest log (or that none exists),
the exact A:M About version, and the full installed path of AMBuildSmoke_64.hxt.
Keep PR #3 draft and unmerged until the host test is confirmed.
