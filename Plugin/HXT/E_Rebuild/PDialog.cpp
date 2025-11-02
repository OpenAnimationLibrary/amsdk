// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "E_Rebuild.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
PDialog::PDialog(PParameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), m_para(parameters), m_groups(m_para->hasExplodegroups), m_strict(m_para->groupstrict), m_forceextrude(m_para->check_minextrude), m_maxpatch(m_para->maxPatches), m_scale(m_para->scale), m_extrude(m_para->minextrude), m_reverse(m_para->reverseextrude), m_randomextrude(m_para->randomscale), m_near(m_para->near_average), m_minscale(m_para->minscale), m_maxscale(m_para->maxscale) {
    //{{AFX_DATA_INIT(PDialog)
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Check(pDX, IDC_CHECK1, m_groups);
    DDX_Check(pDX, IDC_CHECK2, m_strict);
    DDX_Check(pDX, IDC_CHECK3, m_forceextrude);
    DDX_Text(pDX, IDC_EDIT1, m_maxpatch);
    DDV_MinMaxInt(pDX, m_maxpatch, 1, 10);
    DDX_Text(pDX, IDC_EDIT3, m_scale);
    DDV_MinMaxFloat(pDX, m_scale, 1.e-007F, 1.F);
    DDX_Text(pDX, IDC_EDIT2, m_extrude);
    DDV_MinMaxFloat(pDX, m_extrude, 1.e-007F, 100000.F);
    DDX_Check(pDX, IDC_CHECK4, m_reverse);
    DDX_Check(pDX, IDC_CHECK5, m_randomextrude);
    DDX_Text(pDX, IDC_EDIT4, m_near);
    DDV_MinMaxFloat(pDX, m_near, 0.F, 1.F);
    DDX_Text(pDX, IDC_EDIT5, m_minscale);
    DDV_MinMaxFloat(pDX, m_minscale, 1.e-007F, 1.F);
    DDX_Text(pDX, IDC_EDIT6, m_maxscale);
    DDV_MinMaxFloat(pDX, m_maxscale, 1.e-007F, 1.F);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_BN_CLICKED(IDC_CHECK1, &PDialog::OnCheck1)
        ON_BN_CLICKED(IDC_CHECK3, &PDialog::OnCheck3)
        ON_BN_CLICKED(IDC_CHECK5, &PDialog::OnCheck5)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 
void PDialog::Update() {
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK2);
    auto *id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
    if (m_groups) {
        id1->EnableWindow(false);
        id2->EnableWindow(false);
    } else {
        id1->EnableWindow(true);
        id2->EnableWindow(true);
    }
    if (m_forceextrude) {
        m_randomextrude = FALSE;
        id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id2->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_CHECK5);
        id1->SetCheck(false);
        id1->EnableWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
        id2->EnableWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
        id2->EnableWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
        id2->EnableWindow(false);
    } else {
        id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id2->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_CHECK5);
        id1->EnableWindow(true);
        if (m_randomextrude) {
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(false);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(true);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(true);
        } else {
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(true);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(false);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(false);
        }
    }
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    if (m_para->hasExplodegroups) {
        id1->EnableWindow(true);
    } else {
        id1->EnableWindow(false);
    }
    UpdateData(false);
    Update();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnCheck1() {
    UpdateData(true);
    Update();
}

void PDialog::OnOK() {

    UpdateData(true);
    m_para->hasExplodegroups = m_groups;
    m_para->groupstrict = m_strict;
    m_para->check_minextrude = m_forceextrude;
    m_para->maxPatches = m_maxpatch;
    m_para->scale = m_scale;
    m_para->minextrude = m_extrude;
    m_para->reverseextrude = m_reverse;
    m_para->randomscale = m_randomextrude;
    m_para->near_average = m_near;
    if (m_minscale >= m_maxscale) {
        m_para->maxscale = 0.9F;
        m_para->minscale = 0.1F;
    } else {
        m_para->maxscale = m_maxscale;
        m_para->minscale = m_minscale;
    }
    CPluginDialog::OnOK();
}

void PDialog::OnCheck3() {
    UpdateData(true);
    Update();
}

void PDialog::OnCheck5() {
    UpdateData(true);
    Update();
}
