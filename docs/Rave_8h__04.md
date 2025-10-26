a1623cbb1ddf0aecd7631bc2b13" class="el">TQAMethodSelector</a> method, <a href="unionTQANoticeMethod.md" class="el">TQANoticeMethod</a> *completionCallBack, void **refCon)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef enum <a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a0" class="el">TQAVersion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a0" class="el">TQAVersion</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f514" class="el">TQAImagePixelType</a> {<br />
  <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f51489b2f80d406c877aa44c130930cfacf6" class="el">kQAPixel_Alpha1</a> = 0, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f51452d24346e663efb7b0d7523522fea218" class="el">kQAPixel_RGB16</a> = 1, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f514034135ee73fb577b09225261e4b44e55" class="el">kQAPixel_ARGB16</a> = 2, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f51432b04207d260a211be198ac747efb397" class="el">kQAPixel_RGB32</a> = 3,<br />
  <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f51453b38ece8f822d347b362997102bfe59" class="el">kQAPixel_ARGB32</a> = 4, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f51446184baa00907a3a1ef767ff1666bac9" class="el">kQAPixel_CL4</a> = 5, <a href="Rave_8h.md#ed246a3940fe2a0a06c7c5610753f514d92af2cd3b701a5d713326e4dd13eb0b" class="el">kQAPixel_CL8</a> = 6<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#7fa401cbca28d63a24ec23212d9791fe" class="el">TQAColorTableType</a> { <a href="Rave_8h.md#7fa401cbca28d63a24ec23212d9791fe14be9ac0a09dc8dac85bbc78f59a3a73" class="el">kQAColorTable_CL8_RGB32</a> = 0, <a href="Rave_8h.md#7fa401cbca28d63a24ec23212d9791fef43b49e0405c58348ec8414eab6dd342" class="el">kQAColorTable_CL4_RGB32</a> = 1 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#1674022bdc8f7bb2549d30d43ac2e1b8" class="el">TQADeviceType</a> { <a href="Rave_8h.md#1674022bdc8f7bb2549d30d43ac2e1b8c07a5b1f1520d7bdfd44b6db2ca59647" class="el">kQADeviceMemory</a> = 0, <a href="Rave_8h.md#1674022bdc8f7bb2549d30d43ac2e1b8e3bc6fab7b37f9cd6781d698f16e8fb3" class="el">kQADeviceGDevice</a> = 1, <a href="Rave_8h.md#1674022bdc8f7bb2549d30d43ac2e1b82fc1be14bf68dc7ddd39303373f72d25" class="el">kQADeviceWin32DC</a> = 2, <a href="Rave_8h.md#1674022bdc8f7bb2549d30d43ac2e1b8d48f4a3a8dddf8c71305487139870451" class="el">kQADeviceDDSurface</a> = 3 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#9ef329d8abd4137fad376699bb99c2a3" class="el">TQAClipType</a> { <a href="Rave_8h.md#9ef329d8abd4137fad376699bb99c2a33c6286b57704155c006a5d6515e25ea3" class="el">kQAClipRgn</a> = 0, <a href="Rave_8h.md#9ef329d8abd4137fad376699bb99c2a37df1ff89e54b06f3782e0ca906567691" class="el">kQAClipWin32Rgn</a> = 1 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651" class="el">TQAError</a> {<br />
  <a href="Rave_8h.md#8966c3d78d6696fa08236778d072265106143473110c96def9cabcbeaa9a99d4" class="el">kQANoErr</a> = 0, <a href="Rave_8h.md#8966c3d78d6696fa08236778d072265109c340adbbc78735fd0d8d3decfc2236" class="el">kQAError</a> = 1, <a href="Rave_8h.md#8966c3d78d6696fa08236778d07226510a8cfb435d32877d3b94507d73585889" class="el">kQAOutOfMemory</a> = 2, <a href="Rave_8h.md#8966c3d78d6696fa08236778d07226510b515256e7a20789e6727322bb6db383" class="el">kQANotSupported</a> = 3,<br />
  <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651274af5586b89bf678446e018c2a39d0f" class="el">kQAOutOfDate</a> = 4, <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651122e5e1ab9dfcc3f1df46666483ffc52" class="el">kQAParamErr</a> = 5, <a href="Rave_8h.md#8966c3d78d6696fa08236778d07226515fcde1f83544f14b9c0b80e0ef544fed" class="el">kQAGestaltUnknown</a> = 6, <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651dd1fb05767577804662f47aac2556e1e" class="el">kQADisplayModeUnsupported</a> = 7,<br />
  <a href="Rave_8h.md#8966c3d78d6696fa08236778d0722651bd777f3867f383158f65af2b5f1bbdcd" class="el">kQAOutOfVideoMemory</a> = 8<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d" class="el">TQATagInt</a> {<br />
  <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d6e704519455128ca27591e25dc61b173" class="el">kQATag_ZFunction</a> = 0, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dc5f11324f35b189272b9ddf155e87615" class="el">kQATag_Antialias</a> = 8, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d48589f0997321185f4fe41f3218e0f7c" class="el">kQATag_Blend</a> = 9, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d540263d049fc201bd5178ccee4e98565" class="el">kQATag_PerspectiveZ</a> = 10,<br />
  <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d0cdd74643518ffbfb2fae279ad2d18bb" class="el">kQATag_TextureFilter</a> = 11, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d2f9c1680935f6fbc8828e7abe36a3204" class="el">kQATag_TextureOp</a> = 12, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dc7825e89432f70dd20aa2bc298e8b802" class="el">kQATag_CSGTag</a> = 14, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d64b0477b6500ffeb55b7095339049aea" class="el">kQATag_CSGEquation</a> = 15,<br />
  <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4de76eafb75b9b3d0681f940f869855bc3" class="el">kQATag_BufferComposite</a> = 16, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dae7cb96ef7878e0d2e3c44935acb962f" class="el">kQATagGL_DrawBuffer</a> = 100, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d81da8ff5e474b3435d3eadda48566649" class="el">kQATagGL_TextureWrapU</a> = 101, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dcedc21672325902e3e24dfe74fb6e763" class="el">kQATagGL_TextureWrapV</a> = 102,<br />
  <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d76d99cc9292c970e7f5d99125935b7a5" class="el">kQATagGL_TextureMagFilter</a> = 103, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d421665b1326a63d4c11e1fa41d17ad2f" class="el">kQATagGL_TextureMinFilter</a> = 104, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d1ca31176cadf6952f4a20ffacd67d668" class="el">kQATagGL_ScissorXMin</a> = 105, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d0726d8df076e03a515e61aba551b639e" class="el">kQATagGL_ScissorYMin</a> = 106,<br />
  <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4db5fc581f3e25831378485382cb98a1da" class="el">kQATagGL_ScissorXMax</a> = 107, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dcd0f57633b3f75c6b6b9eb2b0d333244" class="el">kQATagGL_ScissorYMax</a> = 108, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d2f2344270d811027252657d40f125a87" class="el">kQATagGL_BlendSrc</a> = 109, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dc6cae9cfe77069cb85aa791da4eeed41" class="el">kQATagGL_BlendDst</a> = 110,<br />
  <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4df44189f13dc55dd635e3f23787012790" class="el">kQATagGL_LinePattern</a> = 111, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4d02ec0e55af2e532f58d3170d93edfcc0" class="el">kQATagGL_AreaPattern0</a> = 117, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4dc030e0a0d1f4f29b268ddc1da581a9d4" class="el">kQATagGL_AreaPattern31</a> = 148, <a href="Rave_8h.md#9e1b169f70a8ee087bd3bb218d59bf4de7191ffac18178b67d68a64c5b62286d" class="el">kQATag_EngineSpecific_Minimum</a> = 1000<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#7eb86053655f24fdee134ba846b7f554" class="el">TQATagPtr</a> { <a href="Rave_8h.md#7eb86053655f24fdee134ba846b7f5543bb5871e7b8b2c5c5f32f24c9fc0d37b" class="el">kQATag_Texture</a> = 13 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc9019726" class="el">TQATagFloat</a> {<br />
  <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972631e855bf5a7f0152294cbc7fae61a33e" class="el">kQATag_ColorBG_a</a> = 1, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc9019726b6dbb2e5b701e46b31c868c2f1251264" class="el">kQATag_ColorBG_r</a> = 2, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972672438d7a132b18301e77a6e7ea549275" class="el">kQATag_ColorBG_g</a> = 3, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972622301cccbafe4e6f1c9ccdd2b2630d90" class="el">kQATag_ColorBG_b</a> = 4,<br />
  <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972637bb60798f878779f29f6fe1892c74ef" class="el">kQATag_Width</a> = 5, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972696673ce159b9845bbc1dcf5a2c6e9393" class="el">kQATag_ZMinOffset</a> = 6, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972610b3c656a7deb9d0ea3e468335678c77" class="el">kQATag_ZMinScale</a> = 7, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc90197266f1c93f12d287573d22ec8b1873c60ba" class="el">kQATagGL_DepthBG</a> = 112,<br />
  <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc9019726f5196c9bc12b2884a5fd98d71a79f508" class="el">kQATagGL_TextureBorder_a</a> = 113, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972616c425725d2555ac19c055a63f3abbbd" class="el">kQATagGL_TextureBorder_r</a> = 114, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc9019726de7ee17bd3f1ad603e926649c1f8ae7b" class="el">kQATagGL_TextureBorder_g</a> = 115, <a href="Rave_8h.md#2beafd34351cfbd5cdd4527bc901972694d32b8f93c1cf5c6de58f46420b190a" class="el">kQATagGL_TextureBorder_b</a> = 116<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc" class="el">TQAVertexMode</a> {<br />
  <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc6185c7f56898b7117e3dcc3c1bb61b56" class="el">kQAVertexMode_Point</a> = 0, <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc581dd1a9622895ba00ff65f3790c44ec" class="el">kQAVertexMode_Line</a> = 1, <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc2e8b390abd5c669453c6027be8b18f09" class="el">kQAVertexMode_Polyline</a> = 2, <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc2f916c80751d306e1e080befebab0045" class="el">kQAVertexMode_Tri</a> = 3,<br />
  <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc6e8aa86beed462b5b8168c955787fbe4" class="el">kQAVertexMode_Strip</a> = 4, <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fcdd3327eaf4ddf10252825606c963cf0d" class="el">kQAVertexMode_Fan</a> = 5, <a href="Rave_8h.md#3720fb6190a2015baa1feb54efb798fc87d1e327d68612d8dd27e4f1cf47b8ad" class="el">kQAVertexMode_NumModes</a> = 6<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a019" class="el">TQAGestaltSelector</a> {<br />
  <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a01941d4201fdd7e243e09f634062f39678d" class="el">kQAGestalt_OptionalFeatures</a> = 0, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a019b08530cf9d66237a1abefc2ba6f708d3" class="el">kQAGestalt_FastFeatures</a> = 1, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a0191147d4bb68e8199fb0b1bebba2df7e59" class="el">kQAGestalt_VendorID</a> = 2, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a0198b752c55c48ecc8b3a0be012ca841b2c" class="el">kQAGestalt_EngineID</a> = 3,<br />
  <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a0193d0db7b4a0b811e42fc8b8298fbe36e0" class="el">kQAGestalt_Revision</a> = 4, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a019b72b5beef7ae8c8278c331a15bbe354a" class="el">kQAGestalt_ASCIINameLength</a> = 5, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a0193bd238ff4093cf0e4218d1166f898c76" class="el">kQAGestalt_ASCIIName</a> = 6, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a019dc9238d5a868f5200aa0720ce2df224c" class="el">kQAGestalt_TextureMemory</a> = 7,<br />
  <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a01989dc11e7ca72806403a0d56f1c51af9f" class="el">kQAGestalt_FastTextureMemory</a> = 8, <a href="Rave_8h.md#7e0f655649277a2cba527fe9dc84a0196279afa5bacc1ced36a1f1ca997d4c94" class="el">kQAGestalt_NumSelectors</a> = 9<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b13" class="el">TQAMethodSelector</a> {<br />
  <a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b13fe15dfc00658fe7f3ed328a45dfef8ee" class="el">kQAMethod_RenderCompletion</a> = 0, <a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b1388bb20bdc09bd4e7fa074efabd5a1bbb" class="el">kQAMethod_DisplayModeChanged</a> = 1, <a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b13ebf685b1b9ee4b0d8f8887dd8fa9b4e5" class="el">kQAMethod_ReloadTextures</a> = 2, <a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b13e042a6e5e7fd6e54f75da096fe9a4d8c" class="el">kQAMethod_BufferInitialize</a> = 3,<br />
  <a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b132723d6f944f67efa434308c0b1960909" class="el">kQAMethod_BufferComposite</a> = 4, <a href="Rave_8h.md#80f59a1623cbb1ddf0aecd7631bc2b134588a964866a06c184c99f43f53bafa4" class="el">kQAMethod_NumSelectors</a> = 5<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a0" class="el">TQAVersion</a> { <a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a05caec6a8bac22921b6c0f7202931435b" class="el">kQAVersion_Prerelease</a> = 0, <a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a01fb457a30f4d8d7c28034ecd49bd57a9" class="el">kQAVersion_1_0</a> = 1, <a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a00ffe0ae72c2c71b97f5c9c0b2adcdf3b" class="el">kQAVersion_1_0_5</a> = 2, <a href="Rave_8h.md#d73b82c928c7a4d6eaf2b7f4ddd0d8a0bf373bcde02304cf592825a73b5c1015" class="el">kQAVersion_1_5</a> = 3 }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"