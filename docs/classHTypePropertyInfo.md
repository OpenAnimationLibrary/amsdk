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

# HTypePropertyInfo Class Reference

Contains the UI information that is used to display a drop-down list in a property panel. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HTypePropertyInfo:

<span class="image placeholder" original-image-src="classHTypePropertyInfo__inherit__graph.gif" original-image-title="" border="0" usemap="#HTypePropertyInfo__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HTypePropertyInfo:

<span class="image placeholder" original-image-src="classHTypePropertyInfo__coll__graph.gif" original-image-title="" border="0" usemap="#HTypePropertyInfo__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHTypePropertyInfo-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypePropertyInfo.md#4eb18dc5ccc83d499cee5f4a2b91a068" class="el">SetDefaultIndex</a> (UINT index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypePropertyInfo.md#f9709d7eb0070af37c7bd907b29c8ab9" class="el">GetDefaultIndex</a> () const</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTypePropertyInfo.md#7a0161121f59aa7875878d2e0d61f0f8" class="el">New</a> (const char *localizedname, const char *matchname, <a href="classTypeInfoArray.md" class="el">TypeInfoArray</a> *typeinfoarray)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Contains the UI information that is used to display a drop-down list in a property panel.

This class would normally be used with <a href="classHTypeProperty.md" class="el">HTypeProperty</a>.

**See also:**  
<a href="classHTypeProperty.md" class="el">HTypeProperty</a>

Definition at line <a href="HPropert_8h-source.md#l00700" class="el">700</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="f9709d7eb0070af37c7bd907b29c8ab9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">UINT HTypePropertyInfo::GetDefaultIndex</td>
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

<span id="7a0161121f59aa7875878d2e0d61f0f8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTypePropertyInfo.md" class="el">HTypePropertyInfo</a> * HTypePropertyInfo::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const char * </td>
<td class="mdname" data-nowrap=""><em>localizedname</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const char * </td>
<td class="mdname" data-nowrap=""><em>matchname</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTypeInfoArray.md" class="el">TypeInfoArray</a> * </td>
<td class="mdname" data-nowrap=""><em>typeinfoarray</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [static]</code></td>
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
<td><p>Creates a new HTypePropertyInfo UI for a new drop-down list.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>localizedname</em> </td>
<td>- <a href="classString.md" class="el">String</a> of text used to name the property as it will appear on the left column of the property panel in the PWS.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>matchname</em> </td>
<td>- <a href="classString.md" class="el">String</a> used in the saved A:M file as a tag to identify and retrieve the saved property value.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>typeinfoarray</em> </td>
<td>- The actual array of <a href="classHTypeInfo.md" class="el">HTypeInfo</a> that holds all the choices available in the drop-down list.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPropertyInfo.md#bdacc650d76c0dae25171fcd41afc353" class="el">HPropertyInfo::SetLocalizedName</a> and <a href="classHPropertyInfo.md#a76daf6ed0e6a62af293abac832e595f" class="el">HPropertyInfo::SetMatchName</a> for more informations about localized names and match names.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="4eb18dc5ccc83d499cee5f4a2b91a068" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HTypePropertyInfo::SetDefaultIndex</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>index</em></td>
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

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropert_8h-source.md" class="el">HPropert.h</a>
- C:/Dox/SDK/Comments/<a href="Property_8dox.md" class="el">Property.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:58 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
