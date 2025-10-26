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

# CPXComPort Class Reference

`#include <`<a href="ComPort_8h-source.md" class="el"><code>ComPort.h</code></a>`>`

[List of all members.](classCPXComPort-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#aa8ae2b641404c7a223237107b04ec6c" class="el">CPXComPort</a> (int port=1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#f4e4470e338a45e5146bf67f714bdaa9" class="el">~CPXComPort</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#6fd2bd4202480b375600cbdf8f5eb098" class="el">UserConfigure</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#5bb80ba7d65cbb039f251e69ad764467" class="el">Configure</a> (DCB *dcb)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#721e7a23f41e0c0c69a63827db9f8780" class="el">CloseConnection</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#14393b1e44e374a685b68cd4f9701d98" class="el">OpenConnection</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#e42761236c794499f6bb7243eb370f3e" class="el">SendBuffer</a> (LPCTSTR buffer, DWORD size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#70c13e647344498d583c7e8fd01e84bc" class="el">ReadBuffer</a> (LPCTSTR buffer, DWORD size)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#add83966748f35caad081ab7c9d33537" class="el">m_InSize</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#80b1fc72e879ba1efd588a2a99149cd5" class="el">m_OutSize</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">COMMTIMEOUTS </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#4d1a55c8a999035e5545f2ac54450711" class="el">m_TO</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">unsigned char </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#bdd471ae9af7d68bc5d9319338678b39" class="el">m_PortNum</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DCB </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#551fc36a55b99e56d27b61dd04f072be" class="el">m_DCB</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPXComPort.md#249b2893839a28cbec8846224a8ea477" class="el">m_hDev</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

