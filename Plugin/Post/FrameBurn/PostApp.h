// NAP  9/11/2003  \Noelsrv105\Plugin\Post\FrameBurn\PostApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/Misc.h"
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CPostApp
// See Post.cpp for the implementation of this class
//
class CPostApp final : public CPluginApp {
public:
    HPercentPropertyInfo *m_fontscaleinfo{nullptr};
    HPercentPropertyInfo *m_opacityinfo{nullptr};
    HBoolPropertyInfo *m_displaynameinfo{nullptr};
    HBoolPropertyInfo *m_displayshadowinfo{nullptr};
    CPostApp();
    BOOL InitInstance() override;
    int ExitInstance() override;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPostApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CPostApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

CPostApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
