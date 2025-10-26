>typedef </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#9e6a6d542a0c41db986e70cd76114f63" class="el">void</a> (RAVE_CALLBACK *TQASetFloat)(<a href="structTQADrawContext.md" class="el">TQADrawContext</a> *drawContext</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float</a> (RAVE_CALLBACK *TQAGetFloat)(const <a href="structTQADrawContext.md" class="el">TQADrawContext</a> *drawContext</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#00098632eb05dfb3bb11ef7c6bf90c00" class="el">TQAError</a> (RAVE_CALLBACK *TQARenderEnd)(const <a href="structTQADrawContext.md" class="el">TQADrawContext</a> *drawContext</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#96e714e5116fd8025c3c90491f3aa9a6" class="el">QADrawContextNew</a> (const <a href="structTQADevice.md" class="el">TQADevice</a> *device, const <a href="structTQARect.md" class="el">TQARect</a> *rect, const <a href="structTQAClip.md" class="el">TQAClip</a> *clip, const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, <a href="structTQADrawContext.md" class="el">TQADrawContext</a> **newDrawContext)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#4fbbd0d48e53f93df04d463ad874eec3" class="el">QADrawContextDelete</a> (<a href="structTQADrawContext.md" class="el">TQADrawContext</a> *drawContext)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#1cf1867e34b9f7d069b28ef2446ad69e" class="el">QAColorTableNew</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#7fa401cbca28d63a24ec23212d9791fe" class="el">TQAColorTableType</a> tableType, void *pixelData, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> transparentIndexFlag, <a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> **newTable)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#5c55980ee2f6eb31aef3af60d7d11c1f" class="el">QAColorTableDelete</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> *colorTable)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#5ec67a55bcf12fa265cf4fa06b05eefc" class="el">QATextureNew</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f514" class="el">TQAImagePixelType</a> pixelType, const <a href="structTQAImage.md" class="el">TQAImage</a> images[], <a href="Rave_8h.md#5beaf91662dd1191af467f0c97bbfd5b" class="el">TQATexture</a> **newTexture)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#63e3ddc86f73940d790795fff4f08d52" class="el">QATextureDetach</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#5beaf91662dd1191af467f0c97bbfd5b" class="el">TQATexture</a> *texture)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#ac4b14f6b8a21963d9871992a83587d4" class="el">QATextureDelete</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#5beaf91662dd1191af467f0c97bbfd5b" class="el">TQATexture</a> *texture)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#de254f5538d57fb56f359fb505b00785" class="el">QATextureBindColorTable</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#5beaf91662dd1191af467f0c97bbfd5b" class="el">TQATexture</a> *texture, <a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> *colorTable)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#8ecca1d9a350f09a45af22bfdbf1c4e0" class="el">QABitmapNew</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f514" class="el">TQAImagePixelType</a> pixelType, const <a href="structTQAImage.md" class="el">TQAImage</a> *image, <a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> **newBitmap)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#3b097b19bfb17bee5ae477633555ed39" class="el">QABitmapDetach</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> *<a href="Rave_8h.md#86bb33755628454af74f88f047ec894a" class="el">bitmap</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT void RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#f484bd57d94f46a24223bccd18d5e232" class="el">QABitmapDelete</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> *<a href="Rave_8h.md#86bb33755628454af74f88f047ec894a" class="el">bitmap</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#b09bd534354a6e1f272fba4b7033a9ad" class="el">QABitmapBindColorTable</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#a6de8bcf13e6cac0f5ed818fe0c9d1af" class="el">TQABitmap</a> *<a href="Rave_8h.md#86bb33755628454af74f88f047ec894a" class="el">bitmap</a>, <a href="Rave_8h.md#def7f4317fdcb0655d351ec5aeeee2ee" class="el">TQAColorTable</a> *colorTable)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#e4606c40580d8c17f319c1f2cf33b9b1" class="el">QADeviceGetFirstEngine</a> (const <a href="structTQADevice.md" class="el">TQADevice</a> *device)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#baadb969a4f608b6ac47ff8076cfe5d1" class="el">QADeviceGetNextEngine</a> (const <a href="structTQADevice.md" class="el">TQADevice</a> *device, const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *currentEngine)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#23ed40284ae2fce88c14f6db010ca0f1" class="el">QAEngineCheckDevice</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, const <a href="structTQADevice.md" class="el">TQADevice</a> *device)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#4a307d1c586479ff50119f1a3ab8994b" class="el">QAEngineGestalt</a> (const <a href="Rave_8h.md#586d82c6919b40cc1d895dca958a2123" class="el">TQAEngine</a> *engine, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a019" class="el">TQAGestaltSelector</a> selector, void *response)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#23370b1a207d0853ca8fd86f6cb30c9a" class="el">QAEngineEnable</a> (<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> vendorID, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> engineID)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">RAVE_EXPORT <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> RAVE_CALL </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#e3228050b47c1531c2adedfbbbe031f2" class="el">QAEngineDisable</a> (<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> vendorID, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> engineID)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

