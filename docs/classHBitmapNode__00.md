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

# HBitmapNode Class Reference

`#include <`<a href="HBitmap_8h-source.md" class="el"><code>HBitmap.h</code></a>`>`

Inheritance diagram for HBitmapNode:

<span class="image placeholder" original-image-src="classHBitmapNode__inherit__graph.gif" original-image-title="" border="0" usemap="#HBitmapNode__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HBitmapNode:

<span class="image placeholder" original-image-src="classHBitmapNode__coll__graph.gif" original-image-title="" border="0" usemap="#HBitmapNode__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHBitmapNode-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f90" class="el">LoadFlags</a> {<br />
  <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f90a3eda5885d0d1d9df4b7ca5186ab8d19" class="el">LOADDEFAULT</a> = 0x0, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f908d752d82170bc40c52648233fb4b2e92" class="el">LOADBKCOLOR</a> = 0x01, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f90c32120c146000b42843de769221473a6" class="el">LOADINFOONLY</a> = 0x02, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f9067d00896560d72e79b9aa815b703e9b0" class="el">INITIALIZE</a> = 0x04,<br />
  <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f906fe5a6de34947399bec1de494faffbb4" class="el">NOMODIFIEDCHECK</a> = 0x08<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classHBitmapNode.md#dca29a1140aadadfd92b34a02fa516ef7b0d329a6efd1e7a527acf8970807616" class="el">LOAD_FAILED</a>, <a href="classHBitmapNode.md#dca29a1140aadadfd92b34a02fa516efad12af68d8c8a5dde34120db91a75e04" class="el">LOAD_OK</a>, <a href="classHBitmapNode.md#dca29a1140aadadfd92b34a02fa516efe817054f069c2f8f0db23cc1904d9594" class="el">ALREADY_LOADED</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classHBitmapNode.md#68986ab776eb5d6b5a809a1c005a73001ecc89dbe4cbc5edea13ce47f5e4bbab" class="el">WRITE_NORESULT</a> = 0, <a href="classHBitmapNode.md#68986ab776eb5d6b5a809a1c005a73006ffd8aa558c1ab84ddc0a01e4f14ed0d" class="el">WRITE_ERROR</a> = 0x01, <a href="classHBitmapNode.md#68986ab776eb5d6b5a809a1c005a730088c7dbe6cb83ed7007d031d2aaf99da5" class="el">WRITE_OK</a> = 0x02, <a href="classHBitmapNode.md#68986ab776eb5d6b5a809a1c005a7300819f8bf3646673def34d8208b4f59bd9" class="el">WRITE_NEEDCLOSE</a> = 0x04 }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#ce2848c68165384ff92043fdf7f975ff" class="el">GetWidth</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#35170f8abe223996b6ba9a0ee517f031" class="el">GetHeight</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#ff85d77fe4659bd9dfb48ca398b42b5f" class="el">SetWidth</a> (int width)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#feea73156231ff8f250e7f9f349e49f0" class="el">SetHeight</a> (int height)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBitmapNode.md" class="el">HBitmapNode</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#5988ebe9c94bc1df268302398b88259f" class="el">ScaleBitmap</a> (int width, int height)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#1a46212a663cf71ce9f1cfa68c2f6cac" class="el">CreateByteBlock</a> (int *rbytesperpixel, BOOL withborder=FALSE, BOOL *bHasTransparency=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#2a464a96ca46ec3f785db55051012b5e" class="el">GetFps</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#01f124db0da9e88f374426f626c7d711" class="el">SetFps</a> (LONG fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#0670dbd645d0e24b7f8f78d5c15d6aca" class="el">GetLength</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#f4257287ceccc0286ca07706359b33ba" class="el">SetLength</a> (int length)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#fed2199c2c73e7ac8eb60dd8b2e28099" class="el">AddBuffer</a> (<a href="classHBitmapBuffer.md" class="el">HBitmapBuffer</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#4f0b6a9c241d31a68df9e9009aaede12" class="el">DeleteAllBuffers</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBitmapBuffer.md" class="el">HBitmapBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#3cc76c8aec87ae4638e22cb40c83c6e8" class="el">GetBufferHead</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#76bd1fa3bd3914167a53e3e25ccb595e" class="el">ReadPixel</a> (int x, int y, <a href="classRGBFloat.md" class="el">RGBFloat</a> &amp;color)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#bffbb1bdcca358aafe5ae702077168d1" class="el">ReadPixel</a> (int x, int y, <a href="classRGBAFloat.md" class="el">RGBAFloat</a> &amp;color)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#a350bf25f70ebc124213e5ab0b4b924b" class="el">ReadPixel</a> (int x, int y, <a href="classYAFloat.md" class="el">YAFloat</a> &amp;color)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#4cf4c60fa05e10346f857fbdaf635245" class="el">LoadFrame</a> (const <a href="classString.md" class="el">String</a> &amp;filename, int frame=-1, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f90" class="el">LoadFlags</a> <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>=LOADDEFAULT)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHYABuffer.md" class="el">HYABuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#54201c467292cd17d120ab6203716047" class="el">CreateYABuffer</a> (const <a href="classString.md" class="el">String</a> &amp;name, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2" class="el">HBitmapBuffer::ChannelType</a> chantype, int width, int height)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHRGBABuffer.md" class="el">HRGBABuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#9942003d2f0b3c767e5d6071e57863df" class="el">CreateRGBABuffer</a> (const <a href="classString.md" class="el">String</a> &amp;name, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2" class="el">HBitmapBuffer::ChannelType</a> chantype, int width, int height)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHRGBBuffer.md" class="el">HRGBBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#8e893441f6061f6ce81e197d9539208c" class="el">CreateRGBBuffer</a> (const <a href="classString.md" class="el">String</a> &amp;name, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2" class="el">HBitmapBuffer::ChannelType</a> chantype, int width, int height)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHScalarBuffer.md" class="el">HScalarBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#4969c388c157e108c322e8f3a5534069" class="el">CreateScalarBuffer</a> (const <a href="classString.md" class="el">String</a> &amp;name, <a href="classHBitmapBuffer.md#d554a7dc176ab0ceadbb9ee4a647c3d2" class="el">HBitmapBuffer::ChannelType</a> chantype, int width, int height)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHRGBAFloatBuffer.md" class="el">HRGBAFloatBuffer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBitmapNode.md#a9d250a4399c8362d9a9f136b2f003c2" class="el">CreateRGBAFloatBuffer</a> (const <a href="classString.md" class="el">String</a> &amp;name, int width, int height)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

