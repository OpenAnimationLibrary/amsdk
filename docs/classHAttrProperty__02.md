## Member Function Documentation

<span id="40f5f3314129372a0022c8660594272e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetAmbiance</td>
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
|   | Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Ambiance brightness of the surface at hit point. Ambiance is the value that determines the brightness of an object when no light is hitting it. |

<span id="c9e3575adcdf845ef7dcba702c2cfe52" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * HAttrProperty::GetAmbianceColor</td>
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
<td><p>Retrieves a pointer to the <a href="classHColorProperty.md" class="el">HColorProperty</a> which contains the current Ambiance <a href="unionColor.md" class="el">Color</a> of the surface at hit point.</p>
<p>If the ambiance color is "Not Set", then the ambiance color will match the diffuse color even if that color ultimately comes from a decal.</p></td>
</tr>
</tbody>
</table>

<span id="cfb7d00aaeee1095dd446a7b6acf04d1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * HAttrProperty::GetAmbianceColorForRead</td>
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
|   | If you call GetAmbianceColor you will get those actual properties just like it always use to be. If the user leaves the ambiance color marked as "Not Set" in the PWS then when the render is invoked it will use the diffuse color for ambiance <a href="unionColor.md" class="el">Color</a>. So the GetAmbianceColorForRead will return one of two properties : If Ambiance color is marked as "not set" it will actually return the Diffuse <a href="unionColor.md" class="el">Color</a> property, not the Ambiance <a href="unionColor.md" class="el">Color</a> Property. So with that being said you should only use this property for read purposes, because if you call StoreValue on it you will actually be changing the Diffuse <a href="unionColor.md" class="el">Color</a> not the Ambiance color property. |

<span id="c2e8a538b3abe003556a77b26019bada" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * HAttrProperty::GetBaseAttr</td>
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
|   | HAttrProperty always points to the attribute value for the object you are on, never any other. But if you are on a <a href="classHGroup.md" class="el">HGroup</a> you may call GetBaseAttr to retrieve the HAttrProperty on the <a href="classHModelCache.md" class="el">HModelCache</a>. |

<span id="8df6e91d957412d570ca7eb985861a3a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetDensity</td>
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
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Density of the surface at hit point.</p>
<p>As a material thickens, it eventually becomes opaque, and most water becomes opaque when only a few feet deep. Density is affected by size and is calibrated to the suggested scale used by Animation:Master (in increments of .001/cm), so transparent objects must be built to the correct scale. Colored glass has a density of "2", while seawater has a density of "5",</p></td>
</tr>
</tbody>
</table>

<span id="2699c2805f2bb142359abd74fe85297b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * HAttrProperty::GetDiffuseColor</td>
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
|   | Retrieves a pointer to the <a href="classHColorProperty.md" class="el">HColorProperty</a> which contains the current Diffuse color of the surface at hit point. |

<span id="44561a878f10c78d37b16190eeeb7d46" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetDiffuseFallOff</td>
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
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Diffuse falloff value of the surface at hit point.</p>
<p>Diffuse Falloff controls the transition from light to dark in shaded areas on a model.</p></td>
</tr>
</tbody>
</table>

<span id="da5649410f99213646c67ce2b4062243" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * HAttrProperty::GetGlow</td>
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
|   | Retrieves a pointer to the <a href="classHBoolProperty.md" class="el">HBoolProperty</a> indicating if the surface should glow. Glow is a post effect. But this could bu used by a shader to decide how to shade. The glow color is the diffuse color of the base attribute of the model. The intensity of the glow is controlled by the Ambiance value, and the radius of the glow is a property of the Choreography. |

<span id="f2f6f5b0b6dfb5b486960590936d57d7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHMaterial.md" class="el">HMaterial</a>* HAttrProperty::GetMaterialHead</td>
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

|     |     |
|-----|-----|
|     |     |

<span id="e6b107dd6a25ae57ff605c0f387dca50" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetRadiance</td>
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
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Radiance of the surface at hit point.</p>
<p>Radiance is used by Radiosity. Normally radiance is determined from diffuse color. But the user may change it to get special effects.</p></td>
</tr>
</tbody>
</table>

<span id="a71687d3ab552528a58c37f35a6dbd1f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHPercentProperty.md" class="el">HPercentProperty</a> * HAttrProperty::GetReflectiveBlend</td>
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
<td><p>Retrieves a pointer to the <a href="classHPercentProperty.md" class="el">HPercentProperty</a> which contains the current Reflection Blending of the surface at hit point.</p>
<p>Reflective Blend indicates how reflections are combined with surface color. 0 indicates reflections are additive, 100% indicates the reflections are blended.</p></td>
</tr>
</tbody>
</table>

<span id="f9b6e6209ed2b9816937c227a0398a3c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetReflectivity</td>
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
|   | Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Reflectivity of the surface at hit point. |

<span id="0af69e66cdba553a8e271dd30cb17a40" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetReflectivityFallOff</td>
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
<td><p>Retrieves a pointer to the <a href="classHFloatProperty.md" class="el">HFloatProperty</a> which contains the current Reflectivity Falloff of the surface at hit point.</p>
<p>Reflection Falloff indicates at which distance reflections are no longer visible. It is specified as the distance measured from the ray’s intersection to the reflecting surface.</p></td>
</tr>
</tbody>
</table>

<span id="3b9ab2a1cd96b52682d7bc647a4692f9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * HAttrProperty::GetRefraction</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class