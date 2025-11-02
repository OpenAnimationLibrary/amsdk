// KB  2/4/2003  \Ken105\Plugin\Flock\Swarm\flockapp.cpp
//

#include "StdAfx.h"
#include "flockapp.h"
#include "resource.h"		// main symbols

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
        DOC(
            "This value will determine the density of the swarm. <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->This \
 will also affect the behavior of the individual members, since the density \
 will determine how much and how often they have to modify their paths. \
 <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->A fly swarm \
 will probably be less dense than a bee swarm."
        ));

    string.LoadString(IDS_JITTER);
    m_jitterinfo = HIntPropertyInfo::New(string, "Jitter");
    m_jitterinfo->SetDefaultValue(5);
    m_jitterinfo->SetMinValue(0);
    m_jitterinfo->SetMaxValue(10000);
    m_jitterinfo->SetDocumentation(
        DOC("This is a randomizing value used to make the flock more chaotic. <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->The \
 higher this value, the more the members of the flock will adjust their \
 direction."));

    string.LoadString(IDS_MAXSPEED);
    m_maxspeedinfo = HFloatPropertyInfo::New(string, "MaxSpeed");
    m_maxspeedinfo->SetDefaultValue(10.F);
    m_maxspeedinfo->SetMinValue(0.F);
    m_maxspeedinfo->SetMaxValue(10000.0f);
    m_maxspeedinfo->SetDocumentation(
        DOC(
            "This is the maximum speed of each member of the swarm. <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}--> \
 (Think of it as a speed limit). <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->You \
 will probably want to use a lower value for flies, and a higher value \
 for bees and knats."
        ));

    string.LoadString(IDS_ACCELERATION);
    m_accelerationinfo = HFloatPropertyInfo::New(string, "Acceleration");
    m_accelerationinfo->SetDefaultValue(10.F);
    m_accelerationinfo->SetMinValue(0.F);
    m_accelerationinfo->SetMaxValue(10000.0f);
    m_accelerationinfo->SetDocumentation(
        DOC("Use this value to affect the steering ability of the swarm members. \
 <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->The higher \
 the value, the tighter the members can turn and readjust their paths."));

    return CPluginApp::InitInstance();
}

int CFlockApp::ExitInstance() {
    // Delete Infos Here

    delete m_mindistanceinfo;
    delete m_jitterinfo;
    delete m_maxspeedinfo;
    delete m_accelerationinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlockApp object

CFlockApp theApp;
