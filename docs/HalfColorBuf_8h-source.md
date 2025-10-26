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

# HalfColorBuf.h

[Go to the documentation of this file.](HalfColorBuf_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  7/26/2004  \DanLP115\Include\HalfColorBuf.h
00002 
00003 #define __HALFCOLORBUF_H
00004 
00005 #include "3rdParty/OpenEXR/half.h"
00006 
00007 class ColorBuf;
00008 class ColorVector;
00009 class ColorVectorAlpha;
00010 class HalfColorBuf 
00011 {
00012 public:
00013    half  m_red, m_green, m_blue;
00014    HalfColorBuf() { m_red = m_green = m_blue = 0; }
00015 
00016 //Copy Constructors
00017    HalfColorBuf( const HalfColorBuf &other );
00018    HalfColorBuf( const ColorVector &colorvector );
00019 
00020    HalfColorBuf &operator = ( const HalfColorBuf &other );
00021    
00022    void operator += ( const HalfColorBuf &other );
00023    void operator -= ( const HalfColorBuf &other );
00024    void operator *= ( float factor );
00025    void operator /= ( float factor );
00026 
00027    HalfColorBuf operator + ( const HalfColorBuf &other );
00028 
00029    half operator [] ( int i ) const  { return (&m_red)[i]; }
00030    half &operator [] (int i) { return (&m_red)[i]; }
00031 
00032    int operator == ( const HalfColorBuf &other ) const;
00033    int operator != ( const HalfColorBuf &other ) const  { return !(*this == other); }   
00034 
00035    half Red()   const { return m_red; }
00036    half Green() const { return m_green; }
00037    half Blue()  const { return m_blue; }
00038    
00039    void Set( half value ) { m_red = m_green = m_blue = value; }
00040    void Set( half red, half green, half blue) { m_red = red; m_green = green; m_blue = blue; }
00041    void SetRed  ( half red   ) { m_red   = red;   }
00042    void SetGreen( half green ) { m_green = green; }
00043    void SetBlue ( half blue  ) { m_blue  = blue;  }
00044    
00045    void Max(float max) { 
00046       SetRed( MIN(pmax, Red()));
00047       SetGreen( MIN(pmax, Green()));
00048       SetBlue( MIN(pmax, Blue()));
00049    }
00050    float GetLuminance() const { return 0.3f*m_red + 0.59f*m_green + 0.11f*m_blue; }
00051 };
00052 
00053 inline HalfColorBuf::HalfColorBuf( const HalfColorBuf &other )
00054 {
00055    (*this) = other;
00056 }
00057 
00058 inline HalfColorBuf &HalfColorBuf::operator = ( const HalfColorBuf &other )
00059 {
00060    m_red   = other.Red();
00061    m_green = other.Green();
00062    m_blue  = other.Blue();
00063    return *this;
00064 }
00065 
00066 inline void HalfColorBuf::operator += ( const HalfColorBuf &other )
00067 {
00068    m_red   += other.Red();
00069    m_green += other.Green();
00070    m_blue  += other.Blue();
00071 }
00072 
00073 inline void HalfColorBuf::operator -= ( const HalfColorBuf &other )
00074 {
00075    m_red   -= other.Red();
00076    m_green -= other.Green();
00077    m_blue  -= other.Blue();
00078 }
00079 
00080 inline void HalfColorBuf::operator *= ( float factor )
00081 {
00082    m_red  *= factor;
00083    m_green *= factor;
00084    m_blue  *= factor;
00085 }
00086 
00087 inline void HalfColorBuf::operator /= ( float factor )
00088 {
00089    m_red   /= factor;
00090    m_green /= factor;
00091    m_blue  /= factor;
00092 }
00093 
00094 inline HalfColorBuf HalfColorBuf::operator + ( const HalfColorBuf &other )
00095 {
00096    m_red += other.Red();
00097    m_green += other.Green();
00098    m_blue += other.Blue();
00099    return HalfColorBuf(*this);
00100 }
00101 
00102 inline int HalfColorBuf::operator == ( const HalfColorBuf &other ) const
00103 {
00104    if (m_red == other.m_red &&
00105     m_green == other.m_green &&
00106     m_blue == other.m_blue)
00107       return TRUE;
00108    return FALSE;
00109 }
00110 
00111 //**********************************************************
00112 //**********************************************************
00113 //**********************************************************
00114 //**********************************************************
00115 class HalfColorBufAlpha 
00116 {
00117 public:
00118    HalfColorBuf m_color;
00119    half m_alpha;
00120      HalfColorBufAlpha() { m_alpha = 1; }
00121 //Copy Constructors
00122    HalfColorBufAlpha( const HalfColorBufAlpha &other ) { (*this) = other;}
00123    HalfColorBufAlpha( const HalfColorBuf &other ) : m_color(other) { m_alpha = 1; }
00124    HalfColorBufAlpha( const ColorBuf &colorbuf );
00125 
00126    HalfColorBufAlpha &operator = ( const HalfColorBufAlpha &other );
00127    
00128    void operator += ( const HalfColorBufAlpha &other );
00129    void operator -= ( const HalfColorBufAlpha &other );
00130    void operator *= ( float factor);
00131    void operator /= ( float factor);
00132 
00133    HalfColorBufAlpha operator + ( const HalfColorBufAlpha &other );
00134 
00135    int operator == ( const HalfColorBufAlpha &other ) const;
00136    int operator != ( const HalfColorBufAlpha &other ) const  { return !(*this == other); }   
00137 
00138    half operator [] ( int i ) const  { return ((half *) &m_color)[i]; }
00139    half &operator [] (int i) { return ((half *) &m_color)[i]; }
00140 
00141    HalfColorBuf Color() const { return m_color; }
00142 
00143    half Red()   const { return m_color.Red(); }
00144    half Green() const { return m_color.Green(); }
00145    half Blue()  const { return m_color.Blue(); }
00146    half Alpha() const { return m_alpha; }
00147 
00148    void SetRed(half red) { m_color.SetRed(red);} 
00149    void SetGreen(half green) { m_color.SetGreen(green);} 
00150    void SetBlue(half blue) { m_color.SetBlue(blue);} 
00151 
00152    void SetColor ( HalfColorBuf &color ) { m_color = color;   }
00153    void SetAlpha ( half alpha ) { m_alpha = alpha;   }
00154 
00155    void Set( half red, half green, half blue, half alpha) { m_color.Set(red, green, blue); m_alpha = alpha; }
00156    
00157    void Max(float max) { 
00158       m_color.Max(max);
00159       SetAlpha( MIN( pmax, Alpha()));
00160    }
00161 };
00162 
00163 inline HalfColorBufAlpha &HalfColorBufAlpha::operator = ( const HalfColorBufAlpha &other )
00164 {
00165    m_color = other.Color();
00166    m_alpha = other.Alpha();
00167    return *this;
00168 }
00169 
00170 inline void HalfColorBufAlpha::operator += ( const HalfColorBufAlpha &other )
00171 {
00172    m_color += other.Color();
00173    m_alpha += other.Alpha();
00174 }
00175 
00176 inline void HalfColorBufAlpha::operator -= ( const HalfColorBufAlpha &other )
00177 {
00178    m_color -= other.Color();
00179    m_alpha -= other.Alpha();
00180 }
00181 
00182 inline void HalfColorBufAlpha::operator *= ( float factor )
00183 {
00184    m_color *= factor;
00185    m_alpha *= factor;
00186 }
00187 
00188 inline void HalfColorBufAlpha::operator /= ( float factor )
00189 {
00190    m_color /= factor;
00191    m_alpha /= factor;
00192 }
00193 
00194 inline HalfColorBufAlpha HalfColorBufAlpha::operator + ( const HalfColorBufAlpha &other )
00195 {
00196    m_color += other.Color();
00197    m_alpha += other.Alpha();
00198    return HalfColorBufAlpha(*this);
00199 }
00200 
00201 inline int HalfColorBufAlpha::operator == ( const HalfColorBufAlpha &other ) const
00202 {
00203    if (m_color == other.Color() && m_alpha == other.Alpha())
00204       return TRUE;
00205    return FALSE;
00206 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
