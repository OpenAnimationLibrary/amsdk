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

# Texture.h

[Go to the documentation of this file.](Texture_8h.md)

<div class="fragment">

``` fragment
00001 // BC  6/14/2005  \Master120\Include\Texture.h
00002 
00003 #define __TEXTURE_H
00004 
00005 #include "DLLPlugi.h"
00006 
00007 class HTexInfo;
00008 class Vector;
00009 class HModel;
00010 class HGroup;
00011 class HObjectListNode;
00012 class HPointerPropertyBase;
00013 
00014 #define TEXTUREDLLVERSION 2
00015 
00016 class PLUGINEXPORT Texture : public DLLPlugin {  // this has a chance of breaking old texture plugins, if so, just export the bottom two functions below
00017 public:
00018    Texture() {}
00019    Texture(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}
00020 
00021 // RENDERING
00022    virtual BOOL Evaluate( const Vector &evalp, HTexInfo *texinfo ) = 0;
00023    virtual BOOL EvaluateTransparency( const Vector &evalp, HTexInfo *texinfo ) = 0;
00024    virtual HObjectListNode *GetPointerList( HPointerPropertyBase *prop ) { return NULL; }
00025    virtual void CheckOut( HHashObject *cache ) {}  // used copy instead, could remove this function
00026    virtual void OnNotifyNewProperty( HProperty *prop, const String &matchname ) {}
00027 
00028    // detect what we are currently applied to
00029    HModel *GetModel();  // this one should never be NULL
00030    HGroup *GetGroup();  // this one can be NULL, if not on a group
00031 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
