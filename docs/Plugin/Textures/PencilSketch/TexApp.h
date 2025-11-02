// KB  3/1/01  \Ken90\Plugin\Textures\PencilSketch\TexApp.h
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
    HFloatPropertyInfo *m_roughinfo{};
    HFloatPropertyInfo *m_chatterinfo{};
    HFloatPropertyInfo *m_brefinfo{};
    HFloatPropertyInfo *m_boinfo{};
    HFloatPropertyInfo *m_frefinfo{};
    HFloatPropertyInfo *m_foinfo{};
    HFloatPropertyInfo *m_fuzzinfo{};
    HFloatPropertyInfo *m_xsinfo{};
    HFloatPropertyInfo *m_ysinfo{};
    HFloatPropertyInfo *m_pencilinfo{};
    HFloatPropertyInfo *m_mixinfo{};
    HVectorPropertyInfo *m_lightinfo{};
    HBoolPropertyInfo *m_usebackinfo{};
    HColorPropertyInfo *m_bcolorinfo{};
    HColorPropertyInfo *m_fcolorinfo{};
    short m_noiz_tbl[MAXX][MAXY][MAXZ];

    CTextureApp();
    BOOL InitInstance() override;
    int ExitInstance() override;
    // CUSTOM TEXTURE FUNCTIONS
    void InitNoiseTable();
    [[nodiscard]] float Noise(Vector p) const;

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
