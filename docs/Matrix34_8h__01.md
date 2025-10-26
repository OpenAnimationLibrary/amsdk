## Function Documentation

<span id="f57d590b1c44db757c91c7dd9790ba2e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> CreateEulerMatrix</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classRotate.md" class="el">Rotate</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>rotate</em></td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00155" class="el">155</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>References <a href="Rotate_8h-source.md#l00014" class="el">Rotate::roll</a>, <a href="Rotate_8h-source.md#l00014" class="el">Rotate::swivel</a>, <a href="Rotate_8h-source.md#l00014" class="el">Rotate::tilt</a>, <a href="Matrix34_8h-source.md#l00465" class="el">Matrix34::Transpose()</a>, and <a href="Matrix34_8h-source.md#l00135" class="el">YXZRotate()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix34_8h_f57d590b1c44db757c91c7dd9790ba2e_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix34_8h_f57d590b1c44db757c91c7dd9790ba2e_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="a9e9d4b367969631692f3073684568ac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> Identity34</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00205" class="el">205</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>References <a href="Matrix34_8h-source.md#l00053" class="el">Matrix34::InitBottomRow()</a>, <a href="Matrix34_8h-source.md#l00052" class="el">Matrix34::SetIdentity()</a>, and <a href="macwinsock_8h-source.md#l00036" class="el">TRUE</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix34_8h_a9e9d4b367969631692f3073684568ac_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix34_8h_a9e9d4b367969631692f3073684568ac_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="840773f9e5364b95d0a623450fa3027e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> operator *</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>v</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>m</em></td>
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
|   | Definition at line <a href="Matrix34_8h-source.md#l00131" class="el">131</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>. |

<span id="6d9ecae044b2f972995de8fdec41e29f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> Rotatef</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>angle</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00354" class="el">354</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>References <a href="Matrix34_8h-source.md#l00139" class="el">RotateV()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix34_8h_6d9ecae044b2f972995de8fdec41e29f_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix34_8h_6d9ecae044b2f972995de8fdec41e29f_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="cc49a8715c21e919bc629b6fdbd486a7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> RotateV</td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00139" class="el">139</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p>
<p>Referenced by <a href="Matrix34_8h-source.md#l00354" class="el">Rotatef()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="85ad183cd6e45377da219513d7ac2487" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> Scalef</td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00342" class="el">342</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>Referenced by <a href="Matrix34_8h-source.md#l00349" class="el">ScaleV()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="90daeb8672a3c3f34ac377f3b0474d7d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> ScaleV</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>v</em></td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00349" class="el">349</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>References <a href="Matrix34_8h-source.md#l00342" class="el">Scalef()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix34_8h_90daeb8672a3c3f34ac377f3b0474d7d_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix34_8h_90daeb8672a3c3f34ac377f3b0474d7d_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="ac7d11f3570f7c43f6029349705ab9f1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> StandardToVectors</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>newzdir</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>newydir</em></td>
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
<td><p>Definition at line <a href="Matrix34_8h-source.md#l00310" class="el">310</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>.</p>
<p>References <a href="Vector_8h-source.md#l00315" class="el">Vector::Norm()</a>, and <a href="Vector_8h-source.md#l00320" class="el">Vector::Normalize()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix34_8h_ac7d11f3570f7c43f6029349705ab9f1_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix34_8h_ac7d11f3570f7c43f6029349705ab9f1_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="c93fe4af36147fe6a797312f81e764f5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> ToMatrix33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classMatrix44.md" class="el">Matrix44</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>m</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Matrix34_8h-source.md#l00279" class="el">279</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>. |

<span id="593ddd99bc0c69f4c8d8d32a394d2e76" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> ToMatrix33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>m</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Matrix34_8h-source.md#l00272" class="el">272</a> of file <a href="Matrix34_8h-source.md" class="el">Matrix34.h</a>. |

<span id="c4b1ff6e9c551581f4feed6eff7c7079" class="anchor"></span>

<table class="mdTable