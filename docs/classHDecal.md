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

# HDecal Class Reference

One decal in a "Decals" folder. [More...](#_details)

`#include <`<a href="HDecal_8h-source.md" class="el"><code>HDecal.h</code></a>`>`

Inheritance diagram for HDecal:

<span class="image placeholder" original-image-src="classHDecal__inherit__graph.gif" original-image-title="" border="0" usemap="#HDecal__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HDecal:

<span class="image placeholder" original-image-src="classHDecal__coll__graph.gif" original-image-title="" border="0" usemap="#HDecal__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHDecal-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalClip.md" class="el">HDecalClip</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDecal.md#6a8ed899a7468e1a246fe412ff261be4" class="el">AddDecalClip</a> (<a href="classHClip.md" class="el">HClip</a> *clipcache=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalStamp.md" class="el">HDecalStamp</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDecal.md#8fd28333de657c11493d8f7a3a1d2996" class="el">AddDecalStamp</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalClipContainer.md" class="el">HDecalClipContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDecal.md#c0573b3e1e96aa5e6275d0da484f86bf" class="el">GetChildDecalClipContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalStampContainer.md" class="el">HDecalStampContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHDecal.md#ca675030347e63b69583c1e35ea8b2c2" class="el">GetChildDecalStampContainer</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

One decal in a "Decals" folder.

This is the class which is represented by one particular decal as child of the "Decals" folder in the PWS. A HDecal may be one of many childrens of <a href="classHDecalContainer.md" class="el">HDecalContainer</a>. And a HDecal have two children: one <a href="classHDecalClipContainer.md" class="el">HDecalClipContainer</a> and one <a href="classHDecalStampContainer.md" class="el">HDecalStampContainer</a>.

<div align="center">

<span class="image placeholder" original-image-src="DecalClasses.jpg" original-image-title="">DecalClasses.jpg</span>

**Class relationships for decals**

</div>

**See also:**  
<a href="classHDecalContainer.md" class="el">HDecalContainer</a>, <a href="classHDecalClipContainer.md" class="el">HDecalClipContainer</a>, <a href="classHDecalStampContainer.md" class="el">HDecalStampContainer</a>.

Definition at line <a href="HDecal_8h-source.md#l00119" class="el">119</a> of file <a href="HDecal_8h-source.md" class="el">HDecal.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="6a8ed899a7468e1a246fe412ff261be4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHDecalClip.md" class="el">HDecalClip</a> * HDecal::AddDecalClip</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHClip.md" class="el">HClip</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>clipcache</em> = <code>NULL</code></td>
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
|   | Adds a Image to the Decal; Will create the " Images" folder if it doesn't exist. |

<span id="8fd28333de657c11493d8f7a3a1d2996" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHDecalStamp.md" class="el">HDecalStamp</a> * HDecal::AddDecalStamp</td>
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
|   | Adds a Stamp to the Decal; Will create the "Stamps" folder if it doesn't exist. |

<span id="c0573b3e1e96aa5e6275d0da484f86bf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHDecalClipContainer.md" class="el">HDecalClipContainer</a>* HDecal::GetChildDecalClipContainer</td>
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

<span id="ca675030347e63b69583c1e35ea8b2c2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHDecalStampContainer.md" class="el">HDecalStampContainer</a>* HDecal::GetChildDecalStampContainer</td>
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

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HDecal_8h-source.md" class="el">HDecal.h</a>
- C:/Dox/SDK/Comments/<a href="Decals_8dox.md" class="el">Decals.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
