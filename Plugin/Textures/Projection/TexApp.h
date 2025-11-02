// KB  4/6/01  \Ken90\Plugin\Textures\Projection\TexApp.h
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

class CTextureApp final : public CPluginApp {
public:
    enum types { PLANAR, CYLINDRICAL, SPHERICAL, TYPE_NUMBER };

    enum kinds {
        OPAQUEMAP,
        TRANSPARENCYMAP,
        BUMPMAP,
        SPECULARSIZEMAP,
        SPECULARINTENSITYMAP,
        DIFFUSEMAP,
        MIRRORMAP,
        AMBIANCEMAP,
        COOKIECUTMAP,
        NORMALMAP,
        KIND_NUMBER
    };

    HClipPropertyInfo *m_clipinfo{};
    TypeInfoArray m_kindinfoarray;
    HTypePropertyInfo *m_kindinfo{};
    TypeInfoArray m_typeinfoarray;
    HTypePropertyInfo *m_typeinfo{};
    HFloatPropertyInfo *m_valueinfo{};
    HVector2PropertyInfo *m_sizeinfo{};

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
