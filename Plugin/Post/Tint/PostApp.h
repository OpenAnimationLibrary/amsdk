// NAP  3/3/2003  \Noel105\Plugin\Post\Tint\PostApp.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/Misc.h"
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CPostApp
// See Post.cpp for the implementation of this class
//

#define BW_LIGHT    RGBFloat(1.F)
#define BW_DARK     RGBFloat(0.F)
#define BW_PERCENT  1.F

#define COBALT_LIGHT   RGBFloat(.282f, .090f, .803f)
#define COBALT_DARK    RGBFloat(0.F)
#define COBALT_PERCENT 1.F

#define SEPIA_LIGHT   RGBFloat(.996f, .866f, .674f)
#define SEPIA_DARK    RGBFloat(0.F)
#define SEPIA_PERCENT 1.F

#define XRAY_LIGHT   RGBFloat(0.F)
#define XRAY_DARK    RGBFloat(1.F)
#define XRAY_PERCENT 1.F

enum { STYLE_BW, STYLE_COBALT, STYLE_SEPIA, STYLE_XRAY, STYLE_RAINBOW, STYLE_CUSTOM, NUM_STYLES };

class CPostApp final : public CPluginApp {
public:
    TypeInfoArray m_styletypes;
    HTypePropertyInfo *m_styleinfo;
    HColorPropertyInfo *m_lightcolorinfo;
    HColorPropertyInfo *m_darkcolorinfo;
    HPercentPropertyInfo *m_percentinfo;

    CPostApp();
    BOOL InitInstance() override;
    int ExitInstance() override;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPostApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CPostApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

CPostApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
