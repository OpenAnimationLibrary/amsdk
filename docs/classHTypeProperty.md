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

# HTypeProperty Class Reference

Holds a value associated to a choice from a drop-down list. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HTypeProperty:

<span class="image placeholder" original-image-src="classHTypeProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HTypeProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HTypeProperty:

<span class="image placeholder" original-image-src="classHTypeProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HTypeProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHTypeProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md#327efd5d9ea06c9066f84f20ca5ae0fe" class="el">GetValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md#6e0d7bac16384f7ce07565211ecb103c" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md#fca95a2ea641471952f8cc68ec4f1f9f" class="el">SetValue</a> (UINT value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md#26366592b1d760b4b21c6311687801fa" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, UINT value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypeProperty.md#c6bd8097f77e4fb8ba2cb4df27c9d6a4" class="el">New</a> (<a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Holds a value associated to a choice from a drop-down list.

The actual drop-down list is a <a href="classTypeInfoArray.md" class="el">TypeInfoArray</a> stored in the associated <a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a>.

**See also:**  
<a href="classTypeInfoArray.md" class="el">TypeInfoArray</a> and <a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a>

Definition at line <a href="HPropert_8h-source.md#l00712" class="el">712</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="6e0d7bac16384f7ce07565211ecb103c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">UINT HTypeProperty::GetValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>time</em></td>
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

<span id="327efd5d9ea06c9066f84f20ca5ae0fe" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">UINT HTypeProperty::GetValue</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Retrieves the value corresponding to the current selection position (base 0) from a list of possible choices. |

<span id="c6bd8097f77e4fb8ba2cb4df27c9d6a4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * HTypeProperty::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>propinfo</em></td>
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
<td><p>Creates a new HTypeProperty</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>propinfo</em> </td>
<td>- the <a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a> that holds the actual drop-down list elements.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

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
<td class="md" data-nowrap="" data-valign="top">static <a href="classHTypeProperty.md" class="el">HTypeProperty</a>* HTypeProperty::New</td>
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

|     |     |
|-----|-----|
|     |     |

<span id="fca95a2ea641471952f8cc68ec4f1f9f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HTypeProperty::SetValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>value</em></td>
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
|   | Sets the value corresponding to the current selection position (base 0) in a list of possible choices. |

<span id="26366592b1d760b4b21c6311687801fa" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HTypeProperty::StoreValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname" data-nowrap=""><em>time</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>value</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>storeundo</em> = <code>TRUE</code></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
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
- C:/Dox/SDK/Comments/<a href="Property_8dox.md" class="el">Property.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:58 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
