// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "CloneWeight.h"
#include "PDialog.h"

PDialog::PDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_para = parameters;
    //}}AFX_DATA_INIT
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK1, m_para->reassigncp);
    //{{AFX_DATA_MAP(PDialog)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
END_MESSAGE_MAP()

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;

    HProject *hproject = GetHProject();
    HObjectCacheContainer *hocc = hproject->GetChildObjectCacheContainer();
    for (HHashObject *hmc = hocc->GetChildModelCache(); hmc; hmc = hmc->GetSibling()) {
        if (hmc->GetObjectType() == HOT_MODEL) {
            if (hmc != m_para->hmc) {
                temp.Format("%s", hmc->GetName());
                const int index = id1->AddString(temp);
                id1->SetItemDataPtr(index, hmc);
            }
        }
    }
    id1->SetCurSel(0);
    return TRUE;
}

void PDialog::OnOK() {
    // TODO: Zusõtzliche Pr³fung hier einf³gen
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    UpdateData(true);
    m_para->hmc = (HModelCache *)id1->GetItemDataPtr(id1->GetCurSel());
    CPluginDialog::OnOK();
}
