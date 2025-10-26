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

# HAction.h

[Go to the documentation of this file.](HAction_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  6/22/2004  \DanLP110\Include\SDK\HAction.h
00002 
00003 #define __HACTION_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 
00011 class HActionCacheContainer;
00012 class HChor;
00013 class HActionCache;
00014 class HBone;
00015 class HModel;
00016 class HModelCache;
00017 class HPropertyDriver;
00018 class HProperty;
00019 class HFileInfoProperty;
00020 class HBoolCategoryProperty;
00021 class HTimeProperty;
00022 class HTimeRangeProperty;
00023 class HFloatProperty;
00024 class HPointerProperty;
00025 class HTypeProperty;
00026 class HPercentProperty;
00027 class HBoolProperty;
00028 
00029 //*********************************************************
00030 //** HAction
00031 //*********************************************************
00032 class PLUGINEXPORT HAction : public HHashObject
00033 {
00034 public:
00035 //Properties
00036    HTimeRangeProperty *GetCropRange();
00037    HTimeRangeProperty *GetChorRange();
00038    HFloatProperty *GetRepeatCount();
00039    HTimeProperty *GetCycleLength();
00040    HTypeProperty *GetBlendMethod(); enum BlendMethod { REPLACE, ADD, BLEND };
00041    HPercentProperty *GetBlendRatio();
00042    HBoolProperty *GetIsHoldLastFrame();
00043    HBoolProperty *GetIsPostTransition();
00044    HPercentProperty *GetEase();
00045    
00046 //Operations
00047    Time GetTotalTime();
00048    float GetScaleFactor();
00049 
00050 //Traversal
00051    HBone *GetParentBone();
00052    HActionCache *GetActionCache();
00053    HModel *GetParentModel();
00054 
00055    HChor *GetChor();
00056 };
00057 
00058 //*********************************************************
00059 //** HActionCache
00060 //*********************************************************
00061 class PLUGINEXPORT HActionCache : public HHashObject
00062 {
00063 public:
00064    char *GetName();
00065 // Properties
00066    HFileInfoProperty *GetFileInfo();
00067 
00068    HBoolCategoryProperty *GetHasStrideLength();
00069    HFloatProperty *GetStrideLength();
00070    HTimeRangeProperty *GetStrideRange();
00071    
00072    HTypeProperty *GetScaleMethod(); enum ScaleMethod { SCALENONE, SCALELENGTH, SCALEPOSITION }; // advanced
00073    HPointerProperty *GetScaleBone();
00074    
00075 //Traversal
00076    HActionCacheContainer *GetParentActionCacheContainer();
00077    HChor *GetChor();
00078    HActionCache *GetSiblingActionCache(); // use this over GetSibling because ActionCaches get moved if the Action is currently being edited with a model
00079 
00080 //Operations
00081    HModelCache *GetDefaultModelCache();
00082    void SetDefaultModelCache(const char *name);
00083    void SetDefaultModelCache(HModelCache *mch);
00084    Time GetTotalTime();
00085    HActionCache *CreateUncontrainedActionCache(HModel *mh, float errortolerance);
00086    HPropertyDriver *CreateStorageDriver( HProperty *var );
00087    float GetScaleFactor();
00088    float GetScaleStandard();
00089    
00090 // HActionCache Creation   
00091    static HActionCache *New(const char *name=NULL, BOOL embedded=TRUE, BOOL insertintoactioncachecontainer=TRUE);
00092 
00093 // HActionCache Editing
00094    HModel *EditWithModelCache(HModelCache *hmc);
00095    void EndEditWithModelCache(HModel *hm); // pass in the HModel returned from EditWithModelCache
00096    void EndEditWithModelCache(); // not supported anymore (use the one that takes a HModel *)
00097    
00098 };
00099 
00100 //*********************************************************
00101 //** HChorAction
00102 //*********************************************************
00103 class PLUGINEXPORT HChorAction : public HActionCache
00104 {
00105 public:
00106    HTypeProperty *GetBlendMethod(); enum BlendMethod { REPLACE, ADD, BLEND };
00107 
00108 };
00109 
00110 
00111 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
