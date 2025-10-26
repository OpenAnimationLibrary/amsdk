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

# MCDriver.h

[Go to the documentation of this file.](MCDriver_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/24/2002  \HRandy95\Include\MCDriver.h
00002 
00003 #define __MCDRIVER_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #ifndef __EXPORTS_H
00009 #include "EXPORTS.H"
00010 #endif
00011 #include "DLLPlugi.h"
00012 
00013 class MCDevice;
00014 class Matrix34;
00015 class Time;
00016 
00017 #define MCDLLVERSION 2
00018 
00019 class PLUGINEXPORT MCDriver : public DLLPlugin {
00020 private:
00021    MCDevice *device;
00022    
00023 public:
00024    // RETURN VALUES FOR LiveCaptureFrame()
00025    enum FrameError { FE_FAILED, FE_SUCCESS, FE_TRYAGAIN };
00026 
00027    // CHANNEL INDEXES FOR SETVALUE
00028    enum { XTRANS, YTRANS, ZTRANS, XSCALE, YSCALE, ZSCALE, XORIENT, YORIENT, ZORIENT, ROLL };
00029    
00030    MCDriver(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}
00031 
00032    void SetDevice( MCDevice *pdevice ) { device = pdevice; }
00033    MCDevice *GetDevice() { return device; }
00034    
00035    // UTILITY FUNCTIONS FOR LIVE & STATIC CAPTURE
00036    BOOL  BuildSensorArray( int count );
00037    BOOL  InsertSensor( int index, char *name, int parentindex=-1 );
00038    BOOL  InsertSensor( int index, char *name, Vector start, Vector end, int parentindex=-1 );
00039    void DoneInsertingSensors();
00040    void  FreeSensorArray();
00041    BOOL  SetValue( int sensorindex, int channelindex, float value );
00042    BOOL  StoreRotate( int sensorindex, const Matrix34 &matrix );
00043    BOOL  StoreRotateStandard( int sensorindex, const Matrix34 &matrix );
00044    BOOL  StoreTranslateStandard( int sensorindex, const Vector translate );
00045    BOOL  StorePose( MCDevice *device, char *name, float percent );
00046 
00047    // UTILITY FUNCTIONS FOR STATIC CAPTURE
00048    Time  GetTime();
00049    void  SetTime( Time time );
00050    float GetFrame();
00051    void  SetFrame( float frame );
00052    float GetSystemRate();
00053    float GetCaptureRate();
00054 
00055    void  Redraw();
00056    BOOL  EscapeKeyDown();
00057 
00058    // CAPABILITIES
00059    virtual BOOL         SupportsLiveCaptureSequence()   { return FALSE; }
00060    virtual BOOL         SupportsLiveCaptureFrame()      { return FALSE; }
00061    virtual BOOL         SupportsStaticCaptureSequence() { return FALSE; } 
00062 
00063    // IMPLEMENTATION OF LIVE CAPTURE
00064    virtual BOOL         LiveCaptureInit() { return FALSE; }
00065    virtual FrameError   LiveCaptureFrame() { return FE_FAILED; }
00066    virtual void         LiveCaptureClose() {}
00067 
00068    // IMPLEMENTATION OF STATIC CAPTURE
00069    virtual BOOL         StaticCaptureSequence() { return FALSE; }
00070 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
