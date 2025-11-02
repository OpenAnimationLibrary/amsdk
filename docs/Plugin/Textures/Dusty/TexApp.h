// KB  3/2/01  \Ken90\Plugin\Textures\Dusty\TexApp.h
//
#pragma once
#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
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
    HFloatPropertyInfo *m_noiseinfo{}, *m_freqinfo{}, *m_boinfo{}, *m_mixinfo{};
    HColorPropertyInfo *m_bcolorinfo{};
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
