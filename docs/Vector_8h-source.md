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

# Vector.h

[Go to the documentation of this file.](Vector_8h.md)

<div class="fragment">

``` fragment
00001 // BC  2/19/2004  \Bob110\Include\Vector.h
00002 
00003 #define __VECTOR_H
00004 
00005 #ifndef __EXPORTS_H
00006 #include "Exports.h"
00007 #endif
00008 #include <math.h>
00009 
00010 #ifdef _SIMD
00011 #include "smlmath.h"
00012 #endif
00013 
00014 #define V_PI 3.1415926535898
00015 
00016 class Matrix34;
00017 class Matrix33;
00018 class Vector2;
00019 class Quaternion;
00020 
00021 class MATRIXEXPORT Vector {
00022 public:
00023    union {
00024 #ifdef _SIMD
00025       struct { SMLVec3f m_smlvec3f; };
00026 #endif      
00027       struct { float x, y, z; };
00028    };
00029    
00030    Vector( void ) {}
00031    Vector( float xi, float yi, float zi );
00032    Vector( const Vector &other );
00033    Vector( float f );
00034    Vector( const Vector2 &v2 );
00035    float operator[]( int i ) const;
00036    float &operator[]( int i );
00037 
00038    Vector & operator += ( const Vector &other );
00039    Vector & operator -= ( const Vector &other );
00040    Vector & operator /= ( const Vector &other )
00041    {
00042       x /= other.x;
00043       y /= other.y;
00044       z /= other.z;
00045       return *this;
00046    }
00047    Vector & operator *= ( const Vector &other )  // GOOD CANDIDATES FOR sse, NOT IN sml
00048    {
00049       x *= other.x;
00050       y *= other.y;
00051       z *= other.z;
00052       return *this; 
00053    }
00054 
00055    Vector & operator *= ( float scale );
00056    Vector & operator /= ( float scale );
00057    Vector & operator ^= ( const Vector &a ) { return (*this = Cross(a)); }
00058 
00059    Vector & operator *= ( const Matrix34 &m );
00060    Vector & operator *= ( const Matrix33 &m );
00061    Vector & operator *= ( const Quaternion &q );
00062 
00063    Vector & Negate( void );
00064    void Set( float xi, float yi, float zi );
00065    void Set( float f );
00066    void Swap( Vector &a )           { Vector temp(*this); *this = a; a = temp; }
00067 
00068    int operator == ( const Vector &a ) const;
00069    int operator != ( const Vector &a ) const { return !(*this == a); }   
00070    
00071    Vector operator + ( const Vector &a )   const { return Vector(*this) += a; }
00072    Vector operator - ( const Vector &a )   const { return Vector(*this) -= a; }
00073    Vector operator - ( void )              const { return Vector(*this).Negate(); } // unary minus
00074    Vector operator * ( const Vector &a )   const { return Vector(*this) *= a; }
00075    Vector operator * ( float s )           const { return Vector(*this) *= s; }
00076    Vector operator / ( float s )           const { return Vector(*this) /= s; }
00077    Vector operator / ( const Vector &a )   const { return Vector(*this) /= a; }
00078 
00079    float Norm( void ) const;
00080    Vector Normalized( void )    const { return Vector(*this).Normalize(); }
00081    float NormalizeLength( void )
00082    {
00083       float length = Norm();
00084       if (length)
00085          operator /= (length);
00086       return length;
00087    }
00088    Vector & Normalize( void );
00089    float Dot( const Vector &a ) const;
00090    float Square( void )       const { return Dot(*this); }
00091    Vector Absolute( void )    const { return Vector( (float)fabs( x ), (float)fabs( y ), (float)fabs( z )); }
00092    Vector Reciprocal( void )  const { return Vector( 1.0f/x, 1.0f/y, 1.0f/z ); }
00093    void CrossSelf( const Vector &a )     { *this = Cross( a ); }
00094    Vector Cross( const Vector &v ) const
00095    {
00096       return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);  // SML is just inline anyway, save = operator
00097    }
00098    Vector Hundredized()        const { return Vector(*this).Hundredize(); } 
00099    Vector & Hundredize( void )
00100    {
00101       float length = Norm();
00102       if (length)
00103          *this *= (100/length);
00104       return *this;
00105    }
00106 
00107    float operator | ( const Vector &a ) const { return Dot(a); } // same as Dot
00108    Vector operator ^ ( const Vector &a ) const { return Cross(a); } // same as Cross
00109 
00110    friend Vector operator * ( const float s, const Vector &a )  { return a * s; }
00111    friend float Dot( const Vector &a, const Vector &b )         { return a.Dot(b); }
00112    friend Vector Cross( const Vector &a, const Vector &b )      { return a.Cross(b); }
00113    friend void Swap( Vector &a, Vector &b )                     { a.Swap(b); }
00114    friend BOOL IsBackward( const Vector &a, const Vector &b, const Vector &c )
00115    {
00116       return (b.x-a.x) * (c.y-a.y) - (b.y-a.y) * (c.x-a.x) < 0;
00117    }
00118 
00119    void Min(float min) { if (x<min) x=min; if (y<min) y=min; if (z<min) z=min; }
00120    void Max(float max) { if (x>max) x=max; if (y>max) y=max; if (z>max) z=max; }
00121 };
00122 
00123 inline float DistancePointToPlane( const Vector &point, const Vector &pointonplane, const Vector &normal )
00124 {
00125    Vector delta = point;
00126    delta -= pointonplane;
00127    return Dot( delta, normal );
00128 }
00129 
00130 inline void PushMinMax( const Vector &p, Vector &minv, Vector &maxv )
00131 {
00132    if ( p.x > maxv.x )
00133       maxv.x = p.x;
00134    if ( p.x < minv.x )
00135       minv.x = p.x;
00136    if ( p.y > maxv.y )
00137       maxv.y = p.y;
00138    if ( p.y < minv.y )
00139       minv.y = p.y;
00140    if ( p.z > maxv.z )
00141       maxv.z = p.z;
00142    if ( p.z < minv.z )
00143       minv.z = p.z;
00144 }
00145 
00146 #ifdef _SIMD
00147 
00148 inline Vector::Vector( float xi, float yi, float zi ) :  m_smlvec3f(xi, yi, zi)
00149 {
00150 }
00151 
00152 inline Vector::Vector( const Vector &other ) : m_smlvec3f( other.m_smlvec3f )
00153 {
00154 }
00155 
00156 inline Vector::Vector( float f ) : m_smlvec3f( f, f, f )
00157 {
00158 }
00159 
00160 inline float Vector::operator[]( int i ) const
00161 {
00162    return m_smlvec3f[i];
00163 }
00164 
00165 inline float &Vector::operator[]( int i )
00166 {
00167    return m_smlvec3f[i];
00168 }
00169 
00170 inline Vector & Vector::operator += ( const Vector &other )
00171 {
00172    m_smlvec3f += other.m_smlvec3f;
00173    return *this;
00174 }
00175 
00176 inline Vector & Vector::operator -= ( const Vector &other )
00177 {
00178    m_smlvec3f -= other.m_smlvec3f;
00179    return *this;
00180 }
00181 
00182 inline Vector & Vector::operator *= ( float scale )
00183 {
00184    m_smlvec3f *= scale;
00185    return *this;
00186 }
00187 
00188 inline Vector & Vector::operator /= ( float scale )
00189 {
00190    m_smlvec3f /= scale;
00191    return *this;
00192 }
00193 
00194 inline Vector & Vector::Negate( void )
00195 {
00196    m_smlvec3f.Negate();
00197    return *this;
00198 }
00199 
00200 inline void Vector::Set( float xi, float yi, float zi )
00201 {
00202    m_smlvec3f.Set(xi, yi, zi);
00203 }
00204 
00205 inline void Vector::Set( float f )
00206 {
00207    m_smlvec3f.Set(f,f,f);
00208 }
00209 
00210 inline int Vector::operator == ( const Vector &a ) const
00211 {
00212    return m_smlvec3f == a.m_smlvec3f;
00213 }
00214 
00215 inline float Vector::Norm( void ) const
00216 {
00217    return m_smlvec3f.Length();
00218 } 
00219 
00220 inline Vector & Vector::Normalize( void )
00221 {
00222    m_smlvec3f.Normalize();
00223    return *this;
00224 }
00225 
00226 inline float Vector::Dot( const Vector &a ) const
00227 {
00228    return m_smlvec3f.Dot(a.m_smlvec3f);
00229 }
00230 
00231 #else  // not SIMD
00232 
00233 inline Vector::Vector( float xi, float yi, float zi )
00234 {
00235    Set(xi,yi,zi);
00236 }
00237 
00238 inline Vector::Vector( const Vector &other )
00239 {
00240    *this = other;
00241 }
00242 
00243 inline Vector::Vector( float fill )
00244 {
00245    Set(fill);
00246 }
00247 
00248 inline float Vector::operator[]( int i ) const
00249 {
00250    return (&x)[i];
00251 }
00252 
00253 inline float &Vector::operator[]( int i )
00254 {
00255    return (&x)[i];
00256 }
00257 
00258 inline Vector & Vector::operator += ( const Vector &other )
00259 {
00260    x += other.x;
00261    y += other.y;
00262    z += other.z;
00263    return *this; 
00264 }
00265 
00266 inline Vector & Vector::operator -= ( const Vector &other )
00267 {
00268    x -= other.x;
00269    y -= other.y;
00270    z -= other.z;
00271    return *this; 
00272 }
00273 
00274 inline Vector & Vector::operator *= ( float scale )
00275 {
00276    x *= scale;
00277    y *= scale;
00278    z *= scale;
00279    return *this;
00280 }
00281 
00282 inline Vector & Vector::operator /= ( float scale )
00283 {
00284    x /= scale;
00285    y /= scale;
00286    z /= scale;
00287    return *this;
00288 }
00289 
00290 inline Vector & Vector::Negate( void )
00291 {
00292    x = -x;
00293    y = -y;
00294    z = -z;
00295    return *this;
00296 }
00297 
00298 inline void Vector::Set( float xi, float yi, float zi )
00299 {
00300    x = xi;
00301    y = yi;
00302    z = zi;
00303 }
00304 
00305 inline void Vector::Set( float fill )
00306 {
00307    x = y = z = fill;
00308 }
00309 
00310 inline int Vector::operator == ( const Vector &a ) const
00311 {
00312    return (x == a.x) && (y == a.y) && (z == a.z);
00313 }
00314 
00315 inline float Vector::Norm( void ) const
00316 {
00317    return (float)sqrt(Square());
00318 }
00319 
00320 inline Vector & Vector::Normalize( void )
00321 {
00322 //   *this *= InverseSqrt( x*x + y*y + z*z );
00323    float length = Norm();
00324    if (length)
00325       *this /= length;
00326    return *this;
00327 }
00328 
00329 inline float Vector::Dot( const Vector &a ) const
00330 {
00331    return x * a.x + y * a.y + z * a.z;
00332 }
00333 
00334 #endif // not SIMD
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
