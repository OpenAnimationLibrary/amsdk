tring</a> &amp;string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#8b7825d5eca17af4260923e99b635e35" class="el">DeleteRegistryItem</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#f81c5c4e4c49412c7cb609e904625cc0" class="el">ResetRegistry</a> (const <a href="classString.md" class="el">String</a> &amp;regname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#6c2db0c2c3489d7f1f82b54199367f55" class="el">ResetRegistry</a> (const <a href="classString.md" class="el">String</a> &amp;key, const <a href="classString.md" class="el">String</a> &amp;regname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#c35c1ed7d27d8b17991d63d7cb6af7ee" class="el">GetRegistryBOOL</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, BOOL defaultvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#9bfeaf4c02f2b0413024e5c079c53bbb" class="el">SetRegistryBOOL</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, BOOL value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT int </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#a8ad4c505284f2da0f35ffa175315c1e" class="el">GetRegistryValue</a> (BOOL ischar, const char *section, const char *entry, int defaultvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#21d4b395ebea58b7b5fed3bd1500fcd1" class="el">GetRegistryValue</a> (BOOL ischar, const char *section, const char *entry, float defaultvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT char * </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#f5cfb50f5336b9522b6f3e12f0fb309a" class="el">GetRegistryString</a> (BOOL ischar, const char *section, const char *entry, const char *defaultstring)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#b7b840b13a2f130e227f443e1beb038e" class="el">SetRegistryValue</a> (BOOL ischar, const char *section, const char *entry, int tvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#ffa73efd790c359f79e13f52c520add0" class="el">SetRegistryValue</a> (BOOL ischar, const char *section, const char *entry, float value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#9da1eea53d1fd83ba1fead80559dbf0d" class="el">SetRegistryString</a> (BOOL ischar, const char *section, const char *entry, const char *string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#919806ac7ab0e3ea2254bd4ec61c18b3" class="el">WriteProfileBinarySplit</a> (BOOL ischar, const char *section, const char *entry, LPBYTE pData, UINT nBytes)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#49827432a5d55ba6db0d51b0e5f62283" class="el">GetProfileBinarySplit</a> (BOOL ischar, const char *section, const char *entry, LPBYTE *ppData, UINT *pBytes)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT int </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#0060bfdfff9d4ae3f1932e380663355c" class="el">GetLocalRegistryValue</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, int defaultvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#b35da810ea9f34604b26764cf0f560ed" class="el">GetLocalRegistryValue</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, float defaultvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#252adf02c42f131d30bce6aeb2cc426b" class="el">GetLocalRegistryString</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, const <a href="classString.md" class="el">String</a> &amp;defaultstring)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#c3ae9e87e377e44d8af28b21bec82d09" class="el">SetLocalRegistryValue</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, int tvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#6d03274ea723865170a819d637e1d95a" class="el">SetLocalRegistryValue</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, float value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#1bbc5c06177abf509521aeabee012529" class="el">SetLocalRegistryString</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, const <a href="classString.md" class="el">String</a> &amp;string)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#dfb00ed44a6b40871abd523ea92a34fa" class="el">SetLocalRegistryProfile</a> (const <a href="classString.md" class="el">String</a> &amp;profile)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#428d0acd1c3e8b61e9eeee8441a58f6c" class="el">GetLocalRegistryProfile</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#66b2e836c08b314214450b9c04853ec9" class="el">FreeLocalRegistryProfile</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#8bef9d17934e59b9ea4aba0238a7dd52" class="el">WriteProfileBinarySplit</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, LPBYTE pData, UINT nBytes)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#5f2cda0f1aff53f3074f912138d9c4d6" class="el">GetProfileBinarySplit</a> (const <a href="classString.md" class="el">String</a> &amp;section, const <a href="classString.md" class="el">String</a> &amp;entry, LPBYTE *ppData, UINT *pBytes)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#d1887553d9bf9d3fcda57af538c738e9" class="el">InitMacProfile</a> (char *name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#c486ddeab88891d5ccd6aa34db1d60f8" class="el">FreeMacProfile</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#7c30028e6bb7959c536971b389c11f5d" class="el">SaveMacProfile</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#3d6c7f5ad696e355ae1318713f4fe47f" class="el">GetLastSubdivision</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#0c8d2feae8f2a83f42caf4ae54508817" class="el">SaveRequest</a> (UINT titleid, UINT filterid, <a href="classString.md" class="el">String</a> &amp;filename, char *extension, const char *inilookup, UINT actionid=3, CWnd *parent=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#d1734eef39d5329ea77a15e13be95000" class="el">SaveRequest</a> (UINT titleid, const <a href="classString.md" class="el">String</a> &amp;filters, <a href="classString.md" class="el">String</a> &amp;filename, char *extension, const char *inilookup, UINT actionid=3, CWnd *parent=NULL, int *pindex=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#93b9aefdc559a2f11d8bc3773930757b" class="el">SaveRequest</a> (const <a href="classString.md" class="el">String</a> &amp;title, const <a href="classString.md" class="el">String</a> &amp;filters, <a href="classString.md" class="el">String</a> &amp;filename, char *extension, const char *inilookup, UINT actionid=3, CWnd *parent=NULL, int *pindex=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#89fc2f141beec6c4cc47ff144166cca8" class="el">GetDescriptionGivenIndex</a> (const <a href="classString.md" class="el">String</a> &amp;filters, int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#e3682551bb76d51fc3afcddcf26ab697" class="el">DeleteStringList</a> (<a href="classStringList.md" class="el">StringList</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#6cad26bc962cfbf84cb1b525eb16d3b9" class="el">OpenRequest</a> (UINT titleid, UINT filterid, <a href="classString.md" class="el">String</a> &amp;filename, char *extension, char *inilookup, int *index=NULL, CWnd *parent=NULL, <a href="classStringList.md" class="el">StringList</a> **multiselect=NULL, CHashFileDialog *pdlg=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#f5cb88620a5905a1012ca5ebce8eca05" class="el">OpenRequest</a> (const <a href="classString.md" class="el">String</a> &amp;title, const <a href="classString.md" class="el">String</a> &amp;filter, <a href="classString.md" class="el">String</a> &amp;filename, char *extension, char *inilookup, int *index=NULL, CWnd *parent=NULL, <a href="classStringList.md" class="el">StringList</a> **multiselect=NULL, CHashFileDialog *pdlg=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#e0ca77911ea6e8143102a2efb676c729" class="el">OpenRequest</a> (const <a href="classString.md" class="el">String</a> &amp;title, const <a href="classString.md" class="el">String</a> &amp;filter, <a href="classString.md" class="el">String</a> &amp;filename, char *extension, char *inilookup, int *index, CWnd *parent, <a href="classStringList.md" class="el">StringList</a> **multiselect, CHashFileDialog *pdlg, BOOL *pbCancelall)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#2a013836e75d3cfad842bf8b4a13ca7a" class="el">StringRequest</a> (UINT messageid, <a href="classString.md" class="el">String</a> &amp;string, CWnd *parent=NULL, UINT titleid=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="F__Protos_8h.md#6b2f14583bf89fd91d18fefd76899251" class="el">StringRequest</a> (CString &amp;message, <a href="classString.md" class="el">String</a> &amp;string, CWnd *parent=NULL, UINT titleid=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;