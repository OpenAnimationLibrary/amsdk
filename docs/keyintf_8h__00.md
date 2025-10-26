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

# keyintf.h File Reference

[Go to the source code of this file.](keyintf_8h-source.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">struct  </td>
<td class="memItemRight" data-valign="bottom"><a href="structksrr.md" class="el">ksrr</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#b666223becc6e7d3b160ccd529714334" class="el">__KEYINTF__</a>   0x5000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#572571892b882ebee079616365e2d450" class="el">SC_DETACHABLE</a>   0x01</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#9e9edc9dad94a4b3a80769ff06972315" class="el">SC_LOCALZONE</a>   0x02</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#14fafee7deb8ffd10db40b480f9a5902" class="el">SC_SRVRSPECIFIC</a>   0x04</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#cf54a96b3fdab699dce949acf8a91ed0" class="el">SC_BACKGDWARN</a>   0x08</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#4bbe6760746186f0c34562956e1d92e5" class="el">SC_MULTILAUNCH</a>   0x40</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#611ebb8798a523b3fd0a429596e9ac71" class="el">SC_HAVEKEY</a>   0x80</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#316bb72b4f099e351d9391b82e16e230" class="el">SDV_NOQUIT</a>   0x00200000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#bd3c83741d270e542d81a76b645fbe36" class="el">SDV_NOPTCH</a>   0x00400000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#e95187c54559d901b927e6b6f706a187" class="el">SDV_DEFER</a>   0x00800000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#5f8189e59bd1eac4d0a0ecce58fb3fa8" class="el">SDV_NOCUST</a>   0x04000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#ba1350ff7322f50f5bc9ab3bd8270137" class="el">SDV_NONTFY</a>   0x08000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#e9c9d74f27d0e264e89a9ebdc40ff5b7" class="el">SDV_NOINIT</a>   0x10000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#70db3e728dc5e9d1883a23f4a58409be" class="el">SDV_NOPOST</a>   0x20000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#d084b2a72eeec1223a947fbfd5601627" class="el">SDV_NOEXIT</a>   0x40000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#e4e9355ff87cc232a9084ffb018617cd" class="el">SDV_NOCSUM</a>   0x80000000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#5b7c51d018473e2c90a56b33f65dd50c" class="el">KEY_SUCCESS</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#56fbcdd8409ff35002ef567497d05bbe" class="el">KEY_FAILURE</a>   -1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#2a7fda1e7968582d6e5f033f5d03b241" class="el">KEY_FIRSTERR</a>   -10000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#0f9a94d29013da6468c0dee38da23105" class="el">KEY_NOTAVAIL</a>   -10000</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#92dad613dda75b139f06f74897841345" class="el">KEY_MAXUSERS</a>   -10001</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#b2400a6e22fdb04a707c64f33d0106a4" class="el">KEY_MAXAPPS</a>   -10002</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#c5ddbaf5eae63dc4e25f14a5c0f6fd12" class="el">KEY_REMOTEDENY</a>   -10003</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#ecce57213039b599a4cf4efe4ecd5078" class="el">KEY_OLDPROGRAM</a>   -10004</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#f77fde34fd5a2379f87b0ff952811941" class="el">KEY_ONQUEUE</a>   -10005</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#05baf2d26bddffe4b8d489956b2c2c6d" class="el">KEY_NOSELECTION</a>   -10006</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#6965efa2647665d2f70ecef1921ce6e7" class="el">KEY_OLDCLIENT</a>   -10007</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#4c037f9570e7aea6d334789d2875748b" class="el">KEY_NORESPONSE</a>   -10008</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#7d846f92898845cb0694984a3e92cddc" class="el">KEY_NOREASON</a>   -10009</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#c65562a4ae65d30cddd4dbd6a196d3ae" class="el">KEY_UNKNOWN</a>   -10010</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#992da563f5c0983e8fa08ddfa8ead71a" class="el">KEY_BADCHKSUM</a>   -10011</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#491fd5d1e3c8712401980b2ede9a29ad" class="el">KEY_IDDIFFERS</a>   -10012</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#5bf34d418853844731f21166e240be8f" class="el">KEY_AUTHABORT</a>   -10013</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#8636c0743b28b0cf0340c9b505e7e253" class="el">KEY_NOTAUTHED</a>   -10014</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#939c140617148051af11fc8c27374710" class="el">KEY_USRUNKNOWN</a>   -10015</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#9256fca291b4d0d925e8511fe708eac0" class="el">KEY_PERMDENIED</a>   -10016</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#b18d672180ec8cdcfef6781a811f790e" class="el">KEY_GUESTONLY</a>   -10017</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#8d7fe5f2920c8a9ef31ae19e3dc7e5e1" class="el">KEY_BADCACHE</a>   -10018</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#effa992d80658cce9f1988e4bc1e4795" class="el">KEY_CACHEABORT</a>   -10019</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#59756a10be99ba75d628010b762621b9" class="el">KEY_NOTKEYED</a>   -10020</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#7d88c67ca4ef30f25c40ebb10b61bafd" class="el">KEY_NOTSYSVOLUME</a>   -10021</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#33aad678225e223f42bcb3c56250bac3" class="el">KEY_FLOPPYDISKSYS</a>   -10022</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#8db65ef08a549e90faad7a9c87cd383d" class="el">KEY_PKVERSUNKNOWN</a>   -10023</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#565b3dd5a400a7149d95a75964954691" class="el">KEY_FLOPPYDISK</a>   -10024</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#5120269a7773610ce3e0358486b11a3f" class="el">KEY_NOAFPLAUNCH</a>   -10025</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#f2796e5912302ed92dcb65d04b42ba31" class="el">KEY_MUSTAFPLAUNCH</a>   -10026</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#421dc29cbe829ecd2d7110c54198cfd7" class="el">KEY_SERVERNOTFOUND</a>   -10027</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#a5c1c9b84cecace25cc3bc8478759d94" class="el">KEY_NOTQUEUED</a>   -10028</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#408bf2d386c73e2971f1d305f3fb96f3" class="el">KEY_LASTERR</a>   -10028</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#28652eff8d4825acd60c04bcec7355cb" class="el">KEY_NOCLIENT</a>   -35</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#4bd7c180b0f5d7a412e8b6d4270c9261" class="el">KEY_HANDLE</a>   unsigned <a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#b29c2112bfaaf57810c5c5192fa4e0b7" class="el">KEY_RESULT</a>   short</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="keyintf_8h.md#b529a8129fa98838e748b027f35d6f19" class="el">KEY_ROUTINE</a>(type)   type WINAPI</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="typedefs">Typedefs</h2></td>
</tr>
<tr>
<td class="memItemLeft" styl