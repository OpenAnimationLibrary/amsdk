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

# HBitmapBuffer Class Reference

`#include <`<a href="HBitmap_8h-source.md" class="el"><code>HBitmap.h</code></a>`>`

Inheritance diagram for HBitmapBuffer:

<span class="image placeholder" original-image-src="classHBitmapBuffer__inherit__graph.gif" original-image-title="" border="0" usemap="#HBitmapBuffer__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HBitmapBuffer:

<span class="image placeholder" original-image-src="classHBitmapBuffer__coll__graph.gif" original-image-title="" border="0" usemap="#HBitmapBuffer__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHBitmapBuffer-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2" class="el">ChannelType</a> {<br />
  <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d27d2931e991fc794182b46df6d565240f" class="el">CT_UBYTE</a> = 0, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2e5ad4f387424d5911fb914b97a3c01db" class="el">CT_UINT</a> = 1, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d253d0b60c79df001c59cba43ff1929ef6" class="el">CT_HALF</a> = 2, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d20e15cc0864a156807f63f784bac3f09b" class="el">CT_FLOAT</a> = 3,<br />
  <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2e52fa2c98c247280e46a89cdfe7b1885" class="el">CT_NUM_CHANNELTYPE</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f419" class="el">BufferType</a> {<br />
  <a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f4199790677e710760eb40b785e9fce43c0e" class="el">BT_SCALAR</a> = 0, <a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f419bfbc55299d5853abda88c148cabd31cd" class="el">BT_RGB</a> = 1, <a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f419191e1123d5d060462b811e1cf8f9562e" class="el">BT_RGBA</a> = 2, <a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f4196661c045737508682adadc558c5267d7" class="el">BT_YA</a> = 3,<br />
  <a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f419c30aa37dadbeaa34f95af5833718643e" class="el">BT_NUM_BUFFERTYPE</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#96e0486821b8a819072c1943f9f87a64" class="el">GetChannelAt</a> (int channum)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#e8830560ace291fdc0784667f1f91580" class="el">AllocateData</a> (int mipmaplevel=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#ce2848c68165384ff92043fdf7f975ff" class="el">GetWidth</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#35170f8abe223996b6ba9a0ee517f031" class="el">GetHeight</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BITMAPINFO * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#05513298bdd6f84ba990456658128ac5" class="el">CreateBITMAPINFO</a> (BOOL replacealpha0withbk=FALSE, BOOL maketransparent=FALSE, <a href="classRGBFloat.md" class="el">RGBFloat</a> *background=FALSE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBitmapBuffer.md" class="el">HBitmapBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#0d4ba4036cc2dcca8c73cdde356797cd" class="el">GetNext</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#b062d260dfc6363d45c095431f549824" class="el">GetNbrChannels</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2" class="el">ChannelType</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#26551028538b3f4aa5388f79eabca331" class="el">GetChannelsType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classHBitmapBuffer.md#6bdf0c91f27cb5f76edc6886eb10f419" class="el">BufferType</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#a1b2b8fc06e04650516eaf5289ecf860" class="el">GetBufferType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#9e31c7df549d3c6b21495b286c5992dd" class="el">GetChannelNameAt</a> (int channum)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#ece2e6485f1eb7112a8cd99d36eec8c6" class="el">SetBackground</a> (const <a href="classRGBFloat.md" class="el">RGBFloat</a> &amp;color)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classRGBFloat.md" class="el">RGBFloat</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#b804427fc19146300af4c084ca1232ea" class="el">GetBackground</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#bb1ea4901086b219c43a00d3260a8b77" class="el">SetIsKeyBackground</a> (BOOL iskeybackground)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#877f18f56fa87141fefef1df4264f49b" class="el">GetIsKeyBackground</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#cc188c9e2068e7191e13651b0d800afc" class="el">SetGamma</a> (float gamma)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#afcb03ef1c1eb4a4681aed36e60d82ee" class="el">GetGamma</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#3e0552436f1fc4721e8c1e80eb63273e" class="el">SetIsPremultipliedAlpha</a> (BOOL ispremultiplied)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#0aa3b5b9aed125e0f69ad2c639c67745" class="el">GetIsPremultipliedAlpha</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBitmapBuffer.md" class="el">HBitmapBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#f05155d66a18c82acfa7d871654a2cb2" class="el">MakeCopy</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBitmapBuffer.md" class="el">HBitmapBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapBuffer.md#2e68e2dd9fee6346776207c1e49484bc" class="el">MakeBlankCopy</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

