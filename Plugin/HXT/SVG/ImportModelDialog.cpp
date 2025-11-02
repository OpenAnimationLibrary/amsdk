// \Plugin\HXT\SVG\ImportModelDialog.cpp
// ImportModelDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "StrClass.h"
#include "Hxt.h"
#include "ImportModelDialog.h"
#include "F_Protos.h"
#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog dialog

CImportModelDialog::CImportModelDialog(SVGParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(CImportModelDialog)
    m_parameters = parameters;
    //}}AFX_DATA_INIT
}

void CImportModelDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CImportModelDialog)
    DDX_Text(pDX, IDC_EDIT1, m_parameters->resolution);
    DDV_MinMaxInt(pDX, m_parameters->resolution, 1, 6000);
    DDX_Check(pDX, IDC_CHECK1, m_parameters->center);
    DDX_Check(pDX, IDC_CHECK2, m_parameters->importaspathonly);
    DDX_CBIndex(pDX, IDC_COMBO1, m_parameters->unit);
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
    DDV_MinMaxFloat(pDX, m_parameters->m_bevamt, 0.F, 1000.0F);
    int subdivradio = m_parameters->m_subdivkind;
    DDX_Radio(pDX, IDC_SUB_NONE, subdivradio);
    m_parameters->m_subdivkind = subdivradio;
    DDX_Text(pDX, IDC_EDIT2, m_parameters->m_depth);
    DDV_MinMaxFloat(pDX, m_parameters->m_depth, 0.01F, 10000.0F);

    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImportModelDialog, CDialog)
        //{{AFX_MSG_MAP(CImportModelDialog)
        //}}AFX_MSG_MAP
        ON_CBN_SELCHANGE(IDC_COMBO1, &CImportModelDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog message handlers

void CImportModelDialog::OnOK() {
    CPluginDialog::OnOK();
    //	SetRegistryValue((String)"SVG Plugin", (String)"Peak Tolerance", m_peaktolerance);
}

BOOL CImportModelDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    if (m_parameters->unit == 0) {
        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
    } else {
        GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
    }
    return TRUE;
}

void CImportModelDialog::OnCbnSelchangeCombo1() {
    // TODO: Add your control notification handler code here
    UpdateData(true);
    if (m_parameters->unit == 0) {
        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
    } else {
        GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
    }
}
