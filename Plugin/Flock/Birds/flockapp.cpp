// KB  2/4/2003  \Ken105\Plugin\Flock\Birds\flockapp.cpp
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
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    string.LoadString(IDS_MINDISTANCE);
    m_mindistanceinfo = HFloatPropertyInfo::New(string, "MinDistance");
    m_mindistanceinfo->SetDefaultValue(50.0f);
    m_mindistanceinfo->SetMinValue(0.F);
    m_mindistanceinfo->SetMaxValue(10000.0f);
    m_mindistanceinfo->SetDocumentation(DOC("This is the distance that each bird will try to maintain with its neighbors. \
 <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->If the \
 bird is closer than this value from it’s nearest neighbor, it will steer \
 away from that neighbor <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->This \
 distance is measured from the pivot of one bird to the pivot of the next, \
 so you should allow for the size of the model. . <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->(You \
 will want to set this value after you scale the model used in the flock)."));

    string.LoadString(IDS_JITTER);
    m_jitterinfo = HIntPropertyInfo::New(string, "Jitter");
    m_jitterinfo->SetDefaultValue(5);
    m_jitterinfo->SetMinValue(0);
    m_jitterinfo->SetMaxValue(10000);
    m_jitterinfo->SetDocumentation(DOC("This is a randomizing value used to make the flock more chaotic. <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->The \
 higher this value, the more the members of the flock will adjust their \
 steering. <!--kadov_tag{{<spaces>}}-->&nbsp;&nbsp;<!--kadov_tag{{</spaces>}}-->You \
 might try a higher value for bats."));

    string.LoadString(IDS_MAXSPEED);
    m_maxspeedinfo = HFloatPropertyInfo::New(string, "MaxSpeed");
    m_maxspeedinfo->SetDefaultValue(10.F);
    m_maxspeedinfo->SetMinValue(0.F);
    m_maxspeedinfo->SetMaxValue(10000.0f);
    m_maxspeedinfo->SetDocumentation(DOC("This is the maximum speed of each member of the flock. <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->You \
 will probably want to use a lower value for geese, and a higher value \
 for swallows."));

    string.LoadString(IDS_ACCELERATION);
    m_accelerationinfo = HFloatPropertyInfo::New(string, "Acceleration");
    m_accelerationinfo->SetDefaultValue(5.0f);
    m_accelerationinfo->SetMinValue(0.F);
    m_accelerationinfo->SetMaxValue(10000.0f);
    m_accelerationinfo->SetDocumentation(DOC("This value affects the amount of course correction a bird can make per \
 frame. <!--kadov_tag{{<spaces>}}-->&nbsp;<!--kadov_tag{{</spaces>}}-->Slower \
 birds, like geese, should have a lower value than bats or swallows."));

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
