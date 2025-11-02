// ExportActionsDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"
#include "MapLimit.h"
#include "SDK/Misc.h"
#include "SDK/HAction.h"
#include "SDK/HProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportActionsDialog dialog

CExportActionsDialog::CExportActionsDialog(HActionCacheContainer *hacc) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hacc = hacc;
    m_dir = GetRegistryString("AV2 Plugin", "Output Directory", ".");
    m_generatemodelmaps = GetRegistryString("AV2 Plugin", "Generate Model Maps", "FALSE") == "TRUE";
    m_minsize = GetRegistryValue("AV2 Plugin", "Min Map Size", ML_1);
    m_maxsize = GetRegistryValue("AV2 Plugin", "Max Map Size", ML_256);
    //{{AFX_DATA_INIT(CExportActionsDialog)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void CExportActionsDialog::FillCombo(const int id) const {
    auto *combo = (CComboBox *)GetDlgItem(id);

    int index = combo->AddString("1");
    combo->SetItemData(index, (DWORD_PTR)ML_1);

    index = combo->AddString("2");
    combo->SetItemData(index, (DWORD_PTR)ML_2);

    index = combo->AddString("4");
    combo->SetItemData(index, (DWORD_PTR)ML_4);

    index = combo->AddString("8");
    combo->SetItemData(index, (DWORD_PTR)ML_8);

    index = combo->AddString("16");
    combo->SetItemData(index, (DWORD_PTR)ML_16);

    index = combo->AddString("32");
    combo->SetItemData(index, (DWORD_PTR)ML_32);

    index = combo->AddString("64");
    combo->SetItemData(index, (DWORD_PTR)ML_64);

    index = combo->AddString("128");
    combo->SetItemData(index, (DWORD_PTR)ML_128);

    index = combo->AddString("256");
    combo->SetItemData(index, (DWORD_PTR)ML_256);
    index = combo->AddString("512");
    combo->SetItemData(index, (DWORD_PTR)ML_512);

}

BOOL CExportActionsDialog::OnInitDialog() {
    FillCombo(IDC_MINSIZE_COMBO);
    FillCombo(IDC_MAXSIZE_COMBO);
    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);

    CDialog::OnInitDialog();

    m_selected.RemoveAll();
    for (HActionCache *hac = m_hacc->GetChildActionCache(); hac; hac = hac->GetSiblingActionCache()) {
        String name = hac->GetName();
        const int iIndex = m_checklistbox.AddString(name.GetNameOnlyWithoutSuffix().Get());
        m_checklistbox.SetItemData(iIndex, (DWORD_PTR)hac);
        m_checklistbox.SetCheck(iIndex, TRUE);
    }
    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());
    CString text;
    text.LoadString(IDS_ACTIONSTOEXPORT);
    GetDlgItem(IDC_LISTLABEL)->SetWindowText(text);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportActionsDialog::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportActionsDialog)
    DDX_Check(pDX, IDC_GENERATEMODELMAPS, m_generatemodelmaps);
    DDX_CBIndex(pDX, IDC_MINSIZE_COMBO, m_minsize);
    DDX_CBIndex(pDX, IDC_MAXSIZE_COMBO, m_maxsize);
    DDX_Control(pDX, IDC_MODELLIST_COMBO, m_checklistbox);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportActionsDialog, CDialog)
    //{{AFX_MSG_MAP(CExportActionsDialog)
    ON_CBN_SELCHANGE(IDC_MAXSIZE_COMBO, &CExportActionsDialog::OnMaxSize)
    ON_CBN_SELCHANGE(IDC_MINSIZE_COMBO, &CExportActionsDialog::OnMinSize)
    ON_BN_CLICKED(IDC_GENERATEMODELMAPS, &CExportActionsDialog::OnGeneratemodelmaps)
    ON_BN_CLICKED(IDC_BROWSE, &CExportActionsDialog::OnBrowse)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportActionsDialog message handlers

void CExportActionsDialog::OnOK() {
    CDialog::OnOK();
    for (int iIndex = 0; iIndex < m_checklistbox.GetCount(); iIndex++) {
        if (m_checklistbox.GetCheck(iIndex)) {
            auto *hac = (HActionCache *)m_checklistbox.GetItemData(iIndex);
            m_selected.AddTail(hac);
        }
    }
    SetRegistryString("AV2 Plugin", "Output Directory", m_dir);
    SetRegistryString("AV2 Plugin", "Generate Model Maps", m_generatemodelmaps ? "TRUE" : "FALSE");
    SetRegistryValue("AV2 Plugin", "Min Map Size", m_minsize);
    SetRegistryValue("AV2 Plugin", "Max Map Size", m_maxsize);
}

void CExportActionsDialog::OnMaxSize() {
    const CComboBox *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    auto *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = maxcombo->GetCurSel();
    const int maxlimit = maxcombo->GetItemData(index);

    index = mincombo->GetCurSel();
    const int minlimit = mincombo->GetItemData(index);

    if (maxlimit < minlimit)
        maxcombo->SetCurSel(index);
}

void CExportActionsDialog::OnMinSize() {
    auto *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    const CComboBox *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = mincombo->GetCurSel();
    const int minlimit = mincombo->GetItemData(index);

    index = maxcombo->GetCurSel();
    const int maxlimit = maxcombo->GetItemData(index);

    if (minlimit > maxlimit)
        mincombo->SetCurSel(index);
}

void CExportActionsDialog::OnGeneratemodelmaps() {
    m_generatemodelmaps = IsDlgButtonChecked(IDC_GENERATEMODELMAPS);
    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
}

void CExportActionsDialog::OnBrowse() {
    CString caption;
    caption.LoadString(IDS_CHOOSEDIRECTORY);
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!DirRequest(m_dir, caption/*nullptr*/, m_dir.Get(), this))
            return;
    }
    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());
}
