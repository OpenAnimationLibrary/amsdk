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

# ColorBuf Class Reference

Simple RGB and RGBA color buffer where R, G, B and A are represented by byte values. Same as what is stored in the TGA files. [More...](#_details)

`#include <`<a href="ColorBuf_8h-source.md" class="el"><code>ColorBuf.h</code></a>`>`

[List of all members.](classColorBuf-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#674842783ab8e99b3a00fe0aedd72785" class="el">operator+=</a> (const <a href="classColorBuf.md" class="el">ColorBuf</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#e29bf1c7d903ec4f63643d2b8b924ec6" class="el">operator-=</a> (const <a href="classColorBuf.md" class="el">ColorBuf</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#299cf8813cba25caa1a8533ce7709734" class="el">operator *=</a> (const float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classColorBuf.md" class="el">ColorBuf</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#2485eb54184a6269e7cf9c830c526585" class="el">operator+</a> (const <a href="classColorBuf.md" class="el">ColorBuf</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#937d3668c777a0e6e44b58c7567e1bb7" class="el">operator COLORREF</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classColorBuf.md" class="el">ColorBuf</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#6f516da35f71dcc106f4a69756480a3c" class="el">operator=</a> (const <a href="classColorBuf.md" class="el">ColorBuf</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#3a716da63246c77ec051591509ae7a01" class="el">GetFactoredRGBFloat</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#edabf03f9243223a1b19ec1b8e6d3a7d" class="el">GetNormalizedRGBFloat</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#99e2887344e07f414aa3a4914e815a45" class="el">ColorBuf</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#12193a668cd16d0e496fee9b99faa33d" class="el">ColorBuf</a> (LONG col)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#a54f386c09bfdd0c512b26ca38752205" class="el">ColorBuf</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pred, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pgreen, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pblue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#f22227be93524420a17d925f89004a08" class="el">ColorBuf</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pred, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pgreen, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pblue, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> palpha)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#78f92abbc4e45930c92b0c17e462b1b0" class="el">ColorBuf</a> (COLORREF c)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#8d9b7ca6430ee525350352f4072e7a2e" class="el">ColorBuf</a> (const <a href="classRGBAFloat.md" class="el">RGBAFloat</a> &amp;<a href="classColorBuf.md#70dda5dfb8053dc6d1c492574bce9bfd" class="el">color</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#3d061051286831d4f2aebae980198b48" class="el">Red</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#eb4e3e708de4af84613f52d0c8067edf" class="el">Green</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#e3b99a5fe15a4330fd055c8b157ee12f" class="el">Blue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#0333130ffc9187bb3ed905eb61d99832" class="el">Alpha</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#619d7deb16927463582495a28b86f235" class="el">Color</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#405027301c008c45770a164fb2f8633b" class="el">Set</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pred, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pgreen, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> pblue, <a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> <a href="classColorBuf.md#2c1743a391305fbf367df8e4f069f9f9" class="el">alpha</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#9094715e2cd64cfe154c5db24096b5f7" class="el">SetRed</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> <a href="classColorBuf.md#bda9643ac6601722a28f238714274da4" class="el">red</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#331230b42dbdf273e6024283cdf3546d" class="el">SetGreen</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> <a href="classColorBuf.md#9f27410725ab8cc8854a2769c7a516b8" class="el">green</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#352554b9fd5ce121b0456448ec6ce711" class="el">SetBlue</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> <a href="classColorBuf.md#48d6215903dff56238e52e8891380c8f" class="el">blue</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#97494d371de239388e6a503b319bf25e" class="el">SetAlpha</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> <a href="classColorBuf.md#2c1743a391305fbf367df8e4f069f9f9" class="el">alpha</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#3112225f31c99e195e7d86ffcf2d45da" class="el">SetColor</a> (<a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> pcolor)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#a021873f9867b21b3e6ea9b95e32cba8" class="el">GammaCorrect</a> (float power)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#bd37cbaf06b0ce675453ece1c22dcb85" class="el">Get</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#3ff93e400445c24a8d552488a6564874" class="el">GetOpacity</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#6574062eb561f53375a793f735b31d74" class="el">Set</a> (const <a href="classRGBFloat.md" class="el">RGBFloat</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md#d540a7f9be1f9038a2b11c24267eb97d" class="el">SetOpacity</a> (const float value)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

