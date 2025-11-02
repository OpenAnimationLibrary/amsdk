//  2005-11-22  \Master13.0\Shaders\Planet Glow\Shader.cpp
//

#include "StdAfx.h"
#include "Shader.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShaderApp

BEGIN_MESSAGE_MAP(CShaderApp, CWinApp)
    //{{AFX_MSG_MAP(CShaderApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardApp construction

CShaderApp::CShaderApp(): m_FalloffInfo{nullptr}, m_GlowInfo{nullptr}, m_FadeInfo{nullptr}, m_XparencyInfo{nullptr}, m_LoColorInfo{nullptr}, m_HiColorInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString String;

    String.LoadString(IDS_FALLOFF);
    m_FalloffInfo = HPercentPropertyInfo::New(String, "PlanetFallOff");
    m_FalloffInfo->SetDefaultValue(0.75f);
    m_FalloffInfo->SetMinValue(0.F);
    m_FalloffInfo->SetMaxValue(1.F);

    String.LoadString(IDS_GLOW);
    m_GlowInfo = HPercentPropertyInfo::New(String, "PlanetGlow");
    m_GlowInfo->SetDefaultValue(1.1f);
    m_GlowInfo->SetMinValue(0.F);
    m_GlowInfo->SetMaxValue(10.F);

    String.LoadString(IDS_FADE);
    m_FadeInfo = HPercentPropertyInfo::New(String, "PlanetFade");
    m_FadeInfo->SetDefaultValue(2.F);
    m_FadeInfo->SetMinValue(0.F);
    m_FadeInfo->SetMaxValue(10.F);

    String.LoadString(IDS_XPARENCY);
    m_XparencyInfo = HPercentPropertyInfo::New(String, "PlanetTransparency");
    m_XparencyInfo->SetDefaultValue(3.00f);
    m_XparencyInfo->SetMinValue(0.F);
    m_XparencyInfo->SetMaxValue(10.F);

    String.LoadString(IDS_LOCOLOR);
    m_LoColorInfo = HColorPropertyInfo::New(String, "PlanetLoColor");
    m_LoColorInfo->SetDefaultValue(ColorVector(1.F, 0.91f, 0.87f));

    String.LoadString(IDS_HICOLOR);
    m_HiColorInfo = HColorPropertyInfo::New(String, "PlanetHiColor");
    m_HiColorInfo->SetDefaultValue(ColorVector(1.00f, 21.0f, 21.0f));

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_FalloffInfo;
    delete m_GlowInfo;
    delete m_FadeInfo;
    delete m_XparencyInfo;
    delete m_LoColorInfo;
    delete m_HiColorInfo;
    return CPluginApp::ExitInstance();
}

CShaderApp &GetApp() {
    return theApp;
}
