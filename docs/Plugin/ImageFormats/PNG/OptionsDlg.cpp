// OptionsDlg.cpp : implementation file
//
#include "StdAfx.h"
#include "resource.h"
#include "ImageIO.h"
#include "Custom.h"
#include "OptionsDlg.h"

// OptionsDlg dialog

IMPLEMENT_DYNAMIC(OptionsDlg, CPluginDialog)

OptionsDlg::OptionsDlg(CWnd *pParent) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), m_interlaced{0}, m_8bit{0}, m_compression{0} {}

OptionsDlg::~OptionsDlg() = default;

void OptionsDlg::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_INTERLACED, m_interlaced);
    DDX_Radio(pDX, IDC_8BIT, m_8bit);
}

BOOL OptionsDlg::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
    id1->AddString("No Compression");
    id1->AddString("Best Speed");
    id1->AddString("Best Compression");
    id1->SetCurSel(m_compression);
    return TRUE;
}

void OptionsDlg::OnOK() {
    UpdateData(true);
    const CComboBox *id1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
    m_compression = id1->GetCurSel();
    CPluginDialog::OnOK();
}

BEGIN_MESSAGE_MAP(OptionsDlg, CPluginDialog)END_MESSAGE_MAP()

// OptionsDlg message handlers
