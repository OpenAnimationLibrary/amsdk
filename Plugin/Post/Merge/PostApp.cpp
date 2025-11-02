// NAP  3/3/2003  \Noel105\Plugin\Post\Add\PostApp.cpp
//

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

CPostApp::CPostApp(): m_mergetypeinfo{nullptr}, m_percentinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_mergetypes.SetArraySize(NUM_MERGES);
    m_mergetypes[ID_ADD]->SetMatchName("Add");
    string.LoadString(IDS_ADD);
    m_mergetypes[ID_ADD]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_SUBTRACT]->SetMatchName("Subtract");
    string.LoadString(IDS_SUBTRACT);
    m_mergetypes[ID_SUBTRACT]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_MULTIPLY]->SetMatchName("Multiply");
    string.LoadString(IDS_MULTIPLY);
    m_mergetypes[ID_MULTIPLY]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_DIVIDE]->SetMatchName("Divide");
    string.LoadString(IDS_DIVIDE);
    m_mergetypes[ID_DIVIDE]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_SCREEN]->SetMatchName("Screen");
    string.LoadString(IDS_SCREEN);
    m_mergetypes[ID_SCREEN]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_DARKEN]->SetMatchName("Darken");
    string.LoadString(IDS_DARKEN);
    m_mergetypes[ID_DARKEN]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_LIGHTEN]->SetMatchName("Lighten");
    string.LoadString(IDS_LIGHTEN);
    m_mergetypes[ID_LIGHTEN]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_DIFFERENCE]->SetMatchName("Difference");
    string.LoadString(IDS_DIFFERENCE);
    m_mergetypes[ID_DIFFERENCE]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_NEGATION]->SetMatchName("Negation");
    string.LoadString(IDS_NEGATION);
    m_mergetypes[ID_NEGATION]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_EXCLUSION]->SetMatchName("Exclusion");
    string.LoadString(IDS_EXCLUSION);
    m_mergetypes[ID_EXCLUSION]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_OVERLAY]->SetMatchName("Overlay");
    string.LoadString(IDS_OVERLAY);
    m_mergetypes[ID_OVERLAY]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_HARDLIGHT]->SetMatchName("HardLight");
    string.LoadString(IDS_HARDLIGHT);
    m_mergetypes[ID_HARDLIGHT]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_SOFTLIGHT]->SetMatchName("SoftLight");
    string.LoadString(IDS_SOFTLIGHT);
    m_mergetypes[ID_SOFTLIGHT]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_DODGE]->SetMatchName("Dodge");
    string.LoadString(IDS_DODGE);
    m_mergetypes[ID_DODGE]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_SOFTDODGE]->SetMatchName("FoftDodge");
    string.LoadString(IDS_SOFTDODGE);
    m_mergetypes[ID_SOFTDODGE]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_INVDODGE]->SetMatchName("InvDodge");
    string.LoadString(IDS_INVDODGE);
    m_mergetypes[ID_INVDODGE]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_BURN]->SetMatchName("Burn");
    string.LoadString(IDS_BURN);
    m_mergetypes[ID_BURN]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_SOFTBURN]->SetMatchName("SofBurn");
    string.LoadString(IDS_SOFTBURN);
    m_mergetypes[ID_SOFTBURN]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_INVBURN]->SetMatchName("InvBurn");
    string.LoadString(IDS_INVBURN);
    m_mergetypes[ID_INVBURN]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_REFLECT]->SetMatchName("Reflect");
    string.LoadString(IDS_REFLECT);
    m_mergetypes[ID_REFLECT]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_GLOW]->SetMatchName("Glow");
    string.LoadString(IDS_GLOW);
    m_mergetypes[ID_GLOW]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_FREEZE]->SetMatchName("Freeze");
    string.LoadString(IDS_FREEZE);
    m_mergetypes[ID_FREEZE]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_HEAT]->SetMatchName("Heat");
    string.LoadString(IDS_HEAT);
    m_mergetypes[ID_HEAT]->SetLocalizedName(string.GetBuffer());
    m_mergetypes[ID_STAMP]->SetMatchName("Stamp");
    string.LoadString(IDS_STAMP);
    m_mergetypes[ID_STAMP]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_SELECT);
    m_mergetypeinfo = HTypePropertyInfo::New(string, "MergeOperation", &m_mergetypes);
    m_mergetypeinfo->SetDefaultIndex(ID_ADD);

    string.LoadString(IDS_PERCENT);
    m_percentinfo = HPercentPropertyInfo::New(string, "Percent");
    m_percentinfo->SetDefaultValue(1.F);
    //   m_percentinfo->SetConstant(TRUE);//#6491
    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_mergetypeinfo;
    delete m_percentinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
