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
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportModelsDialog dialog

CExportModelsDialog::CExportModelsDialog(HObjectCacheContainer *hocc) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hocc = hocc;
    m_dir = GetRegistryString("OBJ Plugin", "Output Directory", ".");
    m_generatemodelmaps = GetRegistryString("OBJ Plugin", "Generate Model Maps", "FALSE") == "TRUE";
    m_minsize = GetRegistryValue("OBJ Plugin", "Min Map Size", ML_1);
    m_maxsize = GetRegistryValue("OBJ Plugin", "Max Map Size", ML_256);
    m_subtype = GetRegistryValue("OBJ Plugin", "Sub Type", ST_VARIABLE);
    m_exportscale = GetRegistryValue("OBJ Plugin", "ExportScale", 1.F);
    m_applybump = GetRegistryString("OBJ Plugin", "Apply Displace", "FALSE") == "TRUE";
    m_discardfaces = GetRegistryString("OBJ Plugin", "Discard degenerated faces", "FALSE") == "TRUE";
    m_btriangles = GetRegistryString("OBJ Plugin", "Triangles only", "FALSE") == "TRUE";
    m_exportnormals = GetRegistryString("OBJ Plugin", "Export Normals", "TRUE") == "TRUE";

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
    CDialog::OnInitDialog();

    FillCombo(IDC_MINSIZE_COMBO);
    FillCombo(IDC_MAXSIZE_COMBO);
    GetDlgItem(IDC_MINSIZE_COMBO)->EnableWindow(m_generatemodelmaps);
    GetDlgItem(IDC_MAXSIZE_COMBO)->EnableWindow(m_generatemodelmaps);

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
    DDX_Radio(pDX, IDC_SUB1, m_subtype);
    DDX_Check(pDX, IDC_TRIANGLES, m_btriangles);
    DDX_Text(pDX, IDC_EXPORTSCALE, m_exportscale);
    DDV_MinMaxFloat(pDX, m_exportscale, 1e-10F, 10000.F);
    DDX_Check(pDX, IDC_CHECK1, m_applybump);
    DDX_Check(pDX, IDC_CHECK4, m_discardfaces);
    DDX_Check(pDX, IDC_CHECK5, m_exportnormals);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_MODELLIST_COMBO, m_checklistbox);
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
    SetRegistryString("OBJ Plugin", "Output Directory", m_dir);
    SetRegistryString("OBJ Plugin", "Generate Model Maps", m_generatemodelmaps ? "TRUE" : "FALSE");
    SetRegistryString("OBJ Plugin", "Apply Displace", m_applybump ? "TRUE" : "FALSE");
    SetRegistryValue("OBJ Plugin", "Min Map Size", m_minsize);
    SetRegistryValue("OBJ Plugin", "Max Map Size", m_maxsize);
    SetRegistryValue("OBJ Plugin", "Sub Type", m_subtype);
    SetRegistryValue("OBJ Plugin", "ExportScale", m_exportscale);
    SetRegistryString("OBJ Plugin", "Discard degenerated faces", m_discardfaces ? "TRUE" : "FALSE");
    SetRegistryString("OBJ Plugin", "Triangles only", m_btriangles ? "TRUE" : "FALSE");
    SetRegistryString("OBJ Plugin", "Export Normals", m_exportnormals ? "TRUE" : "FALSE");
}

void CExportModelsDialog::OnMaxSize() {
    const CComboBox *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    auto *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = maxcombo->GetCurSel();
    const int maxlimit = (int)maxcombo->GetItemData(index);

    index = mincombo->GetCurSel();
    const int minlimit = (int)mincombo->GetItemData(index);

    if (maxlimit < minlimit)
        maxcombo->SetCurSel(index);
}

void CExportModelsDialog::OnMinSize() {
    auto *mincombo = (CComboBox *)GetDlgItem(IDC_MINSIZE_COMBO);
    const CComboBox *maxcombo = (CComboBox *)GetDlgItem(IDC_MAXSIZE_COMBO);

    int index = mincombo->GetCurSel();
    const int minlimit = (int)mincombo->GetItemData(index);

    index = maxcombo->GetCurSel();
    const int maxlimit = (int)maxcombo->GetItemData(index);

    if (minlimit > maxlimit)
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
