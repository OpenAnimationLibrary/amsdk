// Dan  3/24/2003  \DanLP105\Plugin\Textures\Crumple\TexApp.cpp
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

CTextureApp::CTextureApp() = default;

BOOL CTextureApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here

    string.LoadString(IDS_CLIP);
    m_clipinfo = HClipPropertyInfo::New(string, "Bitmap");
    m_clipinfo->SetDrawWhen(HClipPropertyInfo::DRAWIFMATERIALS);
/*
    string.LoadString(IDS_INTENSITY);
    m_intensityinfo = HFloatPropertyInfo::New(string, "Intensity");
    m_intensityinfo->SetDefaultValue(100.0F);
    m_intensityinfo->SetMinValue(0.0F);
    m_intensityinfo->SetMaxValue(5000.0F);
    */
    string.LoadString(IDS_OPACITY);
    m_opacityinfo = HFloatPropertyInfo::New(string, "Opacity");
    m_opacityinfo->SetDefaultValue(100.0F);
    m_opacityinfo->SetMinValue(0.0F);
    m_opacityinfo->SetMaxValue(100.0F);
    m_opacityinfo->SetDrawWhen(HFloatPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_ADDITIV);
    m_additivinfo = HBoolPropertyInfo::New(string, "Additive");
    m_additivinfo->SetDefaultValue(FALSE);
    m_additivinfo->SetDocumentation("Adds the color of the map to the underlying color of the object.");
    m_additivinfo->SetDrawWhen(HBoolPropertyInfo::DRAWIFMATERIALS);
/*
    string.LoadString(IDS_DECAL);
    m_decalinfo = HPointerPropertyInfo::New(string, "Decal");
*/
    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    delete m_clipinfo;
//    delete m_intensityinfo;
    delete m_opacityinfo;
    delete m_additivinfo;
//    delete m_decalinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CTextureApp construction

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
