// PDialog.cpp: Implementierungsdatei
#include "StdAfx.h"
#include "CalcSurface.h"
#include "PDialog.h"
#include "Detail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_surface = 0.0;
    m_photoncast = 1000;
    m_photonsample = 10;
    m_samplingarea = 1.F;
    m_para = parameters;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, m_surface);
    DDX_Text(pDX, IDC_EDIT2, m_photoncast);
    DDV_MinMaxInt(pDX, m_photoncast, 1000, 50000000);
    DDX_Text(pDX, IDC_EDIT3, m_photonsample);
    DDV_MinMaxInt(pDX, m_photonsample, 10, 500000);
    DDX_Text(pDX, IDC_EDIT4, m_samplingarea);
    DDV_MinMaxFloat(pDX, m_samplingarea, 0.0001F, 50000.F);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnButton1)
        ON_BN_CLICKED(IDC_BUTTON2, &PDialog::OnButton2)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::Calculate() {
    const double a = m_photoncast / m_surface;
    const double b = m_photonsample / a;
    const int c = (int)(hash_math::sqrt(b / hash_constants::pi ) * 100) / 50;
    m_samplingarea = (float)c * 50.F;
    m_samplingarea = MIN(MAX(m_samplingarea, 0.0001F),50000.F);
}

void PDialog::OnButton1() {
    // Recalculate
    if (UpdateData(true)) {
        Calculate();
        UpdateData(false);
    }
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    m_surface = m_para->surface;
    m_photoncast = m_para->iVPhotonCast;
    m_photonsample = m_para->iVPhotonSample;
    Calculate();
    UpdateData(false);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {
    m_para->iVPhotonCast = m_photoncast;
    m_para->iVPhotonSample = m_photonsample;
    m_para->fVSampleArea = m_samplingarea;
    CPluginDialog::OnOK();
}

void PDialog::OnButton2()  {
    CDetail pdlg(m_para, m_hWnd);
    pdlg.DoModal();
}
