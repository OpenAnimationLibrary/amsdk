// APDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "MMoP.h"
#include "APDialog.h"

IMPLEMENT_DYNAMIC(APDialog, CPluginDialog)

APDialog::APDialog(PParameter *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    mp = para;
}

APDialog::~APDialog() = default;

void APDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK1, mp->action_random);
}

BEGIN_MESSAGE_MAP(APDialog, CPluginDialog)
END_MESSAGE_MAP()

void APDialog::OnOK() {
    UpdateData(true);
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    const int nCount = id1->GetSelCount();
    if (nCount > 0) {
        CArray<int, int> selection;
        selection.SetSize(nCount);
        id1->GetSelItems(nCount, selection.GetData());
        for (int i = 0; i < selection.GetSize() && i < 21; ++i) {
            mp->hac[i] = (HActionCache *)id1->GetItemDataPtr(i);
            mp->azaction = i + 1;
        }
    }
    CPluginDialog::OnOK();
}

BOOL APDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id2 = (CButton *)GetDlgItem(IDC_CHECK1);
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;
    HActionCacheContainer *hacc = mp->hproject->GetChildActionCacheContainer();
    for (HActionCache *hac1 = hacc->GetChildActionCache(); hac1; hac1 = hac1->GetSiblingActionCache()) {
        temp.Format("%s", hac1->GetMatchName().Get());
        const int index = id1->AddString(temp);
        id1->SetItemDataPtr(index, hac1);
    }
    if (id1->GetCount() < 2)
        id2->EnableWindow(false);
    return TRUE; // return TRUE unless you set the focus to a control
}

// APDialog-Meldungshandler
