// SPDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "MMoP.h"
#include "SPDialog.h"

IMPLEMENT_DYNAMIC(SPDialog, CPluginDialog)
SPDialog::SPDialog(PParameter *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    mp = para;
}

SPDialog::~SPDialog() = default;

void SPDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(SPDialog, CPluginDialog)
END_MESSAGE_MAP()

void SPDialog::UpdatePoses() const {
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    //    CButton *id2 = (CButton *)GetDlgItem(IDC_CHECK1);
    id1->ResetContent();
    HUserCategoryProperty *hucp = mp->hmc->GetUserCategoryProperty();
    if (hucp) {
        HProperty *prop;
        CString temp;
        for (int i = 0; (prop = hucp->GetPropertyAt(i)) != nullptr; ++i) {
            if (prop->GetObjectType() == HOT_PERCENT) {
                HPropertyInfo *hpi = prop->GetPropertyInfo();
                temp.Format("%s", hpi->GetMatchName().Get());
                const int index = id1->AddString(temp);
                id1->SetItemDataPtr(index, prop);
            }
        }
    }
}

void SPDialog::OnOK() {
    const CButton *id2 = (CButton *)GetDlgItem(IDC_CHECK1);
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    if (id2->GetCheck()) {
        const int nCount = id1->GetSelCount();
        CArray<int, int> selection;
        selection.SetSize(nCount);
        id1->GetSelItems(nCount, selection.GetData());
        for (int i = 0; i < selection.GetSize() && i < 21; ++i) {
            mp->props[i] = (HProperty *)id1->GetItemDataPtr(i);
            mp->azprop = i + 1;
        }
    }
    CPluginDialog::OnOK();
}

BOOL SPDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    UpdatePoses();
    return TRUE; // return TRUE unless you set the focus to a control
}
