<div class="tabs">

- [Main Page](index.md)
- <span id="current">[Classes](annotated.md)</span>
- [Files](files.md)
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [Class List](annotated.md)
- [Alphabetical List](classes.md)
- [Class Hierarchy](hierarchy.md)
- [Class Members](functions.md)

</div>

# PatchSplitter Class Reference

`#include <`<a href="SplitPat_8h-source.md" class="el"><code>SplitPat.h</code></a>`>`

[List of all members.](classPatchSplitter-members.md)

<table data-border="0" data-cellpadding="0" data-cellspacing="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td></td>
<td></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#1b64976b869f866a0faf14e39e8e7388" class="el">PatchSplitter</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#493aa5fc7bb3e46ce2a777ad4f8785a9" class="el">Subdivide</a> (<a href="classSplitPatch.md" class="el">SplitPatch</a> &amp;splitpatch, DWORD flatflags=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#54c1600489bf313c42a418e2ca89f70e" class="el">SubdivideCallback</a> (<a href="classSplitPatch.md" class="el">SplitPatch</a> &amp;patch)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#0b203d8925442c330e6d5c89ee0a5eee" class="el">Flatness</a> (<a href="classVector.md" class="el">Vector</a> &amp;p0, <a href="classVector.md" class="el">Vector</a> &amp;p1, <a href="classVector.md" class="el">Vector</a> &amp;p2, <a href="classVector.md" class="el">Vector</a> &amp;p3)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#c9807ec9a9145e333fa931f32b4a62bb" class="el">FlatnessFirst</a> (<a href="classVector.md" class="el">Vector</a> &amp;p0, <a href="classVector.md" class="el">Vector</a> &amp;p1, <a href="classVector.md" class="el">Vector</a> &amp;p2, <a href="classVector.md" class="el">Vector</a> &amp;p3)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#dcc93234b5c633205862441ea965af96" class="el">m_straight</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#1bddf8d0b4ac031a27003b997d852c29" class="el">m_zoom</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#645e4d7ccdb68b5491dc5b08b22d19c2" class="el">m_viewplane</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#1acf5bbbc55232801c7664a7f01d09dd" class="el">m_hither</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#20e382452d724065bc425f47ba94a62d" class="el">m_maxlevel</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#de812cb8066aad908294b43ef4b363df" class="el">m_flags</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#8833f7b4681f1487a1653447a8f3cc6f" class="el">m_isuvs</a>: 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#f86ba90fc262614f189067b81210fb8a" class="el">m_isnormals</a>: 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#9fab6631e025eba443492209783158e3" class="el">m_0or1uvs</a>: 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#2e5073964a61a33503a3c329c097b71a" class="el">m_isvariable</a>: 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#e6e0a806907769d81fc8f53a4492d5bd" class="el">m_is3point</a>: 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#d887fc1e8a7ccb6aadabed144990b25d" class="el">m_iscullbackfacing</a>: 1</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#f3686ac56d1971bfa47f3131f50c0eb4" class="el">SplitSubPatch</a> (<a href="classSplitPatch.md" class="el">SplitPatch</a> &amp;patch, int level, LONG flatflags)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#09e19dde64fc8d9768d69a6c449f1b2d" class="el">SubSplitHorizontal</a> (<a href="classSplitPatch.md" class="el">SplitPatch</a> &amp;patch, int level, LONG flatflags)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchSplitter.md#d7688b2457c00a403131df93fd4d8222" class="el">SubSplitVertical</a> (<a href="classSplitPatch.md" class="el">SplitPatch</a> &amp;patch, int level, LONG flatflags)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

