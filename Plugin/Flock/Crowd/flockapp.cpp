// KB  2/4/2003  \Ken105\Plugin\Flock\Crowd\flockapp.cpp
//

#include "StdAfx.h"
#include "flockapp.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlockApp

BEGIN_MESSAGE_MAP(CFlockApp, CWinApp)
        //{{AFX_MSG_MAP(CFlockApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlockApp construction

CFlockApp::CFlockApp() = default;

BOOL CFlockApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    string.LoadString(IDS_MINDISTANCE);
    m_mindistanceinfo = HFloatPropertyInfo::New(string, "MinDistance");
    m_mindistanceinfo->SetDefaultValue(50.0f);
    m_mindistanceinfo->SetMinValue(0.F);
    m_mindistanceinfo->SetMaxValue(10000.0f);
    m_mindistanceinfo->SetDocumentation(
        DOC("This value determines the density of the crowd. \
You will want to adjust this according to the scale of your object.  The members \
of the crowd will be placed at least this distance from their nearest neighbor."));

    string.LoadString(IDS_XZSCALEOFFSET);
    m_xzscaleoffsetinfo = HFloatPropertyInfo::New(string, "XZScaleOffset");
    m_xzscaleoffsetinfo->SetDefaultValue(0.F);
    m_xzscaleoffsetinfo->SetMinValue(0.F);
    m_xzscaleoffsetinfo->SetMaxValue(100.F);
    m_xzscaleoffsetinfo->SetDocumentation(
        DOC(
            "Objects in a crowd or forest are rarely \
the same exact size or scale.  This value determines how much they vary in width, \
and depth. The same random value will be used for both width and depth.  The higher \
the percentage, the more they will differ in XZ scale."
        ));

    string.LoadString(IDS_YSCALEOFFSET);
    m_yscaleoffsetinfo = HFloatPropertyInfo::New(string, "YScaleOffset");
    m_yscaleoffsetinfo->SetDefaultValue(0.F);
    m_yscaleoffsetinfo->SetMinValue(0.F);
    m_yscaleoffsetinfo->SetMaxValue(100.F);
    m_yscaleoffsetinfo->SetDocumentation(DOC("This value is similar to XZ scale %, but governs height. \
This is perticularly useful for plants and trees, because they tend to vary more \
in height."));

    string.LoadString(IDS_ROLLOFFSET);
    m_rolloffsetinfo = HFloatPropertyInfo::New(string, "RollOffset");
    m_rolloffsetinfo->SetDefaultValue(0.F);
    m_rolloffsetinfo->SetMinValue(0.F);
    m_rolloffsetinfo->SetMaxValue(360.0f);
    m_rolloffsetinfo->SetDocumentation(DOC("This controls the maximum random roll of each \
member of the crowd.  If you do not want all the members facing the same direction, \
increase this value."));

    string.LoadString(IDS_PROPORTIONAL);
    m_proportionalinfo = HBoolPropertyInfo::New(string, "Proportional");
    m_proportionalinfo->SetDefaultValue(FALSE);
    m_proportionalinfo->SetDocumentation(
        DOC(
            "Select this option to keep height \
proportional to the width and depth.  You will probably want to select this for \
characters.  Plants and trees look more natural with a variety of proportions than \
people do.  Characters tend to look distorted unless these proportions are maintained."
        ));

    return CPluginApp::InitInstance();
}

int CFlockApp::ExitInstance() {
    // Delete Infos Here
    delete m_mindistanceinfo;
    delete m_xzscaleoffsetinfo;
    delete m_yscaleoffsetinfo;
    delete m_rolloffsetinfo;
    delete m_proportionalinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlockApp object

CFlockApp theApp;
