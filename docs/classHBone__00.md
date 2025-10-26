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

# HBone Class Reference

`#include <`<a href="HBone_8h-source.md" class="el"><code>HBone.h</code></a>`>`

Inheritance diagram for HBone:

<span class="image placeholder" original-image-src="classHBone__inherit__graph.gif" original-image-title="" border="0" usemap="#HBone__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HBone:

<span class="image placeholder" original-image-src="classHBone__coll__graph.gif" original-image-title="" border="0" usemap="#HBone__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHBone-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTransformProperty.md" class="el">HTransformProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#4cc444739659b7a56dd5eba6ce83b67f" class="el">GetTransform</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#a507cd27f1f309f39b260e0fa6726d62" class="el">GetRollMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#c8e51a877bcc736eeba95c906dd4cb1a" class="el">GetStop</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#c8d8bfb3bb6ae57ba7ef45ddd58c277e" class="el">GetHidden</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBone.md" class="el">HBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#51d89c7918b5264abf82303ff6a02f38" class="el">GetSiblingBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBone.md" class="el">HBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#31d13bcf0bf7437fff05f7bda665ac61" class="el">GetChildBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBone.md" class="el">HBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#1eac48ebb8f1217140a11ce4a58153bb" class="el">GetParentBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoneCache.md" class="el">HBoneCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#1e1c96f1524975a0c663a1c311e4aa81" class="el">GetBoneCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#391038fffa4f9d7de7696d35ae11131a" class="el">GetLocalMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#cc295415acaef8ce98bc51a997a3b83a" class="el">GetGlobalMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#6f30d3f0b08cf9921c360d1dce21aebb" class="el">GetLocalTSQ</a> (<a href="classVector.md" class="el">Vector</a> &amp;translate, <a href="classVector.md" class="el">Vector</a> &amp;scale, <a href="classQuaternion.md" class="el">Quaternion</a> &amp;quat)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#bc6ce1877fc851a782ca1da0eb1a8612" class="el">GetLocalTSE</a> (<a href="classVector.md" class="el">Vector</a> &amp;translate, <a href="classVector.md" class="el">Vector</a> &amp;scale, <a href="classRotateEuler.md" class="el">RotateEuler</a> &amp;re)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#225da4f3f9aae6591bde20dc017ac851" class="el">ComputeBoneDirections</a> (<a href="classVector.md" class="el">Vector</a> &amp;bonedir, <a href="classVector.md" class="el">Vector</a> &amp;rolldir, <a href="classVector.md" class="el">Vector</a> &amp;parentbonedir, <a href="classVector.md" class="el">Vector</a> &amp;parentrolldir)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Obsolete. <a href="#225da4f3f9aae6591bde20dc017ac851"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#e20790511b2d4ef265800b7e57816f74" class="el">GetStandardToAction</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#afa7e6b59a0b263233a8493e062684ce" class="el">SetLocalMatrix</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;matrix)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#60c4d5da3899b8aed77658c4c218b8e2" class="el">SetLocalTSQ</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classVector.md" class="el">Vector</a> &amp;translate, const <a href="classVector.md" class="el">Vector</a> &amp;scale, const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;quat)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#b409be8547e0b598c2c3ce62a3221b66" class="el">SetLocalTSE</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classVector.md" class="el">Vector</a> &amp;translate, const <a href="classVector.md" class="el">Vector</a> &amp;scale, const <a href="classRotateEuler.md" class="el">RotateEuler</a> &amp;re)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#290ff228cbcee1825af7d3d7440d7fa5" class="el">GetBounds</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#912d53db45ea4b82c0ea8dbc69c851aa" class="el">GetBoneToStandardMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#3da152b35859cba7da6a9df0b1215dd0" class="el">GetStandardToBoneMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#ca2ad24d66a1736e78ec895efe47de8e" class="el">GetModelToWorldMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#b01c8745a90935f7c777b701a1063ce2" class="el">GetWorldToModelMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#f9038b5a158f5d0ffc6e3a7ff86c904c" class="el">GetModelToScreenMatrix</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBone.md#c215ca2c36ded6e531fa048b26c9ef89" class="el">GetScreenToModelMatrix</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

