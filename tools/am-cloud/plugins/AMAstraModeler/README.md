# AMAstraModeler 0.2.0 — Astra model generation for Animation:Master

Developed for Rodney Baker / OpenAnimationLibrary with OpenAI Codex assistance.
Windows x64, Animation:Master 19.5 SDK, native C++ command HXT.

This is a host-test candidate. The portable planner tests and Windows build/binary
audit do not certify behavior inside Animation:Master. Read `HOST-TEST-ASTRA.md`
and begin with a disposable project.

## What it does

Right-click **Objects**, a **Model**, or a **Group inside a model**, then choose
**Wizard → Create Model with Astra...**. Enter a model description, optionally
load one reference image with **Browse...**, and set component/patch limits. The
plugin sends the prompt and selected image to OpenAI's Responses API with model
`gpt-6-astra`, receives one strict function call, validates the complete plan,
and shows a preview. Nothing is added to the A:M project until **Create Model**
is pressed.

The command always creates a **new embedded model** and opens its modeling window.
It never edits the selected model. Components become disconnected named groups
with A:M surface colors and finish approximations. Version 0.2.0 supports:

- boxes;
- smooth cube-sphere ellipsoids;
- tori;
- open tapered tubes;
- open positive-radius lathes; and
- custom rectangular patch grids.

Tube and lathe ends are intentionally open, so the planner is instructed to bury
or cover them when a closed silhouette matters. Components can overlap but are
not Booleaned or welded together. This favors modest stylized models rather than
dense production topology.

## Reference image input

The prompt dialog now has a **Reference image (optional)** row. Click **Browse...**
to choose one PNG or JPEG file; the selected path appears in
the read-only field. Click **Clear** to return to a text-only request. The image is
read and revalidated when **Generate Plan** is pressed. Validation uses the file
signature rather than trusting its extension.

Reference images are limited to 4 MiB, 65,535 pixels per side, and 64 megapixels.
Their signature, dimensions, single-frame structure, and decoded pixels are
validated with Windows Imaging Component before the API key is read. They are
sent to OpenAI as a Base64 data URL with `detail: "high"`; they are not added to the
A:M project as decals, rotoscopes, or image assets. The plugin uses the visible
subject, silhouette, proportions, and large color regions as modeling guidance.
It is not photogrammetry: backgrounds and fine texture are ignored, unseen sides
are inferred, components remain disconnected, and this version does not create
bones. A clean view with a simple background and a short prompt such as
`Make a stylized model of this vehicle.` is the intended starting point.

## Install and configure

1. Close Animation:Master. Extract the entire kit and run
   `pwsh -NoProfile -File .\plugin\Verify-Package.ps1`.
2. Back up any earlier plugin outside A:M's scanned plugin directories. Copy only
   `plugin\AMAstraModeler_64.hxt` to the same HXT folder used by your working A:M
   19.5 x64 plugins. Do not install the Debug `.hxtd` in a Release host.
3. In the directory containing `master.exe`, create a plain-text file named
   `api_key.txt`. Put exactly one OpenAI API key in it; surrounding whitespace and
   a UTF-8 BOM are accepted. Do not add this file to source control or the kit.
4. Restrict `api_key.txt` to the Windows account that runs A:M. The key is plain
   text because that location and format are part of this plugin's configuration.
5. Start A:M with a disposable project and follow `HOST-TEST-ASTRA.md`.

The plugin does not read an environment variable or search other directories for
the key. It never writes the key to the prompt log, error messages, build receipt,
or API request body. It uses Windows' system HTTPS/proxy stack and refuses HTTP
redirects. The OpenAI account that owns the key is responsible for API access,
usage limits, and charges.

## Prompt log

Every submitted prompt is recorded as UTF-8 JSON Lines in:

`<directory containing master.exe>\astra_modeler.log`

If that directory cannot be written, the fallback is:

`%LOCALAPPDATA%\AnimationMaster\AstraModeler\astra_modeler.log`

The plugin opens and flushes the first log record **before** reading the key or
sending the prompt. If neither log can be opened, the API request is not made.
Each attempt has two append-only records:

- `attempt_started`: UTC timestamp, attempt ID, plugin/model, exact prompt,
  requested limits, and either `reference_image: null` or the selected image's
  basename, canonical media type, byte size, dimensions, and `high` detail mode;
- `attempt_finished`: success, failure, or cancellation; request/response IDs and
  token counts when available; and validated model/material/component/patch/
  vertex/spline/CP totals when available.

Failure detail is recorded, but the API key, Authorization header, absolute image
path, image bytes/Base64, full response, and function arguments are not. The log
can still contain sensitive prompt text and the image basename; protect, retain,
or delete it according to your own policy. Image data URLs and unusually long
encoded values are redacted from diagnostic text before display or logging.

## Validation and failure behavior

The model does not return C++ or A:M script. It must call one strict function whose
schema only permits the six component types above. Before A:M is modified, the
plugin rejects unknown fields, invalid materials, duplicate names, non-finite or
out-of-range coordinates, collapsed points, zero-area/duplicate/non-manifold
quads, junctions that require more than two A:M spline CP records, unsafe spline
routing, or a limit overrun.

Hard limits are 16 materials, 100 components, 20,000 four-point patches, 100,000
native CP records, a 16,000-byte prompt, a 4 MiB/64-megapixel reference image, an 8 MiB API
request, a 1 MiB tool-call argument payload, and an 8 MiB API response. The
defaults are 100 components and 2,000 patches.

After native creation, the plugin independently checks spline edges, CP positions
and attachment counts, smooth/peaked state, four-point patch identity, absence of
five-point patches, normals, group coverage, and stored diffuse colors. Only then
is `ASTRA INCOMPLETE - ...` renamed to the requested model name.

Cancellation before preview creates no model. A native host failure can leave a
new model visibly named `ASTRA INCOMPLETE - ...`; inspect or remove it. Existing
models are not edited. Automatic rollback and one-step whole-build Undo are not
promised. Network cancellation is cooperative; a blocking Windows HTTPS operation
may take until its timeout to return.

## API behavior and privacy

The request uses the Responses API with:

- `model: "gpt-6-astra"`;
- high reasoning effort;
- one forced strict `build_animation_master_model` function;
- parallel tool calls disabled;
- response storage disabled; and
- no unsupported sampling fields such as `temperature` or `top_p`.

The exact prompt, fixed modeling instructions/schema, and the explicitly selected
image bytes are sent to OpenAI. Raw image metadata such as EXIF may be present in
those bytes. No A:M project geometry or other local files are uploaded. The
request sets `store: false`, but API processing still occurs. Review the current
[OpenAI image-input documentation](https://developers.openai.com/api/docs/guides/images-vision),
API data controls, and your organization's policy before using confidential
prompts or images.

## Build

Install Visual Studio 2022 C++ desktop tools, dynamic MFC, MSVC 14.44.35207, and
Windows SDK 10.0.26100.0. Extract the checksum-verified A:M 19.5 SDK as `sdk` next
to `source`, so `sdk\SDK\V19_5\Include\SDK\Entry.h` exists. Open
`source\AMAstraModeler.sln`, select Release | x64, and build. Output:
`source\bin\x64\Release\AMAstraModeler_64.hxt`.

The project runs the portable planner tests as a pre-link gate. The repository's
audited route is:

```text
python -m unittest discover -s tools/am-cloud/tests -v
python tools/am-cloud/build.py --configuration Release --project tools/am-cloud/plugins/AMAstraModeler/source/AMAstraModeler.vcxproj
```

The dedicated workflow builds Release and Debug, runs the planner tests, checks
PE architecture/security flags, exports, dependencies, PDBs, warnings, package
hashes, the shipped verifier, and deliberate tamper rejection. Its receipt keeps
`runtime_tested: false` until the exact binary is exercised in A:M.
