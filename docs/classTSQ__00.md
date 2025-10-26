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

# TSQ Class Reference

`#include <`<a href="Rotate_8h-source.md" class="el"><code>Rotate.h</code></a>`>`

Collaboration diagram for TSQ:

<span class="image placeholder" original-image-src="classTSQ__coll__graph.gif" original-image-title="" border="0" usemap="#TSQ__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTSQ-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#c0ad411b9781e2252720ea9d04d89e2a" class="el">TSQ</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#7b57407bc28819991dd2dea59eaf84aa" class="el">TSQ</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;actionmatrix)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#0425c7bf0377d3463e8a6369ff70bc20" class="el">TSQ</a> (const <a href="classVector.md" class="el">Vector</a> &amp;ptranslate, const <a href="classVector.md" class="el">Vector</a> &amp;pscale, const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;pquat)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#6c9cacf56014f62c5b9c55a89094271f" class="el">operator!=</a> (const <a href="classTSQ.md" class="el">TSQ</a> &amp;b) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#76778c3a6f621cd10d92dc726bad0084" class="el">SetDefault</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTSQ.md" class="el">TSQ</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#f6f22c7806c8be3b2fd353331da22f1e" class="el">operator+=</a> (const <a href="classTSQ.md" class="el">TSQ</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTSQ.md" class="el">TSQ</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#69beae508cd8025dbd0d419ee219aa98" class="el">operator *=</a> (float scalar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#e5f88dcca8df39e32e44a577392ae6b6" class="el">PostBlend</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#dab268ff04d627804bfddcf1c11d38b6" class="el">FillMatrices</a> (<a href="classMatrix34.md" class="el">Matrix34</a> &amp;matrix, <a href="classMatrix34.md" class="el">Matrix34</a> &amp;inverse)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#fc46e26a907870744758b76166150f62" class="el">translate</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#0cb47aeb6e5f9323f0969e628c4e59f5" class="el">scale</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#21d7dc6abbf56bdd120c87b69ba9e6a6" class="el">quat</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#b6a5d96a4e99b63723ab54ddb471baad" class="el">roll</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md#18d4ac9112b1a6454fa87c50eb0ac20e" class="el">m_isrollcomputed</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

