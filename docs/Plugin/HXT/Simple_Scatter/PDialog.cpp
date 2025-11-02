// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Simple_Scatter.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
PDialog::PDialog(PARAMETER *parameter) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), m_para(parameter) {
    //{{AFX_DATA_INIT(PDialog)
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, m_para->azimport);
    DDV_MinMaxInt(pDX, m_para->azimport, 1, 1000);
    DDX_Check(pDX, IDC_CHECK1, m_para->xrotate);
    DDX_Text(pDX, IDC_EDIT2, m_para->rotate_min.x);
    DDV_MinMaxFloat(pDX, m_para->rotate_min.x, -180.F, 180.F);
    DDX_Text(pDX, IDC_EDIT3, m_para->rotate_max.x);
    DDV_MinMaxFloat(pDX, m_para->rotate_max.x, -180.F, 180.F);
    DDX_Check(pDX, IDC_CHECK2, m_para->yrotate);
    DDX_Text(pDX, IDC_EDIT4, m_para->rotate_min.y);
    DDV_MinMaxFloat(pDX, m_para->rotate_min.y, -180.F, 180.F);
    DDX_Text(pDX, IDC_EDIT5, m_para->rotate_max.y);
    DDV_MinMaxFloat(pDX, m_para->rotate_max.y, -180.F, 180.F);
    DDX_Check(pDX, IDC_CHECK3, m_para->zrotate);
    DDX_Text(pDX, IDC_EDIT6, m_para->rotate_min.z);
    DDV_MinMaxFloat(pDX, m_para->rotate_min.z, -180.F, 180.F);
    DDX_Text(pDX, IDC_EDIT7, m_para->rotate_max.z);
    DDV_MinMaxFloat(pDX, m_para->rotate_max.z, -180.F, 180.F);
    DDX_Check(pDX, IDC_CHECK4, m_para->xscale);
    DDX_Text(pDX, IDC_EDIT8, m_para->scale_min.x);
    DDV_MinMaxFloat(pDX, m_para->scale_min.x, 0.1F, 1000.F);
    DDX_Text(pDX, IDC_EDIT9, m_para->scale_max.x);
    DDV_MinMaxFloat(pDX, m_para->scale_max.x, 0.1F, 1000.F);
    DDX_Check(pDX, IDC_CHECK5, m_para->yscale);
    DDX_Text(pDX, IDC_EDIT10, m_para->scale_min.y);
    DDV_MinMaxFloat(pDX, m_para->scale_min.y, 0.1F, 1000.F);
    DDX_Text(pDX, IDC_EDIT11, m_para->scale_max.y);
    DDV_MinMaxFloat(pDX, m_para->scale_max.y, 0.1F, 1000.F);
    DDX_Check(pDX, IDC_CHECK6, m_para->zscale);
    DDX_Text(pDX, IDC_EDIT12, m_para->scale_min.z);
    DDV_MinMaxFloat(pDX, m_para->scale_min.z, 0.1F, 1000.F);
    DDX_Text(pDX, IDC_EDIT13, m_para->scale_max.z);
    DDV_MinMaxFloat(pDX, m_para->scale_max.z, 0.1F, 1000.F);
    DDX_Check(pDX, IDC_CHECK7, m_para->uniformscale);
    DDX_Text(pDX, IDC_EDIT14, m_para->uscale_min);
    DDV_MinMaxFloat(pDX, m_para->uscale_min, 0.1F, 1000.F);
    DDX_Text(pDX, IDC_EDIT15, m_para->uscale_max);
    DDV_MinMaxFloat(pDX, m_para->uscale_max, 0.1F, 1000.F);
    DDX_Check(pDX, IDC_CHECK8, m_para->add_bullet);
    DDX_Check(pDX, IDC_CHECK9, m_para->b_calcweight);
    DDX_Check(pDX, IDC_CHECK10, m_para->align);
    DDX_Text(pDX, IDC_EDIT16, m_para->b_bounce);
    DDV_MinMaxFloat(pDX, m_para->b_bounce, 0, 2);
    DDX_Text(pDX, IDC_EDIT17, m_para->b_friction);
    DDV_MinMaxFloat(pDX, m_para->b_friction, 0, 2);
    DDX_Text(pDX, IDC_EDIT18, m_para->b_density);
    DDV_MinMaxFloat(pDX, m_para->b_density, 0.001F, 50);
    DDX_Text(pDX, IDC_EDIT19, m_para->b_weight);
    DDV_MinMaxFloat(pDX, m_para->b_weight, 0, 1000);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
    //{{AFX_MSG_MAP(PDialog)
    ON_BN_CLICKED(IDC_CHECK1, &PDialog::OnCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &PDialog::OnCheck2)
    ON_BN_CLICKED(IDC_CHECK3, &PDialog::OnCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &PDialog::OnCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &PDialog::OnCheck5)
    ON_BN_CLICKED(IDC_CHECK6, &PDialog::OnCheck6)
    ON_BN_CLICKED(IDC_CHECK7, &PDialog::OnCheck7)
    ON_BN_CLICKED(IDC_CHECK8, &PDialog::OnCheck8)
    ON_BN_CLICKED(IDC_CHECK10, &PDialog::OnCheck10)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 
void PDialog::UpdateDialog() const {
    CEdit *id1;
    if (m_para->xrotate && !m_para->align) {
        id1 = (CEdit*)GetDlgItem(IDC_EDIT2);
        id1->EnableWindow(true);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT3);
        id1->EnableWindow(true);
    } else {
        id1 = (CEdit*)GetDlgItem(IDC_EDIT2);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT3);
        id1->EnableWindow(false);
    }
    if (m_para->yrotate) {
        id1 = (CEdit*)GetDlgItem(IDC_EDIT4);
        id1->EnableWindow(true);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT5);
        id1->EnableWindow(true);
    } else {
        id1 = (CEdit*)GetDlgItem(IDC_EDIT4);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT5);
        id1->EnableWindow(false);
    }
    if (m_para->zrotate && !m_para->align) {
        id1 = (CEdit*)GetDlgItem(IDC_EDIT6);
        id1->EnableWindow(true);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT7);
        id1->EnableWindow(true);
    } else {
        id1 = (CEdit*)GetDlgItem(IDC_EDIT6);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT7);
        id1->EnableWindow(false);
    }
    if (m_para->align) {
        auto *id2 = (CButton*)GetDlgItem(IDC_CHECK1);
        id2->SetCheck(FALSE);
        auto *id3 = (CButton*)GetDlgItem(IDC_CHECK3);
        id3->SetCheck(FALSE);
    }
    if (m_para->uniformscale) {
        auto *id2 = (CButton*)GetDlgItem(IDC_CHECK4);
        id2->SetCheck(FALSE);
        id2 = (CButton*)GetDlgItem(IDC_CHECK5);
        id2->SetCheck(FALSE);
        id2 = (CButton*)GetDlgItem(IDC_CHECK6);
        id2->SetCheck(FALSE);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT8);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT9);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT10);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT11);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT12);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT13);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT14);
        id1->EnableWindow(true);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT15);
        id1->EnableWindow(true);
    } else {
        auto *id2 = (CButton*)GetDlgItem(IDC_CHECK7);
        id2->SetCheck(FALSE);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT14);
        id1->EnableWindow(false);
        id1 = (CEdit*)GetDlgItem(IDC_EDIT15);
        id1->EnableWindow(false);
        if (m_para->xscale) {
            id1 = (CEdit*)GetDlgItem(IDC_EDIT8);
            id1->EnableWindow(true);
            id1 = (CEdit*)GetDlgItem(IDC_EDIT9);
            id1->EnableWindow(true);
        } else {
            id1 = (CEdit*)GetDlgItem(IDC_EDIT8);
            id1->EnableWindow(false);
            id1 = (CEdit*)GetDlgItem(IDC_EDIT9);
            id1->EnableWindow(false);
        }
        if (m_para->yscale) {
            id1 = (CEdit*)GetDlgItem(IDC_EDIT10);
            id1->EnableWindow(true);
            id1 = (CEdit*)GetDlgItem(IDC_EDIT11);
            id1->EnableWindow(true);
        } else {
            id1 = (CEdit*)GetDlgItem(IDC_EDIT10);
            id1->EnableWindow(false);
            id1 = (CEdit*)GetDlgItem(IDC_EDIT11);
            id1->EnableWindow(false);
        }
        if (m_para->zscale) {
            id1 = (CEdit*)GetDlgItem(IDC_EDIT12);
            id1->EnableWindow(true);
            id1 = (CEdit*)GetDlgItem(IDC_EDIT13);
            id1->EnableWindow(true);
        } else {
            id1 = (CEdit*)GetDlgItem(IDC_EDIT12);
            id1->EnableWindow(false);
            id1 = (CEdit*)GetDlgItem(IDC_EDIT13);
            id1->EnableWindow(false);
        }
    }
    auto *id2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
    if (m_para->add_bullet) {
        id2->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT16)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT17)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT18)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT19)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK9)->EnableWindow(TRUE);
    } else {
        id2->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT16)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT17)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT18)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT19)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK9)->EnableWindow(FALSE);
    }
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    HObjectCacheContainer *hocc = GetHProject()->GetChildObjectCacheContainer();
    auto *id1 = (CComboBox*)GetDlgItem(IDC_COMBO1);
    CString modelname = m_para->hm_target->GetName();
    SetDlgItemText(IDC_STATIC_1, modelname);

    for (HModelCache *hmc = hocc->GetChildModelCache(); hmc; hmc = (HModelCache*)hmc->GetSibling()) {
        if (hmc != m_para->hmc_target) {
            modelname = hmc->GetName();
            const int index = id1->AddString(modelname);
            id1->SetItemDataPtr(index, hmc);
        }
    }
    id1->SetCurSel(0);
    m_para->hmc_source = (HModelCache*)id1->GetItemDataPtr(id1->GetCurSel());
    id1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
    id1->SetCurSel(m_para->b_shape);
    UpdateData(false);
    UpdateDialog();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {
    UpdateData(true);
    const CComboBox *id1 = (CComboBox*)GetDlgItem(IDC_COMBO1);
    m_para->hmc_source = (HModelCache*)id1->GetItemDataPtr(id1->GetCurSel());
    const CComboBox *id2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
    m_para->b_shape = id2->GetCurSel();
    CPluginDialog::OnOK();
}

void PDialog::OnCheck1() {
    UpdateData(true);
    UpdateDialog();
}

void PDialog::OnCheck2() {
    UpdateData(true);
    UpdateDialog();
}

void PDialog::OnCheck3() {
    UpdateData(true);
    UpdateDialog();
}

void PDialog::OnCheck4() {
    UpdateData(true);
    m_para->uniformscale = FALSE;
    UpdateDialog();
}

void PDialog::OnCheck5() {
    UpdateData(true);
    m_para->uniformscale = FALSE;
    UpdateDialog();
}

void PDialog::OnCheck6() {
    UpdateData(true);
    m_para->uniformscale = FALSE;
    UpdateDialog();
}

void PDialog::OnCheck7() {
    UpdateData(true);
    UpdateDialog();
}

void PDialog::OnCheck8() {
    UpdateData(true);
    UpdateDialog();
}

void PDialog::OnCheck10() {
    UpdateData(true);
    UpdateDialog();
}
