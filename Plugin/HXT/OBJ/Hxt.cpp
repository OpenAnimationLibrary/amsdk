#include "StdAfx.h"
#include "Hxt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHxtApp

BEGIN_MESSAGE_MAP(CHxtApp, CWinApp)
    //{{AFX_MSG_MAP(CHxtApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHxtApp construction

CHxtApp::CHxtApp(): m_bexporttriangles{0}, m_normalsneedrebuild{0}, m_discarddegenerated{0}, m_exportnormals{0}, needsmapdlg{0}, m_buvcount{false} {
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_isbuildattrarray = TRUE;
    m_iemp.m_isbuildbonelist = TRUE;
    m_materialfile_found = true;
    m_hprogressbar = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHxtApp object

CHxtApp theApp;

BOOL CHxtApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CWinApp::InitInstance();
}

int CHxtApp::ExitInstance() {
    return CWinApp::ExitInstance();
}
