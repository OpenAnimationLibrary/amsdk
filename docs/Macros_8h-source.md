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

# Macros.h

[Go to the documentation of this file.](Macros_8h.md)

<div class="fragment">

``` fragment
00001 // BC  2/4/2004  \Bob110\Include\Macros.h
00002 
00003 #define __MACROS_H
00004 
00005 #ifndef __FASTFTOL_H
00006 #include "Fastftol.h"
00007 #endif
00008 
00009 #define __OS9ROS_H
00010 
00011 #include <math.h>
00012 
00013 #define ABS(a)             (((a)<0)?(-(a)):(a))
00014 #undef MAX
00015 #define MAX(a,b)           (((a)>(b))?(a):(b))
00016 #undef MIN
00017 #define MIN(A,B)           ((A)<(B)?(A):(B))
00018 #define ROWBYTES(A)        (((A)+15)>>4<<1)
00019 #define ROWWORDS(A)        (((A)+15)>>4)
00020 #define ROUNDOFF(A)        (LONG)((A)<(0)?((A)-.5):((A)+.5))
00021 #define ISODD(A)           (A&0x1)
00022 #define INVERSE(A)         { A.x=-A.x;A.y=-A.y;A.z=-A.z; }
00023 #define FLOOR(a)           ((a)>(0) ? (int)(a) : -(int)(-a))
00024 #define CEILING(a)         ((a)==(int)(a) ? (a) : (a)>0 ? 1+(int)a : -(1+(int)(-a)))
00025 #define SIGN(x)            ((x) >= 0 ? 1 : -1)
00026 #define NUMELEMENTS(array) (sizeof(array)/sizeof(array[0]))
00027 #define NULLDELETE(a)      { delete a; a = NULL; }
00028 #define PADWIDTH(x)        (((x)*8 + 31)  & (~31))/8
00029 #ifdef _DOCUMENT
00030 #define DOC(A)             A
00031 #define MENU_DOC(A,B) static MenuDoc f_##A(A, DOC(B))
00032 #else
00033 #define DOC(A)             ""
00034 #define MENU_DOC(A,B)
00035 #endif
00036 
00037 inline void Round( float &number, float modulo )
00038 {
00039    double dnum = number;
00040    dnum += SIGN(dnum) * 0.5 * (double)modulo;
00041    dnum -= fmod(dnum, (double)modulo);
00042    number = (float)dnum;
00043 /*
00044    number /= modulo;
00045    fast_round(number);  // this way would be faster
00046    number *= modulo;
00047 */
00048 }
00049 
00050 inline float RoundValue( float number, float modulo )
00051 {
00052    float rvalue( number );
00053    Round( rvalue, modulo );
00054    return rvalue;
00055 }
00056 
00057 inline long RoundValue( double number )
00058 {
00059    return (long)(number + SIGN(number) * .5f);
00060 }
00061 
00062 class MenuDoc;
00063 void AddMenuDoc( MenuDoc *menudoc );
00064 class MenuDoc 
00065 {
00066 public:
00067    UINT  m_id;
00068    char *m_documentation;
00069 
00070    MenuDoc( UINT menuid, char *documentation )
00071    {
00072       m_id = menuid;
00073       m_documentation = documentation;
00074 
00075       AddMenuDoc( this );
00076    }
00077 };
00078 
00079 void *GetMenuDocMap();
00080 
00081 #define DLLEXPORT
00082 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
