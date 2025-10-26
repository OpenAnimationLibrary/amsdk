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

# HAttrProperty Class Reference

This is where the surface attributes are stored. Initially, the HAttrProperties are filled with the surpace properties as entered by the user in the PWS "Surface" properties. Then, the HAttrProperty is filled with the values that came back from the previous plugins's Evaluate calls. It is up to you whether you combine with what's there or strictly overwrite the contents. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HAttrProperty:

<span class="image placeholder" original-image-src="classHAttrProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HAttrProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HAttrProperty:

<span class="image placeholder" original-image-src="classHAttrProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HAttrProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHAttrProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#c2e8a538b3abe003556a77b26019bada" class="el">GetBaseAttr</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#2699c2805f2bb142359abd74fe85297b" class="el">GetDiffuseColor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#44561a878f10c78d37b16190eeeb7d46" class="el">GetDiffuseFallOff</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#c9e3575adcdf845ef7dcba702c2cfe52" class="el">GetAmbianceColor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#cfb7d00aaeee1095dd446a7b6acf04d1" class="el">GetAmbianceColorForRead</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#40f5f3314129372a0022c8660594272e" class="el">GetAmbiance</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#8c9ebb6656b8569b1919338be36e7ec9" class="el">GetSpecularColor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#8834484c647e8882698b525c30c6c899" class="el">GetSpecularColorForRead</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#24d2711062124e62d1f77886b8dff709" class="el">GetSpecularSize</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#ca682eda0f9c446ff524973bd940c585" class="el">GetSpecularIntensity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#bfca0cafe6e358982fa58b0d9b813d32" class="el">GetRoughness</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#a780bfaed06942ed2d456cc43d74039f" class="el">GetRoughnessScale</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#987e0b5f735975e57a683af4f4cc8bb8" class="el">GetTransparency</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#8df6e91d957412d570ca7eb985861a3a" class="el">GetDensity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#3b9ab2a1cd96b52682d7bc647a4692f9" class="el">GetRefraction</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#5ea546fa185f495e56f7417e007da108" class="el">GetTranslucency</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#f9b6e6209ed2b9816937c227a0398a3c" class="el">GetReflectivity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPercentProperty.md" class="el">HPercentProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#a71687d3ab552528a58c37f35a6dbd1f" class="el">GetReflectiveBlend</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#0af69e66cdba553a8e271dd30cb17a40" class="el">GetReflectivityFallOff</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#e6b107dd6a25ae57ff605c0f387dca50" class="el">GetRadiance</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#da5649410f99213646c67ce2b4062243" class="el">GetGlow</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#e6c777c8868e6c7b4c1e6e361e605809" class="el">IsComplex</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#babc46110514d463775be8b32e77d9ef" class="el">IsBump</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#e01b86bc84d44bdd04d08ea13dc28635" class="el">IsInvariant</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#a4d06b7df2141069e22cc9f61ffe7f48" class="el">IsDisplace</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHMaterial.md" class="el">HMaterial</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#f2f6f5b0b6dfb5b486960590936d57d7" class="el">GetMaterialHead</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHAttrProperty.md" class="el">HAttrProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#8a05873b69f20510233a9d605e731f9e" class="el">New</a> (<a href="classHAttrPropertyInfo.md" class="el">HAttrPropertyInfo</a> *propinfo)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHAttrProperty.md" class="el">HAttrProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAttrProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

