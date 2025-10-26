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

# DataType.h

[Go to the documentation of this file.](DataType_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/24/2002  \HRandy95\Include\DataType.h
00002 
00003 #define __DATATYPE_H
00004 
00005 typedef unsigned long  ULONG;
00006 typedef unsigned short UWORD;
00007 typedef unsigned char  UBYTE;
00008 typedef signed short   SWORD;
00009 typedef signed char    SBYTE;
00010 typedef short          SHORT;
00011 typedef unsigned short USHORT;
00012 typedef unsigned char  BITFIELDS8;
00013 typedef unsigned short BITFIELDS16;
00014 typedef unsigned long  BITFIELDS32;
00015 
00016 #define BIG_INT        2147483647
00017 #define SMALL_FLOAT    1e-8f
00018 #define BIG_FLOAT      1e8f
00019 #define BIG_LONG       0xFFFFFFFF // 4294967295 // 4295000000 //4.295e9
00020 #define MIN_FLOAT      1.175494351e-38F //3.4e-38f
00021 #define MAX_FLOAT      3.402823466e+38F //3.4e+38f
00022 #define SMALL_HALF     1e-5f
00023 
00024 typedef struct {
00025    float left;
00026    float top;
00027    float right;
00028    float bottom;
00029 } FRECT;    
00030 
00031 #if defined(_MAC) && !defined(_XCODE)
00032 typedef struct
00033 {
00034    WORD dlgVer;
00035    WORD signature;
00036    DWORD helpID;
00037    DWORD exStyle;
00038    DWORD style;
00039    WORD cDlgItems;
00040    short x;
00041    short y;
00042    short cx;
00043    short cy;
00044 } DLGTEMPLATEEX;
00045 #endif
00046 
00047 enum SubdivisionPresets { SP_1, SP_4, SP_16, SP_VARIABLESUB };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
