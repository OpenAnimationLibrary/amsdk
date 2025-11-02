// IE.h : main header file for the IE DLL
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
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/Misc.h"
#include "resource.h"		// main symbols

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
    BOOL ExportPLY(IEPolyModel *model, const String &filename, BOOL saveweights);
    void SaveAttributes(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SaveTextureMaps(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SaveVertexList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SaveNormalList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SavePolys(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const;
    void SaveBones(FileStream &fs, const IEPolyModel *model, int &totalitems, int &curritem, BOOL saveweights) const;
    void SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem, BOOL saveweights) const;

    BOOL OnImportModelCache(HModelCache *hmc) const;
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc) const;
    static IEPolyModel *ImportPLY(const String &pfilename);
    static void LoadBones(FileStream &fs, IEBone **parentuplink, IEBone *parent);

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
