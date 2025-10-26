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

# HFloatPropertyInfo Class Reference

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HFloatPropertyInfo:

<span class="image placeholder" original-image-src="classHFloatPropertyInfo__inherit__graph.gif" original-image-title="" border="0" usemap="#HFloatPropertyInfo__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HFloatPropertyInfo:

<span class="image placeholder" original-image-src="classHFloatPropertyInfo__coll__graph.gif" original-image-title="" border="0" usemap="#HFloatPropertyInfo__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHFloatPropertyInfo-members.md)

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
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef18ee54cba4157c7a889331972efa6b59" class="el">FF_X</a> = 0x0001, <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef52e0e6c61ce913c1be9bc37be1b72832" class="el">FF_Y</a> = 0x0002, <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef2cc0694357b15cfd75220b9f18ebf93b" class="el">FF_Z</a> = 0x0003, <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef205e9cb46493d134b46ade47288f1c39" class="el">FF_RED</a> = 0x0008,<br />
  <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef74f99654881aa8016d42bb4b7d78e739" class="el">FF_GREEN</a> = 0x0010, <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef31eba9fb32d8a68c1100fe5dd3c1ebde" class="el">FF_BLUE</a> = 0x0020, <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516ef25bff532ba2726e30bb26ade838ce290" class="el">FF_UNIT</a> = 0x0040, <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516efda52cd52769e85004b08a1b55a9716aa" class="el">FF_PERCENTAGE</a> = 0x0080,<br />
  <a href="classHFloatPropertyInfo.md#dca29a1140aadadfd92b34a02fa516efcdffd157ddfcd1f0137344f0fabdb75d" class="el">FF_ANGLE</a> = 0x0100<br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#ad4ed5c613e233cf465b8feac67f63d3" class="el">SetFactorValue</a> (float val)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#9bbc9a5719a2828567edcf0e858040d9" class="el">SetModulo</a> (float modulo)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#7fb6889b5144ffe0d6f8d0fa797bf0fc" class="el">SetDefaultValue</a> (float val)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#ae6c0e2d2e6224c00fb2daa4190ea1bc" class="el">SetMinValue</a> (float val)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#e0937695d7268eff8cc0f6b202e5d059" class="el">SetMaxValue</a> (float val)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#f217ff34efa649b563bc05baa0ffcc00" class="el">SetFlags</a> (UINT <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#15e0e825580a0ea151a9751dd66c41eb" class="el">GetFactorValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#1c6b0608d991369c384116941cfeef02" class="el">GetDefaultValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#1ff70527b9e3080ca1a2fe4d0ed8e1cc" class="el">GetMinValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#e0691420ad2333a6cb7c6e81275d29f5" class="el">GetMaxValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#938d6993463175b4205567095f135bbc" class="el">GetFlags</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#ec3967e3fc4d1592452e91dcf9092235" class="el">SetDisplayInPoseSlider</a> (BOOL show)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#ccba75d43edf111d6b33591f3b1c1814" class="el">GetDisplayInPoseSlider</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHFloatPropertyInfo.md" class="el">HFloatPropertyInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHFloatPropertyInfo.md#3184c8fe6d6f9a3b2284ddcadfd1424f" class="el">New</a> (const char *localizedname, const char *matchname)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

