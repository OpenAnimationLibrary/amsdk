// KB  8/24/01  \Ken90\Plugin\Textures\Joyce\TexApp.h
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
    HColorPropertyInfo *m_papercolorinfo{};
    HColorPropertyInfo *m_pencilcolorinfo{};
    HColorPropertyInfo *m_washcolorinfo{};
    HColorPropertyInfo *m_dark1colorinfo{};
    HColorPropertyInfo *m_dark2colorinfo{};
    HFloatPropertyInfo *m_pencilnoiseinfo{};
    HFloatPropertyInfo *m_pencilfreqinfo{};
    HFloatPropertyInfo *m_pencilsizeinfo{};
    HFloatPropertyInfo *m_washnoiseinfo{};
    HFloatPropertyInfo *m_washfreqinfo{};
    HFloatPropertyInfo *m_washsizeinfo{};
    HFloatPropertyInfo *m_dark1noiseinfo{};
    HFloatPropertyInfo *m_dark1freqinfo{};
    HFloatPropertyInfo *m_dark1sizeinfo{};
    HFloatPropertyInfo *m_dark2noiseinfo{};
    HFloatPropertyInfo *m_dark2freqinfo{};
    HFloatPropertyInfo *m_dark2sizeinfo{};
    HFloatPropertyInfo *m_mixinfo{};
    HFloatPropertyInfo *m_freqinfo{};
    HVectorPropertyInfo *m_lightinfo{};
    HClipPropertyInfo *m_bitmapinfo{};

    short m_noiz_tbl[MAXX][MAXY][MAXZ];

    CTextureApp();
    BOOL InitInstance() override;
    int ExitInstance() override;
    // CUSTOM TEXTURE FUNCTIONS
    void InitNoiseTable();
    [[nodiscard]] float Noise(Vector p) const;
    static float fBm(Vector P, float freq);

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
