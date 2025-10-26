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

# RGBFloat.h

[Go to the documentation of this file.](RGBFloat_8h.md)

<div class="fragment">

``` fragment
00001 // NAP  12/13/2004  \Noel120\Include\RGBFloat.h
00002 
00003 #ifndef __RGBFLOAT_H
00004 #define __RGBFLOAT_H
00005 
00006 #ifndef __ALLOCATE_H
00007 #include "Allocate.h"
00008 #endif
00009 #ifndef __FASTFTOL_H
00010 #include "FastFTOL.h"
00011 #endif
00012 #ifndef __VECTOR_H
00013 #include "Vector.h"
00014 #endif
00015 #ifndef __DATATYPE_H
00016 #include "DataType.h"
00017 #endif
00018 #ifndef __OS9ROS_H
00019 #include "Macros.h"
00020 #endif
00021 
00022 #include <math.h>
00023 
00024 class RGBHalf;
00025 class ColorBuf;
00026 class RGBByte;
00027 //******************************************************************************
00028 //** RGBFloat
00029 //******************************************************************************
00030 class RGBFloat {
00031 public:
00032    float m_blue;
00033    float m_green;
00034    float m_red;
00035 
00036    RGBFloat( void ) { }
00037    RGBFloat( float red, float green, float blue ) { m_red = red; m_green = green; m_blue = blue; }
00038    RGBFloat( const float scalar ) { m_red = m_green = m_blue = scalar; }
00039    RGBFloat( COLORREF c ) { m_red=GetRValue(c); m_green=GetGValue(c); m_blue=GetBValue(c); }
00040    RGBFloat( const RGBFloat &other ) { *this = other; }
00041    RGBFloat( const RGBHalf &other );
00042    RGBFloat( const RGBByte &other );
00043 
00044 #if _MEMDEBUG
00045    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00046 #else
00047    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00048 #endif   
00049    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00050 
00051    RGBFloat & operator = ( float scalar) { m_red = m_green = m_blue = scalar; return *this; }
00052    RGBFloat & operator = ( const RGBFloat &other) { m_red = other.m_red; m_green = other.m_green; m_blue = other.m_blue; return *this; }
00053 
00054    RGBFloat & operator += ( const RGBFloat &other ) { m_red += other.m_red; m_green += other.m_green; m_blue += other.m_blue; return *this; }
00055    RGBFloat & operator -= ( const RGBFloat &other ) { m_red -= other.m_red; m_green -= other.m_green; m_blue -= other.m_blue; return *this; }
00056    RGBFloat & operator *= ( const RGBFloat &other ) { m_red *= other.m_red; m_green *= other.m_green; m_blue *= other.m_blue; return *this; }
00057    RGBFloat & operator *= ( float scale )              { m_red *= scale; m_green *= scale; m_blue *= scale; return *this; }
00058    RGBFloat & operator /= ( const RGBFloat &other ) { m_red /= other.m_red; m_green /= other.m_green; m_blue /= other.m_blue; return *this; }
00059    RGBFloat & operator /= ( float scale )              { return (*this *= (1/scale)); }
00060 
00061    float Red() const   { return m_red;   }
00062    float Green() const { return m_green; }
00063    float Blue() const { return m_blue;  }   
00064    
00065    void SetRed(float red)     { m_red = red;   }
00066    void SetGreen(float green) { m_green = green; }
00067    void SetBlue(float blue)   { m_blue = blue;  }   
00068    
00069    void Set( float red, float green, float blue ) { m_red = red; m_green = green; m_blue = blue; }
00070    void Set( float init ) { m_red = m_green = m_blue = init; }
00071 
00072    int operator == ( const RGBFloat &a )       const { return (m_red == a.m_red) && (m_green == a.m_green) && (m_blue == a.m_blue); }
00073    int operator != ( const RGBFloat &a )       const { return !(*this == a); }   
00074 
00075    RGBFloat operator + ( const RGBFloat &a ) const { return RGBFloat(*this) += a; }
00076    RGBFloat operator - ( const RGBFloat &a ) const { return RGBFloat(*this) -= a; }
00077    RGBFloat operator * ( const RGBFloat &a ) const { return RGBFloat(*this) *= a; }
00078    RGBFloat operator * ( float s )              const { return RGBFloat(*this) *= s; }
00079    RGBFloat operator / ( float s )              const { return RGBFloat(*this) /= s; }
00080    RGBFloat operator / ( const RGBFloat &a ) const { return RGBFloat(*this) /= a; }
00081    float operator[]( int i ) const { ASSERT(i < 3); return (&m_blue)[i]; }
00082 
00083    COLORREF GetCOLORREF() const { return RGB(fast_round(MAX(0.0f,MIN(255.0f, m_red))), fast_round(MAX(0.0f,MIN(255.0f, m_green))), fast_round(MAX(0.0f,MIN(255.0f, m_blue)))); }
00084    float GetLuminance() const { return 0.3f*m_red + 0.59f*m_green + 0.11f*m_blue; }
00085 
00086    friend RGBFloat operator * ( const float s, const RGBFloat &a )  { return a * s; }
00087    
00088    void Min(float min) { if (m_red<min) m_red=min; if (m_green<min) m_green=min; if (m_blue<min) m_blue=min; }
00089    void Max(float max) { if (m_red>max) m_red=max; if (m_green>max) m_green=max; if (m_blue>max) m_blue=max; }
00090    void MinMax(float min, float max) { if (m_red>max) m_red=max; else if (m_red<min) m_red=min; 
00091                                        if (m_green>max) m_green=max; else if (m_green<min) m_green=min;
00092                                        if (m_blue>max) m_blue=max; else if (m_blue<min) m_blue=min; }
00093    RGBFloat GammaCorrect( float power ) const
00094    {
00095       if (power == 1)
00096          *this;
00097       return RGBFloat((float)pow(m_red, 1.f/power ), (float)pow(m_green, 1.f/power ), 
00098        (float)pow(m_blue, 1.f/power ));
00099    }
00100 
00101    BOOL CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
00102       if ( m_red < lobound || m_red > hibound )
00103          return TRUE;
00104       if ( m_green < lobound || m_green > hibound )
00105          return TRUE;
00106       if ( m_blue < lobound || m_blue > hibound )
00107          return TRUE;
00108       return FALSE;
00109    };
00110 };
00111 
00112 inline RGBFloat GetSpectrumColor(float x)
00113 {
00114    float theta = (1.66f * (float)V_PI) * x;
00115    return RGBFloat((2.0f+(float)cos(theta))/3.0f, (1.0f+(float)cos(theta-(2.0f*V_PI/3.0f)))/2.0f, (2.0f+(float)cos(theta-(4.0f*V_PI/3.0f)))/3.0f);
00116 }
00117 
00118 //*****************************************************************************
00119 //** RGBAFloat
00120 //*****************************************************************************
00121 class RGBAHalf;
00122 class RGBAByte;
00123 class RGBAFloat 
00124 {
00125 public:
00126    RGBFloat m_color;
00127    float m_alpha;
00128 
00129    RGBAFloat( void ) { }
00130    RGBAFloat( float red, float green, float blue, float alpha ) : m_color(red, green, blue) {m_alpha = alpha; }
00131    RGBAFloat( float scalar ) : m_color(scalar) { m_alpha = scalar; }
00132    RGBAFloat( COLORREF c ) : m_color(c) { m_alpha = 1.0f; }
00133    RGBAFloat( const RGBAFloat &other ) { *this = other; }
00134    RGBAFloat( const RGBAHalf &other );
00135    RGBAFloat( const RGBAByte &other );
00136    RGBAFloat( const ColorBuf &other );
00137    RGBAFloat( const RGBHalf &other );
00138 
00139 #if _MEMDEBUG
00140    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00141 #else
00142    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00143 #endif   
00144    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00145 
00146    RGBAFloat & operator = ( const RGBAFloat &other) { m_color = other.Color(); m_alpha = other.Alpha(); return *this; }
00147 
00148    RGBAFloat & operator += ( const RGBAFloat &other ) { m_color += other.Color(); m_alpha += other.m_alpha; return *this; }
00149    RGBAFloat & operator -= ( const RGBAFloat &other ) { m_color -= other.Color(); m_alpha -= other.m_alpha; return *this; }
00150    RGBAFloat & operator *= ( const RGBAFloat &other ) { m_color *= other.Color(); m_alpha *= other.m_alpha; return *this; }
00151    RGBAFloat & operator *= ( float scale ) { m_color *= scale; m_alpha *= scale; return *this; }
00152    RGBAFloat & operator /= ( const RGBAFloat &other ) { m_color /= other.Color(); m_alpha /= other.m_alpha; return *this; }
00153    RGBAFloat & operator /= ( float scale ) { return (*this *= (1/scale)); }
00154 
00155    RGBFloat Color() const { return m_color; }
00156    float Red() const { return m_color.Red();  }   
00157    float Green() const { return m_color.Green();  }   
00158    float Blue() const { return m_color.Blue();  }   
00159    float Alpha() const { return m_alpha;  }   
00160    void SetRed(float red) { m_color.SetRed(red); }
00161    void SetGreen(float green) { m_color.SetGreen(green); }
00162    void SetBlue(float blue) { m_color.SetBlue(blue); }
00163    void SetAlpha(float alpha) { m_alpha = alpha; }
00164 
00165    void Set( float red, float green, float blue, float alpha )  { m_color.Set(red, green, blue); m_alpha = alpha; }
00166    void Set( float init ) { m_color.Set(init); m_alpha = init; }
00167    void SetNoAlpha( const RGBFloat &color) { m_color = color; }
00168    
00169    int operator == ( const RGBAFloat &a )       const { return (m_color == a.Color()) && (m_alpha == a.Alpha()); }
00170    int operator != ( const RGBAFloat &a )       const { return !(*this == a); }   
00171 
00172    RGBAFloat operator + ( const RGBAFloat &a ) const { return RGBAFloat(*this) += a; }
00173    RGBAFloat operator - ( const RGBAFloat &a ) const { return RGBAFloat(*this) -= a; }
00174    RGBAFloat operator * ( const RGBAFloat &a ) const { return RGBAFloat(*this) *= a; }
00175    RGBAFloat operator * ( float s )              const { return RGBAFloat(*this) *= s; }
00176    RGBAFloat operator / ( float s )              const { return RGBAFloat(*this) /= s; }
00177    RGBAFloat operator / ( const RGBAFloat &a ) const { return RGBAFloat(*this) /= a; }
00178    float operator[]( int i ) const { ASSERT(i < 4); return (&m_color.m_blue)[i]; }
00179 
00180    friend RGBAFloat operator * ( const float s, const RGBAFloat &a )  { return a * s; }
00181 
00182    BOOL CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
00183       return m_color.CheckOffBound( lobound, hibound );
00184    };
00185 };
00186 
00187 //*****************************************************************************
00188 //** YAFloat
00189 //*****************************************************************************
00190 class YAHalf;
00191 class YAByte;
00192 class YAFloat 
00193 {
00194 public:
00195    float m_luminance;
00196    float m_alpha;
00197 
00198    YAFloat( void ) { }
00199    YAFloat( float luminance ) : m_luminance(luminance), m_alpha(1.0f) {};
00200    YAFloat( float luminance, float alpha ) : m_luminance(luminance), m_alpha(alpha) {};
00201    YAFloat( const YAFloat &other ) { *this = other; }
00202    YAFloat( const YAHalf &other );
00203    YAFloat( const YAByte &other );
00204 
00205    // Compute the CIE Rec.709 luminance
00206    YAFloat( const RGBAFloat &other ) { m_luminance = other.Red() * 0.2125f + other.Green() * 0.7154f + other.Blue() * 0.0721f; m_alpha = other.Alpha(); };
00207    YAFloat( const RGBAHalf &other );
00208    YAFloat( const RGBAByte &other );
00209    YAFloat( const ColorBuf &other );
00210    YAFloat( const RGBHalf &other );
00211    YAFloat( const RGBByte &other );
00212 
00213 #if _MEMDEBUG
00214    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00215 #else
00216    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00217 #endif   
00218    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00219 
00220    YAFloat & operator = ( const YAFloat &other) { m_luminance = other.m_luminance; m_alpha = other.m_alpha; return *this; }
00221 
00222    YAFloat & operator += ( const YAFloat &other ) { m_luminance += other.m_luminance; m_alpha += other.m_alpha; return *this; }
00223    YAFloat & operator -= ( const YAFloat &other ) { m_luminance -= other.m_luminance; m_alpha -= other.m_alpha; return *this; }
00224    YAFloat & operator *= ( const YAFloat &other ) { m_luminance *= other.m_luminance; m_alpha *= other.m_alpha; return *this; }
00225    YAFloat & operator *= ( float scale ) { m_luminance *= scale; m_alpha *= scale; return *this; }
00226    YAFloat & operator /= ( const YAFloat &other ) { m_luminance /= other.m_luminance; m_alpha /= other.m_alpha; return *this; }
00227    YAFloat & operator /= ( float scale ) { return (*this *= (1/scale)); }
00228 
00229    float Luminance() const { return m_luminance; }
00230    float Alpha() const { return m_alpha;  }   
00231    void SetLuminance(float luminance) { m_luminance = luminance; }
00232    void SetAlpha(float alpha) { m_alpha = alpha; }
00233 
00234    void Set( float luminance, float alpha )  { m_luminance = luminance; m_alpha = alpha; }
00235    void Set( float luminance ) { m_luminance = luminance; m_alpha = 1.0f; }
00236    // Compute the CIE Rec.709 luminance
00237    void Set( float red, float green, float blue, float alpha=1.0f ) { m_luminance = red * 0.2125f + green * 0.7154f + blue * 0.0721f; m_alpha = alpha; };
00238    void SetNoAlpha( const float luminance) { m_luminance = luminance; }
00239    
00240    int operator == ( const YAFloat &a )       const { return (m_luminance == a.m_luminance) && (m_alpha == a.m_alpha); }
00241    int operator != ( const YAFloat &a )       const { return !(*this == a); }   
00242 
00243    YAFloat operator + ( const YAFloat &a ) const { return YAFloat(*this) += a; }
00244    YAFloat operator - ( const YAFloat &a ) const { return YAFloat(*this) -= a; }
00245    YAFloat operator * ( const YAFloat &a ) const { return YAFloat(*this) *= a; }
00246    YAFloat operator * ( float s )              const { return YAFloat(*this) *= s; }
00247    YAFloat operator / ( float s )              const { return YAFloat(*this) /= s; }
00248    YAFloat operator / ( const YAFloat &a ) const { return YAFloat(*this) /= a; }
00249    float operator[]( int i ) const { ASSERT(i < 2); return (&m_luminance)[i]; }
00250 
00251    friend YAFloat operator * ( const float s, const YAFloat &a )  { return a * s; }
00252 
00253    BOOL CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
00254       if ( m_luminance <