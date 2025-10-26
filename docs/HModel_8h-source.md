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

# HModel.h

[Go to the documentation of this file.](HModel_8h.md)

<div class="fragment">

``` fragment
00001 // BC  10/13/2004  \BobL115\Include\SDK\HModel.h
00002 
00003 #define __HMODEL_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HSEGMENT_H
00008 #include "HSegment.h"
00009 #endif
00010 
00011 class HDecalContainer;
00012 class HGroupCP;
00013 class HObjectCacheContainer;
00014 class HAction;
00015 class HChor;
00016 class HModel;
00017 class HGroup;
00018 class HCP;
00019 class HSpline;
00020 class HPatch;
00021 class HPatch5;
00022 class HAttrProperty;
00023 class HGroupContainer;
00024 class HDecalContainer;
00025 class HSplineContainer;
00026 class HLightCacheContainer;
00027 class HLightContainer;
00028 class HBoneCacheContainer;
00029 class HBoneContainer;
00030 class HLightListNode;
00031 class HDecal;
00032 class HRelationContainer;
00033 class HPolyModifierShortcut;
00034 class HGroupNode;
00035 class HPolyModifierNode;
00036 class PolyModifier;
00037 
00038 //*********************************************************
00039 //** HModelCache
00040 //*********************************************************
00041 class PLUGINEXPORT HModelCache : public HSegmentCache
00042 {
00043 public:
00044 // Properties
00045    HFileInfoProperty  *GetFileInfo();
00046    HAttrProperty      *GetAttr();
00047 
00048 // Traversal
00049    HModelCache *GetSiblingModelCache();
00050    HObjectCacheContainer *GetParentObjectCacheContainer();
00051    
00052 // Export IEModel classes
00053    IEPatchModel *BuildExportModel(IEModelParms *iemp, const char *modelmapfilename);
00054    IEPolyModel  *BuildExportModel(IEPolyModelParms *iemp, const char *modelmapfilename);
00055 
00056 // Import IEModel classes
00057    BOOL MergeIEModel(IEPatchModel *model, const char *name, float peaktolerance, BOOL addgroup, BOOL showprogressbar);
00058    BOOL MergeIEModel(IEPolyModel *model, const char *name, float peaktolerance, BOOL addgroup, BOOL showprogressbar);
00059    
00060 // Creation
00061    static HModelCache *New(const char *name=NULL, BOOL embedded=TRUE);
00062    HModel *NewInstance(HChor *);
00063    
00064    void SetChanged( BOOL modified = TRUE);
00065 
00066 // Spline Operations
00067    HSpline *GetHeadSpline();
00068    HSpline *CreateSpline(); // Be sure to add at least two CP's to the spline
00069    void DeleteSpline( HSpline *spline );
00070    BOOL AttachCPs( HCP *cp1, HCP *cp2 );
00071    BOOL AttachHook( HCP *cp1, HCP *cp2, float s );
00072       
00073    // Old style spline operations but still work great   
00074    HSpline *StartSpline( Vector *p1, Vector *p2);
00075    HCP *AddCP( HCP *cp, Vector *p );
00076    HCP *InsertCP( HCP **cpuplink, HCP *cp, Vector *p );
00077    BOOL DeleteCP( HCP **cpuplink, HCP *matchcp );
00078    void BreakSpline( HCP *cp );
00079 
00080    BOOL Make5PointPatch( HGroup *group );
00081    BOOL Make5PointPatch( HCP *cp1, HCP *cp2, HCP *cp3, HCP *cp4, HCP *cp5);
00082    
00083    void CopyExtrude( BOOL extrude, HGroupCP *grouptocopy, HGroupCP **newgroup );
00084 
00085 // Bone operations
00086 //      Example: modelcache->AddSegment(NULL, NULL, "Bone1", GetColor(modelcache->CountBones()));
00087    HSegmentCache *AddSegment(HBoneCache *parentbonecache, HBoneCache *afterbonecache, String &name, COLORREF color);
00088    int CountBones();
00089    
00090 // Group Operations
00091    void AddToTemporaryGroup( HGroupCP *gh );
00092    HGroup *CreateGroup(const String &name);
00093 
00094 // Patch Operations
00095    void FindPatches();
00096    HPatch *FindPatch(HCP *cp1,  HCP *cp2, HCP *cp3, HCP *cp4);
00097    HPatch5 *FindPatch(HCP *cp1,  HCP *cp2, HCP *cp3, HCP *cp4, HCP *cp5);
00098    UINT GetPatchCount();
00099    HPatch  *GetPatch(UINT index);
00100    HPatch5 *GetHeadPatch5();
00101    
00102 // Decal Operations
00103    HDecal *AddDecal(HClip *clipcache=NULL); // NULL will prompt   
00104    
00105 // Retrieval
00106    HDecalContainer *GetChildDecalContainer();
00107    HGroupContainer *GetChildGroupContainer();
00108    HBoneCacheContainer   *GetChildBoneCacheContainer();
00109    HLightCacheContainer  *GetChildLightCacheContainer();
00110    HSplineContainer *GetChildSplineContainer();
00111 
00112    HRelationContainer *CreateRelationContainer();// Will return existing if already allocated
00113 };
00114 
00115 //*********************************************************
00116 //** HModel
00117 //*********************************************************
00118 class PLUGINEXPORT HModel : public HSegment
00119 {
00120 public:
00121 // Properties
00122    HAttrProperty *GetAttr();
00123    HModel *GetNextModelInChor(); // Use with HChor::GetChildModel()
00124 
00125    HBone *FindBone(const char *name);
00126    void ApplyAttrPropertyToPatches(); // Applies group's HAttrProperties to appropriate patches
00127 
00128 // Retrieval
00129    HDecalContainer *GetChildDecalContainer();
00130    HGroupContainer *GetChildGroupContainer();
00131    HBoneContainer   *GetChildBoneContainer();
00132    HLightContainer  *GetChildLightContainer();
00133    HSplineContainer *GetChildSplineContainer();
00134    HLightListNode   *GetHeadLightList();
00135    HRelationContainer *GetChildRelationContainer();
00136    HPolyModifierShortcut *GetPolyModifierHead();
00137    HGroupNode            *GetPolyModifierGroups();
00138    HChor                 *GetHChor();
00139    
00140 // Export IEModel classes
00141    IEPatchModel *BuildExportModel(IEModelParms *iemp, Time time, const char *modelmapfilename);
00142    IEPolyModel  *BuildExportModel(IEPolyModelParms *iemp, Time time, const char *modelmapfilename);
00143    
00144 // Operations
00145    void MakeCurrent();   
00146 };
00147 
00148 //*********************************************************
00149 //** HPathModel
00150 //*********************************************************
00151 class PLUGINEXPORT HPathModel : public HModel
00152 {
00153 public:
00154    HModelCache* GetPathModelCache();
00155 };
00156 
00157 //*********************************************************
00158 //** HPolyModifierShortcut
00159 //*********************************************************
00160 class PLUGINEXPORT HPolyModifierShortcut : public HHashObject
00161 {
00162 public:
00163    HPolyModifierShortcut *GetNextModifier();
00164    HPolyModifierNode *GetHPolyModifierNode();
00165    char *GetClassName();
00166 };
00167 
00168 //*********************************************************
00169 //** HPolyModifierNode
00170 //*********************************************************
00171 class PLUGINEXPORT HPolyModifierNode : public HHashObject
00172 {
00173 public:
00174    PolyModifier *GetPolyModifier();
00175    char *GetClassName();
00176 };
00177 
00178 //*********************************************************
00179 //** HGroupNode
00180 //*********************************************************
00181 class PLUGINEXPORT HGroupNode 
00182 {
00183 public:
00184    HGroupNode *GetNext();
00185    HGroup     *GetGroup();
00186 };
00187 
00188 
00189 #endif
00190 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
