// NAP  3/3/2003  \Noel105\Plugin\Post\Dither\PostApp.h
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

#define BITS_24_LEVELS 576
#define BITS_16_LEVELS 256
#define BITS_8_LEVELS  64

enum { BITS_24, BITS_16, BITS_8, BITS_CUSTOM, NUM_BIT_STYLES };

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_bittypes;
    HTypePropertyInfo *m_bittypeinfo;
    HIntPropertyInfo *m_levelsinfo;

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
