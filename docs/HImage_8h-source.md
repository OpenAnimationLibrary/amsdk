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

# HImage.h

[Go to the documentation of this file.](HImage_8h.md)

<div class="fragment">

``` fragment
00001 // NAP  12/20/2004  \Noel120\Include\SDK\HImage.h
00002 
00003 #define __HIMAGE_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 #ifndef __COLORBUF_INL
00010 #include "ColorBuf.inl"
00011 #endif
00012 
00013 class BitmapNode;
00014 class HFilenameProperty;
00015 class HColorProperty;
00016 class HFloatProperty;
00017 class HBoolProperty;
00018 class HIntProperty;
00019 
00020 //*********************************************************
00021 //** HClip
00022 //*********************************************************
00023 class PLUGINEXPORT HClip : public HHashObject
00024 {
00025 public:
00026    int GetWidth( float repeat );
00027    int GetHeight( float repeat );
00028    ColorBuf GetBKColor();
00029    BOOL ReadBitmap( float x, float y, RGBFloat *diffuse, float *opacity, float pixelwidth, Time time, const Vector2 &repeat, BOOL isseamless  );
00030    /* don't use this one anymore, just for old plugins*/ BOOL ReadBitmap( float x, float y, ColorVector *diffuse, float *opacity, float pixelwidth, Time time, const Vector2 &repeat, BOOL isseamless  );
00031    
00032    BOOL ReadBumpmap( float x, float y, Vector2 &delta, float pixelwidth, Time time, const class Vector2 &repeat, BOOL isseamless  );
00033 };
00034 
00035 //*********************************************************
00036 //** HImage
00037 //*********************************************************
00038 class PLUGINEXPORT HImage : public HClip
00039 {
00040 public:
00041    HFilenameProperty *GetFilename();
00042    HColorProperty    *GetKeyColor();
00043    HFloatProperty    *GetGamma();
00044    HBoolProperty     *GetIsStoreCompressed();
00045    BitmapNode        *GetBitmapNode();
00046 };
00047 
00048 //*********************************************************
00049 //** HStill
00050 //*********************************************************
00051 class PLUGINEXPORT HStill : public HImage
00052 {
00053 public:
00054 };
00055 
00056 //*********************************************************
00057 //** HAnimation
00058 //*********************************************************
00059 class PLUGINEXPORT HAnimation : public HImage
00060 {
00061 public:
00062    HIntProperty  *GetCropStart();
00063    HIntProperty  *GetCropEnd();
00064    HFloatProperty *GetFps();
00065    HIntProperty   *GetCacheSize();
00066 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
