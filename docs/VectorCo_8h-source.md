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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# VectorCo.h

[Go to the documentation of this file.](VectorCo_8h.md)

<div class="fragment">

``` fragment
00001 //
00002 
00003 #include <AfxTempl.h>
00004 
00005 class HashNode 
00006 {
00007 public:
00008    HashNode *m_next;
00009    int       m_id;
00010    LONG      m_key;
00011 };
00012 
00013 class VectorCollection 
00014 {
00015 private:
00016    CArray<HashNode *, HashNode *> m_hasharray;
00017 
00018    int GetHashKey(LONG key);
00019    int GetHashKey(const Vector &vector);
00020 public:
00021    CArray<Vector, Vector &> m_array;
00022 
00023    VectorCollection() {
00024       m_array.SetGranularity(1000);
00025       m_hasharray.SetSize(1999);
00026    }   
00027    
00028    virtual ~VectorCollection();
00029    
00030    int GetSize() const { return m_array.GetSize(); }
00031    void SetSize( int newsize, int growby = -1 ) { m_array.SetSize(newsize, growby); } 
00032    int Add(Vector &vector, LONG key=-1);
00033    int LookUp(const Vector &vector, LONG key=-1);
00034    int LookUpHashKey(Vector &vector);
00035    void Empty();
00036 
00037    void Shrink() {
00038       m_array.FreeExtra();
00039    }
00040 
00041    Vector *GetArray() { return m_array.GetArray(); }
00042    Vector  GetAt(int index) const { return m_array.GetAt(index); }
00043    Vector &ElementAt(int index) { return m_array.ElementAt(index); }
00044    Vector  operator [] ( int index ) const { return m_array.GetAt(index); }
00045    Vector &operator [](int index) { return m_array.ElementAt(index); }
00046 
00047 };
00048 
00049 inline void VectorCollection::Empty()
00050 {
00051    int i, count = m_hasharray.GetSize();
00052    for (i=0; i < count; i++) {
00053       HashNode *nodehead = m_hasharray[i];
00054       if (nodehead) {
00055          HashNode *next;
00056          for (HashNode *node = nodehead; node; node=next) {
00057             next = node->m_next;
00058             delete node;
00059          }
00060          m_hasharray[i] = NULL;
00061       }
00062    }
00063    m_array.SetSize(0);
00064 }
00065 
00066 inline VectorCollection::~VectorCollection()
00067 {
00068    Empty();
00069 }
00070 
00071 inline int VectorCollection::GetHashKey(LONG key)
00072 {
00073    return ((int)(void*)(LONG)key) >> 4;
00074 }
00075 
00076 inline int VectorCollection::GetHashKey(const Vector &vector)
00077 {
00078    double x = (int)(vector.x * 1000.0f + SIGN(vector.x) * .5f)/1000.0*12.3;
00079    double y = (int)(vector.y * 1000.0f + SIGN(vector.y) * .5f)/1000.0*23.4;
00080    double z = (int)(vector.z * 1000.0f + SIGN(vector.z) * .5f)/1000.0*34.5;
00081    return (int) (pow(x*x + y*y + z*z, 0.5 ) * 9.87);  
00082 }
00083 
00084 inline int VectorCollection::LookUp(const Vector &vector, LONG key)
00085 {
00086    int hashkey;
00087    if (key == -1)
00088       hashkey = GetHashKey(vector);
00089    else
00090       hashkey = GetHashKey(key);
00091 
00092    int index = hashkey%m_hasharray.GetSize();   
00093    HashNode *nodehead = m_hasharray.GetAt(index);
00094    for (HashNode *node = nodehead; node; node=node->m_next) {
00095       if (key != -1 && node->m_key != -1) {
00096          if (node->m_key == key)
00097             return node->m_id;
00098          continue;
00099       }
00100       const Vector &match = m_array.GetAt(node->m_id);
00101       Vector diff = match-vector;
00102       if (fabs(diff.x) < 1.e-3 &&
00103        fabs(diff.y) < 1.e-3 &&
00104        fabs(diff.z) < 1.e-3)
00105          return node->m_id;
00106    }
00107    return -1;
00108 }
00109 
00110 inline int VectorCollection::LookUpHashKey(Vector &vector)
00111 {
00112    int i, count = m_hasharray.GetSize();
00113    for (i = 0; i < count; i++) {
00114       HashNode *nodehead = m_hasharray.GetAt(i);
00115       if (nodehead) {
00116          for (HashNode *node = nodehead; node; node=node->m_next) {
00117             const Vector &match = m_array.GetAt(node->m_id);
00118             Vector diff = match-vector;
00119             if (fabs(diff.x) < 1.e-3 &&
00120                fabs(diff.y) < 1.e-3 &&
00121                fabs(diff.z) < 1.e-3)
00122                return node->m_key;
00123          }
00124       }
00125    }
00126    return -1;
00127 }
00128 
00129 inline int VectorCollection::Add(Vector &vector, LONG key)
00130 {
00131    int hashkey;
00132    if (key == -1)
00133       hashkey = GetHashKey(vector);
00134    else
00135       hashkey = GetHashKey(key);
00136 
00137    int index = hashkey%m_hasharray.GetSize();   
00138    HashNode *nodehead = m_hasharray.GetAt(index);
00139    for (HashNode *node = nodehead; node; node=node->m_next) {
00140       if (key != -1 && node->m_key != -1) {
00141          if (node->m_key == key)
00142             return node->m_id;
00143          continue;
00144       }
00145       const Vector &match = m_array.GetAt(node->m_id);
00146       Vector diff = match-vector;
00147       if (fabs(diff.x) < 1.e-3 &&
00148        fabs(diff.y) < 1.e-3 &&
00149        fabs(diff.z) < 1.e-3)
00150          return node->m_id;
00151    }
00152 // doesn't exist yet
00153    int newid = m_array.Add(vector);
00154    HashNode *newnode = new HashNode;
00155    newnode->m_id = newid;
00156    newnode->m_key = key;
00157    newnode->m_next = nodehead;
00158    m_hasharray.SetAt(index, newnode);
00159    return newid;
00160 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
