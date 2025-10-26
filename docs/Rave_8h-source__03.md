umber of vertices */
00919    TQAVertexMode        vertexMode,       /* One of kQAVertexMode_xxx enumerated values */
00920    const TQAVTexture       vertices[],       /* Array of vertices */
00921    const unsigned long     flags[]);         /* Array of per-triangle flags (or NULL) */
00922 
00923 typedef void (RAVE_CALLBACK *TQADrawBitmap) (
00924    const TQADrawContext *drawContext,     /* Draw context */
00925    const TQAVGouraud       *v,               /* xyz, and (if a 1 bit/pixel bitmap) argb */
00926    TQABitmap            *bitmap);         /* Previously allocated by QABitmapNew() */
00927 
00928 typedef void (RAVE_CALLBACK *TQARenderStart) (
00929    const TQADrawContext *drawContext,     /* Draw context */
00930    const TQARect        *dirtyRect,       /* Minimum area to clear; NULL means whole buffer */
00931    const TQADrawContext *initialContext); /* Initial background image (or NULL) */
00932 
00933 typedef TQAError (RAVE_CALLBACK *TQARenderEnd) (
00934    const TQADrawContext *drawContext,     /* Draw context */
00935    const TQARect        *modifiedRect);      /* Minimum area to swap; NULL means whole buffer */
00936 
00937 typedef TQAError (RAVE_CALLBACK *TQARenderAbort) (
00938    const TQADrawContext *drawContext);    /* Draw context */
00939 
00940 typedef TQAError (RAVE_CALLBACK *TQAFlush) (
00941    const TQADrawContext *drawContext);    /* Draw context */
00942 
00943 typedef TQAError (RAVE_CALLBACK *TQASync) (
00944    const TQADrawContext *drawContext);    /* Draw context */
00945 
00946 typedef TQAError (RAVE_CALLBACK *TQASetNoticeMethod)(
00947    const TQADrawContext *drawContext,     /* Draw context */
00948    TQAMethodSelector    method,
00949    TQANoticeMethod         completionCallBack,
00950    void              *refCon);
00951 
00952 typedef TQAError (RAVE_CALLBACK * TQAGetNoticeMethod)(
00953    const TQADrawContext *drawContext,     /* Draw context */
00954    TQAMethodSelector    method,
00955    TQANoticeMethod         *completionCallBack,
00956    void              **refCon);
00957 
00958 /************************************************************************************************
00959  *
00960  * Public TQADrawContext structure. This contains function pointers for the chosen
00961  * drawing engine.
00962  *
00963  ***********************************************************************************************/
00964 
00965 /*
00966  * TQAVersion sets the TQADrawContext 'version' field. It is set by
00967  * the manager to indicate the version of the TQADrawContext structure.
00968  */
00969 
00970 typedef enum TQAVersion
00971 {
00972    kQAVersion_Prerelease      = 0,
00973    kQAVersion_1_0          = 1,
00974    kQAVersion_1_0_5        = 2,        /* Added tri mesh functions, color tables */
00975    kQAVersion_1_5          = 3            /* Added call backs, texture compression, and new error return code */
00976 
00977 } TQAVersion;
00978 
00979 struct TQADrawContext
00980 {
00981    TQADrawPrivate       *drawPrivate;     /* Engine's private data for this context */
00982    const TQAVersion     version;       /* Version number */
00983    TQASetFloat          setFloat;         /* Method: Set a float state variable */
00984    TQASetInt            setInt;           /* Method: Set an unsigned long state variable */
00985    TQASetPtr            setPtr;           /* Method: Set an unsigned long state variable */
00986    TQAGetFloat          getFloat;         /* Method: Get a float state variable */
00987    TQAGetInt            getInt;           /* Method: Get an unsigned long state variable */
00988    TQAGetPtr            getPtr;           /* Method: Get an pointer state variable */
00989    TQADrawPoint         drawPoint;        /* Method: Draw a point */
00990    TQADrawLine          drawLine;         /* Method: Draw a line */
00991    TQADrawTriGouraud    drawTriGouraud;      /* Method: Draw a Gouraud shaded triangle */
00992    TQADrawTriTexture    drawTriTexture;      /* Method: Draw a texture mapped triangle */
00993    TQADrawVGouraud         drawVGouraud;     /* Method: Draw Gouraud vertices */
00994    TQADrawVTexture         drawVTexture;     /* Method: Draw texture vertices */
00995    TQADrawBitmap        drawBitmap;       /* Method: Draw a bitmap */
00996    TQARenderStart       renderStart;      /* Method: Initialize for rendering */
00997    TQARenderEnd         renderEnd;        /* Method: Complete rendering and display */
00998    TQARenderAbort       renderAbort;      /* Method: Abort any outstanding rendering (blocking) */
00999    TQAFlush          flush;            /* Method: Start render of any queued commands (non-blocking) */
01000    TQASync              sync;          /* Method: Wait for completion of all rendering (blocking) */
01001    TQASubmitVerticesGouraud   submitVerticesGouraud;  /* Method: Submit Gouraud vertices for trimesh */
01002    TQASubmitVerticesTexture   submitVerticesTexture;  /* Method: Submit Texture vertices for trimesh */
01003    TQADrawTriMeshGouraud      drawTriMeshGouraud;     /* Method: Draw a Gouraud triangle mesh */
01004    TQADrawTriMeshTexture      drawTriMeshTexture;     /* Method: Draw a Texture triangle mesh */
01005    TQASetNoticeMethod         setNoticeMethod;     /* Method: Set a notice method */
01006    TQAGetNoticeMethod         getNoticeMethod;     /* Method: Get a notice method */
01007 };
01008 
01009 /************************************************************************************************
01010  *
01011  * Acceleration manager function prototypes.
01012  *
01013  ***********************************************************************************************/
01014 
01015 RAVE_EXPORT TQAError RAVE_CALL QADrawContextNew (
01016    const TQADevice   *device,          /* Target device */
01017    const TQARect  *rect,               /* Target rectangle (device coordinates) */
01018    const TQAClip  *clip,               /* 2D clip region */
01019    const TQAEngine   *engine,          /* Drawing engine to use */
01020    unsigned long  flags,               /* Mask of kQAContext_xxx */
01021    TQADrawContext **newDrawContext);      /* (Out) Newly created TQADrawContext */
01022 
01023 RAVE_EXPORT void RAVE_CALL QADrawContextDelete (
01024    TQADrawContext *drawContext);       /* Context to delete */
01025 
01026 RAVE_EXPORT TQAError RAVE_CALL QAColorTableNew(
01027    const TQAEngine      *engine,       /* Drawing engine to use */
01028    TQAColorTableType tableType,        /* Depth, color space, etc. */
01029    void           *pixelData,       /* lookup table entries in pixelType format */
01030    long           transparentIndexFlag,   /* boolean, false means no transparency, true means index 0 is transparent */
01031    TQAColorTable     **newTable);      /* (Out) Newly created TQAColorTable */
01032 
01033 RAVE_EXPORT void RAVE_CALL QAColorTableDelete(
01034    const TQAEngine      *engine,       /* Drawing engine to use */
01035    TQAColorTable     *colorTable);     /* Previously allocated by QAColorTableNew() */
01036 
01037 RAVE_EXPORT TQAError RAVE_CALL QATextureNew (
01038    const TQAEngine      *engine,       /* Drawing engine to use */
01039    unsigned long     flags,            /* Mask of kQATexture_xxx flags */
01040    TQAImagePixelType pixelType,        /* Depth, color space, etc. */
01041    const TQAImage    images[],         /* Image(s) for texture */
01042    TQATexture        **newTexture);    /* (Out) Newly created TQATexture, or NULL on error */ 
01043 
01044 RAVE_EXPORT TQAError RAVE_CALL QATextureDetach (
01045    const TQAEngine      *engine,       /* Drawing engine to use */
01046    TQATexture        *texture);        /* Previously allocated by QATextureNew() */
01047 
01048 RAVE_EXPORT void RAVE_CALL QATextureDelete (
01049    const TQAEngine      *engine,       /* Drawing engine to use */
01050    TQATexture        *texture);        /* Previously allocated by QATextureNew() */
01051 
01052 RAVE_EXPORT TQAError RAVE_CALL QATextureBindColorTable(
01053    const TQAEngine      *engine,       /* Drawing engine to use */
01054    TQATexture        *texture,         /* Previously allocated by QATextureNew() */
01055    TQAColorTable     *colorTable);     /* Previously allocated by QAColorTableNew() */
01056    
01057 RAVE_EXPORT TQAError RAVE_CALL QABitmapNew (
01058    const TQAEngine      *engine,       /* Drawing engine to use */
01059    unsigned long     flags,            /* Mask of kQABitmap_xxx flags */
01060    TQAImagePixelType pixelType,        /* Depth, color space, etc. */
01061    const TQAImage    *image,           /* Image */
01062    TQABitmap         **newBitmap);     /* (Out) Newly created TQABitmap, or NULL on error */ 
01063 
01064 RAVE_EXPORT TQAError RAVE_CALL QABitmapDetach (
01065    const TQAEngine      *engine,       /* Drawing engine to use */
01066    TQABitmap         *bitmap);         /* Previously allocated by QABitmapNew() */
01067 
01068 RAVE_EXPORT void RAVE_CALL QABitmapDelete (
01069    const TQAEngine      *engine,       /* Drawing engine to use */
01070    TQABitmap         *bitmap);         /* Previously allocated by QABitmapNew() */
01071 
01072 RAVE_EXPORT TQAError RAVE_CALL QABitmapBindColorTable(
01073    const TQAEngine      *engine,       /* Drawing engine to use */
01074    TQABitmap         *bitmap,       /* Previously allocated by QABitmapNew() */
01075    TQAColorTable     *colorTable);     /* Previously allocated by QAColorTableNew() */
01076    
01077 RAVE_EXPORT TQAEngine *RAVE_CALL QADeviceGetFirstEngine (
01078    const TQADevice   *device);            /* Target device */
01079 
01080 RAVE_EXPORT TQAEngine *RAVE_CALL QADeviceGetNextEngine (
01081    const TQADevice   *device,          /* Target device */
01082    const TQAEngine   *currentEngine);     /* Engine after 'currentEngine' is returned */
01083 
01084 RAVE_EXPORT TQAError RAVE_CALL QAEngineCheckDevice (
01085    const TQAEngine   *engine,          /* Engine to check on 'device' */
01086    const TQADevice   *device);            /* Target device */
01087 
01088 RAVE_EXPORT TQAError RAVE_CALL QAEngineGestalt (
01089    const TQAEngine      *engine,       /* Engine being queried */
01090    TQAGestaltSelector   selector,         /* Gestalt parameter being requested */
01091    void           *response);       /* Buffer that receives response */
01092 
01093 RAVE_EXPORT TQAError RAVE_CALL QAEngineEnable (
01094    long        vendorID,            /* Vendor ID of engine to enable */
01095    long        engineID);           /* Engine ID of engine to enable */
01096 
01097 RAVE_EXPORT TQAError RAVE_CALL QAEngineDisable (
01098    long        vendorID,            /* Vendor ID of engine to disable */
01099    long        engineID);           /* Engine ID of engine to disable */
01100 
01101 #ifdef __cplusplus
01102 }
01103 #endif
01104 
01105 #endif /* _RAVE_h */
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
