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

# MessageR.h File Reference

`#include "`<a href="DataType_8h-source.md" class="el"><code>DataType.h</code></a>`"`  
`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  

Include dependency graph for MessageR.h:

<span class="image placeholder" original-image-src="MessageR_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/MessageR.h_map"></span>

[Go to the source code of this file.](MessageR_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#dc7eaee8bbc089cc6744c7003d5119e0" class="el">__MESSAGER_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#eb4f2dbb58bcd0e990a04f8605389284" class="el">MR_OK</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#3a2451928c8f369857a0b09a6985b38b" class="el">MR_OKCANCEL</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#5e340a60e8b57cf6f4e0f28f7d13c70f" class="el">MR_RETRYCANCEL</a>   2</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#456191e894a5c67acfc559b706479cb8" class="el">MR_YESNO</a>   3</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#1886c088d0fc14240825cc208c7e11da" class="el">MR_YESNOCANCEL</a>   4</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#fe0d4d75849f679a83df54c840d887e4" class="el">MR_ABORTRETRYIGNORE</a>   5</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#4669434f3fc779f50df5350fb0bcb5b3" class="el">MR_SAVE</a>   6</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#48e8f4ae3b6a53b4207c749286472d52" class="el">MR_WARNING</a>   7</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#888a4dfd6a6e726bcda97c9e2fc1def4" class="el">MR_RETABORT</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#544a4af2d55720a3dfbdb75e1516bbe8" class="el">MR_RETNO</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#93b8f81f61385d2c6d0710be31615370" class="el">MR_RETCANCEL</a>   -1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#f95634e235b3098fb840b123640f61c2" class="el">MR_RETIGNORE</a>   2</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#e3c79315cbbadc73b42d59d32060d115" class="el">MR_RETOK</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#5917356bb2b8052eff72eddb8115e187" class="el">MR_RETRETRY</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#b031ca39fcd01db261fb584de5cc613f" class="el">MR_RETYES</a>   1</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#463cf42c5dd907fcc7895461b71db05e" class="el">MessageRequest</a> (UINT messageid, UINT style=MR_OK, void *parent=NULL, UINT stringid=128)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="MessageR_8h.md#3fbe70dc77ac59ad7082259989a23483" class="el">MessageRequest</a> (const <a href="classString.md" class="el">String</a> &amp;message, UINT style=MR_OK, void *parent=NULL, UINT stringid=128)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

