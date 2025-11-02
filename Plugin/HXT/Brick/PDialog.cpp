// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Brick.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(PParameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_para = parameters;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, m_para->row);
    DDV_MinMaxInt(pDX, m_para->row, 1, 10000);
    DDX_Text(pDX, IDC_EDIT2, m_para->column);
    DDV_MinMaxInt(pDX, m_para->column, 1, 10000);
    DDX_Text(pDX, IDC_EDIT3, m_para->space_x);
    DDV_MinMaxFloat(pDX, m_para->space_x, 0, 10000);
    DDX_Text(pDX, IDC_EDIT4, m_para->space_y);
    DDV_MinMaxFloat(pDX, m_para->space_y, 0, 10000);
    DDX_Check(pDX, IDC_CHECK1, m_para->scale);
    DDX_Check(pDX, IDC_CHECK2, m_para->add_bullet);
    DDX_Check(pDX, IDC_CHECK3, m_para->b_calcweight);
    DDX_Check(pDX, IDC_CHECK4, m_para->userfolder);
    DDX_Text(pDX, IDC_EDIT5, m_para->b_bounce);
    DDV_MinMaxFloat(pDX, m_para->b_bounce, 0, 2);
    DDX_Text(pDX, IDC_EDIT6, m_para->b_friction);
    DDV_MinMaxFloat(pDX, m_para->b_friction, 0, 2);
    DDX_Text(pDX, IDC_EDIT7, m_para->b_density);
    DDV_MinMaxFloat(pDX, m_para->b_density, 0.001F, 50.F);
    DDX_Text(pDX, IDC_EDIT8, m_para->b_weight);
    DDV_MinMaxFloat(pDX, m_para->b_weight, 0, 1000);
    DDX_Text(pDX, IDC_EDIT9, m_para->position_z);
    DDV_MinMaxFloat(pDX, m_para->position_z, -100000, 100000);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_LBN_SELCHANGE(IDC_LIST1, &PDialog::OnSelchangeList1)
        ON_BN_CLICKED(IDC_CHECK2, &PDialog::OnCheck2)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::OnSelchangeList1() {
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;
    temp.Format("Import \'%s\'", ((HModelCache *)id1->GetItemDataPtr(id1->GetCurSel()))->GetName());
    SetDlgItemText(IDC_STATIC1, temp);
}

void PDialog::OnCheck2() {
    UpdateData(true);
    auto *id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    if (m_para->add_bullet) {
        id2->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
    } else {
        id2->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
    }
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;

    HObjectCacheContainer *hocc = m_para->hproject->GetChildObjectCacheContainer();
    for (HHashObject *hmc = hocc->GetChildModelCache(); hmc; hmc = hmc->GetSibling()) {
        if (hmc->GetObjectType() == HOT_MODEL) {
            temp.Format("%s", hmc->GetName());
            const int index = id1->AddString(temp);
            id1->SetItemDataPtr(index, hmc);
        }
    }
    id1->SetCurSel(0);
    temp.Format("Import \'%s\'", ((HModelCache *)id1->GetItemDataPtr(id1->GetCurSel()))->GetName());
    SetDlgItemText(IDC_STATIC1, temp);

    auto *id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    id2->SetCurSel(m_para->b_shape);

    if (!m_para->add_bullet) {
        id2->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
    }

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {
    UpdateData(true);
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    m_para->hmc = (HModelCache *)id1->GetItemDataPtr(id1->GetCurSel());
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    m_para->b_shape = id2->GetCurSel();

    CPluginDialog::OnOK();
}
