# Two-plugin message test

Windows x64 command plugins for Animation:Master 19.5, built against the committed,
locked SDK. New code by Open Animation Library with AI assistance. HXT registration
and project setup follow the Hash SDK samples and the existing AMBuildSmoke builder.

## Install and run

1. Download the successful **Release** packages for **AMMessageA** and **AMMessageB**.
   Verify each package using its supplied verifier and retain its receipt and PDB.
2. Close A:M. Copy only `AMMessageA_64.hxt` and `AMMessageB_64.hxt` into the
   **same active HXT folder**. Restart A:M. No compiler is required to use them.
3. Open a Model. Right-click its Model entry in the Project Workspace and choose
   **Plugins > Wizards > Message Test A -> B**. The Group selection menu in the
   Model window is also registered. Empty-space menu placement depends on the host.
4. Plugin B displays **Hello from Plugin A.** Click OK: B finishes and returns its
   reply. Plugin A then displays **Plugin A resumed after Plugin B returned**, along
   with the sent message, reply and Completed result.
5. Run **Message Test B -> A** for the reverse direction. The same two-dialog
   sequence should finish with Plugin B resuming.
6. Repeat with Cancel in the receiving dialog. The caller must resume and show
   Cancelled. Close the final dialog and confirm the Model window remains usable.

No model data or selection is modified, no files are written by the plugins, and no
network/worker thread is used. The borrowed object context is passed synchronously
and never retained or deleted. Neither DLL starts another exchange when receiving,
so A/B cannot recursively call one another. Nested invocations return Busy.

If a partner is missing, the initiating plugin displays a load error. Put both
matching Release files together. Debug `_64d.hxtd` output requires a matching debug
A:M host and must not be installed in ordinary A:M. Close A:M before changing files.
To remove this test, close A:M and remove only its two HXT files.

## Implementation and validation

Both independently loadable HXTs export the three A:M command callbacks plus our
own `AMMessageExchangeV1` C entry point. `GetProcAddress` resolves that entry in the
sibling HXT. A synchronous function call returns the response to the original
plugin. The caller holds its own module reference throughout the call. Fixed-size
caller-owned structures carry a version, borrowed context/window and ASCII message;
there is no cross-DLL allocation or C++ exception propagation. MFC state is scoped
inside each DLL callback.

Build each standalone project with `tools/am-cloud/build.py --configuration Release
--project tools/am-cloud/plugins/AMMessageA/AMMessageA.vcxproj` (or AMMessageB), using
the existing locked Windows environment. Use a fresh `--output` for each build.
The message workflow compiles both plugins in Release and Debug, checks exports
(including our message ABI), dependencies and PE format, and verifies each intact
package and rejection of a modified copy. Standalone native protocol tests cover
completion, cancellation, borrowed-context identity and invalid sizes/versions/text.

CI does not run Animation:Master or load these DLLs into its host. Thus the actual
Model-menu appearance, modal dialog sequence, cross-DLL call in A:M and host
stability remain **untested until the exact binaries are tried in A:M**. Receipts
retain `runtime_tested: false`. Record run, commit, HXT hashes, A:M version, menu
route and results before promoting a candidate. See ../../HOST-TEST.md.

The test branch explicitly records the runner's compiler patch 19.44.35229 after
run 40258131287 detected the change from 19.44.35228. The SDK archive, MSVC toolset
directory and Windows SDK stay unchanged. The earlier host-tested baseline record
is preserved; it does not validate these newly compiled plugins.
