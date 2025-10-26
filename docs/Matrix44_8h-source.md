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

# Matrix44.h

[Go to the documentation of this file.](Matrix44_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  2/24/2004  \DanLP110\Include\Matrix44.h
00002 
00003 #define __MATRIX44_H
00004 
00005 #ifndef __VECTOR4_H
00006 #include "Vector4.h"
00007 #endif
00008 #ifdef _SIMD
00009 #include "smlmath.h"
00010 #endif
00011 
00012 class Quaternion;
00013 
00014 // ************************** MATRIX44 ********************************
00015 
00016 class MATRIXEXPORT Matrix44 {
00017 protected:
00018 #ifdef _SIMD
00019    union {
00020       struct { SMLMatrix4f m_smlmatrix4f; };
00021       struct { Vector4 v[4]; };
00022    };
00023 #else
00024    Vector4 v[4];
00025 #endif
00026 
00027 public:
00028    Matrix44() {}
00029    Matrix44( const Matrix44 &m );
00030    Matrix44( float fill )
00031    {
00032       v[0].Set( fill );
00033       v[1].Set( fill );
00034       v[2].Set( fill );
00035       v[3].Set( fill );
00036    }
00037    Matrix44( const Vector4 &v0, const Vector4 &v1, const Vector4 &v2, const Vector4 &v3 )
00038    {
00039       v[0] = v0;
00040       v[1] = v1;
00041       v[2] = v2;
00042       v[3] = v3;
00043    }
00044    Matrix44(const Quaternion &quat);
00045    
00046    Matrix44 &operator *= ( const Matrix44 &other ) { return *this = *this * other; }
00047    const Vector4 &operator[]( int row ) const { return v[row]; }
00048    Vector4 &operator[]( int row ) { return v[row]; }
00049 
00050    void SetIdentity();
00051    Matrix44 Transpose() const;
00052    Matrix44 Inverse() const;
00053    
00054    Matrix44 operator * ( const Matrix44 &b ) const;
00055    Vector operator * ( const Vector &v ) const;
00056    Vector4 operator * ( const Vector4 &v ) const;
00057    friend MATRIXEXPORT Matrix44 Identity44();
00058 };
00059 
00060 #ifdef _SIMD
00061 
00062 inline Matrix44::Matrix44( const Matrix44 &m )
00063 {
00064    m_smlmatrix4f = m.m_smlmatrix4f;
00065 }
00066 
00067 inline void Matrix44::SetIdentity()
00068 {
00069    m_smlmatrix4f.Identity();
00070 }
00071 
00072 inline Matrix44 Matrix44::Transpose() const
00073 {
00074    Matrix44 temp( *this );
00075    temp.m_smlmatrix4f.Transpose();
00076    return temp;
00077 }
00078 
00079 inline Matrix44 Matrix44::Inverse() const
00080 {
00081    Matrix44 result, source=*this;
00082    result.m_smlmatrix4f.Invert(source.m_smlmatrix4f);  // BUG IN SML, SOURCE SHOULD BE DECLARED CONST
00083    return result;
00084 }
00085 
00086 inline Matrix44 Matrix44::operator * ( const Matrix44 &b ) const
00087 {
00088    Matrix44 result;
00089    result.m_smlmatrix4f.Multiply(m_smlmatrix4f, b.m_smlmatrix4f);
00090    return result;
00091 }
00092 
00093 inline Vector Matrix44::operator * ( const Vector &v ) const
00094 {
00095    Vector result;
00096    m_smlmatrix4f.TransformPoint( v.m_smlvec3f, result.m_smlvec3f );
00097    return result;
00098 }
00099 
00100 inline Vector4 Matrix44::operator * ( const Vector4 &v ) const
00101 {
00102    Vector4 result;
00103    m_smlmatrix4f.Transform( v.m_smlvec4f, result.m_smlvec4f );
00104    return result;
00105 }
00106 
00107 inline MATRIXEXPORT Matrix44 Identity44()
00108 {
00109    Matrix44 result;
00110    result.m_smlmatrix4f.Identity();
00111    return result;
00112 }
00113 
00114 #else  // not SIMD
00115 
00116 inline Matrix44::Matrix44( const Matrix44 &m )
00117 {
00118    v[0] = m.v[0];
00119    v[1] = m.v[1];
00120    v[2] = m.v[2];
00121    v[3] = m.v[3];
00122 }
00123 
00124 inline void Matrix44::SetIdentity()
00125 {
00126    v[0].Set(1.0f,0.0f,0.0f,0.0f);
00127    v[1].Set(0.0f,1.0f,0.0f,0.0f);
00128    v[2].Set(0.0f,0.0f,1.0f,0.0f);
00129    v[3].Set(0.0f,0.0f,0.0f,1.0f);
00130 }
00131 
00132 inline Matrix44 Matrix44::Transpose() const
00133 {
00134    return Matrix44( Vector4( v[0][0], v[1][0], v[2][0], v[3][0] ),
00135                     Vector4( v[0][1], v[1][1], v[2][1], v[3][1] ),
00136                     Vector4( v[0][2], v[1][2], v[2][2], v[3][2] ),
00137                     Vector4( v[0][3], v[1][3], v[2][3], v[3][3] ));
00138 }
00139 
00140 inline Vector Matrix44::operator * ( const Vector &vec ) const
00141 {
00142    Vector4 vec4( vec.x, vec.y, vec.z, 1.0f );
00143    return Vector( v[0]|vec4, v[1]|vec4, v[2]|vec4 );
00144 }
00145 
00146 inline Vector4 Matrix44::operator * ( const Vector4 &vec ) const
00147 {
00148    return Vector4( v[0]|vec, v[1]|vec, v[2]|vec, v[3]|vec );
00149 }
00150 
00151 inline MATRIXEXPORT Matrix44 Identity44()
00152 {
00153    return Matrix44( Vector4( 1.f, 0.f, 0.f, 0.f ),
00154                     Vector4( 0.f, 1.f, 0.f, 0.f ),
00155                     Vector4( 0.f, 0.f, 1.f, 0.f ),
00156                     Vector4( 0.f, 0.f, 0.f, 1.f ));
00157 }
00158 
00159 #endif  // not SIMD
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
