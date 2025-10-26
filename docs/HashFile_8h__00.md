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

# HashFile.h File Reference

`#include "`<a href="StrClass_8h-source.md" class="el"><code>StrClass.h</code></a>`"`  
`#include <afxtempl.h>`  

Include dependency graph for HashFile.h:

<span class="image placeholder" original-image-src="HashFile_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/HashFile.h_map"></span>

[Go to the source code of this file.](HashFile_8h-source.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classLabel.md" class="el">Label</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md" class="el">Header</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classStreamBOOL.md" class="el">StreamBOOL</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md" class="el">HashStream</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classFileStream.md" class="el">FileStream</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classStreamError.md" class="el">StreamError</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemoryStream.md" class="el">MemoryStream</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#d142546a7ec56c2939aef41af92b1df0" class="el">__HASHFILE_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#1c8d4b9e4fb469e87842090dd22a2e5a" class="el">NUMSTATUSSUBDIVISIONS</a>   100</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#10c2342bfaf8ea8d8c7d2b06f9d9f485" class="el">PRODUCTVERSION</a>   12.00f</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#31651a58ad0e0917a2aef68f9d809e89" class="el">GetLabelIDFromString</a> (char *string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#093dfdc372c3686bce9b66c065b2996d" class="el">GetHeaderIDFromString</a> (char *string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#5705b8edecaf69eb1d563b84dbb269c2" class="el">GetLabelStringFromID</a> (LONG pid, char *string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#fc7caea5c1d3301f6b594eb7e3c18e32" class="el">GetHeaderStringFromID</a> (LONG pid, char *string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#bac5ddbca35f0b9549a45c00fe9a9db9" class="el">IsFileOfType</a> (const <a href="classString.md" class="el">String</a> &amp;filename, LONG headerid)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#806ffc0ad13c1fba4ddbe6d08cb63603" class="el">IsFileOfTypeHash</a> (<a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#eeafdcf8da24a774bffa17eedd4c827b" class="el">FreeHashFileToken</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#f9bfd2a8aac87535d59540d88fae3260" class="el">sp</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#23977c20e77dd2c85b3f8f9d8a0b7e10" class="el">spb</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#4e9ece76d43756c9b2e29fe77577fb44" class="el">nl</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#207c954eca36f1b50f68fd9c0c91adfc" class="el">nlb</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#a833ef0bbd8e8e6aaea7945f49184de2" class="el">tab</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#387c7d1a5d2a2904e8c5b184de8d429f" class="el">tabb</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHeader.md" class="el">Header</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#7a9328ac0752a5a6fad93e450c4f1676" class="el">LabelAsHeader</a> (const <a href="classLabel.md" class="el">Label</a> &amp;label)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHeader.md" class="el">Header</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="HashFile_8h.md#6470fec773dd6b0b75015029471442c9" class="el">LabelAsEndHeader</a> (const <a href="classLabel.md" class="el">Label</a> &amp;label)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

