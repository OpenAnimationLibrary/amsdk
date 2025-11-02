// Dan  3/24/2003  \DanLP105\Plugin\Textures\Projection\TexApp.cpp
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
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    string.LoadString(IDS_IMAGE);
    m_clipinfo = HClipPropertyInfo::New(string, "Clip");

    m_typeinfoarray.SetArraySize(TYPE_NUMBER);
    string.LoadString(IDS_PLANAR);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[0]->SetMatchName("Planar");
    string.LoadString(IDS_CYLINDRICAL);
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[1]->SetMatchName("Cylindrical");
    string.LoadString(IDS_SPHERICAL);
    m_typeinfoarray[2]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[2]->SetMatchName("Spherical");
    string.LoadString(IDS_METHOD);
    m_typeinfo = HTypePropertyInfo::New(string, "Type", &m_typeinfoarray);
    m_typeinfo->SetDefaultIndex(SPHERICAL);
    m_typeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_kindinfoarray.SetArraySize(KIND_NUMBER);

    string.LoadString(IDS_COLOR);
    m_kindinfoarray[0]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[0]->SetMatchName("Color");

    string.LoadString(IDS_TRANSPARENCY);
    m_kindinfoarray[1]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[1]->SetMatchName("Transparency");

    string.LoadString(IDS_BUMP);
    m_kindinfoarray[2]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[2]->SetMatchName("Bump");

    string.LoadString(IDS_SPECULARSIZE);
    m_kindinfoarray[3]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[3]->SetMatchName("SpecularSize");

    string.LoadString(IDS_SPECULARINTENSITY);
    m_kindinfoarray[4]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[4]->SetMatchName("SpecularIntensity");

    string.LoadString(IDS_DIFFUSE);
    m_kindinfoarray[5]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[5]->SetMatchName("Diffuse");

    string.LoadString(IDS_REFLECTIVITY);
    m_kindinfoarray[6]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[6]->SetMatchName("Mirror");

    string.LoadString(IDS_AMBIANCE);
    m_kindinfoarray[7]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[7]->SetMatchName("Ambiance");

    string.LoadString(IDS_COOKIECUT);
    m_kindinfoarray[8]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[8]->SetMatchName("CookieCut");

    string.LoadString(IDS_NORMAL);
    m_kindinfoarray[9]->SetLocalizedName(string.GetBuffer());
    m_kindinfoarray[9]->SetMatchName("Normal");

    string.LoadString(IDS_TYPE);
    m_kindinfo = HTypePropertyInfo::New(string, "Kind", &m_kindinfoarray);
    m_kindinfo->SetDefaultIndex(OPAQUEMAP);
    m_kindinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_PERCENTAGE);
    m_valueinfo = HFloatPropertyInfo::New(string, "Percentage");
    m_valueinfo->SetDefaultValue(100.F);
    m_valueinfo->SetMinValue(-hash_constants::max_float);
    m_valueinfo->SetMaxValue(hash_constants::max_float);
    m_valueinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SIZE);
    m_sizeinfo = HVector2PropertyInfo::New(string, "Size");
    m_sizeinfo->GetX()->SetDefaultValue(100.F);
    m_sizeinfo->GetX()->SetMinValue(1e-8F);
    m_sizeinfo->GetX()->SetMaxValue(hash_constants::big_float);
    m_sizeinfo->GetY()->SetDefaultValue(100.F);
    m_sizeinfo->GetY()->SetMinValue(1e-8F);
    m_sizeinfo->GetY()->SetMaxValue(hash_constants::big_float);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_clipinfo;
    delete m_kindinfo;
    delete m_typeinfo;
    delete m_valueinfo;
    delete m_sizeinfo;
    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
