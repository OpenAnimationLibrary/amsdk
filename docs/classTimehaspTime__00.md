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

# TimehaspTime Class Reference

`#include <`<a href="Timehasp_8h-source.md" class="el"><code>Timehasp.h</code></a>`>`

[List of all members.](classTimehaspTime-members.md)

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
<td class="memItemRight" data-valign="bottom">{ <a href="classTimehaspTime.md#68986ab776eb5d6b5a809a1c005a73007a1920d61156abc05a60135aefe8bc67" class="el">Default</a> = -1, <a href="classTimehaspTime.md#68986ab776eb5d6b5a809a1c005a73001e1cc9bdeb2f29f5480106aec7e9bc48" class="el">Now</a> = 0 }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#ee8ab37654f58f721b58c99b9e36c6bc" class="el">TimehaspTime</a> (time_t aTime=Default)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#f534455bc7165a6b0ecbdbe3eff33f64" class="el">TimehaspTime</a> (int hh, int mm, int ss)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">bool </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#831461f04850a88060322f4a164f9ccc" class="el">Valid</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#01d115e51bbaea3b3e3da4cf9b19a0f3" class="el">Hour</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#4226fb142287e8176ded46c46e03d166" class="el">Minute</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#709e822be0a67b1249f77ca7be032175" class="el">Second</a> () const</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#f3f16eb5859d3bf642e6beb88534d012" class="el">Init</a> (time_t aTime)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#cf4d8c64ad8cdffbd356d922be6908aa" class="el">Check</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#896c55cc5e46fab38ce9f51ebf7bfcd3" class="el">hour</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#0a7d55be9d12a369a6a8da0fb517fba4" class="el">minute</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#a9f0e61a137d86aa9db53465e0801612" class="el">second</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">bool </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#9f7d0ee82b6a6ca7ddeae841f3253059" class="el">valid</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md#c811d5b2d6a2a0dc95dd04a1e438ae93" class="el">TimeHasp</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

