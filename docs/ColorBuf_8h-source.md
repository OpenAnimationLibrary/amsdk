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

# ColorBuf.h

[Go to the documentation of this file.](ColorBuf_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  7/22/2004  \DanLP115\Include\ColorBuf.h
00002 
00003 #define __COLORBUF_H
00004 
00005 #ifndef __FASTFTOL_H
00006 #include "FastFTOL.h"
00007 #endif
00008 #ifndef __VECTOR_H
00009 #include "Vector.h"
00010 #endif
00011 #ifndef __DATATYPE_H
00012 #include "DataType.h"
00013 #endif
00014 #ifndef __OS9ROS_H
00015 #include "Macros.h"
00016 #endif
00017 
00018 #include <math.h>
00019 #define V_PI 3.1415926535898
00020 
00021 #define BACKGROUNDMASK        0x00FFFFFF
00022 #define MAXCOLOR     255
00023 #define DEPTH24      24
00024 #define NUMMIPLEVEL  4
00025 
00026 typedef union {
00027    struct {
00028       unsigned blue     :  4;
00029       unsigned green    :  4;
00030       unsigned red      :  4;
00031       unsigned unused   :  3;
00032       unsigned edge  :  1;
00033    } bits;
00034    SWORD color;
00035 } Color;
00036 
00037 class RGBAFloat;
00038 class RGBFloat;
00039 class ColorBuf {
00040 public:
00041    union {
00042       struct {
00043 #ifndef _MAC
00044         UBYTE             red, green, blue, alpha;
00045 #else
00046         UBYTE             alpha, blue, green, red;
00047 #endif
00048       } values;
00049       ULONG color;
00050    };
00051 
00052    void operator += ( const ColorBuf & );
00053    void operator -= ( const ColorBuf & );
00054    void operator *= ( const float );
00055    ColorBuf operator + ( const ColorBuf &other );
00056    operator COLORREF() { return RGB(values.red, values.green, values.blue); }
00057    ColorBuf &operator = ( const ColorBuf &other) { color = other.color; return *this; }
00058    
00059    RGBFloat GetFactoredRGBFloat() const;
00060    RGBFloat GetNormalizedRGBFloat() const;
00061 
00062    ColorBuf() { color = 0; values.alpha = MAXCOLOR; }
00063    ColorBuf( LONG col ) { color = col; values.alpha = MAXCOLOR; }
00064    ColorBuf( UBYTE pred, UBYTE pgreen, UBYTE pblue ) { values.red = pred; values.green = pgreen; values.blue = pblue; values.alpha = MAXCOLOR; }
00065    ColorBuf( UBYTE pred, UBYTE pgreen, UBYTE pblue, UBYTE palpha ) { values.red = pred; values.green = pgreen; values.blue = pblue; values.alpha = palpha; }
00066    ColorBuf( COLORREF c ) { values.red=GetRValue(c); values.green=GetGValue(c); values.blue=GetBValue(c); }
00067    ColorBuf( const RGBAFloat &color );
00068    
00069    UBYTE Red()   const { return values.red; }
00070    UBYTE Green() const { return values.green; }
00071    UBYTE Blue()  const { return values.blue; }
00072    UBYTE Alpha() const { return values.alpha; }
00073    ULONG Color() const { return color; }
00074    void Set( UBYTE pred, UBYTE pgreen, UBYTE pblue, UBYTE alpha ) { values.red = pred; values.green = pgreen; values.blue = pblue; values.alpha = alpha; }
00075    void SetRed( UBYTE red ) { values.red = red; }
00076    void SetGreen( UBYTE green ) { values.green = green; }
00077    void SetBlue( UBYTE blue ) { values.blue = blue; }
00078    void SetAlpha( UBYTE alpha ) { values.alpha = alpha; }
00079    void SetColor( ULONG pcolor ) { color = pcolor; values.alpha = MAXCOLOR; }
00080    void GammaCorrect(float power);
00081 
00082    inline RGBFloat Get() const;
00083    float GetOpacity() const;
00084    inline void Set( const RGBFloat & );
00085    void SetOpacity( const float value );
00086 };
00087 
00088 inline float ColorBuf::GetOpacity( void ) const
00089 {
00090    return (float)values.alpha/MAXCOLOR;
00091 }
00092 
00093 inline void ColorBuf::SetOpacity( const float opacity )
00094 {
00095    values.alpha = fast_ftol_unsigned(opacity * MAXCOLOR + .5f);
00096 }
00097 
00098 inline void ColorBuf::operator += ( const ColorBuf &other )
00099 {
00100    int tempred, tempgreen, tempblue, tempalpha;
00101    if ((tempred = values.red + other.values.red) > MAXCOLOR)
00102       values.red = MAXCOLOR;
00103    else
00104       values.red = tempred;
00105    if ((tempgreen = values.green + other.values.green) > MAXCOLOR)
00106       values.green = MAXCOLOR;
00107    else
00108       values.green = tempgreen;
00109    if ((tempblue = values.blue + other.values.blue) > MAXCOLOR)
00110       values.blue = MAXCOLOR;
00111    else
00112       values.blue = tempblue;
00113    if ((tempalpha = values.alpha + other.values.alpha) > MAXCOLOR)
00114       values.alpha = MAXCOLOR;
00115    else
00116       values.alpha = tempalpha;
00117 }
00118 
00119 inline ColorBuf ColorBuf::operator + ( const ColorBuf &other )
00120 {
00121    ColorBuf temp(*this);
00122    temp.red += other.values.red;
00123    temp.green += other.values.green;
00124    temp.blue += other.values.blue;
00125    temp.alpha += other.values.alpha;
00126    return temp;
00127 }
00128 
00129 inline void ColorBuf::operator -= ( const ColorBuf &other )
00130 {
00131    values.red -= other.values.red;
00132    values.green -= other.values.green;
00133    values.blue -= other.values.blue;
00134    values.alpha -= other.values.alpha;
00135 }
00136 
00137 inline void ColorBuf::operator *= ( const float factor )
00138 {
00139    values.red = (UBYTE)(values.red * factor + .5);
00140    values.green = (UBYTE)(values.green * factor + .5);
00141    values.blue = (UBYTE)(values.blue * factor + .5);
00142    values.alpha = (UBYTE)(values.alpha * factor + .5);
00143 }
00144 
00145 inline void GammaCorrectColBuf( UBYTE *color, float power)
00146 {
00147    if (power == 1)
00148       return;
00149    *color = fast_round(MIN(255.0f, MAXCOLOR * (float)pow((float)*color/MAXCOLOR, 1.f/power )));
00150 }
00151 
00152 inline void ColorBuf::GammaCorrect(float power)
00153 {
00154    if (power == 1)
00155       return;
00156    ::GammaCorrectColBuf(&values.red,   power);
00157    ::GammaCorrectColBuf(&values.green, power);
00158    ::GammaCorrectColBuf(&values.blue,  power);
00159 }
00160 
00161 #define MAKELUMINANCE( red, green, blue ) (0.3f*red + 0.59f*green + 0.11f*blue)
00162 
00163 
00164 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
