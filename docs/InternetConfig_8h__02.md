andle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#5ee27adc93844e60ebd920f1a53710d4" class="el">ICMapEntryFlags</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef short </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#86fcd4839c79656b45fe120c81613252" class="el">ICFixedLength</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICMapEntry.md" class="el">ICMapEntry</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#f3aca96c7a0556b3b435d81f30ba1a79" class="el">ICMapEntry</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICMapEntry.md" class="el">ICMapEntry</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#46871dd8d8b73888226aadc1ba53b7ba" class="el">ICMapEntryPtr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICMapEntry.md" class="el">ICMapEntryPtr</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#c1223d1a6c8eccd4a99e84ad138e79cd" class="el">ICMapEntryHandle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef short </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#8c8e6e1fe193496d95d8ee012b21076a" class="el">ICServiceEntryFlags</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICServiceEntry.md" class="el">ICServiceEntry</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#66078c865b4abef5e3c1854c7f6eafe1" class="el">ICServiceEntry</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICServiceEntry.md" class="el">ICServiceEntry</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#a06e97d468fbeff7d71f77e5a96d3cc9" class="el">ICServiceEntryPtr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICServiceEntry.md" class="el">ICServiceEntryPtr</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#d9344072e984724c15267bc7b37f4535" class="el">ICServiceEntryHandle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICServices.md" class="el">ICServices</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#b773e0a5d564ead7fb7b691fccb359ea" class="el">ICServices</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICServices.md" class="el">ICServices</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#2a6ed7b7b47973355a4660b93ab316a8" class="el">ICServicesPtr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef <a href="structICServices.md" class="el">ICServicesPtr</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="InternetConfig_8h.md#a1cd934877e66d8665db460a967611cc" class="el">ICServicesHandle</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516efa7144117565a6c0947a491d2ecd84b02" class="el">icPrefNotFoundErr</a> = -666, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef38079e959f2519465dcc28357797f05b" class="el">icPermErr</a> = -667, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516efc21a4bcf14d26733a1e557f7fc761b60" class="el">icPrefDataErr</a> = -668, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef18554118cf8bbc500f77d5bffae44876" class="el">icInternalErr</a> = -669,<br />
  <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef29968c9ecfe010eb79846506dbf8a58f" class="el">icTruncatedErr</a> = -670, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef8de8928cca5618ad8efaa7cda35e691b" class="el">icNoMoreWritersErr</a> = -671, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef30f0502805862ab43dab3a6b8d500109" class="el">icNothingToOverrideErr</a> = -672, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef0604c3cd2bbe77c97a31638ac0e7fa28" class="el">icNoURLErr</a> = -673,<br />
  <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516efba3ef7c7243f9da73bddf128f4a1f01d" class="el">icConfigNotFoundErr</a> = -674, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516ef229ff09c6c1c1af5831656f6993d57e3" class="el">icConfigInappropriateErr</a> = -675, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516efd061679655ad45de4332a83a529c6b20" class="el">icProfileNotFoundErr</a> = -676, <a href="InternetConfig_8h.md#dca29a1140aadadfd92b34a02fa516efae8d1752db3986ab7850bd7169bc677c" class="el">icTooManyProfilesErr</a> = -677<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="InternetConfig_8h.md#68986ab776eb5d6b5a809a1c005a7300038aeb9ca079ed46d5991ea468ce4e88" class="el">kICComponentInterfaceVersion0</a> = 0x00000000, <a href="InternetConfig_8h.md#68986ab776eb5d6b5a809a1c005a73000ef948dd5d721a24ccd213604f7aa710" class="el">kICComponentInterfaceVersion1</a> = 0x00010000, <a href="InternetConfig_8h.md#68986ab776eb5d6b5a809a1c005a730098c74808c6b3edd15a27ce7efe866195" class="el">kICComponentInterfaceVersion2</a> = 0x00020000, <a href="InternetConfig_8h.md#68986ab776eb5d6b5a809a1c005a73006dda3f85628100bbf9f12e95a66179cc" class="el">kICComponentInterfaceVersion3</a> = 0x00030000,<br />
  <a href="InternetConfig_8h.md#68986ab776eb5d6b5a809a1c005a730078c2f1f4e1439f688424a1644cd778ca" class="el">kICComponentInterfaceVersion4</a> = 0x00040000, <a href="InternetConfig_8h.md#68986ab776eb5d6b5a809a1c005a730021593558248e263aa65980852a2f8d45" class="el">kICComponentInterfaceVersion</a> = kICComponentInterfaceVersion4<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#02653d87b6fa8554fc0d1a3726fea2d0bf096044d7a1e538e2a0261d492ea0d7" class="el">kICAttrLockedBit</a> = 0, <a href="InternetConfig_8h.md#02653d87b6fa8554fc0d1a3726fea2d0793df6ed548fbdcea43e4f34d9073648" class="el">kICAttrVolatileBit</a> = 1 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#1378d7d8767899287b0407055215aa4eac0c6357e9afeadeb10caa6b2bf15632" class="el">kICAttrNoChange</a> = (unsigned long)0xFFFFFFFF, <a href="InternetConfig_8h.md#1378d7d8767899287b0407055215aa4e5ecf653cc60b2ae86068ddc44cf64d70" class="el">kICAttrLockedMask</a> = 0x00000001, <a href="InternetConfig_8h.md#1378d7d8767899287b0407055215aa4e99959411fff3cf07981470fd69928178" class="el">kICAttrVolatileMask</a> = 0x00000002 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#a4d79cb252987ad7f099770543e601a1f29a29f40a2ed0b552daed30376474b6" class="el">icNoPerm</a> = 0, <a href="InternetConfig_8h.md#a4d79cb252987ad7f099770543e601a1527869ed561acf63d75da5412147ea3c" class="el">icReadOnlyPerm</a> = 1, <a href="InternetConfig_8h.md#a4d79cb252987ad7f099770543e601a18de2e71f7006a8e588c9a640203be99d" class="el">icReadWritePerm</a> = 2 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#e80230e7c0b67771dddc6a497e5e2e5ef392682fe438b1a79f0e6d245237ff51" class="el">kICNilProfileID</a> = 0 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#21945c50944818f4cf3b6aef8608f9cedc3b8e12d1b6b3bf270f0d80dbaa014d" class="el">kICNoUserInteractionBit</a> = 0 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#60e3c12db6ddaae1f88a6e0e8d5118e017d39ab2920f223fad45864c5bcf4de2" class="el">kICNoUserInteractionMask</a> = 0x00000001 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#63f5f87eab8bf5d1395b98caa0a448ba9f8c094058bdab3e7cbcfbce5ce4d0ee" class="el">kICFileType</a> = FOUR_CHAR_CODE('ICAp'), <a href="InternetConfig_8h.md#63f5f87eab8bf5d1395b98caa0a448baf560c32bec07c505f396c0afd730454d" class="el">kICCreator</a> = FOUR_CHAR_CODE('ICAp') }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#bdca477a0c8312f3fd1c917c21d567cb60e9812dd950210ff739c71e15d7ad5d" class="el">kInternetEventClass</a> = FOUR_CHAR_CODE('GURL'), <a href="InternetConfig_8h.md#bdca477a0c8312f3fd1c917c21d567cb2a24791080b892490815b19dfdace481" class="el">kAEGetURL</a> = FOUR_CHAR_CODE('GURL'), <a href="InternetConfig_8h.md#bdca477a0c8312f3fd1c917c21d567cb42c318acd5521b44d7a0b0161dd54a37" class="el">kAEFetchURL</a> = FOUR_CHAR_CODE('FURL'), <a href="InternetConfig_8h.md#bdca477a0c8312f3fd1c917c21d567cb6e37936f7815c4853756c9e32b39778b" class="el">keyAEAttaching</a> = FOUR_CHAR_CODE('Atch') }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#292e4a2c5dcece13fd75f0a1bc0a4dbe5b0f5a5e7621be97808020d1943ea571" class="el">kICEditPreferenceEventClass</a> = FOUR_CHAR_CODE('ICAp'), <a href="InternetConfig_8h.md#292e4a2c5dcece13fd75f0a1bc0a4dbe9e27079dd3f3e85fda1bd807f8e6baee" class="el">kICEditPreferenceEvent</a> = FOUR_CHAR_CODE('ICAp'), <a href="InternetConfig_8h.md#292e4a2c5dcece13fd75f0a1bc0a4dbe06e952fb52aa3753cd4c96d18ccb0b5b" class="el">keyICEditPreferenceDestination</a> = FOUR_CHAR_CODE('dest') }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#4f465ceb1b510107884ceaee7abcd0f4b913069e94936392a579e13d65d2970b" class="el">kICComponentVersion</a> = 0, <a href="InternetConfig_8h.md#4f465ceb1b510107884ceaee7abcd0f41071ea22e39a66e2f9b4e34f3510fdd9" class="el">kICNumVersion</a> = 1 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#c8afa25b694ce89e7c6f15b35f6d93681514daee775f028ae8102789701515b1" class="el">kICFileSpecHeaderSize</a> = sizeof(ICFileSpec) - sizeof(AliasRecord) }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#bdf416144f79b0adea50b8078e2b2c7fda35c14f1dd490cfe937ed43cee1cba9" class="el">kICMapFixedLength</a> = 22 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="InternetConfig_8h.md#6510bf0ffe7b2d9f39d3ab102991e8411c55f6d98a51f53a73af3847016c6e7b" class="el">kICMapBinaryBit</a> = 0, <a href="InternetConfig_8h.md#6510bf0ffe7b2d9f39d3ab102991e84158d661ce58ee7f188eb93657c1a8ceea" class="el">kICMapResourceForkBit</a> = 1, <a href="InternetConfig_8h.md#6510bf0ffe7b2d9f39d3ab102991e8410bc2cf0983754b8c7cd620ac34d090c9" class="el">kICMapDataForkBit</a> = 2, <a href="InternetConfig_8h.md#6510bf0ffe7b2d9f39d3ab102991e8414e3ebc8f90c1cb4378dc800c3008b149" class="el">kICMapPostBit</a> = 3,<br />
  <a href="InternetConfig_8h.md#6510bf0ffe7b2d9f39d3ab102991e841ca672796e6e23cc08849be739e53c553" class="el">kICMapNotIncomingBit</a> = 4, <a href="InternetConfig_8h.md#6510bf0ffe7b2d9f39d3ab102991e84195a87ae127ce84d37faa37089861fa4d" class="el">kICMapNotOutgoingBit</a> = 5<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="InternetConfig_8h.md#83e65c6f5037b6249378b339db52d84d40017c6552cb961a3315e41ec8ae3a87" class="el">kICMapBinaryMask</a> = 0x00000001, <a href="InternetConfig_8h.md#83e65c6f5037b6249378b339db52d84dba99ba05cc12c4951103f0141db61731" class="el">kICMapResourceForkMask</a> = 0x00000002, <a href="InternetConfig_8h.md#83e65c6f5037b6249378b339db52d84dea503455266ffdcc2611617eae9ed0d1" class="el">kICMapDataForkMask</a> = 0x00000004, <a href="InternetConfig_8h.md#83e65c6f5037b6249378b339db52d84d141b346fbcc2fc1fb7ece62f90a0c158" class="el">kICMapPostMask</a> = 0x00000008,<br />
  <a href="InternetConfig_8h.md#83e65c6f5037b6249378b339db52d84dab01c9ea326de3295e097c5b3a225a1c" class="el">kICMapNotIncomingMask</a> = 0x00000010, <a href="InternetConfig_8h.md#83e65c6f5037b6249378b339db52d84d7bb53280cd13d002a03df2dca969d7d4" class="el">kICMapNotOutgoingMask</a> = 0x00000020<br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#68e3b06335fbcedc7232ab741738269ce9a8b633084a524e8dfdb10a8096da53" class="el">kICServicesTCPBit</a> = 0, <a href="InternetConfig_8h.md#68e3b06335fbcedc7232ab741738269cebaa316ba752698f7a6544cc9ff592c4" class="el">kICServicesUDPBit</a> = 1 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="InternetConfig_8h.md#522dbf5f367e0a96a94135f388be77549b239019e6680919369cf4a0ccb31e6a" class="el">kICServicesTCPMask</a> = 0x00000001, <a href="InternetConfig_8h.md#522dbf5f367e0a96a94135