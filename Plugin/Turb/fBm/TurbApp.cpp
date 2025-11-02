// KB  9/26/01  \Ken90\Plugin\Turb\fBm\TurbApp.cpp
//

#include "StdAfx.h"
#include "TurbApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurbApp

BEGIN_MESSAGE_MAP(CTurbApp, CWinApp)
    //{{AFX_MSG_MAP(CTurbApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurbApp construction

float CTurbApp::m_exponent[8] = {1.F, .707107F, .5F, .353553F, .25F, .176777F, .125F, .0883883F};

BOOL CTurbApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    string.LoadString(IDS_OCTAVES);
    m_octavesinfo = HIntPropertyInfo::New(string, "Octaves");
    m_octavesinfo->SetDefaultValue(1);
    m_octavesinfo->SetMinValue(0);
    m_octavesinfo->SetMaxValue(5);
    // Ensure the material preview window will update when this value is changed
    m_octavesinfo->SetDrawWhen(HIntPropertyInfo::DRAWIFMATERIALS);

    m_fractalincrement = .5F;
    InitfBm(m_fractalincrement);

    return CPluginApp::InitInstance();
}

int CTurbApp::ExitInstance() {
    // Delete Infos Here
    delete m_octavesinfo;

    return CPluginApp::ExitInstance();
}

void CTurbApp::InitfBm(const float h) {
    float frequency = 1.F;
    for (float &i: m_exponent) {
        i = hash_math::pow(frequency, -h);
        frequency *= 2.F;
    }
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTurbApp object

CTurbApp theApp;
