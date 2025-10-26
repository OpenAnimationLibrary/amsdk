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

# TimeHasp Class Reference

`#include <`<a href="Timehasp_8h-source.md" class="el"><code>Timehasp.h</code></a>`>`

[List of all members.](classTimeHasp-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef unsigned char </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#7b9cd50a2309eafad4d4f64938ea07d0" class="el">MemoType</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#cd67882e4c6bea3b7b1287c9d703874e" class="el">TimeHasp</a> (LocalHaspImp *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#ca1460062945c4b977dd23aa4129ad57" class="el">TimeHasp</a> (unsigned int pass1, unsigned int pass2, HaspErrorProc handler=0, unsigned int lptnum=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#70bca494cacbe176263a69f6492fa30a" class="el">~TimeHasp</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#a6fe5c9e6470f24f670ae8e2f55033fa" class="el">Accept</a> (HaspApplicator &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#2884cb68a429ef45551a15c5bc6817d1" class="el">GetTime</a> (<a href="classTimehaspTime.md" class="el">TimehaspTime</a> &amp;<a href="classTime.md" class="el">Time</a>) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#8b6aa366cb5a88b3d5a21b8391b2ec93" class="el">SetTime</a> (const <a href="classTimehaspTime.md" class="el">TimehaspTime</a> &amp;<a href="classTime.md" class="el">Time</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#4bcfa181f134dab3f37fd3938553f3bd" class="el">GetDate</a> (<a href="classTimehaspDate.md" class="el">TimehaspDate</a> &amp;Date) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#2759d3d07e0a6a4684bdc5ac5f6c34fa" class="el">SetDate</a> (const <a href="classTimehaspDate.md" class="el">TimehaspDate</a> &amp;Date)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#b9531dae3697e0869d3d5955c9551e00" class="el">TimeHasp</a> (const <a href="classTimeHasp.md" class="el">TimeHasp</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeHasp.md" class="el">TimeHasp</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#8edd3dbd023aa6310e9d87d5c36178e4" class="el">operator=</a> (const <a href="classTimeHasp.md" class="el">TimeHasp</a> &amp;rhs)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md#43ac1760a7417ff9c685f44987518f9d" class="el">MemohaspConverter</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

