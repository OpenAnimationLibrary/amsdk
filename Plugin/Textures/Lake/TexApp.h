// KB  3/2/01  \Ken90\Plugin\Textures\Lake\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "SDK/HPropert.h"

constexpr int MAXX = 100;
constexpr int MAXY = 5;
constexpr int MAXZ = 100;

/////////////////////////////////////////////////////////////////////////////
// CTextureApp
// See Texture.cpp for the implementation of this class
//

class CTextureApp final : public CPluginApp {
public:
    HFloatPropertyInfo *m_wampinfo{};
    HFloatPropertyInfo *m_woinfo{};
    HFloatPropertyInfo *m_wlacinfo{};
    HFloatPropertyInfo *m_wgaininfo{};
    HFloatPropertyInfo *m_noiseinfo{};
    HFloatPropertyInfo *m_bumpinfo{};
    HFloatPropertyInfo *m_brefinfo{};
    HFloatPropertyInfo *m_boinfo{};
    HFloatPropertyInfo *m_frefinfo{};
    HFloatPropertyInfo *m_foinfo{};
    HFloatPropertyInfo *m_msizeinfo{};
    HFloatPropertyInfo *m_fuzzinfo{};
    HFloatPropertyInfo *m_amplitudeinfo{};
    HFloatPropertyInfo *m_mixinfo{};
    HTranslatePropertyInfo *m_offsetinfo{};
    HScalePropertyInfo *m_scaleinfo{};
    HColorPropertyInfo *m_bcolorinfo{};
    HColorPropertyInfo *m_fcolorinfo{};
    HBoolPropertyInfo *m_usebackinfo{};
    short m_noiz_tbl[MAXX][MAXY][MAXZ]{};

    CTextureApp();
    BOOL InitInstance() override;
    int ExitInstance() override;
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
