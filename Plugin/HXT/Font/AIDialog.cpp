// KB  11/5/01  \Ken90\Plugin\HXT\Font\AIDialog.cpp

#include "StdAfx.h"
#include "StrClass.h"
#include "Hxt.h"
#include "F_Protos.h"
#include "AIDialog.h"
#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIDialog dialog

CAIDialog::CAIDialog(FontParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(CAIDialog)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_parameters = parameters;

    const String aifolder = GetRegistryString("Font HXT", "AIFolder", "");
    m_parameters->m_aifolder = CString(aifolder.Get());
    m_parameters->m_fronts = GetRegistryValue("Font HXT", "Fronts", TRUE);
    m_parameters->m_sides = GetRegistryValue("Font HXT", "Sides", TRUE);
    m_parameters->m_backs = GetRegistryValue("Font HXT", "Backs", FALSE);
    m_parameters->m_bevfronts = GetRegistryValue("Font HXT", "BevFronts", TRUE);
    m_parameters->m_bevsides = GetRegistryValue("Font HXT", "BevSides", FALSE);
    m_parameters->m_bevbacks = GetRegistryValue("Font HXT", "BevBacks", FALSE);
    m_parameters->m_bevround = GetRegistryValue("Font HXT", "BevRound", FALSE);
    m_parameters->m_bevinward = GetRegistryValue("Font HXT", "BevInward", TRUE);
    m_parameters->m_subdivkind = GetRegistryValue("Font HXT", "SubdivKind", FontParameters::SUB_NONE);
    m_parameters->m_bevamt = GetRegistryValue("Font HXT", "BevAmount", 2.0F);
    if (!m_parameters->m_fronts)
        m_parameters->m_bevfronts = FALSE;
    if (!m_parameters->m_sides)
        m_parameters->m_bevsides = FALSE;
    if (!m_parameters->m_backs)
        m_parameters->m_bevbacks = FALSE;
    m_parameters->m_depth = GetRegistryValue("Font HXT", "ExtrudeDepth", 2.5F);
}

void CAIDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_AI_FILE, m_parameters->m_aifile);
    DDX_Check(pDX, IDC_FRONTS, m_parameters->m_fronts);
    DDX_Check(pDX, IDC_SIDES, m_parameters->m_sides);
    DDX_Check(pDX, IDC_BACKS, m_parameters->m_backs);
    DDX_Check(pDX, IDC_BEVEL_FRONTS, m_parameters->m_bevfronts);
    DDX_Check(pDX, IDC_BEVEL_SIDES, m_parameters->m_bevsides);
    DDX_Check(pDX, IDC_BEVEL_BACKS, m_parameters->m_bevbacks);
    int roundradio = m_parameters->m_bevround ? 0 : 1;
    DDX_Radio(pDX, IDC_BEVEL_ROUND, roundradio);
    m_parameters->m_bevround = roundradio == 0;
    DDX_Check(pDX, IDC_BACKS, m_parameters->m_backs);
    int inwardradio = m_parameters->m_bevinward ? 0 : 1;
    DDX_Radio(pDX, IDC_BEVEL_INWARD, inwardradio);
    m_parameters->m_bevinward = inwardradio == 0;
    DDX_Text(pDX, IDC_BEVAMOUNT, m_parameters->m_bevamt);
    DDV_MinMaxFloat(pDX, m_parameters->m_bevamt, 0.0F, 1000.0F);
    int subdivradio = m_parameters->m_subdivkind;
    DDX_Radio(pDX, IDC_SUB_NONE, subdivradio);
    m_parameters->m_subdivkind = subdivradio;
    DDX_Text(pDX, IDC_EDIT1, m_parameters->m_depth);
    DDV_MinMaxFloat(pDX, m_parameters->m_depth, 0.01F, 10000.0F);

    //{{AFX_DATA_MAP(CAIDialog)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAIDialog, CDialog)
    //{{AFX_MSG_MAP(CAIDialog)
    ON_BN_CLICKED(IDC_BROWSE_AI, &CAIDialog::OnBrowseAi)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIDialog message handlers

void CAIDialog::OnBrowseAi() {
    static char BASED_CODE szFilter[] = "Adobe Illustrator files (*.ai)|*.ai|All files (*.*)|*.*||";

    CFileDialog dlg(TRUE, _T("ai"), _T("*.ai"), 0, szFilter, FromHandle(GetMainApplicationWnd()));

    if (!m_parameters->m_aifolder.IsEmpty()) {
        dlg.m_ofn.lpstrInitialDir = m_parameters->m_aifolder;
    }

    if (dlg.DoModal() == IDOK) {
        CString filename = dlg.GetPathName();
        auto *ce = (CEdit *)GetDlgItem(IDC_AI_FILE);
        ce->SetWindowText(filename);
        m_parameters->m_aifile = filename;

        String filestring = filename;
        m_parameters->m_aifolder = filestring.GetPathOnly().Get();
    }
}

void CAIDialog::OnOK() {
    CPluginDialog::OnOK();
    const String aifolder((LPCTSTR)m_parameters->m_aifolder);
    SetRegistryString("Font HXT", "AIFolder", aifolder);
    SetRegistryValue("Font HXT", "Fronts", m_parameters->m_fronts);
    SetRegistryValue("Font HXT", "Sides", m_parameters->m_sides);
    SetRegistryValue("Font HXT", "Backs", m_parameters->m_backs);
    SetRegistryValue("Font HXT", "BevFronts", m_parameters->m_bevfronts);
    SetRegistryValue("Font HXT", "BevSides", m_parameters->m_bevsides);
    SetRegistryValue("Font HXT", "BevBacks", m_parameters->m_bevbacks);
    SetRegistryValue("Font HXT", "BevRound", m_parameters->m_bevround);
    SetRegistryValue("Font HXT", "BevInward", m_parameters->m_bevinward);
    SetRegistryValue("Font HXT", "BevAmount", m_parameters->m_bevamt);
    SetRegistryValue("Font HXT", "SubdivKind", m_parameters->m_subdivkind);
    SetRegistryValue("Font HXT", "ExtrudeDepth", m_parameters->m_depth);
}
