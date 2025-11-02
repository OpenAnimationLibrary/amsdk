// NAP  3/3/2003  \Noel105\Plugin\Post\Gamma\PostApp.h
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

#define GAMMA_NONE    1.F
#define GAMMA_MONITOR 1.8f
#define GAMMA_NTSC    2.2f

enum { STYLE_NONE, STYLE_MONITOR, STYLE_NTSC, STYLE_CUSTOM, NUM_STYLES };

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_styletypes;
    HTypePropertyInfo *m_styleinfo;
    HFloatPropertyInfo *m_gammainfo;

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
