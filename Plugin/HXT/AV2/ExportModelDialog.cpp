// ExportModelDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ExportModelDialog.h"
#include "F_Protos.h"
#include "MapLimit.h"
#include "SDK/HModel.h"
#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportModelDialog dialog

CExportModelDialog::CExportModelDialog(const String &filename): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    const String path = GetRegistryString("AV2 Plugin", "File Path", ".");
    m_filename = filename.GetNameOnlyWithoutSuffix() + ".AV2";
    m_filename = CombineNameToPath(path, m_filename);

    //{{AFX_DATA_INIT(CExportModelDialog)
    m_generatemodelmaps = GetRegistryString("AV2 Plugin", "Generate Model Maps", "FALSE") == "TRUE";
    m_minsize = GetRegistryValue("AV2 Plugin", "Min Map Size", ML_1);
    m_maxsize = GetRegistryValue("AV2 Plugin", "Max Map Size", ML_256);
    //}}AFX_DATA_INIT
}

void CExportModelDialog::FillCombo(const int id) const {
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

BOOL CExportModelDialog::OnInitDialog() {
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

    FillCombo(IDC_MINSIZE_COMBO);
    FillCombo(IDC_MAXSIZE_COMBO);
    CPluginDialog::OnInitDialog();

    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportModelDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportModelDialog)
    DDX_Check(pDX, IDC_GENERATEMODELMAPS, m_generatemodelmaps);
    DDX_CBIndex(pDX, IDC_MINSIZE_COMBO, m_minsize);
    DDX_CBIndex(pDX, IDC_MAXSIZE_COMBO, m_maxsize);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportModelDialog, CDialog)
    //{{AFX_MSG_MAP(CExportModelDialog)
    ON_BN_CLICKED(IDC_BROWSE, &CExportModelDialog::OnBrowse)
    ON_CBN_SELCHANGE(IDC_MAXSIZE_COMBO, &CExportModelDialog::OnMaxSize)
    ON_CBN_SELCHANGE(IDC_MINSIZE_COMBO, &CExportModelDialog::OnMinSize)
    ON_BN_CLICKED(IDC_GENERATEMODELMAPS, &CExportModelDialog::OnGeneratemodelmaps)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportModelDialog message handlers

void CExportModelDialog::OnOK() {
    CPluginDialog::OnOK();
    const String path = m_filename.GetPathOnly();
    SetRegistryString("AV2 Plugin", "File Path", path);
    SetRegistryString("AV2 Plugin", "Generate Model Maps", m_generatemodelmaps ? "TRUE" : "FALSE");
    SetRegistryValue("AV2 Plugin", "Min Map Size", m_minsize);
    SetRegistryValue("AV2 Plugin", "Max Map Size", m_maxsize);
}

void CExportModelDialog::OnBrowse() {
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);

    const String ext("AV2");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, m_filename, ext.Get(), ext.Get()))
            return;
    }
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
}

void CExportModelDialog::OnMaxSize() {
    const CComboBox *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    auto *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = maxcombo->GetCurSel();
    const int maxlimit = maxcombo->GetItemData(index);

    index = mincombo->GetCurSel();
    const int minlimit = mincombo->GetItemData(index);

    if (maxlimit < minlimit)
        maxcombo->SetCurSel(index);
}

void CExportModelDialog::OnMinSize() {
    auto *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    const CComboBox *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = mincombo->GetCurSel();
    const int minlimit = mincombo->GetItemData(index);

    index = maxcombo->GetCurSel();
    const int maxlimit = maxcombo->GetItemData(index);

    if (minlimit > maxlimit)
        mincombo->SetCurSel(index);
}

void CExportModelDialog::OnGeneratemodelmaps() {
    m_generatemodelmaps = IsDlgButtonChecked(IDC_GENERATEMODELMAPS);
    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
}
