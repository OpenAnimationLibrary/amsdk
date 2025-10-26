<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSAGETASYNCBUFLEN</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">luParam </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   LOWORD(luParam)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00878" class="el">878</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="9be53add599cc56c83a1320e7f3f38d4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSAGETASYNCERROR</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">luParam </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   HIWORD(luParam)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00884" class="el">884</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="358326fabe4fa4983d16e5212bbbd380" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSAGETSELECTERROR</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">luParam </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   HIWORD(luParam)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00896" class="el">896</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="dd69b4f9b6a564083ed7e16b3cf94cdf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSAGETSELECTEVENT</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">luParam </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   LOWORD(luParam)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00890" class="el">890</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="bba791e15808012bc99531a767db7727" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSAHOST_NOT_FOUND   (WSABASEERR+1001)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00659" class="el">659</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="08dd146effc1060c56447dac8327ebb2" class="anchor"></span>

\#define WSAMAKEASYNCREPLY

( 

buflen,

error 

 ) 

   MAKELONG(buflen,error)

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00867" class="el">867</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="a2e6dc7b6e118c8f10792af71a3dd92d" class="anchor"></span>

\#define WSAMAKESELECTREPLY

( 

event,

error 

 ) 

   MAKELONG(event,error)

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00872" class="el">872</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="f0a3687a0cb6da1bf12e426d4864de10" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSANO_ADDRESS   WSANO_DATA</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00675" class="el">675</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="fd5c2c6b04c1c302db1aa1901e8d497c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSANO_DATA   (WSABASEERR+1004)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00671" class="el">671</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="ca7f8361fd07467e21c919a9172dc8b6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSANO_RECOVERY   (WSABASEERR+1003)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00667" class="el">667</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="1030be5fc53317f506576a3dd434e75e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSANOTINITIALISED   (WSABASEERR+93)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00643" class="el">643</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="92355499662d70dd5d4e95e42ff30aaf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSASYS_STATUS_LEN   128</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00366" class="el">366</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="423024e1ce8f2534ea426c3b8b344395" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSASYSNOTREADY   (WSABASEERR+91)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00641" class="el">641</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="e2bd8b2faee29ea6887f86df183e7b39" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSATRY_AGAIN   (WSABASEERR+1002)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00663" class="el">663</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="e32bbf64e3c74c3a4c480944be30a0d7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define WSAVERNOTSUPPORTED   (WSABASEERR+92)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00642" class="el">642</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

------------------------------------------------------------------------

