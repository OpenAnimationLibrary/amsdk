// NAP  3/3/2003  \Noel105\Plugin\Post\MinMedMax\PostApp.h
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
#define POS_MIN   0.F
#define POS_MED  (50.0f/UNIT)
#define POS_MAX (100.F/UNIT)

enum { STYLE_MIN, STYLE_MED, STYLE_MAX, STYLE_CUSTOM, NUM_STYLES };

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_styletypes;
    HTypePropertyInfo *m_styleinfo;
    HPercentPropertyInfo *m_posinfo;
    HIntPropertyInfo *m_radiusinfo;
    HBoolPropertyInfo *m_isroundinfo;

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
