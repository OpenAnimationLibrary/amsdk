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

# Vector2.h

[Go to the documentation of this file.](Vector2_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/24/2002  \HRandy95\Include\Vector2.h
00002 
00003 #define __VECTOR2_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #include <math.h>
00009 
00010 class Matrix33;
00011 
00012 class Vector2 {
00013 public:
00014    float x, y;
00015    
00016    Vector2() {}
00017    Vector2( float xinit, float yinit )
00018    {
00019       x = xinit;
00020       y = yinit;
00021    }
00022    Vector2( const Vector2 &other )
00023    {
00024       x = other.x;
00025       y = other.y;
00026    }
00027    Vector2( float scalar )
00028    {
00029       x = y = scalar;
00030    }
00031 
00032    float operator[]( int i ) const
00033    {
00034       return (&x)[i];
00035    }
00036    float &operator[]( int i )
00037    {
00038       return (&x)[i];
00039    }
00040 
00041    Vector2 &operator=( const Vector2 &other )
00042    {
00043       x = other.x;
00044       y = other.y;
00045       return *this;
00046    }
00047    Vector2 &operator=( float scalar )
00048    {
00049       x = y = scalar;
00050       return *this;
00051    }
00052 
00053    void operator += ( const Vector2 & );
00054    void operator -= ( const Vector2 & );
00055    void operator *= ( const Vector2 & );
00056    void operator *= ( const float );
00057    void operator /= ( const Vector2 & );
00058    void operator /= ( const float );
00059 
00060    float Norm() const
00061    {
00062       return (float)sqrt( x*x + y*y );
00063    } 
00064    void Negate();
00065    void Set( float px, float py );
00066    void Set( float );
00067    Vector2 Normalized() const;
00068    Vector2 Absolute() const;
00069    Vector2 Reciprocal() const;
00070    Vector2 Orthogonal() const;
00071 
00072    float Normalize()
00073    {
00074       float length;
00075       
00076       if (length = Norm())
00077          (*this) /= length;
00078       return length;
00079    }
00080    float Dot( const Vector2 & );
00081 
00082    friend Vector2 operator - ( const Vector2 & );
00083    friend Vector2 operator + ( const Vector2 &, const Vector2 & );
00084    friend Vector2 operator - ( const Vector2 &, const Vector2 & );
00085    friend Vector2 operator * ( const Vector2 &, const float );
00086    friend Vector2 operator * ( const float, const Vector2 & );
00087    friend Vector2 operator / ( const Vector2 &, const float );
00088 
00089    friend Vector2 operator * ( const Vector2 &, const Vector2 & ); // MEMBERWISE MULTIPLY
00090    friend float operator | ( const Vector2 &, const Vector2 & );  // DOT PRODUCT
00091    friend float operator ^ ( const Vector2 &, const Vector2 & );  // DOT PRODUCT
00092 
00093    friend int operator == ( const Vector2 &, const Vector2 & );
00094    friend int operator != ( const Vector2 &, const Vector2 & );
00095    friend void Swap( Vector2 &, Vector2 & );
00096 
00097    friend float Dot( const Vector2 &a, const Vector2 &b ) { return a.x * b.x + a.y * b.y; }
00098 
00099    friend Vector2 ToVector2( const Vector &p )
00100    {
00101       return Vector2( p.x, p.y );
00102    }
00103 
00104 //   friend Vector2 operator * ( const Matrix33 &, const Vector2 & );
00105 //   friend Vector2 operator * ( const Vector2 &v, const Matrix33 &m );
00106 };
00107 
00108 inline int operator == ( const Vector2 &a, const Vector2 &b )
00109 {
00110    return (a.x==b.x) && (a.y==b.y);
00111 }
00112 
00113 inline void Vector2::operator += ( const Vector2 &other )
00114 {
00115    x += other.x;
00116    y += other.y;
00117 }
00118 
00119 inline void Vector2::operator -= ( const Vector2 &other )
00120 {
00121    x -= other.x;
00122    y -= other.y;
00123 }
00124 
00125 inline void Vector2::operator *= ( const Vector2 &other )
00126 {
00127    x *= other.x;
00128    y *= other.y;
00129 }
00130 
00131 inline void Vector2::operator *= ( const float scale )
00132 {
00133    x *= scale;
00134    y *= scale;
00135 }
00136 
00137 inline void Vector2::operator /= ( const float scale )
00138 {
00139    x /= scale;
00140    y /= scale;
00141 }
00142 
00143 inline void Vector2::operator /= ( const Vector2 &other )
00144 {
00145    x /= other.x;
00146    y /= other.y;
00147 }
00148 
00149 inline void Vector2::Negate()
00150 {
00151    x = -x;
00152    y = -y;
00153 }
00154 
00155 inline void Vector2::Set( float xinit, float yinit )
00156 {
00157    x = xinit;
00158    y = yinit;
00159 }
00160 
00161 inline void Vector2::Set( float init )
00162 {
00163    x = init;
00164    y = init;
00165 }
00166 
00167 inline Vector2 operator / ( const Vector2 &a, const float s )
00168 {
00169    return Vector2( a.x/s, a.y/s );
00170 }
00171 
00172 inline Vector2 operator - ( const Vector2 &unary )
00173 {
00174    return Vector2( -unary.x, -unary.y );
00175 }   
00176 
00177 inline Vector2 operator + ( const Vector2 &a, const Vector2 &b )
00178 {
00179    return Vector2( a.x+b.x, a.y+b.y );
00180 }
00181 
00182 inline Vector2 operator - ( const Vector2 &a, const Vector2 &b )
00183 {
00184    return Vector2( a.x-b.x, a.y-b.y );
00185 }
00186 
00187 inline Vector2 operator * ( const Vector2 &a, const float s )
00188 {
00189    return Vector2( a.x*s, a.y*s );
00190 }
00191 
00192 inline Vector2 operator * ( const float s, const Vector2 &a )
00193 {
00194    return a*s;
00195 }
00196 
00197 inline Vector2 operator * ( const Vector2 &a, const Vector2 &b )
00198 {
00199    return Vector2( a.x*b.x, a.y*b.y );
00200 }
00201 
00202 inline float operator | ( const Vector2 &a, const Vector2 &b )
00203 {
00204    return a.x*b.x + a.y*b.y;
00205 }
00206 
00207 inline float operator ^ ( const Vector2 &a, const Vector2 &b )
00208 {
00209    return a.x*b.y - a.y*b.x;
00210 }
00211 
00212 inline int operator != ( const Vector2 &a, const Vector2 &b )
00213 {
00214    return !(a==b);
00215 }   
00216 
00217 inline float Vector2::Dot( const Vector2 &other )
00218 {
00219    return x * other.x + y * other.y;
00220 }
00221 
00222 inline void Swap( Vector2 &a, Vector2 &b )
00223 {
00224    Vector2 temp( a );
00225    a = b;
00226    b = temp;
00227 }
00228 
00229 inline Vector2 Vector2::Normalized() const
00230 {
00231    float length;
00232    Vector2 n = *this;
00233    
00234    if (length = n.Norm())
00235       n /= length;
00236    return n;
00237 }
00238 
00239 inline Vector2 Vector2::Absolute() const
00240 {
00241    return Vector2( (float)fabs( x ), (float)fabs( y ));
00242 }
00243 
00244 inline Vector2 Vector2::Reciprocal() const
00245 {
00246    return Vector2( 1.f/x, 1.f/y );
00247 }
00248 
00249 inline Vector2 Vector2::Orthogonal() const
00250 {
00251    return Vector2( y, -x );
00252 }
00253 
00254 inline Vector::Vector( const Vector2 &v2 )
00255 {
00256    x = v2.x; y = v2.y; z = 1.0f;
00257 }
00258 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
