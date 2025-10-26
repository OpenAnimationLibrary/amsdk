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

# RGBByte.h

[Go to the documentation of this file.](RGBByte_8h.md)

<div class="fragment">

``` fragment
00001 // NAP  12/20/2004  \Noel120\Include\RGBByte.h
00002 
00003 #define __RGBBYTE_H
00004 
00005 #ifndef __ALLOCATE_H
00006 #include "Allocate.h"
00007 #endif
00008 #ifndef __FASTFTOL_H
00009 #include "FastFTOL.h"
00010 #endif
00011 #ifndef __VECTOR_H
00012 #include "Vector.h"
00013 #endif
00014 #ifndef __DATATYPE_H
00015 #include "DataType.h"
00016 #endif
00017 #ifndef __OS9ROS_H
00018 #include "Macros.h"
00019 #endif
00020 
00021 class RGBAFloat;
00022 class RGBFloat;
00023 
00024 #define MAXCOLOR 255
00025 #define FLOATTOBYTE(flt) MAX(0,MIN(MAXCOLOR, fast_ftol_unsigned((flt) * MAXCOLOR + .5f)))
00026 
00027 //******************************************************************************
00028 //** RGBByte
00029 //******************************************************************************
00030 class RGBByte {
00031 public:
00032 #ifdef _MAC
00033    UBYTE m_red, m_green, m_blue;
00034 #else
00035    UBYTE m_blue, m_green, m_red;
00036 #endif
00037    RGBByte() { m_red = m_green = m_blue = 0;  }
00038    RGBByte( UBYTE pred, UBYTE pgreen, UBYTE pblue ) { m_red = pred; m_green = pgreen; m_blue = pblue; }
00039    RGBByte( COLORREF c ) { m_red=GetRValue(c); m_green=GetGValue(c); m_blue=GetBValue(c); }
00040    RGBByte( const RGBFloat &color );
00041 
00042 #if _MEMDEBUG
00043    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00044 #else
00045    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00046 #endif   
00047    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00048 
00049    RGBByte &operator += ( const RGBByte & );
00050    RGBByte &operator -= ( const RGBByte & );
00051    RGBByte &operator *= ( const float );
00052    RGBByte operator + ( const RGBByte &other );
00053    operator COLORREF() { return RGB(m_red, m_green, m_blue); }
00054    RGBByte &operator = ( const RGBByte &other) { m_red=other.m_red;m_green=other.m_green;m_blue=other.m_blue; return *this; }
00055    RGBByte &operator /= ( float scale )  { return (*this *= (1/scale)); }
00056    
00057    RGBFloat GetFactoredRGBFloat() const;
00058    RGBFloat GetNormalizedRGBFloat() const;
00059 
00060    UBYTE Red()   const { return m_red; }
00061    UBYTE Green() const { return m_green; }
00062    UBYTE Blue()  const { return m_blue; }
00063 
00064    void Set( UBYTE pred, UBYTE pgreen, UBYTE pblue ) { m_red = pred; m_green = pgreen; m_blue = pblue; }
00065    void Set( UBYTE value) { m_red = m_green = m_blue = value; }
00066    void SetRed( UBYTE red ) { m_red = red; }
00067    void SetGreen( UBYTE green ) { m_green = green; }
00068    void SetBlue( UBYTE blue ) { m_blue = blue; }
00069    RGBByte GammaCorrect(float power);
00070  
00071    RGBFloat Get() const;
00072    void Set( const RGBFloat & );
00073    
00074    float GetLuminance() { return 0.3f*m_red + 0.59f*m_green + 0.11f*m_blue; }   
00075 
00076    BOOL CheckOffBound( float lobound, float hibound ) { return FALSE; }; // YP : For HDR testing and debugging purpose
00077 };
00078 
00079 inline RGBByte &RGBByte::operator += ( const RGBByte &other )
00080 {
00081    int tempred, tempgreen, tempblue;
00082    if ((tempred = m_red + other.m_red) > MAXCOLOR)
00083       m_red = MAXCOLOR;
00084    else
00085       m_red = tempred;
00086    if ((tempgreen = m_green + other.m_green) > MAXCOLOR)
00087       m_green = MAXCOLOR;
00088    else
00089       m_green = tempgreen;
00090    if ((tempblue = m_blue + other.m_blue) > MAXCOLOR)
00091       m_blue = MAXCOLOR;
00092    else
00093       m_blue = tempblue;
00094    return *this;
00095 }
00096 
00097 inline RGBByte RGBByte::operator + ( const RGBByte &other )
00098 {
00099    m_red   += other.m_red;
00100    m_green += other.m_green;
00101    m_blue  += other.m_blue;
00102    return *this;
00103 }
00104 
00105 inline RGBByte &RGBByte::operator -= ( const RGBByte &other )
00106 {
00107    m_red   -= other.m_red;
00108    m_green -= other.m_green;
00109    m_blue  -= other.m_blue;
00110    return *this;
00111 }
00112 
00113 inline RGBByte &RGBByte::operator *= ( const float factor )
00114 {
00115    m_red   = (UBYTE)(m_red   * factor + .5);
00116    m_green = (UBYTE)(m_green * factor + .5);
00117    m_blue  = (UBYTE)(m_blue  * factor + .5);
00118    return *this;
00119 }
00120 
00121 inline void GammaCorrect( UBYTE *color, float power)
00122 {
00123    if (power == 1)
00124       return;
00125    *color = fast_round(MIN(255.0f, MAXCOLOR * (float)pow((float)*color/MAXCOLOR, 1.f/power )));
00126 }
00127 
00128 inline RGBByte RGBByte::GammaCorrect(float power)
00129 {
00130    if (power == 1)
00131       return *this;
00132    return RGBByte(
00133     fast_round(MIN(255.0f, MAXCOLOR * (float)pow((float)m_red/MAXCOLOR, 1.f/power ))),
00134     fast_round(MIN(255.0f, MAXCOLOR * (float)pow((float)m_green/MAXCOLOR, 1.f/power ))),
00135     fast_round(MIN(255.0f, MAXCOLOR * (float)pow((float)m_blue/MAXCOLOR, 1.f/power ))));
00136 }
00137 
00138 //******************************************************************************
00139 //** RGBAByte
00140 //******************************************************************************
00141 class RGBAByte {
00142 public:
00143    RGBByte m_color;
00144    UBYTE m_alpha;
00145 
00146    RGBAByte() { m_color.Set(0); m_alpha = MAXCOLOR; }
00147    RGBAByte( UBYTE pred, UBYTE pgreen, UBYTE pblue ) { m_color.Set(pred, pgreen, pblue); m_alpha = MAXCOLOR; }
00148    RGBAByte( UBYTE pred, UBYTE pgreen, UBYTE pblue, UBYTE palpha ) { m_color.Set(pred, pgreen, pblue); m_alpha = palpha; }
00149    RGBAByte( COLORREF c ) : m_color(c) { m_alpha = MAXCOLOR; }
00150    RGBAByte( const RGBAFloat &color );
00151 
00152 #if _MEMDEBUG
00153    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00154 #else
00155    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00156 #endif   
00157    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00158 
00159    RGBAByte &operator += ( const RGBAByte & );
00160    RGBAByte &operator -= ( const RGBAByte & );
00161    RGBAByte &operator *= ( const float );
00162    RGBAByte operator + ( const RGBAByte &other );
00163    operator COLORREF() { return (COLORREF)m_color; }
00164    RGBAByte &operator = ( const RGBAByte &other) { m_color = other.m_color; m_alpha = other.m_alpha; return *this; }
00165    RGBAByte &operator /= ( float scale )              { return (*this *= (1/scale)); }
00166    
00167    RGBFloat GetFactoredRGBFloat() const;
00168    RGBFloat GetNormalizedRGBFloat() const;
00169    RGBAFloat GetFactoredRGBAFloat() const;
00170    RGBAFloat GetNormalizedRGBAFloat() const;
00171    
00172    UBYTE Red()   const { return m_color.m_red; }
00173    UBYTE Green() const { return m_color.m_green; }
00174    UBYTE Blue()  const { return m_color.m_blue; }
00175    UBYTE Alpha() const { return m_alpha; }
00176    void Set( UBYTE pred, UBYTE pgreen, UBYTE pblue, UBYTE alpha ) { m_color.Set(pred, pgreen, pblue); m_alpha = alpha; }
00177    void SetRed( UBYTE red ) { m_color.SetRed(red); }
00178    void SetGreen( UBYTE green ) { m_color.SetGreen(green); }
00179    void SetBlue( UBYTE blue ) { m_color.SetBlue(blue); }
00180    void SetAlpha( UBYTE alpha ) { m_alpha = alpha; }
00181    RGBAByte GammaCorrect(float power) { 
00182       RGBAByte value; 
00183       value.m_color = m_color.GammaCorrect(power);
00184       value.m_alpha = m_alpha;
00185       return value;
00186    }
00187 
00188    inline RGBFloat GetRGBFloat() const;
00189    inline RGBAFloat GetRGBAFloat() const;
00190    float GetOpacity() const;
00191    inline void Set( const RGBFloat & );
00192    inline void Set( const RGBAFloat & );
00193    void SetOpacity( const float value );
00194    
00195    float GetLuminance() { return m_color.GetLuminance(); }
00196 
00197    BOOL CheckOffBound( float lobound, float hibound ) { return FALSE; }; // YP : For HDR testing and debugging purpose
00198 };
00199 
00200 inline float RGBAByte::GetOpacity( void ) const
00201 {
00202    return (float)m_alpha/MAXCOLOR;
00203 }
00204 
00205 inline void RGBAByte::SetOpacity( const float opacity )
00206 {
00207    m_alpha = FLOATTOBYTE(opacity);
00208 }
00209 
00210 inline RGBAByte &RGBAByte::operator += ( const RGBAByte &other )
00211 {
00212    m_color.operator+=(other.m_color);
00213 
00214    int tempalpha;
00215    if ((tempalpha = m_alpha + other.m_alpha) > MAXCOLOR)
00216       m_alpha = MAXCOLOR;
00217    else
00218       m_alpha = tempalpha;
00219    return *this;
00220 }
00221 
00222 inline RGBAByte RGBAByte::operator + ( const RGBAByte &other )
00223 {
00224    m_color += other.m_color;
00225    m_alpha += other.m_alpha;
00226    return RGBAByte(*this);
00227 }
00228 
00229 inline RGBAByte &RGBAByte::operator -= ( const RGBAByte &other )
00230 {
00231    m_color -= other.m_color;
00232    m_alpha -= other.m_alpha;
00233    return *this;
00234 }
00235 
00236 inline RGBAByte &RGBAByte::operator *= ( const float factor )
00237 {
00238    m_color*=factor;
00239    m_alpha = (UBYTE)(m_alpha * factor + .5);
00240    return *this;
00241 }
00242 
00243 //******************************************************************************
00244 //** YAByte
00245 //******************************************************************************
00246 class YAFloat;
00247 class YAByte {
00248 public:
00249    UBYTE m_luminance;
00250    UBYTE m_alpha;
00251 
00252    YAByte() { m_luminance = 0; m_alpha = MAXCOLOR; }
00253    YAByte( const UBYTE luminance ) { m_luminance = luminance; m_alpha = MAXCOLOR; };
00254    YAByte( const UBYTE luminance, const UBYTE alpha ) { m_luminance = luminance; m_alpha = alpha; };
00255    YAByte( const float luminance ) { m_luminance = (UBYTE) (luminance*255.0f); m_alpha = MAXCOLOR; };
00256    YAByte( const float luminance, const float alpha ) { m_luminance = (UBYTE) (luminance*255.0f); m_alpha = (UBYTE) (alpha*255.0f); };
00257    // compute CIE Rec.709 luminance
00258    YAByte( UBYTE pred, UBYTE pgreen, UBYTE pblue ) { m_luminance = (UINT) (pred * 0.2125f + pgreen * 0.7154f + pblue * 0.0721f); m_alpha = MAXCOLOR; }
00259    YAByte( UBYTE pred, UBYTE pgreen, UBYTE pblue, UBYTE palpha ) { m_luminance = (UINT) (pred * 0.2125f + pgreen * 0.7154f + pblue * 0.0721f); m_alpha = palpha; }
00260 
00261 #if _MEMDEBUG
00262    void             *operator new( size_t size, char *file, const int line ) { return ALLOCBITMAP( size, file, line ); }
00263 #else
00264    void             *operator new( size_t size ) { return AllocBitmap( size ); }
00265 #endif   
00266    void              operator delete( void *ptr ) { FreeBitmap( ptr ); }
00267 
00268    YAByte &operator += ( const YAByte & );
00269    YAByte &operator -= ( const YAByte & );
00270    YAByte &operator *= ( const float );
00271    YAByte operator + ( const YAByte &other );
00272    operator UBYTE() { return m_luminance; }
00273    YAByte &operator = ( const YAByte &other) { m_luminance = other.m_luminance; m_alpha = other.m_alpha; return *this; }
00274    YAByte &operator /= ( float scale ) { return (*this *= (1/scale)); }
00275    
00276    float GetFactoredFloat() const { return m_luminance; };
00277    float GetNormalizedFloat() const { return (float) m_luminance/MAXCOLOR; };
00278    YAFloat GetFactoredRGBAFloat() const;
00279    YAFloat GetNormalizedRGBAFloat() const;
00280    
00281    UBYTE Luminance()   const { return m_luminance; }
00282    UBYTE Alpha() const { return m_alpha; }
00283    void Set( UBYTE luminance, UBYTE alpha ) { m_luminance = luminance; m_alpha = alpha; }
00284    void SetLuminance( UBYTE luminance ) { m_luminance = luminance; }
00285    void SetLuminance( float luminance ) { m_luminance = (UBYTE) (luminance*MAXCOLOR); }
00286    void SetAlpha( UBYTE alpha ) { m_alpha = alpha; }
00287    YAByte GammaCorrect(float power) { 
00288       if (power == 1)
00289          return *this;
00290       YAByte value; 
00291       value.m_luminance = fast_round(MIN(255.0f, MAXCOLOR * (float)pow((float)m_luminance/MAXCOLOR, 1.f/power )));
00292       value.m_alpha = m_alpha;
00293       return value;
00294    }
00295 
00296    float GetFloat() const { return (float) m_luminance/MAXCOLOR; };
00297    YAFloat GetYAFloat() const;
00298    float GetOpacity() const { return (float) m_alpha/MAXCOLOR; };
00299    void SetOpacity( const float value ) { m_alpha = FLOATTOBYTE(value); };
00300    float GetLuminance() { return (float) m_luminance / MAXCOLOR; }
00301 
00302    BOOL CheckOffBound( float lobound, float hibound ) { return FALSE; }; // YP : For HDR testing and debugging purpose
00303 };
00304 
00305 inline YAByte &YAByte::operator += ( const YAByte &other )
00306 {
00307    int temp;
00308    if ((temp = m_luminance + other.m_luminance) > MAXCOLOR)
00309       m_luminance = MAXCOLOR;
00310    else
00311       m_luminance = temp;
00312    if ((temp = m_alpha + other.m_alpha) > MAXCOLOR)
00313       m_alpha = MAXCOLOR;
00314    else
00315       m_alpha = temp;
00316    return *this;
00317 }
00318 
00319 inline YAByte YAByte::operator + ( const YAByte &other )
00320 {
00321    m_luminance += other.m_luminance;
00322    m_alpha += other.m_alpha;
00323    return YAByte(*this);
00324 }
00325 
00326 inline YAByte &YAByte::operator -= ( const YAByte &other )
00327 {
00328    m_luminance -= other.m_luminance;
00329    m_alpha -= other.m_alpha;
00330    return *this;
00331 }
00332 
00333 inline YAByte &YAByte::operator *= ( const float factor )
00334 {
00335    m_luminance = (UBYTE)(m_luminance * factor + .5);
00336    m_alpha = (UBYTE)(m_alpha * factor + .5);
00337    return *this;
00338 }
00339 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Ge