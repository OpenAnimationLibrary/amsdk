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

# Fastftol.h

[Go to the documentation of this file.](Fastftol_8h.md)

<div class="fragment">

``` fragment
00001 // KB  8/21/2003  \Ken105\Include\Fastftol.h
00002 
00003 #define __FASTFTOL_H
00004 
00005 #ifndef _MAC
00006 #define ASSEMBLER_OPTIMIZATIONS 1
00007 
00008 #define FAST_ROUND(fx,x) \
00009    { \
00010       float __fx = (fx); \
00011       _asm fld __fx \
00012       _asm fistp x \
00013    } 
00014 #else
00015 #define FAST_ROUND(fx,x) {}
00016 #endif
00017 
00018 inline int fast_round( float d ) // this the fastest
00019 {
00020 #if ASSEMBLER_OPTIMIZATIONS
00021    int result;
00022    FAST_ROUND( d, result );
00023    return result;
00024 #else
00025    if (d<0)
00026       return (int)(d-0.5f);
00027    else
00028       return (int)(d+0.5f);
00029 #endif
00030 }
00031 
00032 inline int fast_ftol_unsigned( float d ) // extract the long from the IEEE float
00033 {
00034 // SXXX XXXX   XMMM MMMM   MMMM MMMM   MMMM MMMM
00035 #ifdef _MAC  // KB: not needed for PowerPC
00036    return abs((int)d);
00037 #else
00038    ULONG *ptr = (ULONG *)&d;
00039    int exp = ((*ptr & 0x7F800000) >> 23) - 127;
00040    int man =  (*ptr & 0x007FFFFF) | 0x00800000;
00041    exp = 23 - exp;
00042    if (exp > 0) {
00043       if (exp > 31)
00044          return 0;
00045       else
00046          return man >> exp;
00047    }
00048    else
00049       return man << -exp;
00050 #endif
00051 }
00052 
00053 inline int fast_ftol_signed( float d ) // extract the long from the IEEE float
00054 {
00055 // SXXX XXXX   XMMM MMMM   MMMM MMMM   MMMM MMMM
00056 #ifdef _MAC  // KB: not needed for PowerPC
00057    return (int)d;
00058 #else
00059    ULONG *ptr = (ULONG *)&d;
00060    int exp = ((*ptr & 0x7F800000) >> 23) - 127;
00061    int man =  (*ptr & 0x007FFFFF) | 0x00800000;
00062    exp = 23 - exp;
00063    if (*ptr & 0x80000000) { // signed
00064       if (exp > 0) {
00065          if (exp > 31)
00066             return 0;
00067          else
00068             return -(man >> exp);
00069       }
00070       else
00071          return -(man << -exp);
00072    }
00073    else {
00074       if (exp > 0) {
00075          if (exp > 31)
00076             return 0;
00077          else
00078             return man >> exp;
00079       }
00080       else
00081          return man << -exp;
00082    }   
00083 #endif
00084 }
00085 
00086 inline int fast_floor( float d ) // extract the long from the IEEE float
00087 {
00088 // SXXX XXXX   XMMM MMMM   MMMM MMMM   MMMM MMMM
00089    ULONG *ptr = (ULONG *)&d;
00090    int exp = ((*ptr & 0x7F800000) >> 23) - 127;
00091    int man =  (*ptr & 0x007FFFFF) | 0x00800000;
00092    exp = 23 - exp;
00093    if (*ptr & 0x80000000) { // signed
00094       if (exp > 0) {
00095          if (exp > 31)
00096             return -1;
00097          int i = man >> exp;
00098          if ((i << exp) == man)
00099             return -i;
00100          else
00101             return -(i+1);
00102       }
00103       else
00104          return -(man << -exp);
00105    }
00106    else {
00107       if (exp > 0) {
00108          if (exp > 31)
00109             return 0;
00110          else
00111             return man >> exp;
00112       }
00113       else
00114          return man << -exp;
00115    }   
00116 }
00117 
00118 #ifdef _MAC
00119 #include <math.h>
00120 inline float InverseSqrt(float a)
00121 #else
00122 inline __declspec(naked) float __fastcall InverseSqrt(float a)
00123 #endif
00124 {
00125 #ifndef _MAC
00126    __asm {
00127          mov      eax, 0be6eb508h
00128          mov      DWORD PTR [esp-12],03fc00000h ;  1.5 on the stack
00129          sub      eax, DWORD PTR [esp+4]; a
00130          sub      DWORD PTR [esp+4], 800000h ; a/2 a=Y0
00131          shr      eax, 1     ; firs approx in eax=R0
00132          mov      DWORD PTR [esp-8], eax
00133          
00134          fld      DWORD PTR [esp-8] ;r
00135          fmul  st, st            ;r*r
00136          fld      DWORD PTR [esp-8] ;r
00137          fxch  st(1)
00138          fmul  DWORD PTR [esp+4];a ;r*r*y0
00139          fld      DWORD PTR [esp-12];load 1.5
00140          fld      st(0)
00141          fsub  st,st(2)          ;r1 = 1.5 - y1
00142          ;x1 = st(3)
00143          ;y1 = st(2)
00144          ;1.5 = st(1)
00145          ;r1 = st(0)
00146          
00147          fld      st(1)
00148          fxch  st(1)
00149          fmul  st(3),st       ; y2=y1*r1*...
00150          fmul  st(3),st       ; y2=y1*r1*r1
00151          fmulp st(4),st            ; x2=x1*r1
00152          fsub  st,st(2)               ; r2=1.5-y2
00153          ;x2=st(3)
00154          ;y2=st(2)
00155          ;1.5=st(1)
00156          ;r2 = st(0)
00157          
00158          fmul  st(2),st       ;y3=y2*r2*...
00159          fmul  st(3),st       ;x3=x2*r2
00160          fmulp st(2),st       ;y3=y2*r2*r2
00161          fxch  st(1)
00162          fsubp st(1),st       ;r3= 1.5 - y3
00163          ;x3 = st(1)
00164          ;r3 = st(0)
00165          fmulp st(1), st
00166          ret 4
00167    }
00168 #else
00169    return 1.0f/(float)sqrt(a);
00170 #endif //_MAC
00171 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
