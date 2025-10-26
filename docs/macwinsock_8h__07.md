d class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal <a href="macwinsock_8h.md#11841f74c59ef60168fc8e35b773c569" class="el">WSABlockingHookUPP</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#ec686e32a2ca8ca4c32963333b6d0d64" class="el">WSASetBlockingHook</a> (<a href="macwinsock_8h.md#11841f74c59ef60168fc8e35b773c569" class="el">WSABlockingHookUPP</a> pprocHook)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#fa1e43c37f9ec06b43fadd2758c73267" class="el">WSACancelBlockingCall</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#7ab41c6da4746603a4731b59b09a6f27" class="el">WSAAsyncGetServByName</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, char *name, char *proto, char *buf, int buflen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#2dbad6ebc2464bc2c487b130afc5011a" class="el">WSAAsyncGetServByPort</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, int port, char *proto, char *buf, int buflen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#73189342f1a1ff56042896a812348fcb" class="el">WSAAsyncGetProtoByName</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, char *name, char *buf, int buflen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#4f8ace0df88a68917e542464545a4137" class="el">WSAAsyncGetProtoByNumber</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, int number, char *buf, int buflen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#43b555d678c3e985ddb1775a74e38f2f" class="el">WSAAsyncGetHostByName</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, char *name, char *buf, int buflen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal HANDLE </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#1f85dcbbcefd15e36403b1e5f7937c68" class="el">WSAAsyncGetHostByAddr</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, char *addr, int len, int type, char *buf, int buflen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#3c6c6f3edfb91f2d4dd1ab35a462edd0" class="el">WSACancelAsyncRequest</a> (HANDLE lAsyncTaskID)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#5e7c40545bcf3bfc0b6691fd2ea70e72" class="el">WSAAsyncSelect</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, <a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> hWnd, <a href="macwinsock_8h.md#cc6e39cd4e6b0933050bad4144ee1ceb" class="el">u_int</a> wMsg, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> lEvent)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

