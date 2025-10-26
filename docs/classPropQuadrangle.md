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

# PropQuadrangle Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for PropQuadrangle:

<span class="image placeholder" original-image-src="classPropQuadrangle__inherit__graph.gif" original-image-title="" border="0" usemap="#PropQuadrangle__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for PropQuadrangle:

<span class="image placeholder" original-image-src="classPropQuadrangle__coll__graph.gif" original-image-title="" border="0" usemap="#PropQuadrangle__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classPropQuadrangle-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#97d88b5708e3a7dbd73f5ce6f9bea734" class="el">Bounds</a> (<a href="classVector.md" class="el">Vector</a> *vertexlist, <a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, ThreadInfo *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#baba436d04765f15dccba87a6a9a0b26" class="el">Collision</a> (ThreadInfo *, <a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">Normal</a> (<a href="classHit.md" class="el">Hit</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#ec21a530074d93e6d3c5883b04543a87" class="el">m_vertexid</a> [4]</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classPropQuadrangle.md#6b5ed913dc8f1aaa7311421ebabc6cb1" class="el">m_normalid</a> [4]</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="influenc_8h-source.md#l00058" class="el">58</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="97d88b5708e3a7dbd73f5ce6f9bea734" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void PropQuadrangle::Bounds</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="mdname" data-nowrap=""><em>vertexlist</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>min</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>max</em></td>
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

<span id="baba436d04765f15dccba87a6a9a0b26" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void PropQuadrangle::Collision</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">ThreadInfo * </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>min</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>max</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implements <a href="classQuadObject.md#c4fc0ecc7d5b33b72e07a25a9c9e8d4d" class="el">QuadObject</a>. |

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
<td class="md" data-nowrap="" data-valign="top">int PropQuadrangle::GetType</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
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
<td><p>Reimplemented from <a href="classQuadObject.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">QuadObject</a>.</p>
<p>Definition at line <a href="influenc_8h-source.md#l00067" class="el">67</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.</p>
<p>References <a href="RType_8h-source.md#l00033" class="el">PROPQUADRANGLE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ebc1dd006469e892a02410cbfdd1d3ec" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void PropQuadrangle::Intersect</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">ThreadInfo * </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implements <a href="classQuadObject.md#c3c898dc00647a45cf30e65c45723946" class="el">QuadObject</a>. |

<span id="8a11f22291743884b9331d9cb58e455e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void PropQuadrangle::Normal</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHit.md" class="el">Hit</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implements <a href="classQuadObject.md#d4db60536569ed9a39b2a82c7cba5024" class="el">QuadObject</a>. |

------------------------------------------------------------------------

## Member Data Documentation

<span id="6b5ed913dc8f1aaa7311421ebabc6cb1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classPropQuadrangle.md#6b5ed913dc8f1aaa7311421ebabc6cb1" class="el">PropQuadrangle::m_normalid</a>[4]</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="influenc_8h-source.md#l00060" class="el">60</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>. |

<span id="ec21a530074d93e6d3c5883b04543a87" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classPropQuadrangle.md#ec21a530074d93e6d3c5883b04543a87" class="el">PropQuadrangle::m_vertexid</a>[4]</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="influenc_8h-source.md#l00060" class="el">60</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="influenc_8h-source.md" class="el">influenc.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:01 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
