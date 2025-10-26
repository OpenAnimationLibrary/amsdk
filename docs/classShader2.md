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

# Shader2 Class Reference

Base class for all shaders that support ambiance shading. [More...](#_details)

`#include <`<a href="ShadeDll_8h-source.md" class="el"><code>ShadeDll.h</code></a>`>`

Inheritance diagram for Shader2:

<span class="image placeholder" original-image-src="classShader2__inherit__graph.gif" original-image-title="" border="0" usemap="#Shader2__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for Shader2:

<span class="image placeholder" original-image-src="classShader2__coll__graph.gif" original-image-title="" border="0" usemap="#Shader2__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classShader2-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classShader2.md#f1a476ac73c56213c3f4ab24de736467" class="el">Shader2</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *treeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual const char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classShader2.md#123659ca53c07d0d3840da958ea0dcb9" class="el">GetShaderAmbianceFilters</a> ()=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classShader2.md#fed93b92a83b95cbfe0a59d49d34ca2f" class="el">GetAmbiance</a> (<a href="classHShading.md" class="el">HShading</a> *shading)=0</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Base class for all shaders that support ambiance shading.

To write a shader plug-in for Animation Master you must derive a class from the <a href="classShader.md" class="el">Shader</a> class provided in "ShadeDll.h". The derivation should look something like this:

<div class="fragment">

``` fragment
class MyCoolShader : public Shader2; 
```

</div>

Once you have declared your new class, you can begin overriding the virtual functions found in the Shader2 base class or in the <a href="classDLLPlugin.md" class="el">DLLPlugin</a> base class. You will need to override nearly every function in the base classes to have a completely functional new shader.

A Shader2 may compute an ambiance value in addition to either a diffuse value, a specular value or all values.

The speciic Ambiance part of a Shader2 is called only once per scene per pixel. The returned ambiance value is added in the rendering equation.

The diffuse and specular parts of the Shaders are called for each lights in the scene. The hit point on the surface of the object is the actual world hit point. This is different from the hit point for Textures and <a href="classTurbulence.md" class="el">Turbulence</a>.

**See also:**  
<a href="classTexture.md" class="el">Texture</a> and <a href="classTurbulence.md" class="el">Turbulence</a>.

Definition at line <a href="ShadeDll_8h-source.md#l00022" class="el">22</a> of file <a href="ShadeDll_8h-source.md" class="el">ShadeDll.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="f1a476ac73c56213c3f4ab24de736467" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Shader2::Shader2</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>treeobject</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
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
<td><dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>treeobject</em> </td>
<td>Points to the plugins owner. It is the class that the <a href="classTexture.md" class="el">Texture</a> is member of. It is the actual class you see in the PWS tree. The constructor only uses it to set the member variable m_treeobject. This member is used for ReAssignPtr. This is also the pointer returned by <a href="classDLLPlugin.md#3ba36241b4d77d9ed655a45db06da58f" class="el">GetOwner()</a>.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classDLLPlugin.md#c4c3b643593ffd04799c247889aeeaa5" class="el">DLLPlugin::DLLPlugin</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *htreeobject)
</dd>
</dl>
<p>Definition at line <a href="ShadeDll_8h-source.md#l00024" class="el">24</a> of file <a href="ShadeDll_8h-source.md" class="el">ShadeDll.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Function Documentation

<span id="fed93b92a83b95cbfe0a59d49d34ca2f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void Shader2::GetAmbiance</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHShading.md" class="el">HShading</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>shading</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [pure virtual]</code></td>
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
<td><p>Returns in the <a href="classHShading.md" class="el">HShading</a> parameter the computed ambiance value.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>shading</em> </td>
<td>Set the <a href="classHShading.md#47915cbb257fa63ed203c352f1763ca1" class="el">HShading::GetACol()</a> to the new computed ambiance color.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
GetAmbiance is called for every visible parts of the scene.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="123659ca53c07d0d3840da958ea0dcb9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">const char * Shader2::GetShaderAmbianceFilters</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [pure virtual]</code></td>
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
<td><p>Indicated whether the plugin will compute an ambiance value.</p>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
NULL if the plugin does not compute an ambiance value or a pointer to a MENUFILTER string if it does compute an ambiance value.
</dd>
</dl>
Example:
<div class="fragment">
<pre class="fragment"><code>const char *CustomShader::GetShaderAmbianceFilters()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   static CString filter;
   filter.LoadString(IDS_MENUFILTER);
   return (LPCTSTR)filter;
}</code></pre>
</div></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="ShadeDll_8h-source.md" class="el">ShadeDll.h</a>
- C:/Dox/SDK/Comments/<a href="ShadeDll_8dox.md" class="el">ShadeDll.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:03 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
