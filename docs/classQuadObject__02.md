## Member Function Documentation

<span id="c4fc0ecc7d5b33b72e07a25a9c9e8d4d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void QuadObject::Collision</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">ThreadInfo * </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Reimplemented from <a href="classRObject.md#baba436d04765f15dccba87a6a9a0b26" class="el">RObject</a>.</p>
<p>Implemented in <a href="classQuadrangle.md#baba436d04765f15dccba87a6a9a0b26" class="el">Quadrangle</a>, and <a href="classPropQuadrangle.md#baba436d04765f15dccba87a6a9a0b26" class="el">PropQuadrangle</a>.</p></td>
</tr>
</tbody>
</table>

<span id="97bbe45df6b2b139c951f179d5dc83b8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int QuadObject::GetType</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Implements <a href="classRObject.md#13122199faaf2c52d0df4d93fc16f11c" class="el">RObject</a>.</p>
<p>Reimplemented in <a href="classPropQuadrangle.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">PropQuadrangle</a>.</p>
<p>Definition at line <a href="influenc_8h-source.md#l00025" class="el">25</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.</p>
<p>References <a href="RType_8h-source.md#l00019" class="el">QUADRANGLE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="c3c898dc00647a45cf30e65c45723946" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void QuadObject::Intersect</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">ThreadInfo * </td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Reimplemented from <a href="classRObject.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">RObject</a>.</p>
<p>Implemented in <a href="classQuadrangle.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Quadrangle</a>, and <a href="classPropQuadrangle.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">PropQuadrangle</a>.</p></td>
</tr>
</tbody>
</table>

<span id="4bffe3bafe7317374a6eb3369ba34453" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL QuadObject::IsPatch</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Reimplemented from <a href="classRObject.md#4bffe3bafe7317374a6eb3369ba34453" class="el">RObject</a>.</p>
<p>Definition at line <a href="influenc_8h-source.md#l00024" class="el">24</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00036" class="el">TRUE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="d4db60536569ed9a39b2a82c7cba5024" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void QuadObject::Normal</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHit.md" class="el">Hit</a> &amp; </td>
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
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Reimplemented from <a href="classRObject.md#8a11f22291743884b9331d9cb58e455e" class="el">RObject</a>.</p>
<p>Implemented in <a href="classQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">Quadrangle</a>, <a href="classFractalQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">FractalQuadrangle</a>, <a href="classPropQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">PropQuadrangle</a>, and <a href="classDisplaceQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">DisplaceQuadrangle</a>.</p></td>
</tr>
</tbody>
</table>

<span id="bc715659c306f0a65069ac15e7f2d659" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void* QuadObject::operator new</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">size_t </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
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
|   | Reimplemented from <a href="classRObject.md#650118fc0cd96c1cd00cb1243c5e3358" class="el">RObject</a>. |

------------------------------------------------------------------------

