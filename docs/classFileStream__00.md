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

# FileStream Class Reference

`#include <`<a href="HashFile_8h-source.md" class="el"><code>HashFile.h</code></a>`>`

Inheritance diagram for FileStream:

<span class="image placeholder" original-image-src="classFileStream__inherit__graph.gif" original-image-title="" border="0" usemap="#FileStream__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for FileStream:

<span class="image placeholder" original-image-src="classFileStream__coll__graph.gif" original-image-title="" border="0" usemap="#FileStream__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classFileStream-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#d32ff537926df3d28b48a40581a8beca" class="el">FileStream</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#fa0fbe0ec0717ccb03545ae939eb1654" class="el">~FileStream</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#cc0777dbdd97306c635c96d1396f076f" class="el">Open</a> (const <a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>, LONG <a href="classHashStream.md#15d61712450a686a7f365adf4fef581f" class="el">mode</a>=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#9ad16508f2d39de33797079f1073fdcc" class="el">Open</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>, LONG <a href="classHashStream.md#15d61712450a686a7f365adf4fef581f" class="el">mode</a>=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#1e6c6a7d86ca7ecb5484df545e4c667e" class="el">Open</a> (int filenumber)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#bc97709a8940b98bdc86badffdb5e9da" class="el">Eof</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#0670dbd645d0e24b7f8f78d5c15d6aca" class="el">GetLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#fde77f23fe7b2aff9b4bbff7886cd45b" class="el">ReadC</a> (void *buf, LONG count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#50b8cc23ca1673bb26d626a2c394f342" class="el">Read</a> (void *buf, LONG count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#2a21ad14c1f9061e86f3488908c097f4" class="el">Write</a> (const void *buf, LONG count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#5731576369d5ec612f670909a11ff1f9" class="el">Flush</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#4e063d9e8233e6a30cc01cbb65795797" class="el">Close</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#3985cde3ac5a2f0b11bfabd47c3fc3b2" class="el">ReadLine</a> (<a href="classString.md" class="el">String</a> &amp;line)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#a55de19009057e7dd54f3a8954878f6a" class="el">ReadLine</a> (<a href="classMemoryStream.md" class="el">MemoryStream</a> &amp;stream)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#1954df99f12b88ac8edbab26c3964df9" class="el">ParseString</a> (<a href="classString.md" class="el">String</a> &amp;token)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#f9f639af97521979917dfaaa5604b80d" class="el">ParseToken</a> (<a href="classString.md" class="el">String</a> &amp;token)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#fdad34f7c204434802464a3ca3306d2e" class="el">ParseToken</a> (char *token, char delim)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#e2861fe5083df269f60854d79c18558d" class="el">Seek</a> (int pos, <a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c" class="el">SeekMode</a> seekmode)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#f94a854611b76efe8e8e66ae56577baf" class="el">GetPos</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#7d1ac097cd1f593248b42b6135afaa04" class="el">FindAliasAsk</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#50baa73d45bca08c8e6eb3f89bba941a" class="el">FindFileAlias</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#ef0efddbf027fa60b1fa504f7a5524b8" class="el">FindFileAliasNameOnly</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#b2cb3275f47842fcaae5e4d8d2b6dd4d" class="el">FindPathAlias</a> (<a href="classString.md" class="el">String</a> &amp;pathname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#0582b7d9088a60d145fdff8ef521e798" class="el">AddFileAlias</a> (const <a href="classString.md" class="el">String</a> &amp;oldfilename, const <a href="classString.md" class="el">String</a> &amp;newfilename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#ae353a6b948bc21dbfbe8d91e0f6a530" class="el">AddPathAlias</a> (const <a href="classString.md" class="el">String</a> &amp;oldpathname, const <a href="classString.md" class="el">String</a> &amp;newpathname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#d20c0f53e9e7701272b5c4ad1fa5bf63" class="el">FreeFileAliases</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#b0ef2cb3d7ea744009a538097b1efc2f" class="el">FreePathAliases</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#df908ace8192cbe89aa9c7ad6ac6038a" class="el">FindAlias</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#b451959fa2fddc994e307366e99e464c" class="el">IsInFailedList</a> (<a href="classString.md" class="el">String</a> &amp;<a href="classHashStream.md#435ed7e9f07f740abf511a62c00eef6e" class="el">filename</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#1b3fe5749d19f82adb9f08a95f6ba296" class="el">ClearFailedList</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#aee1a3b9f67b83696ef8a7cc16e53c10" class="el">ResetCancelAll</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CStdioFile </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#8c7dd922ad47494fc02c388e12c00eac" class="el">file</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#de1faa8354c85adbc49fcbd7a4196bfa" class="el">m_tempname</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-protected-attributes">Static Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static CList&lt; <a href="classString.md" class="el">String</a>, <a href="classString.md" class="el">String</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#1b8c28feb10ee7732b6b83ef0ea04f96" class="el">failedloadlist</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static PathAlias * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#16ecdd2bf4d6c8eff29dd5b14a552ea2" class="el">pathaliashead</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static FileAlias * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#dd224b41adc5768b5db6365edd975066" class="el">filealiashead</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md#4f325e46a02969439b76d27dfc55d357" class="el">m_bCancelAll</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

