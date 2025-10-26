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

# HProject.h

[Go to the documentation of this file.](HProject_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  3/29/2004  \DanLP110\Include\SDK\HProject.h
00002 
00003 #define __HPROJECT_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HHASHOBJ_H
00008 #include "HHashObj.h"
00009 #endif
00010 
00011 class HModelCache;
00012 class HSoundCache;
00013 class HClip;
00014 
00015 //*********************************************************
00016 //** HObjectCacheContainer
00017 //*********************************************************
00018 class PLUGINEXPORT HObjectCacheContainer : public HHashObject
00019 {
00020 public:
00021    HModelCache *GetChildModelCache();
00022 };
00023 
00024 //*********************************************************
00025 //** HClipCacheContainer
00026 //*********************************************************
00027 class PLUGINEXPORT HClipCacheContainer : public HHashObject
00028 {
00029 public:
00030    BOOL BrowseClip(String &filename, BOOL *issequence); // Opens File Dialog
00031    HClip *CreateClip(const String &filename, BOOL issequence); // Loads file
00032 };
00033 
00034 //*********************************************************
00035 //** HMaterialCacheContainer
00036 //*********************************************************
00037 class PLUGINEXPORT HMaterialCacheContainer : public HObjectCacheContainer
00038 {
00039 public:
00040 };
00041 
00042 class HActionCache;
00043 //*********************************************************
00044 //** HActionCacheContainer
00045 //*********************************************************
00046 class PLUGINEXPORT HActionCacheContainer : public HObjectCacheContainer
00047 {
00048 public:
00049    HActionCache *GetChildActionCache();// use this over GetChild because ActionCaches get moved if the Action is currently being edited with a model
00050 };
00051 
00052 //*********************************************************
00053 //** HActionShortcutContainer
00054 //*********************************************************
00055 class HActionShortcutContainer : public HObjectCacheContainer
00056 {
00057 public:
00058 };
00059 
00060 //*********************************************************
00061 //** HSoundContainer
00062 //*********************************************************
00063 class PLUGINEXPORT HSoundContainer : public HHashObject
00064 {
00065 public:
00066    HSoundCache *GetChildSoundCache();
00067 };
00068 
00069 class HChor;
00070 //*********************************************************
00071 //** HChorContainer
00072 //*********************************************************
00073 class PLUGINEXPORT HChorContainer : public HObjectCacheContainer
00074 {
00075 public:
00076    HChor *GetChildChor();
00077 };
00078 
00079 class HClip;
00080 //*********************************************************
00081 //** HProject
00082 //*********************************************************
00083 class PLUGINEXPORT HProject : public HHashObject
00084 {
00085 public:
00086    float GetFPS();
00087    HObjectCacheContainer *GetChildObjectCacheContainer();
00088    HClipCacheContainer *GetChildClipCacheContainer();
00089    HMaterialCacheContainer *GetChildMaterialCacheContainer();
00090    HActionCacheContainer *GetChildActionCacheContainer();
00091    HChorContainer *GetChildChorContainer();
00092    
00093    HClip *AddClip(const String &filename, BOOL issequence);
00094    
00095    void DeselectAll();
00096    void SetTime( Time time );
00097    void UpdateAllViews( BOOL force=FALSE );
00098 };
00099 
00100 // Retrieval
00101 PLUGINEXPORT HProject *GetHProject();
00102 
00103 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
