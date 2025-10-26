## Function Documentation

<span id="51b38547609c2cb31342492287c149e1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">typedef float</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">RAVE_CALLBACK * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>TQAGetFloat</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Referenced by <a href="Fastftol_8h-source.md#l00122" class="el">__declspec()</a>, <a href="Quaterni_8h-source.md#l00073" class="el">Quaternion::GetAngle()</a>, <a href="Quaterni_8h-source.md#l00081" class="el">Quaternion::GetAxis()</a>, <a href="RGBFloat_8h-source.md#l00112" class="el">GetSpectrumColor()</a>, <a href="ColorVec_8h-source.md#l00083" class="el">GetSpectrumColorVector()</a>, <a href="Rotate_8h-source.md#l00266" class="el">LinearToAngle360()</a>, <a href="Matrix34_8h-source.md#l00188" class="el">Matrix34::Matrix34()</a>, <a href="Rotate_8h-source.md#l00156" class="el">Quaternion::Quaternion()</a>, <a href="RGBFloat_8inl-source.md#l00044" class="el">RGBAFloat::RGBAFloat()</a>, <a href="Matrix34_8h-source.md#l00405" class="el">RotateEuler::RotateEuler()</a>, <a href="Rotate_8h-source.md#l00202" class="el">RotateSphere::RotateSphere()</a>, <a href="Matrix34_8h-source.md#l00395" class="el">RotateVector::RotateVector()</a>, <a href="Macros_8h-source.md#l00037" class="el">Round()</a>, <a href="Quaterni_8h-source.md#l00090" class="el">Quaternion::SetAngleAxis()</a>, <a href="Rotate_8h-source.md#l00245" class="el">VectorsToLinear()</a>, <a href="Matrix34_8h-source.md#l00300" class="el">VectorsToStandard()</a>, <a href="Matrix33_8h-source.md#l00155" class="el">VectorsToStandard33()</a>, <a href="Quaterni_8h-source.md#l00270" class="el">VectorsToStandardQ()</a>, <a href="Matrix34_8h-source.md#l00366" class="el">XRotateRadians()</a>, <a href="Matrix33_8h-source.md#l00129" class="el">XRotateRadians33()</a>, <a href="RGBFloat_8inl-source.md#l00067" class="el">YAFloat::YAFloat()</a>, <a href="Matrix34_8h-source.md#l00375" class="el">YRotateRadians()</a>, <a href="Matrix33_8h-source.md#l00138" class="el">YRotateRadians33()</a>, <a href="Matrix34_8h-source.md#l00384" class="el">ZRotateRadians()</a>, and <a href="Matrix33_8h-source.md#l00147" class="el">ZRotateRadians33()</a>. |

<span id="b09bd534354a6e1f272fba4b7033a9ad" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL QABitmapBindColorTable</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>engine</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> * </td>
<td class="mdname" data-nowrap=""><em>bitmap</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> * </td>
<td class="mdname" data-nowrap=""><em>colorTable</em></td>
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

<span id="f484bd57d94f46a24223bccd18d5e232" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL QABitmapDelete</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>engine</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> * </td>
<td class="mdname" data-nowrap=""><em>bitmap</em></td>
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

<span id="3b097b19bfb17bee5ae477633555ed39" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL QABitmapDetach</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>engine</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> * </td>
<td class="mdname" data-nowrap=""><em>bitmap</em></td>
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

<span id="8ecca1d9a350f09a45af22bfdbf1c4e0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL QABitmapNew</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>engine</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="mdname" data-nowrap=""><em>flags</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f514" class="el">TQAImagePixelType</a> </td>
<td class="mdname" data-nowrap=""><em>pixelType</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="structTQAImage.md" class="el">TQAImage</a> * </td>
<td class="mdname" data-nowrap=""><em>image</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> ** </td>
<td class="mdname" data-nowrap=""><em>newBitmap</em></td>
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

<span id="5c55980ee2f6eb31aef3af60d7d11c1f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL QAColorTableDelete</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>engine</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> * </td>
<td class="mdname" data-nowrap=""><em>colorTable</em></td>
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

<span id="1cf1867e34b9f7d069b28ef2446ad69e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL QAColorTableNew</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>engine</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#7fa401cbca28d63a24ec23212d9791fe" class="el">TQAColorTableType</a> </td>
<td class="mdname" data-nowrap=""><em>tableType</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">void * </td>
<td class="mdname" data-nowrap=""><em>pixelData</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="mdname" data-nowrap=""><em>transparentIndexFlag</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> ** </td>
<td class="mdname" data-nowrap=""><em>newTable</em></td>
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

<span id="e4606c40580d8c17f319c1f2cf33b9b1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a>* RAVE_CALL QADeviceGetFirstEngine</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="structTQADevice.md" class="el">TQADevice</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>device</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="baadb969a4f608b6ac47ff8076cfe5d1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a>* RAVE_CALL QADeviceGetNextEngine</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="structTQADevice.md" class="el">TQADevice</a> * </td>
<td class="mdname" data-nowrap=""><em>device</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> * </td>
<td class="mdname" data-nowrap=""><em>currentEngine</em></td>
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

<span id="4fbbd0d48e53f93df04d463ad874eec3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL QADrawContextDelete</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="structTQADrawContext.md" class="el">TQADrawContext</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>drawContext</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="96e714e5116fd8025c3c90491f3aa9a6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL QADrawContextNew</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="structTQADevice.md" class="el">TQADevice</a> * </td>
<td class="mdname" data-nowrap=""><em>device</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="structTQARect.md" class="el">TQARect</a> * </td>
<td class="mdname" data-no