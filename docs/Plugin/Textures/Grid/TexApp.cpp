// Dan  3/24/2003  \DanLP105\Plugin\Textures\Grid\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"
#include "F_Protos.h"
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
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    string.LoadString(IDS_LCOLOR);
    m_lcolorinfo = HColorPropertyInfo::New(string, "LineColor");
    m_lcolorinfo->GetRed()->SetDefaultValue(0.39F);
    m_lcolorinfo->GetGreen()->SetDefaultValue(0.39F);
    m_lcolorinfo->GetBlue()->SetDefaultValue(0.39F);

    string.LoadString(IDS_TRANSPARENCY);
    m_transpinfo = HFloatPropertyInfo::New(string, "Transparency");
    m_transpinfo->SetDefaultValue(0.F);
    m_transpinfo->SetMinValue(0.F);
    m_transpinfo->SetMaxValue(100.F);
    m_transpinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_typeinfoarray.SetArraySize(GRIDTYPE_NUMBER);
    m_typeinfoarray[0]->SetMatchName("GRIDTYPE_PLANE");
    string.LoadString(IDS_PLANE);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[1]->SetMatchName("GRIDTYPE_LINE");
    string.LoadString(IDS_LINE);
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[2]->SetMatchName("GRIDTYPE_CUBE"); 
    string.LoadString(IDS_CUBE);
    m_typeinfoarray[2]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[3]->SetMatchName("GRIDTYPE_DOT");
    string.LoadString(IDS_DOT);
    m_typeinfoarray[3]->SetLocalizedName(string.GetBuffer());
    string.LoadString(IDS_GRIDTYPE);
    m_gtypeinfo = HTypePropertyInfo::New(string, "GridType", &m_typeinfoarray);
    m_gtypeinfo->SetDefaultIndex(GRIDTYPE_PLANE);
    m_gtypeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_ORIGIN);
    m_origininfo = HVectorPropertyInfo::New(string, "Origin");
    m_origininfo->GetX()->SetDefaultValue(0.F);
    m_origininfo->GetX()->SetMinValue(1e-8F);
    m_origininfo->GetX()->SetMaxValue(hash_constants::big_float);
    m_origininfo->GetY()->SetDefaultValue(0.F);
    m_origininfo->GetY()->SetMinValue(1e-8F);
    m_origininfo->GetY()->SetMaxValue(hash_constants::big_float);
    m_origininfo->GetZ()->SetMinValue(0.F);
    m_origininfo->GetZ()->SetMinValue(1e-8F);
    m_origininfo->GetZ()->SetMaxValue(hash_constants::big_float);

    string.LoadString(IDS_WIDTH);
    m_widthinfo = HVectorPropertyInfo::New(string, "Width");
    m_widthinfo->GetX()->SetDefaultValue(1.F);
    m_widthinfo->GetX()->SetMinValue(0.F);
    m_widthinfo->GetX()->SetMaxValue(hash_constants::big_float);

    m_widthinfo->GetY()->SetDefaultValue(1.F);
    m_widthinfo->GetY()->SetMinValue(0.F);
    m_widthinfo->GetY()->SetMaxValue(hash_constants::big_float);

    m_widthinfo->GetZ()->SetDefaultValue(1.F);
    m_widthinfo->GetZ()->SetMinValue(0.F);
    m_widthinfo->GetZ()->SetMaxValue(hash_constants::big_float);

    string.LoadString(IDS_INTERVAL);
    m_intervalinfo = HVectorPropertyInfo::New(string, "Interval");
    m_intervalinfo->GetX()->SetDefaultValue(2.F);
    m_intervalinfo->GetX()->SetMinValue(0.F);
    m_intervalinfo->GetX()->SetMaxValue(hash_constants::big_float);

    m_intervalinfo->GetY()->SetDefaultValue(2.F);
    m_intervalinfo->GetY()->SetMinValue(0.F);
    m_intervalinfo->GetY()->SetMaxValue(hash_constants::big_float);

    m_intervalinfo->GetZ()->SetDefaultValue(2.F);
    m_intervalinfo->GetZ()->SetMinValue(0.F);
    m_intervalinfo->GetZ()->SetMaxValue(hash_constants::big_float);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_lcolorinfo;
    delete m_transpinfo;
    delete m_gtypeinfo;
    delete m_origininfo;
    delete m_widthinfo;
    delete m_intervalinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
