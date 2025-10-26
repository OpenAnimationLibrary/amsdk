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

# HObject.h

[Go to the documentation of this file.](HObject_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  8/4/2004  \DanLP110\Include\SDK\HObject.h
00002 
00003 #define __HOBJECT_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HBone_H
00008 #include "HBone.h"
00009 #endif
00010 
00011 class HChor;
00012 class HActionShortcutContainer;
00013 class HRelationContainer;
00014 class HAction;
00015 
00016 //*********************************************************
00017 //** HObjectCache
00018 //*********************************************************
00019 class PLUGINEXPORT HObjectCache : public HBoneCache
00020 {
00021 public:
00022 };
00023 
00024 //*********************************************************
00025 //** HObject
00026 //*********************************************************
00027 class PLUGINEXPORT HObject : public HBone
00028 {
00029 public:
00030 //Properties
00031    HBoolProperty *GetActive();
00032    HChor *GetChor();
00033    
00034    HActionShortcutContainer *GetActionShortcutContainer();
00035    HRelationContainer *GetRelationContainer();
00036    HAction *GetCurrentChorAction();
00037    HObject *MakeCopy(BOOL insertintochor=TRUE);
00038    
00039    void SetIsActionDeleted(BOOL bState);
00040    BOOL IsActionDeleted();
00041    HAnimObject *FindAnimObjectFromCache(HAnimObject *key);
00042 };
00043 
00044 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
