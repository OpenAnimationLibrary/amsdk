## Define Documentation

<span id="a3281dba0c426d503ce29a429e02b63c" class="anchor"></span>

\#define \_IO

( 

x,

y 

 ) 

   (IOC_VOID\|(x\<\<8)\|y)

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00168" class="el">168</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="100fea1d7a14c57851ecf035f47a6cef" class="anchor"></span>

\#define \_IOR

( 

x,

y,

t 

 ) 

   (IOC_OUT\|(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>)sizeof(t)&IOCPARM_MASK)\<\<16)\|(x\<\<8)\|y)

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00170" class="el">170</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="77575278163d69413263c36c1c28573c" class="anchor"></span>

\#define \_IOW

( 

x,

y,

t 

 ) 

   (IOC_IN\|(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>)sizeof(t)&IOCPARM_MASK)\<\<16)\|(x\<\<8)\|y)

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00172" class="el">172</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="3d664e2b834ffc68a5c4d6247619b374" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_APPLETALK   16</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00492" class="el">492</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="ea36719eb14f49095507df32044a6d6b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_CCITT   10</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00486" class="el">486</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="d4273c73b386f83338a127ffa100910e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_CHAOS   5</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00480" class="el">480</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="74597f68ccee140984e0eab806dec85d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_DATAKIT   9</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00485" class="el">485</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="9264052b3a9dbc8e8504535a0d177808" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_DECnet   12</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00488" class="el">488</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="4e7b88de97100de2885f8e21e409fbb6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_DLI   13</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00489" class="el">489</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="13a85a0a646a6cd7babfcf69fbee715c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_ECMA   8</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00484" class="el">484</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="9aced386467dbeb64ac788509e57029d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_HYLINK   15</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00491" class="el">491</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="05365858ef359ad952114a82637968af" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_IMPLINK   3</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00478" class="el">478</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="5bc602efd98ee8b55d4533725dd27ea8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_INET   2</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00477" class="el">477</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="d9199903d1ac104e7baf50d0be210ce5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_ISO   7</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00482" class="el">482</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="170f4de24ddf9e5e4b465c52982a74dc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_LAT   14</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00490" class="el">490</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="6c871076aec6dec30819e30a2e3a4fc3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_MAX   18</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00495" class="el">495</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="dd8e7ab14f8edb35b6868e7f63881c8a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_NETBIOS   17</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00493" class="el">493</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="583263863f759b7414873f908c2b41cd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_NS   6</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00481" class="el">481</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="4632fef0e1964a0443898d474d7aa11a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_OSI   AF_ISO</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00483" class="el">483</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="3462cbdaa4032cadf4454bf9be94defb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_PUP   4</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00479" class="el">479</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="2c0900c81827dad7d83aa43539b8fc52" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_SNA   11</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00487" class="el">487</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="0c3400c34055390819719bb8eaa7cc7c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_UNIX   1</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00476" class="el">476</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="15330f6070f0f4dc7b20e75cc6750a80" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define AF_UNSPEC   0</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00475" class="el">475</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="b5e6563319959203fa44325f39ebc70e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define CallWSABlockingHookProc</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">userRoutine </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (*(userRoutine))()</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00753" class="el">753</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="ab6660ef146116405472dbe51ded359c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define EADDRINUSE   WSAEADDRINUSE</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00694" class="el">694</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="36ac74d3ed0089e6d249e173802e73cb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody