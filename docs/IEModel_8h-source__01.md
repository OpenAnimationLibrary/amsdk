array;
00429 public:
00430    HashArray <TYPE, ARG_TYPE> m_array;
00431    
00432    LONG  Add(ARG_TYPE newelement, LONG key=-1);
00433    LONG  AddForce(ARG_TYPE newelement);
00434    LONG  LookUp(ARG_TYPE newelement, LONG key=-1);
00435    TYPE *GetArray() { return m_array.GetArray(); }
00436    TYPE  GetAt(int index) const { return m_array.GetAt(index); }
00437    TYPE &ElementAt(int index) { return m_array.ElementAt(index); }
00438    int   GetSize() const { return m_array.GetSize(); }
00439    void  SetSize( int newsize, int growby = -1 ) { m_array.SetSize(newsize, growby); m_keyarray.SetSize(newsize, growby); }
00440    TYPE  operator [] ( int index ) const { return m_array.GetAt(index); }
00441    TYPE &operator [](int index) { return m_array.ElementAt(index); }
00442 
00443    void SetGranularity(int granularity) { 
00444       m_keyarray.SetGranularity(granularity);
00445       m_array.SetGranularity(granularity);
00446    }
00447 
00448    void Shrink() {
00449       m_keyarray.FreeExtra();
00450       m_array.FreeExtra();
00451    }
00452 };
00453 
00454 template <class TYPE, class ARG_TYPE>
00455 inline LONG UDCollection<TYPE, ARG_TYPE>::Add(ARG_TYPE newelement, LONG key)
00456 {
00457    int count = m_array.GetSize();
00458    for (int i=0; i<count; i++) {
00459       if (key!=-1 && m_keyarray.GetAt(i)!=-1) {
00460          if (m_keyarray.GetAt(i) == key)
00461             return i;
00462       }
00463       else {
00464          if (m_array.GetAt(i) == newelement)
00465             return i;
00466       }
00467    }
00468    
00469    m_keyarray.Add(key);
00470    return m_array.Add(newelement);
00471 }
00472 
00473 template <class TYPE, class ARG_TYPE>
00474 inline LONG UDCollection<TYPE, ARG_TYPE>::AddForce(ARG_TYPE newelement)
00475 {
00476    m_keyarray.Add(-1);
00477    return m_array.Add(newelement);
00478 }
00479 
00480 template <class TYPE, class ARG_TYPE>
00481 inline LONG UDCollection<TYPE, ARG_TYPE>::LookUp(ARG_TYPE newelement, LONG key)
00482 {
00483    int count = m_array.GetSize();
00484    for (int i=0; i<count; i++) {
00485       if (key!=-1 && m_keyarray.GetAt(i)!=-1) {
00486          if (m_keyarray.GetAt(i) == key)
00487             return i;
00488       }
00489       else {
00490          if (m_array.GetAt(i) == newelement)
00491             return i;
00492       }
00493    }
00494    return -1;
00495 }
00496 
00497 //*******************************************************
00498 
00499 class RenderInfo;
00500 
00501 class IEModel 
00502 {
00503 public:
00504    VectorCollection m_vertexlist;
00505    UDCollection<IEMap, IEMap &> m_maplist;
00506    UDCollection<Attr, Attr &> m_attrlist;
00507    
00508    IEBone *m_bonehead;
00509    
00510    IEModel() {
00511       m_bonehead = NULL;
00512       m_maplist.SetGranularity(20);
00513       m_attrlist.SetGranularity(20);
00514    }
00515    
00516    virtual ~IEModel() {
00517       DeleteBoneBranch(m_bonehead);       
00518    }
00519    void DeleteBoneBranch(IEBone *bone);
00520    void Draw( RenderInfo *renderinfo );
00521    Vector *GetVertexArray() { return m_vertexlist.GetArray(); }
00522    Vector &GetVertex( int i ) { return m_vertexlist[i]; }
00523 };
00524 
00525 inline void IEModel::DeleteBoneBranch(IEBone *startbone) 
00526 {
00527    IEBone *sibling, *bone;
00528    
00529    for (bone=startbone; bone; bone=sibling) {
00530       sibling = bone->m_sibling;
00531       if (bone->m_child)
00532          DeleteBoneBranch(bone->m_child);
00533       delete bone;
00534    }   
00535 }
00536 
00537 class IEColor
00538 {
00539 public:
00540    BYTE m_red, m_green, m_blue, m_alpha;
00541    
00542    IEColor()
00543    {
00544       m_red = m_green = m_blue = m_alpha = 0;
00545    }
00546    
00547    IEColor(BYTE red, BYTE green, BYTE blue, BYTE alpha) {
00548       m_red   = red;
00549       m_green = green;
00550       m_blue  = blue;
00551       m_alpha = alpha;
00552    }
00553 };
00554    
00555 class IEPolyModel : public IEModel
00556 {
00557 public:
00558    HashArray<IEPoly *, IEPoly *> m_polyarray;  // this crazy array should definitely be an array of poly's, not an array of pointers to poly's, overworked allocator... pointless
00559    VectorCollection m_normallist;
00560    
00561    IEPolyModel() {
00562       m_polyarray.SetGranularity(1000);
00563    }
00564    IEPolyModel(const IEPolyModel &other)
00565    {
00566       m_polyarray.SetGranularity(1000);
00567       *this = other;
00568    }
00569    IEPolyModel &operator = (const IEPolyModel &other)
00570    {
00571       SetNumVerts(other.GetNumVerts());
00572       int i;
00573       for (i=0; i<GetNumVerts(); i++)
00574          m_vertexlist[i] = other.m_vertexlist[i];
00575 
00576       SetNumFaces(other.GetNumFaces());
00577       for (i=0; i<GetNumFaces(); i++) {
00578          IEPoly &poly = *other.m_polyarray[i];
00579          m_polyarray[i]->SetVerts(poly.m_vertexid[0], poly.m_vertexid[1], poly.m_vertexid[2], poly.m_vertexid[3]);
00580       }
00581       return *this;
00582    }
00583    virtual ~IEPolyModel()
00584    {
00585       FreeData();
00586    }
00587    void FreeData()
00588    {
00589       for (int i=0;i < m_polyarray.GetSize(); i++)
00590          delete m_polyarray[i];
00591    }
00592    PLUGINEXPORT void BuildNormalList( float angletolerance ); // 0-180
00593    PLUGINEXPORT void BuildNormalList();                       // same as 180 above, but much faster, always one normal per vertex
00594 
00595    int GetNumVerts() const 
00596    {
00597       return m_vertexlist.GetSize();
00598    }
00599    void SetNumVerts( int i )
00600    {
00601       m_vertexlist.SetSize( i );
00602    }
00603    int GetNumFaces() const
00604    {
00605       return m_polyarray.GetSize();
00606    }
00607    void SetNumFaces( int numfaces )
00608    {
00609       m_polyarray.SetSize( numfaces );     // it seems crazy that m_polyarray is not an array of IEPolys, but rather an array of pointers to IEPolys ??
00610       for (int i=0; i<numfaces; i++)
00611          m_polyarray[i] = new IEPoly;
00612    }
00613    int GetNumNormals() const
00614    {
00615       return m_normallist.GetSize();
00616    }
00617    void SetNumNormals( int i )
00618    {
00619       m_normallist.SetSize( i );
00620    }
00621 
00622    // for Vlado's EdgeLister
00623    int getNumVerts() { return GetNumVerts(); }
00624    int getNumFaces() { return GetNumFaces(); }
00625    int getFaceVertex(int face, int v) { return m_polyarray[face]->m_vertexid[v]; }
00626 };
00627 
00628 /*
00629 // for vlado's EdgeLister
00630 struct EdgeData {
00631    int v[2]; // The two vertices
00632    int f[2]; // The two faces
00633    int i[2]; // Indices of the edge in the faces
00634    int tv[2]; // The opposite vertices
00635    int numFaces;
00636 };
00637 */
00638 
00639 class PLUGINEXPORT IETriModel : public IEPolyModel
00640 {
00641 public:
00642    HashArray<IEPoly, IEPoly &> m_polyclassarray;  // this is an array of actual IEPoly classes, we initialize all the pointers in the base class m_polyarray to point at these
00643    HashArray<IEEdge, IEEdge &> m_edges;
00644    int *m_edgeindex;  // an array of edge indexes, these would be more easily stored in 3 in each Triangle, but we are using IEPoly which cannot be invalidated
00645 
00646    IETriModel() 
00647    {
00648       Init();
00649    }
00650    IETriModel(const IETriModel &other)
00651    {
00652       Init();
00653       *this = other;
00654    }
00655    IETriModel & operator = (const IETriModel &other)
00656    { 
00657       int i;
00658       SetNumVerts(other.GetNumVerts());
00659       for (i=0; i<GetNumVerts(); i++)
00660          m_vertexlist[i] = other.m_vertexlist[i];
00661       SetNumFaces(other.GetNumFaces());
00662       for (i=0; i<GetNumFaces(); i++)
00663          m_polyarray[i] = other.m_polyarray[i];
00664       SetNumEdges(other.GetNumEdges());
00665       for (i=0; i<GetNumEdges(); i++)
00666          m_edges[i] = other.m_edges[i];
00667       return *this;
00668    }
00669    virtual ~IETriModel();
00670    void FreeData()
00671    {
00672       m_edges.RemoveAll();
00673       if (m_edgeindex)
00674          delete [] m_edgeindex;
00675       m_edgeindex = NULL;
00676    }
00677    void Init()
00678    {
00679       m_polyarray.SetGranularity(1000);
00680       m_edges.RemoveAll();
00681       m_edgeindex = NULL;
00682    }
00683 
00684    void SetNumEdges( int i )
00685    {
00686       m_edges.SetSize( i );
00687    }
00688    int GetNumEdges() const
00689    {
00690       return m_edges.GetSize();
00691    }
00692    void SetNumFaces( int numfaces )  // override the IEPoly version, not virtual
00693    {
00694       m_polyarray.SetSize( numfaces );  // this one is pointers
00695       m_polyclassarray.SetSize( numfaces );
00696       for (int i=0; i<numfaces; i++)
00697          m_polyarray[i] = &m_polyclassarray[i];
00698    }
00699    void BuildEdges(BOOL deleteold=TRUE);
00700 
00701    friend PLUGINEXPORT void Triangulate( const IEPolyModel &mesh, IETriModel &tmesh );
00702    friend PLUGINEXPORT void LoopSubdivideStep( const IETriModel &mesh, IETriModel &smesh );
00703    friend PLUGINEXPORT void LoopSubdivide( IETriModel &mesh, IETriModel &smesh, int numSteps );
00704 
00705    // for Vlado's EdgeLister
00706    void setNumEdges(int numEdges) { SetNumEdges(numEdges); }
00707 /*
00708    void setEdge(int idx, EdgeData &edge) {
00709       IEEdge &ieedge = m_edges[idx];
00710       ieedge.m_vertexid[0]      = edge.v[0];
00711       ieedge.m_vertexid[1]      = edge.v[1];
00712       ieedge.m_numfaces         = edge.numFaces;
00713       ieedge.m_polyid[0]        = edge.f[0];
00714       ieedge.m_polyid[1]        = edge.f[1];
00715       ieedge.m_polyvertexnum[0] = edge.i[0];
00716       ieedge.m_polyvertexnum[1] = edge.i[1];
00717       ieedge.m_thirdvertex[0]   = edge.tv[0];
00718       ieedge.m_thirdvertex[1]   = edge.tv[1];
00719    }
00720 */
00721 };
00722 
00723 class IEPatchModel : public IEModel
00724 {
00725 public:
00726    HashArray<IEPatch *, IEPatch *> m_patcharray;
00727    VectorCollection m_controlvertexlist;
00728 
00729    IEPatchModel() {
00730       m_patcharray.SetGranularity(1000);
00731    }
00732 
00733    virtual ~IEPatchModel() {
00734       for (int i=0;i < m_patcharray.GetSize(); i++) {
00735          IEPatch *patch = m_patcharray.ElementAt(i);
00736          delete patch;
00737       }
00738    }
00739 };
00740 
00741 class IEModelParms
00742 {
00743 public:
00744    MapLimit m_minmodelmapsize, m_maxmodelmapsize, 
00745     m_unused1, m_unused2;
00746    union { 
00747       unsigned long  m_flags;
00748       struct {
00749          unsigned long m_isbuildmaparray        : 1,
00750                        m_isbuildattrarray       : 1,
00751                        m_isbuildbonelist        : 1,
00752                        m_isbuildmodelmap        : 1,
00753                        m_isdisplaypercentbar    : 1,
00754                        m_useconsistentids       : 1,
00755                        m_isnormalizeuvs         : 1;
00756        };
00757    };
00758    
00759    IEModelParms() {
00760       m_flags = 0L;
00761       m_minmodelmapsize  = ML_0;
00762       m_maxmodelmapsize  = ML_256;
00763       m_isdisplaypercentbar = TRUE;
00764    }
00765 };
00766 
00767 enum SubType { ST_1, ST_4, ST_16, ST_VARIABLE, SUBTYPE_COUNT };
00768 
00769 class IEPolyModelParms : public IEModelParms
00770 {
00771 public:
00772    SubType  m_subtype;
00773 
00774    union { 
00775       unsigned long m_polyflags;
00776       struct {
00777          unsigned long m_isbuildnormalarray : 1;
00778        };
00779    };
00780 
00781    IEPolyModelParms() {
00782       m_polyflags = 0L;
00783       m_subtype = ST_1;
00784    }
00785    IEPolyModelParms( SubType subdivisiontype, BOOL buildnormals ) {
00786       m_isbuildnormalarray = buildnormals;
00787       m_subtype = subdivisiontype;
00788    }
00789 };
00790 
00791 class HGroup;
00792 class HCP;
00793 
00794 class VertexInfo 
00795 {
00796 public:
00797    HashArray<HPatch *, HPatch *>          m_patcharray;    // the patch each vertex came from
00798    HashArray<Vector2, Vector2>            m_uvarray;       // the uv on that patch for each vertex
00799    HashArray<HCP *, HCP *>                m_cparray;       // the cp associated with the vertex, only if at a patch corner
00800 
00801 // computed and used only by cloth plugin - these should be moved to plugin local storage
00802    HashArray<HGroup *, HGroup *>          m_grouparray;    // the custom group whose properties will control the behavior of the vertex
00803    HashArray<char, char>                  m_attachedarray; // a bool indicating whether the vertex is attached
00804 
00805    void RemoveAll()
00806    {
00807       m_patcharray.RemoveAll();
00808       m_uvarray.RemoveAll();
00809       m_cparray.RemoveAll();
00810 
00811       m_grouparray.RemoveAll();
00812       m_attachedarray.RemoveAll();
00813    }
00814 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
