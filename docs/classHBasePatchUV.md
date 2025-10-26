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

# HBasePatchUV Class Reference

a HBasePatchUV is a class which keeps the UV's for a <a href="classHPatch.md" class="el">HPatch</a> or <a href="classHPatch5.md" class="el">HPatch5</a> [More...](#_details)

`#include <`<a href="HDecal_8h-source.md" class="el"><code>HDecal.h</code></a>`>`

Inheritance diagram for HBasePatchUV:

<span class="image placeholder" original-image-src="classHBasePatchUV__inherit__graph.gif" original-image-title="" border="0" usemap="#HBasePatchUV__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HBasePatchUV:

<span class="image placeholder" original-image-src="classHBasePatchUV__coll__graph.gif" original-image-title="" border="0" usemap="#HBasePatchUV__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHBasePatchUV-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch.md" class="el">HPatch</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBasePatchUV.md#b0b2cf3e4910ff24532fc64a9ed73969" class="el">GetPatch</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBasePatchUV.md#4e840be527126b7b96107a26d73c45a4" class="el">IsPatch5UV</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBasePatchUV.md#c8fe811caf330775aac0583304563b34" class="el">SetUVs</a> (<a href="classVector2.md" class="el">Vector2</a> uvs[])</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBasePatchUV.md#24c574636417117e82b9509cc184af68" class="el">GetUVs</a> (<a href="classVector2.md" class="el">Vector2</a> uvs[])</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

a HBasePatchUV is a class which keeps the UV's for a <a href="classHPatch.md" class="el">HPatch</a> or <a href="classHPatch5.md" class="el">HPatch5</a>

From the HBasePatchUV you can retrieve the <a href="classHPatch.md" class="el">HPatch</a> class and the UV's for that patch. Now remember you are working with Patches not polygons so an <a href="classHPatch.md" class="el">HPatch</a> has 12 UV's and an <a href="classHPatch5.md" class="el">HPatch5</a> has 15 UV's as shown here.

<div align="center">

<span class="image placeholder" original-image-src="UV-points.gif" original-image-title="">UV-points.gif</span>

**UVs numbering**

</div>

Definition at line <a href="HDecal_8h-source.md#l00053" class="el">53</a> of file <a href="HDecal_8h-source.md" class="el">HDecal.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="b0b2cf3e4910ff24532fc64a9ed73969" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHPatch.md" class="el">HPatch</a> * HBasePatchUV::GetPatch</td>
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
|   | Returns the <a href="classHPatch.md" class="el">HPatch</a> or <a href="classHPatch5.md" class="el">HPatch5</a> |

<span id="24c574636417117e82b9509cc184af68" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HBasePatchUV::GetUVs</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector2.md" class="el">Vector2</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>uvs</em>[]</td>
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

<span id="4e840be527126b7b96107a26d73c45a4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HBasePatchUV::IsPatch5UV</td>
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

<span id="c8fe811caf330775aac0583304563b34" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HBasePatchUV::SetUVs</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector2.md" class="el">Vector2</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>uvs</em>[]</td>
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

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HDecal_8h-source.md" class="el">HDecal.h</a>
- C:/Dox/SDK/Comments/<a href="Decals_8dox.md" class="el">Decals.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:52 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
