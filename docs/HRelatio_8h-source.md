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

# HRelatio.h

[Go to the documentation of this file.](HRelatio_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  2/13/2004  \DanLP110\Include\SDK\HRelatio.h
00002 
00003 #define __HRELATIO_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HHASHOBJ_H
00008 #include "HHashObj.h"
00009 #endif
00010 
00011 #ifndef __HACTION_H
00012 #include "HAction.h"
00013 #endif
00014 
00015 class HRelation;
00016 //*********************************************************
00017 //** HRelationContainer
00018 //*********************************************************
00019 class PLUGINEXPORT HRelationContainer : public HHashObject
00020 {
00021 public:
00022     HRelation *CreateRelation( HProperty *drivingproperty );
00023 };
00024 
00025 //*********************************************************
00026 //** HRelation
00027 //*********************************************************
00028 class PLUGINEXPORT HRelation : public HActionCache
00029 {
00030 public:
00031 
00032    HModel *StartEdit();
00033    void EndEdit(HModel *hm);
00034    
00035 //Properties
00036    HProperty *GetControllingProperty();
00037    HPercentProperty *GetEnforcement();
00038    HFloatProperty *RadiusFactor();
00039    HTimeProperty *GetLag();
00040 };
00041 
00042 //*********************************************************
00043 //** HRelationKey
00044 //*********************************************************
00045 class PLUGINEXPORT HRelationKey : public HHashObject
00046 {
00047 public:
00048 };
00049 
00050 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
