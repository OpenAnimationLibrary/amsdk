# AMGLBImport 0.1.7 — Animation:Master GLB importer

Developed for Rodney Baker / OpenAnimationLibrary with OpenAI Codex assistance.
Windows x64, A:M 19.5 SDK, native C++ command HXT. This is an updated host-test
candidate: successful CI builds do not certify behavior inside A:M.

## Fix in 0.1.7: missing box faces prevented colors

The owner supplied an A:M 19.5 saved sunglasses model and a **0.1.5** error
popup. Comparing CP attachments and patch corners with the unchanged source GLB
found 404 of 406 planned patches, no extra patches, and exactly two missing faces:
the backs of the brass hinges. Each missing face was bounded by one closed spline.
All 404 saved patches used two or more distinct boundary splines. The file had
only the 11 neutral part groups, no material groups and no hidden material entries:
native patch verification stopped the import before its color-assignment stage.
The default 0.1.6 routing had the same issue; its density options did not fix it.

The router now verifies that each planned quad spans at least two spline paths.
For an offending face it tries alternative through-pairs at two existing
three-edge junctions, retaining only a reduction in the number of offending faces.
Each trial preserves positions, edges, face corners, materials and the maximum of
two CP records per attachment. Regular four-edge continuation is unchanged.
Disconnected surfaces are processed separately; repair is limited to 20 million
candidate edge visits per connected surface. An unresolved routing fails before
creating an A:M model. This is a focused correction, not a complete simulation
of A:M's patch finder. The native patch/edge/color gates remain mandatory.

The sunglasses retain 406 quads, 424 mesh vertices, 11 named parts, five colors
and 25 planned material groups, with no subdivision or fallback seams. The
regression driver independently checks boundary spline ownership for every quad,
including the original sword, isolated boxes and rotated/shuffled box arrays.
A native mismatch now states expected/actual counts, missing/unexpected counts,
and the first part with a missing patch; it explicitly explains why colors were
not assigned. Host acceptance of the new binary remains pending. Peaked control
points remain the default; the owner's manual Smooth edit is separate feedback.

## Options added in 0.1.6

- **Target patches:** enter a desired maximum final patch count, up to 100,000.
  `0` preserves the full-density conversion. This is a reduction budget, not an
  instruction to add subdivisions when the source is already below the target.
- **Leave unpaired triangles empty:** retain reconstructed quads and omit the
  remaining triangles instead of filling them with three subdivided quads.
  Empty parts are omitted too. Default is off, retaining the 0.1.5 behavior.
- **Update preview:** recalculate after changing either option. The preview
  reports target versus actual patches, reduced/omitted triangle counts, omitted
  parts and seam counts. Import is disabled while the preview is stale or empty.
  A preview error leaves the options available for adjustment; no model exists yet.

Density reduction preserves named parts, material regions, sharp geometric
edges, boundary corners and extrema. Intermediate points on straight boundary
runs may be removed. It uses up to six candidate reductions and retains the best
valid final quad count, so reducing source triangles cannot silently increase
the delivered patch count. Topology checks reject unsafe candidates; an invalid
reduced part falls back to its original geometry. Some targets are unreachable,
particularly on small, sharply faceted parts. The actual count remains visible.

The edge-collapse solver is pinned [meshoptimizer v1.2](https://github.com/zeux/meshoptimizer/tree/9d9890c73011d75920af614485296d1e03e95448),
used with a relative error threshold of 0.05. That is its approximate shape-error
metric, not a certified maximum pointwise distance. Remaining vertices use source
positions; reduction changes tessellation and can lose detail. Reduced parts
discard source UV/normal seams, which the native importer does not transfer as
decals/custom shading normals. Full-density pairing retains its earlier seam
protections. Basic material colors remain assigned to their retained surfaces.

Omission leaves real holes. A:M can discover small patch loops automatically,
so the converter separates attachments around unintended small boundary loops
while preserving their neighboring quads. Disconnected vertex fans are separated
too. These points appear in the existing neutral `Seam points` groups. Cutouts
can therefore introduce additional unwelded seams. The cleanup is bounded to
eight scans; a pathological remaining case separates its remaining quads rather
than inventing triangle/five-point fills. Every retained patch still has four
distinct corners and each attachment uses at most two spline CP records.

Portable examples: the mixed quad/triangle retains one quad with omission on;
the enclosed-triangle regression retains all three surrounding quads and its hole;
the original sword retains 1,398 quads and omits 932 triangles/two empty parts.
The 320-triangle icosphere reduces from 642 to 194 patches for a budget of 200;
a lower budget can stop above target at the shape/topology limit. A two-color
grid reduces from 64 to 25 patches for a budget of 32 with both colored areas intact.

## Changes in 0.1.5

Fixes the 0.1.4 refusal to import otherwise valid models with unresolved crowded
junctions, including the original sword. Triangle pairing and local reconstruction
still run first. Remaining crowded regions use a seam fallback: keep four-sided
faces, but separate CP attachments along selected matching boundaries. Every
attachment has at most two spline CP records. No triangular/five-point patches
or three-spline attachments are enabled.

**Fallback seams are unwelded.** Their two sides have matching positions, but
are separate CPs and can move apart during editing or deformation. Multiple
independent attachments can occupy the same position. The two-spline limit is
per attachment, not a claim of at most two spline paths at each spatial position.
This retains surface coverage and color assignments, but sacrifices some welded
continuity; it is not global retopology or a watertight deformation mesh. Dense
unstructured input may need many seams. Welding their sides back together can
recreate the crowded junction. Quad-compatible regions do not acquire seams.

The preview and completion message report seam counts. Neutral `Part / Seam points`
groups select all copies of the separated points for inspection. They have no
surface override. The fallback leaves the converted quad corner positions and
materials unchanged; curved patch interiors and shading still need a host check.
The original sword is again a successful portable conversion regression: 2,324
triangles become 5,544 quads with 13 material groups. Native A:M acceptance is pending.

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
4. Choose a GLB. Set target patches and omission if desired, then click **Update
   preview**. Review actual part, quad, omission and unwelded seam counts. Default scale is **100 cm per
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
- If a connected region retains triangles or crowded vertices, subdivide the
  whole region to avoid T-junctions: a triangle becomes three quads and a quad
  becomes four. This separates old crowded poles by regular midpoints/centers.
- Around each remaining crowded pole, separate a bounded neighborhood into
  sectors of at most three incident faces, each bounded by at most four edges.
  Reconnect whole seam paths when both ends still satisfy the limit. Four cleanup
  passes share one million fan-corner checks per part; minimum seam count is not
  guaranteed. Only remaining cut fans receive coincident, unwelded vertex copies.
  No converted face is removed, duplicated or reassigned to a different material.
  Native float preparation permits these explicitly tracked copies, while still
  rejecting unrelated vertices collapsed by scale/coordinate precision.
- Route each mesh edge once. Four-edge junctions use two through-splines;
  three-edge junctions use one through-spline and one ending spline. CPs remain
  peaked. Every attachment has at most two spline CP records, including seam sides.
- Verify native positions, edges, junction counts and each patch's four distinct
  CP heads. Reject missing, duplicate, triangular, five-point or unintended
  patches. Align normals to source winding and Mirror Z. Native failure can still
  leave an incomplete new model for inspection/removal.

Four-sided faces alone do not establish good deformation or ideal spline flow.
This version provides usable fallback surfaces under the attachment limit; it
does not provide global field-guided retopology or fitted smooth spline biases.

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
transferred as texture coordinates or custom native shading normals. Density
reduction discards those pairing seams in parts whose geometry is reduced.

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
- `crowded_pole.glb`: a twelve-edge source pole now produces 24 quads with
  unwelded seams. It must reach the preview/import instead of the 0.1.4 refusal.
- `simple_sword.glb`: the original 2,324-triangle sword now produces 5,544 quads,
  with seams in nine parts and all 13 material groups covered. It deliberately
  remains the original input; no replacement sword hides the regression.
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
with origin, commit and hashes in `source/third_party/provenance.json`, and pinned
MIT meshoptimizer with the same metadata in `source/third_party/meshoptimizer/`.

Read `HOST-TEST-GLB.md` before treating a binary as ready for regular use.
