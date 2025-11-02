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
#include "HashTime.h"
#include "SDK/Misc.h"

#define VERSION 2L

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See IE.cpp for the implementation of this class
//

// include macromedia flash libraries
#include "./Flash/F3SDK.h"

class HModelCache;
class HChor;
class FileStream;
class String;
class HProgressBar;
class HActionCache;

class CHxtApp final : public CPluginApp {
public:
    IEPolyModelParms m_iemp{};
    HProgressBar *m_hprogressbar{nullptr};

    CHxtApp();

    static void ReportExportError(const String &filename);

    BOOL OnExportActionCache(HActionCache *hac);
    BOOL OnExportChor(HChor *chor);

    BOOL ExportDialog(HChor *chor, char *name, const Time &length);
    BOOL Export(HChor *chor, char *name, const Time &length, BOOL previewMode);

    static void StartSWF(FObjCollection &flashObjects);
    static void FinishSWF(FObjCollection &flashObjects, const String &filename);

    BOOL ExportSWF(FObjCollection &flashObjects, IEPolyModel *model, HChor *chor, Time time, const String &filename, int totalitems, int currentitem);
    static float PointDistance(float x1, float y1, float z1, float x2, float y2, float z2);
//    void PrepareCalc(Vector &vec);
//    int CalcX();
//    int CalcY();
//    void CalcTrig();
//    void Preprocessing(IEPolyModel *model);
    static void SavePolys(FObjCollection &flashObjects, FileStream &fs, IEPolyModel *model, HChor *chor, Time time, HProgressBar *progressbar, int totalitems, int currentitem);

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
