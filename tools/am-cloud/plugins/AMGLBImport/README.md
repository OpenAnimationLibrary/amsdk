# AMGLBImport 0.1.3 — Animation:Master GLB importer

Developed for Rodney Baker / OpenAnimationLibrary with OpenAI Codex assistance.
Windows x64, A:M 19.5 SDK, native C++ command HXT. This is an updated host-test
candidate: successful CI builds do not certify behavior inside A:M.

## Changes in 0.1.3

The owner's saved two-color MDL files contain the correct diffuse RGB values and
CP membership, with empty material lists. The imported groups instead store
white specular size 8000% and intensity 2000%, explaining the washed-out colors.
The added working group sets only diffuse green. Renaming did not change the
imported surface values; there is no hidden material in these files.

The adapter had passed displayed percentages to `HFloatProperty::StoreValue`,
which expects normalized fractions. This release corrects specular size,
intensity, reflectivity and transparency, checks their ranges, and reads back
stored values. For `two_color_parts.glb`, specular size must now save as 80 and
intensity as 20. Diffuse colors, group membership, spline routing and geometry
are unchanged. The legacy material mapping is still an approximation to glTF PBR.

The earlier 0.1.1 nullable patch-surface failure was addressed in 0.1.2 by using
persistent `HGroup` properties. That path successfully saved the supplied RGB
colors, but still had the percentage bug. Groups retain complete CP attachment
stacks and split if combining them would enclose another material's face. Part
selection groups remain neutral; no unused default or whole-model color group
is created. The supplied models identify A:M 19.5 PC but do not identify the
installed HXT hash. Acceptance of this new binary remains pending.

## Install and import

1. Close A:M. Extract the whole kit. In `plugin`, run
   `pwsh -NoProfile -File .\Verify-Package.ps1` and preserve the receipt/PDB.
2. Back up any previous AMGLBImport binary, then copy only `AMGLBImport_64.hxt`
   into the same HXT folder used by the working MakeaBone/cloud test plugin.
   Do not copy SDK libraries or Debug `.hxtd` files into an ordinary A:M host.
3. Start A:M and use a disposable project. Right-click **Objects**, a **Model**,
   or a **Group inside a model** → **Import → GLB as Quad Patches...**
4. Choose a GLB. Review the part and quad counts. Default scale is **100 cm per
   GLB unit**, matching glTF meters. Mirror Z is an explicit orientation option.
5. Click Import. A new embedded, editable model is created. Check wireframe,
   shaded surfaces, dimensions, named groups and colors; save as `.mdl`.

The chosen Model/Group is a menu context only; import always creates a new model.
Cancelling either dialog creates nothing. Cancel is available before import;
the native conversion itself has no mid-import cancellation. If the host conversion
fails, a visibly named `GLB INCOMPLETE - ...` model can remain. Inspect or remove
that new model. Automatic rollback and one-step Undo are not promised.

## Quad conversion

- Weld exactly coincident positions within each mesh node; keep separate nodes
  separate. Material, UV0 and normal discontinuities prevent triangle pairing.
- Pair adjacent triangles only when winding, material, seam attributes, convexity,
  angle, aspect ratio and coplanarity tests agree. Pairing is deterministic/greedy,
  not a reconstruction guarantee of the source artist's original quad layout.
- If any triangles remain in a connected region, subdivide that entire region:
  a triangle becomes three quads, a reconstructed quad becomes four. Shared edge
  midpoints prevent T-junctions. Vertices are not smoothed or projected.
- Route each undirected mesh edge once, then create native splines explicitly.
  Three-way centers use one through-spline and one ending spline (two CP records).
  Regular four-way vertices use two through-splines; two-edge boundary corners
  retain two ending splines. CPs remain peaked; positions and quad faces are unchanged.
- Verify native CP positions, CP records per junction, unique edges and every
  patch's four CP-head identities against the plan. Reject missing, duplicated,
  collapsed, triangular, five-point or unintended patches. Align native normals
  with the source winding and Mirror Z choice. A mismatch remains an incomplete import.
- Source vertices with more than four edges still require more than two splines.
  The preview counts these poles explicitly; they need manual retopology for ideal
  spline flow. A pole above 64 edges is rejected before model creation. This release
  fixes generated three-way centers; it does not claim to eliminate source poles.

All-quads does not imply production retopology, good deformation flow or ideal
A:M spline flow. This conservative mode targets static props such as the sword.
It can significantly increase patch count. Smooth character retopology and bias
fitting are future work.

## Supported inputs and limits

GLB 2.0 with a single embedded, uncompressed geometry buffer. Indexed or
non-indexed triangles, strips and fans; float positions; sparse vertex attributes;
node transforms and repeated ordinary mesh nodes. The default scene is used,
or the first scene if none is marked default. Node hierarchy is flattened into
named groups in one model. Positions are converted to native float precision.

Basic material base colors and alpha are assigned through native material groups.
Part selection groups retain Surface = Not Set. Separate groups named
`Part / Material [number]` carry the actual surface settings. A group may cover
only faces with its source material, so overlapping CP sets cannot override
another color. A single-material part needs only one material group; the sword
uses 13. Native checks verify group coverage, stored diffuse RGB and material percentages.
Metallic/roughness factors receive an approximate legacy mapping: specular size
5–80%, intensity 20–80%, reflectivity 0–35%, and transparency from base-color
alpha (0–100%). These properties use 0–1 fractions at the SDK boundary; this is
not PBR parity.
Texture images/UV decals, vertex colors, animations, cameras and lights are omitted
with preview notices. UV0/normals are read to protect pairing seams but are not
transferred as texture coordinates or custom native shading normals.

Skins, morph targets, Draco, meshopt, GPU instancing and any required glTF extension
are rejected. External buffers are never opened. Optional extensions may be omitted;
core attributes are used. Empty, duplicate, non-manifold or inconsistently wound
surfaces are rejected; degenerate source triangles are skipped with a notice.
Names are sanitized to bounded ASCII for the legacy MultiByte host interface.

Limits: 32 MiB GLB; 50,000 source triangles; 100,000 output quads; 250,000 output
mesh vertices; 256 parts; 4,096 nodes/primitives; 8,192 accessors/buffer views;
128 MiB parser allocation budget. Native CP count can exceed mesh vertex count.
All parsing, quad conversion and native input preparation occur before creating
the model. A:M SDK internal allocation/exception behavior remains host-dependent.

## Reference model

`source/examples/simple_sword.glb` is the original generated sword. Standalone
conversion produces 13 parts, 2,324 source triangles, 684 paired quads,
8 subdivided regions, 5,202 output quads and 5,236 mesh vertices. Its 20 boundary
edges belong to open accent surfaces. Its 1,068 three-way vertices each route to
two spline CP records; 906 higher-valence source poles remain and appear in the
preview. These counts describe the portable plan, not host acceptance.
Other included fixtures isolate a single triangle, square, mixed region, cube and
two independently colored named parts (`two_color_parts.glb`). The additional
`color_boundary.glb` has a blue center surrounded by eight red squares and checks
that shared CPs cannot spread the red material onto the blue patch.

## Build in Visual Studio

Install VS 2022 C++ desktop tools, dynamic MFC, MSVC 14.44.35207 and Windows SDK
10.0.26100.0. Compiler identity is 19.44.35228; see `toolchain.lock.json`.
Extract the included checksum-verified `sdk195.zip` into a sibling `sdk` directory,
so `sdk/SDK/V19_5/Include/SDK/Entry.h` exists next to `source`.
Open `source/AMGLBImport.sln`, select Release | x64, and build. Override `AMSdkRoot`
if the SDK is elsewhere. Output: `source/bin/x64/Release/AMGLBImport_64.hxt`.
Debug requires the matching debug A:M host and CRT.

The repository's audited route is:

```
python -m unittest discover -s tools/am-cloud/tests -v
python tools/am-cloud/build.py --configuration Release --project tools/am-cloud/plugins/AMGLBImport/AMGLBImport.vcxproj
```

The dedicated `AMGLBImport Windows Build` workflow builds Release and Debug,
checks PE architecture/exports/dependencies/symbols/warnings, tests the packaged
hash verifier including tamper rejection, and assembles this kit. Its unchanged
`plugin/build-receipt.json` records exact checkout, PR head, CI run/attempt, SDK,
compiler and binary identity. `runtime_tested` remains false. `KIT-SHA256SUMS.txt`
covers all kit members except itself. Source dependencies: pinned MIT cgltf,
with origin, commit and hashes in `source/third_party/provenance.json`.

Read `HOST-TEST-GLB.md` before treating a binary as ready for regular use.
