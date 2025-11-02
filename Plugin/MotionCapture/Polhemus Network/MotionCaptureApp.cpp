// WEP  4/12/2005  \will120\Plugin\MotionCapture\Polhemus Network\MotionCaptureApp.cpp
//

#include "StdAfx.h"
#include "MotionCaptureApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCApp

BEGIN_MESSAGE_MAP(CMCApp, CWinApp)
        //{{AFX_MSG_MAP(CMCApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// The one and only CMCApp object

CMCApp theApp;

BOOL CMCApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;

    string.LoadString(IDS_TIMEOUT);
    m_timeoutinfo = HIntPropertyInfo::New(string, "Timeout");
    m_timeoutinfo->SetDefaultValue(30);

    string.LoadString(IDS_ISBINARY);
    m_isbinaryinfo = HBoolPropertyInfo::New(string, "IsBinary");
    m_isbinaryinfo->SetDefaultValue(TRUE);

    string.LoadString(IDS_IPADDRESS);
    m_ipaddressinfo = HStringPropertyInfo::New(string, "IPADDRESS");
    m_ipaddressinfo->SetDefaultValue("192.168.5.250");

    string.LoadString(IDS_PORT);
    m_portinfo = HIntPropertyInfo::New(string, "Port");
    m_portinfo->SetDefaultValue(5100);

    m_typeinfoarray.SetArraySize(2);
    string.LoadString(IDS_CENTIMETERS);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[0]->SetMatchName("CENTIMETERS");

    string.LoadString(IDS_INCHES);
    m_typeinfoarray[1]->SetMatchName("INCHES");
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_UNITS);
    m_scalefactortypeinfo = HTypePropertyInfo::New(string, "Units", &m_typeinfoarray);
    m_scalefactortypeinfo->SetDefaultIndex(CENTIMETERS);

    return CPluginApp::InitInstance();
}

int CMCApp::ExitInstance() {
    delete m_isbinaryinfo;
    delete m_ipaddressinfo;
    delete m_portinfo;
    delete m_scalefactortypeinfo;
    delete m_timeoutinfo;

    return CPluginApp::ExitInstance();
}
