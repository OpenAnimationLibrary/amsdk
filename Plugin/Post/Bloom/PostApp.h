// NAP  3/3/2003  \Noel105\Plugin\Post\Bloom\PostApp.h
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

#define DAY_STRENGTH  0.9f
#define DAY_THRESHOLD 0.25f
#define DAY_RADIUS    6

#define NIGHT_STRENGTH  0.75f
#define NIGHT_THRESHOLD 0.3f
#define NIGHT_RADIUS    6

enum { STYLE_DAY, STYLE_NIGHT, STYLE_CUSTOM, NUM_STYLES };

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_styletypes;
    HTypePropertyInfo *m_styleinfo;
    HPercentPropertyInfo *m_strengthinfo;
    HPercentPropertyInfo *m_thresholdinfo;
    HIntPropertyInfo *m_radiusinfo;

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
