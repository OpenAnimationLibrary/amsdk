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

# HDataProperty Class Reference

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HDataProperty:

<span class="image placeholder" original-image-src="classHDataProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HDataProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HDataProperty:

<span class="image placeholder" original-image-src="classHDataProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HDataProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHDataProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#327efd5d9ea06c9066f84f20ca5ae0fe" class="el">GetValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classDataValue.md" class="el">DataValue</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#a4b7d04c245a3f84126b7157f269b819" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#7733b9d3a4646b2ccc31f9168c04a7a0" class="el">SetValue</a> (const <a href="classDataValue.md" class="el">DataValue</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#e9413c4f8a18cdea15bb61065f2f6d05" class="el">StoreValue</a> (const <a href="classDataValue.md" class="el">DataValue</a> &amp;value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#e02606dcd4b6afd5d3d704d2e2fdff92" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classDataValue.md" class="el">DataValue</a> &amp;value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHDataProperty.md" class="el">HDataProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHDataProperty.md" class="el">HDataProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDataProperty.md#859474888945fe4f540e0f407c2eb995" class="el">New</a> (<a href="classHDataPropertyInfo.md" class="el">HDataPropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="HPropert_8h-source.md#l01088" class="el">1088</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="a4b7d04c245a3f84126b7157f269b819" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classDataValue.md" class="el">DataValue</a> HDataProperty::GetValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>time</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const</td>
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
<td class="md" data-nowrap="" data-valign="top">const <a href="classDataValue.md" class="el">DataValue</a>&amp; HDataProperty::GetValue</td>
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

|     |     |
|-----|-----|
|     |     |

<span id="859474888945fe4f540e0f407c2eb995" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHDataProperty.md" class="el">HDataProperty</a>* HDataProperty::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHDataPropertyInfo.md" class="el">HDataPropertyInfo</a> * </td>
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
<td class="md" data-nowrap="" data-valign="top">static <a href="classHDataProperty.md" class="el">HDataProperty</a>* HDataProperty::New</td>
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

<span id="7733b9d3a4646b2ccc31f9168c04a7a0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HDataProperty::SetValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>value</em></td>
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

<span id="e02606dcd4b6afd5d3d704d2e2fdff92" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HDataProperty::StoreValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname" data-nowrap=""><em>time</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
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

<span id="e9413c4f8a18cdea15bb61065f2f6d05" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HDataProperty::StoreValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
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

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropert_8h-source.md" class="el">HPropert.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
