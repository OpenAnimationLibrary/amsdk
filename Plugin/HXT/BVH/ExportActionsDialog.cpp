// ExportActionsDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"

#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"

CExportActionsDialog::CExportActionsDialog(HActionCacheContainer *hacc) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hacc = hacc;
    m_dir = GetRegistryString("BVH Plugin", "Output Directory", ".");
    m_ispadmotion = GetRegistryString("BVH Plugin", "Pad Motion", "FALSE") == "TRUE";
    m_nomotion = GetRegistryString("BVH Plugin", "No Motion", "FALSE") == "TRUE";
    m_exportstate = GetRegistryValue("BVH Plugin", "Export Bones", 0);
    m_errortolerance = 0.F;
}

CExportActionsDialog::~CExportActionsDialog() {
    m_checklistbox.Detach();
}

void CExportActionsDialog::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ACTIONLIST_COMBO, m_checklistbox);
    DDX_Check(pDX, IDC_PADMOTION_CHECK, m_ispadmotion);
    DDX_Check(pDX, IDC_CHECK1, m_nomotion);
    DDX_Radio(pDX, IDC_RADIO1, m_exportstate);
}

BEGIN_MESSAGE_MAP(CExportActionsDialog, CDialog)ON_BN_CLICKED(IDC_BROWSE, &CExportActionsDialog::OnBrowse)END_MESSAGE_MAP()

BOOL CExportActionsDialog::OnInitDialog() {
    CDialog::OnInitDialog();

    m_selected.RemoveAll();
    for (HActionCache *hac = m_hacc->GetChildActionCache(); hac; hac = hac->GetSiblingActionCache()) {
        String name = hac->GetName();
        const int iIndex = m_checklistbox.AddString(name.GetNameOnlyWithoutSuffix().Get());
        m_checklistbox.SetItemData(iIndex, (DWORD_PTR)hac);
        m_checklistbox.SetCheck(iIndex, TRUE);
    }

    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportActionsDialog::OnOK() {
    CDialog::OnOK();
    for (int iIndex = 0; iIndex < m_checklistbox.GetCount(); iIndex++) {
        if (m_checklistbox.GetCheck(iIndex)) {
            auto *hac = (HActionCache *)m_checklistbox.GetItemData(iIndex);
            m_selected.AddTail(hac);
        }
    }
    SetRegistryString("BVH Plugin", "Output Directory", m_dir);
    SetRegistryString("BVH Plugin", "Pad Motion", m_ispadmotion ? "TRUE" : "FALSE");
    SetRegistryValue("BVH Plugin", "Export Bones", m_exportstate);
    SetRegistryString("BVH Plugin", "No Motion", m_nomotion ? "TRUE" : "FALSE");
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
