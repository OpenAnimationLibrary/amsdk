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

# HLightCache Class Reference

`#include <`<a href="HLight_8h-source.md" class="el"><code>HLight.h</code></a>`>`

Inheritance diagram for HLightCache:

<span class="image placeholder" original-image-src="classHLightCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HLightCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HLightCache:

<span class="image placeholder" original-image-src="classHLightCache__coll__graph.gif" original-image-title="" border="0" usemap="#HLightCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHLightCache-members.md)

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
<td class="memItemRight" data-valign="bottom">{ <a href="classHLightCache.md#dca29a1140aadadfd92b34a02fa516efc66841b14724869ac8d2afae9dfadfb1" class="el">RAYTRACED</a>, <a href="classHLightCache.md#dca29a1140aadadfd92b34a02fa516ef5e88a21bbfa558dc2e0bd33c7b8a4ae5" class="el">ZBUFFERED</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classHLightCache.md#68986ab776eb5d6b5a809a1c005a7300f86eadadfdbec3325b30153311c9a453" class="el">SM_256</a>, <a href="classHLightCache.md#68986ab776eb5d6b5a809a1c005a7300338957867fe392143fa198fe53c92d84" class="el">SM_512</a>, <a href="classHLightCache.md#68986ab776eb5d6b5a809a1c005a730096c0d83e9a46168ff7ba6c3a4592ab29" class="el">SM_1024</a>, <a href="classHLightCache.md#68986ab776eb5d6b5a809a1c005a7300b3fcab75f6b943934218654beb2c754c" class="el">SM_2048</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#f22275518d1b0a15454747f7a57f2677" class="el">GetIntensity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#75d44c7c54551f25270529c9e66469fc" class="el">GetDiffuse</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#a9c4e4b0bc417eedf59c46334bf2f198" class="el">GetSpecular</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolCategoryProperty.md" class="el">HBoolCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#9b406ce3d4bb29218575ffe342d034b7" class="el">GetVolumetric</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolCategoryProperty.md" class="el">HBoolCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#39772af3de1b053ab64e068db75410c6" class="el">GetCastShadows</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#85e7520421f0a0859bdd7820ba332fc8" class="el">GetShadowType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHIntProperty.md" class="el">HIntProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#ab116b1cef88e5e13f37c8c3e09fa574" class="el">GetShadowRaysCast</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#72213bec87faa54bc5196c0926e8e8b3" class="el">GetShadowRayBias</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#4067cbc008f740ae8bbcac2bbfc0103c" class="el">GetShadowMapSoftness</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#4c0dc21aa04836745be53b6c964921d6" class="el">GetShadowMapDarkness</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#a00031239b46e5e0d509028c409f0b24" class="el">GetShadowMapTint</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#c2ef950f3303c70a6867d268d248e705" class="el">GetShadowMapRes</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#a25e8ba073496c44efcdfbef01e47269" class="el">GetShadowMapBias</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFileInfoProperty.md" class="el">HFileInfoProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHLightCache.md#5158778c75932b3f5cce79855150386f" class="el">GetFileInfo</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

