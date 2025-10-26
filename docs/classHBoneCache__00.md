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

# HBoneCache Class Reference

`#include <`<a href="HBone_8h-source.md" class="el"><code>HBone.h</code></a>`>`

Inheritance diagram for HBoneCache:

<span class="image placeholder" original-image-src="classHBoneCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HBoneCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HBoneCache:

<span class="image placeholder" original-image-src="classHBoneCache__coll__graph.gif" original-image-title="" border="0" usemap="#HBoneCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHBoneCache-members.md)

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
&#10;<h2 id="public-types">Public Types</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#b4d8902602dd5b62f5b3733df915f51d" class="el">RollMethod</a> { <a href="classHBoneCache.md#b4d8902602dd5b62f5b3733df915f51d4aaa841a56cd6ceaabbed1af3cfa63ba" class="el">Z_SINGULARITY</a>, <a href="classHBoneCache.md#b4d8902602dd5b62f5b3733df915f51dccc40021065ef8ad2868f299f668b20d" class="el">Y_POLES_SINGULARITY</a>, <a href="classHBoneCache.md#b4d8902602dd5b62f5b3733df915f51d84322911d26bccb0bcb0684f8cc13f59" class="el">ROLL_HISTORY</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classHBoneCache.md#dca29a1140aadadfd92b34a02fa516ef2664d4f53735a04613bc282b990311a0" class="el">MANIP_STANDARD</a>, <a href="classHBoneCache.md#dca29a1140aadadfd92b34a02fa516efb8225ab4ae17358f582f0b2fe0786c36" class="el">MANIP_TRANSLATEONLY</a>, <a href="classHBoneCache.md#dca29a1140aadadfd92b34a02fa516ef7bb19f7caaa75af743ec4128cf901275" class="el">MANIP_ROTATEONLY</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#a507cd27f1f309f39b260e0fa6726d62" class="el">GetRollMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#c657778ef0580dc8d6f47320853cbd45" class="el">GetChained</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#a3ea59d2292f93bf2cd480f0c183a551" class="el">GetManipulationMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolCategoryProperty.md" class="el">HBoolCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#6b72919921ce7e1b096d1b22f39ad775" class="el">GetLimitManipulators</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#939bcec2905d4c14204c0db43a6aaf6f" class="el">GetAllowXTranslate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#daf3a6e642de7a461550fbbf7242c94d" class="el">GetAllowYTranslate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#223f91a0b1de17e13a95a5f7645fc8bb" class="el">GetAllowZTranslate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#36e6eddf1284af76b67a5f81f57e6a6b" class="el">GetAllowXScale</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#d4764835c664336693200f6bfeb1b9e4" class="el">GetAllowYScale</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#4c7a58f30a62da3efd1af566b7f39f74" class="el">GetAllowZScale</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#0d4e118a27febf18c7292f5ba61b43d3" class="el">GetAllowXRotate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#739a5e167f5510165e7f2e9050e88041" class="el">GetAllowYRotate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#ff91af58db38458b37665645f647bf39" class="el">GetAllowZRotate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#c8e51a877bcc736eeba95c906dd4cb1a" class="el">GetStop</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHVectorProperty.md" class="el">HVectorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#cd163c36bdab70b3ad7da9218ad74487" class="el">GetPivot</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHVectorProperty.md" class="el">HVectorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#eaea84cb0d49827aebc23dc5ce16d498" class="el">GetEnd</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHRotateProperty.md" class="el">HRotateProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#1d847328e29003cb93b4f5b2e0df52a0" class="el">GetRotate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#0670dbd645d0e24b7f8f78d5c15d6aca" class="el">GetLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#5b802ba8e1093510813427e3845eb03c" class="el">GetRollHandle</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">For 8.5 backward compatibility. <a href="#5b802ba8e1093510813427e3845eb03c"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#457f4c2b50f7e26fb0af8eed2434b5de" class="el">SetBoneColor</a> (<a href="classColorBuf.md" class="el">ColorBuf</a> &amp;color)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classColorBuf.md" class="el">ColorBuf</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#f874f6f9a097bd96887f22d26d64ad3e" class="el">GetBoneColor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#290ff228cbcee1825af7d3d7440d7fa5" class="el">GetBounds</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoneCache.md" class="el">HBoneCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#1027a808f585a06ebd367cc3cbf1a83b" class="el">GetSiblingBoneCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoneCache.md" class="el">HBoneCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#fc081323b0e35d76b80274b170cd8867" class="el">GetChildBoneCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoneCache.md" class="el">HBoneCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#c27c3c337c5c045153d6c237833e2286" class="el">GetParentBoneCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#a573ef0d3c4edccc3e1b01a594da82b0" class="el">GetBoneToStandard</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBone.md" class="el">HBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoneCache.md#db4a871cefb6385afcb3e7779e9539b0" class="el">GetCurrentBone</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

