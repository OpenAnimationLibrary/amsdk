// KB  10/3/00  \Ken90\Plugin\Hxt\Grid\GridDialog.cpp

#include "StdAfx.h"
#include "StrClass.h"
#include "GridDialog.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridDialog dialog

CGridDialog::CGridDialog(GridParameters *parameters): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(CGridDialog)
    m_parameters = parameters;
    //}}AFX_DATA_INIT
    // Init dialog from stored registry values
    m_parameters->m_height = GetRegistryValue("Grid HXT", "Height", 30.0F);
    m_parameters->m_width = GetRegistryValue("Grid HXT", "Width", 30.0F);
    m_parameters->m_stepheight = GetRegistryValue("Grid HXT", "Step Height", 5.0F);
    m_parameters->m_stepwidth = GetRegistryValue("Grid HXT", "Step Width", 5.0F);
    m_parameters->m_orientation = GetRegistryValue("Grid HXT", "Orientation", 0);
    m_parameters->m_turbscale = GetRegistryValue("Grid HXT", "Turb Scale", 100.F);
    m_parameters->m_turbmagnitude = GetRegistryValue("Grid HXT", "Turb Magnitude", 0.F);
}

void CGridDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_HEIGHT, m_parameters->m_height);
    DDV_MinMaxFloat(pDX, m_parameters->m_height, .01F, 100000.0F);
    DDX_Text(pDX, IDC_STEPHEIGHT, m_parameters->m_stepheight);
    DDV_MinMaxFloat(pDX, m_parameters->m_stepheight, .01F, 100000.0F);
    DDX_Text(pDX, IDC_STEPWIDTH, m_parameters->m_stepwidth);
    DDV_MinMaxFloat(pDX, m_parameters->m_stepwidth, .01F, 100000.0F);
    DDX_Text(pDX, IDC_WIDTH, m_parameters->m_width);
    DDV_MinMaxFloat(pDX, m_parameters->m_width, .01F, 100000.0F);
    DDX_Radio(pDX, IDC_XY, m_parameters->m_orientation);
    DDX_Text(pDX, IDC_SCALE, m_parameters->m_turbscale);
    DDV_MinMaxFloat(pDX, m_parameters->m_turbscale, .001f, 10000.0F);
    DDX_Text(pDX, IDC_MAGNITUDE, m_parameters->m_turbmagnitude);
    DDV_MinMaxFloat(pDX, m_parameters->m_turbmagnitude, 0.F, 100000.0F);

    //{{AFX_DATA_MAP(CGridDialog)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGridDialog, CDialog)
    //{{AFX_MSG_MAP(CGridDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridDialog message handlers

void CGridDialog::OnOK() {
    CPluginDialog::OnOK();
    // save dialog values to registry
    SetRegistryValue("Grid HXT", "Height", m_parameters->m_height);
    SetRegistryValue("Grid HXT", "Width", m_parameters->m_width);
    SetRegistryValue("Grid HXT", "Step Height", m_parameters->m_stepheight);
    SetRegistryValue("Grid HXT", "Step Width", m_parameters->m_stepwidth);
    SetRegistryValue("Grid HXT", "Orientation", m_parameters->m_orientation);
    SetRegistryValue("Grid HXT", "Turb Scale", m_parameters->m_turbscale);
    SetRegistryValue("Grid HXT", "Turb Magnitude", m_parameters->m_turbmagnitude);

}
