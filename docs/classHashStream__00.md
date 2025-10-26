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

# HashStream Class Reference

`#include <`<a href="HashFile_8h-source.md" class="el"><code>HashFile.h</code></a>`>`

Inheritance diagram for HashStream:

<span class="image placeholder" original-image-src="classHashStream__inherit__graph.gif" original-image-title="" border="0" usemap="#HashStream__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HashStream:

<span class="image placeholder" original-image-src="classHashStream__coll__graph.gif" original-image-title="" border="0" usemap="#HashStream__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHashStream-members.md)

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
  <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516efdc85a74fb03315a5269bf43adbd60e74" class="el">HS_STORE</a> = 0, <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516ef87dd1bb846fb3f09903e4d53a477aa05" class="el">HS_LOAD</a> = 1, <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516ef0ba5a3dce5222817d24080ee0121825e" class="el">HS_ASCII</a> = 0, <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516ef0a24c17a7f02f6a0e61f64f6083a2a31" class="el">HS_BINARY</a> = 2,<br />
  <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516ef55cca2eb4b4e12269e3df06cdd28eda6" class="el">HS_BYTESWAP</a> = 4, <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516eff6e052ca1ba72f44efd8b91b8cf486ca" class="el">HS_APPEND</a> = 8, <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516ef4dcf67e4a401ce034e1ef11d3c85a147" class="el">HS_FAILED</a> = 16, <a href="classHashStream.md#dca29a1140aadadfd92b34a02fa516ef0d5021fe206a905fcf2bbf4a1dc0d47c" class="el">HS_HASH</a> = 32<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c" class="el">SeekMode</a> { <a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c548f35d1cedeff150ca6530ac5451a60" class="el">HS_BEGINNING</a>, <a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c88dc12d1c93132f94951a5d9caf95ae8" class="el">HS_END</a>, <a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c7fe0e562e104864af3c7869fb54a9e95" class="el">HS_OFFSET</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#e6fcfc45a311d107944d6bf14635435a" class="el">HashStream</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#6e6077282e5d9048b661a831a88b0157" class="el">~HashStream</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#650118fc0cd96c1cd00cb1243c5e3358" class="el">operator new</a> (size_t size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#b2a90b0840ba0f087728d89d27353935" class="el">operator delete</a> (void *ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#d6250c7bedd41bd6244d5bd066ef9723" class="el">IsLoading</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#99f3dc774a162fd431fad9511de42a70" class="el">IsStoring</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#94977e284e49dc050203510b6574c19c" class="el">IsAppend</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#2407b618828aafa3fddf93a9fe6dcb53" class="el">IsBinary</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#aa9e3a1038c202d0b0a43be670500cb5" class="el">OnBinary</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#626e55657c8d034138ab0337249e1a0c" class="el">IsAscii</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#06aec4adb36fea5da51cfaf90d9989b2" class="el">OnAscii</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#3c6292aa52abee79ecfff30eb76abc52" class="el">IsHash</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#3b596ce44b575912067e2c5658059b85" class="el">IsByteSwap</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#0f146f8dbcb71bd798ef677ceecf1227" class="el">OnFailed</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#18968f1e5832925d8a11de1be88357f6" class="el">OffFailed</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#ad8b70f98e8988393d100775ceef5e78" class="el">IsFailed</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#e840a4630a40ba4ccbdc2eafe1ca6345" class="el">SetMode</a> (LONG pmode)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#77f3867c60ec3eeaee1465e72e5dda45" class="el">GetMode</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#b3a1f9250aecfd9edd8239080e52b742" class="el">SkipPast</a> (UINT id)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CRuntimeClass *PASCAL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#7fd7f5afb260535add9156d09aef1772" class="el">LoadRuntimeClass</a> (UINT *pwSchemaNum)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#d8c0e626362f7c5aff3842e31b6b1c78" class="el">StoreRuntimeClass</a> (CRuntimeClass *rtc)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#432bbd32c16ab1131aa2cdc29b73f5ad" class="el">ReadC</a> (void *buf, LONG count)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#540bdb848e6d3cfb15f360bfc92382f9" class="el">Read</a> (void *buf, LONG count)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#3de8faa0726694190a3006bf2f1a4a37" class="el">Write</a> (const void *buf, LONG count)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#77af8c6caabb9f8cab550bd12db6217e" class="el">Flush</a> ()=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#1a5364d59f4ae62f557f7e1ff560ed15" class="el">Close</a> ()=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#08e6da5f6890398a21f4faba4032a6a8" class="el">ReadLine</a> (<a href="classString.md" class="el">String</a> &amp;line)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#22f953c43f82b65bd9bd781f33b79659" class="el">ReadLine</a> (<a href="classMemoryStream.md" class="el">MemoryStream</a> &amp;stream)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#813e7ded5de53be981181373dea3bdbb" class="el">ParseString</a> (<a href="classString.md" class="el">String</a> &amp;token)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#8a8a7e2468b8aed299ba5c455da0d74e" class="el">ParseToken</a> (<a href="classString.md" class="el">String</a> &amp;token)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#ceaab37d8eb02f41bf5b893ba87f58e4" class="el">ParseToken</a> (char *token, char delim)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#5c3376aa36f5c8049d4be3c281e3781f" class="el">Seek</a> (int pos, <a href="classHashStream.md#a3642d2e14408dd483bffb854fd85a2c" class="el">SeekMode</a> seekmode)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#a0beb67581de4746aebead5334327042" class="el">GetPos</a> ()=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#738b2b475456de6cd5654fb16b7a4f95" class="el">WriteLine</a> (<a href="classString.md" class="el">String</a> &amp;line)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#915bc4ac9bfb31e446e333eda6f3f873" class="el">SetStatusMeter</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#7d2e3a81d8d78251ccf815b00d00528f" class="el">SkipHeader</a> (<a href="classHeader.md" class="el">Header</a> &amp;header)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#ecc44c93efeecf9d06ab3fbdaf4f10b9" class="el">ReadString</a> (char delimit)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#08008741795d8c76cdb00549e7606f8d" class="el">ParseToken</a> (<a href="classString.md" class="el">String</a> &amp;token, char delim)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#27ef046565a2f8112a918c13fff7f472" class="el">operator&lt;&lt;</a> (<a href="DataType_8h.md#ed2faba8f48cf2c4bfa2014166424df0" class="el">SBYTE</a> sb)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#44ed1f49c4cd8c600f31c74979ba8c85" class="el">operator&lt;&lt;</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> ub)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#e2e427d7b687c40dee137385b2be222e" class="el">operator&lt;&lt;</a> (<a href="DataType_8h.md#cbd2d4a26a53d662f50ce88a33d98f5b" class="el">SWORD</a> w)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashStream.md#4639c748a17843b3ff7e40130172a57c" class="el">operator&lt;&lt;</a> (<a href="DataType_8h.md#39e2ad1a55f0dcdf5d92e82fe2e3a83d" class="el"