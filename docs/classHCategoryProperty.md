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

# HCategoryProperty Class Reference

Property used to group several other related properties into a group. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HCategoryProperty:

<span class="image placeholder" original-image-src="classHCategoryProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HCategoryProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HCategoryProperty:

<span class="image placeholder" original-image-src="classHCategoryProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HCategoryProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHCategoryProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCategoryProperty.md#af7a28db1a2df225d6bc68ebfde049d8" class="el">AddProperty</a> (<a href="classHProperty.md" class="el">HProperty</a> *property)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCategoryProperty.md#19cf720234d097ca5370f2873133e7cc" class="el">RemoveProperty</a> (<a href="classHProperty.md" class="el">HProperty</a> *property)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCategoryProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCategoryProperty.md#5d97edce62d064870e238bb938a6450e" class="el">New</a> (<a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Property used to group several other related properties into a group.

**Note:**  
For HXT plugins, use the <a href="classHDynamicCategoryProperty.md" class="el">HDynamicCategoryProperty</a>.

<!-- -->

**See also:**  
<a href="classHDynamicCategoryProperty.md" class="el">HDynamicCategoryProperty</a>

Definition at line <a href="HPropert_8h-source.md#l00164" class="el">164</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="af7a28db1a2df225d6bc68ebfde049d8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int HCategoryProperty::AddProperty</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>property</em></td>
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
<td><p>Appends a new property at the end of the properties group.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>property</em> </td>
<td>- The new appended property.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
The index of the new property in the properties group. The property may later be retrieved with <a href="classHTreeObject.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">HTreeObject::GetPropertyAt</a> function.
</dd>
</dl>
Example:
<div class="fragment">
<pre class="fragment"><code>m_options = HCategoryProperty::New( theApp.m_optionsinfo );
   m_ampl = HFloatProperty::New( theApp.m_amplinfo );
   m_options-&gt;AddProperty(m_ampl);
   m_octaves = HIntProperty::New( theApp.m_octavesinfo );
   m_options-&gt;AddProperty(m_octaves);</code></pre>
</div>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
You must remove the property before deleting it
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="Cshuser_8h.md#8583de6bbb140fde9ab8f93357543a63" class="el">BOOL</a> <a href="classHCategoryProperty.md#19cf720234d097ca5370f2873133e7cc" class="el">HCategoryProperty::RemoveProperty(HProperty *property)</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="5d97edce62d064870e238bb938a6450e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a>* HCategoryProperty::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>propinfo</em></td>
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
|   | Reimplemented from <a href="classHContainerProperty.md#5d97edce62d064870e238bb938a6450e" class="el">HContainerProperty</a>. |

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
<td class="md" data-nowrap="" data-valign="top">static <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a>* HCategoryProperty::New</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Reimplemented from <a href="classHContainerProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">HContainerProperty</a>.</p>
<p>Reimplemented in <a href="classHUserCategoryProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">HUserCategoryProperty</a>, <a href="classHBoolCategoryProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">HBoolCategoryProperty</a>, and <a href="classHTypeCategoryProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">HTypeCategoryProperty</a>.</p></td>
</tr>
</tbody>
</table>

<span id="19cf720234d097ca5370f2873133e7cc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HCategoryProperty::RemoveProperty</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>property</em></td>
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
<td><p>Removes the property from a properties group.</p>
<p>It is the responsibility of the programmer to remove the property from the group before deleting it.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>property</em> </td>
<td>- The property to delete.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
TRUE if the property could be removed.
</dd>
</dl>
Example:
<div class="fragment">
<pre class="fragment"><code>   m_options-&gt;RemoveProperty(m_ampl);
   delete m_ampl;</code></pre>
</div></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropert_8h-source.md" class="el">HPropert.h</a>
- C:/Dox/SDK/Comments/<a href="Property_8dox.md" class="el">Property.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:54 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
