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
    m_dir = GetRegistryString("DXF Plugin", "Output Directory", ".");
    m_subtype = GetRegistryValue("DXF Plugin", "Sub Type", ST_VARIABLE);
    m_applybump = GetRegistryString("DXF Plugin", "Apply Displace", "FALSE") == "TRUE";
    //{{AFX_DATA_INIT(CExportModelsDialog)
    //}}AFX_DATA_INIT
}

BOOL CExportModelsDialog::OnInitDialog() {
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
    DDX_Control(pDX, IDC_MODELLIST_COMBO, m_checklistbox);
    DDX_Radio(pDX, IDC_SUB1, m_subtype);
    DDX_Check(pDX, IDC_CHECK1, m_applybump);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportModelsDialog, CDialog)
    //{{AFX_MSG_MAP(CExportModelsDialog)
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
    SetRegistryString("DXF Plugin", "Output Directory", m_dir);
    SetRegistryValue("DXF Plugin", "Sub Type", m_subtype);
    SetRegistryString("DXF Plugin", "Apply Displace", m_applybump ? "TRUE" : "FALSE");
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
