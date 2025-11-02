// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "Transfer_AW.h"
#include "PDialog.h"

IMPLEMENT_DYNAMIC(PDialog, CPluginDialog)

PDialog::PDialog(W_PARA *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_para = parameters;
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_para->pass1_cp);
    DDV_MinMaxInt(pDX, m_para->pass1_cp, 1, 17);
    DDX_Text(pDX, IDC_EDIT2, m_para->pass2_cp);
    DDV_MinMaxInt(pDX, m_para->pass2_cp, 1, 17);
    DDX_Text(pDX, IDC_EDIT3, m_para->smooth);
    DDV_MinMaxFloat(pDX, m_para->smooth, 0.F, 1.F);
    DDX_Text(pDX, IDC_EDIT4, m_para->az_smoothpass);
    DDV_MinMaxInt(pDX, m_para->az_smoothpass, 1, 10001);
    DDX_Check(pDX, IDC_CHECK1, m_para->alternate_hiresdist);
    DDX_Check(pDX, IDC_CHECK2, m_para->proceed_nohidden);
    //	DDX_Radio(pDX, IDC_RADIO1, m_para->az_smoothpass);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
END_MESSAGE_MAP()

// PDialog-Meldungshandler
