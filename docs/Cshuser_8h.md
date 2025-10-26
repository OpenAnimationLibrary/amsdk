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

# Cshuser.h File Reference

[Go to the source code of this file.](Cshuser_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#cdf50e9dcd8276e4735822120b1bc464" class="el">CSHHelpEnabled</a>(_pCshOn)   SendMessage(GetFocus(), (UINT)RegisterWindowMessage("WM_CSHHASHELP"), (WPARAM)(0), (LPARAM)(LPINT)_pCshOn)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#1da6a72e8d3b76314ef1901d26618040" class="el">CSH_DLLNAME</a>   "CSH.DLL"</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#bab88e321e90bbc9d83e184b8bc6fb93" class="el">CSH_INITFUNCNAME</a>   "CSHInitialize"</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#463b1cc9865b73d8d4713a618620cfcc" class="el">CSH_REGISTERFUNCNAME</a>   "CSHRegisterDialog"</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="typedefs">Typedefs</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#e7306adfca41cfcf8bc37b95e4476077" class="el">a_UniqueID</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL WINAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#4a420b9a4f165a968592f18199ab4901" class="el">CSHInitialize</a> (LPSTR a_pHelpFile, BOOL bContextMenu)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL WINAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#10fbc6995c0489e6f988feea90d37d2f" class="el">CSHRegisterDialog</a> (HWND a_hDialog, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> <a href="Cshuser_8h.md#e7306adfca41cfcf8bc37b95e4476077" class="el">a_UniqueID</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#8583de6bbb140fde9ab8f93357543a63" class="el">BOOL</a> (WINAPI *fnCSHREGISTERDIALOG)(HWND a_hDialog</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL WINAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#216046c47b1dc0d7bd82d059c1e4b7bd" class="el">CSHContextMenu</a> (HWND hDlg, HWND hWndPoint, LPPOINT pPt)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL WINAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="Cshuser_8h.md#9bf2c8c4cdba564f3878ebc2ca4bc68e" class="el">CSHContextHelp</a> (HWND hDlg, HWND hCtrl, int iContextType)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="1da6a72e8d3b76314ef1901d26618040" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define CSH_DLLNAME   "CSH.DLL"</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Cshuser_8h-source.md#l00044" class="el">44</a> of file <a href="Cshuser_8h-source.md" class="el">Cshuser.h</a>. |

<span id="bab88e321e90bbc9d83e184b8bc6fb93" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define CSH_INITFUNCNAME   "CSHInitialize"</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Cshuser_8h-source.md#l00045" class="el">45</a> of file <a href="Cshuser_8h-source.md" class="el">Cshuser.h</a>. |

<span id="463b1cc9865b73d8d4713a618620cfcc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define CSH_REGISTERFUNCNAME   "CSHRegisterDialog"</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Cshuser_8h-source.md#l00046" class="el">46</a> of file <a href="Cshuser_8h-source.md" class="el">Cshuser.h</a>. |

<span id="cdf50e9dcd8276e4735822120b1bc464" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define CSHHelpEnabled</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">_pCshOn </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   SendMessage(GetFocus(), (UINT)RegisterWindowMessage("WM_CSHHASHELP"), (WPARAM)(0), (LPARAM)(LPINT)_pCshOn)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Cshuser_8h-source.md#l00041" class="el">41</a> of file <a href="Cshuser_8h-source.md" class="el">Cshuser.h</a>. |

------------------------------------------------------------------------

## Typedef Documentation

<span id="e7306adfca41cfcf8bc37b95e4476077" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">typedef <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> <a href="Cshuser_8h.md#e7306adfca41cfcf8bc37b95e4476077" class="el">a_UniqueID</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Cshuser_8h-source.md#l00032" class="el">32</a> of file <a href="Cshuser_8h-source.md" class="el">Cshuser.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="8583de6bbb140fde9ab8f93357543a63" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">typedef BOOL</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">WINAPI * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>fnCSHREGISTERDIALOG</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Referenced by <a href="HashFile_8h-source.md#l00155" class="el">HashStream::IsFailed()</a>, and <a href="StrClass_8h-source.md#l00076" class="el">String::operator!=()</a>. |

<span id="9bf2c8c4cdba564f3878ebc2ca4bc68e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL WINAPI CSHContextHelp</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">HWND </td>
<td class="mdname" data-nowrap=""><em>hDlg</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">HWND </td>
<td class="mdname" data-nowrap=""><em>hCtrl</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>iContextType</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="216046c47b1dc0d7bd82d059c1e4b7bd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL WINAPI CSHContextMenu</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">HWND </td>
<td class="mdname" data-nowrap=""><em>hDlg</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">HWND </td>
<td class="mdname" data-nowrap=""><em>hWndPoint</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">LPPOINT </td>
<td class="mdname" data-nowrap=""><em>pPt</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="4a420b9a4f165a968592f18199ab4901" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL WINAPI CSHInitialize</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LPSTR </td>
<td class="mdname" data-nowrap=""><em>a_pHelpFile</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>bContextMenu</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="10fbc6995c0489e6f988feea90d37d2f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL WINAPI CSHRegisterDialog</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">HWND </td>
<td class="mdname" data-nowrap=""><em>a_hDialog</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="mdname" data-nowrap=""><em>a_UniqueID</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
