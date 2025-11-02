// IE.h : main header file for the IE DLL
//
#pragma once

#if !defined(AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_IE_H__58C0982D_D8D2_11D3_83A5_00E0811049D9__INCLUDED_


#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/HPropert.h"
#include "SDK/Misc.h"
#include "resource.h"		// main symbols
#include "IEModel.h"
#include "Matrix34.h"

#define VERSION "# 1LWO"
#define NL "\x0D\x0A"

#define NEWLINE_CHAR '\n'

class AttrMap {
public:
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
    CHxtApp();
    IEPolyModelParms m_iemp;
    HProgressBar *m_hprogressbar;
    BOOL m_bexporttriangles{};
    HashArray<CString, CString &> m_maplist;
    VectorCollection m_texturevertexlist;
    HashArray<AttrMap, AttrMap &> m_attrmap;
    UDCollection<CString, CString &> m_texturemaps;
    bool m_buvcount{};

    static void ReportImportError(const String &filename);
    static void ReportExportError(const String &filename);

    BOOL OnExportModelCache(HModelCache *hmc);
    BOOL OnExportObjectCacheContainer(HObjectCacheContainer *hocc);
    BOOL OnExportActionCache(HActionCache *hac);
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    BOOL OnExportChor(HChor *hchor);

    int CountBones(const IEPolyModel *model);
    static BOOL ExportLWO(IEPolyModel *model, const String &filename);
    static void SaveAttributeNames(FILE *fp, const IEPolyModel *model, int &totalitems, int &curritem, char *baseName);
    static void SaveAttributes(FILE *fp, IEPolyModel *model, int &totalitems, int &curritem, char *baseName);
    static void SaveVertexList(FILE *fp, IEPolyModel *model, int &totalitems, int &curritem);
    static void SavePolys(FILE *fp, IEPolyModel *model, int &totalitems, int &curritem);
    static unsigned short swapShort(unsigned short w);
    static unsigned long swapLong(unsigned long w);
    static void writeTag(FILE *fp, const char *tag);
    static void writeChar(FILE *fp, unsigned char dat);
    static void writeShort(FILE *fp, unsigned short dat);
    static void writeLong(FILE *fp, unsigned long dat);
    static void writeFloat(FILE *fp, float dat);
    static void writeName(FILE *fp, const char *name);
    static const char *getFilename(const char *name);
    static char *getBasename(const char *name, char *dest);
    void CopyMaps(const String &path, IEPolyModel *model);
    int CountMaps(int index);
    int GetMapType(int index);
    int GetNextMap(int mtlindex, int *lastmap);
    int FindMapIndex(CString mapname);

    static BOOL OnImportModelCache(HModelCache *hmc);
    static BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc);
    static IEPolyModel *ImportLWO(const String &pfilename, BOOL isnewimport = TRUE);
    static unsigned short _SwapTwoBytes(unsigned short w);
    static unsigned long _SwapFourBytes(unsigned long w);
    static int read_pnts(IEPolyModel *model, unsigned long nbytes, FILE *file);
    static char *read_pols(IEPolyModel *model, unsigned long nbytes, FILE *file, unsigned int nSfs);
    static int read_srfs(unsigned long nbytes, FILE *file);
    static void read_surf(IEPolyModel *model, int attrid, unsigned long nbytes, FILE *file);
    static IEPolyModel *Escape(FILE *fp, IEPolyModel *model, const char *message);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
public:
    BOOL InitInstance() override;
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
