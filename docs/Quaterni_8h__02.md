## Function Documentation

<span id="7a2ab26ca21ece08d92e9f46b6c96470" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float Dot</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>a</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>b</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00213" class="el">213</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Quaterni_8h-source.md#l00023" class="el">Quaternion::v</a>, and <a href="Quaterni_8h-source.md#l00024" class="el">Quaternion::w</a>.</p>
<p>Referenced by <a href="Vector_8h-source.md#l00123" class="el">DistancePointToPlane()</a>, <a href="Quaterni_8h-source.md#l00099" class="el">Quaternion::Norm()</a>, <a href="Vector_8h-source.md#l00107" class="el">Vector::operator|()</a>, <a href="Vector_8h-source.md#l00090" class="el">Vector::Square()</a>, <a href="Rotate_8h-source.md#l00256" class="el">VectorsToAngle()</a>, and <a href="Rotate_8h-source.md#l00245" class="el">VectorsToLinear()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="886801291d0b13c7836ad19a19fd48b9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> IdentityQ</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00205" class="el">205</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>Referenced by <a href="Quaterni_8h-source.md#l00133" class="el">Quaternion::IsIdentity()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="16f0ee948800b237780f9b7b38068efd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> RotateVQ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>angle</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>axis</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00217" class="el">217</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p></td>
</tr>
</tbody>
</table>

<span id="53f2b9ac633e0057a6afa297f42f06f2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void TransformVector</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>q</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>v</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Quaterni_8h-source.md#l00209" class="el">209</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>. |

<span id="dcbdf5fc577cb21a8807236a1eb23e78" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> VectorsToStandardQ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>becomezdir</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>becomeydir</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00270" class="el">270</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>, <a href="Vector_8h-source.md#l00030" class="el">Vector::Vector()</a>, <a href="Vector_8h-source.md#l00027" class="el">Vector::x</a>, <a href="Vector_8h-source.md#l00027" class="el">Vector::y</a>, and <a href="Quaterni_8h-source.md#l00229" class="el">ZRotateRadiansQ()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Quaterni_8h_dcbdf5fc577cb21a8807236a1eb23e78_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Quaterni_8h_dcbdf5fc577cb21a8807236a1eb23e78_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="b10b0c1dc6c1e5ae2f185fcaed561f72" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> XRotateQ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>angle</em></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00233" class="el">233</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>, and <a href="Quaterni_8h-source.md#l00221" class="el">XRotateRadiansQ()</a>.</p>
<p>Referenced by <a href="Quaterni_8h-source.md#l00265" class="el">XYRotateQ()</a>, and <a href="Quaterni_8h-source.md#l00261" class="el">XYZRotateQ()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Quaterni_8h_b10b0c1dc6c1e5ae2f185fcaed561f72_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Quaterni_8h_b10b0c1dc6c1e5ae2f185fcaed561f72_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="743e737bdf4b64049d0fc6a7462b7705" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> XRotateRadiansQ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>anglerad</em></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00221" class="el">221</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Vector_8h-source.md#l00030" class="el">Vector::Vector()</a>.</p>
<p>Referenced by <a href="Quaterni_8h-source.md#l00233" class="el">XRotateQ()</a>, <a href="Quaterni_8h-source.md#l00249" class="el">YXRotateRadiansQ()</a>, and <a href="Quaterni_8h-source.md#l00245" class="el">YXZRotateRadiansQ()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Quaterni_8h_743e737bdf4b64049d0fc6a7462b7705_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Quaterni_8h_743e737bdf4b64049d0fc6a7462b7705_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="51692f9c4b5b036d3c3cfd78d99053c8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> XYRotateQ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>x</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>y</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00265" class="el">265</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Quaterni_8h-source.md#l00233" class="el">XRotateQ()</a>, and <a href="Quaterni_8h-source.md#l00237" class="el">YRotateQ()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Quaterni_8h_51692f9c4b5b036d3c3cfd78d99053c8_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Quaterni_8h_51692f9c4b5b036d3c3cfd78d99053c8_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="aefc203c35d02b9b7b4071b8fe1e4c4c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> XYZRotateQ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>x</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>y</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>z</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>Definition at line <a href="Quaterni_8h-source.md#l00261" class="el">261</a> of file <a href="Quaterni_8h-source.md" class="el">Quaterni.h</a>.</p>
<p>References <a href="Quaterni_8h-source.md#l00233" class="el">XRotateQ()</a>, <a href="Quaterni_8h-source.md#l00237" class="el">YRotateQ()</a>, and <a href="Quaterni_8h-source.md#l00241" class="el">ZRotateQ()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Quaterni_8h_aefc203c35d02b9b7b4071b8fe1e4c4c_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Quaterni_8h_aefc203c35d02b9b7b4071b8fe1e4c4c_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="0494837754cefe126a0141ef97a25397" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><ta