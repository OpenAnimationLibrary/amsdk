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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# OldAttr.h

[Go to the documentation of this file.](OldAttr_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  7/23/2004  \DanLP115\Include\OldAttr.h
00002 
00003 #define __OLDATTR_H
00004 
00005 #ifndef __RGBFLOAT_INL
00006 #include "RGBFloat.inl"
00007 #endif
00008 
00009 class Attr {
00010 public:
00011    char              m_name[256];
00012    RGBFloat       m_diffusecolor;
00013    float             m_diffusefalloff;
00014    float             m_ambiance;
00015    RGBFloat       m_specularcolor;
00016    float             m_specularsize;
00017    float             m_specularintensity;
00018    float             m_roughness;
00019    float             m_roughnessscale;
00020    float             m_transparency;
00021    float             m_density;
00022    float             m_refraction;
00023    float             m_translucency;
00024    float             m_reflectivity;
00025    float             m_reflectivityfalloff;
00026    float             m_radiance;
00027    BOOL              m_isglow;
00028 
00029    Attr() {
00030       m_name[0] = '\0';
00031       m_diffusecolor.Set( 0.0f );
00032       m_diffusefalloff    = 1.0f;
00033       m_ambiance          = 0.0f;
00034       m_roughness         = 0.0f;
00035       m_roughnessscale    = 1.0f;
00036       m_reflectivity      = 0.0f;
00037       m_transparency      = 0.0f;
00038       m_refraction        = 1.0f;
00039       m_specularcolor.Set( 0.0f );
00040       m_specularsize      = 0.0f;
00041       m_specularintensity = 1.0f;
00042       m_density = 0.0f;
00043       m_translucency = 0.0f;
00044       m_radiance = 1.0f;
00045       m_reflectivityfalloff = 0.0f;
00046       m_isglow = FALSE;
00047    }
00048    
00049    int operator == ( const Attr &other ) const 
00050    { 
00051       return m_diffusecolor == other.m_diffusecolor &&
00052       m_diffusefalloff == other.m_diffusefalloff &&
00053       m_ambiance == other.m_ambiance &&
00054       m_specularcolor == other.m_specularcolor &&
00055       m_specularsize == other.m_specularsize &&
00056       m_specularintensity == other.m_specularintensity &&
00057       m_roughness == other.m_roughness &&
00058       m_roughnessscale == other.m_roughnessscale &&
00059       m_transparency == other.m_transparency &&
00060       m_density == other.m_density &&
00061       m_refraction == other.m_refraction &&
00062       m_translucency == other.m_translucency &&
00063       m_reflectivity == other.m_reflectivity &&
00064       m_reflectivityfalloff == other.m_reflectivityfalloff &&
00065       m_radiance == other.m_radiance &&
00066       m_isglow == other.m_isglow;
00067    }
00068 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
