// ExportModelsDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ExportModelsDialog.h"
#include "F_Protos.h"
#include "MapLimit.h"
#include <direct.h>
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportModelsDialog dialog

CExportModelsDialog::CExportModelsDialog(HObjectCacheContainer *hocc) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hocc = hocc;
    m_dir = GetRegistryString("3DS Plugin", "Output Directory", ".");
    m_generatemodelmaps = GetRegistryString("3DS Plugin", "Generate Model Maps", "FALSE") == "TRUE";
    m_minsize = GetRegistryValue("3DS Plugin", "Min Map Size", ML_1);
    m_maxsize = GetRegistryValue("3DS Plugin", "Max Map Size", ML_256);
    m_subtype = GetRegistryValue("3DS Plugin", "Sub Type", ST_VARIABLE);
    m_applybump = GetRegistryString("3DS Plugin", "Apply Displace", "FALSE") == "TRUE";
    //{{AFX_DATA_INIT(CExportModelsDialog)
    //}}AFX_DATA_INIT
}

void CExportModelsDialog::FillCombo(const int id) const {
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

    index = combo->AddString("1024");
    combo->SetItemData(index, (DWORD_PTR)ML_1024);
    index = combo->AddString("2048");
    combo->SetItemData(index, (DWORD_PTR)ML_2048);
    index = combo->AddString("4096");
    combo->SetItemData(index, (DWORD_PTR)ML_4096);
    index = combo->AddString("8192");
    combo->SetItemData(index, (DWORD_PTR)ML_8192);
}

BOOL CExportModelsDialog::OnInitDialog() {
    FillCombo(IDC_MINSIZE_COMBO);
    FillCombo(IDC_MAXSIZE_COMBO);
    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);

    CDialog::OnInitDialog();

    m_selected.RemoveAll();
    for (HModelCache *hmc = m_hocc->GetChildModelCache(); hmc; hmc = (HModelCache *)hmc->GetSiblingSame()) {
        String name = hmc->GetName();
        const int iIndex = m_checklistbox.AddString(name.GetNameOnlyWithoutSuffix().Get());
        m_checklistbox.SetItemData(iIndex, (DWORD_PTR)hmc);
        m_checklistbox.SetCheck(iIndex, TRUE);
    }
    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportModelsDialog::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportModelsDialog)
    DDX_Check(pDX, IDC_GENERATEMODELMAPS, m_generatemodelmaps);
    DDX_CBIndex(pDX, IDC_MAXSIZE_COMBO, m_maxsize);
    DDX_CBIndex(pDX, IDC_MINSIZE_COMBO, m_minsize);
    DDX_Control(pDX, IDC_MODELLIST_COMBO, m_checklistbox);
    DDX_Radio(pDX, IDC_SUB1, m_subtype);
    DDX_Check(pDX, IDC_CHECK1, m_applybump);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportModelsDialog, CDialog)
    //{{AFX_MSG_MAP(CExportModelsDialog)
    ON_CBN_SELCHANGE(IDC_MAXSIZE_COMBO, &CExportModelsDialog::OnMaxSize)
    ON_CBN_SELCHANGE(IDC_MINSIZE_COMBO, &CExportModelsDialog::OnMinSize)
    ON_BN_CLICKED(IDC_GENERATEMODELMAPS, &CExportModelsDialog::OnGeneratemodelmaps)
    ON_BN_CLICKED(IDC_BROWSE, &CExportModelsDialog::OnBrowse)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportModelsDialog message handlers

void CExportModelsDialog::OnOK() {
    CDialog::OnOK();
    for (int iIndex = 0; iIndex < m_checklistbox.GetCount(); iIndex++) {
        if (m_checklistbox.GetCheck(iIndex)) {
            auto *hmc = (HModelCache *)m_checklistbox.GetItemData(iIndex);
            m_selected.AddTail(hmc);
        }
    }
    SetRegistryString("3DS Plugin", "Output Directory", m_dir);
    SetRegistryString("3DS Plugin", "Generate Model Maps", m_generatemodelmaps ? "TRUE" : "FALSE");
    SetRegistryValue("3DS Plugin", "Min Map Size", m_minsize);
    SetRegistryValue("3DS Plugin", "Max Map Size", m_maxsize);
    SetRegistryValue("3DS Plugin", "Sub Type", m_subtype);
    SetRegistryString("3DS Plugin", "Apply Displace", m_applybump ? "TRUE" : "FALSE");
}

void CExportModelsDialog::OnMaxSize() {
    const CComboBox *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    auto *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = maxcombo->GetCurSel();
    const int maxlimit = maxcombo->GetItemData(index);

    index = mincombo->GetCurSel();

    if (const int minlimit = mincombo->GetItemData(index); maxlimit < minlimit)
        maxcombo->SetCurSel(index);
}

void CExportModelsDialog::OnMinSize() {
    auto *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    const CComboBox *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = mincombo->GetCurSel();
    const int minlimit = mincombo->GetItemData(index);

    index = maxcombo->GetCurSel();

    if (const int maxlimit = maxcombo->GetItemData(index); minlimit > maxlimit)
        mincombo->SetCurSel(index);
}

void CExportModelsDialog::OnGeneratemodelmaps() {
    m_generatemodelmaps = IsDlgButtonChecked(IDC_GENERATEMODELMAPS);
    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
}

void CExportModelsDialog::OnBrowse() {
    CString caption;
    caption.LoadString(IDS_CHOOSEDIRECTORY);
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!DirRequest(m_dir, caption/*nullptr*/, m_dir.Get(), this))
            return;
    }
    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());
}
