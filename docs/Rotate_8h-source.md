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

# Rotate.h

[Go to the documentation of this file.](Rotate_8h.md)

<div class="fragment">

``` fragment
00001 // RC  6/11/2002  \Randy95\Include\Rotate.h
00002 
00003 #define __ROTATE_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #ifndef __QUATERNI_H
00009 #include "Quaterni.h"
00010 #endif
00011 
00012 class Rotate {
00013 public:   
00014    float          swivel, tilt, roll;
00015    //                x      z     y
00016 
00017    Rotate() {}
00018    Rotate( const float scalar ) { swivel = tilt = roll = scalar; }
00019    Rotate( const float pswivel, const float ptilt, const float proll )
00020     { swivel = pswivel; tilt = ptilt; roll = proll; }
00021    int operator == ( const Rotate &a ) const { return swivel==a.swivel && tilt == a.tilt && roll==a.roll; }
00022    int operator != ( const Rotate &a ) const { return !(*this == a); }   
00023 };
00024 
00025 class RotateSphere;
00026 class RotateEuler;
00027 
00028 class RotateVector {
00029 public:
00030    Vector               end;
00031    float                roll;
00032    
00033    RotateVector() {}
00034    RotateVector( const Vector &pend, float proll ) { end=pend; roll=proll; }
00035    ~RotateVector() {}
00036    RotateVector( const RotateSphere &sphere );
00037    RotateVector( const RotateEuler &euler );
00038    RotateVector( const Matrix34 &matrix );
00039    RotateVector( const Quaternion &quat );
00040 
00041    friend int operator != ( const RotateVector &a, const RotateVector &b )
00042     { return a.end!=b.end || a.roll!=b.roll; }
00043 };
00044 
00045 class RotateSphere {
00046 public:
00047    float                latitude,
00048                         longitude,
00049                         roll;
00050    RotateSphere() {}
00051    ~RotateSphere() {}
00052    RotateSphere( const Vector &vec );
00053    RotateSphere( const RotateVector &rotateend );
00054    RotateSphere( const Quaternion &quat );
00055    RotateSphere( const Quaternion &quat, Bone *bone );
00056 };
00057 
00058 class RotateEuler { 
00059 public:   
00060    float          x, y, z;
00061 
00062    RotateEuler() {}
00063    ~RotateEuler() {}
00064    RotateEuler( float px, float py, float pz ) { x=px; y=py; z=pz; }
00065    RotateEuler( const Matrix34 &t );
00066    RotateEuler( const RotateVector &rotateend );
00067    RotateEuler( const Quaternion &quat );
00068    void ToEuler( const Matrix34 &t );
00069    RotateEuler operator * ( float scale ) { RotateEuler other; other.x = x * scale; other.y  = y * scale; other.z = z * scale; return other; }
00070    float operator[]( int i ) const
00071    {
00072       return (&x)[i];
00073    }
00074    float &operator[]( int i )
00075    {
00076       return (&x)[i];
00077    }
00078 };
00079 
00080 class TSR {
00081 public:
00082    Vector            translate;
00083    Vector            scale;
00084    RotateVector      rotate;
00085    
00086    friend int operator != ( const TSR &a, const TSR &b )
00087     { return a.rotate!=b.rotate || a.translate!=b.translate || a.scale!=b.scale; }
00088    void SetDefault()
00089     { translate.Set(0.0f); scale.Set(1.0f); rotate.end.Set(0.0f,0.0f,1.0f); rotate.roll=0.0f; }
00090 };
00091 
00092 class MATRIXEXPORT TSQ {
00093 public:
00094    Vector            translate;
00095    Vector            scale;
00096    Quaternion        quat;
00097    float             roll;
00098    BOOL              m_isrollcomputed;
00099    
00100    TSQ(){}
00101    TSQ(const Matrix34 &actionmatrix);
00102    TSQ(const Vector &ptranslate, const Vector &pscale, const Quaternion &pquat)
00103    {
00104       translate = ptranslate;
00105       scale = pscale;
00106       quat = pquat;
00107    }
00108    
00109    int operator != ( const TSQ &b ) const
00110     { return quat!=b.quat || translate!=b.translate || scale!=b.scale; }
00111    void SetDefault()
00112     { translate.Set(0.0f); scale.Set(1.0f); quat.SetIdentity(); }
00113    TSQ &operator += ( const TSQ &other )
00114    {
00115       translate += other.translate;
00116       scale += other.scale;
00117       quat += other.quat;
00118       return *this;
00119    }
00120    TSQ &operator *= ( float scalar )
00121    {
00122       translate *= scalar;
00123       scale *= scalar;
00124       quat *= scalar;
00125       return *this;
00126    }
00127    void PostBlend()
00128    {
00129       quat.Normalize();
00130    }
00131    void FillMatrices( Matrix34 &matrix, Matrix34 &inverse );
00132 };
00133 
00134 // ANY ROTATION TYPE TO AND FROM QUATERNION
00135 
00136 inline RotateEuler::RotateEuler( const Quaternion &quat )
00137 {
00138    Vector end( quat.GetZAxis());
00139    y = (float)(atan2( end.x, end.z ) * RADIANS);
00140    x = (float)(atan2( -end.y, sqrt(end.x*end.x + end.z*end.z)) * RADIANS);
00141    Vector rolldir( quat.GetYAxis());
00142    rolldir *= YXRotateQ( y, x ).Inverse();
00143    z = (float)(atan2( -rolldir.x, rolldir.y ) * RADIANS);
00144 }
00145 
00146 inline RotateVector::RotateVector( const Quaternion &quat )  // SOB STYLE ROLL
00147 {
00148    end = quat.GetZAxis();
00149    float y = (float)atan2( end.x, end.z );
00150    float x = (float)atan2( -end.y, (float)sqrt(end.x*end.x + end.z*end.z));
00151    Vector rolldir = quat.GetYAxis();
00152    rolldir *= YXRotateRadiansQ( y, x ).Inverse();
00153    roll = (float)atan2( -rolldir.x, rolldir.y ) * RADIANS;
00154 }
00155 
00156 inline Quaternion::Quaternion( const RotateVector &rv )  // SOB STYLE ROLL
00157 {
00158    float y = (float)atan2( rv.end.x, rv.end.z );
00159    float x = (float)atan2( -rv.end.y, (float)sqrt(rv.end.x*rv.end.x + rv.end.z*rv.end.z));
00160    if ( rv.roll )
00161       *this = YXZRotateRadiansQ( y, x, rv.roll / RADIANS );
00162    else
00163       *this = YXRotateRadiansQ( y, x );
00164 }
00165 
00166 inline RotateSphere::RotateSphere( const Quaternion &quat )
00167 {
00168    *this = RotateSphere(RotateVector(quat));
00169 }
00170 
00171 inline Quaternion::Quaternion( const RotateSphere &rs )
00172 {
00173    *this = Quaternion(RotateVector(rs));
00174 }
00175 
00176 inline Quaternion::Quaternion( const RotateEuler &re )
00177 {
00178    if ( re.z )
00179       *this = YXZRotateQ( re.y, re.x, re.z );
00180    else
00181       *this = YXRotateQ( re.y, re.x );
00182 }
00183 
00184 inline Quaternion::Quaternion( const RotateEuler &re, BOOL isyxz )
00185 {
00186    if (isyxz) {
00187       if ( re.z )
00188          *this = YXZRotateQ( re.y, re.x, re.z );
00189       else
00190          *this = YXRotateQ( re.y, re.x );
00191    }
00192    else {
00193       if ( re.z )
00194          *this = XYZRotateQ( re.x, re.y, re.z );
00195       else
00196          *this = XYRotateQ( re.x, re.y );
00197    }
00198 }
00199 
00200 // CONVERSIONS BETWEEN ROTATE TYPES
00201 
00202 inline RotateSphere::RotateSphere( const Vector &vec )
00203 {
00204    longitude = (float)atan2( -vec.x, vec.y )*RADIANS;
00205    latitude = (float)atan2( (float)sqrt(vec.x*vec.x + vec.y*vec.y), vec.z )*RADIANS;
00206 }
00207 
00208 inline RotateSphere::RotateSphere( const RotateVector &rotate )
00209 {
00210    longitude = (float)atan2( -rotate.end.x, rotate.end.y )*RADIANS;
00211    latitude = (float)atan2( (float)sqrt(rotate.end.x*rotate.end.x + rotate.end.y*rotate.end.y),
00212     rotate.end.z )*RADIANS;
00213    roll = rotate.roll; 
00214 }
00215 
00216 inline RotateVector::RotateVector( const RotateSphere &sphere )
00217 {
00218     float r = (float)sin( sphere.latitude/RADIANS );
00219     end.z = (float)cos( sphere.latitude/RADIANS );
00220     end.y = r * (float)cos( sphere.longitude/RADIANS );
00221     end.x = -r * (float)sin( sphere.longitude/RADIANS );
00222     roll = sphere.roll;
00223 }
00224 
00225 inline RotateVector::RotateVector( const RotateEuler &euler )
00226 {
00227    float cy = (float)cos( euler.y / RADIANS ),
00228          sy = (float)sin( euler.y / RADIANS ),
00229          cx = (float)cos( euler.x / RADIANS ),
00230          sx = (float)sin( euler.x / RADIANS );
00231    end.Set( sy*cx, -sx, cy*cx );  // SPEED UP: THESE ARE THE Z COLUMN OUT OF YXROTATE, WHICH IS THE SAME AS BUILDING THAT MATRIX, THEN TRANSFORMING (0,0,1) BY IT
00232    roll = euler.z;
00233  }
00234 
00235 inline RotateEuler::RotateEuler( const RotateVector &rotatev )
00236 {
00237    y = (float)atan2( rotatev.end.x, rotatev.end.z ) * RADIANS;
00238    x = (float)atan2( -rotatev.end.y, (float)sqrt(rotatev.end.x*rotatev.end.x +
00239     rotatev.end.z*rotatev.end.z)) * RADIANS;
00240    z = rotatev.roll;
00241 }
00242 
00243 // THE 4 FUNCTIONS BELOW WORK ONLY 0 TO 90 DEGREES
00244 
00245 inline float VectorsToLinear( const Vector &v, const Vector &v1 )
00246 {
00247    float cosa = Dot(v.Normalized(), v1.Normalized());
00248    if ( cosa == 0.0f )
00249       return 0.0f;
00250    float sina = (float)sqrt( 1.0f - cosa*cosa );
00251    float slope = sina / cosa;
00252    float percent = slope / (slope + 1.0f);
00253    return percent *= 90.0f;
00254 }
00255 
00256 inline float VectorsToAngle( const Vector &v, const Vector &v1 )
00257 {
00258    return (float)acos(Dot(v.Normalized(), v1.Normalized())) * RADIANS;
00259 }
00260 
00261 inline float LinearToAngle( float linear )
00262 {
00263    return (float)atan( linear / (90-linear)) * RADIANS;
00264 }
00265 
00266 inline float LinearToAngle360( float linear )
00267 {
00268    if ( linear < 0 )
00269       return -LinearToAngle360( -linear );
00270    if ( linear <= 90 )
00271       return LinearToAngle( linear );
00272    float remainder = (float)fmod( linear, 90 );
00273    float excess = linear - remainder;
00274    return excess + LinearToAngle( remainder );
00275 }
00276 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
