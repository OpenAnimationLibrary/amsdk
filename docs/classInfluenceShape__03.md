## Member Function Documentation

<span id="ed465fcabfc74d46120708c749bd1cb1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual <a href="classVector.md" class="el">Vector</a> InfluenceShape::Attract</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">RSphere</a>, <a href="classCone.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">Cone</a>, <a href="classCylinder.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">Cylinder</a>, and <a href="classSlab.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">Slab</a>. |

<span id="02e6db22f790c52d2b24411be1f0581a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual float InfluenceShape::Falloff</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">RSphere</a>, <a href="classCone.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">Cone</a>, <a href="classCylinder.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">Cylinder</a>, and <a href="classSlab.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">Slab</a>. |

<span id="747a5ea3a354d8d9cc6ce1138eacc6ce" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void InfluenceShape::FindBounds</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>min</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>max</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#1f8f3d611956246ca336e4f45fd01927" class="el">RSphere</a>, <a href="classCone.md#1f8f3d611956246ca336e4f45fd01927" class="el">Cone</a>, <a href="classCylinder.md#1f8f3d611956246ca336e4f45fd01927" class="el">Cylinder</a>, and <a href="classSlab.md#1f8f3d611956246ca336e4f45fd01927" class="el">Slab</a>. |

<span id="b8901bf3e1a17ce3905d633600d9a41f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual <a href="classVector.md" class="el">Vector</a> InfluenceShape::Friction</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">RSphere</a>, <a href="classCone.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">Cone</a>, <a href="classCylinder.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">Cylinder</a>, and <a href="classSlab.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">Slab</a>. |

<span id="295b20d009018e2440e3b3ab2d053928" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float InfluenceShape::GetAttenuation</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>d</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="influenc_8h-source.md#l00095" class="el">95</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.</p>
<p>References <a href="influenc_8h-source.md#l00087" class="el">m_k0</a>, <a href="influenc_8h-source.md#l00087" class="el">m_k1</a>, and <a href="influenc_8h-source.md#l00087" class="el">m_k2</a>.</p></td>
</tr>
</tbody>
</table>

<span id="d15806044fc54bed18e5ebcc9fec450f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL InfluenceShape::IsInside</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>p</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">RSphere</a>, <a href="classCone.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">Cone</a>, <a href="classCylinder.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">Cylinder</a>, and <a href="classSlab.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">Slab</a>. |

<span id="537d66a6bbd42ad08263de580a2b2ed5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual float InfluenceShape::Lighting</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float &amp; </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">RSphere</a>, <a href="classCone.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">Cone</a>, <a href="classCylinder.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">Cylinder</a>, and <a href="classSlab.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">Slab</a>. |

<span id="863d00ecaa895fef07eee8d995926179" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual float InfluenceShape::LightingNoCap</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>p</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Reimplemented in <a href="classCone.md#863d00ecaa895fef07eee8d995926179" class="el">Cone</a>.</p>
<p>Definition at line <a href="influenc_8h-source.md#l00115" class="el">115</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="7490d5dd0cac19f83890f8b849062bc1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void InfluenceShape::SetAttenuation</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>attenuation</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="influenc_8h-source.md#l00103" class="el">103</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.</p>
<p>References <a href="influenc_8h-source.md#l00087" class="el">m_k0</a>, <a href="influenc_8h-source.md#l00087" class="el">m_k1</a>, <a href="influenc_8h-source.md#l00087" class="el">m_k2</a>, and <a href="Macros_8h-source.md#l00015" class="el">MAX</a>.</p>
<p>Referenced by <a href="influenc_8h-source.md#l00091" class="el">InfluenceShape()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="e976136b845128b8c3ffc6df95689a1b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void InfluenceShape::SetMatrices</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
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

<span id="598208f3fbafd245609ae9fc5cb320a1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void InfluenceShape::Transform</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">RSphere</a>, <a href="classCone.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">Cone</a>, <a href="classCylinder.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">Cylinder</a>, and <a href="classSlab.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">Slab</a>. |

<span id="8fb905b10b0a894a9e053a0648139da0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual <a href="classVector.md" class="el">Vector</a> InfluenceShape::Vortex</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Implemented in <a href="classRSphere.md#cf2ea65a3bf1134f7a05638c12a6c1bf" class="el">RSphere</a>, <a href="classCone.md#cf2ea65a3bf1134f7a05638c12a6c1bf" class="el"