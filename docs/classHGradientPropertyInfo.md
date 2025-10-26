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

# HGradientPropertyInfo Class Reference

Holds information about a gradient property. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HGradientPropertyInfo:

<span class="image placeholder" original-image-src="classHGradientPropertyInfo__inherit__graph.gif" original-image-title="" border="0" usemap="#HGradientPropertyInfo__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HGradientPropertyInfo:

<span class="image placeholder" original-image-src="classHGradientPropertyInfo__coll__graph.gif" original-image-title="" border="0" usemap="#HGradientPropertyInfo__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHGradientPropertyInfo-members.md)

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
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHGradientPropertyInfo.md" class="el">HGradientPropertyInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGradientPropertyInfo.md#3184c8fe6d6f9a3b2284ddcadfd1424f" class="el">New</a> (const char *localizedname, const char *matchname)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Holds information about a gradient property.

**Note:**  
The gradient file (.gra) will always have a \[GRADIENT\] header at the top, and has the following format for each key:

<div class="fragment">

``` fragment
GradientKey = type position r g b percent
```

</div>

**Parameters:**  
|  |  |  |
|----|----|----|
|  | *type*  | is either 0 or 1, which means a <a href="unionColor.md" class="el">Color</a> key or a Percentage key respectively. |
|  | *Position*  | is a percent along the gradient from 0.0 to 1.0. |
|  | *RGB*  | are the 0.0 to 1.0 color values when key is a color |
|  | *Percent*  | is the percentage when key is a percentage |

Definition at line <a href="HPropert_8h-source.md#l01052" class="el">1052</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="3184c8fe6d6f9a3b2284ddcadfd1424f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHGradientPropertyInfo.md" class="el">HGradientPropertyInfo</a>* HGradientPropertyInfo::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const char * </td>
<td class="mdname" data-nowrap=""><em>localizedname</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const char * </td>
<td class="mdname" data-nowrap=""><em>matchname</em></td>
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
<td><p>Creates a new <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> or any of its derived class UI slot in a property panel in the PWS.</p>
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
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPropertyInfo.md#bdacc650d76c0dae25171fcd41afc353" class="el">HPropertyInfo::SetLocalizedName</a> and <a href="classHPropertyInfo.md#a76daf6ed0e6a62af293abac832e595f" class="el">HPropertyInfo::SetMatchName</a>
</dd>
</dl>
<p>Reimplemented from <a href="classHPropertyInfo.md#3184c8fe6d6f9a3b2284ddcadfd1424f" class="el">HPropertyInfo</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropert_8h-source.md" class="el">HPropert.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
