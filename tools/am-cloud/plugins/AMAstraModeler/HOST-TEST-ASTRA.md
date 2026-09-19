# AMAstraModeler 0.1.0 host acceptance — Animation:Master 19.5 x64

Record the exact Release HXT SHA-256 and build receipt before testing. CI cannot
launch or inspect Animation:Master, so every item below remains pending until a
tester records it against that exact binary.

## Safe setup

1. Close A:M. Use a disposable project and back up prior HXT files outside every
   plugin-scanned folder.
2. Run `plugin\Verify-Package.ps1`; record its success and the HXT hash.
3. Copy only `AMAstraModeler_64.hxt` into the known-working A:M 19.5 x64 HXT folder.
4. Put a restricted test key in `api_key.txt` beside `master.exe`. Use an account
   with a modest spend limit. Confirm neither the kit nor source tree contains it.
5. Restart A:M. Verify **Wizard → Create Model with Astra...** appears when
   right-clicking Objects, a model, and a group inside a model.

## Required functional checks

- Cancel the prompt dialog: no API call/log attempt and no model.
- Submit `A simple red cube, 20 cm on each side.` with defaults. Confirm the log
  start record appears before the network result, the preview reports six patches,
  and cancelling the preview creates no model.
- Submit the cube again and approve it. Confirm a new embedded model opens, is
  sensibly named, has six four-point patches, one named component group, red
  surface color, outward normals, and no five-point patch.
- In wireframe, verify the box CPs are peaked. Save the model as `.mdl`, close and
  reopen it, and verify geometry, group, normals, and color persist.
- Prompt for a modest snowman using ellipsoids and a hat. Verify smooth curved CPs,
  peaked box CPs, named groups, component separation, preview/actual patch totals,
  Zoom Fit, save/reload, and shaded/wireframe appearance.
- Prompt for a small table using boxes and tapered tubes. Inspect all open tube
  ends; they should be deliberately buried or visibly documented by the prompt
  result, not silently capped with unsupported topology.
- Prompt for a vase and handle using a lathe and torus. Verify orientation, open
  lathe ends, material colors, normals, and reasonable dimensions in centimeters.
- Prompt for a 3×3 custom patch-grid flag. Verify exactly four patches, consistent
  winding, smooth/peaked behavior requested by the plan, and editable splines.

## Isolation, limits, and failure paths

- Invoke the command from an existing model containing recognizable geometry.
  Confirm the generated object is a separate model and the old model is unchanged.
- Repeat generation twice. Confirm names/groups remain owned by their respective
  models and closing one view does not corrupt the other.
- Enter a one-patch limit for a cube. Confirm preflight rejects the plan before a
  model is created and records failure in the log.
- Temporarily rename `api_key.txt`. Confirm a clear error, no network request, no
  model, and a failure completion record. Restore the key afterward.
- Use a deliberately invalid/revoked test key. Confirm the popup and log include a
  request ID when supplied, but never include the key or Authorization header.
- Make the `master.exe` directory non-writable for the test account. Confirm the
  log falls back to `%LOCALAPPDATA%\AnimationMaster\AstraModeler` and generation
  still works. Then make both destinations unavailable and confirm no request is
  sent.
- Disconnect networking and test DNS/TLS/timeout errors. Reconnect and confirm a
  later request succeeds without restarting A:M.
- Cancel during generation. Confirm the UI remains responsive, no model is made,
  and the completion log status is `cancelled_during_generation`. Note the time
  needed for a blocking HTTPS operation to return.
- Force a native failure only in a disposable project if a reproducible case is
  available. Confirm any partial model retains the `ASTRA INCOMPLETE -` prefix,
  existing models are unchanged, and the log reports failure.

## Log/privacy checks

- Open `astra_modeler.log` as UTF-8 JSON Lines. Parse every line independently.
- Confirm the exact prompt—including punctuation and line breaks—is present in the
  matching `attempt_started` record.
- Confirm the finish record has the same attempt ID, UTC time, `gpt-6-astra`, final
  status, IDs/tokens when supplied, and validated component/patch summary.
- Search the log, popup screenshots, build diagnostics, and model names for the
  full key. The search must return no matches.
- Confirm the log contains no raw API response or function-call argument payload.

## Acceptance record

Record A:M version/build, Windows version, HXT SHA-256, build receipt commit/run,
test key type (never the key), date, each result above, screenshots, saved `.mdl`
hashes, observed API request/response IDs, and any host crash dump. Keep failures
with the exact prompt and log attempt ID. Do not mark the build runtime-tested on
the basis of CI alone.
