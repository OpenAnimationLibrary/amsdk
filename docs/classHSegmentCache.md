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

# HSegmentCache Class Reference

HSegmentCaches are bones that control Control Points. [More...](#_details)

`#include <`<a href="HSegment_8h-source.md" class="el"><code>HSegment.h</code></a>`>`

Inheritance diagram for HSegmentCache:

<span class="image placeholder" original-image-src="classHSegmentCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HSegmentCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HSegmentCache:

<span class="image placeholder" original-image-src="classHSegmentCache__coll__graph.gif" original-image-title="" border="0" usemap="#HSegmentCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHSegmentCache-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSegmentCache.md#c314047344d073e2c79b1a793cc06ed9" class="el">OnDelete</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSegmentCache.md#c5ab1a675bc8ff99dc2854bb711c653d" class="el">GetBoolCutter</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSegmentCache.md#543cdcb8eb32d17eee3ea3942412c7cb" class="el">GetGroupCP</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Group of cps this bone owns. <a href="#543cdcb8eb32d17eee3ea3942412c7cb"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSegmentCache.md#448c3e85ba706a917d04294f66f8f17f" class="el">IsBooleanCutter</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSegmentCache.md#fb17b78a192147b44af728b9e32ed054" class="el">AquireCP</a> (<a href="classHCP.md" class="el">HCP</a> *cp)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHSegmentCache.md" class="el">HSegmentCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSegmentCache.md#8f09d830f6964929b9b2b5681b7f5b8a" class="el">New</a> (const char *name=NULL)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

HSegmentCaches are bones that control Control Points.

Definition at line <a href="HSegment_8h-source.md#l00019" class="el">19</a> of file <a href="HSegment_8h-source.md" class="el">HSegment.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="fb17b78a192147b44af728b9e32ed054" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HSegmentCache::AquireCP</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>cp</em></td>
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
<td><p>Assigns a CP to a Bone, exactly what you do in Bones mode in a the modeler. Will create a <a href="classHGroupCP.md" class="el">HGroupCP</a> in the HSegmentCache if it doesn't exist and add the <a href="classHCP.md" class="el">HCP</a> to it if the <a href="classHGroup.md" class="el">HGroup</a> already exists.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>cp</em> </td>
<td>- The CP that is assigned to the bone.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
FALSE if the allocation failed. TRUE otherwise.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="c5ab1a675bc8ff99dc2854bb711c653d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a>* HSegmentCache::GetBoolCutter</td>
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

<span id="543cdcb8eb32d17eee3ea3942412c7cb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * HSegmentCache::GetGroupCP</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Group of cps this bone owns.</p>
<p>Retrieves the <a href="classHGroupCP.md" class="el">HGroupCP</a> that includes all the CPs that are controlled by the HSegmentCache.</p></td>
</tr>
</tbody>
</table>

<span id="448c3e85ba706a917d04294f66f8f17f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HSegmentCache::IsBooleanCutter</td>
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

|     |                                                           |
|-----|-----------------------------------------------------------|
|     | Use GetBoolCutter now, this is for backward compatibility |

<span id="8f09d830f6964929b9b2b5681b7f5b8a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHSegmentCache.md" class="el">HSegmentCache</a>* HSegmentCache::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const char * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>name</em> = <code>NULL</code></td>
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

<span id="c314047344d073e2c79b1a793cc06ed9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HSegmentCache::OnDelete</td>
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

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HSegment_8h-source.md" class="el">HSegment.h</a>
- C:/Dox/SDK/Comments/<a href="Bones_8dox.md" class="el">Bones.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:57 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
