// KB  9/23/02  \Ken95\Plugin\Textures\Weave\TexApp.h
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
    enum types {
        SPHERICAL,
        CYLINDRICALX,
        CYLINDRICALY,
        CYLINDRICALZ,
        OLDSTYLE,
        MAP_NUMBER
    };

    HFloatPropertyInfo *m_noiseinfo{};
    HFloatPropertyInfo *m_freqinfo{};
    HFloatPropertyInfo *m_bumpinfo{};
    HFloatPropertyInfo *m_brefinfo{};
    HFloatPropertyInfo *m_boinfo{};
    HFloatPropertyInfo *m_frefinfo{};
    HFloatPropertyInfo *m_foinfo{};
    HFloatPropertyInfo *m_fuzzinfo{};
    HFloatPropertyInfo *m_amplitudeinfo{};
    HFloatPropertyInfo *m_mixinfo{};
    HVector2PropertyInfo *m_scaleinfo{};
    HColorPropertyInfo *m_bcolorinfo{};
    HColorPropertyInfo *m_fcolorinfo{};
    HBoolPropertyInfo *m_usebackinfo{};
    HTypePropertyInfo *m_mapinfo{};
    TypeInfoArray m_mapinfoarray;

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
