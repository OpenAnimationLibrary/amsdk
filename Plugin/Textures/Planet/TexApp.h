// KB  3/2/01  \Ken90\Plugin\Textures\Planet\TexApp.h
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
    HFloatPropertyInfo *m_featuresizeinfo{};
    HFloatPropertyInfo *m_polardistinfo{};
    HFloatPropertyInfo *m_waterinfo{};
    HFloatPropertyInfo *m_iceinfo{};
    HFloatPropertyInfo *m_bumpinfo{};
    HFloatPropertyInfo *m_freqinfo{};
    HFloatPropertyInfo *m_amplinfo{};
    HFloatPropertyInfo *m_octavesinfo{};
    HFloatPropertyInfo *m_noisemultinfo{};
    HFloatPropertyInfo *m_seedinfo{};
    HFloatPropertyInfo *m_offsetinfo{};
    HFloatPropertyInfo *m_mottlesizeinfo{};
    HFloatPropertyInfo *m_mottlemaginfo{};
    HFloatPropertyInfo *m_depthnoiseinfo{};
    HFloatPropertyInfo *m_maxdepthinfo{};
    HFloatPropertyInfo *m_snowinfo{};

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
