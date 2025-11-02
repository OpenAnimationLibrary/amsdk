// Dan  12/27/00  \Dan90\Plugin\HXT\AV2\Hxt.h
//

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
//#include "IEModel.h"

#define VERSION 2L

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
    IEModelParms m_iemp;
    HProgressBar *m_hprogressbar;

    static void ReportImportError(const String &filename);
    static void ReportExportError(const String &filename);

    BOOL OnExportModelCache(HModelCache *hmc);
    BOOL OnExportObjectCacheContainer(HObjectCacheContainer *hocc);
    BOOL OnExportActionCache(HActionCache *hac);
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    BOOL OnExportChor(HChor *hchor);

    static int CountBones(const IEPatchModel *model);
    BOOL ExportAV2(IEPatchModel *model, const String &filename);
    void SaveAttributes(FileStream &fs, IEPatchModel *model, const int &totalitems, int &curritem) const;
    void SaveTextureMaps(FileStream &fs, IEPatchModel *model, const int &totalitems, int &curritem) const;
    void SaveVertexList(FileStream &fs, IEPatchModel *model, const int &totalitems, int &curritem) const;
    void SaveControlVertexList(FileStream &fs, IEPatchModel *model, const int &totalitems, int &curritem) const;
    void SavePatches(FileStream &fs, IEPatchModel *model, const int &totalitems, int &curritem) const;
    void SaveBones(FileStream &fs, const IEPatchModel *model, int &totalitems, int &curritem) const;
    void SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem) const;

    BOOL OnImportModelCache(HModelCache *hmc) const;
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc) const;
    [[nodiscard]] static IEPatchModel *ImportAV2(const String &pfilename);
    static void LoadBones(FileStream &fs, IEBone **parentuplink, IEBone *parent);

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
