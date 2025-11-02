// KB  2/28/01  \Ken90\Plugin\Textures\Crumple\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CTextureApp
// See Texture.cpp for the implementation of this class
//

class CTextureApp final : public CPluginApp {
public:
    HClipPropertyInfo *m_clipinfo;
    HFloatPropertyInfo *m_opacityinfo;
    HBoolPropertyInfo *m_additivinfo;
//    HFloatPropertyInfo *m_intensityinfo;
//    HPointerPropertyInfo *m_decalinfo;

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
