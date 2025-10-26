Pix.r = texPix.a * texPix.r + (1 - texPix.a) * r;
00343  *       texPix.g = texPix.a * texPix.g + (1 - texPix.a) * g;
00344  *       texPix.b = texPix.a * texPix.b + (1 - texPix.a) * b;
00345  *       texPix.a = a;
00346  *    }
00347  *    else
00348  *    {
00349  *       texPix.a = texPix.a * a;
00350  *    }
00351  *    if (kQATextureOp_Modulate)
00352  *    {
00353  *       texPix.r *= kd_r;    // Clamped to prevent overflow
00354  *       texPix.g *= kd_g;    // Clamped to prevent overflow
00355  *       texPix.b *= kd_b;    // Clamped to prevent overflow
00356  *    }
00357  *    if (kQATextureOp_Highlight)
00358  *    {
00359  *       texPix.r += ks_r;    // Clamped to prevent overflow
00360  *       texPix.g += ks_g;    // Clamped to prevent overflow
00361  *       texPix.b += ks_b;    // Clamped to prevent overflow
00362  *    }
00363  *
00364  * After computation of texPix, transparency blending (as shown
00365  * above for TQAVGouraud) is performed.
00366  */
00367 
00368 typedef struct TQAVTexture
00369 {
00370    float          x;    /* X pixel coordinate, 0.0 <= x < width */
00371    float          y;    /* Y pixel coordinate, 0.0 <= y < height */
00372    float          z;    /* Z coordinate, 0.0 <= z <= 1.0 */
00373    float          invW; /* 1 / w (always required) */
00374    
00375    /* rgb are used only when kQATextureOp_Decal is set. a is always required */
00376    
00377    float          r;    /* Red, 0.0 <= r <= 1.0 */
00378    float          g;    /* Green, 0.0 <= g <= 1.0 */
00379    float          b;    /* Blue, 0.0 <= b <= 1.0 */
00380    float          a;    /* Alpha, 0.0 <= a <= 1.0, 1.0 is opaque */
00381 
00382    /* uOverW and vOverW are required by all modes */
00383    
00384    float          uOverW;  /* u / w */
00385    float          vOverW;  /* v / w */
00386    
00387    /* kd_r/g/b are used only when kQATextureOp_Modulate is set */
00388    
00389    float          kd_r; /* Scale factor for texture red, 0.0 <= kd_r */
00390    float          kd_g; /* Scale factor for texture green, 0.0 <= kd_g */
00391    float          kd_b; /* Scale factor for texture blue, 0.0 <= kd_b */
00392    
00393    /* ks_r/g/b are used only when kQATextureOp_Highlight is set */
00394    
00395    float          ks_r; /* Red specular highlight, 0.0 <= ks_r <= 1.0 */
00396    float          ks_g; /* Green specular highlight, 0.0 <= ks_g <= 1.0 */
00397    float          ks_b; /* Blue specular highlight, 0.0 <= ks_b <= 1.0 */
00398 } TQAVTexture;
00399 
00400 /************************************************************************************************
00401  *
00402  * Constants used for the state variables.
00403  *
00404  ***********************************************************************************************/
00405 
00406 /*
00407  * kQATag_xxx is used to select a state variable when calling QASetFloat(), QASetInt(),
00408  * QAGetFloat() and QAGetInt(). The kQATag values are split into two separate
00409  * enumerated types: TQATagInt and TQATagFloat. TQATagInt is used for the QASet/GetInt()
00410  * functions, and TQATagFloat is used for the QASet/GetFloat() functions. (This is so
00411  * that a compiler that typechecks enums can flag a float/int tag mismatch during compile.)
00412  *
00413  * These variables are required by all drawing engines:
00414  *    kQATag_ZFunction        (Int) One of kQAZFunction_xxx
00415  *    kQATag_ColorBG_a        (Float)  Background color alpha
00416  *    kQATag_ColorBG_r        (Float)  Background color red
00417  *    kQATag_ColorBG_g        (Float)  Background color green
00418  *    kQATag_ColorBG_b        (Float)  Background color blue
00419  *    kQATag_Width            (Float)  Line and point width (pixels)
00420  *    kQATag_ZMinOffset       (Float)  Min offset to Z to guarantee visibility (Read only!)
00421  *    kQATag_ZMinScale        (Float)  Min scale to Z to guarantee visibility (Read only!)
00422  
00423  * These variables are used for optional features:
00424  *    kQATag_Antialias        (Int) One of kQAAntiAlias_xxx
00425  *    kQATag_Blend            (Int) One of kQABlend_xxx
00426  *    kQATag_PerspectiveZ        (Int) One of kQAPerspectiveZ_xxx
00427  *    kQATag_TextureFilter    (Int) One of kQATextureFilter_xxx
00428  *    kQATag_TextureOp        (Int) Mask of kQATextureOp_xxx
00429  *    kQATag_Texture          (Int) Pointer to current TQATexture
00430  *    kQATag_CSGTag           (Int) One of kQACSGTag_xxx
00431  *    kQATag_CSGEquation         (Int) 32 bit CSG truth table
00432  *
00433  * These variables are used for OpenGLª support:
00434  *    kQATagGL_DrawBuffer        (Int) Mask of kQAGL_DrawBuffer_xxx
00435  *    kQATagGL_TextureWrapU      (Int) kQAGL_Clamp or kQAGL_Repeat
00436  *    kQATagGL_TextureWrapV      (Int) kQAGL_Clamp or kQAGL_Repeat
00437  *    kQATagGL_TextureMagFilter  (Int) kQAGL_Nearest or kQAGL_Linear
00438  *    kQATagGL_TextureMinFilter  (Int) kQAGL_Nearest, etc.
00439  *    kQATagGL_ScissorXMin    (Int) Minimum X value for scissor rectangle
00440  *    kQATagGL_ScissorYMin    (Int) Minimum Y value for scissor rectangle
00441  *    kQATagGL_ScissorXMax    (Int) Maximum X value for scissor rectangle
00442  *    kQATagGL_ScissorYMax    (Int) Maximum Y value for scissor rectangle
00443  *    kQATagGL_BlendSrc       (Int) Source blending operation
00444  *    kQATagGL_BlendDst       (Int) Destination blending operation
00445  *    kQATagGL_LinePattern    (Int) Line rasterization pattern
00446  *    kQATagGL_AreaPattern0      (Int) First of 32 area pattern registers
00447  *    kQATagGL_AreaPattern31     (Int) Last of 32 area pattern registers
00448  *    kQATagGL_DepthBG        (Float)  Background Z
00449  *    kQATagGL_TextureBorder_a   (Float)  Texture border color alpha
00450  *    kQATagGL_TextureBorder_r   (Float)  Texture border color red
00451  *    kQATagGL_TextureBorder_g   (Float)  Texture border color green
00452  *    kQATagGL_TextureBorder_b   (Float)  Texture border color blue
00453  *
00454  * Tags >= kQATag_EngineSpecific_Minimum may be assigned by the vendor for use as
00455  * engine-specific variables. NOTE: These should be used only in exceptional circumstances,
00456  * as functions performed by these variables won't be generally accessible. All other tag
00457  * values are reserved.
00458  *
00459  *    kQATag_EngineSpecific_Minimum Minimum tag value for drawing-engine specific variables
00460  */
00461 
00462 typedef enum TQATagInt
00463 {
00464    kQATag_ZFunction           = 0,
00465    kQATag_Antialias           = 8,
00466    kQATag_Blend               = 9,
00467    kQATag_PerspectiveZ           = 10,
00468    kQATag_TextureFilter       = 11,
00469    kQATag_TextureOp           = 12,
00470    kQATag_CSGTag              = 14,
00471    kQATag_CSGEquation            = 15,
00472    kQATag_BufferComposite        = 16,
00473    kQATagGL_DrawBuffer           = 100,
00474    kQATagGL_TextureWrapU         = 101,
00475    kQATagGL_TextureWrapV         = 102,
00476    kQATagGL_TextureMagFilter     = 103,
00477    kQATagGL_TextureMinFilter     = 104,
00478    kQATagGL_ScissorXMin       = 105,
00479    kQATagGL_ScissorYMin       = 106,
00480    kQATagGL_ScissorXMax       = 107,
00481    kQATagGL_ScissorYMax       = 108,
00482    kQATagGL_BlendSrc          = 109,
00483    kQATagGL_BlendDst          = 110,
00484    kQATagGL_LinePattern       = 111,
00485    kQATagGL_AreaPattern0         = 117,
00486       /* ...1-30 */
00487    kQATagGL_AreaPattern31        = 148,
00488    kQATag_EngineSpecific_Minimum = 1000
00489 } TQATagInt;
00490 
00491 typedef enum TQATagPtr
00492 {
00493    kQATag_Texture             = 13
00494 } TQATagPtr;
00495 
00496 typedef enum TQATagFloat
00497 {
00498    kQATag_ColorBG_a           = 1,
00499    kQATag_ColorBG_r           = 2,
00500    kQATag_ColorBG_g           = 3,
00501    kQATag_ColorBG_b           = 4,
00502    kQATag_Width               = 5,
00503    kQATag_ZMinOffset          = 6,
00504    kQATag_ZMinScale           = 7,
00505    kQATagGL_DepthBG           = 112,
00506    kQATagGL_TextureBorder_a      = 113,
00507    kQATagGL_TextureBorder_r      = 114,
00508    kQATagGL_TextureBorder_g      = 115,
00509    kQATagGL_TextureBorder_b      = 116
00510 } TQATagFloat;
00511 
00512 /* kQATag_ZFunction */
00513 #define kQAZFunction_None        0  /* Z is neither tested nor written (same as no Z buffer) */
00514 #define kQAZFunction_LT          1  /* Znew < Zbuffer is visible */
00515 #define kQAZFunction_EQ          2  /* OpenGL Only: Znew == Zbuffer is visible */
00516 #define kQAZFunction_LE          3  /* OpenGL Only: Znew <= Zbuffer is visible */
00517 #define kQAZFunction_GT          4  /* OpenGL Only: Znew > Zbuffer is visible */
00518 #define kQAZFunction_NE          5  /* OpenGL Only: Znew != Zbuffer is visible */
00519 #define kQAZFunction_GE          6  /* OpenGL Only: Znew >= Zbuffer is visible */
00520 #define kQAZFunction_True        7  /* Znew is always visible */
00521 
00522 /* kQATag_Width */
00523 #define kQAMaxWidth              128.0
00524 
00525 /* kQATag_Antialias */
00526 #define kQAAntiAlias_Off         0
00527 #define kQAAntiAlias_Fast        1
00528 #define kQAAntiAlias_Mid         2
00529 #define kQAAntiAlias_Best        3
00530 
00531 /* kQATag_Blend */
00532 #define kQABlend_PreMultiply     0
00533 #define kQABlend_Interpolate     1
00534 #define kQABlend_OpenGL          2
00535 
00536 /* kQATag_BufferComposite */
00537 #define kQABufferComposite_None        0  /* Default: New pixels overwrite initial buffer contents */
00538 #define kQABufferComposite_PreMultiply 1  /* New pixels are blended with initial buffer contents via PreMultiply */
00539 #define kQABufferComposite_Interpolate 2  /* New pixels are blended with initial buffer contents via Interpolate */
00540 
00541 /* kQATag_PerspectiveZ */
00542 #define kQAPerspectiveZ_Off         0  /* Use Z for hidden surface removal */
00543 #define kQAPerspectiveZ_On       1  /* Use InvW for hidden surface removal */
00544 
00545 /* kQATag_TextureFilter */
00546 #define kQATextureFilter_Fast    0
00547 #define kQATextureFilter_Mid     1
00548 #define kQATextureFilter_Best    2
00549 
00550 /* kQATag_TextureOp (mask of one or more) */
00551 #define kQATextureOp_None     0           /* Default texture mapping mode */
00552 #define kQATextureOp_Modulate (1 << 0)    /* Modulate texture color with kd_r/g/b */
00553 #define kQATextureOp_Highlight   (1 << 1)    /* Add highlight value ks_r/g/b */
00554 #define kQATextureOp_Decal    (1 << 2)    /* When texture alpha == 0, use rgb instead */
00555 #define kQATextureOp_Shrink      (1 << 3)    /* This is a non-wrapping texture, so the ??? */
00556 
00557 /* kQATag_CSGTag */
00558 #define kQACSGTag_None        0xffffffffUL   /* Do not perform CSG */
00559 #define kQACSGTag_0           0           /* Submitted tris have CSG ID 0 */
00560 #define kQACSGTag_1           1           /* Submitted tris have CSG ID 1 */
00561 #define kQACSGTag_2           2           /* Submitted tris have CSG ID 2 */
00562 #define kQACSGTag_3           3           /* Submitted tris have CSG ID 3 */
00563 #define kQACSGTag_4           4           /* Submitted tris have CSG ID 4 */
00564 
00565 /* kQATagGL_TextureWrapU/V */
00566 #define kQAGL_Repeat          0
00567 #define kQAGL_Clamp              1
00568 
00569 /* kQATagGL_BlendSrc */
00570 #define kQAGL_SourceBlend_XXX    0
00571 
00572 /* kQATagGL_BlendDst */
00573 #define kQAGL_DestBlend_XXX         0
00574 
00575 /* kQATagGL_DrawBuffer (mask of one or more) */
00576 #define kQAGL_DrawBuffer_None    0
00577 #define kQAGL_DrawBuffer_FrontLeft  (1<<0)
00578 #define kQAGL_DrawBuffer_FrontRight (1<<1)
00579 #define kQAGL_DrawBuffer_BackLeft   (1<<2)
00580 #define kQAGL_DrawBuffer_BackRight  (1<<3)
00581 #define kQAGL_DrawBuffer_Front      (kQAGL_DrawBuffer_FrontLeft | kQAGL_DrawBuffer_FrontRight)
00582 #define kQAGL_DrawBuffer_Back    (kQAGL_DrawBuffer_BackLeft | kQAGL_DrawBuffer_BackRight)
00583 
00584 /************************************************************************************************
00585  *
00586  * Constants used as function parameters.
00587  *
00588  ***********************************************************************************************/
00589 
00590 /*
00591  * TQAVertexMode is a parameter to QADrawVGouraud() and QADrawVTexture() that specifies how
00592  * to interpret and draw the vertex array.
00593  */
00594 
00595 typedef enum TQAVertexMode
00596 {
00597    kQAVertexMode_Point           = 0,     /* Draw nVertices points */
00598    kQAVertexMode_Line            = 1,     /* Draw nVertices/2 line segments */
00599    kQAVertexMode_Polyline        = 2,     /* Draw nVertices-1 connected line segments */
00600    kQAVertexMode_Tri          = 3,     /* Draw nVertices/3 triangles */
00601    kQAVertexMode_Strip           = 4,     /* Draw nVertices-2 triangles as a strip */
00602    kQAVertexMode_Fan          = 5,        /* Draw nVertices-2 triangles as a fan from v0 */
00603    kQAVertexMode_NumModes        = 6
00604 
00605 } TQAVertexMode;
00606 
00607 /*
00608  * TQAGestaltSelector is a parameter to QAEngineGestalt(). It selects which gestalt
00609  * parameter will be copied into 'response'.
00610  */
00611 
00612 typedef enum TQAGestaltSelector
00613 {
00614    kQAGestalt_OptionalFeatures      = 0,     /* Mask of one or more kQAOptional_xxx */
00615    kQAGestalt_FastFeatures       = 1,     /* Mask of one or more kQAFast_xxx */
00616    kQAGestalt_VendorID           = 2,     /* Vendor ID */
00617    kQAGestalt_EngineID           = 3,     /* Engine ID */
00618    kQAGestalt_Revision           = 4,     /* Revision number of this engine */
00619    kQAGestalt_ASCIINameLength    = 5,     /* strlen (asciiName) */
00620    kQAGestalt_ASCIIName       = 6,     /* Causes strcpy (response, asciiName) */
00621    kQAGestalt_TextureMemory      = 7,     /* amount of texture RAM currently available */
00622    kQAGestalt_FastTextureMemory  = 8,     /* amount of texture RAM currently available */
00623    kQAGestalt_NumSelectors       = 9
00624 
00625 } TQAGestaltSelector;
00626 
00627 /*
00628  * TQAMethodSelector is a parameter to QASetNoticeMethod to select the notice method
00629  */
00630 
00631 typedef enum TQAMethodSelector
00632 {
00633    kQAMethod_RenderCompletion    = 0,     /* Called when rendering has completed and buffers swapped */
00634    kQAMethod_DisplayModeChanged  = 1,     /* Called when a display mode has changed */
00635    kQAMethod_ReloadTextures      = 2,     /* Called when texture memory has been invalidated */
00636    kQAMethod_BufferInitialize    = 3,     /* Called when a buffer needs to be initialized */
00637    kQAMethod_BufferComposite     = 4,     /* Called when rendering is finished and its safe to composite */
00638    kQAMethod_NumSelectors        = 5
00639    
00640 } TQAMethodSelector;
00641 
00642 /*
00643  * kQATriFlags_xxx are ORed together to generate the 'f