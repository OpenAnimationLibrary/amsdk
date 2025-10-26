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

# HCameraCache Class Reference

`#include <`<a href="HCamera_8h-source.md" class="el"><code>HCamera.h</code></a>`>`

Inheritance diagram for HCameraCache:

<span class="image placeholder" original-image-src="classHCameraCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HCameraCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HCameraCache:

<span class="image placeholder" original-image-src="classHCameraCache__coll__graph.gif" original-image-title="" border="0" usemap="#HCameraCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHCameraCache-members.md)

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
&#10;<h2 id="public-types">Public Types</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCameraCache.md#ad4273093aee1f495514870f521f23ac" class="el">CAMERATYPE</a> { <a href="classHCameraCache.md#ad4273093aee1f495514870f521f23acee04d2e6467189130c405e01fd51df64" class="el">CT_ORTHOGONAL</a>, <a href="classHCameraCache.md#ad4273093aee1f495514870f521f23acdd2b5111ed3698312869b5377dd92435" class="el">CT_PERSPECTIVE</a>, <a href="classHCameraCache.md#ad4273093aee1f495514870f521f23ac0650a082911453069fcf3bcecea0b8bf" class="el">CT_GAME</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCameraCache.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCameraCache.md#78189a4474ebe8c0454c3423e9e9a870" class="el">GetBackGroundColor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCameraCache.md#2abb3adc07fed2a2970fe92e67ff13c6" class="el">GetFocalLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCameraCache.md#66e2a92b6086edbecbfdda573e09b52d" class="el">GetFocalDistance</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHCameraCache.md#aa4622111fe0a9e9bd2e1f57649cc292" class="el">GetGlobalAmbiance</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="HCamera_8h-source.md#l00014" class="el">14</a> of file <a href="HCamera_8h-source.md" class="el">HCamera.h</a>.

------------------------------------------------------------------------

## Member Enumeration Documentation

<span id="ad4273093aee1f495514870f521f23ac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="classHCameraCache.md#ad4273093aee1f495514870f521f23ac" class="el">HCameraCache::CAMERATYPE</a></td>
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
<dt><strong>Enumerator:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"><em><span id="ad4273093aee1f495514870f521f23acee04d2e6467189130c405e01fd51df64" class="anchor"></span>CT_ORTHOGONAL</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="ad4273093aee1f495514870f521f23acdd2b5111ed3698312869b5377dd92435" class="anchor"></span>CT_PERSPECTIVE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="ad4273093aee1f495514870f521f23ac0650a082911453069fcf3bcecea0b8bf" class="anchor"></span>CT_GAME</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="HCamera_8h-source.md#l00017" class="el">17</a> of file <a href="HCamera_8h-source.md" class="el">HCamera.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Function Documentation

<span id="78189a4474ebe8c0454c3423e9e9a870" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHColorProperty.md" class="el">HColorProperty</a>* HCameraCache::GetBackGroundColor</td>
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

<span id="66e2a92b6086edbecbfdda573e09b52d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a>* HCameraCache::GetFocalDistance</td>
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

<span id="2abb3adc07fed2a2970fe92e67ff13c6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a>* HCameraCache::GetFocalLength</td>
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

<span id="aa4622111fe0a9e9bd2e1f57649cc292" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a>* HCameraCache::GetGlobalAmbiance</td>
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

<span id="97bbe45df6b2b139c951f179d5dc83b8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTypeProperty.md" class="el">HTypeProperty</a>* HCameraCache::GetType</td>
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
|   | Reimplemented from <a href="classHTreeObject.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">HTreeObject</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HCamera_8h-source.md" class="el">HCamera.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:54 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
