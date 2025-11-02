// TurbApp.h : main header file for the TURB DLL
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/Misc.h"
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CTurbApp
// See TurbApp.cpp for the implementation of this class
//

class CTurbApp final : public CPluginApp {
public:
    FractalNoiseUI m_NoiserUI;
    TransfererUI m_TransfererUI;
    SamplerUI m_SamplerUI;

    CTurbApp() noexcept = default;
    BOOL InitInstance() override;
    int ExitInstance() override;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTurbApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CTurbApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CTurbApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
