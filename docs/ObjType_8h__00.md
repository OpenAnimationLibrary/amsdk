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

# ObjType.h File Reference

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="ObjType_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/ObjType.hdep_map"></span>

[Go to the source code of this file.](ObjType_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="ObjType_8h.md#11bf90926b0ca5e1b89f7ae9182eb417" class="el">__OBJTYPE_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> {<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db016d93f66f1cae19405997cf96b65315b" class="el">HOT_CHOR</a> = 0, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db023ca032a218ef825ebd0e0710097328f" class="el">HOT_MODEL</a> = 1, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db02b868d040901235b2c7fa206e4a01ad2" class="el">HOT_SEGMENT</a> = 2, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db09ebab77361a7fc20f6f4f905f7e6c1b4" class="el">HOT_ACTION</a> = 3,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0e8ee46bbf63a21a9914da68dfc7da3da" class="el">HOT_GROUP</a> = 4, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db02c850c0a79635bc355a195be29d7d993" class="el">HOT_DECAL</a> = 5, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db09160db84fad36767f756655bfcc90fab" class="el">HOT_ROTOSCOPE</a> = 6, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0fc8b28b1f250fa3f1cb814f99d8c5d90" class="el">HOT_HASHOBJECT</a> = 7,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db043aaa588c0a2c5078bd0e1fe5defe078" class="el">HOT_CAMERA</a> = 9, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0bf957246d35207aba3ed158ee383526f" class="el">HOT_LIGHT</a> = 10, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db091ddb89ae88f2700ca585d870c6f8bc6" class="el">HOT_NULLOBJECT</a> = 11, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0aff390af1e3b31795e9f97f55ff6bd13" class="el">HOT_PROJECT</a> = 12,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c9434844a2a76f965d965855578cdc67" class="el">HOT_MUSCLECHANNELCONTAINER</a> = 13, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0e06f0d5873cb163d8a15d919f8183039" class="el">HOT_OBJECTCACHECONTAINER</a> = 14, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db07cd63a0933de1fef106b7f91edc36daa" class="el">HOT_ACTIONCACHECONTAINER</a> = 15, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0be1db8778f706ced55751cf3e95dbdde" class="el">HOT_MATERIALCACHECONTAINER</a> = 16,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db075070f4012001482ca0ce6f97ba32da9" class="el">HOT_AIMATCONSTRAINT</a> = 17, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0e88198bdfcd7918f636bbd2430dbb4e7" class="el">HOT_AIMROLLATCONSTRAINT</a> = 18, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0f39d55c6faf90c859a757ff3d94a1b9c" class="el">HOT_TRANSLATETOCONSTRAINT</a> = 19, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0e39d79a689bedce8ce32bd870c6cf7dc" class="el">HOT_ORIENTLIKECONSTRAINT</a> = 20,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db036df14afefe5969538790b847fe5951a" class="el">HOT_KINEMATICCONSTRAINT</a> = 21, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0762129964af71f2ead5f094642d533f2" class="el">HOT_AIMLIKETWOCONSTRAINT</a> = 22, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0bfe417b9dd0a7b88fdc790ec3cec67ec" class="el">HOT_AIMROLLLIKETWOCONSTRAINT</a> = 23, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db048bfdf54ccd884e89ab9fc8155276781" class="el">HOT_MATERIAL</a> = 24,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0ce9c9a870e6c4d7296033d6a5cc81ec7" class="el">HOT_ATTRIBUTE</a> = 25, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0d79bc7dcc2b1646488a27651d14d51c7" class="el">HOT_GRADIENT</a> = 26, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db03c7b6b11229063d667af3f37a28dd6e8" class="el">HOT_SPHERICAL</a> = 27, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0668d849d8a24b773b4e9f65240a7fc42" class="el">HOT_CHECKER</a> = 28,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0f4425be2fef6975e47dcc4d5f2970f43" class="el">HOT_DISTORT</a> = 29, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0fc3469be6f5b1f1c460ace45851165d0" class="el">HOT_TURBULENCE</a> = 30, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0171698ea26b974d57a13082a786c97f7" class="el">HOT_BLOBBY</a> = 31, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db092062f3b17e4c0a07a9de33257356db4" class="el">HOT_STREAK</a> = 32,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0d5ba24f0b388a8a506deb07f1e372dfe" class="el">HOT_PATH</a> = 33, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0137ff38622aacdead4556efea2bb3e16" class="el">HOT_PATHCONSTRAINT</a> = 34, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0b06155a33b9cc0d5579a2ad5ae4ce1e1" class="el">HOT_SPHERICALLIMITS</a> = 35, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0d519fccf8823bac8c01c647ef95eb5bf" class="el">HOT_UNUSED3</a> = 36,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0b9552f2c203076980edb264c48fb91eb" class="el">HOT_EULERLIMITS</a> = 37, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0cff9c7cfa300cddd77f9e6e2bbdd3ea2" class="el">HOT_POSE</a> = 38, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0d2da94b6009f43d61e62214031057c4d" class="el">HOT_POSECACHECONTAINER</a> = 39, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db089b176acc71a27544f617878bdbe6859" class="el">HOT_DOPESHEET</a> = 40,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db093d5be2f74de293059f08893abecc807" class="el">HOT_DOPEFRAME</a> = 41, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db04690b8e730b1bc393147e0e578beee0c" class="el">HOT_WEATHERMAP</a> = 42, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db023cf6871cca8fd555b5078f382face7b" class="el">HOT_STAMP</a> = 43, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db000e90b7217546978de3b2eeb480c5f57" class="el">HOT_PATHFIGURE</a> = 44,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0a0f67bb33e27ed13206523e48128a752" class="el">HOT_BONE</a> = 45, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c594ec54f51538aa09ca796b7a811a3e" class="el">HOT_CHORCONTAINER</a> = 46, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0d53606bf29a5a0a28f061d11f508feeb" class="el">HOT_MOTIONCAPTUREDEVICE</a> = 47, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0a49e21af7af440bc4d212a1240279af8" class="el">HOT_SENSOR</a> = 48,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0afb4532e75621ecf10a7ec0efb4c2c17" class="el">HOT_CONTAINER</a> = 49, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0b19771bf98e70ec58bad0357fadf0fe2" class="el">HOT_ACTIONOBJECTSCONTAINER</a> = 50, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db026aee0fdbbc54701cb6d03a07646d5b3" class="el">HOT_ROLLLIKECONSTRAINT</a> = 51, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db00cdc4a083bcd9547f7ac6fbf212f291f" class="el">HOT_ACTIONOBJECTACTION</a> = 52,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0124282932464f88b8e0c69ad54a613a4" class="el">HOT_FORCE</a> = 53, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0b3c42c61b78f76923a3cd0ed981c9336" class="el">HOT_PARTICLE</a> = 54, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0afcfe421492c1cae9606ecff866244fd" class="el">HOT_RADIOSITYMAP</a> = 55, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0a3b8cb8367597af019fc9f873e38d955" class="el">HOT_MATFX</a> = 56,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0fdadef1288c9d9112ec48a58c37a2eae" class="el">HOT_VOLFX</a> = 57, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0ab0f894498abdbe793a78a0a3b94f2c0" class="el">HOT_HAIR</a> = 58, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0348a00fc25812ea30a351d0e44d2c5cd" class="el">HOT_SOUNDCONTAINER</a> = 59, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0a9e6e8bddf66691741cc581c4b8ca3cc" class="el">HOT_SOUND</a> = 60,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db02da7529faf2b2a2eac3d5162f77746cc" class="el">HOT_IMAGECONTAINER</a> = 61, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db093ecbccd91299f73c72cba11bf36f7f7" class="el">HOT_CLIP</a> = 62, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0fe277198025c90b480a68883387dd52a" class="el">HOT_STILL</a> = 63, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0062bc88ca432af1f6c607e6409b833ec" class="el">HOT_ANIMATION</a> = 64,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0d5dc70bd7b6f9ccaa9ca0f89a6f2c2f1" class="el">HOT_DECALCLIP</a> = 65, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0f1a009068c00617c7b2c0d494380ef68" class="el">HOT_DECALCONTAINER</a> = 66, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0733a4c84ba22940057d65dd54005ba40" class="el">HOT_DECALCLIPCONTAINER</a> = 67, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c4798eeac02af7857de18c909044e888" class="el">HOT_STAMPCONTAINER</a> = 68,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db013867d25d4623c610a032907380d5dd1" class="el">HOT_WEATHERCLIP</a> = 69, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db009a251742ea40f0b518c6eef25985829" class="el">HOT_SPRITESYSTEM</a> = 70, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db001a461b463e66694e06f43daa897ecb9" class="el">HOT_SPRITEEMITTER</a> = 71, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db01604422cf9048fbab7a3c63a07e91a6a" class="el">HOT_SKELETALCHANNELMODIFIER</a> = 72,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c536484150c27c8bd8896e25da72d27c" class="el">HOT_SKELETALPOSEMODIFIER</a> = 73, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db06830e352e87e8bef70c346a099297d18" class="el">HOT_RELATIONCONTAINER</a> = 74, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0844f331703891c34abe76595e7ed6725" class="el">HOT_RELATION</a> = 75, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db08c6c51ddfa27867c1dd3380a8bd08c2b" class="el">HOT_RELATIONKEY</a> = 76,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0bc74638f267ceae6178e4694351a63e1" class="el">HOT_RELATIONMDSHORTCUT</a> = 77, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db06d3a613d8463831b0bbab05e3fac8a3d" class="el">HOT_SURFACECONSTRAINT</a> = 78, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db097855eec6105d0f6eaf60c2117fcb752" class="el">HOT_SCALELIKECONSTRAINT</a> = 79, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db004f5318bf2a6fc5bb51d045e920d97eb" class="el">HOT_GROUPCONTAINER</a> = 80,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db07c06c221caaf25e65b07c5f602546461" class="el">HOT_TRANSLATELIMITS</a> = 81, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0515fed605463deda8a463d96930c76a3" class="el">HOT_UNUSED6</a> = 82, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db09350d2c68c579a418c014fc1d959acb3" class="el">HOT_FLOCKFX</a> = 83, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db093fb2ab790db37c2e7f35f7c589e61d2" class="el">HOT_LIGHTLISTNODE</a> = 84,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db06a0af185cf0570eec3317c1e5900cdbb" class="el">HOT_LIGHTCONTAINER</a> = 85, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0b680ca37974048c44a72eb8c68ef111a" class="el">HOT_CHORACTION</a> = 86, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c6b7362ef9b50cca3b3da3a0eb316dee" class="el">HOT_USERCONTAINER</a> = 87, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0935d4f5a052a6769103795e0d8bea247" class="el">HOT_BONECONTAINER</a> = 88,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db07f41c3a7f2c3db0f4073488467062dca" class="el">HOT_ONETARGETSHORTCUT</a> = 89, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db043aac14c771b9f6dd0615a91fd0256bd" class="el">HOT_SPRING</a> = 90, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c3ab75499dbb1e3cd6d88a119516c26d" class="el">HOT_SPRINGSCONTAINER</a> = 91, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db08f636df68a29d582944d1280981decf1" class="el">HOT_SPRINGSYSTEM</a> = 92,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c94be8e0ef6b5b38a01fe8804934e64b" class="el">HOT_MASS</a> = 93, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db06842bfec19fa8ad7399dd7c71fe92933" class="el">HOT_MASSCONTAINER</a> = 94, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db00d6ec92d377bf552e54542f76cc71f58" class="el">HOT_PROP</a> = 95, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db06c1301989be5ff9c4711b2688a329ac6" class="el">HOT_PHONEME</a> = 96,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db03edb37f2d536daf1e95ad5a7c8cf1d5e" class="el">HOT_TEXT</a> = 97, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db03b9e56c4fe0ed202aa77e33a937ad207" class="el">HOT_UNUSED7</a> = 98, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0cd7d1b79bc1968a107a47190a0c5411d" class="el">HOT_UNUSED2</a> = 99, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db06499a891044f685e78704593525e63d8" class="el">HOT_CPTOMASSCONSTRAINT</a> = 100,<br />
  <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0be4427aaeb20f6c695d8a8029f36daf0" class="el">HOT_ACTIONDOPESHEET</a> = 101, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0c0a157a72dc438b6d1f9b6c90654d223" class="el">HOT_TWOTARGETSHORTCUT</a> = 102, <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2d