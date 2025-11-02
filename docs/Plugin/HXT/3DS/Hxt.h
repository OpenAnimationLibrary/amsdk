// KB  1/3/05  \Plugin\HXT\3DS\Hxt.h
//

// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#if !defined(AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/HPropert.h"
#include "SDK/Misc.h"
#include "resource.h"		// main symbols
#include "IEModel.h"
#include "Matrix34.h"

// Each 3DS data-chunk starts with a 6 byte header.
// The first item in the header is a 2 byte (word) id-number.
// After that follows a dword which gives the size of
// the data-chunk including the header. The size can be used
// as an relative offset to the next chunk.
#define MIN3DS(A,B)           ((A)<(B)?(A):(B))

#define CHUNKIDSIZE sizeof(WORD)
#define DEFAULTCHUCKSIZE (DWORD) 0

#define CHUNK_M3DVERSION    (WORD) 0x0002
#define CHUNK_RGB_F         (WORD) 0x0010
#define CHUNK_RGB_B         (WORD) 0x0011
#define CHUNK_LIN_RBG_B     (WORD) 0x0012
#define CHUNK_LIN_RBG_F     (WORD) 0x0013
#define CHUNK_PERCENT_W     (WORD) 0x0030
#define CHUNK_PERCENT_F     (WORD) 0x0031
#define CHUNK_MASTERSCALE   (WORD) 0x0100
#define CHUNK_MAIN          (WORD) 0x4D4D
#define CHUNK_OBJMESH       (WORD) 0x3D3D
#define CHUNK_MESHVERSION   (WORD) 0x3D3E
#define CHUNK_BKGCOLOR      (WORD) 0x1200
#define CHUNK_AMBCOLOR      (WORD) 0x2100
#define CHUNK_OBJCHUNK      (WORD) 0x4000
#define CHUNK_TRIMESH       (WORD) 0x4100
#define CHUNK_VERTLIST      (WORD) 0x4110
#define CHUNK_FACELIST      (WORD) 0x4120
#define CHUNK_FACEMAT       (WORD) 0x4130
#define CHUNK_UVLIST        (WORD) 0x4140
#define CHUNK_SMOOLIST      (WORD) 0x4150
#define CHUNK_TRMATRIX      (WORD) 0x4160
#define CHUNK_MESHCOLOR     (WORD) 0x4165
#define CHUNK_LIGHT         (WORD) 0x4600
#define CHUNK_SPOTLIGHT     (WORD) 0x4610
#define CHUNK_CAMERA        (WORD) 0x4700
#define CHUNK_MATERIAL      (WORD) 0xAFFF
#define CHUNK_MAT_NAME      (WORD) 0xA000
#define CHUNK_MAT_AMBIENT   (WORD) 0xA010
#define CHUNK_MAT_DIFFUSE   (WORD) 0xA020
#define CHUNK_MAT_SPECULAR  (WORD) 0xA030
#define CHUNK_MAT_SHININESS    (WORD) 0xA040
#define CHUNK_MAT_SHIN2PCT     (WORD) 0xA041
#define CHUNK_MAT_SHIN3PCT  	 (WORD) 0xA042
#define CHUNK_MAT_TRANSPARENCY (WORD) 0xA050
#define CHUNK_MAT_SHADING      (WORD) 0xA100
#define CHUNK_MAT_TEXTUREMAP   (WORD) 0xA200
#define CHUNK_MAT_SPECULARMAP  (WORD) 0xA204
#define CHUNK_MAT_OPACMAP      (WORD) 0xA210
#define CHUNK_MAT_REFLECTMAP   (WORD) 0xA220
#define CHUNK_MAT_BUMPMAP    	 (WORD) 0xA230
#define CHUNK_MAT_MAPNAME      (WORD) 0xA300

class MeshObject {
public:
    class Face {
    public:
        WORD m_vertexid[3]{0};
        WORD m_flags{0};
        int m_attrid{-1};
        HashArray<IEMapNode *, IEMapNode *> m_mapnodes; // don't have to delete these because they get robbed by IEPoly.

        Face() = default;
    };

    CString m_name{};
    HashArray<Vector, Vector &> m_vertexlist;
    HashArray<Face, Face &> m_facelist;
    HashArray<Vector2, Vector2 &> m_mapuvlist;
    Matrix34 m_matrix;

    MeshObject() {
        m_vertexlist.SetSize(0, 3000);
        m_facelist.SetSize(0, 1000);
        m_mapuvlist.SetSize(0, 1000);
        m_matrix.SetIdentity();
    }
};

class IEMapNodeExt final : public IEMapNode {
public:
    CString m_filename;
};

class AttrExt {
public:
    CString m_matname{};

    CList<IEMapNodeExt *, IEMapNodeExt *> m_mapnodeextlist;

    AttrExt() = default;
    ~AttrExt() {
        for (POSITION pos = m_mapnodeextlist.GetHeadPosition(); pos;)
            delete m_mapnodeextlist.GetNext(pos);
    }
    AttrExt(const AttrExt&) = delete;
    AttrExt &operator= (const AttrExt&) = delete; 
    AttrExt(AttrExt &&) = delete; 
    AttrExt &operator=(AttrExt &&) = delete; 

};

class IEPoly;

class MapMaterialID {
public:
    int m_colormapid{0};
    int m_specularmapid{0};
    int m_bumpmapid{0};
    int m_opacitymapid{0};
    int m_reflectmapid{0};
    int m_materialid{0};

    //   int MapMaterialID::operator == ( const MapMaterialID &other ) const
    int operator ==(const MapMaterialID &other) const {
        return m_materialid == other.m_materialid && m_colormapid == other.m_colormapid && m_specularmapid == other.m_specularmapid && m_bumpmapid == other.m_bumpmapid && m_opacitymapid == other.m_opacitymapid && m_reflectmapid == other.m_reflectmapid;
    }

    void Set(IEPoly *poly);
};

template<>
UINT AFXAPI HashKey<MapMaterialID &>(MapMaterialID &key);

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See IE.cpp for the implementation of this class
//

class HModelCache;
class HObjectCacheContainer;
class FileStream;
class String;
class HProgressBar;
class HActionCache;
class HActionCacheContainer;
class HChor;

class CHxtApp final : public CPluginApp {
public:
    IEPolyModelParms m_iemp{};
    HProgressBar *m_hprogressbar{nullptr};
    HashArray<AttrExt *, AttrExt *> m_attrextlist; // Expands m_attrlist in iepolymodel, same index id to reference into this ar the m_attrlist
    CMap<MapMaterialID, MapMaterialID &, int, int &> m_hashtable; // Used for Exporting
    HashArray<CString, CString &> m_maplist;
    DWORD m_importfilelength{0};
    int m_currexportitem{0};
    int m_totalexportitems{0};
    float m_masterscale{0.F};

    CHxtApp();

    ~CHxtApp() override {
        for (int i = 0; i < m_attrextlist.GetSize(); ++i)
            delete m_attrextlist[i];
    }
    CHxtApp(const CHxtApp&) = delete;
    CHxtApp &operator= (const CHxtApp&) = delete; 
    CHxtApp(CHxtApp &&) = delete; 
    CHxtApp &operator=(CHxtApp &&) = delete; 


    static void ReportImportError(const String &filename);
    static void ReportExportError(const String &filename);

    BOOL OnExportModelCache(HModelCache *hmc);
    BOOL OnExportObjectCacheContainer(HObjectCacheContainer *hocc);
    BOOL OnExportActionCache(HActionCache *hac);
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    BOOL OnExportChor(HChor *hchor);

    BOOL Export3DS(IEPolyModel *model, const String &filename);
    void WriteObjMeshChunk(CArchive &ar, IEPolyModel *model);
    static void WriteMaterial(CArchive &ar, const Attr &attr, int id);
    void WriteMapMaterial(CArchive &ar, IEPolyModel *model, const MapMaterialID *mapmaterialid, int i);
    void WriteObjChunk(CArchive &ar, IEPolyModel *model);
    void WriteTriMeshChunk(CArchive &ar, IEPolyModel *model);
    void WriteVertexList(CArchive &ar, IEPolyModel *model);
    void WriteFaceList(CArchive &ar, IEPolyModel *model);
    static void WriteFaceMat(CArchive &ar, IEPolyModel *model, int id);
    void WriteFaceMapMat(CArchive &ar, IEPolyModel *model, int matchid) const;
    static void WriteUVList(CArchive &ar, IEPolyModel *model);
    void CopyMaps(const String &path, IEPolyModel *model);

    BOOL OnImportModelCache(HModelCache *hmc);
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc);
    IEPolyModel *Import3DS(const String &pfilename);
    void ReadObjMeshChunk(CArchive &ar, DWORD endpos, IEPolyModel *model);
    void ReadObjChunk(CArchive &ar, DWORD endpos, IEPolyModel *model);
    void ReadMaterial(CArchive &ar, DWORD endpos, IEPolyModel *model);
    IEMapNodeExt *ReadTextureMap(CArchive &ar, DWORD endpos, AttrExt *attrext) const;
    void ReadTriMeshChunk(CArchive &ar, DWORD endpos, IEPolyModel *model, const CString &name);
    static void ReadVertexList(CArchive &ar, DWORD endpos, MeshObject &meshobj);
    static void ReadFaceList(CArchive &ar, DWORD endpos, MeshObject &meshobj);
    void ReadFaceMat(CArchive &ar, DWORD endpos, MeshObject &meshobj, IEPolyModel *model);
    static void ReadUVList(CArchive &ar, DWORD endpos, MeshObject &meshobj);
    static void AddMeshObjectToModel(MeshObject &meshobj, IEPolyModel *model);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
public:
    BOOL InitInstance() override;
    BOOL ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CHxtApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
