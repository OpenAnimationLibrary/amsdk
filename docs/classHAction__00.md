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

# HAction Class Reference

`#include <`<a href="HAction_8h-source.md" class="el"><code>HAction.h</code></a>`>`

Inheritance diagram for HAction:

<span class="image placeholder" original-image-src="classHAction__inherit__graph.gif" original-image-title="" border="0" usemap="#HAction__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HAction:

<span class="image placeholder" original-image-src="classHAction__coll__graph.gif" original-image-title="" border="0" usemap="#HAction__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHAction-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#a83281640c5167f2fe04b57e79f15ebe" class="el">BlendMethod</a> { <a href="classHAction.md#a83281640c5167f2fe04b57e79f15ebe560a2dd6f6744646473b3b19e1fe96d7" class="el">REPLACE</a>, <a href="classHAction.md#a83281640c5167f2fe04b57e79f15ebe9eeb52badb613229884838847294b90d" class="el">ADD</a>, <a href="classHAction.md#a83281640c5167f2fe04b57e79f15ebef58072a9536aaeef0196115e445fa4d8" class="el">BLEND</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTimeRangeProperty.md" class="el">HTimeRangeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#b3abbad58461c6cfc86329653f2898ec" class="el">GetCropRange</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTimeRangeProperty.md" class="el">HTimeRangeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#8818897e3c55a8607f424ed6b3d29dde" class="el">GetChorRange</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#04c49c8811276417eaf740745131ad1c" class="el">GetRepeatCount</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTimeProperty.md" class="el">HTimeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#42f504c5e5a475c8eff8a65482e0f52b" class="el">GetCycleLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#48128862bf7736d5fd08cedc1772629d" class="el">GetBlendMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPercentProperty.md" class="el">HPercentProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#e3d10f3849b2ca66561dc05573ce62f3" class="el">GetBlendRatio</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#0a2af7c2f4b84212b79c12c57c11d4cd" class="el">GetIsHoldLastFrame</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#bcfe06d58eda94c00cd47c04a0a4865c" class="el">GetIsPostTransition</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPercentProperty.md" class="el">HPercentProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#881b1a7878a567448aee6589e2ee13fb" class="el">GetEase</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#b7f7b6889ba31020bffa815b0785054c" class="el">GetTotalTime</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#1dfe172de3b109aa187c946e0b15b908" class="el">GetScaleFactor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBone.md" class="el">HBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#1eac48ebb8f1217140a11ce4a58153bb" class="el">GetParentBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHActionCache.md" class="el">HActionCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#963b4bcb366cc6fae560c1caa7e7a038" class="el">GetActionCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHModel.md" class="el">HModel</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#f7b2ff40e256004d3fcb5685edb9c922" class="el">GetParentModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChor.md" class="el">HChor</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAction.md#3712f9fe6343f54d507bf46f0976750f" class="el">GetChor</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

