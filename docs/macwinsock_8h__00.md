<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# macwinsock.h File Reference

`#include <sys/Types.h>`  
`#include <MixedMode.h>`  
`#include "`<a href="nmmessage_8h-source.md" class="el"><code>nmmessage.h</code></a>`"`  

Include dependency graph for macwinsock.h:

<span class="image placeholder" original-image-src="macwinsock_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/macwinsock.h_map"></span>

[Go to the source code of this file.](macwinsock_8h-source.md)

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
&#10;<h2 id="classes">Classes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structhostent.md" class="el">hostent</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structnetent.md" class="el">netent</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structservent.md" class="el">servent</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structprotoent.md" class="el">protoent</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structin__addr.md" class="el">in_addr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structsockaddr__in.md" class="el">sockaddr_in</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structWSAData.md" class="el">WSAData</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structip__mreq.md" class="el">ip_mreq</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structsockaddr.md" class="el">sockaddr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structsockproto.md" class="el">sockproto</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structlinger.md" class="el">linger</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#c0d83f0b82a6b30de8811e69e6d95c61" class="el">TRUE</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#946003f97ccc52d5d3b54ac0ec31bbfc" class="el">FALSE</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#6147791e88bc071815284a39d48aef7e" class="el">MAKELONG</a>(loshort, hishort)   ((<a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>)hishort &lt;&lt; 16) | ((short)loshort &amp; 0xFFFF)))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#79416a88190ca334eb9b91f7984faed2" class="el">LOWORD</a>(thelong)   ((<a href="macwinsock_8h.md#90477a3b67a3f9da199a98c216b1a77c" class="el">u_short</a>)((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>) thelong &amp; 0xFFFF))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#5090dc64cc51029464a834447c1103f4" class="el">HIWORD</a>(thelong)   ((<a href="macwinsock_8h.md#90477a3b67a3f9da199a98c216b1a77c" class="el">u_short</a>)(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>) thelong &gt;&gt; 16) &amp; 0xFFFF))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#fbca5cd79971943c488b01006709ff02" class="el">FD_SETSIZE</a>   64</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#4789f2d3912e15ae4c7c6a5a04ed66ef" class="el">FD_CLR</a>(fd, set)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#35a1411f2203273a89cf23c1de4e92a7" class="el">FD_SET</a>(fd, set)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#420a0398ab8524046370ed9e3ce4e0c7" class="el">FD_ZERO</a>(set)   (((fd_set *)(set))-&gt;fd_count=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#4b796657753e8ed63623de06116507c8" class="el">FD_ISSET</a>(fd, set)   __WSAFDIsSet((<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a>)fd, (fd_set *)set)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#df0856024422c1ab1c91a291fe2360fb" class="el">timerisset</a>(tvp)   ((tvp)-&gt;tv_sec || (tvp)-&gt;tv_usec)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#c44a7cd9105e699fbd75050dcfcf4e01" class="el">timercmp</a>(tvp, uvp, cmp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#cc0e8f197b235d55c23c23620547398a" class="el">timerclear</a>(tvp)   (tvp)-&gt;tv_sec = (tvp)-&gt;tv_usec = 0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#a89a79d262fd1c644ecdcade2a6ffa0f" class="el">IOCPARM_MASK</a>   0x7F</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#379de4870a372f5e4b90ad59a29b6721" class="el">IOC_VOID</a>   0x20000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#5b8ac12bd83d9b5ad42141c824ca804c" class="el">IOC_OUT</a>   0x40000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#5a8a6fb94c6dce6252fd0bf09229a9e2" class="el">IOC_IN</a>   0x80000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#0ca4d328299e347d9a2d3295baf33f94" class="el">IOC_INOUT</a>   (IOC_IN|IOC_OUT)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#a3281dba0c426d503ce29a429e02b63c" class="el">_IO</a>(x, y)   (IOC_VOID|(x&lt;&lt;8)|y)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#100fea1d7a14c57851ecf035f47a6cef" class="el">_IOR</a>(x, y, t)   (IOC_OUT|(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>)sizeof(t)&amp;IOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#77575278163d69413263c36c1c28573c" class="el">_IOW</a>(x, y, t)   (IOC_IN|(((<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>)sizeof(t)&amp;IOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#074f1d42a30792f4271729cc9dda6570" class="el">FIONREAD</a>   _IOR('f', 127, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#203ee6c6d0e76c7445ce67a6b15185bd" class="el">FIONBIO</a>   _IOW('f', 126, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#b03902c0e283d5cf9de2120bc40ff466" class="el">FIOASYNC</a>   _IOW('f', 125, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#95965a4551458a98b1236f38f7b04e69" class="el">SIOCSHIWAT</a>   _IOW('s', 0, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#6cfdd58687e4891a562ebf0ea9714b59" class="el">SIOCGHIWAT</a>   _IOR('s', 1, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#b0754c24c0e377e25d8d41c4cfe3eae5" class="el">SIOCSLOWAT</a>   _IOW('s', 2, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#fc4cac58272a9c352a456f80b5c8ca9a" class="el">SIOCGLOWAT</a>   _IOR('s', 3, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#88c8cce4b743b77d6e94fc7cf21a17ea" class="el">SIOCATMARK</a>   _IOR('s', 7, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#a1a75298f640ac785cb7e02a6f8f8227" class="el">h_addr</a>   h_addr_list[0]</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#01d89a69e7d2227061f4902ac6adf188" class="el">IPPROTO_IP</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#0322d7859d8753e242b07c2fa9ef8ec8" class="el">IPPROTO_ICMP</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#54d9dd274bf5ca05310393d0f526915f" class="el">IPPROTO_GGP</a>   2</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#b9001bc02d273a10024644989541b42c" class="el">IPPROTO_TCP</a>   6</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#1194656080a3579f2d5d0fd32a545386" class="el">IPPROTO_PUP</a>   12</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#e6e1b644739d5231e0090e63f0171e86" class="el">IPPROTO_UDP</a>   17</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#eaef7a99c2b4dcda35ecae65b55aaf14" class