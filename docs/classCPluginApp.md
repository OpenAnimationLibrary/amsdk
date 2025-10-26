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

# CPluginApp Class Reference

`#include <`<a href="Misc_8h-source.md" class="el"><code>Misc.h</code></a>`>`

[List of all members.](classCPluginApp-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#dfffe2a2076c104bdb37ff75f006b98f" class="el">~CPluginApp</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual CWnd * </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#fe9aa7ab76745ebf6a0d2589a97a5897" class="el">GetMainWnd</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#4e89444164e7911d14f6690084e2f2a7" class="el">Run</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#8cd28d3fb92504babda287d2df7f4534" class="el">PreTranslateMessage</a> (MSG *pMsg)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#42d676fbeaba2b100e667996b2911cf1" class="el">PumpMessage</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#cff195cdef826b9d1a419fb236fcc153" class="el">OnIdle</a> (LONG lCount)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#94d0a34527c8a35ee5cf64051d4e5fc3" class="el">IsIdleMessage</a> (MSG *pMsg)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#d35a0196573c2c3ea4e39e23be737c6f" class="el">DoMessageBox</a> (LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#d41588beca51316e47d11b317342e95d" class="el">InitInstance</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#63647ffa9ad12da716885319b38ac2b4" class="el">ExitInstance</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md#8828f15f644c9cdf07cecd2a4aa79123" class="el">DoWaitCursor</a> (int nCode)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="Misc_8h-source.md#l00035" class="el">35</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="dfffe2a2076c104bdb37ff75f006b98f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual CPluginApp::~CPluginApp</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00038" class="el">38</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="d35a0196573c2c3ea4e39e23be737c6f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual int CPluginApp::DoMessageBox</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LPCTSTR </td>
<td class="mdname" data-nowrap=""><em>lpszPrompt</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>nType</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>nIDPrompt</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00046" class="el">46</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="8828f15f644c9cdf07cecd2a4aa79123" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void CPluginApp::DoWaitCursor</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>nCode</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00049" class="el">49</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="63647ffa9ad12da716885319b38ac2b4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual int CPluginApp::ExitInstance</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00048" class="el">48</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="fe9aa7ab76745ebf6a0d2589a97a5897" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual CWnd* CPluginApp::GetMainWnd</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00040" class="el">40</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="d41588beca51316e47d11b317342e95d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL CPluginApp::InitInstance</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00047" class="el">47</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="94d0a34527c8a35ee5cf64051d4e5fc3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL CPluginApp::IsIdleMessage</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">MSG * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>pMsg</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00045" class="el">45</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="cff195cdef826b9d1a419fb236fcc153" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL CPluginApp::OnIdle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LONG </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>lCount</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00044" class="el">44</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="8cd28d3fb92504babda287d2df7f4534" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL CPluginApp::PreTranslateMessage</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">MSG * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>pMsg</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00042" class="el">42</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="42d676fbeaba2b100e667996b2911cf1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL CPluginApp::PumpMessage</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00043" class="el">43</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

<span id="4e89444164e7911d14f6690084e2f2a7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual int CPluginApp::Run</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Misc_8h-source.md#l00041" class="el">41</a> of file <a href="Misc_8h-source.md" class="el">Misc.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="Misc_8h-source.md" class="el">Misc.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:51 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
