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

# ColorVec.h

[Go to the documentation of this file.](ColorVec_8h.md)

<div class="fragment">

``` fragment
00001 // NAP  12/20/2004  \Noel120\Include\ColorVec.h
00002 
00003 #ifndef __COLORVEC_H
00004 #define __COLORVEC_H
00005 
00006 #ifndef __FASTFTOL_H
00007 #include "FastFTOL.h"
00008 #endif
00009 #ifndef __VECTOR_H
00010 #include "Vector.h"
00011 #endif
00012 #ifndef __DATATYPE_H
00013 #include "DataType.h"
00014 #endif
00015 #ifndef __OS9ROS_H
00016 #include "Macros.h"
00017 #endif
00018 
00019 #include <math.h>
00020 
00021 class HalfColorBuf;
00022 class ColorBuf;
00023 //******************************************************************************
00024 //** ColorVector
00025 //******************************************************************************
00026 class ColorVector {
00027 public:
00028    float m_red;
00029    float m_green;
00030    float m_blue;
00031 
00032    ColorVector( void ) { }
00033    ColorVector( float red, float green, float blue ) { m_red = red; m_green = green; m_blue = blue; }
00034    ColorVector( const float scalar ) { m_red = m_green = m_blue = scalar; }
00035    ColorVector( COLORREF c ) { m_red=GetRValue(c); m_green=GetGValue(c); m_blue=GetBValue(c); }
00036    ColorVector( const ColorVector &other ) { *this = other; }
00037    ColorVector( const HalfColorBuf &other );
00038 
00039    ColorVector & operator = ( float scalar) { m_red = m_green = m_blue = scalar; return *this; }
00040    ColorVector & operator = ( const ColorVector &other) { m_red = other.m_red; m_green = other.m_green; m_blue = other.m_blue; return *this; }
00041 
00042    ColorVector & operator += ( const ColorVector &other ) { m_red += other.m_red; m_green += other.m_green; m_blue += other.m_blue; return *this; }
00043    ColorVector & operator -= ( const ColorVector &other ) { m_red -= other.m_red; m_green -= other.m_green; m_blue -= other.m_blue; return *this; }
00044    ColorVector & operator *= ( const ColorVector &other ) { m_red *= other.m_red; m_green *= other.m_green; m_blue *= other.m_blue; return *this; }
00045    ColorVector & operator *= ( float scale )              { m_red *= scale; m_green *= scale; m_blue *= scale; return *this; }
00046    ColorVector & operator /= ( const ColorVector &other ) { m_red /= other.m_red; m_green /= other.m_green; m_blue /= other.m_blue; return *this; }
00047    ColorVector & operator /= ( float scale )              { return (*this *= (1/scale)); }
00048 
00049    float Red() const   { return m_red;   }
00050    float Green() const { return m_green; }
00051    float Blue() const { return m_blue;  }   
00052    
00053    void SetRed(float red)     { m_red = red;   }
00054    void SetGreen(float green) { m_green = green; }
00055    void SetBlue(float blue)   { m_blue = blue;  }   
00056    
00057    void Set( float red, float green, float blue ) { m_red = red; m_green = green; m_blue = blue; }
00058    void Set( float init ) { m_red = m_green = m_blue = init; }
00059 
00060    int operator == ( const ColorVector &a )       const { return (m_red == a.m_red) && (m_green == a.m_green) && (m_blue == a.m_blue); }
00061    int operator != ( const ColorVector &a )       const { return !(*this == a); }   
00062 
00063    ColorVector operator + ( const ColorVector &a ) const { return ColorVector(*this) += a; }
00064    ColorVector operator - ( const ColorVector &a ) const { return ColorVector(*this) -= a; }
00065    ColorVector operator * ( const ColorVector &a ) const { return ColorVector(*this) *= a; }
00066    ColorVector operator * ( float s )              const { return ColorVector(*this) *= s; }
00067    ColorVector operator / ( float s )              const { return ColorVector(*this) /= s; }
00068    ColorVector operator / ( const ColorVector &a ) const { return ColorVector(*this) /= a; }
00069    float operator[]( int i ) const { return (&m_red)[i]; }
00070 
00071    COLORREF GetCOLORREF() const { return RGB(fast_round(m_red), fast_round(m_green), fast_round(m_blue)); }
00072    float GetLuminance() const { return 0.3f*m_red + 0.59f*m_green + 0.11f*m_blue; }
00073 
00074    friend ColorVector operator * ( const float s, const ColorVector &a )  { return a * s; }
00075    
00076    void Min(float min) { if (m_red<min) m_red=min; if (m_green<min) m_green=min; if (m_blue<min) m_blue=min; }
00077    void Max(float max) { if (m_red>max) m_red=max; if (m_green>max) m_green=max; if (m_blue>max) m_blue=max; }
00078    void MinMax(float min, float max) { if (m_red>max) m_red=max; else if (m_red<min) m_red=min; 
00079                                        if (m_green>max) m_green=max; else if (m_green<min) m_green=min;
00080                                        if (m_blue>max) m_blue=max; else if (m_blue<min) m_blue=min; }
00081 };
00082 
00083 inline ColorVector GetSpectrumColorVector(float x)
00084 {
00085    float theta = (1.66f * (float)V_PI) * x;
00086    return ColorVector((2.0f+(float)cos(theta))/3.0f, (1.0f+(float)cos(theta-(2.0f*V_PI/3.0f)))/2.0f, (2.0f+(float)cos(theta-(4.0f*V_PI/3.0f)))/3.0f);
00087 }
00088 
00089 //*****************************************************************************
00090 //** ColorVectorAlpha
00091 //*****************************************************************************
00092 class HalfColorBufAlpha;
00093 class ColorVectorAlpha 
00094 {
00095 public:
00096    ColorVector m_color;
00097    float m_alpha;
00098 
00099    ColorVectorAlpha( void ) { }
00100    ColorVectorAlpha( float red, float green, float blue, float alpha ) : m_color(red, green, blue) {m_alpha = alpha; }
00101    ColorVectorAlpha( float scalar ) : m_color(scalar) { m_alpha = scalar; }
00102    ColorVectorAlpha( COLORREF c ) : m_color(c) { m_alpha = 1.0f; }
00103    ColorVectorAlpha( const ColorVectorAlpha &other ) { *this = other; }
00104    ColorVectorAlpha( const HalfColorBufAlpha &other );
00105    ColorVectorAlpha( const ColorBuf &other );
00106 
00107    ColorVectorAlpha & operator = ( const ColorVectorAlpha &other) { m_color = other.Color(); m_alpha = other.Alpha(); return *this; }
00108 
00109    ColorVectorAlpha & operator += ( const ColorVectorAlpha &other ) { m_color += other.Color(); m_alpha += other.m_alpha; return *this; }
00110    ColorVectorAlpha & operator -= ( const ColorVectorAlpha &other ) { m_color -= other.Color(); m_alpha -= other.m_alpha; return *this; }
00111    ColorVectorAlpha & operator *= ( const ColorVectorAlpha &other ) { m_color *= other.Color(); m_alpha *= other.m_alpha; return *this; }
00112    ColorVectorAlpha & operator *= ( float scale ) { m_color *= scale; m_alpha *= scale; return *this; }
00113    ColorVectorAlpha & operator /= ( const ColorVectorAlpha &other ) { m_color /= other.Color(); m_alpha /= other.m_alpha; return *this; }
00114    ColorVectorAlpha & operator /= ( float scale ) { return (*this *= (1/scale)); }
00115 
00116    ColorVector Color() const { return m_color; }
00117    float Red() const { return m_color.Red();  }   
00118    float Green() const { return m_color.Green();  }   
00119    float Blue() const { return m_color.Blue();  }   
00120    float Alpha() const { return m_alpha;  }   
00121    void SetRed(float red) { m_color.SetRed(red); }
00122    void SetGreen(float green) { m_color.SetGreen(green); }
00123    void SetBlue(float blue) { m_color.SetBlue(blue); }
00124    void SetAlpha(float alpha) { m_alpha = alpha; }
00125 
00126    void Set( float red, float green, float blue, float alpha )  { m_color.Set(red, green, blue); m_alpha = alpha; }
00127    void Set( float init ) { m_color.Set(init); m_alpha = init; }
00128 
00129    int operator == ( const ColorVectorAlpha &a )       const { return (m_color == a.Color()) && (m_alpha == a.Alpha()); }
00130    int operator != ( const ColorVectorAlpha &a )       const { return !(*this == a); }   
00131 
00132    ColorVectorAlpha operator + ( const ColorVectorAlpha &a ) const { return ColorVectorAlpha(*this) += a; }
00133    ColorVectorAlpha operator - ( const ColorVectorAlpha &a ) const { return ColorVectorAlpha(*this) -= a; }
00134    ColorVectorAlpha operator * ( const ColorVectorAlpha &a ) const { return ColorVectorAlpha(*this) *= a; }
00135    ColorVectorAlpha operator * ( float s )              const { return ColorVectorAlpha(*this) *= s; }
00136    ColorVectorAlpha operator / ( float s )              const { return ColorVectorAlpha(*this) /= s; }
00137    ColorVectorAlpha operator / ( const ColorVectorAlpha &a ) const { return ColorVectorAlpha(*this) /= a; }
00138    float operator[]( int i ) const { return (&m_color.m_red)[i]; }
00139 
00140    friend ColorVectorAlpha operator * ( const float s, const ColorVectorAlpha &a )  { return a * s; }
00141 };
00142 
00143 //*****************************************************************************
00144 //** Colors
00145 //*****************************************************************************
00146 class ColorVectors {
00147 public:
00148    ColorVector m_ambient, m_diffuse, m_specular, m_reflection, m_shadow;
00149 };
00150 
00151 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
