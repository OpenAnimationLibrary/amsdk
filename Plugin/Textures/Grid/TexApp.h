// KB  3/2/01  \Ken90\Plugin\Textures\Grid\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CTextureApp
// See Texture.cpp for the implementation of this class
//

enum GRIDTYPE {
    GRIDTYPE_PLANE=0,
    GRIDTYPE_LINE,
    GRIDTYPE_CUBE,
    GRIDTYPE_DOT,
    GRIDTYPE_NUMBER
};

class CTextureApp final : public CPluginApp {
public:
    HFloatPropertyInfo *m_transpinfo{};
    HVectorPropertyInfo *m_origininfo{}, *m_widthinfo{}, *m_intervalinfo{};
    HColorPropertyInfo *m_lcolorinfo{};
    HTypePropertyInfo *m_gtypeinfo{};
    TypeInfoArray m_typeinfoarray;

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
