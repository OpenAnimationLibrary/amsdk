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

# HCamera.h

[Go to the documentation of this file.](HCamera_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  6/12/2003  \Dan105\Include\SDK\HCamera.h
00002 
00003 #define __HCAMERA_H
00004 
00005 #ifndef __HOBJECT_H
00006 #include "HObject.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 
00011 //*********************************************************
00012 //** HCameraCache
00013 //*********************************************************
00014 class PLUGINEXPORT HCameraCache : public HObjectCache
00015 {
00016 public:
00017    enum CAMERATYPE { CT_ORTHOGONAL, CT_PERSPECTIVE, CT_GAME } ;
00018 
00019 //Properties   
00020    HTypeProperty  *GetType();
00021    HColorProperty *GetBackGroundColor();
00022    HFloatProperty *GetFocalLength();
00023    HFloatProperty *GetFocalDistance();
00024    HFloatProperty *GetGlobalAmbiance();
00025 };
00026 
00027 //*********************************************************
00028 //** HCamera
00029 //*********************************************************
00030 class PLUGINEXPORT HCamera : public HObject
00031 {
00032 public:
00033 //Properties   
00034    HColorProperty *GetBackGroundColor();
00035    HFloatProperty *GetFocalLength();
00036    HFloatProperty *GetFocalDistance();
00037    HFloatProperty *GetGlobalAmbiance();
00038 
00039    HCamera *GetNextCameraInChor(); // Use With HChor::GetChildCamera
00040 };
00041 
00042 // ToDO
00043 // BitFields
00044 // RenderSettings - Cache
00045 // OutputSettings - Instance
00046 // Rotoscope/Fog Rotoscope
00047 // Camera Type
00048 
00049 
00050 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
