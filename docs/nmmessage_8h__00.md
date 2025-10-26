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

# nmmessage.h File Reference

`#include <sys/Types.h>`  
`#include <MixedMode.h>`  

Include dependency graph for nmmessage.h:

<span class="image placeholder" original-image-src="nmmessage_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/nmmessage.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="nmmessage_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/nmmessage.hdep_map"></span>

[Go to the source code of this file.](nmmessage_8h-source.md)

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
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#e90892939c61bf79f8f2894af07d1845" class="el">_NMMESSAGE_H_</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#30bb5ac5cf28c93780575315bd6c49e3" class="el">NM_INVALID_HANDLER</a>   (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a>)(0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#7026e5e52982b91fcce9ffe4a27f7f86" class="el">NewNMMessageCallbackProc</a>(userRoutine)   ((<a href="nmmessage_8h.md#1d5e0b7146d8d910b53fa3bdf2e18578" class="el">NMMessageCallbackProcPtr</a>) (userRoutine))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#4d1ba9ce71b9b67a071fcc706c65c287" class="el">CallNMMessageCallbackProc</a>(userRoutine, h, msg, wParam, lParam)   (*(userRoutine))((h), (msg), (wParam), (lParam))</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="typedefs">Typedefs</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef pascal unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a>(* </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#1d5e0b7146d8d910b53fa3bdf2e18578" class="el">NMMessageCallbackProcPtr</a> )(<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> h, unsigned int msg, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> wParam, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> lParam)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="nmmessage_8h.md#1d5e0b7146d8d910b53fa3bdf2e18578" class="el">NMMessageCallbackProcPtr</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#657d64418aea6794dd0e0e7f834e21ef" class="el">NMMessageCallbackUPP</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="nmmessage_8h.md#dca29a1140aadadfd92b34a02fa516ef129a9d2646156bd1772b14cc455f1420" class="el">uppNMMessageCallbackProcInfo</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal Boolean </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#164429de729376626fad41313d43a33e" class="el">NMInitializeMessages</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal void </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#b2564767ebf740fc9eacdad33b6314ae" class="el">NMTerminateMessages</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal <a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#eae8db0692ab8c7ff23c77b993d62195" class="el">NMCreateMessageHandler</a> (<a href="nmmessage_8h.md#657d64418aea6794dd0e0e7f834e21ef" class="el">NMMessageCallbackUPP</a> callback, void *refcon, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> reserved)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal Boolean </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#3303405c9ef1bb093251ce0ecb02b879" class="el">NMDestroyMessageHandler</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> h, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal void * </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#0854e84b5ac0384a38e0092f71ae1f09" class="el">NMGetMessageHandlerRefCon</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> h)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal void </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#673cf992c066fd387b654bf93d49a182" class="el">NMSetMessageHandlerRefCon</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> h, void *refcon)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal Boolean </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#6773afd6baf5a41ce411853a19f00e18" class="el">NMPostMessage</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> h, unsigned int msg, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> wParam, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> lParam)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#627b22980119fd0716f11ba0238ff69f" class="el">NMSendMessage</a> (<a href="nmmessage_8h.md#e32528de1cc8fbcfd35849cb4a8ed321" class="el">NMMessageHandler</a> h, unsigned int msg, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> wParam, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> lParam)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">pascal void </td>
<td class="memItemRight" data-valign="bottom"><a href="nmmessage_8h.md#a5bd81810e0626871f9b65489a3c6547" class="el">NMIdle</a> (void)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

