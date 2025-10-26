## Member Function Documentation

<span id="b092f4dc2c9bdb7c92b4d4b1c90e2c37" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * HTexInfo::GetAttr</td>
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
<td><p>Retrieves a pointer to the surface properties. Retrieves a pointer to the surface properties such as diffuse, specular, ambiance colors, roughness, transparency, reflectivity, etc.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
The retrieved pointer is to the properties as set by the user in the PWS. This is not the same as the actual object surface colors (diffuse, specular, ambiance, etc.) that are found in the <a href="classHShading.md" class="el">HShading</a> class.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="b8b65b65056e668b5ea75fe6924c7d52" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> HTexInfo::GetD</td>
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
|   | Normalized incoming direction of light ray. **In screen space**. Must be negated to get a vector pointing away from surface. |

<span id="e3f0d42e63cdf8560045cd9b7fd60afb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> HTexInfo::GetEye</td>
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
|   | Point view ray was cast from. **In screen space**. Since this point is in screen space, a value of (0, 0, 0) means that the view ray was cast from the camera which is the normal situation. Any other values means that the view ray was casted from somewhere else. This is the case when the view ray is deflected by a relfective surface. In this case, the returned vector is the position, in screen space, on the surface where the view ray was reflected. |

<span id="f75eb1966cf590131ff7dd48a1efb58b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HTexInfo::GetFPS</td>
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

<span id="784dc7301a48430b1416d3e2146c6c88" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> HTexInfo::GetGlobalP</td>
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
<td><p>3D hit coordinate. <strong>In world space</strong>.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
<p>The returned value is only valid if the user have turned GlobalAxis ON in the material properties.</p>
<p>From a <a href="classShader.md" class="el">Shader</a> plugin, use HShader::GetHitP instead of this.</p>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="35170f8abe223996b6ba9a0ee517f031" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HTexInfo::GetHeight</td>
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
|   | Gets displacement of surface. The Height value is currently only used by textures themselves. It is a way to pass the height from one texture to another. For instance, you might have a texture that creates canyons, tweaking the normal to give this look, and setting the Height value as it goes. There could be another texture that sets the diffuse color according to the Height value. |

<span id="9d27380717631a4457c44ea0f3091f55" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> * HTexInfo::GetMatrix</td>
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
<td><p>matrix to get from <strong>model space</strong> to <strong>screen space</strong>. In some textures it is necessary to convert a vector from texture space to screen space. This matrix is provided for this reason. To convert the normal to screen space and back again you could do the following:</p>
<div class="fragment">
<pre class="fragment"><code>TransformVectorNoTranslate( texinfo.matrix, delta );</code></pre>
</div></td>
</tr>
</tbody>
</table>

<span id="ff64cf1916b839c04c685dbef2ac020f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * HTexInfo::GetN</td>
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
|   | surface normal at hit point. **In screen space**. This is the surface normal at hit point (where the ray hits the surface). This normal can be tweaked by your plugin to cause a bumped surface. This <a href="classVector.md" class="el">Vector</a> is normalized before being passed to Evaluate, and it should be normalized by your plugin before returning. You can use the <a href="classVector.md#167b1c859984f40a2dd06fb90ffa02dd" class="el">Vector::Normalize</a> function to accomplish this. |

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
<td class="md" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a> * HTexInfo::GetObject</td>
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
|   | Retrieves a pointer to the object being shaded. The pointer must be casted to the appropriate object which can be determined with <a href="classHTexInfo.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">GetObjectType()</a>. For instance, when the object type is FIGUREOBJ, then the pointer should be cast to (<a href="classHModel.md" class="el">HModel</a> \*). |

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
<td class="md" data-nowrap="" data-valign="top">int HTexInfo::GetObjectType</td>
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
<td><p>Retrieves the Object Type of the object being shaded. The object type can be any value from those enumerated in <a href="RType_8h.md" class="el">RType.h</a>. If the object type is FIGUREOBJ, then <a href="classHTexInfo.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">GetObject()</a> can be used to get to the <a href="classHModel.md" class="el">HModel</a> which is being shaded.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
This will not return the same object type as <a href="classHHashObject.md" class="el">HHashObject</a>.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="4c7eda1420dc2272940720f59ceeb369" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HTexInfo::GetPixelWidth</td>
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
|   | Screen pixel size at hit in AM units (cm). The Pixel width may be used by a texture plugin to compute proper antialiasing texture values. |

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
<td class="md" data-nowrap="" data-valign="top">void * HTexInfo::GetSubObject</td>
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
When the raytracer hits a model, <a href="classHTexInfo.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">GetObject()</a> hit retrieve a pointer to an object that derives off of <a href="classRObject.md" class="el">RObject</a> (Renderable Object). If the Object is a FIGUREOBJ, thus a <a href="classHModel.md" class="el">HModel</a>, then the sub object would be the <a href="classHPatch.md" class="el">HPatch</a> that it hit. If the Object is a RPROP the sub object would be a <a href="classIEPoly.md" class="el">IEPoly</a>.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="e9dda391e2c3dedde6558ffcc4071026" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HTexInfo::GetTime</td>
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
<td><p>time (in seconds) to evaluate. This is the elapsed time in the current choreography that the texture resides in. It is stored in seconds. This variable is there just because we thought somebody might want to know.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
(for SDK v8) Note that all values within your ChannelInfo array are already interpolated to reflect their current values.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="8d71834ee3c7995fdefc719a6342e907" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HTexInfo::SetHeight</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>val</em></td>
<td class="md" data-valign="top"> ) </td>
<td clas