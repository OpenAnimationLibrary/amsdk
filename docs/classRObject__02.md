## Member Function Documentation

<span id="baba436d04765f15dccba87a6a9a0b26" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void RObject::Collision</td>
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
<td colspan="2" class="md"><code> [inline, virtual]</code></td>
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
<td><p>Reimplemented in <a href="classQuadObject.md#c4fc0ecc7d5b33b72e07a25a9c9e8d4d" class="el">QuadObject</a>, <a href="classQuadrangle.md#baba436d04765f15dccba87a6a9a0b26" class="el">Quadrangle</a>, and <a href="classPropQuadrangle.md#baba436d04765f15dccba87a6a9a0b26" class="el">PropQuadrangle</a>.</p>
<p>Definition at line <a href="RObject_8h-source.md#l00035" class="el">35</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="13122199faaf2c52d0df4d93fc16f11c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual int RObject::GetType</td>
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
|   | Implemented in <a href="classQuadObject.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">QuadObject</a>, <a href="classPropQuadrangle.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">PropQuadrangle</a>, <a href="classRSphere.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">RSphere</a>, <a href="classCone.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">Cone</a>, <a href="classCylinder.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">Cylinder</a>, and <a href="classSlab.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">Slab</a>. |

<span id="3a8a40efddd68314bac0f4f5cb5d99fb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL RObject::Intersect</td>
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
<td colspan="2" class="md"><code> [inline, virtual]</code></td>
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
<td><p>Reimplemented in <a href="classRSphere.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">RSphere</a>, <a href="classCone.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">Cone</a>, <a href="classCylinder.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">Cylinder</a>, and <a href="classSlab.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">Slab</a>.</p>
<p>Definition at line <a href="RObject_8h-source.md#l00032" class="el">32</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ebc1dd006469e892a02410cbfdd1d3ec" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void RObject::Intersect</td>
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
<td colspan="2" class="md"><code> [inline, virtual]</code></td>
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
<td><p>Reimplemented in <a href="classQuadObject.md#c3c898dc00647a45cf30e65c45723946" class="el">QuadObject</a>, <a href="classQuadrangle.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Quadrangle</a>, <a href="classPropQuadrangle.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">PropQuadrangle</a>, <a href="classRSphere.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">RSphere</a>, <a href="classCone.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Cone</a>, <a href="classCylinder.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Cylinder</a>, and <a href="classSlab.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Slab</a>.</p>
<p>Definition at line <a href="RObject_8h-source.md#l00031" class="el">31</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top">virtual BOOL RObject::IsPatch</td>
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
<td><p>Reimplemented in <a href="classQuadObject.md#4bffe3bafe7317374a6eb3369ba34453" class="el">QuadObject</a>.</p>
<p>Definition at line <a href="RObject_8h-source.md#l00034" class="el">34</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="8a11f22291743884b9331d9cb58e455e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void RObject::Normal</td>
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
<td colspan="2" class="md"><code> [inline, virtual]</code></td>
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
<td><p>Reimplemented in <a href="classQuadObject.md#d4db60536569ed9a39b2a82c7cba5024" class="el">QuadObject</a>, <a href="classQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">Quadrangle</a>, <a href="classFractalQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">FractalQuadrangle</a>, <a href="classPropQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">PropQuadrangle</a>, <a href="classDisplaceQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">DisplaceQuadrangle</a>, <a href="classRSphere.md#8a11f22291743884b9331d9cb58e455e" class="el">RSphere</a>, <a href="classCone.md#8a11f22291743884b9331d9cb58e455e" class="el">Cone</a>, <a href="classCylinder.md#8a11f22291743884b9331d9cb58e455e" class="el">Cylinder</a>, and <a href="classSlab.md#8a11f22291743884b9331d9cb58e455e" class="el">Slab</a>.</p>
<p>Definition at line <a href="RObject_8h-source.md#l00033" class="el">33</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="b2a90b0840ba0f087728d89d27353935" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void RObject::operator delete</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>ptr</em></td>
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
<td><p>Definition at line <a href="RObject_8h-source.md#l00029" class="el">29</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p>
<p>References <a href="Allocate_8h.md#e40f4f61dc48a962d255a67edec0222d" class="el">FreeAtt()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classRObject_b2a90b0840ba0f087728d89d27353935_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classRObject_b2a90b0840ba0f087728d89d27353935_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="650118fc0cd96c1cd00cb1243c5e3358" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void* RObject::operator new</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">size_t </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>size</em></td>
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
<td><p>Reimplemented in <a href="classQuadObject.md#bc715659c306f0a65069ac15e7f2d659" class="el">QuadObject</a>.</p>
<p>Definition at line <a href="RObject_8h-source.md#l00027" class="el">27</a> of file <a href="RObject_8h-source.md" class="el">RObject.h</a>.</p>
<p>References <a href="Allocate_8h.md#66a3f82098ca891d0d8e11e33a48b54c" class="el">AllocAtt()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classRObject_650118fc0cd96c1cd00cb1243c5e3358_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classRObject_650118fc0cd96c1cd00cb1243c5e3358_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="RObject_8h-source.md" class="el">RObject.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:03 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
