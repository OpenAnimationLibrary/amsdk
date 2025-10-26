="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Index of Refraction (IOR) of the surface at hit point.</p>
<p>The IOR is that of the surface properties no matter if the ray hits from inside or outside.</p></td>
</tr>
</tbody>
</table>

<span id="bfca0cafe6e358982fa58b0d9b813d32" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetRoughness</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Roughness of the surface at hit point.</p>
<p>Roughness is a turbulence function that perturbs the surface of the objects. Thus is Roughness in not 0, the surface normal retrieved from the <a href="classHShading.md" class="el">HShading</a> and <a href="classHTexInfo.md" class="el">HTexInfo</a> classes will already have been perturbed accordingly.</p></td>
</tr>
</tbody>
</table>

<span id="a780bfaed06942ed2d456cc43d74039f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetRoughnessScale</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Roughness Scale of the surface at hit point.</p>
<p>Roughness Scale controls the size of the roughness. Small values show high frequency patterns.</p></td>
</tr>
</tbody>
</table>

<span id="8c9ebb6656b8569b1919338be36e7ec9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * HAttrProperty::GetSpecularColor</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves a pointer to the <a href="classHColorProperty.md" class="el">HColorProperty</a> which contains the current Specular <a href="unionColor.md" class="el">Color</a> of the surface at hit point.</p>
<p>If the specular color is Not Set, then the specular color will be set to match the diffuse color even if that color ultimately comes from a decal.</p></td>
</tr>
</tbody>
</table>

<span id="8834484c647e8882698b525c30c6c899" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * HAttrProperty::GetSpecularColorForRead</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | If you call GetSpecularColor you will get those actual properties just like it always use to be. If the user leaves the specular color marked as "Not Set" in the PWS then when the render is invoked it will use the diffuse color for specular <a href="unionColor.md" class="el">Color</a>. So the GetSpecularColorForRead will return one of two properties : If Specular color is marked as "not set" it will actually return the Diffuse <a href="unionColor.md" class="el">Color</a> property, not the Specular <a href="unionColor.md" class="el">Color</a> Property. So with that being said you should only use this property for read purposes, because if you call StoreValue on it you will actually be changing the Diffuse <a href="unionColor.md" class="el">Color</a> not the Specular color property. |

<span id="ca682eda0f9c446ff524973bd940c585" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetSpecularIntensity</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Specular Intensity of the surface at hit point. |

<span id="24d2711062124e62d1f77886b8dff709" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetSpecularSize</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Specular Size of the surface at hit point.</p>
<p>By convention, if Specular Size is 0, there should be no highlight at all.</p></td>
</tr>
</tbody>
</table>

<span id="5ea546fa185f495e56f7417e007da108" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetTranslucency</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Translucency of the surface at hit point. |

<span id="987e0b5f735975e57a683af4f4cc8bb8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetTransparency</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Transparency of the surface at hit point.</p>
<p>A value of 0 means the surface is totally opaque. A value of 1 means the surface is fully transparent.</p></td>
</tr>
</tbody>
</table>

<span id="babc46110514d463775be8b32e77d9ef" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HAttrProperty::IsBump</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Tells whether any of the materials on a pre-composited attr had bump on. |

<span id="e6c777c8868e6c7b4c1e6e361e605809" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HAttrProperty::IsComplex</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |                                                                   |
|-----|-------------------------------------------------------------------|
|     | Tells whether a pre-composited attr is complex (Combiners etc..). |

<span id="a4d06b7df2141069e22cc9f61ffe7f48" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HAttrProperty::IsDisplace</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Tells whether any of the materials on a pre-composited attr had displace on. |

<span id="e01b86bc84d44bdd04d08ea13dc28635" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HAttrProperty::IsInvariant</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Tells whether any of the materials on a pre-composited attr were invariant. |

<span id="3d9cbd41ce5e98d53ee169d9547259d7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHAttrProperty.md" class="el">HAttrProperty</a>* HAttrProperty::New</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [static]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Reimplemented from <a href="classHContainerProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">HContainerProperty</a>. |

<span id="8a05873b69f20510233a9d605e731f9e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHAttrProperty.md" class="el">HAttrProperty</a>* HAttrProperty::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAttrPropertyInfo.md" class="el">HAttrPropertyInfo</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>propinfo</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [static]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropert_8h-source.md" class="el">HPropert.h</a>
- C:/Dox/SDK/Comments/<a href="HPropert_8dox.md" class="el">HPropert.dox</a>
- C:/Dox/SDK/Comments/<a href="Property_8dox.md" class="el">Property.dox</a>

-----------------------------