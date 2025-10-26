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

# Rave.h

[Go to the documentation of this file.](Rave_8h.md)

<div class="fragment">

``` fragment
00001 /* KB  03/10/97  \Ken5\Include\3rdParty\RAVE.H
00002  **                                                          **
00003  **   Module:     RAVE.h                                        **
00004  **                                                       **
00005  **   Purpose:    Header file for RAVE API                         **
00006  **                                                       **
00007  **   Author:     Mike W. Kelley                                **
00008  **               Brent H. Pease                                **
00009  **                                                       **
00010  **   Copyright (C) 1994-96 Apple Computer, Inc.  All rights reserved.   **
00011  **      OpenGLª is a trademark of Silicon Graphics, Inc.                **
00012  **                                                       **
00013  *****************************************************************************/
00014 
00015 #ifndef _RAVE_h
00016 #define _RAVE_h
00017 
00018 #ifdef __cplusplus
00019 extern "C" {
00020 #endif
00021 
00022 /******************************************************************************
00023  *
00024  * Platform macros.
00025  * This sets kQAPlatform to one of kQAMacOS, kQAWin32, or kQAGeneric.
00026  * kQAPlatform controls platform-specific compilation switches and types.
00027  *
00028  *****************************************************************************/
00029 
00030 #if !defined(kQAMacOS)
00031 #define  kQAMacOS    1        /* Target is MacOS               */
00032 #endif
00033 
00034 #if !defined(kQAGeneric)
00035 #define kQAGeneric      2        /* Target is generic platform    */
00036 #endif
00037 
00038 #if !defined(kQAWin32)
00039 #define kQAWin32     3        /* Target is Win32               */
00040 #endif
00041 
00042 #if defined(_WIN32) || defined(_WINDOWS)
00043    #define kQAPlatform kQAWin32
00044 #elif !defined(kQAPlatform)
00045    #define kQAPlatform kQAMacOS
00046 #endif
00047 
00048 /******************************************************************************
00049  *
00050  * Export Control
00051  *
00052  *****************************************************************************/
00053 
00054 #if defined(_MSC_VER)   /* Microsoft Visual C */
00055    #if defined(WIN32_RAVEEXPORTING) /* define when building DLL */
00056       #define  RAVE_EXPORT    __declspec( dllexport )
00057       #define RAVE_CALL
00058       #define RAVE_CALLBACK
00059    #else
00060       #define RAVE_EXPORT     __declspec( dllimport )
00061       #define RAVE_CALL    __cdecl
00062       #define RAVE_CALLBACK   __cdecl
00063    #endif /* WIN32_RAVEEXPORTING */
00064 #else
00065    #define RAVE_EXPORT
00066    #define RAVE_CALL
00067    #define RAVE_CALLBACK
00068 #endif /* _MSC_VER */
00069 
00070 /******************************************************************************
00071  *
00072  * Platform dependent datatypes: TQAImagePixelType, TQADevice, TQAClip, and TQARect.
00073  *
00074  *****************************************************************************/
00075 
00076 typedef enum TQAImagePixelType
00077 {
00078    kQAPixel_Alpha1      = 0,     /* 1 bit/pixel alpha */
00079    kQAPixel_RGB16    = 1,     /* 16 bit/pixel, R=14:10, G=9:5, B=4:0 */
00080    kQAPixel_ARGB16      = 2,     /* 16 bit/pixel, A=15, R=14:10, G=9:5, B=4:0 */
00081    kQAPixel_RGB32    = 3,     /* 32 bit/pixel, R=23:16, G=15:8, B=7:0 */
00082    kQAPixel_ARGB32      = 4,     /* 32 bit/pixel, A=31:24, R=23:16, G=15:8, B=7:0 */
00083    kQAPixel_CL4      = 5,     /* 4 bit color look up table, always big endian,
00084                               ie high 4 bits effect left pixel */
00085    kQAPixel_CL8      = 6         /* 8 bit color look up table */
00086 #if (kQAPlatform == kQAWin32)
00087    ,
00088    kQAPixel_RGB16_565   = 7,     /* 16 bits/pixel, no alpha, R:5, G:6, B:5 */
00089    kQAPixel_RGB24    = 8         /* 24 bits/pixel, no alpha, R:8, G:8, B:8 */
00090 #endif /* kQAPlatform == kQAWin32 */
00091 } TQAImagePixelType;
00092 
00093 typedef enum TQAColorTableType
00094 {
00095    kQAColorTable_CL8_RGB32    = 0,     /* 256 entry, 32 bit/pixel, R=23:16, G=15:8, B=7:0 */
00096    kQAColorTable_CL4_RGB32    = 1         /* 16 entry, 32 bit/pixel, R=23:16, G=15:8, B=7:0 */
00097 } TQAColorTableType;
00098 
00099 typedef enum TQADeviceType       /* Selects target device type */
00100 {
00101    kQADeviceMemory      = 0,     /* Memory draw context */
00102    kQADeviceGDevice  = 1,     /* Macintosh GDevice draw context */
00103    kQADeviceWin32DC  = 2         /* Win32 DC */
00104 #if !defined(RAVE_NO_DIRECTDRAW)
00105    ,
00106    kQADeviceDDSurface   = 3         /* Win32 DirectDraw Surface */
00107 #endif /* !defined(RAVE_NO_DIRECTDRAW) */
00108 } TQADeviceType;
00109 
00110 typedef struct TQADeviceMemory      /* Generic memory pixmap device */
00111 {
00112    long           rowBytes;   /* Rowbytes */
00113    TQAImagePixelType pixelType;  /* Depth, color space, etc. */
00114    long           width;      /* Width in pixels */
00115    long           height;     /* Height in pixels */
00116    void           *baseAddr;  /* Base address of pixmap */
00117 } TQADeviceMemory;
00118 
00119 typedef enum TQAClipType         /* Selects target clip type */
00120 {
00121    kQAClipRgn        = 0,     /* Macintosh clipRgn with serial number */
00122    kQAClipWin32Rgn      = 1         /* Win32 clip region */
00123 } TQAClipType;
00124 
00125 typedef struct TQARect
00126 {
00127    long           left;
00128    long           right;
00129    long           top;
00130    long           bottom;
00131 } TQARect;
00132 
00133 #if (kQAPlatform == kQAMacOS)
00134 
00135    /*
00136    ** the following gets around a problem in xlc with unsigned 32 bit enums 
00137    ** that have been defined in system header files
00138    */
00139    #if defined(__xlc) || defined(__xlC) || defined(__xlC__) || defined(__XLC121__)
00140       #pragma options enum=small
00141    #endif
00142    
00143    /*
00144     * MacOS supports memory and GDevice. TQARect == Rect. TQAClip is a clipRgn.
00145     */
00146    #include <Quickdraw.h>
00147    #include <QDOffscreen.h>
00148    
00149    /*
00150    ** reset to default after the system headers
00151    */
00152    
00153    #if defined(__xlc) || defined(__xlC) || defined(__xlC__) || defined(__XLC121__)
00154       #pragma options enum=reset
00155    #endif
00156       
00157    
00158    typedef union TQAPlatformDevice
00159    {
00160       TQADeviceMemory   memoryDevice;
00161       GDHandle    gDevice;
00162    } TQAPlatformDevice;
00163    
00164    typedef union TQAPlatformClip
00165    {
00166       RgnHandle      clipRgn;
00167    } TQAPlatformClip;
00168    
00169 #elif (kQAPlatform == kQAWin32)
00170    #include <windows.h>
00171 #if !defined(RAVE_NO_DIRECTDRAW)
00172    #include <ddraw.h>
00173 
00174    typedef enum
00175    {
00176       kQADirectDrawObject     = 1,
00177       kQADirectDrawObject2 = 2
00178    } TQADirectDrawObjectSelector;
00179 
00180    typedef enum
00181    {
00182       kQADirectDrawSurface = 1,
00183       kQADirectDrawSurface2   = 2
00184    } TQADirectDrawSurfaceSelector;
00185 
00186 #endif /* !RAVE_NO_DIRECTDRAW */
00187 
00188    typedef union TQAPlatformDevice
00189    {
00190       TQADeviceMemory         memoryDevice;
00191       HDC                  hdc;
00192 #if !defined(RAVE_NO_DIRECTDRAW)
00193       struct
00194       {
00195          TQADirectDrawObjectSelector      objectSelector;
00196          union
00197          {
00198             LPDIRECTDRAW            lpDirectDraw;
00199             LPDIRECTDRAW2           lpDirectDraw2;
00200          };
00201 
00202          TQADirectDrawSurfaceSelector  surfaceSelector;
00203          union
00204          {
00205             LPDIRECTDRAWSURFACE        lpDirectDrawSurface;
00206             LPDIRECTDRAWSURFACE2    lpDirectDrawSurface2;
00207          };
00208       };
00209 #endif /* RAVE_NO_DIRECTDRAW */
00210    } TQAPlatformDevice;
00211 
00212    typedef union TQAPlatformClip
00213    {
00214       HRGN        clipRgn;
00215    } TQAPlatformClip;
00216 #elif (kQAPlatform == kQAGeneric)
00217    /*
00218     * Generic platform supports memory device only. TQARect is generic. TQAClip is ???.
00219     */
00220    
00221    typedef union TQAPlatformDevice
00222    {
00223       TQADeviceMemory   memoryDevice;
00224    } TQAPlatformDevice;
00225    
00226    typedef union TQAPlatformClip
00227    {
00228       void        *region;       /* ??? */
00229    } TQAPlatformClip;
00230 #else
00231    /* ??? Unrecognized kQAPlatform */
00232 #endif
00233 
00234 typedef struct TQADevice
00235 {
00236    TQADeviceType     deviceType;
00237    TQAPlatformDevice device;
00238 } TQADevice;
00239 
00240 typedef struct TQAClip
00241 {
00242    TQAClipType       clipType;
00243    TQAPlatformClip      clip;
00244 } TQAClip;
00245 
00246 /******************************************************************************
00247  *
00248  * Basic data types.
00249  *
00250  *****************************************************************************/
00251 
00252 typedef struct TQADrawContext TQADrawContext;   /* Drawing context for an engine */
00253 typedef struct TQAEngine TQAEngine;       /* Pointer to a drawing engine */
00254 typedef struct TQATexture TQATexture;        /* Pointer to an allocated texture map */
00255 typedef struct TQABitmap TQABitmap;       /* Pointer to an allocated bitmap */
00256 typedef struct TQADrawPrivate TQADrawPrivate;   /* Engine's private draw context pointer */
00257 typedef struct TQAImage TQAImage;            /* An image for use as texture or bitmap */
00258 typedef struct TQAColorTable TQAColorTable;
00259 
00260 typedef struct TQAIndexedTriangle            /* A single triangle element for QADrawTriMesh */
00261 {
00262    unsigned long  triangleFlags;          /* Triangle flags, see kQATriFlags_ */
00263    unsigned long  vertices[3];            /* Indices into a vertex array */
00264 } TQAIndexedTriangle;
00265 
00266 struct TQAImage                           /* An image for use as texture or bitmap */
00267 {
00268    long     width;                     /* Width of pixmap */
00269    long     height;                    /* Height of pixmap */
00270    long     rowBytes;                  /* Rowbytes of pixmap */
00271    void     *pixmap;                /* Pixmap */
00272 };
00273 
00274 typedef enum TQAError                     /* Standard error type */
00275 {
00276    kQANoErr          = 0,           /* No error */
00277    kQAError          = 1,           /* Generic error flag */
00278    kQAOutOfMemory       = 2,           /* Insufficient memory */
00279    kQANotSupported         = 3,           /* Requested feature is not supported */
00280    kQAOutOfDate         = 4,           /* A newer drawing engine was registered */
00281    kQAParamErr          = 5,           /* Error in passed parameters */
00282    kQAGestaltUnknown    = 6,           /* Requested gestalt type isn't available */
00283    kQADisplayModeUnsupported  = 7,        /* Engine cannot render to the display in its current ,
00284                                      * mode, but could if it were in some other mode */
00285    kQAOutOfVideoMemory     = 8               /* There is not enough VRAM to support the desired
00286                                      * context dimensions */
00287 } TQAError;
00288 
00289 /************************************************************************************************
00290  *
00291  * Vertex data types.
00292  *
00293  ***********************************************************************************************/
00294 
00295 /*
00296  * TQAVGouraud is used for Gouraud shading. Each vertex specifies position, color and Z.
00297  *
00298  * Alpha is always treated as indicating transparency. Drawing engines which don't
00299  * support Z-sorted rendering use the back-to-front transparency blending functions
00300  * shown below. (ARGBsrc are the source (new) values, ARGBdest are  the destination
00301  * (previous) pixel values.)
00302  *
00303  *    Premultiplied                    Interpolated
00304  *
00305  *    A = 1 - (1 - Asrc) * (1 - Adest)    A = 1 - (1 - Asrc) * (1 - Adest) 
00306  *    R = (1 - Asrc) * Rdest + Rsrc       R = (1 - Asrc) * Rdest + Asrc * Rsrc
00307  *    G = (1 - Asrc) * Gdest + Gsrc       G = (1 - Asrc) * Gdest + Asrc * Gsrc
00308  *    B = (1 - Asrc) * Bdest + Bsrc       B = (1 - Asrc) * Bdest + Asrc * Bsrc
00309  *
00310  * Note that the use of other blending modes to implement antialiasing is performed
00311  * automatically by the drawing engine when the kQATag_Antialias variable !=
00312  * kQAAntiAlias_Fast. The driving software should continue to use the alpha fields
00313  * for transparency even when antialiasing is being used (the drawing engine will
00314  * resolve the multiple blending requirements as best as it can).
00315  *
00316  * Drawing engines which perform front-to-back Z-sorted rendering should replace
00317  * the blending function shown above with the equivalent front-to-back formula.
00318  */
00319 
00320 typedef struct TQAVGouraud
00321 {
00322    float          x;    /* X pixel coordinate, 0.0 <= x < width */
00323    float          y;    /* Y pixel coordinate, 0.0 <= y < height */
00324    float          z;    /* Z coordinate, 0.0 <= z <= 1.0 */
00325    float          invW; /* 1 / w; required only when kQAPerspectiveZ_On is set */
00326    
00327    float          r;    /* Red, 0.0 <= r <= 1.0 */
00328    float          g;    /* Green, 0.0 <= g <= 1.0 */
00329    float          b;    /* Blue, 0.0 <= b <= 1.0 */
00330    float          a;    /* Alpha, 0.0 <= a <= 1.0, 1.0 is opaque */
00331 } TQAVGouraud;
00332 
00333 /*
00334  * TQAVTexture is used for texture mapping. The texture mapping operation
00335  * is controlled by the kQATag_TextureOp variable, which is a mask of
00336  * kQATextureOp_None/Modulate/Highlight/Decal. Below is pseudo-code for the
00337  * texture shading operation:
00338  *
00339  *    texPix = TextureLookup (uq/q, vq/q);
00340  *    if (kQATextureOp_Decal)
00341  *    {
00342  *       tex