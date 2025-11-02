// KB  9/7/01  \Ken90\Plugin\Textures\MultiSky\TexApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/Misc.h"

#include "SDK/HPropert.h"

constexpr int MAXX = 100;
constexpr int MAXY = 100;
constexpr int MAXZ = 5;

/////////////////////////////////////////////////////////////////////////////
// CTextureApp
// See Texture.cpp for the implementation of this class
//

class CTextureApp final : public CPluginApp {
public:
    enum CLOUD_TYPES {
        TYPE_CLASSIC = 0,
        TYPE_CIRRUS,
        TYPE_FLUFFY,
        TYPE_OREN_NAYAR,
        TYPE_SWIRL,
        TYPE_PUFFY,
        TYPE_NUMBER
    };

    HFloatPropertyInfo *m_heightinfo{};
    HFloatPropertyInfo *m_coverinfo{};
    HIntPropertyInfo *m_octavesinfo{};
    HFloatPropertyInfo *m_hazeinfo{};
    HFloatPropertyInfo *m_sintensityinfo{};
    HBoolPropertyInfo *m_siinfo{};
    HFloatPropertyInfo *m_transinfo{};
    HTypePropertyInfo *m_typeinfo{};
    HVectorPropertyInfo *m_suninfo{};
    HTranslatePropertyInfo *m_offsetinfo{};
    HScalePropertyInfo *m_scaleinfo{};
    HColorPropertyInfo *m_hcolorinfo{};
    HColorPropertyInfo *m_scolorinfo{};
    HColorPropertyInfo *m_c1colorinfo{};
    HColorPropertyInfo *m_c2colorinfo{};
    HColorPropertyInfo *m_bcolorinfo{};
    TypeInfoArray m_typeinfoarray;

    short m_noiz_tbl[MAXX][MAXY][MAXZ];
    float m_cloud_tbl[MAXX][MAXY][MAXZ];

    CTextureApp();
    BOOL InitInstance() override;
    int ExitInstance() override;

    void InitNoiseTable();
    [[nodiscard]] float Noise(Vector p) const;
    [[nodiscard]] float CNoise(Vector p) const;

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
