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

# HMCDevice.h

[Go to the documentation of this file.](HMCDevice_8h.md)

<div class="fragment">

``` fragment
00001 // KB  5/15/01  \Ken90\Include\SDK\HMCDevice.h
00002 
00003 #define __HMCDEVICE_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HHASHOBJ_H
00008 #include "HHashObj.h"
00009 #endif
00010 
00011 //*********************************************************
00012 //** HMCDeviceCache
00013 //*********************************************************
00014 class PLUGINEXPORT HMCDeviceCache : public HObjectCache
00015 {
00016 public:
00017 };
00018 
00019 //*********************************************************
00020 //** HMCDevice
00021 //*********************************************************
00022 class PLUGINEXPORT HMCDevice : public HObject
00023 {
00024 public:
00025 };
00026 
00027 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
