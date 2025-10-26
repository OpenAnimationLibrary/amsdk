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

# Time Class Reference

`#include <`<a href="HashTime_8h-source.md" class="el"><code>HashTime.h</code></a>`>`

[List of all members.](classTime-members.md)

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
<td class="memItemRight" data-valign="bottom">{ <a href="classTime.md#dca29a1140aadadfd92b34a02fa516ef2a1086d09f51f62408276e7a7de4f5ff" class="el">TICKSPERSECOND</a> = 135000 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#2505397568be968e5f1271c5fd619434" class="el">TimeType</a> { <a href="classTime.md#2505397568be968e5f1271c5fd619434b7ecc6443c36f54c338ce9960ef7ade2" class="el">TT_MINSTEP</a>, <a href="classTime.md#2505397568be968e5f1271c5fd61943482e31bb1470e0115c346a4c9f4e6319b" class="el">TT_MAX</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#b65e1d0669dac48ede7c8c63f8ebb951" class="el">Time</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#cc8a5aa3ec00a7b199472876c35715f3" class="el">Time</a> (double seconds)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#3a6c733e58109486847a38ced1bcb783" class="el">Time</a> (double frame, double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#75df6f5543663ff7cc1809062828f766" class="el">Time</a> (<a href="classTime.md#2505397568be968e5f1271c5fd619434" class="el">TimeType</a> rt)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#6b32f8e7da27f864958a787531c3ea9c" class="el">operator=</a> (const double seconds)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#9eee75409005c314bb2f929096931099" class="el">operator=</a> (<a href="classTime.md" class="el">Time</a> other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#83cfc442ebd8ad9fe605b682e8a1f430" class="el">operator==</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#513052758de27d4dfa3085bde45d4ade" class="el">operator!=</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#7a5cacebefc5f2a6a422be229b4a2f59" class="el">operator&gt;</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#c8e7191feba2a0d4b7ff0bb4fee012de" class="el">operator&lt;</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#23f94f833f6a9a9e9c8d646431e634b0" class="el">operator&gt;=</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#53159adfcb58973de9db4e8e694e4d9a" class="el">operator&lt;=</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#127cab4b7653b4b93193cc6feb4e1a71" class="el">operator+</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#378b4422c695d02900cff36fcf79b204" class="el">operator-</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#03b19b4a73af3057e9322488fab0a8dd" class="el">operator *</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#058aaaeae1cad8f46de639dc325cd1b9" class="el">operator *</a> (double n) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#99e859c3d1d62421400f853c4c63bd86" class="el">operator/</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#1eeb042359d7747cb421d66016682d6e" class="el">operator/</a> (double n) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#7e502b99bdb260181abcb39ad7ed64ba" class="el">operator%</a> (<a href="classTime.md" class="el">Time</a> other) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#adf3022f34d7cdf519a09db79e8a0da4" class="el">operator+=</a> (<a href="classTime.md" class="el">Time</a> other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#5380bf75077a6d730608a0ab78311289" class="el">operator-=</a> (<a href="classTime.md" class="el">Time</a> other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#d1bab5afce41baa1a0d505ff762c5934" class="el">operator *=</a> (<a href="classTime.md" class="el">Time</a> other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#25b39f0bb14c9878d42f8043573b6be3" class="el">operator *=</a> (double n)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#fcb6ed5a7bbedfcd70b7574ca5c9939a" class="el">operator/=</a> (<a href="classTime.md" class="el">Time</a> other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#93c269f3dbbc04ad3f0d2478d823c875" class="el">operator/=</a> (double n)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#02e4d75bd33fe10d390cc21af6c60699" class="el">operator-</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#af68bbc29f8f67689346bf513daeb999" class="el">GetSeconds</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">double </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#6d0dccfd670d8054cab0856767014333" class="el">GetSecondsDouble</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#7d29718bb8d003466def06e16b081af0" class="el">SetSeconds</a> (double seconds)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#531091c476e91a36265d9bd259c3707b" class="el">GetTicks</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#02aba8da6d5320e16fc9e592d88a3c65" class="el">SetTicks</a> (<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> ticks)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#027b58e95feed77348d2b6d89eb3d4d9" class="el">IsZero</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#b06851700fc46fe85eb114efb5bf6910" class="el">GetFrame</a> (double fps) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#d8f556b71eb244d9f6a52d9ada687156" class="el">GetFrameInt</a> (double fps) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#20854ae56548bf823cbd741c61071707" class="el">SetFrame</a> (double frame, double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#9d784cccadb0862dbfebd27bcc18c4b1" class="el">StepFrame</a> (double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#5d065533f9ce660c9a2f2b8eb8d939bd" class="el">StepFrames</a> (double frames, double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#d906c6ad1e43ea44d77a066c596e6f91" class="el">SnapToFrame</a> (double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#189d89bad49739996a866265d4a84a06" class="el">FloorToFrame</a> (double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#3e8f798364ac404f56233368db8ec2af" class="el">CeilToFrame</a> (double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#ecd76390872bc74ce3e967f680da7d50" class="el">GetCell</a> (double fps) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#2b2526295f8bda240ea0b9c463402ed9" class="el">SetCell</a> (double cell, double fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#1661c0040251cbec0d8d24b6d52a315c" class="el">ToString</a> (double fps, int timeunits, BOOL treatasdelta=FALSE) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#828124976301d3e43c03e41aff79331d" class="el">SetTagged</a> (BOOL state=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#51da836da857369c7b1749113ea110ce" class="el">IsTagged</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#c80501522212e52657cce60620c3b0ac" class="el">SetMax</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#f3ae7505b95b4f21c7add9ec531543d6" class="el">SetMin</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTime.md#3f8e708f9975407c2c33b78ba4eb531e" class="el">SetMinS