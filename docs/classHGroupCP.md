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

# HGroupCP Class Reference

HGroupCP are used to link control points in a group. [More...](#_details)

`#include <`<a href="HCP_8h-source.md" class="el"><code>HCP.h</code></a>`>`

Inheritance diagram for HGroupCP:

<span class="image placeholder" original-image-src="classHGroupCP__inherit__graph.gif" original-image-title="" border="0" usemap="#HGroupCP__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HGroupCP:

<span class="image placeholder" original-image-src="classHGroupCP__coll__graph.gif" original-image-title="" border="0" usemap="#HGroupCP__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHGroupCP-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroupCP.md#0d4ba4036cc2dcca8c73cdde356797cd" class="el">GetNext</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Returns a pointer to the next HGroupCP in the group. <a href="#0d4ba4036cc2dcca8c73cdde356797cd"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroupCP.md#4019bddef6ba94389b5716cb4bbac192" class="el">GetCP</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Returns a pointer to the <a href="classHCP.md" class="el">HCP</a> associated with this HGroupCP. <a href="#4019bddef6ba94389b5716cb4bbac192"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroupCP.md#51a833214dab53bfafb630573fc0fe77" class="el">Delete</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Destroys the HGroupCP and frees memory. <a href="#51a833214dab53bfafb630573fc0fe77"></a><br />
</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHGroupCP.md" class="el">HGroupCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroupCP.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Allocates and returns a pointer to a new HGroupCP. <a href="#3d9cbd41ce5e98d53ee169d9547259d7"></a><br />
</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

HGroupCP are used to link control points in a group.

HGroupCP is nothing more than a <a href="classHCP.md" class="el">HCP</a> with a next pointer, that is used to chain multiple CP's together in a linked list from a <a href="classHGroup.md" class="el">HGroup</a>. HGroupCP are essentially pointers that link together this control point to another control point. The control points may be from different splines.

**See also:**  
<a href="classHCP.md" class="el">HCP</a> and <a href="classHGroup.md" class="el">HGroup</a>

Definition at line <a href="HCP_8h-source.md#l00126" class="el">126</a> of file <a href="HCP_8h-source.md" class="el">HCP.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="51a833214dab53bfafb630573fc0fe77" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HGroupCP::Delete</td>
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

|     |                                         |
|-----|-----------------------------------------|
|     | Destroys the HGroupCP and frees memory. |

<span id="4019bddef6ba94389b5716cb4bbac192" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HGroupCP::GetCP</td>
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
<td><p>Returns a pointer to the <a href="classHCP.md" class="el">HCP</a> associated with this HGroupCP.</p>
<p>The <a href="classHCP.md" class="el">HCP</a> is set when you call <a href="classHCP.md#015a91031ac055cf5271eb6fdbc81a32" class="el">HCP::AddToGroup(HGroupCP **group)</a>.</p></td>
</tr>
</tbody>
</table>

<span id="0d4ba4036cc2dcca8c73cdde356797cd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * HGroupCP::GetNext</td>
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
<td><p>Returns a pointer to the next HGroupCP in the group.</p>
<p>Returns NULL when it reaches the end of the group.</p>
<p>You can get the <a href="classHCP.md" class="el">HCP</a> by calling <a href="classHGroupCP.md#4019bddef6ba94389b5716cb4bbac192" class="el">GetCP()</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * HGroupCP::New</td>
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

|     |                                                    |
|-----|----------------------------------------------------|
|     | Allocates and returns a pointer to a new HGroupCP. |

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HCP_8h-source.md" class="el">HCP.h</a>
- C:/Dox/SDK/Comments/<a href="HCP_8dox.md" class="el">HCP.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
