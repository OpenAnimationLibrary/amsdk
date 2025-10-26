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

# HTexInfo Class Reference

Surface contextual information at a given ray hit point. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

[List of all members.](classHTexInfo-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#b092f4dc2c9bdb7c92b4d4b1c90e2c37" class="el">GetAttr</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Retrieves a pointer to the surface properties. Retrieves a pointer to the surface properties such as diffuse, specular, ambiance colors, roughness, transparency, reflectivity, etc. <a href="#b092f4dc2c9bdb7c92b4d4b1c90e2c37"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#ff64cf1916b839c04c685dbef2ac020f" class="el">GetN</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">surface normal at hit point. <strong>In screen space</strong>. This is the surface normal at hit point (where the ray hits the surface). This normal can be tweaked by your plugin to cause a bumped surface. This <a href="classVector.md" class="el">Vector</a> is normalized before being passed to Evaluate, and it should be normalized by your plugin before returning. You can use the <a href="classVector.md#167b1c859984f40a2dd06fb90ffa02dd" class="el">Vector::Normalize</a> function to accomplish this. <a href="#ff64cf1916b839c04c685dbef2ac020f"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#35170f8abe223996b6ba9a0ee517f031" class="el">GetHeight</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Gets displacement of surface. The Height value is currently only used by textures themselves. It is a way to pass the height from one texture to another. For instance, you might have a texture that creates canyons, tweaking the normal to give this look, and setting the Height value as it goes. There could be another texture that sets the diffuse color according to the Height value. <a href="#35170f8abe223996b6ba9a0ee517f031"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#8d71834ee3c7995fdefc719a6342e907" class="el">SetHeight</a> (float val)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Sets displacement of surface. <a href="#8d71834ee3c7995fdefc719a6342e907"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#e9dda391e2c3dedde6558ffcc4071026" class="el">GetTime</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">time (in seconds) to evaluate. This is the elapsed time in the current choreography that the texture resides in. It is stored in seconds. This variable is there just because we thought somebody might want to know. <a href="#e9dda391e2c3dedde6558ffcc4071026"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#f75eb1966cf590131ff7dd48a1efb58b" class="el">GetFPS</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#4c7eda1420dc2272940720f59ceeb369" class="el">GetPixelWidth</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Screen pixel size at hit in AM units (cm). The Pixel width may be used by a texture plugin to compute proper antialiasing texture values. <a href="#4c7eda1420dc2272940720f59ceeb369"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#784dc7301a48430b1416d3e2146c6c88" class="el">GetGlobalP</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">3D hit coordinate. <strong>In world space</strong>. <a href="#784dc7301a48430b1416d3e2146c6c88"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#e3f0d42e63cdf8560045cd9b7fd60afb" class="el">GetEye</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Point view ray was cast from. <strong>In screen space</strong>. Since this point is in screen space, a value of (0, 0, 0) means that the view ray was cast from the camera which is the normal situation. Any other values means that the view ray was casted from somewhere else. This is the case when the view ray is deflected by a relfective surface. In this case, the returned vector is the position, in screen space, on the surface where the view ray was reflected. <a href="#e3f0d42e63cdf8560045cd9b7fd60afb"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#b8b65b65056e668b5ea75fe6924c7d52" class="el">GetD</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Normalized incoming direction of light ray. <strong>In screen space</strong>. Must be negated to get a vector pointing away from surface. <a href="#b8b65b65056e668b5ea75fe6924c7d52"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#9d27380717631a4457c44ea0f3091f55" class="el">GetMatrix</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">matrix to get from <strong>model space</strong> to <strong>screen space</strong>. In some textures it is necessary to convert a vector from texture space to screen space. This matrix is provided for this reason. To convert the normal to screen space and back again you could do the following: <a href="#9d27380717631a4457c44ea0f3091f55"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">GetObjectType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">GetObject</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTexInfo.md#410a018b0bb308bee8b9b7914dbbc015" class="el">GetSubObject</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

