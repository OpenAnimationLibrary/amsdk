// Dan  3/24/2003  \DanLP105\Plugin\Textures\Environment\TexApp.cpp

#include "StdAfx.h"
#include "TexApp.h"
#include "resource.h"

CTextureApp theApp;

BOOL CTextureApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here

    string.LoadString(IDS_CLIP);
    m_clipinfo = HClipPropertyInfo::New(string, "Bitmap");
    m_clipinfo->SetDocumentation(DOC("Image used that the object will reflect."));

    string.LoadString(IDS_OPACITY);
    m_opacityinfo = HFloatPropertyInfo::New(string, "Opacity");
    m_opacityinfo->SetDefaultValue(100.F);
    m_opacityinfo->SetMinValue(0.F);
    m_opacityinfo->SetMaxValue(100.F);
    m_opacityinfo->SetDocumentation(DOC("The Opacity value allows you to change how much of the underlying color of the model shows through the map."));
    m_opacityinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_ADDITIVE);
    m_isadditiveinfo = HBoolPropertyInfo::New(string, "Additive");
    m_isadditiveinfo->SetDefaultValue(FALSE);
    m_isadditiveinfo->SetDocumentation(DOC("Adds the color of the map to the underlying color of the object."));
    m_isadditiveinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_clipinfo;
    delete m_opacityinfo;
    delete m_isadditiveinfo;

    return CPluginApp::ExitInstance();
}
