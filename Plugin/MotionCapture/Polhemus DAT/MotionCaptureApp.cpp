// Dan  3/24/2003  \DanLP105\Plugin\MotionCapture\Polhemus DAT\MotionCaptureApp.cpp
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
// CMCApp construction

CMCApp::CMCApp(): m_scalefactortypeinfo(nullptr), m_filenameinfo(nullptr) {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMCApp object

CMCApp theApp;

BOOL CMCApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;

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

    string.LoadString(IDS_ISBINARY);
    //m_isbinaryinfo = HBoolPropertyInfo::New( string, "IsBinary" );
    //m_isbinaryinfo->SetDefaultValue( FALSE );

    string.LoadString(IDS_DATFILENAME);
    m_filenameinfo = HFilenamePropertyInfo::New(string, "DatFilename");
    m_filenameinfo->SetFileDialogTitle("Open Polhemus DAT File");
    m_filenameinfo->SetFileDialogFilter("Polhemus DAT Files (*.dat)|*.dat|TEXT|All Files (*.*)|*.*|****||");
    m_filenameinfo->SetDefaultExtension("dat");

    return CPluginApp::InitInstance();
}

int CMCApp::ExitInstance() {
    delete m_scalefactortypeinfo;
    //delete m_isbinaryinfo;
    delete m_filenameinfo;

    return CPluginApp::ExitInstance();
}
