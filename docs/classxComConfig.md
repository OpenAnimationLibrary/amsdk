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

# xComConfig Class Reference

`#include <`<a href="ComPort_8h-source.md" class="el"><code>ComPort.h</code></a>`>`

[List of all members.](classxComConfig-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#72b41745127c07c547dbec408fb48e74" class="el">xComConfig</a> (DCB *pDCB, CWnd *pParent=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#a2f3d2a80c5819844b92c371cf28e499" class="el">DoDataExchange</a> (CDataExchange *pDX)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#2c14f73f01b234111f154472ddd20080" class="el">OnOK</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#ee9956c8765bd5e2b105470cd549d41c" class="el">OnInitDialog</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CComboBox </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#323a8c43c0ee9cf92a0dbb6e94f34f1e" class="el">m_cStopBits</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CComboBox </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#19cde3a2ad45fd84456f6797be26db6f" class="el">m_cParity</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CComboBox </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#dec26b3b0d2709d04630dbd52961e144" class="el">m_cByteSize</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CComboBox </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#86d43840dde866a28a03223e8131d65e" class="el">m_cBaudRate</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DCB * </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#39c15eda39dce11b000442322c44245c" class="el">m_pDCB</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DCB </td>
<td class="memItemRight" data-valign="bottom"><a href="classxComConfig.md#551fc36a55b99e56d27b61dd04f072be" class="el">m_DCB</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="ComPort_8h-source.md#l00059" class="el">59</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="72b41745127c07c547dbec408fb48e74" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">xComConfig::xComConfig</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">DCB * </td>
<td class="mdname" data-nowrap=""><em>pDCB</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">CWnd * </td>
<td class="mdname" data-nowrap=""><em>pParent</em> = <code>NULL</code></td>
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

## Member Function Documentation

<span id="a2f3d2a80c5819844b92c371cf28e499" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void xComConfig::DoDataExchange</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">CDataExchange * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>pDX</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="ee9956c8765bd5e2b105470cd549d41c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL xComConfig::OnInitDialog</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="2c14f73f01b234111f154472ddd20080" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void xComConfig::OnOK</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [virtual]</code></td>
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

## Member Data Documentation

<span id="86d43840dde866a28a03223e8131d65e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">CComboBox <a href="classxComConfig.md#86d43840dde866a28a03223e8131d65e" class="el">xComConfig::m_cBaudRate</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ComPort_8h-source.md#l00067" class="el">67</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>. |

<span id="dec26b3b0d2709d04630dbd52961e144" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">CComboBox <a href="classxComConfig.md#dec26b3b0d2709d04630dbd52961e144" class="el">xComConfig::m_cByteSize</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ComPort_8h-source.md#l00066" class="el">66</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>. |

<span id="19cde3a2ad45fd84456f6797be26db6f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">CComboBox <a href="classxComConfig.md#19cde3a2ad45fd84456f6797be26db6f" class="el">xComConfig::m_cParity</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ComPort_8h-source.md#l00065" class="el">65</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>. |

<span id="323a8c43c0ee9cf92a0dbb6e94f34f1e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">CComboBox <a href="classxComConfig.md#323a8c43c0ee9cf92a0dbb6e94f34f1e" class="el">xComConfig::m_cStopBits</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ComPort_8h-source.md#l00064" class="el">64</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>. |

<span id="551fc36a55b99e56d27b61dd04f072be" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DCB <a href="classxComConfig.md#551fc36a55b99e56d27b61dd04f072be" class="el">xComConfig::m_DCB</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ComPort_8h-source.md#l00070" class="el">70</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>. |

<span id="39c15eda39dce11b000442322c44245c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DCB* <a href="classxComConfig.md#39c15eda39dce11b000442322c44245c" class="el">xComConfig::m_pDCB</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ComPort_8h-source.md#l00069" class="el">69</a> of file <a href="ComPort_8h-source.md" class="el">ComPort.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="ComPort_8h-source.md" class="el">ComPort.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:07 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
