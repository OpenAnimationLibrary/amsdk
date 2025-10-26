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

# HActionCache Class Reference

`#include <`<a href="HAction_8h-source.md" class="el"><code>HAction.h</code></a>`>`

Inheritance diagram for HActionCache:

<span class="image placeholder" original-image-src="classHActionCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HActionCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HActionCache:

<span class="image placeholder" original-image-src="classHActionCache__coll__graph.gif" original-image-title="" border="0" usemap="#HActionCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHActionCache-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#26c68939b4bcb5192a7cead4484029b0" class="el">ScaleMethod</a> { <a href="classHActionCache.md#26c68939b4bcb5192a7cead4484029b00bb88312cb5b3585e18c8c0975397150" class="el">SCALENONE</a>, <a href="classHActionCache.md#26c68939b4bcb5192a7cead4484029b0445fa2c0825d3b3835024255ad134bd0" class="el">SCALELENGTH</a>, <a href="classHActionCache.md#26c68939b4bcb5192a7cead4484029b02895282d44c7635e50e76d448394cd57" class="el">SCALEPOSITION</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#d85b49d73e45d0431b18e5a61c7e6f3f" class="el">GetName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFileInfoProperty.md" class="el">HFileInfoProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#5158778c75932b3f5cce79855150386f" class="el">GetFileInfo</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolCategoryProperty.md" class="el">HBoolCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#b6c81fb61e23cb4650052659713bea04" class="el">GetHasStrideLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#c52b64d3eceaf6d9641ebcb58a4b06b6" class="el">GetStrideLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTimeRangeProperty.md" class="el">HTimeRangeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#d6ea90fdca794afe2cb0fe432ab09b67" class="el">GetStrideRange</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#69edb8f6830dbde8b77e14dcd149526c" class="el">GetScaleMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPointerProperty.md" class="el">HPointerProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#642160d517c7e2606c4a6d574cfd8cd4" class="el">GetScaleBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHActionCacheContainer.md" class="el">HActionCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#fcb437983a59d60cb01a9f3d36829889" class="el">GetParentActionCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChor.md" class="el">HChor</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#3712f9fe6343f54d507bf46f0976750f" class="el">GetChor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHActionCache.md" class="el">HActionCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#23749ad4fa7cd16f75693a608facc8ae" class="el">GetSiblingActionCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHModelCache.md" class="el">HModelCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#db00f92491d5a9c0975fe5732b7dbe4a" class="el">GetDefaultModelCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#0f3e2c389e2178899850a6a7a9bb49d3" class="el">SetDefaultModelCache</a> (const char *name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#775173a04992d49439252439d53739da" class="el">SetDefaultModelCache</a> (<a href="classHModelCache.md" class="el">HModelCache</a> *mch)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#b7f7b6889ba31020bffa815b0785054c" class="el">GetTotalTime</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHActionCache.md" class="el">HActionCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#3541630d1665172735efcb45fe018716" class="el">CreateUncontrainedActionCache</a> (<a href="classHModel.md" class="el">HModel</a> *mh, float errortolerance)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#945ae88ca05b013a3320f2ab50c5b102" class="el">CreateStorageDriver</a> (<a href="classHProperty.md" class="el">HProperty</a> *var)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#1dfe172de3b109aa187c946e0b15b908" class="el">GetScaleFactor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#984b361b73c1052564754467d7150e66" class="el">GetScaleStandard</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHModel.md" class="el">HModel</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#43edf488b018927250463f3e49e385df" class="el">EditWithModelCache</a> (<a href="classHModelCache.md" class="el">HModelCache</a> *hmc)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#1dbaf3947a123009cbca7fedec85e400" class="el">EndEditWithModelCache</a> (<a href="classHModel.md" class="el">HModel</a> *hm)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#b7896e62ee96a21518068aee6c01d79f" class="el">EndEditWithModelCache</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Not supported anymore. Use the one that takes a HModel*. <a href="#b7896e62ee96a21518068aee6c01d79f"></a><br />
</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHActionCache.md" class="el">HActionCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHActionCache.md#09f5bb519160b476fad073fd650d50ad" class="el">New</a> (const char *name=NULL, BOOL embedded=TRUE, BOOL insertintoactioncachecontainer=TRUE)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

