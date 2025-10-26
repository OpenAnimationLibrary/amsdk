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

# IEModel.h

[Go to the documentation of this file.](IEModel_8h.md)

<div class="fragment">

``` fragment
00001 // BC  6/6/2005  \Master120\Include\IEModel.h
00002 
00003 #define __IEMODEL_H
00004 
00005 #ifndef __VECTOR2_H
00006 #include "Vector2.h"
00007 #endif
00008 #ifndef __VECTOR_H
00009 #include "Vector.h"
00010 #endif
00011 #ifndef __HASHARRA_H
00012 #include "HashArra.h"
00013 #endif
00014 #ifndef __MAPLIMIT_H
00015 #include "MapLimit.h"
00016 #endif
00017 #ifndef __EXPORTS_H
00018 #include "Exports.h"
00019 #endif
00020 #ifndef __OLDATTR_H
00021 #include "OldAttr.h"
00022 #endif
00023 
00024 #define SIGN(x) ((x) >= 0 ? 1 : -1)
00025 #define IEVERSION 3
00026 
00027 class HPatch;
00028 
00029 class IEMap 
00030 {
00031 public:
00032    char    m_filename[256];
00033    WORD    m_width, m_height;
00034 
00035    IEMap &operator = ( const IEMap &other ) {
00036       strcpy(m_filename, other.m_filename);
00037       m_width = other.m_width;
00038       m_height = other.m_height;
00039       return *this;
00040    }
00041    
00042    int operator == ( const IEMap &other ) const 
00043    { 
00044       return !strcmp(m_filename, other.m_filename);
00045    }
00046 };
00047 
00048 class IEMapNode 
00049 {
00050 public:
00051    enum { COLORMAP,             TRANSPARENCYMAP,  BUMPMAP,      SPECULARSIZEMAP, DIFFUSEMAP,
00052           MIRRORMAP,            AMBIANCEMAP,      COOKIECUTMAP, DISPLACEMENTMAP, FRACTALMAP,
00053           SPECULARINTENSITYMAP, NEXTMAPFACTORMAP, OTHERMAP,     NORMALMAP/*,       TANGENTMAP*/ };
00054 
00055    LONG    m_mapid;
00056    float   m_percent;
00057    Vector2 m_repeat;
00058    Vector2 m_uv[4];
00059 
00060    union { 
00061       DWORD  m_flags;
00062       struct {
00063          DWORD m_kind         : 4,
00064                m_isseamless   : 1,
00065                m_isgroupdecal : 1;
00066       };
00067    };
00068 
00069    IEMapNode() {
00070       m_repeat.Set(1.0f,1.0f);
00071       m_percent = 1.0f;
00072       m_flags = 0L;
00073       m_kind = COLORMAP;
00074    }
00075 
00076    IEMapNode &operator = ( const IEMapNode &other ) {
00077       m_mapid = other.m_mapid;
00078       m_repeat = other.m_repeat;
00079       m_percent = other.m_percent;
00080       m_flags = other.m_flags;
00081       m_uv[0] = other.m_uv[0];
00082       m_uv[1] = other.m_uv[1];
00083       m_uv[2] = other.m_uv[2];
00084       m_uv[3] = other.m_uv[3];
00085       return *this;
00086    }
00087 };
00088 
00089 class IEPatchMapNode : public IEMapNode
00090 {
00091 public:
00092    Vector2 m_controluv[8]; // 8 corner control vertices
00093 /*    *01*
00094       2**3
00095       4**5
00096       *67*
00097 */
00098 
00099    IEPatchMapNode &operator = ( const IEPatchMapNode &other ) {
00100       *((IEMapNode *)this) = other;
00101       m_controluv[0]  = other.m_controluv[0];
00102       m_controluv[1]  = other.m_controluv[1];
00103       m_controluv[2]  = other.m_controluv[2];
00104       m_controluv[3]  = other.m_controluv[3];
00105       m_controluv[4]  = other.m_controluv[4];
00106       m_controluv[5]  = other.m_controluv[5];
00107       m_controluv[6]  = other.m_controluv[6];
00108       m_controluv[7]  = other.m_controluv[7];
00109       return *this;
00110    }
00111 };
00112 
00113 class IEPoly 
00114 {
00115 public:
00116    HashArray<IEMapNode *, IEMapNode *>m_mapnodearray;
00117    LONG       m_attrid;
00118    LONG       m_vertexid[4];
00119    LONG       m_normalid[4];
00120    HPatch    *m_origpatch;
00121    
00122    IEPoly()
00123    {
00124       Init();
00125    }
00126    IEPoly(HPatch *patch) { 
00127       m_mapnodearray.SetGranularity(5);
00128       m_attrid = -1;
00129       m_origpatch = patch;
00130    }
00131    virtual ~IEPoly() {
00132       for (int i=0;i < m_mapnodearray.GetSize(); i++) {
00133          IEMapNode *mapnode = m_mapnodearray.ElementAt(i);
00134          delete mapnode;
00135       }
00136    }
00137 
00138    void Init()
00139    {
00140       m_mapnodearray.SetGranularity(5);
00141       m_attrid = -1;
00142       for (int i=0; i<4; i++) {
00143          m_vertexid[i] = 0;
00144          m_normalid[i] = 0;
00145       }
00146       m_origpatch = NULL;
00147    }
00148    IEPoly &operator = ( const IEPoly &other )
00149    {
00150       m_mapnodearray.SetSize( other.m_mapnodearray.GetSize());
00151       for (int i=0; i<m_mapnodearray.GetSize(); i++)
00152          m_mapnodearray[i] = other.m_mapnodearray[i];
00153       SetVerts(other.m_vertexid[0], other.m_vertexid[1], other.m_vertexid[2], other.m_vertexid[3]);
00154       m_normalid[0] = other.m_normalid[0];
00155       m_normalid[1] = other.m_normalid[1];
00156       m_normalid[2] = other.m_normalid[2];
00157       m_normalid[3] = other.m_normalid[3];
00158       m_origpatch = other.m_origpatch;
00159       return *this;
00160    }
00161    void SetVerts( int v0, int v1, int v2 )
00162    {
00163       m_vertexid[0] = v0;
00164       m_vertexid[1] = v1;
00165       m_vertexid[2] = v2;
00166       m_vertexid[3] = v2;
00167    }
00168    void SetVerts( int v0, int v1, int v2, int v3 )
00169    {
00170       m_vertexid[0] = v0;
00171       m_vertexid[1] = v1;
00172       m_vertexid[2] = v2;
00173       m_vertexid[3] = v3;
00174    }
00175    BOOL IsTri() { return m_vertexid[0] == m_vertexid[3]; }
00176    BOOL IsQuad() { return !IsTri(); }
00177 };
00178 
00179 class IEEdge 
00180 {
00181 public:
00182    LONG m_vertexid[2];
00183 
00184    LONG m_numfaces;         // the number of faces sharing the edge (1 or 2)                           numFaces
00185    LONG m_polyid[2];        // the faces sharing the edge                                              f[2]
00186    LONG m_polyvertexnum[2]; // the index in the faces sharing the edge (0, 1, or 2)                    fe[2]
00187    LONG m_thirdvertex[2];   // the third vertex of the faces sharing the edge ( assuming triangles )   tv[2]
00188 
00189    IEEdge()
00190    {
00191    }
00192    IEEdge(int id1, int id2) {
00193       m_vertexid[0] = id1;
00194       m_vertexid[1] = id2;
00195    }
00196    IEEdge &operator = ( const IEEdge &other )
00197    {
00198       m_vertexid[0] = other.m_vertexid[0];
00199       m_vertexid[1] = other.m_vertexid[1];
00200       m_numfaces = other.m_numfaces;
00201       m_polyid[0] = other.m_polyid[0];
00202       m_polyid[1] = other.m_polyid[1];
00203       m_polyvertexnum[0] = other.m_polyvertexnum[0];
00204       m_polyvertexnum[1] = other.m_polyvertexnum[1];
00205       m_thirdvertex[0] = other.m_thirdvertex[0];
00206       m_thirdvertex[1] = other.m_thirdvertex[1];
00207       return *this;
00208    }
00209 };
00210 
00211 // edge0 m_vertexid[0] - m_vertexid[1]
00212 // edge1 m_vertexid[1] - m_vertexid[2] 
00213 // edge2 m_vertexid[2] - m_vertexid[3]
00214 // edge3 m_vertexid[3] - m_vertexid[0]
00215 
00216 class IEPatch
00217 {
00218 public:
00219    HashArray<IEPatchMapNode *, IEPatchMapNode *>m_mapnodearray;
00220    LONG  m_attrid;
00221    LONG  m_vertexid[4];
00222    LONG  m_controlvertexid[12];
00223    HPatch *m_origpatch;
00224    union {
00225       DWORD      m_flags;
00226       struct {
00227          DWORD   m_edge0isdiscontinuous : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
00228                  m_edge1isdiscontinuous : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
00229                  m_edge2isdiscontinuous : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
00230                  m_edge3isdiscontinuous : 1, // used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
00231                  m_is3point             : 1; // m_vertexid[0] == m_vertexis[3]
00232       };
00233    };
00234    
00235    IEPatch(HPatch *patch) { 
00236       m_mapnodearray.SetGranularity(5); 
00237       m_attrid = -1;
00238       m_origpatch = patch;
00239       m_flags = 0L;
00240    }
00241    
00242    virtual ~IEPatch() {
00243       for (int i=0;i < m_mapnodearray.GetSize(); i++) {
00244          IEMapNode *mapnode = m_mapnodearray.ElementAt(i);
00245          delete mapnode;
00246       }
00247    }
00248 };
00249 
00250 class IEBone 
00251 {
00252 public:
00253    IEBone *m_child, *m_sibling;
00254    char   m_name[256];
00255  
00256  // useful only for duplicating the bone arrangment for another package or your own IK
00257  // not needed for motion if using .MOT
00258    Vector m_pivotpos, m_endpos, m_rollpos;
00259    HashArray<LONG, LONG> m_vertexidarray;
00260    
00261    IEBone() {
00262       m_child = m_sibling = NULL;
00263    }
00264 };
00265 
00266 class HashNode 
00267 {
00268 public:
00269    HashNode *m_next;
00270    int       m_id;
00271    LONG      m_key;
00272 };
00273 
00274 class VectorCollection 
00275 {
00276 private:
00277    HashArray<HashNode *, HashNode *> m_hasharray;
00278 public:
00279    HashArray<Vector, Vector &> m_array;
00280 
00281    VectorCollection() {
00282       m_array.SetGranularity(1000);
00283 //      m_hasharray.SetSize(1999);  // rather than here, now done lazily in VectorCollection::Add(). This way models that don't use Add won't have the space wasted on vertexes & normals
00284    }   
00285    
00286    virtual ~VectorCollection();
00287    
00288    Vector *GetArray() { return m_array.GetArray(); }
00289    Vector  GetAt(int index) const { return m_array.GetAt(index); }
00290    int     GetSize() const { return m_array.GetSize(); }
00291    void    SetSize( int newsize, int growby = -1 ) { m_array.SetSize(newsize, growby); } 
00292    Vector &ElementAt(int index) { return m_array.ElementAt(index); }
00293    int Add(Vector &vector, LONG key=-1);
00294    int LookUp(const Vector &vector, LONG key=-1);
00295    int LookUpHashKey(Vector &vector);
00296    int GetHashKey(LONG key);
00297    int GetHashKey(const Vector &vector);
00298    void Empty();
00299    Vector  operator [] ( int index ) const { return m_array.GetAt(index); }
00300    Vector &operator [](int index) { return m_array.ElementAt(index); }
00301 
00302    void Shrink() {
00303       m_array.FreeExtra();
00304    }
00305 };
00306 
00307 inline void VectorCollection::Empty()
00308 {
00309    int i, count = m_hasharray.GetSize();
00310    for (i=0; i < count; i++) {
00311       HashNode *nodehead = m_hasharray[i];
00312       if (nodehead) {
00313          HashNode *next;
00314          for (HashNode *node = nodehead; node; node=next) {
00315             next = node->m_next;
00316             delete node;
00317          }
00318          m_hasharray[i] = NULL;
00319       }
00320    }
00321    m_array.SetSize(0);
00322 }
00323 
00324 inline VectorCollection::~VectorCollection()
00325 {
00326    Empty();
00327 }
00328 
00329 inline int VectorCollection::GetHashKey(LONG key)
00330 {
00331    return ((int)/*(void*)*/(LONG)key) >> 4;
00332 }
00333 
00334 inline int VectorCollection::GetHashKey(const Vector &vector)
00335 {
00336    double x = (int)(vector.x * 1000.0f + SIGN(vector.x) * .5f)/1000.0*12.3;
00337    double y = (int)(vector.y * 1000.0f + SIGN(vector.y) * .5f)/1000.0*23.4;
00338    double z = (int)(vector.z * 1000.0f + SIGN(vector.z) * .5f)/1000.0*34.5;
00339    return (int) (pow(x*x + y*y + z*z, 0.5 ) * 9.87);  
00340 }
00341 
00342 inline int VectorCollection::LookUp(const Vector &vector, LONG key)
00343 {
00344    int hashkey;
00345    if (key == -1)
00346       hashkey = GetHashKey(vector);
00347    else
00348       hashkey = GetHashKey(key);
00349 
00350    int index = hashkey%m_hasharray.GetSize();   
00351    HashNode *nodehead = m_hasharray.GetAt(index);
00352    for (HashNode *node = nodehead; node; node=node->m_next) {
00353       if (key != -1 && node->m_key != -1) {
00354          if (node->m_key == key)
00355             return node->m_id;
00356          continue;
00357       }
00358       const Vector &match = m_array.GetAt(node->m_id);
00359       Vector diff = match-vector;
00360       if (fabs(diff.x) < 1.e-3 &&
00361        fabs(diff.y) < 1.e-3 &&
00362        fabs(diff.z) < 1.e-3)
00363          return node->m_id;
00364    }
00365    return -1;
00366 }
00367 
00368 inline int VectorCollection::LookUpHashKey(Vector &vector)
00369 {
00370    int i, count = m_hasharray.GetSize();
00371    for (i = 0; i < count; i++) {
00372       HashNode *nodehead = m_hasharray.GetAt(i);
00373       if (nodehead) {
00374          for (HashNode *node = nodehead; node; node=node->m_next) {
00375             const Vector &match = m_array.GetAt(node->m_id);
00376             Vector diff = match-vector;
00377             if (fabs(diff.x) < 1.e-3 &&
00378                fabs(diff.y) < 1.e-3 &&
00379                fabs(diff.z) < 1.e-3)
00380                return node->m_key;
00381          }
00382       }
00383    }
00384    return -1;
00385 }
00386 
00387 inline int VectorCollection::Add(Vector &vector, LONG key)
00388 {
00389    if (m_hasharray.GetSize()==0)
00390       m_hasharray.SetSize(1999);
00391    int hashkey;
00392    if (key == -1)
00393       hashkey = GetHashKey(vector);
00394    else
00395       hashkey = GetHashKey(key);
00396 
00397    int index = hashkey%m_hasharray.GetSize();   
00398    HashNode *nodehead = m_hasharray.GetAt(index);
00399    for (HashNode *node = nodehead; node; node=node->m_next) {
00400       if (key != -1 && node->m_key != -1) {
00401          if (node->m_key == key)
00402             return node->m_id;
00403          continue;
00404       }
00405       const Vector &match = m_array.GetAt(node->m_id);
00406       Vector diff = match-vector;
00407       if (fabs(diff.x) < 1.e-3 &&
00408        fabs(diff.y) < 1.e-3 &&
00409        fabs(diff.z) < 1.e-3)
00410          return node->m_id;
00411    }
00412 // doesn't exist yet
00413    int newid = m_array.Add(vector);
00414    HashNode *newnode = new HashNode;
00415    newnode->m_id = newid;
00416    newnode->m_key = key;
00417    newnode->m_next = nodehead;
00418    m_hasharray.SetAt(index, newnode);
00419    return newid;
00420 }
00421 
00422 //*************************** Unique Data Collection *****************************
00423 
00424 template <class TYPE, class ARG_TYPE>
00425 class UDCollection 
00426 {
00427 private:
00428    HashArray <LONG, LONG> m_key