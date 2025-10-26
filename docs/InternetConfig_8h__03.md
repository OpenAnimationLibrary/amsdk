f388be7754ec248171293f995bd3e8dc5853ae2297" class="el">kICServicesUDPMask</a> = 0x00000002 }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#d5f4eabec0e174985533834e64930502" class="el">ICStart</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> *inst, OSType signature)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#9bf36152f4417578356abedcd881a180" class="el">ICStop</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#90b9388ae1b8700b8043a45068b790c3" class="el">ICGetVersion</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> whichVersion, UInt32 *version) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#35e93c332e4efbefd88d1208fc1042e0" class="el">ICGetConfigName</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Boolean longname, Str255 name) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#95c870d0682f138c7968e66d822ba0e8" class="el">ICGetSeed</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *seed) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#2165b1cb2d6d57991e109cc11b206924" class="el">ICGetPerm</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, <a href="InternetConfig_8h.md#8cf3f15172c6a1b9d2704f65736dc8fe" class="el">ICPerm</a> *perm) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#a627466b34163bc442344d18f81476c3" class="el">ICBegin</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, <a href="InternetConfig_8h.md#8cf3f15172c6a1b9d2704f65736dc8fe" class="el">ICPerm</a> perm) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#8445f54fd21040a6e97d726cff312344" class="el">ICGetPref</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key, <a href="InternetConfig_8h.md#d1b878cb2da603758c149bb047cf89de" class="el">ICAttr</a> *attr, void *buf, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *size) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#30067ffe3143875a4384f763df70e717" class="el">ICSetPref</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key, <a href="InternetConfig_8h.md#d1b878cb2da603758c149bb047cf89de" class="el">ICAttr</a> attr, const void *buf, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> size) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#9322353726ebd170a1a86b4faed5df43" class="el">ICFindPrefHandle</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key, <a href="InternetConfig_8h.md#d1b878cb2da603758c149bb047cf89de" class="el">ICAttr</a> *attr, Handle prefh) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#d2dccb67fd70cdfd106d931b84ffc8f4" class="el">ICGetPrefHandle</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key, <a href="InternetConfig_8h.md#d1b878cb2da603758c149bb047cf89de" class="el">ICAttr</a> *attr, Handle *prefh) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#ca862fd5cfd47936ff16c85558b9511e" class="el">ICSetPrefHandle</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key, <a href="InternetConfig_8h.md#d1b878cb2da603758c149bb047cf89de" class="el">ICAttr</a> attr, Handle prefh) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#0a71a25f1f8c60338f7b3c11a91e907b" class="el">ICCountPref</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *count) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#ecdba6d407941d125676be9b0f984fb2" class="el">ICGetIndPref</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> index, Str255 key) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#17a04772482b494a63f0cf678ad50187" class="el">ICDeletePref</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#c3629036ee5db2fa4a12a695b37d5e08" class="el">ICEnd</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#90b7c27e226f2a1ba0f904c180a4f4ee" class="el">ICGetDefaultPref</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key, Handle prefH) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#df5e926a7065303b456496093f9f2a1f" class="el">ICEditPreferences</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param key) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#494da84f9663c778d7745e6302f3d8f3" class="el">ICLaunchURL</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param hint, const void *data, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> len, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *selStart, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *selEnd) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#1b9d2a7f1b61c07fa41d5eacfc5f2f22" class="el">ICParseURL</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param hint, const void *data, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> len, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *selStart, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *selEnd, Handle url) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#08d74a460bfb70bc08fe19d9837948d1" class="el">ICCreateGURLEvent</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, OSType helperCreator, Handle urlH, AppleEvent *theEvent) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#7f944b38c4d57acbad528942b1e4ff74" class="el">ICSendGURLEvent</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, AppleEvent *theEvent) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#261e623f3371c23030f31248b83677a2" class="el">ICMapFilename</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, ConstStr255Param filename, <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#e8da48abf5b15f10cb2de32ccb669390" class="el">ICMapTypeCreator</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, OSType fType, OSType fCreator, ConstStr255Param filename, <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#0d1af0c54aa1b769522db07f776f4935" class="el">ICMapEntriesFilename</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, ConstStr255Param filename, <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#3a3213cca04748e50060b5afdd1cba0a" class="el">ICMapEntriesTypeCreator</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, OSType fType, OSType fCreator, ConstStr255Param filename, <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#824d6e76bf52d7e9b7ddd47900c1fc5a" class="el">ICCountMapEntries</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *count) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#94db9622f298a061cf55bcc49ff0d181" class="el">ICGetIndMapEntry</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> index, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *pos, <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#b9e1350c928c3301b1bdcb2a6576ea1f" class="el">ICGetMapEntry</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> pos, <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#4a0464a9b5980bfc7e64bf03304ad60c" class="el">ICSetMapEntry</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> pos, const <a href="structICMapEntry.md" class="el">ICMapEntry</a> *entry) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#558a6bd95fa25d0de21967fb0f029495" class="el">ICDeleteMapEntry</a> (<a href="InternetConfig_8h.md#7b034292a8aa7586587499419e84e11a" class="el">ICInstance</a> inst, Handle entries, <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> pos) FIVEWORDINLINE(0x2F3C</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#d9dd96115963