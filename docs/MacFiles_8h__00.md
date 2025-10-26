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

# MacFiles.h File Reference

`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  

Include dependency graph for MacFiles.h:

<span class="image placeholder" original-image-src="MacFiles_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/MacFiles.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="MacFiles_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/MacFiles.hdep_map"></span>

[Go to the source code of this file.](MacFiles_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#567f83dd5911b6f65e5e75100dace5fd" class="el">SF_MATAC</a>   0x0001</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#84590c8a92965c0f356f9327fa8f6efc" class="el">SF_MATOC</a>   0x0002</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#0f9fc55fe80f43c8a81c14dee1e759ef" class="el">SF_MOTAC</a>   0x0004</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#aced7842751dddeaec9f4aeb88acb387" class="el">SF_MOTOC</a>   0x0008</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#6679fb07a67048fc482f5df3b5c01750" class="el">SF_SHOWDIR</a>   0x1000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#4d7f97838867522af996e309842fde98" class="el">PATH_SEPARATOR</a>   '\\'</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#318ecb2a2b3d53993bb2f6c5ac161613" class="el">PATH_SEPARATOR_STR</a>   "\\"</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#a7afb0f302dc14d3e3cddc6c12682a80" class="el">MacFindFirst</a>(pName, type, creator, <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, pFD)   FindFirstFile(pName,pFD)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#672b5eb1e55d8681ebe10f0f2785fb57" class="el">MacFindNext</a>   FindNextFile</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#bbdeeb52f62da0f6a5870e9460d7c7d9" class="el">MacFindClose</a>   FindClose</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#a1b154621aae2575ded9041e9ab81815" class="el">MacGetModuleFileName</a>(hModule, path, ptSize)   GetModuleFileName(hModule,path,ptSize)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#9c73e5c8bed8670e642ee45611975221" class="el">MacFileCount</a>(path)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#6932ade2ce4a318b09d71824febb1f5f" class="el">cpxFindFirst</a>(pName, type, creator, <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, pFD)   FindFirstFile(pName,pFD)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#c227577e5b98ca710a522ca340ac4cbb" class="el">cpxFindNext</a>   FindNextFile</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#8da9a14f3055906e086aa6f47fad650e" class="el">cpxFindClose</a>   FindClose</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#a59f3d0ba627422e8f649784ba44ae2d" class="el">cpxGetModuleFileName</a>(hModule, path, ptSize)   GetModuleFileName(hModule,path,ptSize)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#d817428b57bf9cb75fb020286f1893f7" class="el">cpxFileCount</a>(path)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#a8d90fcb28fc2c51bc09939cdfe42ee8" class="el">cpxGetRealFileName</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#8e29b4626ea8f370342a8e39526e0575" class="el">cpxGetSystemDirectory</a>(path, uSize)   GetWindowsDirectory(path,uSize)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#5284ac8021eeac3618e1d4bbe55b5c97" class="el">cpxGetDiskFreeSpace</a>   GetDiskFreeSpace</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#e293f9e78c43d2d6a5d4e087056bcbd0" class="el">cpxGetFileAttributes</a>(pName, type, creator)   GetFileAttributes(pName)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#286f1c1aada9bafd4844fc7e29b6cba7" class="el">ALL_FILES_FILTER</a>   "*.*|****"</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#d7036745e993e30775ca2c9c5acde49e" class="el">MacGetTempFile</a>   cpxGetTempFile</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CString FILEIOEXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#951ec74605d488bb5450339b58075eb2" class="el">cpxGetTempFile</a> (LPCTSTR lpPathName, LPCTSTR lpPrefixString, UINT uUnique)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL FILEIOEXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#8659dd9a09515ffcf21d5772a9771b5a" class="el">cpxExec</a> (BOOL wait, LPCSTR progname, char **argv)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL FILEIOEXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#a3a5a6423f20c4056dfaa27f8efb8c1d" class="el">cpxVolumeCanDenyOpen</a> (LPCSTR volume)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL FILEIOEXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#d93808b4b3139f91d00104f32d208aee" class="el">cpxCanLockFiles</a> (LPCSTR volume)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void FILEIOEXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#9e443ad3d674dbc4d7069ec787344b91" class="el">StripExtension</a> (CString &amp;fName)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void FILEIOEXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="MacFiles_8h.md#fecd6cfe92c600cd91d396082a8c14c9" class="el">AddPathSeparator</a> (CString &amp;fName)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

