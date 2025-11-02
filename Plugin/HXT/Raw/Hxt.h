// Dan  10/18/00  \Dan90\Plugin\IE\AV2\IE.h
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
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See IE.cpp for the implementation of this class
//

class HCamera;
class FileStream;
class HActionCache;
class HActionCacheContainer;
class HBone;
class HModelCache;

class CHxtApp final : public CPluginApp {
public:
    CHxtApp();

    BOOL OnImportRaw(HCamera *hcamera) const;
    BOOL OnExportRaw(HCamera *hcamera) const;

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
