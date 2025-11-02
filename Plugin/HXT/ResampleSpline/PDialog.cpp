// PDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "ResampleSpline.h"
#include "PDialog.h"

// PDialog dialog

//IMPLEMENT_DYNAMIC(PDialog, CDialog)

PDialog::PDialog(PARAMETER *m_para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    para = m_para;
    if (para->zcount == -1) {
        para->zcount = 1;
        z_unsed = TRUE;
    } else {
        z_unsed = FALSE;
    }
    //}}AFX_DATA_INIT
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, para->neededdistance);
    DDV_MinMaxFloat(pDX, para->neededdistance, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT2, para->iteration);
    DDV_MinMaxInt(pDX, para->iteration, 1, 10000);
    DDX_Text(pDX, IDC_EDIT3, para->zcount);
    DDV_MinMaxInt(pDX, para->zcount, 1, 1000);
    DDX_Text(pDX, IDC_EDIT4, para->zvalue);
    DDV_MinMaxFloat(pDX, para->zvalue, -1000.F, 1000.F);
    DDX_Check(pDX, IDC_CHECK1, para->extrude);
    DDX_Radio(pDX, IDC_RADIO1, para->direction);
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CString temp;
    temp.Format("Spline length %.3f   CP count %i", para->splinelength, para->cpcount);
    SetDlgItemText(IDC_STATIC_LENGTH, temp.GetBuffer());
    if (z_unsed) {
        GetDlgItem(IDC_EDIT3)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT4)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_COUNT)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_VALUE)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK1)->ShowWindow(FALSE);
        GetDlgItem(IDC_RADIO1)->ShowWindow(FALSE);
        GetDlgItem(IDC_RADIO2)->ShowWindow(FALSE);
        GetDlgItem(IDC_RADIO3)->ShowWindow(FALSE);
    }
    return TRUE;
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        ON_EN_KILLFOCUS(IDC_EDIT2, &PDialog::OnEnKillfocusEdit2)
        ON_EN_KILLFOCUS(IDC_EDIT1, &PDialog::OnEnKillfocusEdit1)
END_MESSAGE_MAP()

// PDialog message handlers

void PDialog::OnEnKillfocusEdit2() {
    UpdateData(true);
    para->neededdistance = para->splinelength / para->iteration;
    UpdateData(false);
}

void PDialog::OnEnKillfocusEdit1() {
    UpdateData(true);
    para->iteration = RoundValue(para->splinelength / para->neededdistance);
    UpdateData(false);
}

void PDialog::OnOK() {
    // TODO: Zusıtzliche Pr≥fung hier einf≥gen
    SetRegistryValue("ResampleSpline HXT", "distance", para->neededdistance);
    SetRegistryValue("ResampleSpline HXT", "extrude count", para->zcount);
    SetRegistryValue("ResampleSpline HXT", "extrude distance", para->zvalue);
    SetRegistryValue("ResampleSpline HXT", "extruding", para->extrude);
    SetRegistryValue("ResampleSpline HXT", "extrude direction", para->direction);
    CPluginDialog::OnOK();
}
