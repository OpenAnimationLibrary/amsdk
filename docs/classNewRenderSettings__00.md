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

# NewRenderSettings Class Reference

`#include <`<a href="RenderS2_8h-source.md" class="el"><code>RenderS2.h</code></a>`>`

[List of all members.](classNewRenderSettings-members.md)

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
  <a href="classNewRenderSettings.md#dca29a1140aadadfd92b34a02fa516ef2d957f30f3048db573ce1799d245eb6b" class="el">RQ_DEFAULT</a>, <a href="classNewRenderSettings.md#dca29a1140aadadfd92b34a02fa516ef337ba490a4ad987373c622fc624a6936" class="el">RQ_WIREFRAME</a>, <a href="classNewRenderSettings.md#dca29a1140aadadfd92b34a02fa516ef149590a18d326480858e362940e010ce" class="el">RQ_SHADED</a>, <a href="classNewRenderSettings.md#dca29a1140aadadfd92b34a02fa516efd49ea05ea06f285dc5af9a4e0d04cdd5" class="el">RQ_SHADEDWIREFRAME</a>,<br />
  <a href="classNewRenderSettings.md#dca29a1140aadadfd92b34a02fa516eff17761801664016441f851bd006c8103" class="el">RQ_FINAL</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300cb7d457cdafacd0027c8fb4285894839" class="el">MP_1</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a73008ab6e8123881bbb0af62846bc69ca70b" class="el">MP_2</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a73009dc26e7189c346588ede67b5727d8d44" class="el">MP_3</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a73008de200f55699f7989c77bbe71c69f6fb" class="el">MP_4</a>,<br />
  <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a73003053463fc6560ef139f06869a1cd2d93" class="el">MP_5</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300da84b6242d3181a0fb30166e6bccffd3" class="el">MP_9</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a730032e3bd02f358f35018da9e1dbec04ec1" class="el">MP_16</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300d2289afd16c6d88f2684c35b3c37f7a9" class="el">MP_25</a>,<br />
  <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300d40db72ec9e3d868cb8a63f5a0aeab31" class="el">MP_36</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a73009c82efb8a348fcd612e588aaf55b8f1d" class="el">MP_49</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300d5a1dcf2d9dd13e15ce035265cc7bd97" class="el">MP_64</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a730027cb13b918565c8cdaee1b0e0052f1b3" class="el">MP_81</a>,<br />
  <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a73004be3f9488517cb2f15db85f6339ffe40" class="el">MP_100</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300fd80e1eeac0c2bddfd8126cde144dbdf" class="el">MP_121</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300038503e0a9586d733cc988d6671c3918" class="el">MP_144</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300afbaa5eff2950882026fb5e58d9059a5" class="el">MP_169</a>,<br />
  <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300fe0b85d6420e922963350f28c2bc2ce1" class="el">MP_196</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300b348f78fd189b5fd0448688cf2844fd9" class="el">MP_225</a>, <a href="classNewRenderSettings.md#68986ab776eb5d6b5a809a1c005a7300c9039ce948893d425442f8f97f9fee5a" class="el">MP_256</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#02653d87b6fa8554fc0d1a3726fea2d07b9eb147e69be5e39f157016d4d69a4f" class="el">FIELD_ODD</a>, <a href="classNewRenderSettings.md#02653d87b6fa8554fc0d1a3726fea2d01d1d0d6fa2fe2e24fb523be34169b2a1" class="el">FIELD_EVEN</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#1378d7d8767899287b0407055215aa4e85a4c330421cf51c6d89e5141d11edbc" class="el">FREEVIEWING</a>, <a href="classNewRenderSettings.md#1378d7d8767899287b0407055215aa4eb494225fa270f1c5339857dcf0e7c617" class="el">ANAGLYPH</a>, <a href="classNewRenderSettings.md#1378d7d8767899287b0407055215aa4e8472c10b48f63928211bd72d1888071f" class="el">INTERLACED</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#a4d79cb252987ad7f099770543e601a1df13a99b035d6f0bce4f44ab18eec8eb" class="el">PARALLEL</a>, <a href="classNewRenderSettings.md#a4d79cb252987ad7f099770543e601a1470c9adffe4ffd7e3c6831d2e1f3a40b" class="el">CROSSEYED</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#e80230e7c0b67771dddc6a497e5e2e5ed6fd5c9dacdc958a3f2a3424cea07444" class="el">ANAGLYPHPURE</a>, <a href="classNewRenderSettings.md#e80230e7c0b67771dddc6a497e5e2e5ee1db842658b1f41527af29ee4c65cf44" class="el">ANAGLYPHGREY</a>, <a href="classNewRenderSettings.md#e80230e7c0b67771dddc6a497e5e2e5e197343bafd035dda410c85206b688c7f" class="el">ANAGLYPHCOLOR</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#21945c50944818f4cf3b6aef8608f9cee93dc695f4f3d8385e721c4e7fee7982" class="el">REDBLUE</a>, <a href="classNewRenderSettings.md#21945c50944818f4cf3b6aef8608f9ced603bc82e658b9fae3c16cc8536266f9" class="el">BLUERED</a>, <a href="classNewRenderSettings.md#21945c50944818f4cf3b6aef8608f9ceb4a9b83ddd3c36151742fc6015ed6d82" class="el">REDGREEN</a>, <a href="classNewRenderSettings.md#21945c50944818f4cf3b6aef8608f9ce6fbad430c224759c75210682df1fabe7" class="el">GREENRED</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#60e3c12db6ddaae1f88a6e0e8d5118e0e603876a1601e97a6a31ceb3262153d0" class="el">INTERLACE_LEFT</a>, <a href="classNewRenderSettings.md#60e3c12db6ddaae1f88a6e0e8d5118e084fa4a16db1783c2cfc26431ab816527" class="el">INTERLACE_RIGHT</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#63f5f87eab8bf5d1395b98caa0a448ba4ba6fcb4e20cc4f7c3c7cb07d6de2135" class="el">SUB_1</a>, <a href="classNewRenderSettings.md#63f5f87eab8bf5d1395b98caa0a448ba96092d27de975b38f6782f5ef906d6a9" class="el">SUB_4</a>, <a href="classNewRenderSettings.md#63f5f87eab8bf5d1395b98caa0a448ba7fe9a7bb4aacb1438461303ec2da69eb" class="el">SUB_16</a>, <a href="classNewRenderSettings.md#63f5f87eab8bf5d1395b98caa0a448ba587fabfb3cb3b291b6d8bacbeb004556" class="el">SUB_ADAPTIVE</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classNewRenderSettings.md#bdca477a0c8312f3fd1c917c21d567cb254dbcc720d70dd411f2e720a938962f" class="el">GRAIN_NONE</a>, <a href="classNewRenderSettings.md#bdca477a0c8312f3fd1c917c21d567cb387cad9c4bae8825ad53ad51ea37c655" class="el">GRAIN_100ASA</a>, <a href="classNewRenderSettings.md#bdca477a0c8312f3fd1c917c21d567cb5759b99286dc38722ca5a1e3f776c151" class="el">GRAIN_200ASA</a>, <a href="classNewRenderSettings.md#bdca477a0c8312f3fd1c917c21d567cb2423a13ff2965f4a8ecea2152add5382" class="el">GRAIN_400ASA</a>,<br />
  <a href="classNewRenderSettings.md#bdca477a0c8312f3fd1c917c21d567cbd507e8c13605adabec35ff1c7b6fd42c" class="el">GRAIN_CUSTOM</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#292e4a2c5dcece13fd75f0a1bc0a4dbe6b2c7a435eb21bae525d54968b8f754e" class="el">BLOOM_NONE</a>, <a href="classNewRenderSettings.md#292e4a2c5dcece13fd75f0a1bc0a4dbec853537d908dd428df083b8c79927148" class="el">BLOOM_DAY</a>, <a href="classNewRenderSettings.md#292e4a2c5dcece13fd75f0a1bc0a4dbe0e0f4f101695d658af89d306c1c7d477" class="el">BLOOM_NIGHT</a>, <a href="classNewRenderSettings.md#292e4a2c5dcece13fd75f0a1bc0a4dbeb065a3a001a39f7bea3d5f09018d1080" class="el">BLOOM_CUSTOM</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classNewRenderSettings.md#4f465ceb1b510107884ceaee7abcd0f41966396f6c9bdc4a36205319138ea5bf" class="el">TINT_NONE</a>, <a href="classNewRenderSettings.md#4f465ceb1b510107884ceaee7abcd0f4f05420646ca14cb8fd8dace58da1c0b3" class="el">TINT_BW</a>, <a href="classNewRenderSettings.md#4f465ceb1b510107884ceaee7abcd0f4451148d4a695f5f6f681023c0c7028a1" class="el">TINT_COBALT</a>, <a href="classNewRenderSettings.md#4f465ceb1b510107884ceaee7abcd0f4b400a7c59cfe7d2d3a89142154794672" class="el">TINT_SEPIA</a>,<br />
  <a href="classNewRenderSettings.md#4f465ceb1b510107884ceaee7abcd0f42a938128c21d3ff63f1e2a89d332c2fa" class="el">TINT_XRAY</a>, <a href="classNewRenderSettings.md#4f465ceb1b510107884ceaee7abcd0f4e425c3f944556951794c407a9f5bc62b" class="el">TINT_CUSTOM</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classNewRenderSettings.md#c8afa25b694ce89e7c6f15b35f6d9368aa963d3fc2deab5633f218e0405ea4b2" class="el">SOFTEN_NONE</a>, <a href="classNewRenderSettings.md#c8afa25b694ce89e7c6f15b35f6d9368cc46913ece90b4161b06333794aaaa78" class="el">SOFTEN_8MM</a>, <a href="classNewRenderSettings.md#c8afa25b694ce89e7c6f15b35f6d93682b62b833a3a9b6cd718192588dd006f2" class="el">SOFTEN_16MM</a>, <a href="classNewRenderSettings.md#c8afa25b694ce89e7c6f15b35f6d9368af4b9531552accc6c533c59b081cd7fa" class="el">SOFTEN_35MM</a>,<br />
  <a href="classNewRenderSettings.md#c8afa25b694ce89e7c6f15b35f6d9368f75e6250cee5ed9e0a7744859b088729" class="el">SOFTEN_CUSTOM</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="classNewRenderSettings.md#bdf416144f79b0adea50b8078e2b2c7fe5c51e31b141e3dbf241b3283b7ff7e4" class="el">GAMMA_NONE</a>, <a href="classNewRenderSettings.md#bdf416144f79b0adea50b8078e2b2c7f0d19b9dfc20b6d2fd69ad182ac0a0622" class="el">GAMMA_MONITOR</a>, <a href="classNewRenderSettings.md#bdf416144f79b0adea50b8078e2b2c7f5b3a431f4a4ddbeb31d3572695f03a63" class="el">GAMMA_NTSC</a>, <a href="classNewRenderSettings.md#bdf416144f79b0adea50b8078e2b2c7f1efa0d931e29c0486013f47166169998" class="el">GAMMA_CUSTOM</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#e7a0f1af7aa4e8ae50e8bda79e68f045" class="el">NewRenderSettings</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#a87a50db2c28abeae51334d425ecf199" class="el">NewRenderSettings</a> (<a href="classNewRenderSettings.md" class="el">NewRenderSettings</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#7c5a6905a76ab54343d66d3c246320e3" class="el">~NewRenderSettings</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#82357f0909d7b3f9aaac68bcf9463b65" class="el">Init</a> (PropertyInfo *propertyinfo, TreeObject *parent=NULL, BOOL isnull=FALSE, BOOL isloadpropertyinfo=FALSE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#9d74f924ab10c32462e7f82ed5bd060f" class="el">MyInit</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classNewRenderSettings.md" class="el">NewRenderSettings</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#82e77156df426c08740ee52f0041b7b7" class="el">operator=</a> (<a href="classNewRenderSettings.md" class="el">NewRenderSettings</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#b6822691011ea75957ee91dfbc391831" class="el">SetNumPassesFromProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual Property * </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#f05155d66a18c82acfa7d871654a2cb2" class="el">MakeCopy</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#d31ccd86a67ca3a180f26c58bdb80065" class="el">Copy</a> (const Property *property)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual Property * </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">GetPropertyAt</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRigh