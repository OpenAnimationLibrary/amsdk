// NAP  3/3/2003  \Noel105\Plugin\Post\Gamma\PostApp.cpp

#include "StdAfx.h"
#include "PostApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostApp

BEGIN_MESSAGE_MAP(CPostApp, CWinApp)
        //{{AFX_MSG_MAP(CPostApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostApp construction

CPostApp::CPostApp(): m_styleinfo{nullptr}, m_gammainfo{nullptr} {}

/*
   static TypeInfo f_gammapresets[] = {
      TypeInfo( "OFF",     IDS_OFF, 
      DOC("No Gamma Correction will be applied.") ),
      TypeInfo( "Monitor", IDS_MONITOR, 
      DOC("Gamma correct for a computer monitor.") ),
      TypeInfo( "NTSC",    IDS_NTSC, 
      DOC("Gamma correct for an NTSC video signal.") ),
      TypeInfo( "Custom",  IDS_CUSTOM, 
      DOC("Allows you to set your own gamma value.") ) };
   static TypePropertyInfo    f_isgammainfo(                    5,   
   DOC("Select this option to change the image’s dynamic range \
   as a post process, (the gamma value embedded in the file will be set to the gamma \
   value set in the Output Settings, not this value, but the pixels will be adjusted in the image using this value.  \
   Use this option to change the look of a render image as an effect."),
   IDS_GAMMA, f_gammapresets, NUMELEMENTS(f_gammapresets), IDL_GAMMA, 0, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLEALWAYS, PropertyInfo::CONSTANT|PropertyInfo::NOTIFYANIMOBJECTVALUECHANGED );
      static FloatPropertyInfo   f_gammaamountinfo(
         0, DOC("The gamma to adjust the image to."),
         IDS_AMOUNT,             IDL_GAMMAAMOUNT,     0, 1.5, 0,  10, 1, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES );
*/
BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_NONE]->SetMatchName("NONE");
    string.LoadString(IDS_NONE);
    m_styletypes[STYLE_NONE]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_MONITOR]->SetMatchName("Monitor");
    string.LoadString(IDS_MONITOR);
    m_styletypes[STYLE_MONITOR]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_NTSC]->SetMatchName("NTSC");
    string.LoadString(IDS_NTSC);
    m_styletypes[STYLE_NTSC]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_styletypes[STYLE_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_STYLE);
    m_styleinfo = HTypePropertyInfo::New(string, "Style", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_MONITOR);

    string.LoadString(IDS_GAMMA);
    m_gammainfo = HFloatPropertyInfo::New(string, "Gamma");
    m_gammainfo->SetDefaultValue(GAMMA_MONITOR);
    m_gammainfo->SetMinValue(0.F);
    m_gammainfo->SetMaxValue(10.F);
    m_gammainfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_gammainfo;
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
