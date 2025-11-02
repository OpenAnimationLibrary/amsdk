// NAP  3/3/2003  \Noel105\Plugin\Post\FilmGrain\PostApp.h
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
#define FILMGRAINSIZE100ASA    0.4f
#define FILMGRAINAMOUNT100ASA (20.0f/UNIT)

#define FILMGRAINSIZE200ASA    0.5F
#define FILMGRAINAMOUNT200ASA (30.0f/UNIT)

#define FILMGRAINSIZE400ASA    1.F
#define FILMGRAINAMOUNT400ASA (40.0f/UNIT)

enum { STYLE_100ASA, STYLE_200ASA, STYLE_400ASA, STYLE_CUSTOM, NUM_STYLES };

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_styletypes;
    HTypePropertyInfo *m_styleinfo;
    HPercentPropertyInfo *m_sizeinfo;
    HPercentPropertyInfo *m_amountinfo;

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
