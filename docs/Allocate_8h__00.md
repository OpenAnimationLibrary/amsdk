<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# Allocate.h File Reference

`#include "`<a href="DataType_8h-source.md" class="el"><code>DataType.h</code></a>`"`  
`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  
`#include "`<a href="SingleLo_8h-source.md" class="el"><code>SingleLo.h</code></a>`"`  

Include dependency graph for Allocate.h:

<span class="image placeholder" original-image-src="Allocate_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Allocate.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="Allocate_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Allocate.hdep_map"></span>

[Go to the source code of this file.](Allocate_8h-source.md)

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
&#10;<h2 id="classes">Classes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemChunk.md" class="el">MemChunk</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md" class="el">MemHeader</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md" class="el">HashPool</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimpleChunk.md" class="el">SimpleChunk</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md" class="el">SimplePool</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#2cf59dcb1875526cff6cd24b80ea43aa" class="el">__ALLOCATE_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#e69af83a79737b8f5aad3642baade14d" class="el">HASHNEW</a>   new</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#7faa4e6b5bbbbdc3b5bdf8ac5432403f" class="el">BLOCKSIZE</a>   0x008000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#b851388256af5f1cc695a325c14df8f1" class="el">USEDSIZE</a>   (BLOCKSIZE/sizeof(Patch))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#9595cef45868f476bba77532457279f6" class="el">NUMMEMHEADERS</a>   100</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb" class="el">PoolType</a> {<br />
  <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb4b5856626798f180010feeab64637c59" class="el">POOL_EXT</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadbdb9a638ecf87d641231ef43523675254" class="el">POOL_PATCH</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadbab2f9c09b27d4f475f13247aba5142fb" class="el">POOL_PARTICLE</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb88a896f1f93c09729feb0aa38c9e8dd6" class="el">POOL_BITMAP</a>,<br />
  <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb522b5bafe02446adbbdb42c75fe9b83d" class="el">POOL_SEG</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb60a7543136349842214fe5de33dc7d0c" class="el">POOL_ACT</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb05a6c08eb182407c339a1d47f3d7a727" class="el">POOL_CHOR</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb85e04d906014cf8cd2d7de663764a4ef" class="el">POOL_ATT</a>,<br />
  <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadbd473f8584f245851e181928c7dd64d14" class="el">POOL_TEST</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb16bd278227ed13984cde2ea2b3e55b1a" class="el">POOL_SHADOW</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb9291cf1573f9ff1b072ccb7a09ccf625" class="el">POOL_RADIOSITY</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb593a9bfa68f74f8dad32118f8f8a4786" class="el">POOL_STRING</a>,<br />
  <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb1875af9bce833d69dcb30cb82ddef6f8" class="el">POOL_GASSIST</a>, <a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb5bb425fa5fbcc1db70ac7983dd57c639" class="el">POOL_LBUFF</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#58da147528ef57c2ce313d9e44ead08e" class="el">AllocAct</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#ea258f961bd5e1b1ee941d051f1c9c42" class="el">AllocChor</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#66a3f82098ca891d0d8e11e33a48b54c" class="el">AllocAtt</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#8a7580d6e6f53fa9296b05144347b57e" class="el">AllocSeg</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#0edaf122805c62166f9ca67288ff9bc9" class="el">AllocExt</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#6d40ba5dacc7357c74493239d46318a4" class="el">AllocBitmap</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#8e2fd6072fdac9cf115e18da312ce9c6" class="el">AllocParticle</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#c770a0f50a045f966f52ffe7e3153f40" class="el">AllocPatch</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#b0e794de94453857a722b1b7ce28050f" class="el">AllocLBuff</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#45225fd873373e87c1cb13c19e481ec8" class="el">AllocTest</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#fafd35250ea934dedc69dbeeb4b6eea9" class="el">AllocShadow</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#841b41a032d4e5e625ed4be8f9bad5b6" class="el">AllocString</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#81c901cf4521b9c29c4891a19cb0ab9d" class="el">AllocRadiosity</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#d9bd82c60ab1b8f479c9b0ea9d7138c2" class="el">AllocGAssist</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#061af102f0e33bebfc6ef475797d363e" class="el">FreeAct</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#22a866301e95e532031fb814f30ccfc9" class="el">FreeChor</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#e40f4f61dc48a962d255a67edec0222d" class="el">FreeAtt</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#5f3e3821b4c828e4cf67206a4e6e79f0" class="el">FreeSeg</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#7fc37b7be38d47c3198070a04aef55ac" class="el">FreeExt</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#403ff1dad347d283554aa778bf94b6c5" class="el">FreeBitmap</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#fcf30fba000a9b94f32075bbd3325a2d" class="el">FreeParticle</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#eb66cf840fe170f92ce21b21ab544f71" class="el">FreePatch</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#757fa6342edf399539ebe8e327438b5f" class="el">FreeLBuff</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#392afdb4c512beb7db1d8c7e5521800d" class="el">FreeTest</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#88c3b6374251009e5e9564a3eadb9650" class="el">FreeShadow</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#ac511c2f2cc822f2a004301ee08cbfc7" class="el">FreeString</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#399cbb36d7bdf0fbba14db2a1db8167f" class="el">FreeRadiosity</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#ca8bf61f9421d5d33252ac89ab143ae3" class="el">FreeGAssist</a> (void *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#858355a760f1f4ebe2e6cffcb5325384" class="el">AllocZ</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#9d60630326579e10e35423c2de4f9e46" class="el">AllocSubPatch</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#321a9f4060db855224ca6cc73411615f" class="el">FreeSubPatchMemory</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#b6581c72bb8cc3357487005594cb57d7" class="el">FreeZBufferMemory</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Allocate_8h.md#d0f319016ecc46039ae58b204a0e65bd" class="el">FreePatchMemory</a> ()</td>
</tr>
<tr>
<td class="memIt