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

# ColorBuf.inl

[Go to the documentation of this file.](ColorBuf_8inl.md)

<div class="fragment">

``` fragment
00001 // Dan  7/25/2004  \DanLP115\Include\ColorBuf.inl
00002 
00003 #ifndef __COLORBUF_INL
00004 #define __COLORBUF_INL
00005 
00006 #ifndef __COLORBUF_H
00007 #include "ColorBuf.h"
00008 #endif
00009 #ifndef __RGBFLOAT_H
00010 #include "RGBFloat.h"
00011 #endif
00012 
00013 inline ColorBuf::ColorBuf( const RGBAFloat &color )
00014 {
00015    values.red   = MIN(255, fast_ftol_unsigned(color.Red()   * MAXCOLOR + .5f));
00016    values.green = MIN(255, fast_ftol_unsigned(color.Green() * MAXCOLOR + .5f));
00017    values.blue  = MIN(255, fast_ftol_unsigned(color.Blue()  * MAXCOLOR + .5f));
00018    values.alpha = MIN(255, fast_ftol_unsigned(color.Alpha() * MAXCOLOR + .5f));
00019 }
00020 
00021 inline void ColorBuf::Set( const RGBFloat &color )
00022 {
00023    values.red   = MIN(255, fast_ftol_unsigned(color.Red()   * MAXCOLOR + .5f));
00024    values.green = MIN(255, fast_ftol_unsigned(color.Green() * MAXCOLOR + .5f));
00025    values.blue  = MIN(255, fast_ftol_unsigned(color.Blue()  * MAXCOLOR + .5f));
00026 }
00027 
00028 inline RGBFloat ColorBuf::Get( void ) const
00029 {  
00030    return RGBFloat((float)values.red/MAXCOLOR, (float)values.green/MAXCOLOR,
00031     (float)values.blue/MAXCOLOR);
00032 }
00033 
00034 inline RGBFloat ColorBuf::GetFactoredRGBFloat() const
00035 {
00036    return RGBFloat(values.red, values.green, values.blue);
00037 }
00038 
00039 inline RGBFloat ColorBuf::GetNormalizedRGBFloat() const
00040 {
00041    return RGBFloat((float)values.red/MAXCOLOR, (float)values.green/MAXCOLOR, (float)values.blue/MAXCOLOR);
00042 }
00043 
00044 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
