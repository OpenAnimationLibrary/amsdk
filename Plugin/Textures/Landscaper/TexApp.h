// KB  10/23/01  \Ken90\Plugin\Textures\Landscaper\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "SDK/HPropert.h"

constexpr int MAXX = 200;
constexpr int MAXY = 200;
constexpr int MAXZ = 5;

/////////////////////////////////////////////////////////////////////////////
// CTextureApp
// See Texture.cpp for the implementation of this class
//

enum NOISETYPE {
    NOISETYPE_NONOISE = 0,
    NOISETYPE_FRACTAL,
    NOISETYPE_STRATA,
    NOISETYPE_FBM,
    NOISETYPE_TURBULENCE,
    NOISETYPE_STRETCHEDX,
    NOISETYPE_BUMPTURB,
    NOISETYPE_BUMPFBM,
    NOISETYPE_BUMPFOURIER,
    NOISETYPE_NUMBER
};

enum ALT_TYPE {
    ALTTYPE_SLOPE = 0,
    ALTTYPE_FLAT,
    ALTTYPE_NUMBER
};

class CTextureApp final : public CPluginApp {
public:
    HFloatPropertyInfo *m_heightinfo{};
    HFloatPropertyInfo *m_octavesinfo{};
    HFloatPropertyInfo *m_falloffinfo{};
    HFloatPropertyInfo *m_soctinfo{};
    HFloatPropertyInfo *m_sfreqinfo{};
    HFloatPropertyInfo *m_ffreqinfo{};
    HFloatPropertyInfo *m_foctinfo{};
    HFloatPropertyInfo *m_sbumpinfo{};
    HTranslatePropertyInfo *m_offsetinfo{};
    HScalePropertyInfo *m_scaleinfo{};
    HColorPropertyInfo *m_fcolor1info{};
    HColorPropertyInfo *m_fcolor2info{};
    HColorPropertyInfo *m_fcolor3info{};
    HColorPropertyInfo *m_scolor1info{};
    HColorPropertyInfo *m_scolor2info{};
    HColorPropertyInfo *m_scolor3info{};
    HTypePropertyInfo *m_aslopeinfo{};
    HTypePropertyInfo *m_fntinfo{};
    HTypePropertyInfo *m_sntinfo{};
    TypeInfoArray m_typeinfoarray;
    TypeInfoArray m_altinfoarray;
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
