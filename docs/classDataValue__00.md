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

# DataValue Class Reference

`#include <`<a href="DataValue_8h-source.md" class="el"><code>DataValue.h</code></a>`>`

[List of all members.](classDataValue-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#dbb5ad91a874a36b6003324c42c56abb" class="el">DataValue</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#d518cc1ca8e1ebc4707226e8c21092eb" class="el">DataValue</a> (BYTE *data, int length)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#fc673e610d7623f2edbb074cdfe0633c" class="el">DataValue</a> (const <a href="classDataValue.md" class="el">DataValue</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#742f7ecf6f3c6b34d0cbc4afef92d27d" class="el">~DataValue</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#99712cfce3529b5479ca47ea92742879" class="el">Init</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#9ccf1309510e2d2410b66c873a9dec13" class="el">operator=</a> (const <a href="classDataValue.md" class="el">DataValue</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#17bafad8a4b7c410baef55f7a63ddf1a" class="el">operator==</a> (const <a href="classDataValue.md" class="el">DataValue</a> &amp;other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#af6880ba6c41dcbb683182f9a7afcd99" class="el">GetData</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#515260f321f0211ea2a84c190dc56cac" class="el">SetData</a> (BYTE *data, int length)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#70a8806ccc79c5fa10cceb22ae1ad3bc" class="el">GetLength</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#72762c1c420cb029764351e6745f6ba0" class="el">AllocateData</a> (int length)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#f14b970389c12e1f2042f114847ebef7" class="el">FreeData</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#4b60768e769540f6a89151e8189e132a" class="el">IsEmpty</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BYTE * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#bf9e3c21a24d9d5a3de1ffb33d6efe5d" class="el">m_data</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classDataValue.md#cecb4cd09a8adf5aa458591c0dfdbb48" class="el">m_length</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

