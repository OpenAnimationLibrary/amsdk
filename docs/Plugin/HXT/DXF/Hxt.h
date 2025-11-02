// KB  9/25/02  \Ken95\Plugin\HXT\DXF\Hxt.h

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
#ifndef __IEMODEL_H
#include "IEModel.h"
#endif

#define VERSION "# 1DXF"
#define NL "\x0D\x0A"

#define NEWLINE_CHAR '\n'

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

    static void ReportImportError(const String &filename);
    static void ReportExportError(const String &filename);

    BOOL OnExportModelCache(HModelCache *hmc);
    BOOL OnExportObjectCacheContainer(HObjectCacheContainer *hocc);
    BOOL OnExportActionCache(HActionCache *hac);
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    BOOL OnExportChor(HChor *hchor);

    static int CountBones(const IEPolyModel *model);
    BOOL ExportDXF(IEPolyModel *model, const String &pfilename);
    static void PadLine(FILE *file);
    /*
    void SetFileType(const char *filename, UINT type);
    void SaveTextureMaps(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem);
    void SaveVertexList(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem);
    void SaveNormalList(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem);
    void SavePolys(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem);
    void SaveBones(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem);
    void SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem);
     
    */
    BOOL OnImportModelCache(HModelCache *hmc);
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc);
    IEPolyModel *ImportDXF(const String &pfilename, BOOL isnewimport = TRUE);
    static void IgnoreLine(FILE *fs, char lastchar);
    static void GetToken(FILE *fs, char *buffer, char *lastchar);
    static void LoadBones(FileStream &fs, IEBone **parentuplink, IEBone *parent);
    static int FindVertex(const IEPolyModel *model, Vector vertex, int countverticies);
    static int CreateVertex(IEPolyModel *model, Vector vertex, int *countverticies);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
public:
    BOOL InitInstance() override;
    int ExitInstance() override; // AM SDK
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
