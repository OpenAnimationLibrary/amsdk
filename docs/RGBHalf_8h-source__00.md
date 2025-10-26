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

# RGBHalf.h

[Go to the documentation of this file.](RGBHalf_8h.md)

<div class="fragment">

``` fragment
00001 // KB  12/2/2004  \Include\RGBHalf.h
00002 
00003 #define __RGBHALF_H
00004 
00005 #include "3rdparty/openexr/half.h"
00006 
00007 #ifndef __ALLOCATE_H
00008 #include "Allocate.h"
00009 #endif
00010 #ifndef __MACROS_H
00011 #include "Macros.h"
00012 #endif
00013 
00014 class ColorBuf;
00015 class RGBFloat;
00016 class RGBAFloat;
00017 class RGBHalf 
00018 {
00019 public:
00020    half  m_blue, m_green, m_red;
00021    RGBHalf() { m_red = m_green = m_blue = 0; }
00022 
00023 //Copy Constructors
00024    RGBHalf( const RGBHalf &other );
00025    RGBHalf( const RGBFloat &colorvector );
00026    RGBHalf( const float &r, const float &g, const float &b );
00027    RGBHalf( const float &f ); //(f,f,f)
00028 
00029 #if _MEMDEBUG
00030    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00031 #else
00032    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00033 #endif   
00034    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00035 
00036    RGBHalf &operator = ( const RGBHalf &other );
00037    
00038    RGBHalf & operator += ( const RGBHalf &other );
00039    RGBHalf & operator -= ( const RGBHalf &other );
00040    RGBHalf & operator *= ( const RGBHalf &other );
00041    RGBHalf & operator *= ( float factor );
00042    RGBHalf & operator /= ( float factor );
00043    RGBHalf operator * ( const RGBHalf &other ) const { return RGBHalf(*this) *= other; }
00044    RGBHalf operator * ( float s ) const { return RGBHalf(*this) *= s; }
00045    RGBHalf operator / ( float s ) const { return RGBHalf(*this) /= s; }
00046 
00047    RGBHalf operator + ( const RGBHalf &other );
00048 
00049    half operator [] ( int i ) const  { return (&m_red)[i]; }
00050    half &operator [] (int i) { return (&m_red)[i]; }
00051 
00052    int operator == ( const RGBHalf &other ) const;
00053    int operator != ( const RGBHalf &other ) const  { return !(*this == other); }   
00054 
00055    half Red()   const { return m_red; }
00056    half Green() const { return m_green; }
00057    half Blue()  const { return m_blue; }
00058    
00059    void Set( half value ) { m_red = m_green = m_blue = value; }
00060    void Set( half red, half green, half blue) { m_red = red; m_green = green; m_blue = blue; }
00061    void SetRed  ( half red   ) { m_red   = red;   }
00062    void SetGreen( half green ) { m_green = green; }
00063    void SetBlue ( half blue  ) { m_blue  = blue;  }
00064    
00065    void Max(float max) { //Ken, NAP: not sure if this is correct half, float etc
00066       SetRed(MIN(max, (float)Red()));
00067       SetGreen(MIN(max, (float)Green()));
00068       SetBlue(MIN(max, (float)Blue()));
00069    }
00070    float GetLuminance() const { return 0.3f*m_red + 0.59f*m_green + 0.11f*m_blue; }
00071    RGBHalf GammaCorrect( float power)
00072    {
00073       if (power == 1)
00074          *this;
00075       RGBHalf rvalue; //NAP Bitmap speed
00076       rvalue.Set(pow((float)m_red, 1.f/power ), pow((float)m_green, 1.f/power ), 
00077        pow((float)m_blue, 1.f/power ));
00078       return rvalue;
00079    }
00080 
00081    BOOL CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
00082       if ( m_red < lobound || m_red > hibound )
00083          return TRUE;
00084       if ( m_green < lobound || m_green > hibound )
00085          return TRUE;
00086       if ( m_blue < lobound || m_blue > hibound )
00087          return TRUE;
00088       return FALSE;
00089    };
00090 };
00091 
00092 inline RGBHalf::RGBHalf( const RGBHalf &other )
00093 {
00094    (*this) = other;
00095 }
00096 inline RGBHalf::RGBHalf( const float &r, const float &g, const float &b )
00097 {
00098    m_red = r;
00099    m_green = g;
00100    m_blue = b;
00101 }
00102 inline RGBHalf::RGBHalf( const float &f )
00103 {
00104    m_red = f;
00105    m_green = f;
00106    m_blue = f;
00107 }
00108 inline RGBHalf &RGBHalf::operator = ( const RGBHalf &other )
00109 {
00110    m_red   = other.Red();
00111    m_green = other.Green();
00112    m_blue  = other.Blue();
00113    return *this;
00114 }
00115 
00116 inline RGBHalf & RGBHalf::operator += ( const RGBHalf &other )
00117 {
00118    m_red   += other.Red();
00119    m_green += other.Green();
00120    m_blue  += other.Blue();
00121    return *this;
00122 }
00123 
00124 inline RGBHalf & RGBHalf::operator -= ( const RGBHalf &other )
00125 {
00126    m_red   -= other.Red();
00127    m_green -= other.Green();
00128    m_blue  -= other.Blue();
00129    return *this;
00130 }
00131 
00132 inline RGBHalf & RGBHalf::operator *= ( const RGBHalf &other )
00133 {
00134    m_red   *= other.Red();
00135    m_green *= other.Green();
00136    m_blue  *= other.Blue();
00137    return *this;
00138 }
00139 
00140 inline RGBHalf & RGBHalf::operator *= ( float factor )
00141 {
00142    m_red  *= factor;
00143    m_green *= factor;
00144    m_blue  *= factor;
00145    return *this;
00146 }
00147 
00148 inline RGBHalf & RGBHalf::operator /= ( float factor )
00149 {
00150    m_red   /= factor;
00151    m_green /= factor;
00152    m_blue  /= factor;
00153    return *this;
00154 }
00155 
00156 inline RGBHalf RGBHalf::operator + ( const RGBHalf &other )
00157 {
00158    m_red += other.Red();
00159    m_green += other.Green();
00160    m_blue += other.Blue();
00161    return RGBHalf(*this);
00162 }
00163 
00164 inline int RGBHalf::operator == ( const RGBHalf &other ) const
00165 {
00166    if (m_red == other.m_red &&
00167     m_green == other.m_green &&
00168     m_blue == other.m_blue)
00169       return TRUE;
00170    return FALSE;
00171 }
00172 
00173 //**********************************************************
00174 //**********************************************************
00175 //**********************************************************
00176 //**********************************************************
00177 class RGBAHalf 
00178 {
00179 public:
00180    RGBHalf m_color;
00181    half m_alpha;
00182      RGBAHalf() { m_alpha = 1; }
00183 //Copy Constructors
00184    RGBAHalf( const RGBAHalf &other ) { (*this) = other;}
00185    RGBAHalf( const RGBHalf &other ) : m_color(other) { m_alpha = 1; }
00186    RGBAHalf( const float &r, const float &g, const float &b, const float &a );
00187    RGBAHalf( const ColorBuf &colorbuf );
00188    RGBAHalf( const float &f ) { m_alpha = 1; m_color.m_red = m_color.m_green = m_color.m_blue = f;}
00189 
00190 #if _MEMDEBUG
00191    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00192 #else
00193    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00194 #endif   
00195    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00196 
00197    RGBAHalf &operator = ( const RGBAHalf &other );
00198    inline RGBAHalf &operator = ( const RGBAFloat &other );
00199    
00200    RGBAHalf & operator += ( const RGBAHalf &other );
00201    RGBAHalf & operator -= ( const RGBAHalf &other );
00202    RGBAHalf & operator *= ( float factor);
00203    RGBAHalf & operator /= ( float factor);
00204    RGBAHalf operator * ( float s ) const { return RGBAHalf(*this) *= s; }
00205    RGBAHalf operator / ( float s ) const { return RGBAHalf(*this) /= s; }
00206 
00207    RGBAHalf operator + ( const RGBAHalf &other );
00208    RGBAHalf operator - ( const RGBAHalf &other );
00209 
00210    int operator == ( const RGBAHalf &other ) const;
00211    int operator != ( const RGBAHalf &other ) const  { return !(*this == other); }   
00212 
00213    half operator [] ( int i ) const  { return ((half *) &m_color)[i]; }
00214    half &operator [] (int i) { return ((half *) &m_color)[i]; }
00215 
00216    RGBHalf Color() const { return m_color; }
00217 
00218    half Red()   const { return m_color.Red(); }
00219    half Green() const { return m_color.Green(); }
00220    half Blue()  const { return m_color.Blue(); }
00221    half Alpha() const { return m_alpha; }
00222 
00223    void SetRed(half red) { m_color.SetRed(red);} 
00224    void SetGreen(half green) { m_color.SetGreen(green);} 
00225    void SetBlue(half blue) { m_color.SetBlue(blue);} 
00226 
00227    void SetColor ( RGBHalf &color ) { m_color = color;   }
00228    void SetAlpha ( half alpha ) { m_alpha = alpha;   }
00229 
00230    void Set( half red, half green, half blue, half alpha) { m_color.Set(red, green, blue); m_alpha = alpha; }
00231    
00232    void Max(float max) { 
00233       m_color.Max(max);
00234       SetAlpha(MIN(max, (float)Alpha()));
00235    }
00236 
00237    BOOL CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
00238       return m_color.CheckOffBound( lobound, hibound );
00239    };
00240 };
00241 
00242 inline RGBAHalf::RGBAHalf( const float &r, const float &g, const float &b, const float &a )
00243 {
00244    m_color.SetRed( r );
00245    m_color.SetGreen( g );
00246    m_color.SetBlue( b );
00247    m_alpha = a;
00248 }
00249 
00250 inline RGBAHalf &RGBAHalf::operator = ( const RGBAHalf &other )
00251 {
00252    m_color = other.Color();
00253    m_alpha = other.Alpha();
00254    return *this;
00255 }
00256 
00257 inline RGBAHalf & RGBAHalf::operator += ( const RGBAHalf &other )
00258 {
00259    m_color += other.Color();
00260    m_alpha += other.Alpha();
00261    return *this;
00262 }
00263 
00264 inline RGBAHalf & RGBAHalf::operator -= ( const RGBAHalf &other )
00265 {
00266    m_color -= other.Color();
00267    m_alpha -= other.Alpha();
00268    return *this;
00269 }
00270 
00271 inline RGBAHalf & RGBAHalf::operator *= ( float factor )
00272 {
00273    m_color *= factor;
00274    m_alpha *= factor;
00275    return *this;
00276 }
00277 
00278 inline RGBAHalf & RGBAHalf::operator /= ( float factor )
00279 {
00280    m_color /= factor;
00281    m_alpha /= factor;
00282    return *this;
00283 }
00284 
00285 inline RGBAHalf RGBAHalf::operator + ( const RGBAHalf &other )
00286 {
00287    m_color += other.Color();
00288    m_alpha += other.Alpha();
00289    return RGBAHalf(*this);
00290 }
00291 
00292 inline RGBAHalf RGBAHalf::operator - ( const RGBAHalf &other )
00293 {
00294    m_color -= other.Color();
00295    m_alpha -= other.Alpha();
00296    return RGBAHalf(*this);
00297 }
00298 
00299 inline int RGBAHalf::operator == ( const RGBAHalf &other ) const
00300 {
00301    if (m_color == other.Color() && m_alpha == other.Alpha())
00302       return TRUE;
00303    return FALSE;
00304 }
00305 
00306 //**********************************************************
00307 //**********************************************************
00308 //**********************************************************
00309 //**********************************************************
00310 class YAFloat;
00311 class YAByte;
00312 class YAHalf 
00313 {
00314 public:
00315    half m_luminance;
00316    half m_alpha;
00317    YAHalf() { m_alpha = 1; }
00318 //Copy Constructors
00319    YAHalf( const YAHalf &other ) { (*this) = other;}
00320    YAHalf( const half other ) : m_luminance(other) { m_alpha = 1; }
00321    YAHalf( const YAFloat &other );
00322    YAHalf( const YAByte &other );
00323    YAHalf( const float &l, const float &a );
00324    YAHalf( const float f ) { m_alpha = 1; m_luminance = f;}
00325 
00326 #if _MEMDEBUG
00327    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00328 #else
00329    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00330 #endif   
00331    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00332 
00333    YAHalf & operator = ( const YAHalf &other );
00334    YAHalf & operator = ( const YAFloat &other );
00335    YAHalf & operator = ( const YAByte &other );
00336    YAHalf & operator = ( const RGBFloat &other );
00337    YAHalf & operator = ( const RGBAFloat &other );
00338    YAHalf & operator = ( const ColorBuf &colorbuf );
00339    
00340    YAHalf & operator += ( const YAHalf &other );
00341    YAHalf & operator -= ( const YAHalf &other );
00342    YAHalf & operator *= ( float factor);
00343    YAHalf & operator /= ( float factor);
00344 
00345    YAHalf operator + ( const YAHalf &other );
00346 
00347    int operator == ( const YAHalf &other ) const;
00348    int operator != ( const YAHalf &other ) const  { return !(*this == other); }   
00349 
00350    half operator [] ( int i ) const  { return ((half *) &m_luminance)[i]; }
00351    half &operator [] ( int i ) { return ((half *) &m_luminance)[i]; }
00352 
00353    half Luminance() const { return m_luminance; }
00354    half Alpha() const { return m_alpha; }
00355 
00356    void SetLuminance ( half luminance ) { m_luminance = luminance;   }
00357    void SetAlpha ( half alpha ) { m_alpha = alpha;   }
00358 
00359    void Set( half luminance, half alpha) { m_luminance = luminance; m_alpha = alpha; }
00360 
00361    BOOL CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
00362       if ( m_luminance < lobound || m_luminance > hibound )
00363          return TRUE;
00364       return FALSE;
00365    };
00366 };
00367 
00368 inline YAHalf::YAHalf( const float &l, const float &a )
00369 {
00370    m_luminance = l;
00371    m_alpha = a;
00372 }
00373 
00374 inline YAHalf &YAHalf::operator = ( const YAHalf &other )
00375 {
00376    m_luminance = other.m_luminance;
00377    m_alpha = other.m_alpha;
00378    return *this;
00379 }
00380 
00381 inline YAHalf & YAHalf::operator += ( const YAHalf &other )
00382 {
00383    m_luminance += other.m_luminance;
00384    m_alpha += other.m_alpha;
00385    return *this;
00386 }
00387 
00388 inline YAHalf & YAHalf::operator -= ( const YAHalf &other )
00389 {
00390    m_luminance -= other.m_luminance;
00391    m_alpha -= other.m_alpha;
00392    return *this;
00393 }
00394 
00395 inline YAHalf & YAHalf::operator *= ( float factor )
00396 {
00397    m_luminance *= factor;
00398    m_alpha *= factor;
00399    return *this;
00400 }
00401 
00402 inline YAHalf & YAHalf::operator /= ( float factor )
00403 {
00404    m_luminance /= factor;
00