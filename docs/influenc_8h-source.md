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

# influenc.h

[Go to the documentation of this file.](influenc_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  5/26/2004  \iMac115\Include\influenc.h
00002 
00003 #define __INFLUENC_H
00004 
00005 #ifndef __ROBJECT_H
00006 #include "RObject.h"
00007 #endif
00008 #ifndef __VECTOR_H
00009 #include "Vector.h"
00010 #endif
00011 #ifndef __MATRIX34_H
00012 #include "Matrix34.h"
00013 #endif
00014 #ifndef __MACROS_H
00015 #include "Macros.h"
00016 #endif
00017 
00018 class QuadObject : public RObject {
00019 public:
00020    float                smin, smax, tmin, tmax;
00021 
00022    void                 *operator new( size_t );
00023 
00024    BOOL                 IsPatch() { return TRUE;}
00025    int                  GetType() { return QUADRANGLE; }
00026 
00027    virtual void         Intersect( const Vector &, const Vector &, ThreadInfo * ) = 0;
00028    virtual void         Collision( ThreadInfo *, Vector &min, Vector &max ) = 0;
00029    virtual void         Normal( Hit &, Vector &, Vector & ) = 0;
00030 };
00031 
00032 class Quadrangle : public QuadObject {
00033 public:
00034    Quadrangle::Quadrangle( Vector &p1, Vector &p2, Vector &p3,
00035     Vector &p4, float u1, float u2, float v1, float v4, int polyid );
00036 
00037    Vector       p[4];
00038    int          polyid;
00039 
00040    void         Intersect( const Vector &, const Vector &, ThreadInfo * );
00041    void         Bounds( Vector &min, Vector &max );
00042    void         Collision( ThreadInfo *, Vector &min, Vector &max );
00043    void         Normal( Hit &, Vector &, Vector & );
00044 };
00045 
00046 class FractalQuadrangle : public Quadrangle {
00047 public:
00048    Vector               n1, n2, n3, n4;
00049 
00050 //   FractalQuadrangle::FractalQuadrangle() {}
00051    FractalQuadrangle::FractalQuadrangle( Vector &, Vector &, Vector &,
00052     Vector &, float, float, float, float,
00053     Vector &, Vector &, Vector &, Vector &, int polyid );
00054 
00055    void                 Normal( Hit &, Vector &, Vector & );
00056 };   
00057 
00058 class PropQuadrangle : public QuadObject {
00059 public:
00060    int                  m_vertexid[4], m_normalid[4];
00061 
00062    void                 Bounds( Vector *vertexlist, Vector &min, Vector &max );
00063    void                 Intersect( const Vector &, const Vector &, ThreadInfo * );
00064    void                 Collision( ThreadInfo *, Vector &min, Vector &max );
00065 
00066    virtual void         Normal( Hit &, Vector &, Vector & );
00067    int                  GetType() { return PROPQUADRANGLE; }
00068 };   
00069 
00070 class DisplaceQuadrangle : public FractalQuadrangle {
00071 public:
00072    DisplaceQuadrangle( Vector &p1, Vector &p2, Vector &p3,
00073     Vector &p4, float smin, float smax, float tmin, float tmax,
00074     Vector &pn1, Vector &pn2, Vector &pn3, Vector &pn4, int polyid )
00075    : FractalQuadrangle( p1, p2, p3, p4, smin, smax, tmin, tmax, 
00076     pn1, pn2, pn3, pn4, polyid ) {}
00077     
00078    void                 Normal( Hit &, Vector &, Vector & );
00079 };   
00080 
00081 class Bone;
00082 
00083 class InfluenceShape : public RObject {
00084 public:
00085    Bone *bone;
00086    Matrix34 worldmatrix, worldinverse, screenmatrix, screeninverse, steadyscreenmatrix;
00087    float m_k0, m_k2, m_k1;
00088 
00089    void SetMatrices();
00090 
00091    InfluenceShape() {
00092      SetAttenuation(1.0f);
00093    }
00094    
00095    float GetAttenuation( float d )                  
00096    {                                                
00097       if ( d > 1.0f )                               
00098          return 1.0f / ( m_k0 + m_k1*d + m_k2*d*d );
00099       d = 6.0f - 5.0f * d;                          
00100       return -0.2f / ( m_k0 + m_k1*d + m_k2*d*d ) + 1.2f; 
00101    }                                                      
00102 
00103    void SetAttenuation( float attenuation ) 
00104    {
00105       m_k0 = (attenuation < 0.5f) ? 1.0f - attenuation * 2.0f : 0.0f;
00106       m_k2 = (attenuation > 0.5f) ? attenuation * 2.0f - 1.0f : 0.0f;
00107       m_k1 = 1.0f - MAX(m_k0, m_k2);
00108    }
00109 
00110    virtual float  Falloff( Vector ) = 0;
00111    virtual Vector Attract( Vector, float ) = 0;
00112    virtual Vector Vortex( Vector, Vector, float ) = 0;
00113    virtual Vector Friction( Vector, Vector, float ) = 0;
00114    virtual float  Lighting( const Vector &, Vector &, float & ) = 0;
00115    virtual float  LightingNoCap( const Vector &p ) {return 1.0f;}
00116    virtual void   Transform() = 0;
00117    virtual BOOL   IsInside( Vector p ) = 0;
00118    virtual void   FindBounds( Vector &min, Vector &max ) = 0;
00119 };
00120 
00121 
00122 #define K      .8
00123 #define M      1.2
00124 #define ALPHA  2
00125 
00126 class RSphere : public InfluenceShape {
00127 public:
00128    Vector   center;
00129    float    radius, radiussqr, falloffdistance, falloffdistancesqr,
00130              softfalloffdistance, falloffdistancedelta,
00131              S, beta, L; // variables for attenuation falloff
00132 
00133    RSphere() {}
00134    RSphere( float, float, float );
00135 
00136    void Init( float, float, float );
00137 
00138    void  Intersect( const Vector &, const Vector &, ThreadInfo * );
00139    BOOL  Intersect( const Vector &, const Vector &, Vector &, Vector & );
00140    void  Normal( Hit &, Vector &, Vector & );
00141    int   GetType() { return RSPHERE; }
00142    float Falloff( Vector );
00143    Vector Attract( Vector, float );
00144    Vector Vortex( Vector, Vector, float );
00145    Vector Friction( Vector, Vector, float );
00146    float Lighting( const Vector &, Vector &, float & );
00147    void  Transform();
00148    BOOL  IsInside( Vector p );
00149    void  FindBounds( Vector &min, Vector &max );
00150 };
00151 
00152 class Cone : public InfluenceShape {
00153 public:
00154    Vector      base, axis, capbase;
00155    float       angle, halfangle, tanangle, tananglesqr, radius, endradius,
00156                deltaangle, cap, length, lengthsqr, costotalangle,
00157                softness, cossoftangle, falloffdistance, falloffdistancedelta,
00158                S, beta, L; // variables for attenuation falloff
00159 
00160    Cone( float, float, float, float, float );
00161 
00162    void Init( float, float, float, float, float );
00163 
00164    void  Intersect( const Vector &, const Vector &, ThreadInfo * );
00165    BOOL  Intersect( const Vector &, const Vector &, Vector &, Vector & );
00166    void  Normal( Hit &, Vector &, Vector & );
00167    int   GetType() { return RCONE; }
00168    float Falloff( Vector );
00169    Vector Attract( Vector, float );
00170    Vector Vortex( Vector, Vector, float );
00171    Vector Friction( Vector, Vector, float );
00172    float Lighting( const Vector &, Vector &, float & );
00173    float LightingNoCap( const Vector &p );
00174    void Transform();
00175    void Transform( const Matrix34 &screenmatrix );
00176    BOOL IsVisible( Vector, const Matrix34 &, float, float, float (*GetVolumetricZ)(int,int));
00177    BOOL  IsInside( Vector p );
00178    void  FindBounds( Vector &min, Vector &max );
00179 };
00180 
00181 class Cylinder : public InfluenceShape {
00182 public:
00183    Vector               base, axis;
00184    float                radius, radiussqr, length, lengthsqr, radiusfalloffdistance,
00185                         softfalloffdistance, falloffdistancedelta, radiusfalloffdistancedelta,
00186                         S, beta, L; // variables for attenuation falloff
00187 
00188    Cylinder() {}
00189    Cylinder( float, float, float, float );
00190 
00191    void Init( float, float, float, float );
00192 
00193    void  Intersect( const Vector &, const Vector &, ThreadInfo * );
00194    BOOL  Intersect( const Vector &, const Vector &, Vector &, Vector & );
00195    void  Normal( Hit &, Vector &, Vector & );
00196    int   GetType() { return RCYLINDER; }
00197    float Falloff( Vector );
00198    Vector Attract( Vector, float );
00199    Vector Vortex( Vector, Vector, float );
00200    Vector Friction( Vector, Vector, float );
00201    float Lighting( const Vector &, Vector &, float & );
00202    void Transform();
00203    BOOL  IsInside( Vector p );
00204    void  FindBounds( Vector &min, Vector &max );
00205 };
00206 
00207 class Slab : public InfluenceShape {
00208 public:
00209    Vector center, axis;
00210    float length, softlength, lengthdelta, halfwidth, softhalfwidth, halfwidthdelta;
00211    
00212    Slab() {}
00213    Slab( float, float, float, float );
00214 
00215    void Init( float, float, float, float );
00216 
00217    void  Intersect( const Vector &, const Vector &, ThreadInfo * );
00218    BOOL  Intersect( const Vector &, const Vector &, Vector &, Vector & );
00219    void  Normal( Hit &, Vector &, Vector & );
00220    int   GetType() { return RBOX; }
00221    float Falloff( Vector );
00222    Vector Attract( Vector, float );
00223    Vector Vortex( Vector, Vector, float );
00224    Vector Friction( Vector, Vector, float );
00225    float Lighting( const Vector &, Vector &, float & );
00226    void ComputeSides( Vector &, float, float, float );
00227    void Transform();
00228    BOOL  IsInside( Vector p );
00229    void  FindBounds( Vector &min, Vector &max );
00230 };
00231 
00232 BOOL IntersectEndCap( const Vector &eye, const Vector &d, const Vector &base,
00233  float radius, Vector &n, float &t, Vector &hitp );
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
