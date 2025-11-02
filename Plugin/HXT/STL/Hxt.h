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

#include "resource.h"		// main symbols
#include "IEModel.h"
#include "SDK/Misc.h"

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

struct STL_FACET {
    Vector normal;
    Vector vertex[3];
};

class CHxtApp final : public CPluginApp {
public:
    IEPolyModelParms m_iemp;
    HProgressBar *m_hprogressbar;

    CHxtApp();

    static void ReportExportError(const String &filename);
    static void ReportImportError(const String &filename);

    BOOL OnExportModelCache(HModelCache *hmc);
    BOOL OnExportActionCache(HActionCache *hac);
//    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    BOOL OnExportChor(HChor *hchor);

    static BOOL ExportStl(IEPolyModel *model, const String &filename, const String &modelname, BOOL binary_format = TRUE);
    BOOL OnImportModelCache(HModelCache *hmc) const;
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc) const;
    static IEPolyModel *ImportSTL(const String &pfilename, BOOL isnewimport = TRUE, BOOL isprop = FALSE);

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
