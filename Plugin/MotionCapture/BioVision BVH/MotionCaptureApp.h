// MC.h : main header file for the MOTIONCAPTURE DLL
//

#pragma once
#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif
#include "SDK/Misc.h"
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMCApp
// See MC.cpp for the implementation of this class
//

class CMCApp final : public CPluginApp {
public:
    CMCApp() noexcept = default;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMCApp)
    //}}AFX_VIRTUAL
    BOOL InitInstance() override;
    int ExitInstance() override;

    //{{AFX_MSG(CMCApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
