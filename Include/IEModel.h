//BC  6/6/2005  \Master120\Include\IEModel.h
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeMemberInit
// ReSharper disable CppClangTidyModernizeUseEqualsDefault
#pragma once

#include "Vector2.h"
#include "Vector.h"
#include "HashArra.h"
#include "MapLimit.h"
#include "Exports.h"
#include "OldAttr.h"

constexpr int IEVERSION = 3;
class HPatch;

class IEMap final {
public:
    static constexpr UINT FILENAMESIZE = 256;
    char m_filename[FILENAMESIZE]{};
    WORD m_width{0};
    WORD m_height{0};

    IEMap() noexcept = default;
    ~IEMap() = default;

    IEMap(const IEMap &) = default;
    IEMap(IEMap &&) = delete;
    IEMap &operator=(IEMap &&) = delete;

    IEMap &operator=(const IEMap &other) noexcept {
        if (this == &other)
            return *this;
        strcpy_s(m_filename, _countof(m_filename), other.m_filename);
        m_width = other.m_width;
        m_height = other.m_height;
        return *this;
    }

    bool operator==(const IEMap &other) const noexcept {
        return !strcmp(m_filename, other.m_filename);
    }
};

class IEMapNode {
public:
    enum IEDecalMapType {
        COLORMAP,
        TRANSPARENCYMAP,
        BUMPMAP,
        SPECULARSIZEMAP,
        DIFFUSEMAP,
        MIRRORMAP,
        AMBIANCEMAP,
        COOKIECUTMAP,
        DISPLACEMENTMAP,
        FRACTALMAP,
        SPECULARINTENSITYMAP,
        NEXTMAPFACTORMAP,
        OTHERMAP,
        NORMALMAP
    };

    Vector2 m_uv[4]{-1.F, -1.F, -1.F, -1.F};
    Vector2 m_repeat{1.F};
    int m_mapid{-1};
    int m_mapid_parent{-1};
    float m_percent{1.F};

// @formatter:off
    union {
        BITFIELDS8 m_IEMapNode_flags{0}; //m_kind = COLORMAP;
        struct {
            BITFIELDS8 m_kind : 4,//
            m_isseamless : 1,//
            m_isgroupdecal : 1;//
        };
    };
    // @formatter:on

    IEMapNode() noexcept = default;
    virtual ~IEMapNode() = default;

    IEMapNode &operator=(const IEMapNode &other) noexcept {
        if (this == &other)
            return *this;
        m_mapid = other.m_mapid;
        m_mapid_parent = other.m_mapid_parent;
        m_repeat = other.m_repeat;
        m_percent = other.m_percent;
        m_IEMapNode_flags = other.m_IEMapNode_flags;
        m_uv[0] = other.m_uv[0];
        m_uv[1] = other.m_uv[1];
        m_uv[2] = other.m_uv[2];
        m_uv[3] = other.m_uv[3];
        return *this;
    }

    IEMapNode(const IEMapNode &other) noexcept {
        ASSERT(false);
        m_mapid = other.m_mapid;
        m_mapid_parent = other.m_mapid_parent;
        m_repeat = other.m_repeat;
        m_percent = other.m_percent;
        m_IEMapNode_flags = other.m_IEMapNode_flags;
        m_uv[0] = other.m_uv[0];
        m_uv[1] = other.m_uv[1];
        m_uv[2] = other.m_uv[2];
        m_uv[3] = other.m_uv[3];
    }

    IEMapNode(IEMapNode &&other) noexcept {
        ASSERT(false);
        m_mapid = other.m_mapid;
        m_mapid_parent = other.m_mapid_parent;
        m_repeat = other.m_repeat;
        m_percent = other.m_percent;
        m_IEMapNode_flags = other.m_IEMapNode_flags;
        m_uv[0] = other.m_uv[0];
        m_uv[1] = other.m_uv[1];
        m_uv[2] = other.m_uv[2];
        m_uv[3] = other.m_uv[3];
    }

    //    IEMapNode(IEMapNode &&) = delete;
    //    IEMapNode &operator=(IEMapNode &&) = delete;
    IEMapNode &operator=(IEMapNode &&other) noexcept {
        if (this == &other)
            return *this;
        m_mapid = other.m_mapid;
        m_mapid_parent = other.m_mapid_parent;
        m_repeat = other.m_repeat;
        m_percent = other.m_percent;
        m_IEMapNode_flags = other.m_IEMapNode_flags;
        m_uv[0] = other.m_uv[0];
        m_uv[1] = other.m_uv[1];
        m_uv[2] = other.m_uv[2];
        m_uv[3] = other.m_uv[3];
        return *this;
    }
};

class IEPatchMapNode final : public IEMapNode {
public:
    Vector2 m_controluv[8]; //8 corner control vertices
    /*    *01*
          2**3
          4**5
          *67*
    */
    IEPatchMapNode() noexcept = default;
    ~IEPatchMapNode() override = default;

    IEPatchMapNode &operator=(const IEPatchMapNode &other) noexcept {
        if (this == &other)
            return *this;
        m_mapid = other.m_mapid;
        m_mapid_parent = other.m_mapid_parent;
        m_repeat = other.m_repeat;
        m_percent = other.m_percent;
        m_IEMapNode_flags = other.m_IEMapNode_flags;
        m_uv[0] = other.m_uv[0];
        m_uv[1] = other.m_uv[1];
        m_uv[2] = other.m_uv[2];
        m_uv[3] = other.m_uv[3];
        m_controluv[0] = other.m_controluv[0];
        m_controluv[1] = other.m_controluv[1];
        m_controluv[2] = other.m_controluv[2];
        m_controluv[3] = other.m_controluv[3];
        m_controluv[4] = other.m_controluv[4];
        m_controluv[5] = other.m_controluv[5];
        m_controluv[6] = other.m_controluv[6];
        m_controluv[7] = other.m_controluv[7];
        return *this;
    }

    IEPatchMapNode(const IEPatchMapNode &) = delete;
    IEPatchMapNode(IEPatchMapNode &&) = delete;
    IEPatchMapNode &operator=(IEPatchMapNode &&) = delete;
};

class IEPoly final {
public:
    HashArray<IEMapNode *, IEMapNode *> m_mapnodearray;
    int m_vertexid[4]{-1, -1, -1, -1};
    int m_normalid[4]{-1, -1, -1, -1};
    int m_uvid[4]{-1, -1, -1, -1};
    int m_attrid{-1};
    HPatch *m_origpatch{nullptr};
    bool m_istriangle{false};

#ifdef _MEMDEBUG
    void *operator new(size_t size, char *file, const int line) noexcept {
        return ALLOCPOLY(size, file, line);
    }
    void *operator new[](size_t size, char *file, const int line) {
        return ALLOCPOLY(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocPoly(size);
    }

    void *operator new[](const size_t size) noexcept {
        return AllocPoly(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreePoly(ptr);
    }

    void operator delete[](void *ptr) noexcept {
        FreePoly(ptr);
    }

    IEPoly() noexcept = default;

    explicit IEPoly(HPatch *patch) noexcept : m_origpatch(patch) {}
    //for marching cubes
    IEPoly(const int v1, const int v2, const int v3) noexcept {
        m_vertexid[0] = v1;
        m_vertexid[1] = v2;
        m_vertexid[2] = v3;
        m_vertexid[3] = v1;
        m_normalid[0] = 0;
        m_normalid[1] = 0;
        m_normalid[2] = 0;
        m_normalid[3] = 0;
    }

    ~IEPoly() {
        for (int i = 0; i < m_mapnodearray.GetSize(); ++i) {
            const IEMapNode *mapnode = m_mapnodearray.ElementAt(i);
            delete mapnode;
        }
        m_mapnodearray.RemoveAll();
    }

    IEPoly(const IEPoly &) = delete;
    IEPoly(IEPoly &&) = delete;
    IEPoly &operator=(IEPoly &&) = delete;

    void Init() noexcept {
        m_attrid = -1;
        for (int i = 0; i < 4; ++i) {
            m_vertexid[i] = -1;
            m_normalid[i] = -1;
            m_uvid[i] = -1;
        }
        m_origpatch = nullptr;
        m_istriangle = false;
    }

    IEPoly &operator=(const IEPoly &other) noexcept {
        if (this == &other)
            return *this;
        m_mapnodearray.SetSize(other.m_mapnodearray.GetSize());
        for (int i = 0; i < m_mapnodearray.GetSize(); ++i) {
            m_mapnodearray[i] = other.m_mapnodearray[i];
        }
        m_vertexid[0] = other.m_vertexid[0];
        m_vertexid[1] = other.m_vertexid[1];
        m_vertexid[2] = other.m_vertexid[2];
        m_vertexid[3] = other.m_vertexid[3];
        m_normalid[0] = other.m_normalid[0];
        m_normalid[1] = other.m_normalid[1];
        m_normalid[2] = other.m_normalid[2];
        m_normalid[3] = other.m_normalid[3];
        m_uvid[0] = other.m_uvid[0];
        m_uvid[1] = other.m_uvid[1];
        m_uvid[2] = other.m_uvid[2];
        m_uvid[3] = other.m_uvid[3];
        m_origpatch = other.m_origpatch;
        m_istriangle = other.m_istriangle;
        m_attrid = other.m_attrid;
        return *this;
    }

    void SetVerts(const int v0, const int v1, const int v2) noexcept {
        m_vertexid[0] = v0;
        m_vertexid[1] = v1;
        m_vertexid[2] = v2;
        m_vertexid[3] = v0;
    }

    void SetVerts(const int v0, const int v1, const int v2, const int v3) noexcept {
        m_vertexid[0] = v0;
        m_vertexid[1] = v1;
        m_vertexid[2] = v2;
        m_vertexid[3] = v3;
    }

    [[nodiscard]] bool IsTri() const noexcept {
        return m_vertexid[0] == m_vertexid[3];
    }

    [[nodiscard]] bool IsQuad() const noexcept {
        return !IsTri();
    }
};

class IEEdge final {
public:
    int m_vertexid[2]{};
    int m_polyid[2]{}; //the faces sharing the edge                                              f[2]
    int m_polyvertexnum[2]{}; //the index in the faces sharing the edge (0, 1, or 2)                    fe[2]
    int m_thirdvertex[2]{}; //the third vertex of the faces sharing the edge ( assuming triangles )   tv[2]
    int m_numfaces{0}; //the number of faces sharing the edge (1 or 2)                           numFaces

    IEEdge() noexcept = default;

    IEEdge(const int id1, const int id2) noexcept {
        m_vertexid[0] = id1;
        m_vertexid[1] = id2;
    }

    ~IEEdge() = default;

    IEEdge &operator=(const IEEdge &other) noexcept {
        if (this == &other)
            return *this;
        m_vertexid[0] = other.m_vertexid[0];
        m_vertexid[1] = other.m_vertexid[1];
        m_numfaces = other.m_numfaces;
        m_polyid[0] = other.m_polyid[0];
        m_polyid[1] = other.m_polyid[1];
        m_polyvertexnum[0] = other.m_polyvertexnum[0];
        m_polyvertexnum[1] = other.m_polyvertexnum[1];
        m_thirdvertex[0] = other.m_thirdvertex[0];
        m_thirdvertex[1] = other.m_thirdvertex[1];
        return *this;
    }

    IEEdge(const IEEdge &) = default;
    IEEdge &operator=(IEEdge &&) = default;
    IEEdge(IEEdge &&) = default;
};

//edge0 m_vertexid[0] - m_vertexid[1]
//edge1 m_vertexid[1] - m_vertexid[2]
//edge2 m_vertexid[2] - m_vertexid[3]
//edge3 m_vertexid[3] - m_vertexid[0]

class IEPatch final {
public:
    HashArray<IEPatchMapNode *, IEPatchMapNode *> m_mapnodearray;
    // ReSharper disable once CppRedundantZeroInitializerInAggregateInitialization
    int m_controlvertexid[12]{0};
    // ReSharper disable once CppRedundantZeroInitializerInAggregateInitialization
    int m_vertexid[4]{0};
    int m_attrid{-1};
    HPatch *m_origpatch{nullptr};

// @formatter:off
    union {
        BITFIELDS8 m_IEPatch_flags{0};

        struct {
            BITFIELDS8 m_edge0isdiscontinuous : 1, //used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
            m_edge1isdiscontinuous : 1, //used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
            m_edge2isdiscontinuous : 1, //used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
            m_edge3isdiscontinuous : 1, //used to average normals rather than compute, hides anomolies (Caused by 5 point patches)
            m_is3point : 1; //m_vertexid[0] == m_vertexis[3]
        };
    };
    // @formatter:on

    explicit IEPatch(HPatch *patch) noexcept : m_origpatch(patch) {}

    ~IEPatch() {
        for (int i = 0; i < m_mapnodearray.GetSize(); ++i) {
            const IEMapNode *mapnode = m_mapnodearray.ElementAt(i);
            delete mapnode;
        }
        m_mapnodearray.RemoveAll();
    }

    IEPatch(const IEPatch &) = delete;
    IEPatch(IEPatch &&) = delete;
    IEPatch &operator=(const IEPatch &) = delete;
    IEPatch &operator=(IEPatch &&) = delete;
};

class IEBone final {
public:
    HashArray<int, int> m_vertexidarray;
    HashArray<float, float> m_weightarray;
    char m_name[256]{};

    Vector m_pivotpos;
    Vector m_endpos;
    Vector m_rollpos;
    IEBone *m_child{nullptr};
    IEBone *m_sibling{nullptr};

    IEBone() noexcept = default;

    ~IEBone() {
        m_vertexidarray.RemoveAll();
        m_weightarray.RemoveAll();
    }

    IEBone(const IEBone &) = delete;
    IEBone(IEBone &&) = delete;
    IEBone &operator=(const IEBone &) = delete;
    IEBone &operator=(IEBone &&) = delete;
};

class HashNode final {
public:
    HashNode *m_next{nullptr};
    int m_key{-1};
    int m_id{-1};
};

class VectorCollection final {
    HashArray<HashNode *, HashNode *> m_hasharray;

public:
    HashArray<Vector> m_array;

    VectorCollection() noexcept {
        m_array.SetGranularity(1000);
    }

    ~VectorCollection() {
        Empty();
    }

    VectorCollection(const VectorCollection &) = delete;
    VectorCollection &operator=(const VectorCollection &) = delete;
    VectorCollection(VectorCollection &&) = delete;
    VectorCollection &operator=(VectorCollection &&) = delete;

    Vector *GetArray() noexcept {
        return m_array.GetArray();
    }

    [[nodiscard]] Vector GetAt(const int index) const noexcept {
        return m_array.GetAt(index);
    }

    [[nodiscard]] int GetSize() const noexcept {
        return m_array.GetSize();
    }

    void SetSize(const int newsize, const int growby = -1) noexcept {
        m_array.SetSize(newsize, growby);
    }

    Vector &ElementAt(const int index) noexcept {
        return m_array.ElementAt(index);
    }

    int Add(const Vector &vector, int key = -1) noexcept;
    int AddWithoutKey(const Vector &vector) noexcept;
    [[nodiscard]] int LookUp(const Vector &vector, int key = -1) const noexcept;
    [[nodiscard]] int LookUpHashKey(const Vector &vector) const noexcept;
    static UINT GetHashKey(int key) noexcept;
    static UINT GetHashKey(const Vector &vector) noexcept;
    void Empty() noexcept;

    Vector operator [](const int index) const noexcept {
        return m_array.GetAt(index);
    }

    Vector &operator [](const int index) noexcept {
        return m_array.ElementAt(index);
    }

    void Shrink() noexcept {
        m_array.FreeExtra();
    }
};

HASH_INLINE void VectorCollection::Empty() noexcept {
    const int count = m_hasharray.GetSize();
    for (int i = 0; i < count; ++i) {
        if (const HashNode *nodehead = m_hasharray[i]; nodehead) {
            HashNode *next;
            for (const HashNode *node = nodehead; node; node = next) {
                next = node->m_next;
                delete node;
            }
            m_hasharray[i] = nullptr;
        }
    }
    m_array.SetSize(0);
}

HASH_INLINE UINT VectorCollection::GetHashKey(const int key) noexcept {
    return (UINT)key >> 4U;
}

HASH_INLINE UINT VectorCollection::GetHashKey(const Vector &vector) noexcept {
    //    const double x = (int)(vector.x * 1000.0F + SIGN(vector.x) * .5F) / 1000.0 * 12.3;
    //    const double y = (int)(vector.y * 1000.0F + SIGN(vector.y) * .5F) / 1000.0 * 23.4;
    //    const double z = (int)(vector.z * 1000.0F + SIGN(vector.z) * .5F) / 1000.0 * 34.5;
    //    return (int)(hash_math::pow(x * x + y * y + z * z, 0.5) * 9.87);
    size_t seed = 0;
    hash_combine(seed, vector.x);
    hash_combine(seed, vector.y);
    hash_combine(seed, vector.z);
    return (UINT)seed;
}

HASH_INLINE int VectorCollection::LookUp(const Vector &vector, const int key) const noexcept {
    if (m_hasharray.IsEmpty())
        return -1;

    UINT hashkey;
    if (key == -1) {
        hashkey = GetHashKey(vector);
    } else {
        hashkey = GetHashKey(key);
    }

    const UINT index = hashkey % m_hasharray.GetSize();
    const HashNode *nodehead = m_hasharray.GetAt(index);
    for (const HashNode *node = nodehead; node; node = node->m_next) {
        if ((key != -1) && (node->m_key != -1)) {
            if (node->m_key == key)
                return node->m_id;
            continue;
        }
        //        if (match.IsEqual(vector, 1.e-3f))
        if (const Vector &match = m_array.GetAt(node->m_id); match == vector)
            return node->m_id;
    }
    return -1;
}

HASH_INLINE int VectorCollection::LookUpHashKey(const Vector &vector) const noexcept {
    const int count = m_hasharray.GetSize();
    for (int i = 0; i < count; ++i) {
        if (const HashNode *nodehead = m_hasharray.GetAt(i); nodehead) {
            for (const HashNode *node = nodehead; node; node = node->m_next) {
                //                if (match.IsEqual(vector, 1.e-3f))
                if (const Vector &match = m_array.GetAt(node->m_id); match == vector)
                    return node->m_key;
            }
        }
    }
    return -1;
}

HASH_INLINE int VectorCollection::Add(const Vector &vector, const int key) noexcept {
    if (m_hasharray.GetSize() == 0)
        m_hasharray.SetSize(2999);

    UINT hashkey;
    if (key == -1) {
        hashkey = GetHashKey(vector);
    } else {
        hashkey = GetHashKey(key);
    }
    const UINT index = hashkey % m_hasharray.GetSize();
    HashNode *nodehead = m_hasharray.GetAt(index);
    for (const HashNode *node = nodehead; node; node = node->m_next) {
        if ((key != -1) && (node->m_key != -1)) {
            if (node->m_key == key)
                return node->m_id;
            continue;
        }
        //        if (match.IsEqual(vector, 1.e-3f))
        if (const Vector &match = m_array.GetAt(node->m_id); match == vector)
            return node->m_id;
    }
    //doesn't exist yet
#pragma warning(suppress:28193)
    auto *newnode = new (std::nothrow) HashNode;
    if (newnode == nullptr) {
        ASSERT(false);
        return -1;
    }
    const int newid = m_array.Add(vector);
    newnode->m_id = newid;
    newnode->m_key = key;
    newnode->m_next = nodehead;
    m_hasharray.SetAt(index, newnode);
    return newid;
}

HASH_INLINE int VectorCollection::AddWithoutKey(const Vector &vector) noexcept {
    return m_array.Add(vector);
}

//*************************** Unique Data Collection *****************************

template <class TYPE, class ARG_TYPE = const TYPE &>
class UDCollection final {
    HashArray<int, int> m_keyarray;
    HashArray<TYPE, ARG_TYPE> m_array;

public:
    int Add(ARG_TYPE newelement, int key = -1) noexcept;
    int AddForce(ARG_TYPE newelement) noexcept;
    int LookUp(ARG_TYPE newelement, int key = -1) noexcept;

    TYPE *GetArray() noexcept {
        return m_array.GetArray();
    }

    [[nodiscard]] TYPE GetAt(const int index) const noexcept {
        return m_array.GetAt(index);
    }

    TYPE &ElementAt(const int index) noexcept {
        return m_array.ElementAt(index);
    }

    [[nodiscard]] int GetSize() const noexcept {
        return m_array.GetSize();
    }

    void SetSize(const int newsize, const int growby = -1) noexcept {
        m_array.SetSize(newsize, growby);
        m_keyarray.SetSize(newsize, growby);
    }

    TYPE operator [](const int index) const noexcept {
        return m_array.GetAt(index);
    }

    TYPE &operator [](const int index) noexcept {
        return m_array.ElementAt(index);
    }

    void Empty() noexcept {
        m_array.RemoveAll();
        m_keyarray.RemoveAll();
    }

    void SetGranularity(const int granularity) noexcept {
        m_keyarray.SetGranularity(granularity);
        m_array.SetGranularity(granularity);
    }

    void Shrink() noexcept {
        m_keyarray.FreeExtra();
        m_array.FreeExtra();
    }
};

template <class TYPE, class ARG_TYPE>
int UDCollection<TYPE, ARG_TYPE>::Add(ARG_TYPE newelement, const int key) noexcept {
    const int count = m_array.GetSize();

    for (int i = 0; i < count; ++i) {
        if ((key != -1) && (m_keyarray.GetAt(i) != -1)) {
            if (m_keyarray.GetAt(i) == key)
                return i;
        } else {
            if (m_array.GetAt(i) == newelement)
                return i;
        }
    }

    m_keyarray.Add(key);
    return m_array.Add(newelement);
}

template <class TYPE, class ARG_TYPE>
int UDCollection<TYPE, ARG_TYPE>::AddForce(ARG_TYPE newelement) noexcept {
    m_keyarray.Add(-1);
    return m_array.Add(newelement);
}

template <class TYPE, class ARG_TYPE>
int UDCollection<TYPE, ARG_TYPE>::LookUp(ARG_TYPE newelement, const int key) noexcept {
    const int count = m_array.GetSize();

    for (int i = 0; i < count; ++i) {
        if ((key != -1) && (m_keyarray.GetAt(i) != -1)) {
            if (m_keyarray.GetAt(i) == key)
                return i;
        } else {
            if (m_array.GetAt(i) == newelement)
                return i;
        }
    }
    return -1;
}

//*******************************************************

class RenderInfo;

class IEModel {
public:
    VectorCollection m_vertexlist;
    UDCollection<IEMap> m_maplist{};
    UDCollection<Attr> m_attrlist{};
    IEBone *m_bonehead{nullptr};

    IEModel() noexcept {
        m_maplist.SetGranularity(20);
        m_attrlist.SetGranularity(20);
    }

    virtual ~IEModel() {
        DeleteBoneBranch(m_bonehead);
    }

    IEModel(const IEModel &) = delete;
    IEModel(IEModel &&) = delete;
    IEModel &operator=(const IEModel &) = delete;
    IEModel &operator=(IEModel &&) = delete;

    static HASH_INLINE void DeleteBoneBranch(const IEBone *startbone) noexcept;
    //    void Draw(RenderInfo *renderinfo);

    Vector *GetVertexArray() noexcept {
        return m_vertexlist.GetArray();
    }

    Vector &GetVertex(const int i) noexcept {
        return m_vertexlist[i];
    }
};

HASH_INLINE void IEModel::DeleteBoneBranch(const IEBone *startbone) noexcept {
    // ReSharper disable once CppJoinDeclarationAndAssignment
    IEBone *sibling;
    for (const IEBone *bone = startbone; bone; bone = sibling) {
        sibling = bone->m_sibling;
        if (bone->m_child)
            DeleteBoneBranch(bone->m_child);
        delete bone;
    }
}

class IEColor final {
public:
    BYTE m_red{0};
    BYTE m_green{0};
    BYTE m_blue{0};
    BYTE m_alpha{0};

    IEColor() noexcept = default;

    IEColor(const BYTE red, const BYTE green, const BYTE blue, const BYTE alpha) noexcept : m_red(red),
                                                                                            m_green(green),
                                                                                            m_blue(blue),
                                                                                            m_alpha(alpha) {}
};

class IEPolyModel : public IEModel {
public:
    HashArray<IEPoly *, IEPoly *> m_polyarray; //this crazy array should definitely be an array of poly's, not an array of pointers to poly's, overworked allocator... pointless, and a waste of space
    VectorCollection m_normallist;

    IEPolyModel() noexcept {
        m_polyarray.SetGranularity(500);
    }

    IEPolyModel(const IEPolyModel &other) noexcept {
        m_polyarray.SetGranularity(500);
        *this = other;
    }

    IEPolyModel &operator=(const IEPolyModel &other) noexcept {
        if (this == &other)
            return *this;
        const int nvert = other.GetNumVerts();
        SetNumVerts(nvert);
        for (int i = 0; i < nvert; ++i) {
            m_vertexlist[i] = other.m_vertexlist[i];
        }
        const int nface = other.GetNumFaces();
        SetNumFaces(nface);
        for (int i = 0; i < nface; ++i) {
            const IEPoly &poly = *other.m_polyarray[i];
            m_polyarray[i]->SetVerts(poly.m_vertexid[0], poly.m_vertexid[1], poly.m_vertexid[2], poly.m_vertexid[3]);
        }
        const int nnormal = other.GetNumNormals();
        SetNumNormals(nnormal);
        for (int i = 0; i < nnormal; ++i) {
            m_normallist[i] = other.m_normallist[i];
        }
        return *this;
    }

    ~IEPolyModel() override {
        IEPolyModel::FreeData();
    }

    IEPolyModel(IEPolyModel &&) = delete;
    IEPolyModel &operator=(IEPolyModel &&) = delete;

    virtual void FreeData() noexcept {
        m_normallist.Empty();
        const int polysize = m_polyarray.GetSize();
        for (int i = 0; i < polysize; ++i) {
            const IEPoly *poly = m_polyarray[i];
            delete poly;
        }
        m_polyarray.RemoveAll();
    }

    PLUGINEXPORT void BuildNormalList(float angletolerance); //0-180
    PLUGINEXPORT void BuildNormalList(); //same as 180 above, but much faster, always one normal per vertex
    PLUGINEXPORT void BuildNormalListForProp(); //it is possible , that some vertices having no normals, wich cause a realtime render exception

    [[nodiscard]] int GetNumVerts() const noexcept {
        return m_vertexlist.GetSize();
    }

    void SetNumVerts(const int i) noexcept {
        m_vertexlist.SetSize(i);
    }

    [[nodiscard]] int GetNumFaces() const noexcept {
        return m_polyarray.GetSize();
    }

    virtual void SetNumFaces(const int numfaces) noexcept {
        m_polyarray.SetSize(numfaces); //it seems crazy that m_polyarray is not an array of IEPolys, but rather an array of pointers to IEPolys ??
        for (int i = 0; i < numfaces; ++i) {
#pragma warning(suppress:28193)
            m_polyarray[i] = HASHNEW IEPoly;
        }
    }

    [[nodiscard]] int GetNumNormals() const noexcept {
        return m_normallist.GetSize();
    }

    void SetNumNormals(const int i) noexcept {
        m_normallist.SetSize(i);
    }

    [[nodiscard]] int GetNumTris() const noexcept {
        const int nfaces = GetNumFaces();
        int numtris = 0;
        for (int i = 0; i < nfaces; ++i) {
            ++numtris;
            if (m_polyarray[i]->IsQuad())
                ++numtris; //each quad adds two triangles
        }
        return numtris;
    }

    //for Vlado's EdgeLister
    [[nodiscard]] int getNumVerts() const noexcept {
        return GetNumVerts();
    }

    [[nodiscard]] int getNumFaces() const noexcept {
        return GetNumFaces();
    }

    int getFaceVertex(const int face, const int v) noexcept {
        return m_polyarray[face]->m_vertexid[v];
    }
};

class PLUGINEXPORT IETriModel final : public IEPolyModel {
public:
    HashArray<IEPoly> m_polyclassarray; //this is an array of actual IEPoly classes, we initialize all the pointers in the base class m_polyarray to point at these
    HashArray<IEEdge> m_edges;
    int *m_edgeindex{nullptr}; //an array of edge indexes, these would be more easily stored in 3 in each Triangle, but we are using IEPoly which cannot be invalidated

    IETriModel() noexcept {
        Init();
    }

    IETriModel(const IETriModel &other) noexcept : IEPolyModel(other) {
        Init();
        *this = other;
    }

    IETriModel &operator=(const IETriModel &other) noexcept {
        if (this == &other)
            return *this;
        const int nvert = other.GetNumVerts();
        SetNumVerts(nvert);
        for (int i = 0; i < nvert; ++i) {
            m_vertexlist[i] = other.m_vertexlist[i];
        }
        const int nface = other.GetNumFaces();
        SetNumFaces(nface);
        for (int i = 0; i < nface; ++i) {
            m_polyarray[i] = other.m_polyarray[i];
        }
        const int nedge = other.GetNumEdges();
        SetNumEdges(nedge);
        for (int i = 0; i < nedge; ++i) {
            m_edges[i] = other.m_edges[i];
        }
        const int nnormal = other.GetNumNormals();
        SetNumNormals(nnormal);
        for (int i = 0; i < nnormal; ++i) {
            m_normallist[i] = other.m_normallist[i];
        }
        return *this;
    }

    ~IETriModel() override;

    IETriModel(IETriModel &&) = delete;
    IETriModel &operator=(IETriModel &&) = delete;

    void FreeData() noexcept override {
        m_edges.RemoveAll();
        delete[] m_edgeindex;
        m_edgeindex = nullptr;
    }

    void Init() noexcept {
        m_polyarray.SetGranularity(1000);
        m_edges.RemoveAll();
        m_edgeindex = nullptr;
    }

    void SetNumEdges(const int i) noexcept {
        m_edges.SetSize(i);
    }

    [[nodiscard]] int GetNumEdges() const noexcept {
        return m_edges.GetSize();
    }

    void SetNumFaces(const int numfaces) noexcept override {
        //override the IEPoly version
        m_polyarray.SetSize(numfaces); //this one is pointers
        m_polyclassarray.SetSize(numfaces);
        for (int i = 0; i < numfaces; ++i) {
            m_polyarray[i] = &m_polyclassarray[i];
        }
    }

    void BuildEdges(bool deleteold = true);

    friend PLUGINEXPORT void Triangulate(const IEPolyModel &quadmesh, IETriModel &trimesh);
    friend PLUGINEXPORT void LoopSubdivideStep(const IETriModel &mesh, IETriModel &smesh);
    friend PLUGINEXPORT void LoopSubdivide(IETriModel &mesh, IETriModel &smesh, int numSteps);

    void setNumEdges(const int numEdges) noexcept {
        SetNumEdges(numEdges);
    }
};

class IEPatchModel final : public IEModel {
public:
    HashArray<IEPatch *, IEPatch *> m_patcharray;
    VectorCollection m_controlvertexlist;

    IEPatchModel() noexcept {
        m_patcharray.SetGranularity(1000);
    }

    ~IEPatchModel() override {
        const int psize = m_patcharray.GetSize();
        for (int i = 0; i < psize; ++i) {
            const IEPatch *patch = m_patcharray.ElementAt(i);
            delete patch;
        }
        m_patcharray.RemoveAll();
    }

    IEPatchModel(const IEPatchModel &) = delete;
    IEPatchModel &operator=(const IEPatchModel &) = delete;
    IEPatchModel(IEPatchModel &&) = delete;
    IEPatchModel &operator=(IEPatchModel &&) = delete;
};

class IEModelParms {
    // NOLINT
public:
    MapLimit m_minmodelmapsize{ML_1}, m_maxmodelmapsize{ML_512};
    int m_minmodelmapsizeint{0}, m_maxmodelmapsizeint{256};

// @formatter:off
    union {
        BITFIELDS16 m_IEModelParms_flags{624}; //m_isdisplaypercentbar = m_applydisplacement = m_useconsistentids = m_ignorevisibility = true;
        struct {
            BITFIELDS16 m_isbuildmaparray : 1,
                m_isbuildattrarray : 1,
                m_isbuildbonelist : 1,
                m_isbuildmodelmap : 1,
                m_isdisplaypercentbar : 1, // default true
                m_applydisplacement : 1, //if displacement/bumpmapping should be applied to the geometrie // default true
                m_useconsistentids : 1,
                m_isnormalizeuvs : 1,
                m_isbuildweights : 1,
                m_ignorevisibility : 1, // default true
                m_isclothsim : 1, //default False
                m_maxweightcount : 4, //number 0-15, 0 indicates unlimited.
                unused : 1;
        };
    };
    // @formatter:on

    IEModelParms() noexcept = default; // NOLINT
};

enum SubType {
    ST_1,
    ST_4,
    ST_16,
    ST_64,
    ST_256,
    ST_1024,
    ST_4096,
    ST_VARIABLE,
    SUBTYPE_COUNT
};

class IEPolyModelParms final : public IEModelParms {
public:
    SubType m_subtype{ST_VARIABLE};

    IEPolyModelParms() noexcept = default;
    IEPolyModelParms(const SubType subdivisiontype, BOOL) noexcept : m_subtype(subdivisiontype) {}
    explicit IEPolyModelParms(const SubType subdivisiontype) noexcept : m_subtype(subdivisiontype) {}
};

class HGroup;
class HCP;
class HCPInstance;

class VertexInfo final {
public:
    HashArray<HPatch *, HPatch *> m_patcharray; //the patch each vertex came from
    HashArray<HCP *, HCP *> m_cparray; //the cp associated with the vertex, only if at a patch corner
    HashArray<Vector2, Vector2> m_uvarray; //the uv on that patch for each vertex

    //used by cloth plugin and Bullet
    HashArray<HCPInstance *, HCPInstance *> m_cpinstancearray; //the cpinstances for the correspondending cp's

    //used by cloth plugin
    HashArray<HGroup *, HGroup *> m_grouparray; //the custom group whose properties will control the behavior of the vertex
    HashArray<bool, bool> m_attachedarray; //a bool indicating whether the vertex is attached, only used in SimCloth

    VertexInfo() noexcept {
        m_patcharray.SetGranularity(50);
        m_cparray.SetGranularity(50);
        m_uvarray.SetGranularity(50);
    }

    void RemoveAll() noexcept {
        m_patcharray.RemoveAll();
        m_uvarray.RemoveAll();
        m_cparray.RemoveAll();

        m_grouparray.RemoveAll();
        m_attachedarray.RemoveAll();
        m_cpinstancearray.RemoveAll();
    }
};
