// Dan  3/24/2003  \DanLP105\Plugin\Textures\PencilSketch\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"
#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureApp

BEGIN_MESSAGE_MAP(CTextureApp, CWinApp)
    //{{AFX_MSG_MAP(CTextureApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureApp construction

CTextureApp::CTextureApp() = default;

BOOL CTextureApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    string.LoadString(IDS_USECURRENT);
    m_usebackinfo = HBoolPropertyInfo::New(string, "UseCurrent");
    m_usebackinfo->SetDefaultValue(FALSE);
    m_usebackinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BCOLOR);
    m_bcolorinfo = HColorPropertyInfo::New(string, "BColor");
    m_bcolorinfo->GetRed()->SetDefaultValue(1.F);
    m_bcolorinfo->GetGreen()->SetDefaultValue(1.F);
    m_bcolorinfo->GetBlue()->SetDefaultValue(1.F);

    string.LoadString(IDS_FCOLOR);
    m_fcolorinfo = HColorPropertyInfo::New(string, "FColor");
    m_fcolorinfo->GetRed()->SetDefaultValue(0.35F);
    m_fcolorinfo->GetGreen()->SetDefaultValue(0.35F);
    m_fcolorinfo->GetBlue()->SetDefaultValue(0.35F);

    string.LoadString(IDS_FREFLECT);
    m_frefinfo = HFloatPropertyInfo::New(string, "Falloff");
    m_frefinfo->SetDefaultValue(1.F);
    m_frefinfo->SetMinValue(0.F);
    m_frefinfo->SetMaxValue(100.F);
    m_frefinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FOPAC);
    m_foinfo = HFloatPropertyInfo::New(string, "FOpacity");
    m_foinfo->SetDefaultValue(0.F);
    m_foinfo->SetMinValue(0.F);
    m_foinfo->SetMaxValue(100.F);
    m_foinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BOPAC);
    m_boinfo = HFloatPropertyInfo::New(string, "BOpacity");
    m_boinfo->SetDefaultValue(0.F);
    m_boinfo->SetMinValue(0.F);
    m_boinfo->SetMaxValue(100.F);
    m_boinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_MIX);
    m_mixinfo = HFloatPropertyInfo::New(string, "Mix");
    m_mixinfo->SetDefaultValue(100.F);
    m_mixinfo->SetMinValue(0.F);
    m_mixinfo->SetMaxValue(100.F);
    m_mixinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FUZZ);
    m_fuzzinfo = HFloatPropertyInfo::New(string, "Fuzz");
    m_fuzzinfo->SetDefaultValue(10.F);
    m_fuzzinfo->SetMinValue(0.F);
    m_fuzzinfo->SetMaxValue(100.F);
    m_fuzzinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_XS);
    m_xsinfo = HFloatPropertyInfo::New(string, "XScale");
    m_xsinfo->SetDefaultValue(1.F);
    m_xsinfo->SetMinValue(0.F);
    m_xsinfo->SetMaxValue(100.F);
    m_xsinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_YS);
    m_ysinfo = HFloatPropertyInfo::New(string, "YScale");
    m_ysinfo->SetDefaultValue(1.F);
    m_ysinfo->SetMinValue(0.F);
    m_ysinfo->SetMaxValue(100.F);
    m_ysinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_PENCIL);
    m_pencilinfo = HFloatPropertyInfo::New(string, "Intensity");
    m_pencilinfo->SetDefaultValue(20.0F);
    m_pencilinfo->SetMinValue(0.F);
    m_pencilinfo->SetMaxValue(100.F);
    m_pencilinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_LIGHT);
    m_lightinfo = HVectorPropertyInfo::New(string, "Light");
    m_lightinfo->GetX()->SetDefaultValue(3.0F);
    m_lightinfo->GetX()->SetMinValue(-100.F);
    m_lightinfo->GetX()->SetMaxValue(100.F);
    m_lightinfo->GetY()->SetDefaultValue(3.0F);
    m_lightinfo->GetY()->SetMinValue(-100.F);
    m_lightinfo->GetY()->SetMaxValue(100.F);
    m_lightinfo->GetZ()->SetMinValue(-10.F);
    m_lightinfo->GetZ()->SetMinValue(-100.F);
    m_lightinfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_ROUGH);
    m_roughinfo = HFloatPropertyInfo::New(string, "Rough");
    m_roughinfo->SetDefaultValue(4.0F);
    m_roughinfo->SetMinValue(0.F);
    m_roughinfo->SetMaxValue(100.F);
    m_roughinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_CHATTER);
    m_chatterinfo = HFloatPropertyInfo::New(string, "Chatter");
    m_chatterinfo->SetDefaultValue(0.F);
    m_chatterinfo->SetMinValue(0.F);
    m_chatterinfo->SetMaxValue(100.F);
    m_chatterinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_usebackinfo;
    delete m_bcolorinfo;
    delete m_fcolorinfo;
    delete m_frefinfo;
    delete m_foinfo;
    delete m_boinfo;
    delete m_mixinfo;
    delete m_fuzzinfo;
    delete m_xsinfo;
    delete m_ysinfo;
    delete m_pencilinfo;
    delete m_lightinfo;
    delete m_roughinfo;
    delete m_chatterinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
