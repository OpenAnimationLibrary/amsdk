# Patch Draw: stage-B canvas

The Terrain-inspired surface painter is implemented as a **separate draft
plugin**, `tools/am-cloud/plugins/AMPatchDraw`. It paints a binary surface mask,
shows the four-quad-per-cell topology and exports existing Script Builder JSON.
There is no direct A:M geometry mutation in this milestone. Python is not needed.

Rodney reported the earlier `patch_draw_ring_probe.json` works. That supports
starting the isolated canvas gate; exact native face identity, normals,
adjacency and save/reopen are not all implied by that short report.

- [Usage and architecture](../tools/am-cloud/plugins/AMPatchDraw/README.md)
- [Manual host checklist](../tools/am-cloud/plugins/AMPatchDraw/HOST-TEST.md)
- [Design proposal and remaining gates](patch-draw-design.md)
- [Windows tests](../tools/am-cloud/plugins/AMPatchDraw/tests/run_tests.py)

Repository-relative links are for branch review; public documentation deployment
and merging remain separate decisions. The original Terrain Wizard, Script
Builder, baseline plugins, SDK locks and known-good records remain unchanged.
