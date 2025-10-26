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

# Matrix34.h

[Go to the documentation of this file.](Matrix34_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/24/2003  \Bob110\Include\Matrix34.h
00002 
00003 #ifndef __MATRIX34_H
00004 #define __MATRIX34_H
00005 
00006 #ifndef __MATRIX44_H
00007 #include "Matrix44.h"
00008 #endif
00009 #ifndef __MATRIX33_H
00010 #include "Matrix33.h"
00011 #endif
00012 #ifndef __ROTATE_H
00013 #include "Rotate.h"
00014 #endif
00015 
00016 #ifdef _SIMD
00017 #include "smlmath.h"
00018 #include "smlMatrix34.h"
00019 #endif
00020 
00021 class MATRIXEXPORT Matrix34 {
00022 protected:
00023 #ifdef _SIMD
00024    union {
00025       struct { SMLMatrix34f m_smlmatrix34f; };
00026       struct { Vector4 v[3]; };
00027    };
00028 #else
00029    Vector4 v[3];
00030 #endif
00031 
00032 public:
00033    Matrix34( void ) { SetIdentity(FALSE); }
00034    Matrix34( const Vector4 &, const Vector4 &, const Vector4 & );
00035    Matrix34( const Matrix34 &m );
00036    Matrix34( float fillvalue );
00037    Matrix34( const RotateVector &rotate );
00038    Matrix34( const Quaternion & );
00039    Matrix34( const RotateEuler &re );
00040    Matrix34( const TSQ &tsq );
00041    
00042 #ifdef _SIMD
00043    const SMLMatrix34f &GetSMLMatrix34f() const { return m_smlmatrix34f; }
00044    void  SetIdentity(BOOL state) { m_smlmatrix34f.SetIdentity( state!=FALSE ); }
00045    void InitBottomRow() {
00046       m_smlmatrix34f.Set( 3,0,0 );
00047       m_smlmatrix34f.Set( 3,1,0 );
00048       m_smlmatrix34f.Set( 3,2,0 );
00049       m_smlmatrix34f.Set( 3,3,1 );
00050    }
00051 #else
00052    void  SetIdentity(BOOL state) {}
00053    void InitBottomRow() {}
00054 #endif
00055    Matrix34 &operator *= ( const Matrix34 &other ) { return (*this = *this * other); }
00056 
00057    const Vector4 &operator[]( int row ) const { return v[row]; }
00058    Vector4 &operator[]( int row ) { return v[row]; }
00059    void Set( const Vector4 &a, const Vector4 &b, const Vector4 &c );
00060    void SetIdentity()
00061    {
00062       v[0].Set(1.0f,0.0f,0.0f,0.0f);
00063       v[1].Set(0.0f,1.0f,0.0f,0.0f);
00064       v[2].Set(0.0f,0.0f,1.0f,0.0f);
00065       SetIdentity( TRUE );      
00066    }
00067    Matrix34 Transpose( void ) const;
00068    Matrix34 Inverse( void ) const;
00069    void SetTranslate( const Vector &t );
00070    Vector GetTranslate( void ) const;
00071    Matrix34 NoTranslate( void ) const;
00072    Matrix34 GetScaleMatrix( void ) const;
00073    Vector   GetScaleVector( void ) const;
00074    int operator == ( const Matrix34 &a ) const { return v[0]==a[0] && v[1]==a[1] && v[2]==a[2]; }
00075    int operator != ( const Matrix34 &a ) const { return !(*this == a); }   
00076    Vector GetXAxis() const { return Vector( v[0][0], v[1][0], v[2][0] ); }
00077    Vector GetYAxis() const { return Vector( v[0][1], v[1][1], v[2][1] ); }
00078    Vector GetZAxis() const { return Vector( v[0][2], v[1][2], v[2][2] ); }
00079    Matrix34 operator * ( const Matrix34 & ) const;
00080    Vector operator * ( const Vector & ) const;
00081 
00082    Matrix34 InvertRotateTranslate() const  // THE MATRIX MUST HAVE NO SCALE
00083    {
00084       Matrix34 rotate = Transpose();
00085       rotate.SetTranslate( rotate * -GetTranslate());
00086       return rotate;
00087    }
00088    friend /* inline */ Vector operator * ( const Vector &v, const Matrix34 &m );
00089    friend MATRIXEXPORT Matrix34 Identity34( void );
00090 
00091    // GL MATRIX CREATION FUNCTIONS
00092    friend MATRIXEXPORT Matrix34 Translatef( float x, float y, float z );
00093    friend MATRIXEXPORT Matrix34 TranslateV( const Vector &v );
00094    friend MATRIXEXPORT Matrix34 Scalef( float x, float y, float z );
00095    friend MATRIXEXPORT Matrix34 ScaleV( const Vector &v );
00096    friend MATRIXEXPORT Matrix34 RotateVRadians( float angle, const Vector &axis );
00097    friend MATRIXEXPORT Matrix34 Rotatef( float angle, float x, float y, float z );
00098    friend MATRIXEXPORT Matrix34 Rotate2V( const Vector &from, const Vector &to );
00099    friend MATRIXEXPORT Matrix34 XRotateRadians( float anglerad );
00100    friend MATRIXEXPORT Matrix34 YRotateRadians( float anglerad );
00101    friend MATRIXEXPORT Matrix34 ZRotateRadians( float anglerad );
00102    friend MATRIXEXPORT Matrix34 YXRotateRadians( float yangle, float xangle );
00103    friend MATRIXEXPORT Matrix34 YXZRotateRadians( float yangle, float xangle, float zangle );
00104    friend /* inline */ Matrix34 YXZRotate( float yangle, float xangle, float zangle );
00105    friend MATRIXEXPORT Matrix34 XZYRotate( float xangle, float zangle, float yangle );
00106    friend MATRIXEXPORT Matrix34 VectorsToStandard( const Vector &becomezdir, const Vector &becomeydir );
00107    friend MATRIXEXPORT Matrix34 StandardToVectors( const Vector &newzdir, const Vector &newydir );
00108 
00109    friend /* inline */ Matrix34 RotateV( float angle, const Vector &axis );
00110    friend /* inline */ Matrix34 XRotate( float angle );
00111    friend /* inline */ Matrix34 YRotate( float angle );
00112    friend /* inline */ Matrix34 ZRotate( float angle );
00113    
00114    // CONVERSION FUNCTIONS
00115    friend MATRIXEXPORT Matrix44 ToMatrix44( const Matrix33 &m );
00116    friend MATRIXEXPORT Matrix44 ToMatrix44( const Matrix34 &m );
00117    friend MATRIXEXPORT Matrix33 ToMatrix33( const Matrix34 &m );
00118    friend MATRIXEXPORT Matrix33 ToMatrix33( const Matrix44 &m );
00119    friend MATRIXEXPORT Matrix34 ToMatrix34( const Matrix44 &m );
00120    friend MATRIXEXPORT Matrix34 ToMatrix34( const Matrix33 &m );
00121 
00122    friend MATRIXEXPORT void MatrixTimesScale( Matrix34 &a, const Vector &s );
00123    friend MATRIXEXPORT void ScaleTimesMatrix( const Vector &s, Matrix34 &a );
00124    friend MATRIXEXPORT void TwoVectorsToAxisAngle( const Vector &from, const Vector &to, Vector &axis, float &radangle );
00125    friend MATRIXEXPORT void TransformVectorNoTranslate( const Matrix34 &matrix, Vector &p );
00126    friend /* inline */ Matrix34 CreateEulerMatrix( const Rotate &rotate );
00127    friend /* inline */ void TransformVector( const Matrix34 &matrix, Vector &p );
00128 };
00129 
00130 // inline friend functions
00131 inline Vector operator * ( const Vector &v, const Matrix34 &m )
00132 {
00133     return m * v;
00134 }
00135 inline Matrix34 YXZRotate( float yangle, float xangle, float zangle ) 
00136 {
00137    return YXZRotateRadians( yangle/RADIANS, xangle/RADIANS, zangle/RADIANS ); 
00138 }
00139 inline Matrix34 RotateV( float angle, const Vector &axis )
00140 {
00141    return RotateVRadians( angle / RADIANS, axis ); 
00142 }
00143 inline Matrix34 XRotate( float angle )
00144 {
00145    return XRotateRadians( angle / RADIANS ); 
00146 }
00147 inline Matrix34 YRotate( float angle )
00148 {
00149    return YRotateRadians( angle / RADIANS ); 
00150 }
00151 inline Matrix34 ZRotate( float angle )
00152 {
00153    return ZRotateRadians( angle / RADIANS ); 
00154 }
00155 inline Matrix34 CreateEulerMatrix( const Rotate &rotate )
00156 {
00157    return YXZRotate( -rotate.roll, -rotate.swivel, -rotate.tilt ).Transpose(); 
00158 }
00159 inline void TransformVector( const Matrix34 &matrix, Vector &p ) 
00160 {
00161    p = matrix * p; 
00162 }
00163 
00164 
00165 // regular inlined functions
00166 inline void Matrix34::Set( const Vector4 &v0, const Vector4 &v1, const Vector4 &v2 )
00167 {
00168    v[0] = v0;
00169    v[1] = v1;
00170    v[2] = v2;
00171    InitBottomRow();
00172    SetIdentity(FALSE);
00173 }
00174 
00175 inline Matrix34::Matrix34( const Vector4 &v0, const Vector4 &v1, const Vector4 &v2 )
00176 {
00177    Set( v0, v1, v2 );
00178 }
00179 
00180 inline Matrix34::Matrix34( float fillvalue )
00181 {
00182    v[0] = Vector4( fillvalue );
00183    v[1] = Vector4( fillvalue );
00184    v[2] = Vector4( fillvalue );
00185    SetIdentity( FALSE );
00186 }
00187 
00188 inline Matrix34::Matrix34( const RotateVector &rv )
00189 {
00190    float y = (float)atan2( rv.end.x, rv.end.z );
00191    float x = (float)atan2( -rv.end.y, (float)sqrt(rv.end.x*rv.end.x + rv.end.z*rv.end.z));
00192    if ( rv.roll )
00193       *this = YXZRotateRadians( y, x, rv.roll / RADIANS );
00194    else
00195       *this = YXRotateRadians( y, x );
00196    SetIdentity( FALSE );
00197 }
00198 
00199 inline Matrix34::Matrix34( const RotateEuler &re )
00200 {
00201    *this = YXZRotate( re.y, re.x, re.z );
00202    SetIdentity( FALSE );
00203 }
00204 
00205 inline Matrix34 Identity34( void )
00206 {
00207    static Matrix34 identity34(
00208                     Vector4( 1.f, 0.f, 0.f, 0.f ),
00209                     Vector4( 0.f, 1.f, 0.f, 0.f ),
00210                     Vector4( 0.f, 0.f, 1.f, 0.f ));
00211    identity34.SetIdentity( TRUE );
00212    identity34.InitBottomRow();
00213    return identity34;
00214 }                    
00215 
00216 inline void Matrix34::SetTranslate( const Vector &t )
00217 {
00218    v[0][3] = t.x;
00219    v[1][3] = t.y;
00220    v[2][3] = t.z;
00221    SetIdentity( FALSE );
00222 }
00223 
00224 inline Vector Matrix34::GetTranslate( void ) const
00225 {
00226    return Vector( v[0][3], v[1][3], v[2][3] );
00227 }
00228 
00229 inline Matrix34 Matrix34::NoTranslate( void ) const
00230 {
00231    return Matrix34( Vector4( v[0][0], v[0][1], v[0][2], 0.f ),
00232                     Vector4( v[1][0], v[1][1], v[1][2], 0.f ),
00233                     Vector4( v[2][0], v[2][1], v[2][2], 0.f ));
00234 }
00235 
00236 inline Matrix34 Matrix34::GetScaleMatrix( void ) const
00237 {
00238    return Matrix34((Quaternion(*this).Inverse())) * NoTranslate();
00239 }
00240 
00241 inline Vector Matrix34::GetScaleVector( void ) const
00242 {
00243    Matrix34 scalem = GetScaleMatrix();
00244    return Vector(scalem[0][0], scalem[1][1], scalem[2][2]);
00245 }
00246 
00247 inline Vector &Vector::operator *= ( const Matrix34 &m )
00248 {
00249    *this =  m * *this;
00250    return *this;
00251 }
00252 
00253 // ------------ CONVERSION TO AND FROM OTHER TYPES -------------------
00254 
00255 inline Matrix44 ToMatrix44( const Matrix34 &m )
00256 {
00257    return Matrix44( m[0],
00258                     m[1],
00259                     m[2],
00260            Vector4( 0.f, 0.f, 0.f, 1.f ));
00261 }
00262 
00263 inline Matrix44 ToMatrix44( const Matrix33 &m )
00264 {
00265    return Matrix44(
00266     Vector4( m[0][0], m[0][1], m[0][2], 0.f ),
00267     Vector4( m[1][0], m[1][1], m[1][2], 0.f ),
00268     Vector4( m[2][0], m[2][1], m[2][2], 0.f ),
00269     Vector4( 0.f,     0.f,     0.f,     1.f ));
00270 }
00271 
00272 inline Matrix33 ToMatrix33( const Matrix34 &m )
00273 {
00274    return Matrix33( Vector( m[0][0], m[0][1], m[0][2] ),
00275                     Vector( m[1][0], m[1][1], m[1][2] ),
00276                     Vector( m[2][0], m[2][1], m[2][2] ));
00277 }
00278 
00279 inline Matrix33 ToMatrix33( const Matrix44 &m )
00280 {
00281    return Matrix33( Vector( m[0][0], m[0][1], m[0][2] ),
00282                     Vector( m[1][0], m[1][1], m[1][2] ),
00283                     Vector( m[2][0], m[2][1], m[2][2] ));
00284 }
00285 
00286 inline Matrix34 ToMatrix34( const Matrix44 &m )
00287 {
00288    return Matrix34( m[0],
00289                     m[1],
00290                     m[2] );
00291 }
00292 
00293 inline Matrix34 ToMatrix34( const Matrix33 &m )
00294 {
00295    return Matrix34( Vector4( m[0][0], m[0][1], m[0][2], 0.f ),
00296                     Vector4( m[1][0], m[1][1], m[1][2], 0.f ),
00297                     Vector4( m[2][0], m[2][1], m[2][2], 0.f ));
00298 }
00299 
00300 inline Matrix34 VectorsToStandard( const Vector &becomezdir, const Vector &becomeydir )
00301 {
00302    Matrix34 vectostandard = Rotate2V( becomezdir, Vector( 0.0f, 0.0f, 1.0f ));
00303    Vector   rollvec = vectostandard * becomeydir;
00304    float    roll = (float)atan2( -rollvec.x, rollvec.y );
00305    if ( roll )
00306       vectostandard = ZRotateRadians( -roll ) * vectostandard;
00307    return vectostandard;  // may be faster to just compute like below, but the transpose
00308 }
00309 
00310 inline Matrix34 StandardToVectors( const Vector &newzdir, const Vector &newydir )
00311 {
00312    Vector xdir, ydir, zdir;
00313    ydir = newydir;
00314    ydir.Normalize();
00315    zdir = newzdir;
00316    zdir.Normalize();
00317    xdir = Cross( ydir, zdir );
00318    float xlength = xdir.Norm();
00319    if (xlength!=1.0f) {
00320       xdir /= xlength;
00321       ydir = Cross( zdir, xdir );
00322    }
00323    return Matrix34( Vector4(xdir[0], ydir[0], zdir[0], 0),
00324                     Vector4(xdir[0], ydir[0], zdir[0], 0),
00325                     Vector4(xdir[0], ydir[0], zdir[0], 0));
00326 }
00327 
00328 // -------------------- GL STYLE CREATION FUNCTIONS ----------------------
00329 
00330 inline Matrix34 Translatef( float x, float y, float z )
00331 {
00332    return Matrix34( Vector4( 1.f, 0.f, 0.f, x ),
00333                     Vector4( 0.f, 1.f, 0.f, y ),
00334                     Vector4( 0.f, 0.f, 1.f, z ));
00335 }
00336 
00337 inline Matrix34 TranslateV( const Vector &v )
00338 {
00339    return Translatef( v[0], v[1], v[2] );
00340 }
00341 
00342 inline Matrix34 Scalef( float x, float y, float z )
00343 {
00344    return Matrix34( Vector4(   x, 0.f, 0.f, 0.f ),
00345                     Vector4( 0.f,   y, 0.f, 0.f ),
00346                     Vector4( 0.f, 0.f,   z, 0.f ));
00347 }
00348 
00349 inline Matrix34 ScaleV( const Vector &v )
00350 {
00351    return Scalef( v[0], v[1], v[2] );
00352 }
00353 
00354 inline Matrix34 Rotatef( float angle, float x, float y, float z )
00355 {
00356    return RotateV( angle, Vector( x, y, z ));
00357 }
00358 
00359 inline void TransformVectorNoTranslate( const Matrix34 &m, Vector &v )  // CANDIDATE FOR SML
00360 {
00361    v.Set( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z, 
00362           m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
00363           m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z );
00364 }
00365 
00366 inline Matrix34 XRotateRadians( float anglerad )
00367 {
00368    float ca = (float)cos( anglerad ),
00369          sa = (float)sin( anglerad );
00370    return Matrix34( Vector4( 1.f, 0.f, 0.f, 0.f ),
00371                     Vector4( 0.f,  ca, -sa, 0.f ),
00372                     Vector4( 0.f,  sa,  ca, 0.f ));
