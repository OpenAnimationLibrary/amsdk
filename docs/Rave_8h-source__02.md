lags' parameter
00644  * to QADrawTriGouraud() and QADrawTriTexture().
00645  */
00646 
00647 #define  kQATriFlags_None        0        /* No flags (triangle is front-facing or don't care) */
00648 #define kQATriFlags_Backfacing      (1 << 0) /* Triangle is back-facing */
00649 
00650 /*
00651  * kQATexture_xxx are ORed together to generate the 'flags' parameter to QATextureNew().
00652  */
00653 
00654 #define  kQATexture_None            0        /* No flags */
00655 #define kQATexture_Lock          (1<<0)      /* Don't swap this texture out */
00656 #define kQATexture_Mipmap        (1<<1)      /* This texture is mipmapped */
00657 #define kQATexture_NoCompression (1<<2)      /* Do not compress this texture */
00658 #define kQATexture_HighCompression  (1<<3)      /* Compress texture, even if it takes a while */
00659 
00660 /*
00661  * kQABitmap_xxx are ORed together to generate the 'flags' parameter to QABitmapNew().
00662  */
00663 
00664 #define  kQABitmap_None          0        /* No flags */
00665 #define kQABitmap_Lock           (1<<1)      /* Don't swap this bitmap out */
00666 #define kQABitmap_NoCompression     (1<<2)      /* Do not compress this bitmap */
00667 #define kQABitmap_HighCompression   (1<<3)      /* Compress bitmap, even if it takes a while */
00668 
00669 /*
00670  * kQAContext_xxx are ORed together to generate the 'flags' parameter for QADrawContextNew().
00671  */
00672 
00673 #define kQAContext_None          0        /* No flags */
00674 #define kQAContext_NoZBuffer     (1 << 0) /* No hidden surface removal */
00675 #define kQAContext_DeepZ         (1 << 1) /* Hidden surface precision >= 24 bits */
00676 #define kQAContext_DoubleBuffer     (1 << 2) /* Double buffered window */
00677 #define kQAContext_Cache         (1 << 3) /* This is a cache context */
00678 #define kQAContext_NoDither         (1 << 4) /* No dithering, straight color banding */
00679 
00680 /*
00681  * kQAOptional_xxx are ORed together to generate the kQAGestalt_OptionalFeatures response
00682  * from QAEngineGestalt().
00683  */
00684 
00685 #define kQAOptional_None         0        /* No optional features */
00686 #define kQAOptional_DeepZ        (1 << 0) /* Hidden surface precision >= 24 bits */
00687 #define kQAOptional_Texture         (1 << 1) /* Texture mapping */
00688 #define kQAOptional_TextureHQ    (1 << 2) /* High quality texture (tri-linear mip or better) */
00689 #define kQAOptional_TextureColor (1 << 3) /* Full color modulation and highlight of textures */
00690 #define kQAOptional_Blend        (1 << 4) /* Transparency blending of RGB */
00691 #define kQAOptional_BlendAlpha      (1 << 5) /* Transparency blending includes alpha channel */
00692 #define kQAOptional_Antialias    (1 << 6) /* Antialiased rendering */
00693 #define kQAOptional_ZSorted         (1 << 7) /* Z sorted rendering (for transparency, etc.) */
00694 #define kQAOptional_PerspectiveZ (1 << 8) /* Hidden surface removal using InvW instead of Z */
00695 #define kQAOptional_OpenGL       (1 << 9) /* Extended rasterization features for OpenGLª */
00696 #define kQAOptional_NoClear         (1 << 10)   /* This drawing engine doesn't clear before drawing */
00697 #define kQAOptional_CSG          (1 << 11)   /* kQATag_CSGxxx are implemented */
00698 #define kQAOptional_BoundToDevice   (1 << 12)   /* This engine is tightly bound to GDevice */
00699 #define kQAOptional_CL4          (1 << 13)   /* This engine suports kQAPixel_CL4 */
00700 #define kQAOptional_CL8          (1 << 14)   /* This engine suports kQAPixel_CL8 */
00701 #define kQAOptional_BufferComposite (1 << 15)   /* This engine can composite with initial buffer contents */
00702 #define kQAOptional_NoDither     (1 << 16)   /* This engine can draw with no dithering */
00703 
00704 /*
00705  * kQAFast_xxx are ORed together to generate the kQAGestalt_FastFeatures response
00706  * from QAEngineGestalt().
00707  */
00708 
00709 #define kQAFast_None          0        /* No accelerated features */
00710 #define kQAFast_Line          (1 << 0) /* Line drawing */
00711 #define kQAFast_Gouraud          (1 << 1) /* Gouraud shaded triangles */
00712 #define kQAFast_Texture          (1 << 2) /* Texture mapped triangles */
00713 #define kQAFast_TextureHQ        (1 << 3) /* High quality texture (tri-linear mip or better) */
00714 #define kQAFast_Blend            (1 << 4) /* Transparency blending */
00715 #define kQAFast_Antialiasing     (1 << 5) /* Antialiased rendering */
00716 #define kQAFast_ZSorted          (1 << 6) /* Z sorted rendering of non-opaque objects */
00717 #define kQAFast_CL4              (1 << 7) /* This engine accelerates kQAPixel_CL4 */
00718 #define kQAFast_CL8              (1 << 8) /* This engine accelerates kQAPixel_CL8 */
00719 
00720 /************************************************************************************************
00721  *
00722  * Macro definitions for the drawing engine methods included in TQADrawContext. These
00723  * macros are the recommended means of accessing the engine's draw methods, e.g:
00724  *
00725  *    TQADrawContext *drawContext;
00726  *    TQAVTexture    vertices[3];
00727  *
00728  *    drawContext = QADrawContextNew (rect, gdevice, engine, kQAContext_ZBuffer);
00729  *    ...
00730  *    QASetInt (drawContext, kQATag_ZFunction, kQAZFunction_LT);
00731  *    QADrawTriGouraud (drawContext, &vertices[0], &vertices[1], &vertices[2], kQATriFlags_None);
00732  *
00733  * Note that QARenderStart(), QARenderEnd(), QAFlush() and QASync() have real function
00734  * definitions instead of macros. This is because these functions can afford the extra
00735  * per-call overhead of a function layer (which makes application code a little smaller),
00736  * and to allow a cleaner implementation of handling NULL parameters to QARenderStart().
00737  *
00738  ***********************************************************************************************/
00739 
00740 #define QASetFloat(drawContext,tag,newValue) \
00741       (drawContext)->setFloat (drawContext,tag,newValue)
00742 
00743 #define QASetInt(drawContext,tag,newValue) \
00744       (drawContext)->setInt (drawContext,tag,newValue)
00745 
00746 #define QASetPtr(drawContext,tag,newValue) \
00747       (drawContext)->setPtr (drawContext,tag,newValue)
00748 
00749 #define QAGetFloat(drawContext,tag) \
00750       (drawContext)->getFloat (drawContext,tag)
00751 
00752 #define QAGetInt(drawContext,tag) \
00753       (drawContext)->getInt (drawContext,tag)
00754 
00755 #define QAGetPtr(drawContext,tag) \
00756       (drawContext)->getPtr (drawContext,tag)
00757 
00758 #define QADrawPoint(drawContext,v) \
00759       (drawContext)->drawPoint (drawContext,v)
00760 
00761 #define QADrawLine(drawContext,v0,v1) \
00762       (drawContext)->drawLine (drawContext,v0,v1)
00763 
00764 #define QADrawTriGouraud(drawContext,v0,v1,v2,flags) \
00765       (drawContext)->drawTriGouraud (drawContext,v0,v1,v2,flags)
00766 
00767 #define QADrawTriTexture(drawContext,v0,v1,v2,flags) \
00768       (drawContext)->drawTriTexture (drawContext,v0,v1,v2,flags)
00769 
00770 #define QASubmitVerticesGouraud(drawContext,nVertices,vertices) \
00771       (drawContext)->submitVerticesGouraud(drawContext,nVertices,vertices)
00772       
00773 #define QASubmitVerticesTexture(drawContext,nVertices,vertices) \
00774       (drawContext)->submitVerticesTexture(drawContext,nVertices,vertices)
00775       
00776 #define QADrawTriMeshGouraud(drawContext,nTriangle,triangles) \
00777       (drawContext)->drawTriMeshGouraud (drawContext,nTriangle,triangles)
00778 
00779 #define QADrawTriMeshTexture(drawContext,nTriangle,triangles) \
00780       (drawContext)->drawTriMeshTexture (drawContext,nTriangle,triangles)
00781 
00782 #define QADrawVGouraud(drawContext,nVertices,vertexMode,vertices,flags) \
00783       (drawContext)->drawVGouraud (drawContext,nVertices,vertexMode,vertices,flags)
00784 
00785 #define QADrawVTexture(drawContext,nVertices,vertexMode,vertices,flags) \
00786       (drawContext)->drawVTexture (drawContext,nVertices,vertexMode,vertices,flags)
00787 
00788 #define QADrawBitmap(drawContext,v,bitmap) \
00789       (drawContext)->drawBitmap (drawContext,v,bitmap)
00790 
00791 #define QARenderStart(drawContext,dirtyRect,initialContext) \
00792       (drawContext)->renderStart (drawContext,dirtyRect,initialContext)
00793 
00794 #define QARenderEnd(drawContext,modifiedRect) \
00795       (drawContext)->renderEnd (drawContext,modifiedRect)
00796 
00797 #define QARenderAbort(drawContext) \
00798       (drawContext)->renderAbort (drawContext)
00799 
00800 #define QAFlush(drawContext) \
00801       (drawContext)->flush (drawContext)
00802 
00803 #define QASync(drawContext) \
00804       (drawContext)->sync (drawContext)
00805 
00806 #define QASetNoticeMethod(drawContext, method, completionCallBack, refCon) \
00807       (drawContext)->setNoticeMethod (drawContext, method, completionCallBack, refCon)
00808 
00809 #define QAGetNoticeMethod(drawContext, method, completionCallBack, refCon) \
00810       (drawContext)->getNoticeMethod (drawContext, method, completionCallBack, refCon)
00811 
00812 /************************************************************************************************
00813  *
00814  * Typedefs of draw method functions provided by the drawing engine. One function pointer
00815  * for each of these function types in stored in the TQADrawContext public data structure.
00816  *
00817  * These functions should be accessed through the QA<function>(context,...) macros,
00818  * defined above.
00819  *
00820  ***********************************************************************************************/
00821 
00822 typedef void (RAVE_CALLBACK *TQAStandardNoticeMethod)(
00823    const TQADrawContext *drawContext,     /* Draw context */
00824    void              *refCon);         /* user define parameter */
00825 
00826 typedef void (RAVE_CALLBACK *TQABufferNoticeMethod)(
00827    const TQADrawContext *drawContext,     /* Draw context */
00828    const TQADevice         *buffer,       /* TQADevice describing back buffer */
00829    const TQARect        *dirtyRect,       /* Minimum area to process; NULL means whole buffer */
00830    void              *refCon);         /* user define parameter */
00831 
00832 typedef union TQANoticeMethod
00833 {
00834    TQAStandardNoticeMethod standardNoticeMethod;   /* Used for non-buffer related methods */
00835    TQABufferNoticeMethod   bufferNoticeMethod;     /* Used for buffer handling methods */
00836    
00837 } TQANoticeMethod;
00838 
00839 typedef void (RAVE_CALLBACK *TQASetFloat) (
00840    TQADrawContext       *drawContext,     /* Draw context */
00841    TQATagFloat          tag,           /* Tag of variable to set */
00842    float             newValue);        /* New value for variable */
00843 
00844 typedef void (RAVE_CALLBACK *TQASetInt) (
00845    TQADrawContext       *drawContext,     /* Draw context */
00846    TQATagInt            tag,           /* Tag of variable to set */
00847    unsigned long        newValue);        /* New value for variable */
00848 
00849 typedef void (RAVE_CALLBACK *TQASetPtr) (
00850    TQADrawContext       *drawContext,     /* Draw context */
00851    TQATagPtr            tag,           /* Tag of variable to set */
00852    const void           *newValue);       /* New value for variable */
00853 
00854 typedef float (RAVE_CALLBACK *TQAGetFloat) (
00855    const TQADrawContext *drawContext,     /* Draw context */
00856    TQATagFloat          tag);          /* Tag of variable to get */
00857 
00858 typedef unsigned long (RAVE_CALLBACK *TQAGetInt) (
00859    const TQADrawContext *drawContext,     /* Draw context */
00860    TQATagInt            tag);          /* Tag of variable to get */
00861 
00862 typedef void *(RAVE_CALLBACK *TQAGetPtr) (
00863    const TQADrawContext *drawContext,     /* Draw context */
00864    TQATagPtr            tag);          /* Tag of variable to get */
00865 
00866 typedef void (RAVE_CALLBACK *TQADrawPoint) (
00867    const TQADrawContext *drawContext,     /* Draw context */
00868    const TQAVGouraud    *v);           /* Vertex */
00869 
00870 typedef void (RAVE_CALLBACK *TQADrawLine) (
00871    const TQADrawContext *drawContext,     /* Draw context */
00872    const TQAVGouraud       *v0,           /* Vertex 0 */
00873    const TQAVGouraud       *v1);          /* Vertex 1 */
00874 
00875 typedef void (RAVE_CALLBACK *TQADrawTriGouraud) (
00876    const TQADrawContext *drawContext,     /* Draw context */
00877    const TQAVGouraud       *v0,           /* Vertex 0 */
00878    const TQAVGouraud       *v1,           /* Vertex 1 */
00879    const TQAVGouraud       *v2,           /* Vertex 2 */
00880    unsigned long        flags);           /* Mask of kQATriFlags_xxx flags */
00881 
00882 typedef void (RAVE_CALLBACK *TQADrawTriTexture) (
00883    const TQADrawContext *drawContext,     /* Draw context */
00884    const TQAVTexture       *v0,           /* Vertex 0 */
00885    const TQAVTexture       *v1,           /* Vertex 1 */
00886    const TQAVTexture       *v2,           /* Vertex 2 */
00887    unsigned long        flags);           /* Mask of kQATriFlags_xxx flags */
00888 
00889 typedef void (RAVE_CALLBACK *TQASubmitVerticesGouraud) (
00890    const TQADrawContext    *drawContext,  /* Draw context */
00891    unsigned long           nVertices,     /* Number of vertices */
00892    const TQAVGouraud       *vertices);    /* Array of vertices */
00893    
00894 typedef void (RAVE_CALLBACK *TQASubmitVerticesTexture) (
00895    const TQADrawContext    *drawContext,  /* Draw context */
00896    unsigned long           nVertices,     /* Number of vertices */
00897    const TQAVTexture       *vertices);    /* Array of vertices */
00898    
00899 typedef void (RAVE_CALLBACK *TQADrawTriMeshGouraud) (
00900    const TQADrawContext    *drawContext,  /* Draw context */
00901    unsigned long           nTriangles,    /* Number of triangles */
00902    const TQAIndexedTriangle   *triangles);   /* Array of triangles */
00903    
00904 typedef void (RAVE_CALLBACK *TQADrawTriMeshTexture) (
00905    const TQADrawContext    *drawContext,  /* Draw context */
00906    unsigned long           nTriangles,    /* Number of triangles */
00907    const TQAIndexedTriangle   *triangles);   /* Array of triangles */
00908 
00909 typedef void (RAVE_CALLBACK *TQADrawVGouraud) (
00910    const TQADrawContext *drawContext,     /* Draw context */
00911    unsigned long        nVertices,        /* Number of vertices */
00912    TQAVertexMode        vertexMode,       /* One of kQAVertexMode_xxx enumerated values */
00913    const TQAVGouraud       vertices[],       /* Array of vertices */
00914    const unsigned long     flags[]);         /* Array of per-triangle flags (or NULL) */
00915 
00916 typedef void (RAVE_CALLBACK *TQADrawVTexture) (
00917    const TQADrawContext *drawContext,     /* Draw context */
00918    unsigned long        nVertices,        /* N