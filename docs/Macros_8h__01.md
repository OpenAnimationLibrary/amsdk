## Define Documentation

<span id="cfd007269cf70c4227e2e733cd9e8636" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __MACROS_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00003" class="el">3</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="5fc5e255045de6ee86047f56ba211a51" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __OS9ROS_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00009" class="el">9</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="1d37a64ea4e4add5f53e05796eac6119" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define ABS</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">a </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (((a)&lt;0)?(-(a)):(a))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00013" class="el">13</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="24a2a91ce1c395b0d626178ccdf4144b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define CEILING</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">a </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ((a)==(int)(a) ? (a) : (a)&gt;0 ? 1+(int)a : -(1+(int)(-a)))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00024" class="el">24</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="9eef548cd037fba9c87e386298f53872" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define DLLEXPORT</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00081" class="el">81</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="02b0da4211648559373db9255f9f0891" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define DOC</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">A </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ""</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00033" class="el">33</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="d7106fa7ff2ef46ed6913547f055f6a2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FLOOR</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">a </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   ((a)&gt;(0) ? (int)(a) : -(int)(-a))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00023" class="el">23</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="633e51a25d61d100f5be64fbb848e353" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define INVERSE</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">A </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   { A.x=-A.x;A.y=-A.y;A.z=-A.z; }</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00022" class="el">22</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="29ff52b7d513aadbecee8d379b3e1d7b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define ISODD</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">A </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (A&amp;0x1)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00021" class="el">21</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="59feb3c122aef6bc1274714d63378334" class="anchor"></span>

\#define MAX

( 

a,

b 

 ) 

   (((a)\>(b))?(a):(b))

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="Macros_8h-source.md#l00015" class="el">15</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>.</p>
<p>Referenced by <a href="RGBFloat_8h-source.md#l00083" class="el">RGBFloat::GetCOLORREF()</a>, <a href="TimeRang_8h-source.md#l00121" class="el">TimeRange::operator &amp;=()</a>, <a href="TimeRang_8h-source.md#l00268" class="el">TimeLineRect::operator|=()</a>, <a href="TimeRang_8h-source.md#l00111" class="el">TimeRange::operator|=()</a>, <a href="influenc_8h-source.md#l00103" class="el">InfluenceShape::SetAttenuation()</a>, and <a href="TimeRang_8h-source.md#l00172" class="el">TimeRange::Union()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="e6e6480a9ca65fe59160a87ac886d734" class="anchor"></span>

\#define MENU_DOC

( 

A,

B 

 ) 

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00034" class="el">34</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="34c39f670306181866ef5b3d2e61ad72" class="anchor"></span>

\#define MIN

( 

A,

B 

 ) 

   ((A)\<(B)?(A):(B))

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="Macros_8h-source.md#l00017" class="el">17</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>.</p>
<p>Referenced by <a href="ColorBuf_8inl-source.md#l00013" class="el">ColorBuf::ColorBuf()</a>, <a href="RGBByte_8h-source.md#l00287" class="el">YAByte::GammaCorrect()</a>, <a href="RGBByte_8h-source.md#l00128" class="el">RGBByte::GammaCorrect()</a>, <a href="RGBByte_8h-source.md#l00121" class="el">GammaCorrect()</a>, <a href="ColorBuf_8h-source.md#l00145" class="el">GammaCorrectColBuf()</a>, <a href="RGBFloat_8h-source.md#l00083" class="el">RGBFloat::GetCOLORREF()</a>, <a href="RGBHalf_8h-source.md#l00232" class="el">RGBAHalf::Max()</a>, <a href="RGBHalf_8h-source.md#l00065" class="el">RGBHalf::Max()</a>, <a href="HalfColorBuf_8h-source.md#l00157" class="el">HalfColorBufAlpha::Max()</a>, <a href="HalfColorBuf_8h-source.md#l00045" class="el">HalfColorBuf::Max()</a>, <a href="TimeRang_8h-source.md#l00121" class="el">TimeRange::operator &amp;=()</a>, <a href="TimeRang_8h-source.md#l00268" class="el">TimeLineRect::operator|=()</a>, <a href="TimeRang_8h-source.md#l00111" class="el">TimeRange::operator|=()</a>, <a href="ColorBuf_8inl-source.md#l00021" class="el">ColorBuf::Set()</a>, and <a href="TimeRang_8h-source.md#l00172" class="el">TimeRange::Union()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ce580edfbdfedafad6a10ad9748540d7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define NULLDELETE</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">a </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   { delete a; a = NULL; }</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00027" class="el">27</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="a273878eead34934624138fae5ff2e4d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define NUMELEMENTS</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">array </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (sizeof(array)/sizeof(array[0]))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00026" class="el">26</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="f9526c0abef33efac4c9ad5e9a9426c9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define PADWIDTH</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">x </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (((x)*8 + 31) &amp; (~31))/8</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00028" class="el">28</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="4a3e1eaf439a8f711aa83e5a6cc1b76b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define ROUNDOFF</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">A </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (LONG)((A)&lt;(0)?((A)-.5):((A)+.5))</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00020" class="el">20</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="d234c05689bfd9dde94b418b1dba86b9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define ROWBYTES</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">A </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (((A)+15)&gt;&gt;4&lt;&lt;1)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00018" class="el">18</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="6fb2982081cee248a2b1d9639993f634" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define ROWWORDS</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">A </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   (((A)+15)&gt;&gt;4)</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Macros_8h-source.md#l00019" class="el">19</a> of file <a href="Macros_8h-source.md" class="el">Macros.h</a>. |

<span id="fd4285aeb4387dda2c03f4d96135b208" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgr