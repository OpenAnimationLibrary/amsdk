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

# MemoryStream Class Reference

`#include <`<a href="HashFile_8h-source.md" class="el"><code>HashFile.h</code></a>`>`

Inheritance diagram for MemoryStream:

<span class="image placeholder" original-image-src="classMemoryStream__inherit__graph.gif" original-image-title="" border="0" usemap="#MemoryStream__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for MemoryStream:

<span class="image placeholder" original-image-src="classMemoryStream__coll__graph.gif" original-image-title="" border="0" usemap="#MemoryStream__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMemoryStream-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#809fdb57529cb7f8b55cad591d90dc3b" class="el">MemoryStream</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#f19ac16000bdc06eda627b26c4ea54e1" class="el">MemoryStream</a> (int size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#7af079cd4a2459493679be192e66ff0f" class="el">MemoryStream</a> (LONG <a href="classHashStream.md#15d61712450a686a7f365adf4fef581f" class="el">mode</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#99afda8b3ee6e36d7fca6936839f6566" class="el">MemoryStream</a> (const <a href="classMemoryStream.md" class="el">MemoryStream</a> &amp;ms)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#ae2c720f5891216e52d16a114dc7ee87" class="el">~MemoryStream</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#99712cfce3529b5479ca47ea92742879" class="el">Init</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#b63607db495a8777691df371f2a30962" class="el">SetSize</a> (int size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemoryStream.md" class="el">MemoryStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#14b72dc04f121f323b39a64bee7e84b7" class="el">operator=</a> (const <a href="classMemoryStream.md" class="el">MemoryStream</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#09395eba28b4e87202d246617fbcab5b" class="el">Open</a> (LONG <a href="classHashStream.md#15d61712450a686a7f365adf4fef581f" class="el">mode</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#9ad16508f2d39de33797079f1073fdcc" class="el">Open</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>, LONG <a href="classHashStream.md#15d61712450a686a7f365adf4fef581f" class="el">mode</a>=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#91efc67a605bc7a17a3f84dc9b715ffd" class="el">Open</a> (char *initbuf, LONG count, LONG <a href="classHashStream.md#15d61712450a686a7f365adf4fef581f" class="el">mode</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#bc97709a8940b98bdc86badffdb5e9da" class="el">Eof</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#ae22276c7490efee40cd72529c7a83b3" class="el">Empty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#0670dbd645d0e24b7f8f78d5c15d6aca" class="el">GetLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#915bc4ac9bfb31e446e333eda6f3f873" class="el">SetStatusMeter</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#fde77f23fe7b2aff9b4bbff7886cd45b" class="el">ReadC</a> (void *<a href="classMemoryStream.md#cb7e52b21171fb9a53b498202607f0bd" class="el">buf</a>, LONG count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#50b8cc23ca1673bb26d626a2c394f342" class="el">Read</a> (void *<a href="classMemoryStream.md#cb7e52b21171fb9a53b498202607f0bd" class="el">buf</a>, LONG count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#2a21ad14c1f9061e86f3488908c097f4" class="el">Write</a> (const void *<a href="classMemoryStream.md#cb7e52b21171fb9a53b498202607f0bd" class="el">buf</a>, LONG count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#5731576369d5ec612f670909a11ff1f9" class="el">Flush</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#4e063d9e8233e6a30cc01cbb65795797" class="el">Close</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#3985cde3ac5a2f0b11bfabd47c3fc3b2" class="el">ReadLine</a> (<a href="classString.md" class="el">String</a> &amp;line)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#a55de19009057e7dd54f3a8954878f6a" class="el">ReadLine</a> (<a href="classMemoryStream.md" class="el">MemoryStream</a> &amp;stream)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#1954df99f12b88ac8edbab26c3964df9" class="el">ParseString</a> (<a href="classString.md" class="el">String</a> &amp;token)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#f9f639af97521979917dfaaa5604b80d" class="el">ParseToken</a> (<a href="classString.md" class="el">String</a> &amp;token)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#fdad34f7c204434802464a3ca3306d2e" class="el">ParseToken</a> (char *token, char delim)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#e2861fe5083df269f60854d79c18558d" class="el">Seek</a> (int <a href="classMemoryStream.md#5e0bdcbddccca4d66d74ba8c1cee1a68" class="el">pos</a>, <a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c" class="el">SeekMode</a> seekmode)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#f94a854611b76efe8e8e66ae56577baf" class="el">GetPos</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#30512244e4403f57c456776f1f127551" class="el">IsLabel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#4fff96ceaef69ef6ff70b1f522abcbb4" class="el">IsHeader</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#0b2aa7bffc2537ad9036f93c37a92127" class="el">IsHeaderAt0</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#0879fd2cb8a10c0314f03815a9a61341" class="el">IsEndHeaderAt0</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#cb7e52b21171fb9a53b498202607f0bd" class="el">buf</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#5e0bdcbddccca4d66d74ba8c1cee1a68" class="el">pos</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#f5a8e923f8cd24b56b3bab32358cc58a" class="el">len</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md#7a044084747fe8a52d03a7c6aaabd5fa" class="el">blocklen</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

