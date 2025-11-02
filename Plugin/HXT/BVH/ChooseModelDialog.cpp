// ChooseModelDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "F_Protos.h"
#include "ChooseModelDialog.h"

#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseModelDialog dialog

CChooseModelDialog::CChooseModelDialog(HObjectCacheContainer *hocc, const String &actioncachename, HModelCache *hmc, BOOL bMultipleActions): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hocc = hocc;
    m_actioncachename = actioncachename.GetNameOnlyWithoutSuffix();
    m_hmc = hmc;
    m_fErrorTol = GetRegistryValue("BVH Plugin", "Error Tolerance", 0.F);
    m_fFps = GetRegistryValue("BVH Plugin", "FPS", 30.0F);
    m_bMultipleActions = bMultipleActions;
    //{{AFX_DATA_INIT(CChooseModelDialog)
    m_bUseForAllActions = FALSE;
    //}}AFX_DATA_INIT
}

void CChooseModelDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CChooseModelDialog)
    DDX_Check(pDX, IDC_USEFORALLACTIONS, m_bUseForAllActions);
    DDX_Text(pDX, IDC_ERRORTOL_EDIT, m_fErrorTol);
    DDV_MinMaxFloat(pDX, m_fErrorTol, 0.F, 100.F);
    DDX_Text(pDX, IDC_FPS_EDIT, m_fFps);
    DDV_MinMaxFloat(pDX, m_fFps, 1.F, 1000.F);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChooseModelDialog, CDialog)
    //{{AFX_MSG_MAP(CChooseModelDialog)
    ON_LBN_SELCHANGE(IDC_MODELLIST_COMBO, &CChooseModelDialog::OnSelchangeModellistCombo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseModelDialog message handlers

BOOL CChooseModelDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    GetDlgItem(IDOK)->EnableWindow(FALSE);
    if (!m_bMultipleActions)
        GetDlgItem(IDC_USEFORALLACTIONS)->ShowWindow(SW_HIDE);

    auto *listbox = (CListBox *)GetDlgItem(IDC_MODELLIST_COMBO);

    for (HModelCache *hmc = m_hocc->GetChildModelCache(); hmc; hmc = (HModelCache *)hmc->GetSiblingSame()) {
        String name = hmc->GetName();
        name = name.GetNameOnlyWithoutSuffix();
        const int index = listbox->AddString(name.Get());
        listbox->SetItemData(index, (DWORD_PTR)hmc);
    }

    if (m_hmc)
        for (int i = 0; i < listbox->GetCount(); ++i) {
            if (m_hmc == (HModelCache *)listbox->GetItemData(i)) {
                listbox->SetCurSel(i);
                OnSelchangeModellistCombo();
                break;
            }
        }

    CString text;
    text.LoadString(IDS_DIALOGTITLE);
    String temp = text;
    temp.Replace("%1", m_actioncachename);
    text = temp.Get();
    SetWindowText(text);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseModelDialog::OnSelchangeModellistCombo() {
    const CListBox *listbox = (CListBox *)GetDlgItem(IDC_MODELLIST_COMBO);
    GetDlgItem(IDOK)->EnableWindow(listbox->GetCurSel() != -1);
}

void CChooseModelDialog::OnOK() {
    CPluginDialog::OnOK();

    const CListBox *listbox = (CListBox *)GetDlgItem(IDC_MODELLIST_COMBO);
    const int index = listbox->GetCurSel();
    if (index != -1)
        m_hmc = (HModelCache *)listbox->GetItemData(index);

    SetRegistryValue("BVH Plugin", "Error Tolerance", m_fErrorTol);
    SetRegistryValue("BVH Plugin", "FPS", m_fFps);
}
