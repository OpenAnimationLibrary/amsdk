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

# Matrix33.h

[Go to the documentation of this file.](Matrix33_8h.md)

<div class="fragment">

``` fragment
00001 // BC  10/14/2004  \BobL115\Include\Matrix33.h
00002 
00003 #define __MATRIX33_H
00004 
00005 #ifndef __VECTOR2_H
00006 #include "Vector2.h"
00007 #endif
00008 #ifndef __EXPORTS_H
00009 #include "Exports.h"
00010 #endif
00011 #ifndef __FILECONS_H
00012 #include "FileCons.h"
00013 #endif
00014 
00015 #ifdef _SIMD
00016 #include "smlmath.h"
00017 #endif
00018 
00019 class Quaternion;
00020 class Matrix44;
00021 
00022 class MATRIXEXPORT Matrix33 
00023 {
00024 protected:
00025 #ifdef _SIMD
00026    union {
00027       struct { SMLMatrix3f m_smlmatrix3f; };
00028       struct { Vector v[3]; };
00029    };
00030 #else
00031    Vector v[3];
00032 #endif
00033 
00034 public:
00035    Matrix33() {}
00036    Matrix33( const Matrix33 &other );
00037    Matrix33( const Quaternion &q );
00038    Matrix33( const Vector &v0, const Vector &v1, const Vector &v2 )
00039    {
00040       v[0] = v0;
00041       v[1] = v1;
00042       v[2] = v2;
00043    }
00044    Matrix33( float fill )
00045    {
00046       Set( fill );
00047    }
00048 
00049    Matrix33 &operator = ( const Matrix33 &other );
00050    Matrix33 &operator *= ( const Matrix33 &other ) { return (*this = *this * other); }
00051    const Vector &operator[]( int row ) const { return v[row]; }
00052    Vector &operator[]( int row ) { return v[row]; }
00053    void SetIdentity();
00054    Matrix33 Transpose() const;
00055    void TransposeSelf();
00056    Matrix33 Inverse() const;
00057    Vector GetXAxis() const { return Vector( v[0][0], v[1][0], v[2][0] ); }
00058    Vector GetYAxis() const { return Vector( v[0][1], v[1][1], v[2][1] ); }
00059    Vector GetZAxis() const { return Vector( v[0][2], v[1][2], v[2][2] ); }
00060 #ifdef _SIMD
00061    SMLMatrix3f &GetSMLMatrix3f() { return m_smlmatrix3f; }
00062 #endif
00063 
00064    Matrix33 operator * ( const Matrix33 &b ) const;
00065    Vector operator * ( const Vector &v ) const;
00066    friend MATRIXEXPORT Vector2 operator * ( const Matrix33 &m, const Vector2 &v );
00067    friend MATRIXEXPORT Matrix33 Identity33( void );
00068    void Set( float fill )
00069    {
00070       v[0].Set( fill );
00071       v[1].Set( fill );
00072       v[2].Set( fill );
00073    }
00074    void SetTranslate( const Vector2 &t )
00075    {
00076       v[0][3] = t.x;
00077       v[1][3] = t.y;
00078       v[2][3] = 1.0f;
00079    }
00080    void MakeOrthogonal()
00081    {
00082       Matrix33 a = Transpose();  // move the column vectors to the rows
00083       Matrix33 b;
00084       
00085       b[0] = a[0];
00086       b[0].Normalize();
00087       b[1] = a[2] ^ a[0];
00088       b[1].Normalize();
00089       b[2] = b[0] ^ b[1];
00090 
00091       b[0] = a[0];
00092       b[1] *= a[1].Norm();
00093       b[2] *= a[2].Norm();
00094       
00095       *this = b.Transpose();
00096    }
00097 
00098    friend MATRIXEXPORT Matrix33 RotateVRadians33( float angle, const Vector &axis );
00099    friend MATRIXEXPORT Matrix33 XYRotateRadians33( float xangle, float yangle );
00100    friend MATRIXEXPORT Matrix33 YXRotateRadians33( float yangle, float xangle );
00101    friend MATRIXEXPORT Matrix33 ZXRotateRadians33( float zangle, float xangle );
00102    friend MATRIXEXPORT Matrix33 YXZRotateRadians33( float yangle, float xangle, float zangle );
00103    friend MATRIXEXPORT Matrix33 ZXZRotateRadians33( float zangl1, float xangle, float zangl2 );
00104    friend /* inline */ Matrix33 XRotate33( float angle );
00105    friend /* inline */ Matrix33 YRotate33( float angle );
00106    friend /* inline */ Matrix33 ZRotate33( float angle );
00107    friend /* inline */ Matrix33 YXRotate33( float yangle, float xangle );
00108    friend /* inline */ Matrix33 ZXRotate33( float zangle, float xangle );
00109    friend /* inline */ Matrix33 YXZRotate33( float yangle, float xangle, float zangle );
00110    friend /* inline */ Matrix33 ZXZRotate33( float zangl1, float xangle, float zangl2 );
00111    friend /* inline */ Matrix33 RotateV33( float angle, const Vector &axis );
00112    friend MATRIXEXPORT Matrix33 Rotate2V33( const Vector &from, const Vector &to );
00113    friend /* inline */ Matrix33 XRotateRadians33( float anglerad );
00114    friend /* inline */ Matrix33 YRotateRadians33( float anglerad );
00115    friend /* inline */ Matrix33 ZRotateRadians33( float anglerad );
00116    friend /* inline */ Matrix33 VectorsToStandard33( const Vector &becomezdir, const Vector &becomeydir );
00117    
00118 };
00119 
00120 inline Matrix33 XRotate33( float angle )                                { return XRotateRadians33( angle / RADIANS ); }
00121 inline Matrix33 YRotate33( float angle )                                { return YRotateRadians33( angle / RADIANS ); }
00122 inline Matrix33 ZRotate33( float angle )                                { return ZRotateRadians33( angle / RADIANS ); }
00123 inline Matrix33 YXRotate33( float yangle, float xangle )                { return YXRotateRadians33( yangle/RADIANS, xangle/RADIANS ); }
00124 inline Matrix33 ZXRotate33( float zangle, float xangle )                { return ZXRotateRadians33( zangle/RADIANS, xangle/RADIANS ); }
00125 inline Matrix33 YXZRotate33( float yangle, float xangle, float zangle ) { return YXZRotateRadians33( yangle/RADIANS, xangle/RADIANS, zangle/RADIANS ); }
00126 inline Matrix33 ZXZRotate33( float zangl1, float xangle, float zangl2 ) { return ZXZRotateRadians33( zangl1/RADIANS, xangle/RADIANS, zangl2/RADIANS ); }
00127 inline Matrix33 RotateV33( float angle, const Vector &axis )            { return RotateVRadians33( angle / RADIANS, axis ); }
00128 
00129 inline Matrix33 XRotateRadians33( float anglerad )
00130 {
00131     float ca = (float)cos( anglerad ),
00132         sa = (float)sin( anglerad );
00133     return Matrix33( Vector( 1.f, 0.f, 0.f ),
00134                     Vector( 0.f,  ca, -sa ),
00135                     Vector( 0.f,  sa,  ca ));
00136 }
00137 
00138 inline Matrix33 YRotateRadians33( float anglerad )
00139 {
00140     float ca = (float)cos( anglerad ),
00141         sa = (float)sin( anglerad );
00142     return Matrix33( Vector(  ca, 0.f,  sa ),
00143                     Vector( 0.f, 1.f, 0.f ),
00144                     Vector( -sa, 0.f,  ca ));
00145 }
00146 
00147 inline Matrix33 ZRotateRadians33( float anglerad )
00148 {
00149     float ca = (float)cos( anglerad ),
00150         sa = (float)sin( anglerad );
00151     return Matrix33( Vector(  ca, -sa, 0.f ),
00152                     Vector(  sa,  ca, 0.f ),
00153                     Vector( 0.f, 0.f, 1.f ));
00154 }
00155 inline Matrix33 VectorsToStandard33( const Vector &becomezdir, const Vector &becomeydir )
00156 {
00157     Matrix33 vectostandard = Rotate2V33( becomezdir, Vector( 0.0f, 0.0f, 1.0f ));
00158     Vector   rollvec = vectostandard * becomeydir;
00159     float    roll = (float)atan2( -rollvec.x, rollvec.y );
00160     if ( roll )
00161         vectostandard = ZRotateRadians33( -roll ) * vectostandard;
00162     return vectostandard;
00163 }
00164 
00165 inline Vector &Vector::operator *= ( const Matrix33 &m )
00166 {
00167    *this =  m * (*this);
00168    return *this;
00169 }
00170 
00171 #ifdef _SIMD
00172 
00173 inline Matrix33::Matrix33( const Matrix33 &other )
00174 {
00175    m_smlmatrix3f = other.m_smlmatrix3f;
00176 }
00177 
00178 inline Matrix33 &Matrix33::operator = ( const Matrix33 &other )
00179 {
00180    m_smlmatrix3f = other.m_smlmatrix3f;
00181    return *this;
00182 }
00183 
00184 inline void Matrix33::SetIdentity()
00185 {
00186    m_smlmatrix3f.Identity();
00187 }
00188 
00189 inline Matrix33 Matrix33::Transpose() const
00190 {
00191    Matrix33 temp( *this );
00192    temp.m_smlmatrix3f.Transpose();
00193    return temp;
00194 }
00195 
00196 inline void Matrix33::TransposeSelf()
00197 {
00198    m_smlmatrix3f.Transpose();
00199 }
00200 
00201 inline Matrix33 Matrix33::operator * ( const Matrix33 &b ) const
00202 {
00203    Matrix33 result;
00204    result.m_smlmatrix3f.Multiply(m_smlmatrix3f, b.m_smlmatrix3f);
00205    return result;
00206 }
00207 
00208 inline Vector Matrix33::operator * ( const Vector &v ) const
00209 {
00210    Vector result;
00211    m_smlmatrix3f.TransformPoint( v.m_smlvec3f, result.m_smlvec3f );
00212    return result;
00213 }
00214 
00215 inline MATRIXEXPORT Matrix33 Identity33( void )
00216 {
00217    Matrix33 result;
00218    result.m_smlmatrix3f.Identity();
00219    return result;
00220 }
00221 
00222 #else  // not SIMD
00223 
00224 inline Matrix33::Matrix33( const Matrix33 &m )
00225 {
00226    *this = m;
00227 }
00228 
00229 inline Matrix33 &Matrix33::operator = ( const Matrix33 &m )
00230 {
00231    v[0] = m.v[0];
00232    v[1] = m.v[1];
00233    v[2] = m.v[2];
00234    return *this;
00235 }
00236 
00237 inline void Matrix33::SetIdentity()
00238 {
00239    v[0].Set(1.0f, 0.0f, 0.0f);
00240    v[1].Set(0.0f, 1.0f, 0.0f);
00241    v[2].Set(0.0f, 0.0f, 1.0f);
00242 }
00243 
00244 inline Matrix33 Matrix33::Transpose() const
00245 {
00246    return Matrix33( Vector( v[0][0], v[1][0], v[2][0] ),
00247                     Vector( v[0][1], v[1][1], v[2][1] ),
00248                     Vector( v[0][2], v[1][2], v[2][2] ));
00249 }
00250 
00251 inline void Matrix33::TransposeSelf()
00252 {
00253    *this = Transpose();
00254 }
00255 
00256 inline Vector Matrix33::operator * ( const Vector &vec ) const
00257 {
00258    return Vector( v[0]|vec, v[1]|vec, v[2]|vec );
00259 }
00260 
00261 inline MATRIXEXPORT Matrix33 Identity33( void )
00262 {
00263    return Matrix33( Vector( 1.f, 0.f, 0.f ),
00264                     Vector( 0.f, 1.f, 0.f ),
00265                     Vector( 0.f, 0.f, 1.f ));
00266 }
00267 
00268 #endif // not SIMD
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
