ody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHook2</td>
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

|     |                                                        |
|-----|--------------------------------------------------------|
|     | The vertex is the end of an IsUseHook2 spline segment. |

<span id="e07c8f5ec105286f9993a4543e163caa" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHook3</td>
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

|     |                                                        |
|-----|--------------------------------------------------------|
|     | The vertex is the end of an IsUseHook3 spline segment. |

<span id="de47c4dfe12f9016466bbcdafb0186e1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHook4</td>
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

|     |                                                        |
|-----|--------------------------------------------------------|
|     | The vertex is the end of an IsUseHook4 spline segment. |

<span id="11a44ab0e1b5c5bdf9f9c2cd0694a9ba" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHookData1</td>
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
<td><p>If TRUE, this vertex is a hook</p>
<p>if IsHookData1 is set then</p>
<p>if it is an end hook ( its IsEndHook1 flag is set ), calling GetNextAttached(), will yield the base CP of the spline that the vertex is hooked into. If the vertex is not an end hook, calling GetNextAttached() will yield the next hook down the spline.</p></td>
</tr>
</tbody>
</table>

<span id="5419ea42e58303886a23c07e1caf6ed1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHookData2</td>
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
<td><dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#11a44ab0e1b5c5bdf9f9c2cd0694a9ba" class="el">HPatch::IsHookData1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="0196853fd3e3e1905330eac41fedfc5c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHookData3</td>
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
<td><dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#11a44ab0e1b5c5bdf9f9c2cd0694a9ba" class="el">HPatch::IsHookData1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="880661963ef3dc3ca7d8f145304659a5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsHookData4</td>
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
<td><dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#11a44ab0e1b5c5bdf9f9c2cd0694a9ba" class="el">HPatch::IsHookData1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="e13c5507444e41172dcfca5e95d81d42" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsUseHook1</td>
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
<td><p>If TRUE, an adjacent vertex is a hook, or this vertex is a hook. You may not be able to traverse to the next vertex, or the previous from this vertex.</p>
<p>If IsUseHook1 is set then</p>
<p>if the next vertex's IsHookData1 flag is set, it is a hook, and you cannot traverse to it. another way of getting the Out Tangent "A" must be found</p>
<p>1) The next vertex may be a hook--find out by calling <a href="classHPatch.md#11a44ab0e1b5c5bdf9f9c2cd0694a9ba" class="el">IsHookData1()</a> on it.</p>
<p>1.1) If the next vertex is a hook, then you can determine which direction the connecting spline runs by calling <a href="classHPatch.md#b3d0473868d3d6ba7b65627c42755a07" class="el">IsEndHook1()</a> on it. If the call returns a true value, then the spline is coming into the current vertex.</p>
<p>2) The previous vertex may be a hook--find out by calling <a href="classHPatch.md#11a44ab0e1b5c5bdf9f9c2cd0694a9ba" class="el">IsHookData1()</a> on it</p>
<p>2.1) If the previous vertex is a hook, then you can determine which direction the connecting spline runs by calling <a href="classHPatch.md#b3d0473868d3d6ba7b65627c42755a07" class="el">IsEndHook1()</a> to it. If the call returns a true value, then the spline is coming into the currnet vertex.</p>
<p>3) The current vertex may be a hook--find out by calling <a href="classHPatch.md#b3d0473868d3d6ba7b65627c42755a07" class="el">IsEndHook1()</a> on the current vertex</p></td>
</tr>
</tbody>
</table>

<span id="44515e7ea3cc6708dc5641de8f74e423" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsUseHook2</td>
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
<td><dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#e13c5507444e41172dcfca5e95d81d42" class="el">HPatch::IsUseHook1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="aabcf1ad5223a3ca6bce709cb4fbbf94" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsUseHook3</td>
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
<td><dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#e13c5507444e41172dcfca5e95d81d42" class="el">HPatch::IsUseHook1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="fcdf153fe19fe0b6f20a2d7793eddada" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch::IsUseHook4</td>
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
<td><dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#e13c5507444e41172dcfca5e95d81d42" class="el">HPatch::IsUseHook1()</a>
</dd>
</dl></td>
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
<td class="md" data-nowrap="" data-valign="top">void HPatch::operator delete</td>
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

|  |  |
|----|----|
|   | Definition at line <a href="HPatch_8h-source.md#l00056" class="el">56</a> of file <a href="HPatch_8h-source.md" class="el">HPatch.h</a>. |

<span id="97dc84e27b5fae2c56a3aa58679244e5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HPatch::ReverseNormal</td>
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

|     |                                   |
|-----|-----------------------------------|
|     | Reverses the normal on the patch. |

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPatch_8h-source.md" class="el">HPatch.h</a>
- C:/Dox/SDK/Comments/<a href="HPatch_8dox.md" class="el">HPatch.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:56 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
