## Member Function Documentation

<span id="6d8a38eb2e56e83a69410dabe93146f5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static void HPatch::DeleteHandle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHPatch.md" class="el">HPatch</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>handle</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [static]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="b092f4dc2c9bdb7c92b4d4b1c90e2c37" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * HPatch::GetAttr</td>
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

|  |  |
|----|----|
|   | This returns a pointer to the real HAttr in the Model or Group on the HPatch in case a person wanted to take their own samples from a HAttr. |

<span id="6b3726bff1e331be4b9c2c3b524c9dcc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * HPatch::GetCompositedAttr</td>
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

|  |  |
|----|----|
|   | On a HPatch there is a HAttr that is a composited attribute using the coordinates (0,0,0). This is what Hash use in real-time. |

<span id="b716164adb550a7eababd9e76d1d2198" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HPatch::GetCP1</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a pointer to the first <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
<p>There aren't actually real <strong>"first"</strong> CP but we need to start somewhere.</p>
<p>When looking down the patch normal, patch vertices are numbered in ascending order, counter clockwise.</p>
<p>A vertex's normal N can be computed by getting the cross product of its Out Tangent A with its In Tangent B; N = A ^ B ( the ^ symbol is defined as the cross product operator for the <a href="classVector.md" class="el">Vector</a> class )<br />
A: the Out Tangent A, is the "in" tangent of the spline leading to the next vertex ( unless the IsFlipV for the current vertex is set )<br />
B: The In Tangent B, is the "out" tangent of the spline leading from the previous vertex ( unless the IsFlipV for the previous vertex is set )</p>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="35ee595eaae9c809fefce48b3f6bf528" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HPatch::GetCP2</td>
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

|  |  |
|----|----|
|   | Returns a pointer to the second <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch. |

<span id="1cb01deb602779376f234844db81d9be" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HPatch::GetCP3</td>
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

|  |  |
|----|----|
|   | Returns a pointer to the third <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch. |

<span id="3aa897e1362c3ef314a541548c159ce7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HPatch::GetCP4</td>
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

|  |  |
|----|----|
|   | Returns a pointer to the fourth <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch. |

<span id="57e19c7536269e2e0b4085087c439904" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int HPatch::GetGroupImageRotation</td>
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

<span id="e30daf091303cc99467a21a5e7ac63f4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch::GetIT1</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the In tangent to the first <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
There aren't actually real <strong>"first"</strong> CP but we need to start somewhere.
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#2d63252b29a507b4eca3a0d4768c199e" class="el">HPatch::GetOT1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="aa50a3f2867aacd09008428d00930f13" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch::GetIT2</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the In tangent to the second <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#2d63252b29a507b4eca3a0d4768c199e" class="el">HPatch::GetOT1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="a2046e280e7cb552c50d549b98656523" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch::GetIT3</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the In tangent to the third <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#2d63252b29a507b4eca3a0d4768c199e" class="el">HPatch::GetOT1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="bc86939e8e88af4aeaec3364dcc0ca76" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch::GetIT4</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the In tangent to the fourth <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#2d63252b29a507b4eca3a0d4768c199e" class="el">HPatch::GetOT1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="206247c6e736fa90f34cad1dd9c50224" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int HPatch::GetNumPoints</td>
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

<span id="2d63252b29a507b4eca3a0d4768c199e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch::GetOT1</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the Out tangent to the first <a href="classHCP.md" class="el">HCP</a> in the list of 4 CPs that defines the patch.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
<p>GetIT1 and GetOT1 will get the tangent from different HCPs. That is because an HPatch is the result of <a href="classHSpline.md" class="el">HSpline</a> crossing and so the InTangent is from one of the crossing HSplines while the OutTangent is from the other crossing <a href="classHSpline.md" class="el">HSpline</a>. The CP and their tangents may be viewed like this:</p>
<div data-align="center">
<span class="image placeholder" data-original-image-src="CP-Tangents.gif" data-original-image-title="">CP-Tangents.gif</span>
<p><strong>Relations between In tangents, Out tangents and CPs</strong></p>
</div>
<p>The functions GetITx() and GetOTx() are usefull for the computing of normals to the CPs in a patch. it1^ot1 (that is the cross product between it1 and ot1) will generate the surface normal for the cp1 on the patch. However, just crossing the in &amp; out tangents of the splines that make the patch will produce some normals facing in and some out.</p>
<p>There aren't actually real <strong>"first"</strong> CP but we need to start somewhere.</p>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="be9f20fcc037fa45906cd5d3f9ef8a7d" class="anchor"></span>

<table 