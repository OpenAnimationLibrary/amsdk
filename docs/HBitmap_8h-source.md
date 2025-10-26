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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# HBitmap.h

[Go to the documentation of this file.](HBitmap_8h.md)

<div class="fragment">

``` fragment
00001 // KB  12/20/2004  \Noel120\Include\SDK\HBitmap.h
00002 
00003 #define __HBITMAP_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 //*********************************************************
00011 //** HBitmapBuffer
00012 //*********************************************************
00013 class PLUGINEXPORT HBitmapBuffer : public HHashObject
00014 {
00015 public:
00016    enum ChannelType
00017    {
00018        CT_UBYTE = 0,    // unsigned char (8 bit )
00019        CT_UINT  = 1,    // unsigned int (32 bit)
00020        CT_HALF  = 2,    // half (16 bit floating point)
00021        CT_FLOAT = 3,    // float (32 bit floating point)
00022        CT_NUM_CHANNELTYPE  // number of channel types
00023    };
00024    enum BufferType //Keep HBitmapBuffer up to date with this
00025    {
00026        BT_SCALAR = 0,   // One single channel buffer
00027        BT_RGB  = 1,     // RGB 3 channels buffer
00028        BT_RGBA  = 2,    // RGBA 4 channels buffer
00029        BT_YA  = 3,      // YA 2 channels buffer
00030        BT_NUM_BUFFERTYPE   // number of buffer types
00031    };
00032 
00033    void *GetChannelAt(int channum); //NAP Bitmap COME-back expose HBitmapChannel?
00034    void AllocateData(int mipmaplevel=0);
00035    const int GetWidth();
00036    const int GetHeight();
00037    BITMAPINFO   *CreateBITMAPINFO(BOOL replacealpha0withbk=FALSE, BOOL maketransparent=FALSE, RGBFloat *background=FALSE);
00038    HBitmapBuffer *GetNext();
00039    const int GetNbrChannels();
00040    const ChannelType GetChannelsType();
00041    const BufferType GetBufferType();
00042    const char *GetChannelNameAt(int channum);
00043    void SetBackground(const RGBFloat &color);
00044    const RGBFloat GetBackground();   
00045    void SetIsKeyBackground(BOOL iskeybackground);
00046    const BOOL GetIsKeyBackground();
00047    void SetGamma(float gamma);
00048    const float GetGamma();
00049    void SetIsPremultipliedAlpha(BOOL ispremultiplied);
00050    const BOOL GetIsPremultipliedAlpha();
00051    HBitmapBuffer *MakeCopy();
00052    HBitmapBuffer *MakeBlankCopy();
00053 };
00054 
00055 //*********************************************************
00056 //** HYABuffer
00057 //*********************************************************
00058 class PLUGINEXPORT HYABuffer : public HBitmapBuffer
00059 {
00060 public:
00061    void *GetData(int mipmaplevel=0);
00062 };
00063 
00064 //*********************************************************
00065 //** HRGBABuffer
00066 //*********************************************************
00067 class PLUGINEXPORT HRGBABuffer : public HBitmapBuffer
00068 {
00069 public:
00070    void *GetData(int mipmaplevel=0);
00071 };
00072 
00073 //*********************************************************
00074 //** HRGBBuffer
00075 //*********************************************************
00076 class PLUGINEXPORT HRGBBuffer : public HBitmapBuffer
00077 {
00078 public:
00079    void *GetData(int mipmaplevel=0);
00080 };
00081 
00082 //*********************************************************
00083 //** HScalarBuffer
00084 //*********************************************************
00085 class PLUGINEXPORT HScalarBuffer : public HBitmapBuffer
00086 {
00087 public:
00088    void *GetData(int mipmaplevel=0);
00089 };
00090 
00091 //*********************************************************
00092 //** HRGBAFloatBuffer
00093 //*********************************************************
00094 class PLUGINEXPORT HRGBAFloatBuffer : public HRGBABuffer
00095 {
00096 public:
00097    RGBAFloat *GetRGBAFloatData(int miplevel=0);
00098 };
00099 
00100 //*********************************************************
00101 //** HBitmapNode
00102 //*********************************************************
00103 class PLUGINEXPORT HBitmapNode : public HHashObject
00104 {
00105 public:
00106    enum LoadFlags { LOADDEFAULT = 0x0,
00107           LOADBKCOLOR     =0x01,
00108           LOADINFOONLY    =0x02,
00109           INITIALIZE      =0x04,
00110           NOMODIFIEDCHECK =0x08 };
00111 
00112    enum { LOAD_FAILED, LOAD_OK, ALREADY_LOADED };
00113    
00114    enum { WRITE_NORESULT  =0,
00115           WRITE_ERROR     =0x01,
00116           WRITE_OK        =0x02,
00117           WRITE_NEEDCLOSE =0x04 };
00118    const int GetWidth();
00119    const int GetHeight();
00120    void SetWidth(int width);
00121    void SetHeight(int height);
00122    HBitmapNode *ScaleBitmap(int width, int height);
00123    UBYTE *CreateByteBlock(int *rbytesperpixel, BOOL withborder=FALSE, BOOL *bHasTransparency=NULL);
00124    const LONG GetFps();
00125    void SetFps( LONG fps );
00126    const int GetLength();
00127    void SetLength( int length );
00128    void AddBuffer(HBitmapBuffer *);
00129    void DeleteAllBuffers();
00130    HBitmapBuffer *GetBufferHead();
00131    void ReadPixel(int x, int y, RGBFloat &color); //NAP Bitmap return error?
00132    void ReadPixel(int x, int y, RGBAFloat &color); 
00133    void ReadPixel(int x, int y, YAFloat &color); 
00134 
00135    int LoadFrame( const String &filename, int frame=-1, LoadFlags flags = LOADDEFAULT );
00136    
00137    static HYABuffer     *CreateYABuffer(const String &name, HBitmapBuffer::ChannelType chantype, int width, int height);
00138    static HRGBABuffer   *CreateRGBABuffer(const String &name, HBitmapBuffer::ChannelType chantype, int width, int height);
00139    static HRGBBuffer    *CreateRGBBuffer(const String &name, HBitmapBuffer::ChannelType chantype, int width, int height);
00140    static HScalarBuffer *CreateScalarBuffer(const String &name, HBitmapBuffer::ChannelType chantype, int width, int height);
00141    //prefered output of a posteffect plugin is a RGBAFloatBuffer
00142    static HRGBAFloatBuffer *CreateRGBAFloatBuffer(const String &name, int width, int height);
00143 };
00144 
00145 //*********************************************************
00146 //** HBufferShortcut
00147 //*********************************************************
00148 class PLUGINEXPORT HBufferShortcut : public HHashObject
00149 {
00150 public:
00151    HRGBAFloatBuffer *GetRGBAFloatBuffer(Time time);
00152    HBufferShortcut  *GetNextBufferShortcut();
00153    void              SetBuffer(HBitmapBuffer *buffer);
00154    String            GetFileName();
00155 };
00156 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
