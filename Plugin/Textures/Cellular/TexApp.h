// KB  3/2/01  \Ken90\Plugin\Textures\Cellular\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif
#include "SDK/Misc.h"

#include "resource.h"		// main symbols
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
    HFloatPropertyInfo *m_noiseinfo{}, *m_freqinfo{}, *m_bumpinfo{}, *m_brefinfo{}, *m_boinfo{}, *m_frefinfo{},
                       *m_foinfo{}, *m_amplitudeinfo{}, *m_mixinfo{};
    HTranslatePropertyInfo *m_offsetinfo{};
    HScalePropertyInfo *m_scaleinfo{};
    HColorPropertyInfo *m_bcolorinfo{}, *m_fcolorinfo{};
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
