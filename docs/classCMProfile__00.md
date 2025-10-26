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

# CMProfile Class Reference

`#include <`<a href="MProfile_8h-source.md" class="el"><code>MProfile.h</code></a>`>`

[List of all members.](classCMProfile-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#ed3a0b5143e3820425a3a0aa30f9584b" class="el">CMProfile</a> (char *iniFileName=NULL, BOOL flushOnWrite=FALSE, BOOL macwriteDOS=FALSE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#6478f9b99a67659e6db11db8553560bc" class="el">~CMProfile</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#a855d5d4b32621fc618c3c8cb368b21e" class="el">GetProfileString</a> (LPCTSTR psec, LPCTSTR pkey, LPCTSTR pdef, LPTSTR buf, DWORD bufsize)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#a0c2138886ececf79322e99946e65f55" class="el">GetProfileInt</a> (LPCTSTR psec, LPCTSTR pkey, UINT nDefault)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#a00c07862fb11d2a409f2b1ee0dd078e" class="el">WriteProfileString</a> (LPCTSTR psec, LPCTSTR pkey, LPCTSTR buf)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#f6a5ea5f96fc0fe15b7bb0ac95a2cc46" class="el">WriteProfileInt</a> (LPCTSTR psec, LPCTSTR pkey, UINT val)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#04d8e359bdb202ba069a4249e57428ad" class="el">ProfileFlush</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#d39de1b5cbc3e89b83a945c3bfd3dab0" class="el">GetIniPath</a> (const char *fname)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-member-functions">Protected Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#723465f2ce5af899a78994cb79a89d44" class="el">ProfileRead</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#6f1797079c7b3ba64536801db448a350" class="el">ProfileWrite</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#bc002d6599bf82e8b1f32b3e2f83202c" class="el">SetFileAttrib</a> (char *fname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#f2df9976f4bb8c561a3c6a6d04751a27" class="el">trim</a> (CString &amp;cs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#c7b5af668dda16375c691533df186200" class="el">qTrim</a> (CString &amp;cs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#e23e525dc2452c0736408548d8c0a5b6" class="el">quote</a> (CString &amp;cs)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#453f0d607ecff6778b4ab87b12fb8ea6" class="el">m_Dirty</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#7288c78d75a89bb18fc8bed25b20c825" class="el">m_flushOnWrite</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#7a9ca295b4613680ead0945148714f74" class="el">m_macwriteDOS</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CMapStringToPtr * </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#866bb6956dd720222db169b64519aaf4" class="el">m_profList</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CString </td>
<td class="memItemRight" data-valign="bottom"><a href="classCMProfile.md#66dd8e8c073a18dd5199eaf4026a8a14" class="el">m_iniFileName</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

