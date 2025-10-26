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

# ColorVec.inl

[Go to the documentation of this file.](ColorVec_8inl.md)

<div class="fragment">

``` fragment
00001 // Dan  7/25/2004  \DanLP115\Include\ColorVec.inl
00002 
00003 #define __COLORVEC_INL
00004 
00005 #ifndef __COLORVEC_H
00006 #include "ColorVec.h"
00007 #endif
00008 #ifndef __COLORBUF_H
00009 #include "ColorBuf.h"
00010 #endif
00011 #ifndef __HALFCOLORBUF_H
00012 #include "HalfColorBuf.h"
00013 #endif
00014 
00015 //*********************************************************************
00016 //*** ColorVector
00017 //*********************************************************************
00018 inline ColorVector::ColorVector( const HalfColorBuf &other )
00019 {
00020    m_red   = other.Red();
00021    m_green = other.Green();
00022    m_blue  = other.Blue();
00023 }
00024 
00025 //*********************************************************************
00026 //*** ColorVectorAlpha
00027 //*********************************************************************
00028 inline ColorVectorAlpha::ColorVectorAlpha( const HalfColorBufAlpha &other ) :
00029    m_color(other.Color())
00030 {
00031    m_alpha = other.Alpha();
00032 }
00033 
00034 inline ColorVectorAlpha::ColorVectorAlpha( const ColorBuf &other )
00035 { 
00036    SetRed((float)other.values.red   / MAXCOLOR); 
00037    SetGreen((float)other.values.green / MAXCOLOR); 
00038    SetBlue((float)other.values.blue   / MAXCOLOR); 
00039    SetAlpha((float)other.values.alpha / MAXCOLOR); 
00040 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
