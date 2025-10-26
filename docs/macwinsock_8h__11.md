  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00576" class="el">576</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="ceef72e6b1d58ace0842d06fb8ff500e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FD_READ   0x01</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00574" class="el">574</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="35a1411f2203273a89cf23c1de4e92a7" class="anchor"></span>

\#define <a href="macwinsock_8h.md#4b713e955f7da6e32fe29495afaf2d4c" class="el">FD_SET</a>

( 

fd,

set 

 ) 

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p><strong>Value:</strong></p>
<div class="fragment">
<pre class="fragment"><code>do                                                    \
{                                                     \
   if (((fd_set *)(set))-&gt;fd_count &lt; FD_SETSIZE)                  \
      ((fd_set *)(set))-&gt;fd_array[((fd_set *)(set))-&gt;fd_count++]=fd; \
} while ( 0 )</code></pre>
</div>
<p>Definition at line <a href="macwinsock_8h-source.md#l00115" class="el">115</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="fbca5cd79971943c488b01006709ff02" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FD_SETSIZE   64</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00084" class="el">84</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="afcaf1f96379dc563f4fef3e4de93c6c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FD_WRITE   0x02</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00575" class="el">575</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="420a0398ab8524046370ed9e3ce4e0c7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FD_ZERO</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">set </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (((fd_set *)(set))-&gt;fd_count=0)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00122" class="el">122</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="b03902c0e283d5cf9de2120bc40ff466" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FIOASYNC   _IOW('f', 125, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00176" class="el">176</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="203ee6c6d0e76c7445ce67a6b15185bd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FIONBIO   _IOW('f', 126, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00175" class="el">175</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="074f1d42a30792f4271729cc9dda6570" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FIONREAD   _IOR('f', 127, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00174" class="el">174</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="a1a75298f640ac785cb7e02a6f8f8227" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define h_addr   h_addr_list[0]</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00198" class="el">198</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="6af3496f11f4e29f09d1316e68f2af8b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define h_errno   WSAGetLastError()</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00656" class="el">656</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="5090dc64cc51029464a834447c1103f4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define HIWORD</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">thelong </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ((<a href="macwinsock_8h.md#90477a3b67a3f9da199a98c216b1a77c" class="el">u_short</a>)(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>) thelong &gt;&gt; 16) &amp; 0xFFFF))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00068" class="el">68</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="4c98620e2be40adc4194ffc500b7812c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define HOST_NOT_FOUND   WSAHOST_NOT_FOUND</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00660" class="el">660</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="524ff0c804cd5878186b6a1afd8dd18b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define htonl</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">hostlong </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ((<a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)(hostlong))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00722" class="el">722</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="16b7865e0cbd0177c78b530a50fadf74" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define htons</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">hostshort </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ((<a href="macwinsock_8h.md#90477a3b67a3f9da199a98c216b1a77c" class="el">u_short</a>)(hostshort))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00723" class="el">723</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="514b59a55ac470fdb043eead3b62a56c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IMPLINK_HIGHEXPER   158</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00299" class="el">299</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="5bc10f8709786f2e9ecf285d0b2b6cad" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IMPLINK_IP   155</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00297" class="el">297</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="3900e39c664ecbc83d27d485f5499a48" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IMPLINK_LOWEXPER   156</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00298" class="el">298</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="dd4b6604090d7a80e41e677f1e657a10" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IN_CLASSA</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">i </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>)(i) &amp; 0x80000000) == 0)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00332" class="el">332</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="7d4163ef838a09a77af10f3dc4291f93" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IN_CLASSA_HOST   0x00ffffff</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00335" class="el">335</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="b78206c20fcca51d2f1a40421d89ff64" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IN_CLASSA_MAX   128</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="macwinsock_8h-source.md#l00336" class="el">336</a> of file <a href="macwinsock_8h-source.md" class="el">macwinsock.h</a>. |

<span id="9f1845719b05b3773c50dc20ebac3b6e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define IN_CLASSA_NET   0xff000