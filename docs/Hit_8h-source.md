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

# Hit.h

[Go to the documentation of this file.](Hit_8h.md)

<div class="fragment">

``` fragment
00001 // BC  5/3/2004  \Bob110\Include\Hit.h
00002 
00003 #define __HIT_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #ifndef __DATATYPE_H
00009 #include "DataType.h"
00010 #endif
00011 
00012 class RObject;
00013 class BinNode;
00014 class RayPatch;
00015 class Follicle;
00016 class HairCubic;
00017 
00018 class Hit {
00019 public:
00020    double               t;
00021    Vector               p,
00022                         m_truen;      
00023    RObject              *object;
00024    BinNode              *baseobject;
00025    RayPatch             *raypatch;
00026    Follicle             *follicle;
00027    HairCubic            *m_haircubic;
00028    float                u, v;
00029    int                  offset,
00030                         m_polyid;
00031    ULONG                m_patchid;
00032    union {
00033       ULONG             flags;
00034       struct {
00035          BITFIELDS32    isexitblobby                        : 1,
00036                         is5point                            : 1,
00037                         unused                              : 1,
00038                         isblobby                            : 1,
00039                         side                                : 1, // for triangle intersection
00040                         isflipped                           : 1,
00041                         ishit                               : 1,
00042                         m_isadditivetransparency            : 1,
00043                         m_ismultiplyspecularbytransparency  : 1;
00044       };
00045    };
00046 
00047    Hit()                  { Empty(); }
00048    void Empty()           { m_polyid = -1; 
00049                           baseobject = NULL; 
00050                           t = 0; 
00051                           object = NULL; 
00052                           follicle = NULL; 
00053                           flags = 0; 
00054                           offset = 0; }
00055 };
00056 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
