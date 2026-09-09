# AMGLBImport 0.1.4 — Animation:Master GLB importer

Developed for Rodney Baker / OpenAnimationLibrary with OpenAI Codex assistance.
Windows x64, A:M 19.5 SDK, native C++ command HXT. This is an updated host-test
candidate: successful CI builds do not certify behavior inside A:M.

## Changes in 0.1.4

Four-sided patches and at most two splines at every control point are now
requirements. The converter can pair triangles across gentle curvature, then
revisit local pair choices to reduce crowded junctions and recover missed pairs.
It preserves source vertices, part separation, material boundaries, UV seams and
normal discontinuities. Spline routing happens only after the quad topology passes.

A region that still has more than four incident edges at a vertex is rejected
before any native model is created. The error identifies the part, number of
unresolved junctions, and first welded vertex/GLB position. Subdivision is used
only when the resulting junctions meet the limit. No triangular or five-point
patch exception is enabled. Independent plan, routing and native CP checks enforce
the same contract. Three-edge junctions remain valid: one through-spline plus
one ending spline, with four-sided patches around them.

This is bounded local reconstruction, not a general-purpose quad remesher. Dense
icosphere layouts and the original sword can still need external retopology.
The sword is now a rejection regression; it is no longer offered as a successful
import merely because its output faces are quads. Source positions are preserved,
but curved patch interiors and shading must be checked inside A:M.

The 0.1.3 group-color and normalized surface-percentage fixes are retained. The
owner reported that version working; the report did not identify an exact HXT
hash. Host acceptance of this new binary remains pending.

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
- Candidate quads must retain winding, projected convexity, 10–170 degree corner
  angles and at most 25:1 edge ratio. Adjacent triangle normals may differ by up
  to 30 degrees; deviation from their average plane is limited to 15% of the
  longest boundary edge. Corners remain at their original positions.
- Start with shape-quality ordering. Bounded alternating paths/cycles revise
  local pairs to reduce junctions exceeding four edges and recover unmatched
  triangles. Up to eight deterministic orderings share a file-wide budget of
  one million search steps; each local search is limited to 12 pairs/1,024 steps.
  The search is not guaranteed to find every possible valid reconstruction.
- Reject unresolved crowded vertices before subdivision/native creation. If a
  supported connected region retains triangles, subdivide the whole region to
  avoid T-junctions: a triangle becomes three quads and a quad becomes four.
  Shared midpoints and centers introduce no vertex with more than four edges.
- Route each mesh edge once. Four-edge junctions use two through-splines;
  three-edge junctions use one through-spline and one ending spline. CPs remain
  peaked. Every junction has at most two spline CP records.
- Verify native positions, edges, junction counts and each patch's four distinct
  CP heads. Reject missing, duplicate, triangular, five-point or unintended
  patches. Align normals to source winding and Mirror Z. Native failure can still
  leave an incomplete new model for inspection/removal.

Four-sided faces alone do not establish good deformation or ideal spline flow.
This version improves reconstruction and enforces the junction limit; it does
not provide global field-guided retopology or fitted smooth spline biases.

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

## Included geometry checks

- `curved_quad_sphere.glb`: 192 non-coplanar triangles reconstruct into 96 quads,
  without subdivision or crowded vertices. Eight three-edge junctions remain;
  each uses two splines. This tests recovery of a triangulated cube-sphere layout,
  not arbitrary sphere remeshing.
- `shallow_fan.glb`: six triangles at a common center reconstruct into three
  quads, reducing the center from six edges to three without subdivision.
- `crowded_pole.glb`: a twelve-edge source pole must stop before model creation,
  with its part and first unresolved vertex identified.
- `simple_sword.glb`: the original 2,324-triangle sword retains unresolved crowded
  regions and must also stop before native creation. Its historical 5,202-quad
  result does not satisfy this release's two-spline requirement.
- The square, single triangle, mixed region and cube isolate basic conversion.
  `two_color_parts.glb` tests red/blue groups; `color_boundary.glb` tests a blue
  patch surrounded by red patches sharing CPs.

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
