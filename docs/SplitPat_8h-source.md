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

# SplitPat.h

[Go to the documentation of this file.](SplitPat_8h.md)

<div class="fragment">

``` fragment
00001 // MH  22 Jan 2003
00002 
00003 #define __SPLITPAT_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 #ifndef __VECTOR2_H
00009 #include "Vector2.h"
00010 #endif
00011 #ifndef __EXPORTS_H
00012 #include "Exports.h"
00013 #endif
00014 
00015 #define FLAT0               0x00000001
00016 #define FLAT1               0x00000002
00017 #define FLAT2               0x00000004
00018 #define FLAT3               0x00000008
00019 #define NOTFIRSTVERTICAL    0x00000010
00020 #define NOTFIRSTHORIZONTAL  0x00000020
00021 #define NEEDSFLAT0          0x00000040
00022 #define NEEDSFLAT1          0x00000080
00023 #define NEEDSFLAT2          0x00000100
00024 #define NEEDSFLAT3          0x00000200
00025 #define FIRSTFLATTESTVERTICAL   0x00000400
00026 #define FIRSTFLATTESTHORIZONTAL 0x00000800
00027 
00028 #define IsFlat0(a) (a&FLAT0)
00029 #define IsFlat1(a) (a&FLAT1)
00030 #define IsFlat2(a) (a&FLAT2)
00031 #define IsFlat3(a) (a&FLAT3)
00032 
00033 #define OnFlat0(a) (a|=FLAT0)
00034 #define OnFlat1(a) (a|=FLAT1)
00035 #define OnFlat2(a) (a|=FLAT2)
00036 #define OnFlat3(a) (a|=FLAT3)
00037 
00038 #define IsNeedsFlat0(a) (a&NEEDSFLAT0)
00039 #define IsNeedsFlat1(a) (a&NEEDSFLAT1)
00040 #define IsNeedsFlat2(a) (a&NEEDSFLAT2)
00041 #define IsNeedsFlat3(a) (a&NEEDSFLAT3)
00042 
00043 #define OnNeedsFlat0(a) (a|=NEEDSFLAT0)
00044 #define OnNeedsFlat1(a) (a|=NEEDSFLAT1)
00045 #define OnNeedsFlat2(a) (a|=NEEDSFLAT2)
00046 #define OnNeedsFlat3(a) (a|=NEEDSFLAT3)
00047 
00048 #define OffNeedsFlat0(a) (a&=~NEEDSFLAT0)
00049 #define OffNeedsFlat1(a) (a&=~NEEDSFLAT1)
00050 #define OffNeedsFlat2(a) (a&=~NEEDSFLAT2)
00051 #define OffNeedsFlat3(a) (a&=~NEEDSFLAT3)
00052 
00053 /*
00054 SplitPatch vertex ordering
00055 
00056 1 5  9 13
00057 2 6 10 14
00058 3 7 11 15
00059 4 8 12 16
00060 
00061 */
00062 
00063 class SplitPatch 
00064 {
00065 public:
00066    Vector  m_p1, m_p4, m_p16, m_p13,  // Four corners for poly, CCW
00067            m_p2, m_p3,  m_p5,  m_p8,  // Tangents
00068            m_p9, m_p12, m_p14, m_p15; // Tangents
00069    Vector  m_n[4];
00070    Vector2 m_uv[4];
00071    union {
00072       DWORD      m_flags;
00073       struct {
00074          DWORD   m_edge0isdiscontinuous      : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches, Hooks)
00075                  m_edge1isdiscontinuous      : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches, Hooks)
00076                  m_edge2isdiscontinuous      : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches, Hooks)
00077                  m_edge3isdiscontinuous      : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches, Hooks)
00078                  m_is3point                  : 1, // m_p1 == m_p13 or m_vertexid[0] == m_vertexid[3]
00079                  m_edge0forcesplit           : 2, // Forces edge 0 to be split because it is shared with a hook
00080                  m_edge1forcesplit           : 2, // Forces edge 1 to be split because it is shared with a hook
00081                  m_edge2forcesplit           : 2, // Forces edge 2 to be split because it is shared with a hook
00082                  m_edge3forcesplit           : 2; // Forces edge 3 to be split because it is shared with a hook
00083       };
00084    };
00085 
00086    SplitPatch() { m_flags = 0L;}
00087    void SetVertices(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &v3,
00088     const Vector &t0, const Vector &t1, const Vector &t2, const Vector &t5,
00089     const Vector &t6, const Vector &t9, const Vector &t10, const Vector &t11);
00090    void SetNormals(const Vector &n0, const Vector &n1, const Vector &n2, const Vector &n3);
00091    void SetUVs(const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2, const Vector2 &uv3);
00092    void SetEdge0ForceSplit() { m_edge0forcesplit = 2; }
00093    void SetEdge1ForceSplit() { m_edge1forcesplit = 2; }
00094    void SetEdge2ForceSplit() { m_edge2forcesplit = 2; }
00095    void SetEdge3ForceSplit() { m_edge3forcesplit = 2; }
00096 };
00097 
00098 inline void SplitPatch::SetVertices(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &v3,
00099     const Vector &t0, const Vector &t1, const Vector &t2, const Vector &t5,
00100     const Vector &t6, const Vector &t9, const Vector &t10, const Vector &t11) {
00101    m_p1 = v0;
00102    m_p2 = t0;
00103    m_p3 = t1;
00104    m_p4 = v1;
00105    m_p5 = t2;
00106    m_p8 = t5;
00107    m_p9 = t6;
00108    m_p12 = t9;
00109    m_p13 = v3;
00110    m_p14 = t10;
00111    m_p15 = t11;
00112    m_p16 = v2;
00113 };
00114 
00115 inline void SplitPatch::SetNormals(const Vector &n0, const Vector &n1, const Vector &n2, const Vector &n3) 
00116 {
00117    m_n[0] = n0;
00118    m_n[1] = n1;
00119    m_n[2] = n2;
00120    m_n[3] = n3;
00121 };
00122 
00123 inline void SplitPatch::SetUVs(const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2, const Vector2 &uv3) 
00124 {
00125    m_uv[0] = uv0;
00126    m_uv[1] = uv1;
00127    m_uv[2] = uv2;
00128    m_uv[3] = uv3;
00129 };
00130 
00131 class PATCHEXPORT PatchSplitter
00132 {
00133 public:
00134    union { 
00135       DWORD  m_flags;
00136       struct {
00137          DWORD m_isuvs            : 1, // compute new UV
00138                m_isnormals        : 1, // compute normals
00139                m_0or1uvs          : 1, // UV range from 0 to 1, settings this will speed up UV calculations
00140                m_isvariable       : 1, // variable versus fixed sub
00141                m_is3point         : 1, // patch is 3 point patch, must set this ahead of time V0 == V3
00142                m_iscullbackfacing : 1; // CULL backfacing polys
00143 
00144       };
00145    };
00146    float m_straight,   // subdivision tolerance when variable patch splitting
00147          m_zoom,       // zoom projection, used to determine how large patch is to test flatness
00148          m_viewplane,  // -focallength for perspective
00149          m_hither;     // used for perspective flatness testing to determine zoomfactor
00150    int   m_maxlevel;   // levels to fix subdivide the patch, a value of 2 will 
00151                        // split a patch both Horiz and Vert giving 4 polys.
00152 
00153    PatchSplitter() { 
00154       m_flags = 0;
00155       m_maxlevel = 0; 
00156       m_isnormals = TRUE;
00157       m_straight = 6.0f;
00158       m_zoom = 1.0f;
00159       m_isvariable = TRUE;
00160       m_viewplane = 0;
00161       m_hither = -1.0f;
00162       m_iscullbackfacing = TRUE;
00163    }
00164 
00165    void Subdivide( SplitPatch &splitpatch, DWORD flatflags = 0 ) { SplitSubPatch( splitpatch, 0, flatflags ); }
00166    virtual void SubdivideCallback(SplitPatch &patch)=0;
00167    float Flatness( Vector &p0, Vector &p1, Vector &p2, Vector &p3 );
00168    float FlatnessFirst( Vector &p0, Vector &p1, Vector &p2, Vector &p3);
00169 
00170 private:
00171    void SplitSubPatch( SplitPatch &patch, int level, LONG flatflags );
00172    void SubSplitHorizontal( SplitPatch &patch, int level, LONG flatflags );
00173    void SubSplitVertical( SplitPatch &patch, int level, LONG flatflags );
00174 };
00175 
00176 inline void CalcTangent( Vector &p0, Vector &p1, Vector &p2, Vector &p3, Vector &t )
00177 {
00178    t = .75 * (-p0 - p1 + p2 + p3);
00179 }
00180 
00181 inline float PatchSplitter::Flatness( Vector &p0, Vector &p1, Vector &p2, Vector &p3 )
00182 {
00183    float screenzoom;
00184    if (m_viewplane) {
00185       float closesz = min(m_hither, max(p0.z, max(p1.z, max(p2.z, p3.z))));
00186       screenzoom = m_zoom * m_viewplane/closesz;
00187    }
00188    else
00189       screenzoom = m_zoom;
00190 
00191    Vector height;
00192    height.x = 3*(p0.x - p1.x - p2.x + p3.x);
00193    height.y = 3*(p0.y - p1.y - p2.y + p3.y);
00194    height.z = 3*(p0.z - p1.z - p2.z + p3.z);
00195 
00196    return height.Norm() * screenzoom;
00197 }
00198 
00199 inline float PatchSplitter::FlatnessFirst( Vector &p0, Vector &p1, Vector &p2, Vector &p3)
00200 {
00201    float screenzoom;
00202    if (m_viewplane) {
00203       float closesz = min(m_hither, max(p0.z, max(p1.z, max(p2.z, p3.z))));
00204       screenzoom = m_zoom * m_viewplane/closesz;
00205    }
00206    else
00207       screenzoom = m_zoom;
00208 
00209    Vector temp;
00210    temp.x = 4*p0.x - 6*p1.x + 2*p3.x; // at 1/3
00211    temp.y = 4*p0.y - 6*p1.y + 2*p3.y; // at 1/3
00212    temp.z = 4*p0.z - 6*p1.z + 2*p3.z; // at 1/3
00213 
00214    float height;
00215    if ((height = temp.Norm() * screenzoom) > m_straight)
00216       return height;
00217 
00218    temp.x = 2*p0.x - 6*p2.x + 4*p3.x; // at 2/3
00219    temp.y = 2*p0.y - 6*p2.y + 4*p3.y; // at 2/3
00220    temp.z = 2*p0.z - 6*p2.z + 4*p3.z; // at 2/3
00221    return temp.Norm() * screenzoom;
00222 }
00223 
00224 inline void MakeFlat( Vector &p0, Vector &p1, Vector &p2, Vector &p3 )
00225 {
00226    float length;
00227 
00228    Vector delta = p3;
00229    delta -= p0;
00230    
00231    if ((length = delta.Norm()) == 0) {
00232       p1 = p0;
00233       p2 = p3;
00234       return;
00235    }
00236    delta /= length;
00237    p1 -= p0;
00238    p2 -= p3;
00239    p1 = p0+ delta * p1.Norm();
00240    p2 = p3+ delta * -p2.Norm();
00241 }
00242 
00243 inline void MakeFlat5( Vector &p0, Vector &p1, Vector &p2, Vector &p3, Vector &p4, Vector &p5, Vector &p6, Vector &p7)
00244 {
00245    float length;
00246 
00247    Vector delta = p7;
00248    delta -= p0;
00249    
00250    if ((length = delta.Norm()) == 0) {
00251       p1 = p0;
00252       p2 = p0;
00253       p3 = p0;
00254       p4 = p3;
00255       p5 = p7;
00256       p6 = p7;
00257       return;
00258    }
00259    delta /= length;
00260    p1 -= p0;
00261    p2 -= p0;
00262    p3 -= p0;
00263 
00264    p5 -= p7;
00265    p6 -= p7;
00266    p1 = p0 + delta * p1.Norm();
00267    p2 = p0 + delta * p2.Norm();
00268    p3 = p0 + delta * p3.Norm();
00269    p4 = p3;
00270    p5 = p7 + delta * -p5.Norm();
00271    p6 = p7 + delta * -p6.Norm();
00272 }
00273 
00274 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
