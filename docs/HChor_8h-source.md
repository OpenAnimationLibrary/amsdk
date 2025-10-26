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

# HChor.h

[Go to the documentation of this file.](HChor_8h.md)

<div class="fragment">

``` fragment
00001 // BC  11/30/2004  \BobL120\Include\SDK\HChor.h
00002 
00003 #define __HCHOR_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 
00011 class HModel;
00012 class HProp;
00013 class HCamera;
00014 class HForce;
00015 class HMatFX;
00016 class HMCDevice;
00017 class HLightListNode;
00018 class HChorContainer;
00019 class HFileInfoProperty;
00020 class HTimeProperty;
00021 class HVectorProperty;
00022 class HIntProperty;
00023 class HFloatProperty;
00024 class HBoolProperty;
00025 class HGroup;
00026 
00027 //*********************************************************
00028 //** HChor
00029 //*********************************************************
00030 class PLUGINEXPORT HChor : public HHashObject
00031 {
00032 public:
00033 // Creation
00034    static HChor *New();
00035 
00036 // Properties   
00037    HFileInfoProperty *GetFileInfo();
00038    HTimeProperty *GetTotalTime();
00039    HVectorProperty *GetForce();
00040    HIntProperty *GetRigidSubSamples();
00041    HFloatProperty *GetRigidDrag();
00042    HBoolProperty *GetDisplayWhileSimulating();
00043    
00044 // Operations
00045    void CreateFrame( Time time );
00046    void Dirty();
00047    Time GetTime();
00048    void SetTime(Time time);
00049    void SetTimeWithSound(Time time );
00050    
00051 // Traversal
00052    HChorContainer *GetParentChorContainer();
00053    HModel  *GetChildModel();
00054    HProp   *GetChildProp();
00055    HCamera *GetChildCamera();
00056    HForce  *GetChildForce();
00057    HMatFX  *GetChildMatFX();
00058    HMCDevice *GetChildMCDevice();
00059    HLightListNode *GetHeadLightList();
00060    HLightListNode *GetHeadAllLightList();
00061 
00062 // Export IEModel classes
00063    IEPatchModel *BuildExportModel(IEModelParms *iemp, Time time, const char *modelmapfilename);
00064    IEPolyModel  *BuildExportModel(IEPolyModelParms *iemp, Time time, const char *modelmapfilename);
00065    IEPolyModel  *BuildExportModel(IEPolyModelParms *iemp, HModel *hmodel, HGroup *hgroup, BOOL markpatchesinvisible, VertexInfo *vertexinfo);
00066    
00067    BOOL Intersect( Vector &p, Vector &d, Vector &hitp, Vector &hitn, float maxdist ); // old for backward compat, flatness = .160
00068    BOOL Intersect( Vector &p, Vector &d, Vector &hitp, Vector &hitn, float maxdist, float flatness ); 
00069 };
00070 
00071 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
