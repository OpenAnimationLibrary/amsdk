// KB  6/14/01  \Ken90\Plugin\Volume\Dust\VolumeApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeApp
// See Volume.cpp for the implementation of this class
//
#include "SDK/Misc.h"

class CVolumeApp final : public CPluginApp {
public:
    CVolumeApp();

    BOOL InitInstance() override;
    int ExitInstance() override;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVolumeApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CVolumeApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CVolumeApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
