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

# Filecons.h

[Go to the documentation of this file.](Filecons_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/10/2003  \Bob110\Include\FILECONS.H
00002 
00003 #define __FILECONS_H
00004 
00005 #define H_PI                  3.1415926535898
00006 #define SQRT2                 1.4142135623731f
00007 #define SQRT3                 1.73205f
00008 #define GRAVITY               980.665f // 980.665 CM/SEC/SEC
00009 #define RECIPSQRT3            0.57735027f
00010 #define SCREENPIXELSPERLINE   8
00011 
00012 #define FRONTVIEW   0
00013 #define BACKVIEW    1
00014 #define LEFTVIEW    2
00015 #define RIGHTVIEW   3   
00016 #define TOPVIEW     4
00017 #define BOTTOMVIEW  5
00018 #define BIRDVIEW    6
00019 #define CAMERAVIEW1 100
00020 #define LIGHTVIEW1  200
00021 
00022 #define UNIT            100.0f
00023 #define UNITX10         1000.0f
00024 #define WIDTHUNIT       640.0f
00025 #define THOUSAND        1000.
00026 
00027 #define HITHER       1.0
00028 #define YON       BIG_FLOAT
00029 
00030 #define HEADERSIZE      4
00031 #define BLOCKS       1
00032 
00033 #define RADIANS         57.29578f
00034 // **************  NEW  ****************
00035 
00036 #define DEFAULTVIEWPLANE        -50.0f
00037 #define DEFAULTVIEWWIDTH         35.0f
00038 #define FOCALFACTOR              -1.0f
00039 #define MAXVIEWPLANE            -0.05f
00040 #define ORTHOWIDTH              10000  // 10000 is arbitrary, results in 20cm wide view box on a 50mm lens
00041 
00042 /*-----------------------------------------------------------------------------------**
00043 **  -1.0 IS DUE TO: THE ABOVE VIEWWIDTH & VIEWPLANE CREATE APPROXIMATELY A           **
00044 **  38.58 DEGREE FIELD OF VIEW.  THIS IS APPROXIMATELY A 50mm LENS ON A 35mm SLR. BC **
00045 **     viewangle = 2 * atan( (35/2) / focallength )                                  **
00046 **  or                                                                               **
00047 **     focallength = (35/2) / tan( viewangle / 2 )                                   **
00048 **                                                                                   **
00049 **  newfocallength = oldfocallength * (35/2) / (80/3)                                **
00050 **                 = oldfocallength * .65625                                         **
00051 **-----------------------------------------------------------------------------------*/
00052 
00053 /*-----------------------------------------------------------------------------------**
00054 ** ********* OLD ***********                                                         **
00055 **                                                                                   **
00056 ** #define DEFAULTVIEWPLANE       -600.0                                             **
00057 ** #define DEFAULTVIEWWIDTH        640.0                                             **
00058 ** #define FOCALFACTOR             -12.0                                             **
00059 ** #define MAXVIEWPLANE             -1.0                                             **
00060 **                                                                                   **
00061 **                                                                                   **
00062 ** // -12.0 IS DUE TO: THE ABOVE VIEWWIDTH & VIEWPLANE CREATE APPROXIMATELY A        **
00063 ** //  56 DEGREE FIELD OF VIEW.  THIS IS APPROXIMATELY A 50mm LENS ON A 35mm SLR. BC **
00064 ** //    viewangle = 2 * atan( (80/3) / focallength )                                **
00065 ** // or                                                                             **
00066 ** //    focallength = (80/3) / tan( viewangle / 2 )                                 **
00067 **                                                                                   **
00068 **-----------------------------------------------------------------------------------*/
00069 
00070 #define ORTHOGONALVIEWPLANE   -100000
00071 
00072 #define FRONTROTATE           0.,0.,   0. 
00073 #define BACKROTATE         0.,0., 180. 
00074 #define RIGHTROTATE        0.,0., -90. 
00075 #define LEFTROTATE         0.,0.,  90. 
00076 #define TOPROTATE         90.,0.,   0. 
00077 #define BOTTOMROTATE     -90.,0.,   0. 
00078 #define BIRDROTATE        30.,0.,  30. 
00079 
00080 #define MINIRESWIDTH              80
00081 #define MINIRESHEIGHT             60
00082 #define MINIRESASPECT           1.0f
00083 
00084 #define LOWRESWIDTH              320
00085 #define LOWRESHEIGHT             240
00086 #define LOWRESASPECT            1.0f
00087 
00088 #define TGARESWIDTH              512
00089 #define TGARESHEIGHT             486
00090 #define TGARESASPECT            1.266f   
00091 
00092 #define VGARESWIDTH              640
00093 #define VGARESHEIGHT             480
00094 #define VGARESASPECT            1.0f
00095 
00096 #define PARRESWIDTH              752
00097 #define PARRESHEIGHT             486
00098 #define PARRESASPECT            0.875f
00099 
00100 #define DVRESWIDTH      720
00101 #define DVRESHEIGHT     480
00102 #define DVRESASPECT     0.9f
00103 
00104 #define D1NTSCRESWIDTH  720
00105 #define D1NTSCRESHEIGHT 486
00106 #define D1NTSCRESASPECT 0.9f
00107 
00108 #define D1PALRESWIDTH   720
00109 #define D1PALRESHEIGHT  576
00110 #define D1PALRESASPECT  1.067f
00111 
00112 #define HDTV720PRESWIDTH  1280
00113 #define HDTV720PRESHEIGHT  720
00114 #define HDTV720PRESASPECT 1.0f
00115 
00116 #define HDTV1080RESWIDTH  1920
00117 #define HDTV1080RESHEIGHT 1080
00118 #define HDTV1080RESASPECT 1.0f
00119 
00120 #define PANAVISIONRESWIDTH      2048
00121 #define PANAVISIONRESHEIGHT      871
00122 #define PANAVISIONRESASPECT     1.0f
00123 
00124 #define VISTAVISIONRESWIDTH     2048
00125 #define VISTAVISIONRESHEIGHT    1366
00126 #define VISTAVISIONRESASPECT    1.0f
00127 
00128 #define SUPER35RESWIDTH      2048
00129 #define SUPER35RESHEIGHT     1536
00130 #define SUPER35RESASPECT     1.0f
00131 
00132 #define NOGAMMA      1.0f
00133 #define MONITORGAMMA 1.8f
00134 #define NTSCGAMMA    2.2f
00135 #define CRTGAMMA     2.5f
00136 
00137 #define FPS30 .033f
00138 #define FPS10 .1f
00139 #define FPS5  .2f
00140 #define FPS1   1
00141 
00142 #ifdef DEBUG
00143 #define HASHTRY
00144 #define HASHCATCHALL
00145 #define HASHEXIT
00146 #else
00147 #define HASHTRY  try
00148 #define HASHCATCHALL catch(...)
00149 #define HASHEXIT exit(-1)
00150 #endif
00151 
00152 #define MAXIMUMCHAR 255
00153 #ifdef _OS9
00154 #define PROJECTSPATH "\\PROJECTS.HSH"
00155 #else
00156 #define PROJECTSPATH "\\PROJECTS.HSH"
00157 #endif
00158 
00159 enum { SMPTE, FRAMES, CELS };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
