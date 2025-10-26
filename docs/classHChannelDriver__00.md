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

# HChannelDriver Class Reference

`#include <`<a href="HPropDri_8h-source.md" class="el"><code>HPropDri.h</code></a>`>`

Inheritance diagram for HChannelDriver:

<span class="image placeholder" original-image-src="classHChannelDriver__inherit__graph.gif" original-image-title="" border="0" usemap="#HChannelDriver__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HChannelDriver:

<span class="image placeholder" original-image-src="classHChannelDriver__coll__graph.gif" original-image-title="" border="0" usemap="#HChannelDriver__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHChannelDriver-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e8236" class="el">CPInterpolationMethod</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#3a9524907fd7628a15178f0ecc351cfa" class="el">GetInterpolationMethod</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#108ad82cc69c9fe4558afd7e297d69b9" class="el">SetInterpolationMethod</a> (<a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e8236" class="el">CPInterpolationMethod</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af" class="el">ExtrapolationMethod</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#2546c3cf7996bef7910f43f2daf780ad" class="el">GetPreExtrapolationMethod</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#a6028cb528dc72f4429c6ed014dd247e" class="el">SetPreExtrapolationMethod</a> (<a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af" class="el">ExtrapolationMethod</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af" class="el">ExtrapolationMethod</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#fc051bbb8493eaef2d686f27ee6bc3f6" class="el">GetPostExtrapolationMethod</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#6ab909369333e14ff190fd10de303fd2" class="el">SetPostExtrapolationMethod</a> (<a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af" class="el">ExtrapolationMethod</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChannelCP.md" class="el">HChannelCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#d55b4a9828c87389479aeeea3f625fde" class="el">GetHeadCP</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChannelCP.md" class="el">HChannelCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#f0b119d66ac943c0b4d99cf2b3c25a30" class="el">GetTailCP</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChannelCP.md" class="el">HChannelCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#d25322fe3bd5c37b8f80dfe660042b4a" class="el">GetCPFromTime</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#560ff5f17fa01e025d92664c298c865b" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time, <a href="classTimeRange.md" class="el">TimeRange</a> *validrange=NULL)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHChannelDriver.md" class="el">HChannelDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHChannelDriver.md#a2620be04bc6a915b93a20e51f6567d2" class="el">New</a> (<a href="classHProperty.md" class="el">HProperty</a> *parent)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

