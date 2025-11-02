// Yves Poiossant  2004-01-15  \My Plugins\Shaders\Skin\Shader.h
//

#pragma once
#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "resource.h"		// main symbols
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CShaderApp
// See Shader.cpp for the implementation of this class
//
class CShaderApp final : public CPluginApp {
public:
    HPercentPropertyInfo *m_FalloffInfo;
    HPercentPropertyInfo *m_RoughnessInfo;
    HPercentPropertyInfo *m_ShiftStartInfo;
    HPercentPropertyInfo *m_ShiftEndInfo;
    HPercentPropertyInfo *m_SaturationInfo;
    HPercentPropertyInfo *m_HueShiftInfo;
    HColorPropertyInfo *m_BloodColorInfo;
    HPercentPropertyInfo *m_HueStrengthInfo;

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
