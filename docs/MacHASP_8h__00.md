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

# MacHASP.h File Reference

`#include "MacHaspErrors.h"`  

Include dependency graph for MacHASP.h:

<span class="image placeholder" original-image-src="MacHASP_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/MacHASP.h_map"></span>

[Go to the source code of this file.](MacHASP_8h-source.md)

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
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#e10e35f017d943594baaf2990472fa79" class="el">MacHASPCH_def</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#7530bf89212a8f971b31c8c9a1508aa0" class="el">SRV_ISHASP</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#f4a5ac7d18c39119b7f862e6745b77da" class="el">SRV_GET_CODE</a>   2</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#943cb7854b771f3b9026fd1c510c529b" class="el">SRV_GET_HASP_TYPE</a>   3</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#292d098aab2121e9d43693a14a54d5d4" class="el">SRV_READ_MEMO</a>   4</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#7dbb219b731f3978a73e3d6a7f8a9a9e" class="el">SRV_WRITE_MEMO</a>   5</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#eb015aea5ff1352751b2fd7b7fab5710" class="el">SRV_READ_BLOCK</a>   6</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#e519d2600b2afd0864bb7d85844fa18b" class="el">SRV_WRITE_BLOCK</a>   7</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#cf6dd8990bf7d01b30ff30d49bc10936" class="el">SRV_READ_RAM</a>   8</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#57cf78759483c9da0f8d471429301a18" class="el">SRV_WRITE_RAM</a>   9</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#130025719817fc2816ee37072baa902f" class="el">SRV_READ_PRIVILEGE</a>   10</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#85a76e0444244fbcf590a7a7f25bc0b9" class="el">SRV_WRITE_PRIVILEGE</a>   11</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#6c5301e1f1ab4ab7d84a0728b937de0e" class="el">SRV_MAXNET_STATIONS</a>   12</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#e42ee1a9ba07f28b5abb69b86bc66418" class="el">SRV_NET_LOGIN</a>   41</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#67b71a2e026147dbe565af67f9a63ffa" class="el">SRV_NET_LOGOUT</a>   42</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#83ef51b1291fa9092f9119a2edb59483" class="el">SRV_NET_ExLOGOUT</a>   43</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#9e006bcf7aa4edc9b1d72065529007cc" class="el">SRV_NET_GET_CODE</a>   44</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#829e1fea55ce9e25e5780fe2b4ababd7" class="el">SRV_NET_GET_TYPE</a>   45</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#376ff3f62bcea727cbab75347bd84edd" class="el">SRV_NET_READ_MEMO</a>   46</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#32b90d4e0cc4bdb25ecd6ff46c242973" class="el">SRV_NET_WRITE_MEMO</a>   47</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#920cc21211666a1b920b5a78b0ea095d" class="el">SRV_NET_READ_BLOCK</a>   48</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#5ce76e442c808fcb2ba0eb6b9afe282d" class="el">SRV_NET_WRITE_BLOCK</a>   49</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#4f6fbbb3d8e8fdd03a566bd03968d767" class="el">SRV_NET_READ_RAM</a>   50</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#3ea3f61ea98e9bce5b2448d71f1f72ef" class="el">SRV_NET_WRITE_RAM</a>   51</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#2a878bf44c58a3cf83f69e447b384185" class="el">SRV_NET_READ_PRIVILEGE</a>   52</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#43ab9c19e42b914a80ef779bd337cc05" class="el">SRV_NET_WRITE_PRIVILEGE</a>   53</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#f2b3b9aa13890c76c3b93668fa6522b9" class="el">SRV_NET_GET_LOGGEDIN</a>   54</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#3c17b9c4611f007205b1570e6d6e1128" class="el">SRV_NET_GET_ALL_LOGGEDIN</a>   55</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#730a479ef4cd4ba22d030182da542c60" class="el">SRV_NET_GET_PROG_INFO</a>   56</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#7cf866a720a24f81df4941d6d9aaf339" class="el">SRV_NET_SET_IDLE_LIMIT</a>   57</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#c9677e455cb0beceeb8181e6fec8b7e9" class="el">SRV_NET_CHECK_COMPLETE</a>   60</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#ce6e886d678ac4ed103bc5e2cb58a15f" class="el">SRV_NET_SET_SERVER_ADDRESS</a>   61</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#177aa9b0e4dbd5e0fa6a710923c7505d" class="el">SRV_NET_GET_MONITOR_INFO</a>   62</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#2e82c15903b95026afb714d4f79da61d" class="el">SRV_NET_GET_MORE_MONITOR_INFO</a>   63</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#33ceaf115c3a3ddd38a79ff1539b8b35" class="el">SRV_RELEASE_MONITOR_INFO</a>   64</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#650ad90c63876221a141cc9eca422d09" class="el">SRV_CHECK_FOR_COMPLETE</a>   13</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#fccd5086a12012e1a0f7c6f68f0dc2d5" class="el">HASP_NOWAIT_BIT</a>   0x80000000L</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#6cbc9b05f2294bca00fc61ddbdb2818b" class="el">HASP_FROM_DT_BIT</a>   0x40000000L</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#246d2c5cd8ab1f84a81ee00ecdfe312d" class="el">ENV_LOGIN_BIT</a>   0x00008000L</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#50f8eb4c41c16eff51caa77f93a4a742" class="el">SRV_RUS_UPDATE</a>   101</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#7078c75a684bd1545deaa73f599cab2c" class="el">SRV_RUS_CREATE_PASSW</a>   102</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#9fff4b4dccf1c4cdd7eed572507f7ad4" class="el">SRV_RUS_GET_ID</a>   103</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#7fc0111eea7fe39c03bbf0522f8a1634" class="el">SRV_HASP_USB_RESET</a>   200</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#0a94f6a6c8c2bab45738d9ae2e0bfa8a" class="el">PRIVILEGED_LOW</a>   0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#5503f2793a6beba6498b45da8a49919c" class="el">PRIVILEGED_HIGH</a>   9</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#875367f7565c0f9102eb21e935b86f24" class="el">PRIVILEGED_SIZE</a>   PRIVILEGED_HIGH - PRIVILEGED_LOW + 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#60ef7d564938a860e27cd3bdeabaf558" class="el">MAX_ADB</a>   15</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#1fe5dff3553de5101a331206a3c7a464" class="el">MAX_USB</a>   127</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#5f3419e82eb6bd3d5f81ecf0ff360257" class="el">MAX_HASP</a>   MAX_ADB + MAX_USB</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#58ae5ce752a537923fb9e72f0906bac8" class="el">NETHASP_UNLIMITED_IDLE_TIME</a>   0xFFFF</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#646168ace367a9eb08a53bcd922c0c92" class="el">HASP_RESOURCE_NAME</a>   "\pHaspResource"</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#c2beada721101e23520e97bbf3070e7c" class="el">HASP_RESOURCE_TYPE</a>   'HASP'</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="MacHASP_8h.md#790963e84c50069a036d0f99f31193c4" class="el">HASP_RESOURCE_ID</a>   128</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td