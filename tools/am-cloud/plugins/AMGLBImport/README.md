# AMGLBImport 0.1.0 — Animation:Master GLB importer

Developed for Rodney Baker / OpenAnimationLibrary with OpenAI Codex assistance.
Windows x64, A:M 19.5 SDK, native C++ command HXT. This is a first host-test
candidate: successful CI builds do not certify behavior inside A:M.

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
- Send only four-distinct-corner quads to A:M's SDK `MergeIEModel(IEPolyModel*)`.
  Peak native CPs to retain the faceted shape. Verify native patch count and the
  complete multiset of four-corner positions against the planned faces; reject
  collapsed/triangular and five-point patches. A mismatch remains an incomplete
  import for inspection, not a silently successful model.

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

Basic material base colors and alpha are transferred. Metallic/roughness factors
receive an approximate legacy specular/reflection mapping; this is not PBR parity.
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
edges belong to open accent surfaces. This result is a core test, not an A:M render.
Other included fixtures isolate a single triangle, square, mixed region and cube.

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
