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

# HSpline Class Reference

The HSpline class represents the spline curves that contain HCPs and that are stitched together to make the patch based models. [More...](#_details)

`#include <`<a href="HPatch_8h-source.md" class="el"><code>HPatch.h</code></a>`>`

Inheritance diagram for HSpline:

<span class="image placeholder" original-image-src="classHSpline__inherit__graph.gif" original-image-title="" border="0" usemap="#HSpline__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HSpline:

<span class="image placeholder" original-image-src="classHSpline__coll__graph.gif" original-image-title="" border="0" usemap="#HSpline__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHSpline-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#d55b4a9828c87389479aeeea3f625fde" class="el">GetHeadCP</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#d638e82fae03cc73eaeb2c9dbf8a4924" class="el">GetNextSpline</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#7bd5373fa4f52b6bda07da2c856726f6" class="el">CreateCPAtHead</a> (const <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#b599fca54be6c93e9b2fe2aa1f40fd0e" class="el">CreateCPAtTail</a> (const <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#6a1920a906967f5ac97b8a3c238de8c5" class="el">CreateCPBefore</a> (<a href="classHCP.md" class="el">HCP</a> *beforecp, const <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#a0a4b50715c542004fc6435d77305f0c" class="el">CreateCPAfter</a> (<a href="classHCP.md" class="el">HCP</a> *aftercp, const <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#b6a361434a2d7163a6b467370d21db94" class="el">DeleteCP</a> (<a href="classHCP.md" class="el">HCP</a> *cp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#0b59a0b77ff12ca23290e23fc9726e08" class="el">MakeLooped</a> (BOOL looped)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#b2a90b0840ba0f087728d89d27353935" class="el">operator delete</a> (void *ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#0670dbd645d0e24b7f8f78d5c15d6aca" class="el">GetLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#4e95473761f6d1b3a69e5c3063899862" class="el">GetPositionAndDirection</a> (float ease, <a href="classVector.md" class="el">Vector</a> &amp;position, <a href="classVector.md" class="el">Vector</a> &amp;direction)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHSpline.md#f477a35df122a79dd95580efabfbcd99" class="el">DeleteHandle</a> (<a href="classHSpline.md" class="el">HSpline</a> *handle)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

