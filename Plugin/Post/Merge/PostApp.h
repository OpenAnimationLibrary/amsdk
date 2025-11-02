// Yves  10/11/2006  \Plugin\Post\Merge\PostApp.h
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

enum {
    ID_ADD,
    ID_SUBTRACT,
    ID_MULTIPLY,
    ID_DIVIDE,
    ID_SCREEN,
    ID_DARKEN,
    ID_LIGHTEN,
    ID_DIFFERENCE,
    ID_NEGATION,
    ID_EXCLUSION,
    ID_OVERLAY,
    ID_HARDLIGHT,
    ID_SOFTLIGHT,
    ID_DODGE,
    ID_SOFTDODGE,
    ID_INVDODGE,
    ID_BURN,
    ID_SOFTBURN,
    ID_INVBURN,
    ID_REFLECT,
    ID_GLOW,
    ID_FREEZE,
    ID_HEAT,
    ID_STAMP,
    NUM_MERGES
};

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_mergetypes;
    HTypePropertyInfo *m_mergetypeinfo;
    HPercentPropertyInfo *m_percentinfo;

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
