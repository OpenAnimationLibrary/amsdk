## Define Documentation

<span id="e90892939c61bf79f8f2894af07d1845" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define _NMMESSAGE_H_</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="nmmessage_8h-source.md#l00004" class="el">4</a> of file <a href="nmmessage_8h-source.md" class="el">nmmessage.h</a>. |

<span id="4d1ba9ce71b9b67a071fcc706c65c287" class="anchor"></span>

\#define CallNMMessageCallbackProc

( 

userRoutine,

h,

msg,

wParam,

lParam 

 ) 

   (\*(userRoutine))((h), (msg), (wParam), (lParam))

|  |  |
|----|----|
|   | Definition at line <a href="nmmessage_8h-source.md#l00048" class="el">48</a> of file <a href="nmmessage_8h-source.md" class="el">nmmessage.h</a>. |

<span id="7026e5e52982b91fcce9ffe4a27f7f86" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define NewNMMessageCallbackProc</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">userRoutine </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ((<a href="nmmessage_8h.md#1d5e0b7146d8d910b53fa3bdf2e18578" class="el">NMMessageCallbackProcPtr</a>) (userRoutine))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="nmmessage_8h-source.md#l00045" class="el">45</a> of file <a href="nmmessage_8h-source.md" class="el">nmmessage.h</a>. |

<span id="30bb5ac5cf28c93780575315bd6c49e3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define NM_INVALID_HANDLER   (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a>)(0)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="nmmessage_8h-source.md#l00016" class="el">16</a> of file <a href="nmmessage_8h-source.md" class="el">nmmessage.h</a>. |

------------------------------------------------------------------------

