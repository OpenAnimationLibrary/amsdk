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

# Turbulence Class Reference

Base class for all turbulences. [More...](#_details)

`#include <`<a href="Turbulen_8h-source.md" class="el"><code>Turbulen.h</code></a>`>`

Inheritance diagram for Turbulence:

<span class="image placeholder" original-image-src="classTurbulence__inherit__graph.gif" original-image-title="" border="0" usemap="#Turbulence__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for Turbulence:

<span class="image placeholder" original-image-src="classTurbulence__coll__graph.gif" original-image-title="" border="0" usemap="#Turbulence__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTurbulence-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTurbulence.md#ebdac50978660a77bd86552885a89d86" class="el">Turbulence</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *treeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual float </td>
<td class="memItemRight" data-valign="bottom"><a href="classTurbulence.md#33e0b1b8621ec874946cdb2f561832fd" class="el">Evaluate</a> (const <a href="classVector.md" class="el">Vector</a> &amp;evalp)=0</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Base class for all turbulences.

To write a turbulence plug-in for Animation Master you must derive a class from the Turbulence class provided in "Turbulen.h". The derivation should look something like this:

<div class="fragment">

``` fragment
class MyCoolTurbulence : public Turbulence; 
```

</div>

Once you have declared your new class, you can begin overriding the virtual functions found in the Turbulence base class or in the <a href="classDLLPlugin.md" class="el">DLLPlugin</a> base class. You will need to override nearly every function in the base classes to have a completely functional new turbulence.

Definition at line <a href="Turbulen_8h-source.md#l00011" class="el">11</a> of file <a href="Turbulen_8h-source.md" class="el">Turbulen.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="ebdac50978660a77bd86552885a89d86" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Turbulence::Turbulence</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>htreeobject</em></td>
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
<td data-valign="top"><em>htreeobject</em> </td>
<td>- is a pointer to the plugins owner. It is the class that the <a href="classTexture.md" class="el">Texture</a> is member of. It is the actual class you see in the PWS tree. The constructor only uses it to set the member variable m_treeobject. This member is used for ReAssignPtr. This is also the pointer returned by <a href="classDLLPlugin.md#3ba36241b4d77d9ed655a45db06da58f" class="el">GetOwner()</a>.</td>
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
<p>Definition at line <a href="Turbulen_8h-source.md#l00013" class="el">13</a> of file <a href="Turbulen_8h-source.md" class="el">Turbulen.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Function Documentation

<span id="33e0b1b8621ec874946cdb2f561832fd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float Turbulence::Evaluate</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>evalp</em></td>
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
<td><p>Every time a surface is encountered during rendering that has your texture on it, Evaluate is called. This gives you the ability to set what the surface's parameters are.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>evalp</em> </td>
<td>- The 3D coordinate that you should evaluate is passed to you in the form of a <a href="classVector.md" class="el">Vector</a>. This 3D coordinate is the coordinate as computed on the cached object surface. This means that the render time world coordinate on an object surface is reverse transformed to the cached surface. This prevents the texture from floating on the surface as the surface is being deformed from muscle or skeletal actions.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
The value returned should normally be between 0.0 and 1.0 and indicates the mix between the two attributes that are defined in the turbulence as ((Attr1 * retval) + (Attr2 * (1.0 - retval))). Any negative return value is absoluted to positive value and any value greater than 1.0 is clipped to 1.0.
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHObjectCache.md" class="el">HObjectCache</a> for a description of cached objects.
</dd>
</dl></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Turbulen_8h-source.md" class="el">Turbulen.h</a>
- C:/Dox/SDK/Comments/<a href="Turbulen_8dox.md" class="el">Turbulen.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:04 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
