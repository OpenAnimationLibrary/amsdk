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

# Vector4.h

[Go to the documentation of this file.](Vector4_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/24/2002  \HRandy95\Include\Vector4.h
00002 
00003 #define __VECTOR4_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #ifndef __EXPORTS_H
00009 #include "Exports.h"
00010 #endif
00011 
00012 #ifdef _SIMD
00013 #include "smlmath.h"
00014 #endif
00015 
00016 class Matrix44;
00017 
00018 class Vector4 
00019 {
00020 protected:
00021    union {
00022 #ifdef _SIMD
00023       struct { SMLVec4f m_smlvec4f; };
00024 #endif
00025       struct { float n[4]; };
00026    };
00027 
00028 public:
00029    Vector4( void ) {}
00030    Vector4( float x, float y, float z, float w );
00031    Vector4( float fill );
00032    Vector4( const Vector4 &v );
00033    Vector4( const Vector &other3 );
00034    
00035    friend class Matrix44;
00036 
00037    float operator[]( int i ) const;
00038    float &operator[]( int i );
00039    void Set( float x, float y, float z, float w );
00040    void Set( float fill )
00041    {
00042       n[0] = n[1] = n[2] = n[3] = fill;
00043    }
00044    Vector4 & operator = ( const Vector4 &v );
00045    Vector4 & operator /= ( float scalar );
00046    Vector4 & operator -= ( const Vector4 &other );
00047    Vector4 & operator += ( const Vector4 &other );
00048    Vector4 & operator *= ( float scale );
00049    int operator == ( const Vector4 &a ) const;
00050    int operator != ( const Vector4 &a ) const { return !(*this == a); }   
00051 
00052    Vector4 operator + ( const Vector4 &a ) const { return Vector4(*this) += a; }
00053    Vector4 operator - ( const Vector4 &a ) const { return Vector4(*this) -= a; }
00054 
00055    float operator | ( const Vector4 &b ) const;   // Dot Product
00056    float operator | ( const Vector &b ) const;   // Dot Product
00057    Vector4 operator * ( const Vector4 &b ) const // Member by member multiply
00058    {
00059       Vector4 result;               // GOOD CANDIDATE FOR SIMD, NOT IN SML
00060       result[0] = n[0] * b[0];
00061       result[1] = n[1] * b[1];
00062       result[2] = n[2] * b[2];
00063       result[3] = n[3] * b[3];
00064       return result;
00065    }
00066    Vector4 operator * ( float scalar ) const 
00067    {
00068       return Vector4(*this) *= scalar;
00069    }
00070    friend MATRIXEXPORT Vector4 operator * ( float scalar, const Vector4 &v )
00071    {
00072       return v * scalar;
00073    }
00074    friend void Swap( Vector4 &a, Vector4 &b )
00075    {
00076       Vector4 temp( a );
00077       a = b;
00078       b = temp;
00079    }
00080 };
00081 
00082 #ifdef _SIMD
00083 
00084 inline Vector4::Vector4( float x, float y, float z, float w ) : m_smlvec4f( x, y, z, w )
00085 {
00086 }
00087 
00088 inline Vector4::Vector4( float f ) : m_smlvec4f( f, f, f, f )
00089 {
00090 }
00091 
00092 inline Vector4::Vector4( const Vector4 &v ) : m_smlvec4f( v.m_smlvec4f )
00093 {
00094 }
00095 
00096 inline Vector4::Vector4( const Vector &other3 ) : m_smlvec4f( other3[0],other3[1],other3[2],1.0f )
00097 {
00098 }
00099 
00100 inline float Vector4::operator[]( int i ) const
00101 {
00102    return m_smlvec4f.data()[i];
00103 }
00104 
00105 inline float &Vector4::operator[]( int i )
00106 {
00107    return m_smlvec4f.data()[i];
00108 }
00109 
00110 inline void Vector4::Set( float x, float y, float z, float w )
00111 {
00112    m_smlvec4f.Set( x, y, z, w );
00113 }
00114 
00115 inline Vector4 & Vector4::operator = ( const Vector4 &v )
00116 {
00117    m_smlvec4f = v.m_smlvec4f; return *this;
00118 }
00119 
00120 inline Vector4 & Vector4::operator /= ( float scalar )
00121 {
00122    m_smlvec4f /= scalar; return *this;
00123 }
00124 
00125 inline Vector4 & Vector4::operator -= ( const Vector4 &other )
00126 {
00127    m_smlvec4f -= other.m_smlvec4f; return *this;
00128 }
00129 
00130 inline Vector4 & Vector4::operator += ( const Vector4 &other )
00131 {
00132    m_smlvec4f += other.m_smlvec4f;
00133    return *this;
00134 }
00135 
00136 inline Vector4 & Vector4::operator *= ( float scale )
00137 {
00138    m_smlvec4f *= scale;
00139    return *this;
00140 }
00141 
00142 inline int Vector4::operator == ( const Vector4 &a ) const
00143 {
00144    return m_smlvec4f == a.m_smlvec4f;
00145 }
00146 
00147 inline float Vector4::operator | ( const Vector4 &b ) const   // Dot Product
00148 {
00149    return m_smlvec4f.Dot( b.m_smlvec4f );
00150 }
00151 
00152 #else // NOT SIMD
00153 
00154 inline Vector4::Vector4( float x, float y, float z, float w )
00155 {
00156    Set(x,y,z,w);
00157 }
00158 
00159 inline Vector4::Vector4( float fill )
00160 {
00161    Set(fill);
00162 }
00163 
00164 inline Vector4::Vector4( const Vector4 &other )
00165 {
00166    *this = other;
00167 }
00168 
00169 inline Vector4::Vector4( const Vector &other3 )
00170 {
00171    n[0] = other3[0];
00172    n[1] = other3[1];
00173    n[2] = other3[2];
00174    n[3] = 1.0f;
00175 }
00176 
00177 inline float Vector4::operator[]( int i ) const
00178 {
00179    return n[i];
00180 }
00181 
00182 inline float &Vector4::operator[]( int i )
00183 {
00184    return n[i];
00185 }
00186 
00187 inline void Vector4::Set( float x, float y, float z, float w )
00188 {
00189     n[0] = x;
00190     n[1] = y;
00191     n[2] = z;
00192     n[3] = w;
00193 }
00194 
00195 inline Vector4 & Vector4::operator = ( const Vector4 &other )
00196 {
00197    n[0] = other[0];
00198    n[1] = other[1];
00199    n[2] = other[2];
00200    n[3] = other[3];
00201    return *this;
00202 }
00203 
00204 inline Vector4 & Vector4::operator /= ( float scalar )
00205 {
00206    n[0] /= scalar;
00207    n[1] /= scalar;
00208    n[2] /= scalar;
00209    n[3] /= scalar;
00210    return *this;
00211 }
00212 
00213 inline Vector4 & Vector4::operator -= ( const Vector4 &other )
00214 {
00215    n[0] -= other[0];
00216    n[1] -= other[1];
00217    n[2] -= other[2];
00218    n[3] -= other[3];
00219    return *this;
00220 }
00221 
00222 inline Vector4 & Vector4::operator += ( const Vector4 &other )
00223 {
00224    n[0] += other[0];
00225    n[1] += other[1];
00226    n[2] += other[2];
00227    n[3] += other[3];
00228    return *this;
00229 }
00230 
00231 inline Vector4 & Vector4::operator *= ( float scale )
00232 {
00233    n[0]*=scale;
00234    n[1]*=scale;
00235    n[2]*=scale;
00236    n[3]*=scale;
00237    return *this;
00238 }
00239 
00240 inline int Vector4::operator == ( const Vector4 &a ) const
00241 {
00242    return n[0]==a[0] && n[1]==a[1] && n[2]==a[2] && n[3]==a[3];
00243 }
00244 
00245 inline float Vector4::operator | ( const Vector4 &b ) const   // Dot Product
00246 {
00247    return n[0]*b[0] + n[1]*b[1] + n[2]*b[2] + n[3]*b[3];
00248 }
00249 
00250 inline float Vector4::operator | ( const Vector &b ) const   // Dot Product
00251 {
00252    return n[0]*b[0] + n[1]*b[1] + n[2]*b[2] + n[3];
00253 }
00254 
00255 #endif // NOT SIMD
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
