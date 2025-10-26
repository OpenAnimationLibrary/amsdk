<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# HPropert.h File Reference

`#include "`<a href="HHashObj_8h-source.md" class="el"><code>SDK/HHashObj.h</code></a>`"`  
`#include "`<a href="DataValue_8h-source.md" class="el"><code>DataValue.h</code></a>`"`  
`#include "`<a href="ColorVec_8h-source.md" class="el"><code>ColorVec.h</code></a>`"`  

Include dependency graph for HPropert.h:

<span class="image placeholder" original-image-src="HPropert_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/SDK/HPropert.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="HPropert_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/SDK/HPropert.hdep_map"></span>

[Go to the source code of this file.](HPropert_8h-source.md)

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
&#10;<h2 id="classes">Classes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md" class="el">HPropertyInfo</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Father class for all property UI contexts. <a href="classHPropertyInfo.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md" class="el">HProperty</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Father class for all property holder classes. <a href="classHProperty.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoolPropertyInfo.md" class="el">HBoolPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoolProperty.md" class="el">HBoolProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHContainerProperty.md" class="el">HContainerProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCategoryProperty.md" class="el">HCategoryProperty</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Property used to group several other related properties into a group. <a href="classHCategoryProperty.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHUserCategoryProperty.md" class="el">HUserCategoryProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBoolCategoryProperty.md" class="el">HBoolCategoryProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeCategoryProperty.md" class="el">HTypeCategoryProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrPropertyInfo.md" class="el">HAttrPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md" class="el">HAttrProperty</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">This is where the surface attributes are stored. Initially, the HAttrProperties are filled with the surpace properties as entered by the user in the PWS "Surface" properties. Then, the HAttrProperty is filled with the values that came back from the previous plugins's Evaluate calls. It is up to you whether you combine with what's there or strictly overwrite the contents. <a href="classHAttrProperty.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFileInfoPropertyInfo.md" class="el">HFileInfoPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFileInfoProperty.md" class="el">HFileInfoProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md" class="el">HFloatPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatProperty.md" class="el">HFloatProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPercentPropertyInfo.md" class="el">HPercentPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPercentProperty.md" class="el">HPercentProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHIntPropertyInfo.md" class="el">HIntPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHIntProperty.md" class="el">HIntProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotatePropertyInfo.md" class="el">HRotatePropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md" class="el">HRotateProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHButtonPropertyInfo.md" class="el">HButtonPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHButtonProperty.md" class="el">HButtonProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasPropertyInfo.md" class="el">HBiasPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md" class="el">HBiasProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHStringPropertyInfo.md" class="el">HStringPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHStringProperty.md" class="el">HStringProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFilenamePropertyInfo.md" class="el">HFilenamePropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFilenameProperty.md" class="el">HFilenameProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDirPropertyInfo.md" class="el">HDirPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDirProperty.md" class="el">HDirProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTimePropertyInfo.md" class="el">HTimePropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTimeProperty.md" class="el">HTimeProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTimeRangePropertyInfo.md" class="el">HTimeRangePropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTimeRangeProperty.md" class="el">HTimeRangeProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTransformPropertyInfo.md" class="el">HTransformPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTransformProperty.md" class="el">HTransformProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md" class="el">TypeInfoArray</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Holds the list of choices that appears in a drop-down list. <a href="classTypeInfoArray.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeInfo.md" class="el">HTypeInfo</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Holds individual choice from a list of choices in a drop-down list. <a href="classHTypeInfo.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Contains the UI information that is used to display a drop-down list in a property panel. <a href="classHTypePropertyInfo.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md" class="el">HTypeProperty</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Holds a value associated to a choice from a drop-down list. <a href="classHTypeProperty.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHVectorPropertyInfo.md" class="el">HVectorPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHVectorProperty.md" class="el">HVectorProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHVectorPropertyNoSubsInfo.md" class="el">HVectorPropertyNoSubsInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHVectorPropertyNoSubs.md" class="el">HVectorPropertyNoSubs</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHVector2PropertyInfo.md" class="el">HVector2PropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHVector2Property.md" class="el">HVector2Property</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorPropertyInfo.md" class="el">HColorPropertyInfo</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md" class="el">HColorProperty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td c