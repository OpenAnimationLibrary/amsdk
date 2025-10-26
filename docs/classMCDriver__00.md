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

# MCDriver Class Reference

`#include <`<a href="MCDriver_8h-source.md" class="el"><code>MCDriver.h</code></a>`>`

Inheritance diagram for MCDriver:

<span class="image placeholder" original-image-src="classMCDriver__inherit__graph.gif" original-image-title="" border="0" usemap="#MCDriver__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for MCDriver:

<span class="image placeholder" original-image-src="classMCDriver__coll__graph.gif" original-image-title="" border="0" usemap="#MCDriver__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMCDriver-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#90bf8504e8b4c8625619070673984317" class="el">FrameError</a> { <a href="classMCDriver.md#90bf8504e8b4c8625619070673984317450cfc141d8f339671c4b497fa6852c9" class="el">FE_FAILED</a>, <a href="classMCDriver.md#90bf8504e8b4c86256190706739843172ec1f190e144f78663eb5764aea418fb" class="el">FE_SUCCESS</a>, <a href="classMCDriver.md#90bf8504e8b4c8625619070673984317bd8ebe490b4e0564b4802d8902fc524c" class="el">FE_TRYAGAIN</a> }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516efab89d8462fe52fea714ca523f21b9fd6" class="el">XTRANS</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516effdb7466f038e37034ee18610f352e7cc" class="el">YTRANS</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef3b2645c91ddfda0e16399d2577a4f3c6" class="el">ZTRANS</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef119689a6881a476793d78e2f1c3d52e5" class="el">XSCALE</a>,<br />
  <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef09da925c689618d48a12515cce23e869" class="el">YSCALE</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef3046344ca6761ef7c0d5a4d5990da666" class="el">ZSCALE</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef90c282b44b3ac4d471c847958062058e" class="el">XORIENT</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef03389cab6fd285a7a6b3bd9caaf67bb4" class="el">YORIENT</a>,<br />
  <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef1bd100200b9b7bb082fa5008b4e2a16a" class="el">ZORIENT</a>, <a href="classMCDriver.md#dca29a1140aadadfd92b34a02fa516ef08cd1a31f17f0247ac89e2fbaadaa9e8" class="el">ROLL</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#97cf3df5cd4753338efe4b6f02b3c585" class="el">MCDriver</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *htreeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#f6d8e92939008836eadcb8d5bda26ef5" class="el">SetDevice</a> (MCDevice *pdevice)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MCDevice * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#720bcf8e601f3ed7e562438887ce8969" class="el">GetDevice</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#b8c52e0dfd0467fe869435f3c55d570b" class="el">BuildSensorArray</a> (int count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#d7e59a7261559392f8a838154a8ce92a" class="el">InsertSensor</a> (int index, char *name, int parentindex=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#e5f04ad884e5acf1c2f3693640a0cd06" class="el">InsertSensor</a> (int index, char *name, <a href="classVector.md" class="el">Vector</a> start, <a href="classVector.md" class="el">Vector</a> end, int parentindex=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#2e1b9843897104ca2949f0559045811f" class="el">DoneInsertingSensors</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#17210b2efef68624805a0ad13232d793" class="el">FreeSensorArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#5e78d251a47846d278abe05f8c2fe6b9" class="el">SetValue</a> (int sensorindex, int channelindex, float value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#4acb84f7155b3616298fd6463c8c8be2" class="el">StoreRotate</a> (int sensorindex, const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;matrix)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#b9efe61ab18f8f47ea4b29acb408de7f" class="el">StoreRotateStandard</a> (int sensorindex, const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;matrix)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#66b62bdac4408b3b126e37eb8616c0c6" class="el">StoreTranslateStandard</a> (int sensorindex, const <a href="classVector.md" class="el">Vector</a> translate)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#05dd9a4bc958f0d0d6e6cd8d805a4889" class="el">StorePose</a> (MCDevice *<a href="classMCDriver.md#913f9c49dcb544e2087cee284f4a00b7" class="el">device</a>, char *name, float percent)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#e9dda391e2c3dedde6558ffcc4071026" class="el">GetTime</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#434480fdb3c0c105e6cc0569f3e14c84" class="el">SetTime</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#a299addedcaaaf03dd8bc98556cb5bdc" class="el">GetFrame</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#da19134c17e87dcf016d74ac7d7557e9" class="el">SetFrame</a> (float frame)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#43243e43ef65c310f186d0a621b28218" class="el">GetSystemRate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#1be9590ff66bfead7e8ae80b1466208c" class="el">GetCaptureRate</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#b6002cee28e3ac23fd05aebbe41393a9" class="el">Redraw</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#7c937e8de6cd6b41e35091652fa2e293" class="el">EscapeKeyDown</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#34aaab8a706172a6ae552966637fb396" class="el">SupportsLiveCaptureSequence</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#4832509618884fac91fcbc3ffc5b3aed" class="el">SupportsLiveCaptureFrame</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#8b1fbe863e8380e982db921e2f0f85a6" class="el">SupportsStaticCaptureSequence</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#4e0c24227cea849eff3ea34d338e8248" class="el">LiveCaptureInit</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classMCDriver.md#90bf8504e8b4c8625619070673984317" class="el">FrameError</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#b6ed751b0feec894ae922341942c07a4" class="el">LiveCaptureFrame</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#8cdfb60211be909cef0670e698884184" class="el">LiveCaptureClose</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#f7498be562f10f15f28a7e49c6746d49" class="el">StaticCaptureSequence</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MCDevice * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMCDriver.md#913f9c49dcb544e2087cee284f4a00b7" class="el">device</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

