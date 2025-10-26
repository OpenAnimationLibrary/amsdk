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

# HHashObj.h

[Go to the documentation of this file.](HHashObj_8h.md)

<div class="fragment">

``` fragment
00001 // BC  1/12/2005  \BobL120\Include\SDK\HHashObj.h
00002 
00003 #define __HHASHOBJ_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HASHTIME_H
00008 #include "HashTime.h"
00009 #endif
00010 
00011 #ifndef __QUATERNI_H
00012 #include "Quaterni.h"
00013 #endif
00014 
00015 #ifndef __ROTATE_H
00016 #include "Rotate.h"
00017 #endif
00018 
00019 #ifndef __PATCHID_H
00020 #include "PatchID.h"
00021 #endif
00022 
00023 #ifndef __RGBFLOAT_H
00024 #include "RGBFloat.h"
00025 #endif
00026 
00027 #ifndef __OBJTYPE_H
00028 #include "ObjType.h"
00029 #endif
00030 
00031 #ifndef __IEMODEL_H
00032 #include "IEModel.h"
00033 #endif
00034 
00035 #ifndef __TIMERANG_H
00036 #include "TimeRang.h"
00037 #endif
00038 
00039 #ifndef __FILECONS_H
00040 enum { SMPTE, FRAMES, CELS };
00041 #endif
00042 
00043 /**********************************************************
00044 HTreeObject
00045    HAnimObject
00046       HCP   - HPC.h
00047          HHookCP - HCP.h
00048       HHashObject
00049          HPropertyDriver - HPropDri.h
00050             HAttrDriver -
00051             HBiasDriver
00052             HConstDriver
00053             HPropertyShortcut
00054             HFloatDriver
00055                HChannelDriver
00056             HRelationMDShortcut
00057             HRotateDriver
00058                HEulerRotateDriver
00059                HQuaternionRotateDriver
00060                HVectorRotateDriver
00061             HTransformDriver
00062             HVectorDriverNoSubs
00063             HVector2Driver
00064          HProperty - HPropert.h
00065             HBiasProperty
00066             HBoolProperty
00067             HContainerProperty
00068                HAttrProperty
00069                HFileInfoProperty
00070                HCategoryProperty
00071                   HBoolCategoryProperty
00072                   HTypeCategoryProperty
00073             HFloatProperty
00074                HPercentProperty
00075             HIntProperty
00076             HRotateProperty
00077             HStringProperty
00078                HFilenameProperty
00079             HTimeProperty
00080             HTransformProperty
00081             HTypeProperty
00082             HVectorProperty
00083                HColorProperty
00084                HScaleProperty
00085                HTranslateProperty
00086             HVectorPropertyNoSubs
00087             HVector2Property
00088             HPointerProperty
00089                HBitmapProperty
00090          HGroupCP - HCP.cpp
00091          HGroup   - HCP.cpp
00092          HGroupContainer - HCP.CPP
00093          HBoneCacheContainer
00094          HBoneCache - HModel.cpp
00095             HObjectCache
00096                HSegmentCache
00097                   HModelCache
00098                HCamerCache
00099                HPropCache
00100                HFXCache
00101                   HForceCache
00102                   HMatFXCache
00103                   HVolFXCache
00104                      HLightCache
00105          HLightCacheContainer                     
00106          HBoneContainer
00107          HBone
00108             HObject
00109                HSegment
00110                   HModel
00111                HCamera
00112                HProp
00113                HFX
00114                   HForce
00115                   HMatFX
00116                   HVolFX
00117                      HLight
00118          HLightContainer
00119          HClip
00120             HBitmap
00121                HDecal
00122          HDecalClip
00123          HDecalClipContainer
00124          HDecalStamp
00125          HDecalStampContainer
00126          HDecalContainer
00127          HRelationContainer
00128          HRelation
00129          HActionCache
00130             HRelationKey
00131          HAction
00132          HObjectCacheContainer
00133          HActionCacheContainer
00134          HChor
00135          HProject
00136          HAnimObjectShortcut
00137          HSplineContainer
00138       HSPline
00139 HPatch
00140    HPatch5
00141 HChannelCP
00142 HProgressBar
00143 HPropertyInfo
00144    HBiasPropertyInfo
00145    HBoolPropertyInfo
00146    HAttrPropertyInfo
00147    HFileInfoPropertyInfo
00148    HFloatPropertyInfo
00149       HPercentPropertyInfo
00150    HIntPropertyInfo
00151    HRotatePropertyInfo
00152    HStringPropertyInfo
00153       HFilenamePropertyInfo
00154    HTimePropertyInfo
00155    HTransformPropertyInfo
00156    HTypePropertyInfo
00157    HVectorPropertyInfo
00158       HColorPropertyInfo
00159       HScalePropertyInfoInfo
00160       HTranslatPropertyInfo
00161    HVectorPropertyNoSubsInfo
00162    HVector2PropertyInfo
00163    HPointerPropertyInfo
00164 HTypeInfo   
00165 **********************************************************/
00166 
00167 class HProperty;
00168 class HAnimObject;
00169 class HBone;
00170 class HCategoryProperty;
00171 class HUserCategoryProperty;
00172 class HHashObject;
00173 class HashStream;
00174 class HAnimObjectShortcut;
00175 class HPropertyDriver;
00176 
00177 //*********************************************************
00178 //** HTreeObject
00179 //*********************************************************
00180 class PLUGINEXPORT HTreeObject 
00181 {
00182 public:
00183 // Retrieval   
00184    HProperty *GetPropertyAt( int i );
00185    ObjectType GetObjectType();
00186    int GetType();
00187    
00188    void  operator delete( void *ptr ) { DeleteHandle( (HTreeObject *)ptr ); }
00189    static void DeleteHandle(HTreeObject *handle);
00190    
00191    BOOL IsModified();
00192    void OnModified();
00193    HTreeObject *FindChildByName( char *matchname );
00194    HTreeObject *FindChildByTreeName( char *treename );
00195    void ExpandInProjectBar(BOOL expand);
00196    void RefreshInProjectBar( BOOL updatenow=FALSE );
00197    void HilightInProjectBar();
00198       
00199    // These 3 functions allow to walk the complete tree hierarchy and skip possible objects based on paramatwers passed in
00200    enum Skip { SKIPNONE=0x00, SKIPINVISIBLE=0x01, SKIPFILTERED=0x02, SKIPADVANCED=0x04, SKIPFOLDERS=0x08 };
00201    HTreeObject *GetTreeParent( UINT skip=SKIPINVISIBLE|SKIPFILTERED );
00202    HTreeObject *GetTreeProgeny( UINT skip=SKIPINVISIBLE|SKIPFILTERED );
00203    HTreeObject *GetTreeSibling( UINT skip=SKIPINVISIBLE|SKIPFILTERED );
00204    
00205    HTreeObject *GetParent(); // Skips user containers, and doesn't include classes not derived off HashObject (CPs)//
00206    void SetParent(HTreeObject *parent);
00207    void ReassignPtr( void *ptruplink, HTreeObject *newvalue );
00208    HAnimObject *GetAnimObject();
00209    HAnimObject *GetAnimObjectNotProperty();
00210    
00211    String GetMatchName();
00212    String GetFileName();
00213    String GetFullName();
00214 
00215    HBone *IsBone(); //returns this as an HBone if it is one, or NULL;
00216    BOOL IsActionObjectChild();
00217    
00218    void InterpolateObjects( Time time, BOOL notify=TRUE );
00219    void Interpolate( Time time, BOOL notify=TRUE );
00220    void OffInterpolate( HProperty *dueto );
00221    
00222    HHashObject *IsHashObject();
00223    HAnimObjectShortcut *IsAnimObjectShortcut();
00224    HPropertyDriver *IsPropertyDriver();
00225    
00226    BOOL Save( HashStream &hs );
00227    void SetVisible(BOOL visible);
00228 
00229    void SetTempBit( BOOL state );
00230    BOOL GetTempBit();
00231    
00232    HProperty *IsProperty();
00233 };
00234 
00235 class HObject;
00236 //*********************************************************
00237 //** HAnimObject
00238 //*********************************************************
00239 class PLUGINEXPORT HAnimObject : public HTreeObject
00240 {  
00241 public:
00242    
00243    BOOL IsCache();
00244    HAnimObject *GetCache();// will return it self if it is the cache
00245    Time GetFirstKey( BOOL *isselected=NULL );
00246    Time GetLastKey();
00247    Time GetNextKey( Time time, BOOL *isselected=NULL );
00248    Time GetPrevKey( Time time );
00249    BOOL IsKey( Time time );
00250    int  CountKeys();
00251    BOOL DeleteKey( Time time, BOOL storeundo = TRUE );
00252    BOOL Reduce( float error );
00253    void DeleteKeys( TimeRange range );
00254    void TransformKeys( TimeRange range, float scale, Time offset, BOOL issnaptoint );
00255    void RemoveDrivers();
00256    
00257    HObject *GetObject();
00258    HObject *GetActionObject();
00259 };
00260 
00261 //*********************************************************
00262 //** HHashObject
00263 //*********************************************************
00264 class PLUGINEXPORT HHashObject : public HAnimObject
00265 {
00266 public:
00267 // Retrieval
00268    char *GetName();
00269    void SetName(const char *name);
00270    ObjectType GetObjectType(); // Only here for backward compatibility (It is now in HTreeObject)
00271    BOOL IsKindOfBoneCache();
00272    
00273 // Hierachy
00274    HHashObject *GetChild(); // Skips user containers, and doesn't include classes not derived off HashObject (CPs)//
00275    void SetChild(HHashObject *child);
00276    HHashObject *GetSibling(); // Skips user containers, and doesn't include classes not derived off HashObject (CPs)//
00277    void SetSibling(HHashObject *sibling);
00278    HHashObject *GetSiblingSame(); // Skips user containers, and doesn't include classes not derived off HashObject (CPs)//
00279    HHashObject *GetParentOfType(ObjectType ot); // Skips user containers, and doesn't include classes not derived off HashObject (CPs)//
00280    HHashObject *GetHeadInstance();
00281    HHashObject *GetNextInstance(HHashObject *instance);
00282    HCategoryProperty *GetPluginProperties();
00283    HUserCategoryProperty *CreateUserCategoryProperty(); // will return the User Properrties if it already exists
00284    HUserCategoryProperty *GetUserCategoryProperty();
00285    
00286    void InsertChildAtTail( HHashObject *child, BOOL modify = TRUE );
00287    void InsertChildAtHead( HHashObject *child );
00288    void InsertChildAtTailOfType( HHashObject *child );
00289    void InsertChildAtHeadOfType( HHashObject *child );
00290    void InsertChildAfterObject( HHashObject *child, HHashObject *after );
00291    void InsertChildAlpha( HHashObject *child, BOOL modify=TRUE );
00292    void InsertChildOfTypeAlpha( HHashObject *child );
00293    void InsertSibling( HHashObject *child );
00294    
00295    void Unstitch();
00296    void UnstitchWithChildren(BOOL markparentmodified = TRUE);
00297    void Move( HHashObject *parent, HHashObject *oldersibling, BOOL select=TRUE, BOOL markparentmodified=TRUE );
00298    void MoveWithChildren( HHashObject *parent, HHashObject *oldersibling, BOOL select=TRUE, BOOL markparentmodified=TRUE );
00299    void MarkViewsNeedDrawn();
00300 };
00301 
00302 //*********************************************************
00303 //** HAnimObjectShortcut
00304 //*********************************************************
00305 class PLUGINEXPORT HAnimObjectShortcut : public HHashObject
00306 {
00307 public:
00308    static HAnimObjectShortcut *New(const char *name, BOOL isforrelation);
00309    HAnimObject *GetAnimObject();
00310    
00311    HAnimObjectShortcut *MakeCopy();
00312    void Copy(HAnimObjectShortcut *other);
00313 };
00314 
00315 #endif
00316 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
