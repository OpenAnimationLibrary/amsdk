// IE.h : main header file for the IE DLL
//

#if !defined(AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_

#pragma once

#ifndef __AFXWIN_H__
#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/HPropert.h"
#include "SDK/Misc.h"
#include "resource.h"		// main symbols
#include "IEModel.h"

#define VERSION "# 1OBJ"
//#define NL '\n'

#define NEWLINE_CHAR '\n'

class AttrMap {
public:
    bool m_hasadditionalmaps;
    bool m_bmapKd;
    CString m_mapKd;
    bool m_bmapKs;
    CString m_mapKs;
    bool m_bmapKa;
    CString m_mapKa;
    bool m_bmapBump;
    CString m_mapBump;
    bool m_bmapd;
    CString m_mapd;
    int m_mapid;
};

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
    IEPolyModelParms m_iemp;
    HProgressBar *m_hprogressbar;
    BOOL m_bexporttriangles;
    BOOL m_normalsneedrebuild;
    BOOL m_discarddegenerated;
    BOOL m_exportnormals;
    BOOL needsmapdlg;
    HashArray<CString, CString &> m_maplist;
    VectorCollection m_texturevertexlist;
    HashArray<AttrMap, AttrMap &> m_attrmap;
    UDCollection<CString, CString &> m_texturemaps;
    bool m_buvcount;
    bool m_materialfile_found;

    CHxtApp();

    static void ReportImportError(const String &filename);
    static void ReportExportError(const String &filename);

    BOOL OnExportModelCache(HModelCache *hmc);
    BOOL OnExportObjectCacheContainer(HObjectCacheContainer *hocc);
    BOOL OnExportActionCache(HActionCache *hac);
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    BOOL OnExportChor(HChor *hchor);

    static int CountBones(const IEPolyModel *model);
    BOOL ExportOBJ(IEPolyModel *model, const String &filename, BOOL savename = FALSE);
    void MakeUniqueName(String &filename, int count = 1);
    static int FindAttributesFromName(IEPolyModel *model, const String &name);
    void AddAttributesFromTexture(IEPolyModel *model);
    void SaveAttributes(const String &filename, IEPolyModel *model, int &totalitems, int &curritem);
    void SaveTextureMaps(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SaveVertexList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SaveUVs(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem);
    void SaveNormalList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SavePolys(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem, const String &groupname) const;
    void SaveBones(FileStream &fs, const IEPolyModel *model, int &totalitems, int &curritem) const;
    void SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem) const;
    void CopyMaps(const String &path, IEPolyModel *model);
    int CountMaps(int index);
    static int GetMapType(int index);
    int GetNextMap(int mtlindex, int *lastmap);
    int FindMapIndex(CString mapname);
    String FindTextureFilename(IEPolyModel *model, const String &tofind);

    BOOL OnImportModelCache(HModelCache *hmc);
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc);
    IEPolyModel *ImportOBJ(const String &pfilename, BOOL isnewimport = TRUE, BOOL isprop = FALSE, float scaling = 1.f);
    int CountMaterials(const char *filename, const String &path);
    char *BreakUp(char *str, IEPoly *poly, int idx);
    static int FindMtlName(char list[256][256], const char *name);
    static void LoadBones(FileStream &fs, IEBone **parentuplink, IEBone *parent);
    static void IgnoreLine(FILE *fs, char lastchar);
    static void GetToken(FILE *fs, char *buffer, char *lastchar, int maxsize);
    static void GetLine(FILE *fs, char *buffer, char *lastchar, int maxsize);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
public:
    BOOL InitInstance() override;
    int ExitInstance() override;
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
