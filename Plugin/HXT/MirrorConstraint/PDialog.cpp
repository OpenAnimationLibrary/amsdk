// PDialog.cpp : Implementierungsdatei
//
#include "MirrorConstraint.h"
#include "PDialog.h"


//IMPLEMENT_DYNAMIC(PDialog, CDialog)

PDialog::PDialog(MC_PARAMETER *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    mp = para;
}

PDialog::~PDialog() = default;

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    HUserCategoryProperty *hucp = mp->hmc->GetUserCategoryProperty();
    if (hucp) {
        auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
        CString temp;
        int h = 0;
        while (hucp->GetPropertyAt(h)) {
            HProperty *hpo = hucp->GetPropertyAt(h);
            HPropertyShortcut *hpo1 = hpo->FindEmptyRelation();
            if (hpo1) {
                temp.Format("%s", hpo->GetName());
                const int index = id1->AddString(temp);
                id1->SetItemDataPtr(index, hpo1);
            }
            ++h;
        }
    }
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur³ckgeben
}

void PDialog::OnOK() {
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    const int nCount = id1->GetSelCount();
    CArray<int, int> selection;
    selection.SetSize(nCount);
    id1->GetSelItems(nCount, selection.GetData());
    for (int i = 0; i < selection.GetSize(); ++i) {
        auto *hpo1 = (HPropertyShortcut *)id1->GetItemDataPtr(selection[i]);
        mp->poses.Add(hpo1);
    }
    CPluginDialog::OnOK();
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, mp->search);
    DDX_Text(pDX, IDC_EDIT2, mp->replace);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
END_MESSAGE_MAP()

// PDialog-Meldungshandler
