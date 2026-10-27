# Make Group

Standalone A:M 19.5 x64 diagnostic command. Run **Plugins > Wizards > Make Group...**
from a Model window selection or Model node. Use a new empty disposable model.
Close A:M before copying only MakeGroup_64.hxt from the verified Release package
into its HXT folder; restart. FontWiz2 and the original Font wizard are untouched.

The command appends a centered 100 cm cube with six independent four-point faces,
matching the owner's working cube(3).mdl shape. It uses 24 straight two-point
splines and 48 control points. Every cube point belongs to the persistent group
**color** (or color 2, color 3, etc. when that name already exists). Existing model
geometry is not added to this group. New points are selected and the view is fit.

After creating the cube/group, the standard Windows color picker opens, initially
blue. Choose a color and OK to assign only that group's diffuse surface. Cancel
keeps the cube and group with no color override, allowing a manual A:M Surface
assignment as a control test. Each invocation creates another cube; this command
does not recolor an arbitrary pre-existing group. No files are saved/reloaded.

Color setup is intentionally short: enable the group's HAttrProperty and diffuse
child with SetNull(FALSE, group), StoreValue at time zero using normalized RGB,
notify surface/group/model, and request UpdateAllViews. There is no font geometry,
modeless hook, peer API, serializer, patch-attribute inspection or instance walk.
This is a new experiment, not a claim to have repaired FontWiz2 or proved an SDK bug.

A model snapshot is requested before geometry insertion; color StoreValue also
requests Undo. Exact Undo grouping/Redo behavior requires a host test. Insertion
failure may leave partial geometry. The command is synchronous; pointers are
revalidated after the modal color picker before assigning color. Only Model-cache
contexts are accepted. No callbacks or SDK pointers survive command completion.

Host test before promotion:
1. In an empty Model, invoke Make Group. Confirm the cube and color group exist.
2. Choose blue. Check immediate shaded color before Save and after deselection.
3. In another empty Model, Cancel the picker, then set the color group's surface
   manually in A:M. Compare immediate behavior with the plugin assignment.
4. Check all 48 CPs in the group, six patches, group-only color scope, repeated
   invocations, cancellation, Undo/Redo and Save/close/reopen.
5. Confirm A:M remains usable after completion. Record exact HXT hash, A:M/Windows
   version, context and results. Debug builds need the matching debug A:M host.

Native tests validate cube coordinates, planarity, outward face order and corner
coverage, not SDK insertion or color rendering. All package receipts remain
runtime_tested:false. Original SDK notices remain applicable. New plugin code:
Open Animation Library, with AI assistance; cube coordinates derive from the
owner's earlier model. No merge, automatic installation or release.

The build explicitly reviews six C4244 locations in the locked SDK's RGBByte.h
for this project only, matching the earlier color-header review. SDK bytes and
compiler warnings remain visible; any different path, location or warning fails.
