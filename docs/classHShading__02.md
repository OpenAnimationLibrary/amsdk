## Member Function Documentation

<span id="47915cbb257fa63ed203c352f1763ca1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> * HShading::GetACol</td>
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
|   | Retrieves a pointer to the <a href="classRGBFloat.md" class="el">RGBFloat</a> which contains the surface current ambiance color. From this pointer, the plugin may store a newly computed ambiance color. |

<span id="8f9d7f40c8c05087283cc0b5578799f4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * HShading::GetAway</td>
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
|   | Retrieves a pointer to a normalized vector representing the reflected ray away from light at surface hit point. The Away vector is the mirror direction of the light vector about the surface normal. It is pointing away from the surface. |

<span id="2ddbe46dc3c24c9bdcd96322e4fe4aa3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> * HShading::GetDCol</td>
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
|   | Retrieves a pointer to the <a href="classRGBFloat.md" class="el">RGBFloat</a> which contains the current diffuse color. From this pointer, the plugin may store a newly computed diffuse color. |

<span id="469fd4c9c7f6f1280884dd6c70b13e75" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HShading::GetEDot</td>
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
<td><p>Retrieves the dot product (cosine of the angle) between the eye normalized vector and the surface normal.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
The cosine is projected on the surface normal.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="c5d4a0f7aa2b5ad9c06087bda7161b45" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> HShading::GetHitP</td>
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
|   | Retrieves the hit point, in **screen space**, on the object surface corresponding to the pixel being shaded. |

<span id="f22275518d1b0a15454747f7a57f2677" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HShading::GetIntensity</td>
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

|     |                               |
|-----|-------------------------------|
|     | Retrieves the light intensity |

<span id="a2bc4ed514fb89533f0224eac457a3f1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * HShading::GetL</td>
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
|   | Retrieves a pointer to a normalized vector from incoming light direction at surface hit point. **In screen space**. Must be negated to get a vector pointing away from surface, toward the light. |

<span id="325afbe165c4d220b0a56a324bf8b206" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HShading::GetLDot</td>
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
<td><p>Retrieves the dot product (cosine of the angle) between the light normalized vector and the surface normal.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
The cosine is projected on the surface normal.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="df6befb16a611cdfcd5dadd41ce3d4cc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a> * HShading::GetObject</td>
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
<td><p>Retrieves a pointer to the object being shaded. The pointer must be casted to the appropriate object which can be determined with <a href="classHShading.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">GetObjectType()</a>. For instance, when the object type is FIGUREOBJ, then the pointer should be cast to (<a href="classHModel.md" class="el">HModel</a> *).</p>
<p>Reimplemented from <a href="classHAnimObject.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">HAnimObject</a>.</p></td>
</tr>
</tbody>
</table>

<span id="effdee082fe387ec5dd54c03a2e22ed0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int HShading::GetObjectType</td>
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
<td><p>Retrieves the Object Type of the object being shaded. The object type can be any value from those enumerated in <a href="RType_8h.md" class="el">RType.h</a>. If the object type is FIGUREOBJ, then <a href="classHShading.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">GetObject()</a> can be used to get to the <a href="classHModel.md" class="el">HModel</a> which is being shaded.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
This will not return the same object type as <a href="classHHashObject.md" class="el">HHashObject</a>.
</dd>
</dl>
<p>Reimplemented from <a href="classHHashObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HHashObject</a>.</p></td>
</tr>
</tbody>
</table>

<span id="e69862424d143bbcf36e94b0a397f352" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> * HShading::GetSCol</td>
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
|   | Retrieves a pointer to the <a href="classRGBFloat.md" class="el">RGBFloat</a> which contains the current specular color. From this pointer, the plugin may store a newly computed specular color. |

<span id="410a018b0bb308bee8b9b7914dbbc015" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void * HShading::GetSubObject</td>
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
<td><p>Retrieves a pointer to the sub object being shaded.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
When the raytracer hits a model, <a href="classHShading.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">GetObject()</a> hit retrieve a pointer to an object that derives off of <a href="classRObject.md" class="el">RObject</a> (Renderable Object). If the Object is a FIGUREOBJ, thus a <a href="classHModel.md" class="el">HModel</a>, then the sub object would be the <a href="classHPatch.md" class="el">HPatch</a> that it hit. If the Object is a RPROP the sub object would be a <a href="classIEPoly.md" class="el">IEPoly</a>.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="e77d6f578bba4703a3ee7c87c6216f26" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTexInfo.md" class="el">HTexInfo</a> * HShading::GetTexInfo</td>
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
|   | Retrieves a pointer to the <a href="classHTexInfo.md" class="el">HTexInfo</a> which describes the surface attributes at hit point. |

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropert_8h-source.md" class="el">HPropert.h</a>
- C:/Dox/SDK/Comments/<a href="HPropert_8dox.md" class="el">HPropert.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:57 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
