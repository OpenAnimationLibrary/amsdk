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

# HExpression Class Reference

`#include <`<a href="HPropDri_8h-source.md" class="el"><code>HPropDri.h</code></a>`>`

Inheritance diagram for HExpression:

<span class="image placeholder" original-image-src="classHExpression__inherit__graph.gif" original-image-title="" border="0" usemap="#HExpression__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HExpression:

<span class="image placeholder" original-image-src="classHExpression__coll__graph.gif" original-image-title="" border="0" usemap="#HExpression__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHExpression-members.md)

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
&#10;<h2 id="public-types">Public Types</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516efe0aa021e21dddbd6d8cecec71e9cf564" class="el">OK</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef68367ec3fbebddf8f929bdc5106b05c8" class="el">CANTTOKENIZE</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef6473a71b68d111358dda843a64d8cb30" class="el">NORIGHTPARENTHESIS</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef08953bee3cc5bdb535982973427e2cfa" class="el">UNKNOWNSYMBOL</a>,<br />
  <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef488953e35b20e087dd47db90701f76d9" class="el">DIVISIONBYZERO</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef5ab7581e2e5e363244b65c941b278054" class="el">NOLEFTPARENTHESIS</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516efa5697ac3f23b15bc2d2d9de373ca8375" class="el">NOCOMMA</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef09e9c03ee103665a7512d66a5f6b05b8" class="el">OUTOFRANGE</a>,<br />
  <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516effbcd8f32e6f3cb3efd70403297bc82f9" class="el">MUSTBEFLOAT</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516efc376c1f9e8eca687601d8370e8f293d9" class="el">BADTYPESFORADD</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef6bda532b008be1abd589bb12a7d44cb9" class="el">BADTYPESFORMULTIPLY</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef91f1f9d32cc6760c6e8c898d57b4a5a5" class="el">INCORRECTTYPE</a>,<br />
  <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef49412f210798bb76d13062f31e4f31f6" class="el">MUSTBETIME</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516efc5c94c1a3cb2d4168dec6c2803971be1" class="el">BADTYPESFORCOMPARE</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef377b7522214967373381fe0cf1544db1" class="el">BADTYPESFORAND</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef7ffaf53cfa6bfd5b7de749f46697aecc" class="el">BADTYPESFOROR</a>,<br />
  <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef55fea02a9182d5c3a260c0f82911ed3a" class="el">BADTYPEFORNOT</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef6608edab4ed32510da1c79552ae4dcb4" class="el">MUSTBEBOOL</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516efa88d72e3c8161c9197a7c979339e5b47" class="el">MUSTBEVECTOR</a>, <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef351ffcc8b5614080d56ad4d74edacded" class="el">MISSINGPARAMETER</a>,<br />
  <a href="classHExpression.md#dca29a1140aadadfd92b34a02fa516ef627249e6794f5232fd25c81844be7a6b" class="el">MUSTBETRANSFORM</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHExpression.md#3912c3a4319307568f9f3778efcfdfce" class="el">GetExpressionString</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHExpression.md#f6a09012291d49e95b38a88e9f906c1e" class="el">SetExpressionString</a> (const <a href="classString.md" class="el">String</a> &amp;str)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="HPropDri_8h-source.md#l00197" class="el">197</a> of file <a href="HPropDri_8h-source.md" class="el">HPropDri.h</a>.

------------------------------------------------------------------------

## Member Enumeration Documentation

<span id="dca29a1140aadadfd92b34a02fa516ef" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">anonymous enum</td>
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
<td><dl>
<dt><strong>Enumerator:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516efe0aa021e21dddbd6d8cecec71e9cf564" class="anchor"></span>OK</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef68367ec3fbebddf8f929bdc5106b05c8" class="anchor"></span>CANTTOKENIZE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef6473a71b68d111358dda843a64d8cb30" class="anchor"></span>NORIGHTPARENTHESIS</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef08953bee3cc5bdb535982973427e2cfa" class="anchor"></span>UNKNOWNSYMBOL</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef488953e35b20e087dd47db90701f76d9" class="anchor"></span>DIVISIONBYZERO</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef5ab7581e2e5e363244b65c941b278054" class="anchor"></span>NOLEFTPARENTHESIS</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516efa5697ac3f23b15bc2d2d9de373ca8375" class="anchor"></span>NOCOMMA</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef09e9c03ee103665a7512d66a5f6b05b8" class="anchor"></span>OUTOFRANGE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516effbcd8f32e6f3cb3efd70403297bc82f9" class="anchor"></span>MUSTBEFLOAT</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516efc376c1f9e8eca687601d8370e8f293d9" class="anchor"></span>BADTYPESFORADD</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef6bda532b008be1abd589bb12a7d44cb9" class="anchor"></span>BADTYPESFORMULTIPLY</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef91f1f9d32cc6760c6e8c898d57b4a5a5" class="anchor"></span>INCORRECTTYPE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef49412f210798bb76d13062f31e4f31f6" class="anchor"></span>MUSTBETIME</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516efc5c94c1a3cb2d4168dec6c2803971be1" class="anchor"></span>BADTYPESFORCOMPARE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef377b7522214967373381fe0cf1544db1" class="anchor"></span>BADTYPESFORAND</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef7ffaf53cfa6bfd5b7de749f46697aecc" class="anchor"></span>BADTYPESFOROR</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef55fea02a9182d5c3a260c0f82911ed3a" class="anchor"></span>BADTYPEFORNOT</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef6608edab4ed32510da1c79552ae4dcb4" class="anchor"></span>MUSTBEBOOL</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516efa88d72e3c8161c9197a7c979339e5b47" class="anchor"></span>MUSTBEVECTOR</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef351ffcc8b5614080d56ad4d74edacded" class="anchor"></span>MISSINGPARAMETER</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef627249e6794f5232fd25c81844be7a6b" class="anchor"></span>MUSTBETRANSFORM</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="HPropDri_8h-source.md#l00200" class="el">200</a> of file <a href="HPropDri_8h-source.md" class="el">HPropDri.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Function Documentation

<span id="3912c3a4319307568f9f3778efcfdfce" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> HExpression::GetExpressionString</td>
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

<span id="f6a09012291d49e95b38a88e9f906c1e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int HExpression::SetExpressionString</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>str</em></td>
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

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPropDri_8h-source.md" class="el">HPropDri.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
