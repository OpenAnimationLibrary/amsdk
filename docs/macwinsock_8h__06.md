>LPHOSTENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structservent.md" class="el">servent</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#8834174c78864a6d589ba8b0c8777688" class="el">SERVENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structservent.md" class="el">servent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#a70242dca5249c52799ac5610c0e102a" class="el">PSERVENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structservent.md" class="el">servent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#2d8f997aa307d30527c4e0384618e8eb" class="el">LPSERVENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structprotoent.md" class="el">protoent</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#f2bf95961d421d4bc1af710e71544eb5" class="el">PROTOENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structprotoent.md" class="el">protoent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#c363ead4e464fa4338817aac23a39137" class="el">PPROTOENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structprotoent.md" class="el">protoent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#a925df5065f9418705c8105a3ab61662" class="el">LPPROTOENT</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef timeval </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#923b181ddf746772e724e12de14055b6" class="el">TIMEVAL</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef timeval * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#587d0d69a27a6bb6aefee30e4026b160" class="el">PTIMEVAL</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef timeval * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#bf89f73f739027568e04a720dcbd38d5" class="el">LPTIMEVAL</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="macwinsock_8h.md#dca29a1140aadadfd92b34a02fa516eff2ff6be06f8cddc57a6c8f50337cbcb4" class="el">uppWSABlockingHookInfo</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#a712f2d10acd9e146e4b8528098941e2" class="el">__WSAFDIsSet</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a>, fd_set *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal <a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#1bc255182fe5daed65ecfbbfd149f7d8" class="el">accept</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, struct <a href="structsockaddr.md" class="el">sockaddr</a> *addr, int *addrlen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#c6091da5c1fb4240e3614b6c64a6adf0" class="el">bind</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, struct <a href="structsockaddr.md" class="el">sockaddr</a> *addr, int namelen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#f263bae17d2cc05ca8a978c8f81bd345" class="el">closesocket</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#4737d09410720b4ad65bbf3749f279f0" class="el">connect</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, struct <a href="structsockaddr.md" class="el">sockaddr</a> *name, int namelen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#12bcb4acd75b2e39c649166dcbb946ef" class="el">ioctlsocket</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> cmd, <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a> *argp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#87f0217ad856abb99453c986b2a6be24" class="el">getpeername</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, struct <a href="structsockaddr.md" class="el">sockaddr</a> *name, int *namelen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#12aefa689e61f4bfd4e5178910bb9c48" class="el">getsockname</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, struct <a href="structsockaddr.md" class="el">sockaddr</a> *name, int *namelen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#1eeb01dbd36afb2a1e50d765f650149c" class="el">getsockopt</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, int level, int optname, char *optval, int *optlen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal <a href="macwinsock_8h.md#04a40755820b9bdaf3d256f9b9d126b8" class="el">u_long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#7c17d39c452fe1d94c5bb927b85577c5" class="el">inet_addr</a> (char *cp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal char * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#1d77eef413001bbb50b6fbf0b3e804ac" class="el">inet_ntoa</a> (struct <a href="structin__addr.md" class="el">in_addr</a> in)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#63cc537ad17278a98d99b02964b452dd" class="el">listen</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, int backlog)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#0e6103c1549e711bf7cf0bea0f27ea64" class="el">recv</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, char *buf, int len, int <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#7581c06af9d4709c9cd6f161f0cdc5ff" class="el">recvfrom</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, char *buf, int len, int <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, struct <a href="structsockaddr.md" class="el">sockaddr</a> *from, int *fromlen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#1558c76292fd7a23653f75364489d5e8" class="el">select</a> (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#c0603d5064eadfebd42aa8da8fd368ad" class="el">send</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, char *buf, int len, int <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#efefc089ac4a9ed5b67689f2c45d6688" class="el">sendto</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, char *buf, int len, int <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, struct <a href="structsockaddr.md" class="el">sockaddr</a> *to, int tolen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#7f69f4c67ec1cadd4e58b679907faaf2" class="el">setsockopt</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, int level, int optname, char *optval, int optlen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#6de43323a694d53a810b9ada77c87b5b" class="el">shutdown</a> (<a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> s, int how)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal <a href="macwinsock_8h.md#75fbea08c09e684e6b3f3961761354fa" class="el">SOCKET</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#8cd1b3f5f3ad45e843dabb519aabd2fb" class="el">socket</a> (int af, int type, int protocol)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal struct <a href="structhostent.md" class="el">hostent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#6f2f818c7e7433ce140aa7073d88ba08" class="el">gethostbyaddr</a> (char *addr, int len, int type)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal struct <a href="structhostent.md" class="el">hostent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#de13d9d8c11e7e87e84567e400c5aa0c" class="el">gethostbyname</a> (char *name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#98daa038b91ee8a99559008a9a7dadd2" class="el">gethostname</a> (char *name, int namelen)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal struct <a href="structservent.md" class="el">servent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#5ce3aba26275559783f14bf5b231096b" class="el">getservbyport</a> (int port, char *proto)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal struct <a href="structservent.md" class="el">servent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#5feceea6074a7f8c0b806fc9da0c723c" class="el">getservbyname</a> (char *name, char *proto)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal struct <a href="structprotoent.md" class="el">protoent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#141d277505a9ee6493fd9d4d31f101dc" class="el">getprotobynumber</a> (int proto)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal struct <a href="structprotoent.md" class="el">protoent</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#d9ec38a568f21c4b25d7fcf9aba252d5" class="el">getprotobyname</a> (char *name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#726f4828b2369f992f42254fbef3ca93" class="el">WSAStartup</a> (<a href="macwinsock_8h.md#90477a3b67a3f9da199a98c216b1a77c" class="el">u_short</a> wVersionRequired, <a href="structWSAData.md" class="el">LPWSADATA</a> lpWSAData)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#9fe78602fa62bf5033577ebbf3d90eff" class="el">WSACleanup</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal void </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#8ab5a9e0d941d4d3d87690a8bee880ae" class="el">WSASetLastError</a> (int iError)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#e27a5118a2eb838af40f8097c9f5407f" class="el">WSAGetLastError</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#36ea24638e7c2a0b5810bed31c382edd" class="el">WSAIsBlocking</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal int </td>
<td class="memItemRight" data-valign="bottom"><a href="macwinsock_8h.md#806122efc44f227c211922f30c17dd38" class="el">WSAUnhookBlockingHook</a> (void)</td>
</tr>
<tr>
<t