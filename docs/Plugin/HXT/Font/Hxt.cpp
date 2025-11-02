// Dan  3/24/2003  \DanLP105\Plugin\HXT\Font\Hxt.cpp

#include "StdAfx.h"

#include "Hxt.h"
#include "FontTextDialog.h"
#include "AIDialog.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
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

CHxtApp::CHxtApp(): m_parameters{}, makegroup{0} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHxtApp object

CHxtApp theApp;

//#define _WO_Dialog 

BOOL CHxtApp::OnFontWizard(HModelCache *hmc) {
    m_parameters.m_isfont = true;
#ifdef _WO_Dialog
    const String text = GetRegistryString("Font HXT", "Text", "A");
    const String face = GetRegistryString("Font HXT", "Face", "Arial");
    const String style = GetRegistryString("Font HXT", "Style", "Regular");
    m_parameters.m_buildtext = CString(text.Get());
    m_parameters.m_facename = CString(face.Get());
    m_parameters.m_style = CString(style.Get());
    m_parameters.m_fronts = GetRegistryValue("Font HXT", "Fronts", TRUE);
    m_parameters.m_sides = GetRegistryValue("Font HXT", "Sides", FALSE);
    m_parameters.m_backs = GetRegistryValue("Font HXT", "Backs", FALSE);
    m_parameters.m_bevfronts = GetRegistryValue("Font HXT", "BevFronts", TRUE);
    m_parameters.m_bevsides = GetRegistryValue("Font HXT", "BevSides", FALSE);
    m_parameters.m_bevbacks = GetRegistryValue("Font HXT", "BevBacks", FALSE);
    m_parameters.m_bevround = GetRegistryValue("Font HXT", "BevRound", FALSE);
    m_parameters.m_bevinward = GetRegistryValue("Font HXT", "BevInward", TRUE);
    m_parameters.m_subdivkind = GetRegistryValue("Font HXT", "SubdivKind", FontParameters::SUB_NONE);
    m_parameters.m_bevamt = GetRegistryValue("Font HXT", "BevAmount", 2.F);
    if (!m_parameters.m_fronts)
        m_parameters.m_bevfronts = FALSE;
    if (!m_parameters.m_sides)
        m_parameters.m_bevsides = FALSE;
    if (!m_parameters.m_backs)
        m_parameters.m_bevbacks = FALSE;
    m_parameters.m_depth = GetRegistryValue("Font HXT", "ExtrudeDepthFont", 2.5f);
#else
    CFontTextDialog dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return TRUE;
#endif
    if (nullptr == hmc) {
        hmc = HModelCache::New();
        makegroup = FALSE;
    } else {
        makegroup = TRUE;
    }
    return NewShape(hmc);
}

BOOL CHxtApp::OnAIWizard(HModelCache *hmc) {
    m_parameters.m_isfont = false;
#ifdef _DEBUG1
    m_parameters.m_aifile = "E:\\bugs\\SVGTest\\10_test_ai8.ai";
    m_parameters.m_fronts = GetRegistryValue("Font HXT", "Fronts", TRUE);
    m_parameters.m_sides = GetRegistryValue("Font HXT", "Sides", TRUE);
    m_parameters.m_backs = GetRegistryValue("Font HXT", "Backs", FALSE);
    m_parameters.m_bevfronts = GetRegistryValue("Font HXT", "BevFronts", TRUE);
    m_parameters.m_bevsides = GetRegistryValue("Font HXT", "BevSides", FALSE);
    m_parameters.m_bevbacks = GetRegistryValue("Font HXT", "BevBacks", FALSE);
    m_parameters.m_bevround = GetRegistryValue("Font HXT", "BevRound", FALSE);
    m_parameters.m_bevinward = GetRegistryValue("Font HXT", "BevInward", TRUE);
    m_parameters.m_subdivkind = GetRegistryValue("Font HXT", "SubdivKind", FontParameters::SUB_NONE);
    m_parameters.m_bevamt = GetRegistryValue("Font HXT", "BevAmount", 2.0f);
    if (!m_parameters.m_fronts)
        m_parameters.m_bevfronts = FALSE;
    if (!m_parameters.m_sides)
        m_parameters.m_bevsides = FALSE;
    if (!m_parameters.m_backs)
        m_parameters.m_bevbacks = FALSE;
#else
    CAIDialog dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return TRUE;
#endif
    if (nullptr == hmc) {
        hmc = HModelCache::New();
        makegroup = FALSE;
    } else {
        makegroup = TRUE;
    }
    return NewShape(hmc);
}

BOOL CHxtApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CHxtApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

// FontParameters members
int FontParameters::FaceWeight() const {
    return m_style == "Bold" || m_style == "Bold Italic" ? FW_BOLD : FW_NORMAL;
}

int FontParameters::IsItalicFace() const {
    return m_style == "Italic" || m_style == "Bold Italic";
}
