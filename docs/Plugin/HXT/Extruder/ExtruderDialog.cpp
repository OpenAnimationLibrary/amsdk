// ExtruderDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ExtruderDialog.h"
#include "StrClass.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtruderDialog dialog

CExtruderDialog::CExtruderDialog(HModelCache *hmc, HGroup *hg) : CPluginDialog(IDD, nullptr) {
    m_hmodel = hmc;
    m_hpathgroup = hg;
    m_hxsectiongroup = hg;
    m_extrusionmethod = GetRegistryValue("Extruder HXT", "Extrusionmethod", 0);
    m_extrusioncount = GetRegistryValue("Extruder HXT", "Extrusioncount", 10);
    m_extrusiondistance = GetRegistryValue("Extruder HXT", "Extrusiondistance", 10.F);
    m_method = GetRegistryValue("Extruder HXT", "Method", 1);
    m_looped = GetRegistryValue("Extruder HXT", "Looped", 0);
}

void CExtruderDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExtruderDialog)
    DDX_Control(pDX, IDC_PATHGROUP_COMBO, m_pathgroupcombo);
    DDX_Control(pDX, IDC_XSECTIONGROUP_COMBO, m_xsectiongroupcombo);
    DDX_Radio(pDX, IDC_EXTRUSION_COUNT_RADIO, m_extrusionmethod);
    DDX_Text(pDX, IDC_EXTRUSION_COUNT_EDIT, m_extrusioncount);
    DDV_MinMaxInt(pDX, m_extrusioncount, 1, 99999);
    DDX_Radio(pDX, IDC_METHOD_COPY_RADIO, m_method);
    DDX_Check(pDX, IDC_CHECK1, m_looped);
    DDX_Unit(pDX, IDC_EXTRUSION_EVERY_EDIT, m_extrusiondistance);
    DDV_MinMaxUnit(pDX, m_extrusiondistance, 0.001F, 999999.0F);
    //}}AFX_DATA_MAP
    if (pDX->m_bSaveAndValidate) {
        if (m_pathgroupcombo.GetCurSel() != CB_ERR) {
            m_hpathgroup = (HGroup *)m_pathgroupcombo.GetItemDataPtr(m_pathgroupcombo.GetCurSel());
        }
        if (m_xsectiongroupcombo.GetCurSel() != CB_ERR)
            m_hxsectiongroup = (HGroup *)m_xsectiongroupcombo.GetItemDataPtr(m_xsectiongroupcombo.GetCurSel());
    }
}

BEGIN_MESSAGE_MAP(CExtruderDialog, CDialog)
    //{{AFX_MSG_MAP(CExtruderDialog)
    //}}AFX_MSG_MAP
    ON_CBN_SELCHANGE(IDC_PATHGROUP_COMBO, &CExtruderDialog::OnCbnSelchangePathgroupCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtruderDialog message handlers

BOOL CExtruderDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    HGroupContainer *hgc = m_hmodel->GetChildGroupContainer();
    if (hgc) {
        for (HGroup *hgroup = hgc->GetChildGroup(); hgroup; hgroup = (HGroup *)hgroup->GetSiblingSame()) {
            int index = m_pathgroupcombo.AddString(hgroup->GetName());
            m_pathgroupcombo.SetItemDataPtr(index, hgroup);
            if (m_hpathgroup != hgroup)
                m_pathgroupcombo.SetCurSel(index);

            index = m_xsectiongroupcombo.AddString(hgroup->GetName());
            m_xsectiongroupcombo.SetItemDataPtr(index, hgroup);
            if (m_hxsectiongroup == hgroup)
                m_xsectiongroupcombo.SetCurSel(index);
        }
        if (m_pathgroupcombo.GetCurSel() != CB_ERR) {
            m_hpathgroup = (HGroup *)m_pathgroupcombo.GetItemDataPtr(m_pathgroupcombo.GetCurSel());
            HGroupCP *hgcp = m_hpathgroup->GetGroupCP();
            if (hgcp) {
                HCP *hcp = hgcp->GetCP();
                if (hcp) {
                    HSpline *hspline = hcp->GetSpline();
                    if (hspline) {
                        BOOL islooped = FALSE;
                        for (HCP *cp1 = hspline->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
                            if (cp1->IsLoop()) {
                                islooped = TRUE;
                                break;
                            }
                        }
                        if (islooped) {
                            GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
                        } else {
                            GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
                            auto *ccb = (CButton *)GetDlgItem(IDC_CHECK1);
                            ccb->SetCheck(FALSE);
                            m_looped = FALSE;
                        }
                    }
                }
            }
        }
    }

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExtruderDialog::OnOK() {
    CPluginDialog::OnOK();
    SetRegistryValue("Extruder HXT", "Extrusionmethod", m_extrusionmethod);
    SetRegistryValue("Extruder HXT", "Extrusioncount", (int)m_extrusioncount);
    SetRegistryValue("Extruder HXT", "Extrusiondistance", m_extrusiondistance);
    SetRegistryValue("Extruder HXT", "Method", m_method);
    SetRegistryValue("Extruder HXT", "Looped", m_looped);
}

void CExtruderDialog::OnCbnSelchangePathgroupCombo() {
    // TODO: Add your control notification handler code here
    if (m_pathgroupcombo.GetCurSel() != CB_ERR) {
        m_hpathgroup = (HGroup *)m_pathgroupcombo.GetItemDataPtr(m_pathgroupcombo.GetCurSel());
        HGroupCP *hgcp = m_hpathgroup->GetGroupCP();
        if (hgcp) {
            HCP *hcp = hgcp->GetCP();
            if (hcp) {
                HSpline *hspline = hcp->GetSpline();
                if (hspline) {
                    BOOL islooped = FALSE;
                    for (HCP *cp1 = hspline->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
                        if (cp1->IsLoop()) {
                            islooped = TRUE;
                            break;
                        }
                    }
                    if (islooped) {
                        GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
                    } else {
                        GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
                        auto *ccb = (CButton *)GetDlgItem(IDC_CHECK1);
                        ccb->SetCheck(FALSE);
                        m_looped = FALSE;
                    }
                }
            }
        }
    }
}
