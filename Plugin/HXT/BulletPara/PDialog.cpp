// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "BulletPara.h"
#include "PDialog.h"
#include "F_Protos.h"
#include "SDK/HPropert.h"
#include "SDK/HConstra.h"
#include "SDK/HModel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(HChor *chor) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_chor = chor;

    calculate_weight = GetRegistryValue("BulletPara HXT", "CalculateWeight", FALSE);
    weight = GetRegistryValue("BulletPara HXT", "Weight", 1.F);
    density = GetRegistryValue("BulletPara HXT", "Density", 0.998F);
    bounce = GetRegistryValue("BulletPara HXT", "Bounce", 0.5F);
    friction = GetRegistryValue("BulletPara HXT", "Friction", 0.5F);
    rollingfriction = GetRegistryValue("BulletPara HXT", "RollingFriction", 0.05F);
    spinningfriction = GetRegistryValue("BulletPara HXT", "SpinningFriction", 0);
    lindamp = GetRegistryValue("BulletPara HXT", "LinDamp", 0.04F);
    angdamp = GetRegistryValue("BulletPara HXT", "AngDamp", 0.1F);
    margin = GetRegistryValue("BulletPara HXT", "Margin", 0.025F);
    hulltype = GetRegistryValue("BulletPara HXT", "Hull", 5);
    anisotropic = GetRegistryValue("BulletPara HXT", "Anisotropic", FALSE);
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Check(pDX, IDC_CHECK1, calculate_weight);
    DDX_Check(pDX, IDC_CHECK2, anisotropic);
    DDX_Text(pDX, IDC_EDIT1, weight);
    DDV_MinMaxFloat(pDX, weight, 0.F, 1000.F);
    DDX_Text(pDX, IDC_EDIT2, bounce);
    DDV_MinMaxFloat(pDX, bounce, 0.F, 2.F);
    DDX_Text(pDX, IDC_EDIT3, friction);
    DDV_MinMaxFloat(pDX, friction, 0.F, 2.F);
    DDX_Text(pDX, IDC_EDIT4, lindamp);
    DDV_MinMaxFloat(pDX, lindamp, 0.F, 2.F);
    DDX_Text(pDX, IDC_EDIT5, angdamp);
    DDV_MinMaxFloat(pDX, angdamp, 0.F, 2.F);
    DDX_Text(pDX, IDC_EDIT6, margin);
    DDV_MinMaxFloat(pDX, margin, 0.F, 10.F);
    DDX_Text(pDX, IDC_EDIT7, density);
    DDV_MinMaxFloat(pDX, density, 0.001F, 50.F);
    DDX_Text(pDX, IDC_EDIT8, rollingfriction);
    DDV_MinMaxFloat(pDX, rollingfriction, 0.F, 5.F);
    DDX_Text(pDX, IDC_EDIT9, spinningfriction);
    DDV_MinMaxFloat(pDX, spinningfriction, 0.F, 5.F);
    DDX_CBIndex(pDX, IDC_COMBO1, hulltype);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
    //{{AFX_MSG_MAP(PDialog)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnBnClickedButton1) ON_BN_CLICKED(IDC_BUTTON2, &PDialog::OnBnClickedButton2) ON_BN_CLICKED(IDC_BUTTON3, &PDialog::OnBnClickedButton3) ON_BN_CLICKED(IDC_CHECK1, &PDialog::OnBnClickedCheck1)END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;
    int dx = 0;
    CDC *pDC = id1->GetDC();
    CFont *pFont = id1->GetFont();
    CFont *pOldFont = pDC->SelectObject(pFont);
    TEXTMETRIC tm;
    pDC->GetTextMetrics(&tm);

    for (HHashObject *hho = m_chor->GetChild(); hho; hho = hho->GetSibling()) {
        if (hho->GetObjectType() == HOT_MODEL) {
            auto *hm = (HModel *)hho;
            if (const int count_bullet = hm->GetCountBulletRigidConstraints(); count_bullet > 0) {
                for (int i = 0; i < count_bullet; ++i) {
                    if (HBulletConstraint *hbc = hm->GetBulletRigidConstraint(i); hbc) {
                        if (HTreeObject *ht = (HHashObject *)hbc->GetParent(); ht)
                            temp.Format("%s // %s", hm->GetName(), ht->GetMatchName().Get());
                        else
                            temp.Format("%s", hm->GetName());
                        const int index = id1->AddString(temp);
                        id1->SetItemDataPtr(index, hbc);
                        CSize sz = pDC->GetTextExtent(temp);
                        sz.cx += tm.tmAveCharWidth;
                        if (sz.cx > dx)
                            dx = sz.cx;
                    }
                }
            }
        }
    }
    pDC->SelectObject(pOldFont);
    id1->ReleaseDC(pDC);
    id1->SetHorizontalExtent(dx);

    if (calculate_weight) {
        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
    } else {
        GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
    }
    auto *id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    id2->SetCurSel(hulltype);

    //Create the ToolTip control
    if (!m_ToolTip.Create(this)) {
        TRACE0("Unable to create the ToolTip!");
    } else {
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT1), _T("Mass in kg\r\nRange 0 - 1000"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT2), _T("Tendency of object to bounce\r\nRange 0 - 2"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT3), _T("Resistance of object to movement\r\nRange 0 - 2"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT4), _T("Amount of linear velocity that is lost over time\r\nRange 0 - 2"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT5), _T("Amount of angular velocity that is lost over time\r\nRange 0 - 2"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT6), _T("Threshold of distance near surface\r\nRange 0 - 10"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT7), _T("How dense the material should be\r\nRange 0.001 - 50"));
        //        m_ToolTip.AddTool(GetDlgItem(IDC_CHECK1), _T("Calculate the mass from object volume and density"));
        //        m_ToolTip.SetMaxTipWidth(150);
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT1), _T("Range 0 - 1000"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT2), _T("Range 0 - 2"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT3), _T("Range 0 - 2"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT4), _T("Range 0 - 2"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT5), _T("Range 0 - 2"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT6), _T("Range 0 - 10"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT7), _T("Range 0.001 - 50"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT8), _T("Range 0 - 5"));
        m_ToolTip.AddTool(GetDlgItem(IDC_EDIT9), _T("Range 0 - 5"));
        m_ToolTip.AddTool(GetDlgItem(IDC_CHECK1), _T("Calculate the mass from object volume and density"));
        m_ToolTip.AddTool(GetDlgItem(IDC_CHECK2), _T("Use anisotropic friction model"));
        m_ToolTip.Activate(TRUE);
    }
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {
    UpdateData(TRUE);
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CWaitCursor wait;
    const int nCount = id1->GetSelCount();
    CArray<int, int> selection;
    selection.SetSize(nCount);
    id1->GetSelItems(nCount, selection.GetData());
    for (int i = 0; i < selection.GetSize(); ++i) {
        const auto hc1 = (HBulletConstraint *)id1->GetItemDataPtr(selection[i]);
        ASSERT(hc1);
        const CButton *cCheck = (CButton *)GetDlgItem(IDC_CHECK3);
        if (cCheck->GetCheck()) {
            HTypeCategoryProperty *hcp = hc1->GetShapeHull();
            hcp->SetValue(hulltype);
            hcp->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK4);
        if (cCheck->GetCheck()) {
            hc1->GetAnisotropicFriction()->SetValue(anisotropic);
            hc1->GetAnisotropicFriction()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK5);
        if (cCheck->GetCheck()) {
            hc1->GetDensity()->SetValue(density);
            hc1->GetDensity()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK6);
        if (cCheck->GetCheck()) {
            hc1->GetWeight()->SetValue(weight);
            hc1->GetWeight()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK7);
        if (cCheck->GetCheck()) {
            hc1->GetBounce()->SetValue(bounce);
            hc1->GetBounce()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK8);
        if (cCheck->GetCheck()) {
            hc1->GetFriction()->SetValue(friction);
            hc1->GetFriction()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK9);
        if (cCheck->GetCheck()) {
            hc1->GetLinearDamping()->SetValue(lindamp);
            hc1->GetLinearDamping()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK10);
        if (cCheck->GetCheck()) {
            hc1->GetAngularDamping()->SetValue(angdamp);
            hc1->GetAngularDamping()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK11);
        if (cCheck->GetCheck()) {
            hc1->GetMargin()->SetValue(margin);
            hc1->GetMargin()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK12);
        if (cCheck->GetCheck()) {
            if (calculate_weight) {
                hc1->CalculateWeight();
                hc1->OnModified();
            }
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK13);
        if (cCheck->GetCheck()) {
            hc1->GetRollingFriction()->SetValue(rollingfriction);
            hc1->GetRollingFriction()->OnModified();
        }
        cCheck = (CButton *)GetDlgItem(IDC_CHECK14);
        if (cCheck->GetCheck()) {
            hc1->GetSpinningFriction()->SetValue(spinningfriction);
            hc1->GetSpinningFriction()->OnModified();
        }
    }
    SetRegistryValue("BulletPara HXT", "CalculateWeight", calculate_weight);
    SetRegistryValue("BulletPara HXT", "Weight", weight);
    SetRegistryValue("BulletPara HXT", "Density", density);
    SetRegistryValue("BulletPara HXT", "Bounce", bounce);
    SetRegistryValue("BulletPara HXT", "Friction", friction);
    SetRegistryValue("BulletPara HXT", "LinDamp", lindamp);
    SetRegistryValue("BulletPara HXT", "AngDamp", angdamp);
    SetRegistryValue("BulletPara HXT", "Margin", margin);
    SetRegistryValue("BulletPara HXT", "Hull", hulltype);
    SetRegistryValue("BulletPara HXT", "Anisotropic", anisotropic);
    SetRegistryValue("BulletPara HXT", "RollingFriction", rollingfriction);
    SetRegistryValue("BulletPara HXT", "SpinningFriction", spinningfriction);
    CPluginDialog::OnOK();
}

void PDialog::OnBnClickedButton1() {
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    id1->SetSel(-1, TRUE);
}

void PDialog::OnBnClickedButton2() {
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    id1->SetSel(-1, FALSE);
}

void PDialog::OnBnClickedCheck1() {
    calculate_weight ^= TRUE;  // NOLINT(hicpp-signed-bitwise)
    if (calculate_weight) {
        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
    } else {
        GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
    }
}

BOOL PDialog::PreTranslateMessage(MSG *pMsg) {
    m_ToolTip.RelayEvent(pMsg);
    return CPluginDialog::PreTranslateMessage(pMsg);
}

void PDialog::OnBnClickedButton3() {
    UpdateData(TRUE);
    calculate_weight = FALSE;
    anisotropic = FALSE;
    hulltype = 5;
    weight = 1.F;
    density = 0.998F;
    bounce = 0.5F;
    friction = 0.5F;
    lindamp = 0.04F;
    angdamp = 0.1F;
    margin = 0.025F;
    rollingfriction = 0.05F;
    spinningfriction = 0.F;
    UpdateData(FALSE);
    if (calculate_weight) {
        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
    } else {
        GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
    }
}
