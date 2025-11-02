// Yves  2005-11-22  \Master13.0\Plugin\Shaders\PlanetGlow\Shader.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "ShadeDll.h"
#include "SDK/HPropert.h"
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShaderApp
// See Shader.cpp for the implementation of this class
//
class CShaderApp final : public CPluginApp {
public:
    HPercentPropertyInfo *m_FalloffInfo;
    HPercentPropertyInfo *m_GlowInfo;
    HPercentPropertyInfo *m_FadeInfo;
    HPercentPropertyInfo *m_XparencyInfo;
    HColorPropertyInfo *m_LoColorInfo;
    HColorPropertyInfo *m_HiColorInfo;

    CShaderApp();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CShaderApp)
    //}}AFX_VIRTUAL
    BOOL InitInstance() override;
    int ExitInstance() override;

    //{{AFX_MSG(CShaderApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

CShaderApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
