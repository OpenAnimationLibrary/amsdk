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

# Quaterni.h

[Go to the documentation of this file.](Quaterni_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  2/24/2004  \DanLP110\Include\Quaterni.h
00002 
00003 #define __QUATERNI_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #ifndef __EXPORTS_H
00009 #include "Exports.h"
00010 #endif
00011 #ifndef __FILECONS_H
00012 #include "FileCons.h"
00013 #endif
00014 
00015 class RotateVector;
00016 class RotateSphere;
00017 class RotateEuler;
00018 class Bone;
00019 
00020 class MATRIXEXPORT Quaternion 
00021 {
00022 protected:
00023    Vector v;
00024    float w;
00025 
00026 public:
00027 // CONSTRUCTORS
00028    Quaternion() {}
00029    Quaternion( const Matrix33 & );
00030    Quaternion( const Matrix34 & );
00031    Quaternion( const Vector &vec, float scalar )
00032    {
00033       v = vec;
00034       w = scalar;
00035    }
00036    Quaternion( float x, float y, float z, float s )
00037    {                                                                  
00038       v.x = x;
00039       v.y = y;
00040       v.z = z;
00041       w = s;
00042    }
00043    Quaternion( const Quaternion &q )
00044    {
00045       v = q.v;
00046       w = q.w;
00047    }
00048    Quaternion( float scalar )
00049    {
00050       v = Vector( 0.0f );
00051       w = scalar;
00052    }
00053    Quaternion( float radangle, const Vector &axis ) { SetAngleAxis( radangle, axis ); }
00054    Quaternion( const RotateVector &rv );  // SOB STYLE ROLL
00055    Quaternion( const RotateSphere &rs );
00056    Quaternion( const RotateSphere &rs, Bone *bone );
00057    Quaternion( const RotateEuler  &re );
00058    Quaternion( const RotateEuler  &re, BOOL isyxz );
00059    
00060 // STORAGE & RETRIEVAL
00061    const Vector &GetV() const { return v; }
00062    float GetW() const { return w; }
00063    void SetV( const Vector &vec ) { v = vec; } 
00064    void SetV( int index, float value ) { v[index] = value; } 
00065    void SetW( float scalar ) { w = scalar; }
00066    void Set( float x, float y, float z, float pw ) { v.Set(x,y,z); w=pw; }
00067    void Set( Vector pv, float pw ) { v=pv; w=pw; }
00068    void Set( float fillvalue ) { v.Set(fillvalue); w=fillvalue; }
00069    void SetIdentity() { Set(0.0f,0.0f,0.0f,1.0f); }
00070    Vector GetXAxis() const { return *this * Vector(1.0f,0.0f,0.0f); }
00071    Vector GetYAxis() const { return *this * Vector(0.0f,1.0f,0.0f); }
00072    Vector GetZAxis() const { return *this * Vector(0.0f,0.0f,1.0f); }
00073    float GetAngle() const  // this now always returns the smaller angle, ie 30 rather than 330, 175 rather than 185
00074    {
00075       float fw = (float)fabs(w);
00076       if (fw < 1)
00077          return (float)acos(fw)*2.0f;
00078       else
00079          return 0.0f;
00080    }
00081    Vector GetAxis() const
00082    {
00083       if ( w >= 1.0f )
00084          return v;
00085       if ( w > 0 ) 
00086          return v / (float)sin( acos(w));
00087       else
00088          return v / -(float)sin( acos(w));
00089    }
00090    void SetAngleAxis( float radangle, const Vector &axis )
00091    {
00092       v = axis;
00093       v.Normalize();
00094       w = (float)cos( radangle / 2 );
00095       v *= (float)sin( radangle / 2 );
00096    }   
00097 
00098 // UNARY OPERATIONS
00099    float Norm() const
00100    {
00101       return (float)sqrt(Dot(*this,*this));
00102    }
00103    Quaternion & Normalize()
00104    {
00105       *this /= Norm();
00106       return *this;
00107    }   
00108    Quaternion Normalized() const
00109    {
00110       return *this / Norm();
00111    }   
00112    float NormalizeLength( void )
00113    {
00114       float length = Norm();
00115       if (length)
00116          *this /= length;
00117       return length;
00118    }
00119    Quaternion Conjugate() const
00120    {
00121       return Quaternion( -v, w );
00122    }
00123    Quaternion Inverse() const
00124    {
00125       return Conjugate(); // / Norm();  ASSUME ALL OUR QUATS ARE NORMALIZED
00126    }
00127    Quaternion &Negate( void )
00128    {
00129       v.Negate();
00130       w = -w;
00131       return *this;
00132    }
00133    BOOL IsIdentity()
00134    {
00135       return *this == IdentityQ();
00136    }
00137 
00138 // OPERATORS
00139    int operator == ( const Quaternion &a ) const   { return (v == a.v) && (w == a.w); }
00140    int operator != ( const Quaternion &a ) const   { return !(*this == a); }   
00141    Quaternion &operator *= ( const Quaternion &q ) { *this = *this * q; return *this; }
00142    Quaternion &operator *= ( float scalar ) { v*=scalar; w*=scalar; return *this; }
00143    Quaternion &operator /= ( float scalar ) { v/=scalar; w/=scalar; return *this; }
00144    Quaternion &operator += ( const Quaternion &q2 ) { v+=q2.v; w+=q2.w; return *this; }
00145    Quaternion &operator -= ( const Quaternion &q2 ) { v-=q2.v; w-=q2.w; return *this; }
00146    Quaternion operator - ( void )          const   { return Quaternion(*this).Negate(); }
00147    float &operator[]( int i ) { return (&v.x)[i]; }
00148    float operator[]( int i ) const { return (&v.x)[i]; }
00149    
00150    Quaternion operator * ( const Quaternion &b ) const;
00151    Quaternion operator * ( float scalar ) const
00152    {
00153       return Quaternion( v * scalar, w * scalar );
00154    }
00155    friend Quaternion operator * ( float scalar, const Quaternion &q )
00156    {
00157       return Quaternion( q.v * scalar, q.w * scalar );
00158    }
00159    Quaternion operator / ( float scalar ) const
00160    {
00161       return Quaternion( v / scalar, w / scalar );
00162    }
00163    Quaternion operator + ( const Quaternion &b ) const
00164    {
00165       return Quaternion( v + b.v, w + b.w );
00166    }
00167    Quaternion operator - ( const Quaternion &b ) const
00168    {
00169       return Quaternion( v - b.v, w - b.w );
00170    }
00171    Vector operator * ( const Vector &v ) const
00172    {
00173       return (*this * Quaternion(v,0.0f) * Inverse()).GetV();
00174    }
00175 
00176 // FRIENDS
00177    friend class Matrix33;
00178    friend class Matrix34;
00179    friend class Matrix44;
00180    friend Quaternion IdentityQ();
00181    friend void       TransformVector( const Quaternion &q, Vector &v );
00182    friend float      Dot( const Quaternion &a, const Quaternion &b );
00183    friend Quaternion RotateVQ( float angle, const Vector &axis );
00184    friend MATRIXEXPORT Quaternion RotateVRadiansQ( float anglerad, const Vector &axis );
00185    friend Quaternion XRotateRadiansQ( float anglerad );
00186    friend Quaternion YRotateRadiansQ( float anglerad );
00187    friend Quaternion ZRotateRadiansQ( float anglerad );
00188    friend Quaternion XRotateQ( float angle );
00189    friend Quaternion YRotateQ( float angle );
00190    friend Quaternion ZRotateQ( float angle );
00191    friend Quaternion YXZRotateRadiansQ( float y, float x, float z );
00192    friend Quaternion YXRotateRadiansQ( float y, float x );
00193    friend Quaternion YXZRotateQ( float y, float x, float z );
00194    friend Quaternion YXRotateQ( float y, float x );
00195    friend Quaternion XYZRotateQ( float x, float y, float z );
00196    friend Quaternion XYRotateQ( float x, float y );
00197    friend MATRIXEXPORT Quaternion Rotate2VQ( const Vector &from, const Vector &to );
00198    friend Quaternion VectorsToStandardQ( const Vector &becomezdir, const Vector &becomeydir );
00199    friend MATRIXEXPORT Quaternion Blend( const Quaternion &quat1, float percent1, const Quaternion &quat2, float percent2 );
00200 
00201    friend class Vector;
00202 };
00203 
00204 // move friend function implementations outside of the class to compile under Vs .Net 2003 (Niels)
00205 inline Quaternion IdentityQ() 
00206 {
00207    return Quaternion( 0.0f,0.0f,0.0f,1.0f ); 
00208 }
00209 inline void TransformVector( const Quaternion &q, Vector &v ) 
00210 {
00211    v *= q; 
00212 }
00213 inline float Dot( const Quaternion &a, const Quaternion &b )
00214 {
00215    return Dot(a.v,b.v) + a.w*b.w; 
00216 }
00217 inline Quaternion RotateVQ( float angle, const Vector &axis ) 
00218 {
00219    return Quaternion( angle/RADIANS, axis ); 
00220 }
00221 inline Quaternion XRotateRadiansQ( float anglerad ) 
00222 {
00223    return Quaternion( anglerad, Vector(1.0f,0.0f,0.0f)); 
00224 }
00225 inline Quaternion YRotateRadiansQ( float anglerad ) 
00226 {
00227    return Quaternion( anglerad, Vector(0.0f,1.0f,0.0f)); 
00228 }
00229 inline Quaternion ZRotateRadiansQ( float anglerad ) 
00230 {
00231    return Quaternion( anglerad, Vector(0.0f,0.0f,1.0f)); 
00232 }
00233 inline Quaternion XRotateQ( float angle )  
00234 {
00235    return XRotateRadiansQ( angle / RADIANS ); 
00236 }
00237 inline Quaternion YRotateQ( float angle )  
00238 {
00239    return YRotateRadiansQ( angle / RADIANS );
00240 }
00241 inline Quaternion ZRotateQ( float angle )  
00242 {
00243    return ZRotateRadiansQ( angle / RADIANS ); 
00244 }
00245 inline Quaternion YXZRotateRadiansQ( float y, float x, float z ) 
00246 {
00247    return YRotateRadiansQ(y) * XRotateRadiansQ(x) * ZRotateRadiansQ(z); 
00248 }
00249 inline Quaternion YXRotateRadiansQ( float y, float x )    
00250 {
00251    return YRotateRadiansQ(y) * XRotateRadiansQ(x); 
00252 }
00253 inline Quaternion YXZRotateQ( float y, float x, float z )  
00254 {
00255    return YXZRotateRadiansQ(y/RADIANS, x/RADIANS, z/RADIANS);
00256 }
00257 inline Quaternion YXRotateQ( float y, float x )      
00258 {
00259    return YXRotateRadiansQ(y/RADIANS, x/RADIANS); 
00260 }
00261 inline Quaternion XYZRotateQ( float x, float y, float z )    
00262 {
00263    return XRotateQ(x) * YRotateQ(y) * ZRotateQ(z);
00264 }
00265 inline Quaternion XYRotateQ( float x, float y )    
00266 { 
00267    return XRotateQ(x) * YRotateQ(y); 
00268 }
00269 
00270 inline Quaternion VectorsToStandardQ( const Vector &becomezdir, const Vector &becomeydir )
00271 {
00272    Quaternion vectostandard = Rotate2VQ( becomezdir, Vector(0.0f, 0.0f, 1.0f));
00273    Vector   rollvec = vectostandard * becomeydir;
00274    float    roll = (float)atan2( -rollvec.x, rollvec.y );
00275    if ( roll )
00276       vectostandard = ZRotateRadiansQ( -roll ) * vectostandard;
00277    return vectostandard;
00278 }
00279 
00280 inline Quaternion Quaternion::operator * ( const Quaternion &b ) const
00281 {
00282    return Quaternion( (v^b.v) + (w*b.v) + (v*b.w), w*b.w - (v|b.v) );
00283 }
00284 
00285 inline Vector &Vector::operator *= ( const Quaternion &q )
00286 {
00287 /*
00288    Quaternion qtemp( *this, 0.0f );  // 32*, 24+
00289    qtemp = q * qtemp * q.Inverse();
00290    *this = qtemp.GetV();
00291 */
00292    Quaternion q2( (q.v^(*this)) + (q.w*(*this)), -q.v|(*this));  // FASTER 24*, 17+
00293    *this = (q2.v*q.w)-(q2.w*q.v)-(q2.v^q.v);
00294    return *this;
00295 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
