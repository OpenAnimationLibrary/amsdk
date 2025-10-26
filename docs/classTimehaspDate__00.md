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

# TimehaspDate Class Reference

`#include <`<a href="Timehasp_8h-source.md" class="el"><code>Timehasp.h</code></a>`>`

[List of all members.](classTimehaspDate-members.md)

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
<td class="memItemRight" data-valign="bottom">{ <a href="classTimehaspDate.md#dca29a1140aadadfd92b34a02fa516ef7a1920d61156abc05a60135aefe8bc67" class="el">Default</a> = -1, <a href="classTimehaspDate.md#dca29a1140aadadfd92b34a02fa516ef1dd1c5fb7f25cd41b291d43a89e3aefd" class="el">Today</a> = 0 }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#737a3ecd3da1334a5b74c60b349c57c5" class="el">TimehaspDate</a> (time_t aTime=Default)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#9ea90af10154b495b828b9ce80e2fb3a" class="el">TimehaspDate</a> (<a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d" class="el">THMonth</a> mm, <a href="Timehasp_8h.md#834a8a3407d572b6106767f26cd29098" class="el">THDay</a> dd, <a href="Timehasp_8h.md#30ac26c81bc9e5b7d6aafbcd82a211ab" class="el">THYear</a> yy)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">bool </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#831461f04850a88060322f4a164f9ccc" class="el">Valid</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#967d459ed59914ebfeb9974ed8af2fba" class="el">Month</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#1a9fc36ce82c383f9f68da128d05602b" class="el">Day</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#e197b36edfa7c572ff51313526e4ff64" class="el">Year</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#a93847d1eeecf1c738ff22ce44bc3ab9" class="el">APIYear</a> () const</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#f3f16eb5859d3bf642e6beb88534d012" class="el">Init</a> (time_t aTime)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#cf4d8c64ad8cdffbd356d922be6908aa" class="el">Check</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#7436f942d5ea836cb84f1bb2527d8286" class="el">month</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#628b7db04235f228d40adc671413a8c8" class="el">day</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#84cdc76cabf41bd7c961f6ab12f117d8" class="el">year</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">bool </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#9f7d0ee82b6a6ca7ddeae841f3253059" class="el">valid</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md#c811d5b2d6a2a0dc95dd04a1e438ae93" class="el">TimeHasp</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

