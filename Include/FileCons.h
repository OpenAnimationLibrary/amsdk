//BC  12/10/2003  \Bob110\Include\FILECONS.H
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once
#include "DataType.h"

/*
most constants defined now in namespace hash_constants (HashMath.h)
*/

constexpr float SCREENPIXELSPERLINE = 8.F;

constexpr SSHORT FRONTVIEW = 0;
constexpr SSHORT BACKVIEW = 1;
constexpr SSHORT LEFTVIEW = 2;
constexpr SSHORT RIGHTVIEW = 3;
constexpr SSHORT TOPVIEW = 4;
constexpr SSHORT BOTTOMVIEW = 5;
constexpr SSHORT BIRDVIEW = 6;
constexpr SSHORT CAMERAVIEW1 = 100;
constexpr SSHORT LIGHTVIEW1 = 200;

constexpr float UNIT = 100.F;
constexpr float HALF_UNIT = 50.F;
constexpr float UNITX10 = 1000.F;
constexpr float WIDTHUNIT = 640.F;

//#define HEADERSIZE       4
//#define BLOCKS           1

//**************  NEW  ****************

//#define MAXVIEWPLANE     (-0.05f)
//#define DEFAULTVIEWWIDTH 35.F
//#define ORTHOWIDTH       10000         //10000 is arbitrary, results in 20cm wide view box on a 50mm lens
constexpr float ORTHOWIDTH = 10000.F;
constexpr float DEFAULTVIEWWIDTH = 35.F;

/*-----------------------------------------------------------------------------------**
**  -1.0 IS DUE TO: THE ABOVE VIEWWIDTH & VIEWPLANE CREATE APPROXIMATELY A           **
**  38.58 DEGREE FIELD OF VIEW.  THIS IS APPROXIMATELY A 50mm LENS ON A 35mm SLR. BC **
**     viewangle = 2 * hash_math::atan( (35/2) / focallength )                                  **
**  or                                                                               **
**     focallength = (35/2) / hash_math::tan( viewangle / 2 )                                   **
**                                                                                   **
**  newfocallength = oldfocallength * (35/2) / (80/3)                                **
**                 = oldfocallength * .65625                                         **
**-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------**
** ********* OLD ***********                                                         **
**                                                                                   **
** #define DEFAULTVIEWPLANE       -600.0                                             **
** #define DEFAULTVIEWWIDTH        640.0                                             **
** #define FOCALFACTOR             -12.0                                             **
** #define MAXVIEWPLANE             -1.0                                             **
**                                                                                   **
**                                                                                   **
** // -12.0 IS DUE TO: THE ABOVE VIEWWIDTH & VIEWPLANE CREATE APPROXIMATELY A        **
** //  56 DEGREE FIELD OF VIEW.  THIS IS APPROXIMATELY A 50mm LENS ON A 35mm SLR. BC **
** //    viewangle = 2 * hash_math::atan( (80/3) / focallength )                                **
** // or                                                                             **
** //    focallength = (80/3) / hash_math::tan( viewangle / 2 )                                 **
**                                                                                   **
**-----------------------------------------------------------------------------------*/

//#define ORTHOGONALVIEWPLANE (-100000)

#define FRONTROTATE         0.F, 0.F, 0.F
#define BACKROTATE          0.F, 0.F, 180.F
#define RIGHTROTATE         0.F, 0.F, -90.F
#define LEFTROTATE          0.F, 0.F,  90.F
#define TOPROTATE           90.F, 0.F,   0.F
#define BOTTOMROTATE        -90.F, 0.F,   0.F
#define BIRDROTATE          30.F, 0.F,  30.F

constexpr float NOGAMMA = 1.F;
constexpr float MONITORGAMMA = 1.8F;
constexpr float NTSCGAMMA = 2.2F;
constexpr float CRTGAMMA = 2.5F;
constexpr float FPS30 = 1.F / 30.F;
constexpr float FPS10 = 1.F / 10.F;
constexpr float FPS5 = 1.F / 5.F;
constexpr float FPS1 = 1.F;

enum struct TimeUnit {
    SMPTE,
    FRAMES,
    CELS
};

/*
#ifdef DEBUG
#define HASHTRY
#define HASHCATCHALL
#define HASHEXIT
#else
#define HASHTRY      try
#define HASHCATCHALL catch(...)
#define HASHEXIT     exit(-1)
#endif
*/

