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

# Files.h File Reference

`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  

Include dependency graph for Files.h:

<span class="image placeholder" original-image-src="Files_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Files.h_map"></span>

[Go to the source code of this file.](Files_8h-source.md)

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
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#d275a95aeeb08d3b9d5eb7b034a8614c" class="el">Remove</a> (const <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#841fa9a6f39078454af25ebf1000fd0a" class="el">RemoveDir</a> (const <a href="classString.md" class="el">String</a> &amp;dir)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#bb8485e62fa1def13f75495ebb4f65ca" class="el">Rename</a> (const <a href="classString.md" class="el">String</a> &amp;src, const <a href="classString.md" class="el">String</a> &amp;dst)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#060017bca0004965a8f9317ca7d6636c" class="el">DirExists</a> (const <a href="classString.md" class="el">String</a> &amp;pathname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#b6e0cba182468b688431a9d9332bf4e3" class="el">FileExists</a> (const <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#4ce0520f0e4f1449794bd937e68e0a9a" class="el">MakeDirPath</a> (const <a href="classString.md" class="el">String</a> &amp;unexplodedname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#ae488008b2f24ad6814c08e81324a2fb" class="el">CanWriteDirPath</a> (const <a href="classString.md" class="el">String</a> &amp;name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#5ae6405935608dc1e440e86d06074568" class="el">CanWriteToFile</a> (const <a href="classString.md" class="el">String</a> &amp;name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#8e91f3607a32af46bd2007ff241805c4" class="el">IsReadOnly</a> (const <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT FILETIME </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#3b6c2dcf8ae824808557bf0875e7b1d5" class="el">GetFileModifiedTime</a> (int filenumber)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT FILETIME </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#26f519f409a90508cdb69368c196100e" class="el">GetFileModifiedTime</a> (const <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#08b9c06724e221cc92d20970915bfffa" class="el">IsFileModified</a> (const <a href="classString.md" class="el">String</a> &amp;filename, FILETIME reftime)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#6f6cbf82c92423700900431f812a991f" class="el">SetFileType</a> (const <a href="classString.md" class="el">String</a> &amp;filename, BOOL setapp, <a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> type)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Files_8h.md#d4427ff04fd73ca6bfbcb092e8a6b689" class="el">CopyFile</a> (<a href="classString.md" class="el">String</a> src, <a href="classString.md" class="el">String</a> dst)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

