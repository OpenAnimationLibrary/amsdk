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

# HSegment.h

[Go to the documentation of this file.](HSegment_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/6/2003  \HBob110\Include\SDK\HSegment.h
00002 
00003 #define __HSEGMENT_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HOBJECT_H
00008 #include "HObject.h"
00009 #endif
00010 
00011 #ifndef __HCP_H
00012 #include "HCP.h"
00013 #endif
00014 
00015 class HGroupCP;
00016 //*********************************************************
00017 //** HSegmentCache
00018 //*********************************************************
00019 class PLUGINEXPORT HSegmentCache : public HObjectCache
00020 {
00021 public:
00022 // Creation
00023    static HSegmentCache *New(const char *name=NULL);
00024    
00025    BOOL OnDelete();
00026 
00027 // Properties
00028 //   HFloatProperty *GetFallOffRadius();
00029 //   HFloatProperty *GetFallOffEndRadius();
00030 //   HFloatProperty *GetFallOffPivotLength();
00031 //   HFloatProperty *GetFallOffEndLength();
00032    HBoolProperty *GetBoolCutter();
00033    
00034    HGroupCP *GetGroupCP(); // Group of cps this bone owns
00035    BOOL IsBooleanCutter(); // Use GetBoolCutter now, this is for backward compatibility
00036    BOOL AquireCP(HCP *cp);
00037 };
00038 
00039 //*********************************************************
00040 //** HSegment
00041 //*********************************************************
00042 class PLUGINEXPORT HSegment : public HObject
00043 {
00044 public:
00045 // Properties
00046 };
00047 
00048 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
