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

# HForce.h

[Go to the documentation of this file.](HForce_8h.md)

<div class="fragment">

``` fragment
00001 // BC  3/1/2005  \BobL120\Include\SDK\HForce.h
00002 
00003 #define __HFORCE_H
00004 
00005 #ifndef __HOBJECT_H
00006 #include "HObject.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 
00011 //*********************************************************
00012 //** HForceCache
00013 //*********************************************************
00014 class PLUGINEXPORT HForceCache : public HObjectCache
00015 {
00016 public:
00017    enum { F_FAN, F_VORTEX, F_FRICTION };
00018    HFloatProperty *GetMagnitude();
00019 };
00020 
00021 //*********************************************************
00022 //** HForce
00023 //*********************************************************
00024 class PLUGINEXPORT HForce : public HObject
00025 {
00026 public:
00027    HFloatProperty *GetMagnitude();
00028    
00029    HForce *GetNextForceInChor();
00030    Vector  GetForce( const Vector &pos, const Vector &vel );
00031 };
00032 
00033 /*
00034 TODO
00035 TurbNodeHead
00036 Kind
00037 */
00038 
00039 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
