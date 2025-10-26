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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# HSound.h

[Go to the documentation of this file.](HSound_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  12/4/2002  \Dan100\Include\SDK\HSound.h
00002 
00003 #define __HSOUND_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 class HFilenameProperty;
00010 class HTimeProperty;
00011 class HPercentProperty;
00012 class HBoolProperty;
00013 
00014 class PLUGINEXPORT HSoundCache : public HHashObject
00015 {
00016 public:
00017    HFilenameProperty  *GetFilename();
00018    HTimeProperty *GetStart();
00019    HTimeProperty *GetEnd();
00020    HTimeProperty *GetLength();
00021    HPercentProperty *GetVolume();
00022    HBoolProperty *GetMute();
00023 };
00024 
00025 class PLUGINEXPORT HSound : public HHashObject
00026 {
00027 public:
00028    HTimeRangeProperty *GetCrop();
00029    HTimeProperty *GetStart();
00030    HTimeProperty *GetEnd();
00031    HTimeProperty *GetLength();
00032    HPercentProperty *GetVolume();
00033    HBoolProperty *GetMute();
00034 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
