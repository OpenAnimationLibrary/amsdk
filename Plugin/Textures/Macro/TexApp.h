// KB  3/2/01  \Ken90\Plugin\Textures\Macro\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "SDK/HPropert.h"
constexpr int MAXX = 50;
constexpr int MAXY = 50;
constexpr int MAXZ = 10;

/////////////////////////////////////////////////////////////////////////////
// CTextureApp
// See Texture.cpp for the implementation of this class
//

class CTextureApp final : public CPluginApp {
public:
    HFloatPropertyInfo *m_boinfo{};
    HFloatPropertyInfo *m_frefinfo{};
    HFloatPropertyInfo *m_foinfo{};
    HFloatPropertyInfo *m_mixinfo{};
    HColorPropertyInfo *m_bcolorinfo{};
    HColorPropertyInfo *m_fcolorinfo{};
    HBoolPropertyInfo *m_usebackinfo{};

    CTextureApp();
    BOOL InitInstance() override;
    int ExitInstance() override;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTextureApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CTextureApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CTextureApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
