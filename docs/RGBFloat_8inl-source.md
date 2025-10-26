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

# RGBFloat.inl

[Go to the documentation of this file.](RGBFloat_8inl.md)

<div class="fragment">

``` fragment
00001 // NAP  12/11/2004  \Noel120\Include\RGBFloat.inl
00002 
00003 #define __RGBFLOAT_INL
00004 
00005 #ifndef __RGBFLOAT_H
00006 #include "RGBFloat.h"
00007 #endif
00008 #ifndef __COLORBUF_H
00009 #include "ColorBuf.h"
00010 #endif
00011 #ifndef __RGBHALF_H
00012 #include "RGBHalf.h"
00013 #endif
00014 #ifndef __RGBBYTE_H
00015 #include "RGBByte.h"
00016 #endif
00017 
00018 //*********************************************************************
00019 //*** RGBFloat
00020 //*********************************************************************
00021 inline RGBFloat::RGBFloat( const RGBHalf &other )
00022 {
00023    m_red   = other.Red();
00024    m_green = other.Green();
00025    m_blue  = other.Blue();
00026 }
00027 
00028 inline RGBFloat::RGBFloat( const RGBByte &other )
00029 {
00030    m_red   = other.Red()/255.0f;
00031    m_green = other.Green()/255.0f;
00032    m_blue  = other.Blue()/255.0f;
00033 }
00034 
00035 //*********************************************************************
00036 //*** RGBAFloat
00037 //*********************************************************************
00038 inline RGBAFloat::RGBAFloat( const RGBAHalf &other ) :
00039    m_color(other.Color())
00040 {
00041    m_alpha = other.Alpha();
00042 }
00043 
00044 inline RGBAFloat::RGBAFloat( const RGBAByte &other ) :
00045    m_color(other.m_color) //NAP Bitmap should I use Color() instead???
00046 {
00047    m_alpha = (float)other.Alpha()/MAXCOLOR;
00048 }
00049 
00050 inline RGBAFloat::RGBAFloat( const ColorBuf &other )
00051 { 
00052    SetRed((float)other.values.red   / MAXCOLOR); 
00053    SetGreen((float)other.values.green / MAXCOLOR); 
00054    SetBlue((float)other.values.blue   / MAXCOLOR); 
00055    SetAlpha((float)other.values.alpha / MAXCOLOR); 
00056 }
00057 
00058 //*********************************************************************
00059 //*** RGBAFloat
00060 //*********************************************************************
00061 inline YAFloat::YAFloat( const YAHalf &other ) :
00062    m_luminance(other.m_luminance)
00063 {
00064    m_alpha = other.m_alpha;
00065 }
00066 
00067 inline YAFloat::YAFloat( const YAByte &other ) :
00068    m_luminance((float) other.m_luminance / MAXCOLOR) //NAP Bitmap should I use Color() instead???
00069 {
00070    m_alpha = (float)other.m_alpha / MAXCOLOR;
00071 }
00072 
00073 inline YAFloat::YAFloat( const RGBAHalf &other )
00074 {
00075    // Compute the CIE Rec.709 luminance
00076    m_luminance = other.Red() * 0.2125f + other.Green() * 0.7154f + other.Blue() * 0.0721f;
00077    m_alpha = other.Alpha();
00078 }
00079 inline YAFloat::YAFloat( const RGBAByte &other )
00080 {
00081    // Compute the CIE Rec.709 luminance
00082    m_luminance = (float) (other.Red() * 0.2125f + other.Green() * 0.7154f + other.Blue() * 0.0721f) / MAXCOLOR;
00083    m_alpha = (float) other.Alpha()/MAXCOLOR;
00084 }
00085 
00086 inline YAFloat::YAFloat( const ColorBuf &other )
00087 {
00088    // Compute the CIE Rec.709 luminance
00089    m_luminance = (float) (other.values.red * 0.2125f + other.values.green * 0.7154f + other.values.blue * 0.0721f) / MAXCOLOR;
00090    m_alpha = 1.0f;
00091 }
00092 
00093 inline YAFloat::YAFloat( const RGBHalf &other )
00094 {
00095    // Compute the CIE Rec.709 luminance
00096    m_luminance = other.Red() * 0.2125f + other.Green() * 0.7154f + other.Blue() * 0.0721f;
00097    m_alpha = 1.0f;
00098 }
00099 
00100 inline YAFloat::YAFloat( const RGBByte &other ) 
00101 {
00102    // Compute the CIE Rec.709 luminance
00103    m_luminance = (float) (other.Red() * 0.2125f + other.Green() * 0.7154f + other.Blue() * 0.0721f) / MAXCOLOR;
00104    m_alpha = 1.0f;
00105 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
