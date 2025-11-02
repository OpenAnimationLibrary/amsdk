// KB  6/4/01  \Ken90\Plugin\HXT\Duplicator\DupDialog.cpp

#include "StdAfx.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "DupDialog.h"
#include "Hxt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDupDialog dialog

CDupDialog::CDupDialog(DupParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(CDupDialog)
    m_parameters = parameters;
    m_parameters->m_translate.x = GetRegistryValue("Duplicator HXT", "TranslateX", 0.F);
    m_parameters->m_translate.y = GetRegistryValue("Duplicator HXT", "TranslateY", -5.0F);
    m_parameters->m_translate.z = GetRegistryValue("Duplicator HXT", "TranslateZ", 0.F);
    m_parameters->m_sweeprotate.x = GetRegistryValue("Duplicator HXT", "RotateX", 0.F);
    m_parameters->m_sweeprotate.y = GetRegistryValue("Duplicator HXT", "RotateY", 0.F);
    m_parameters->m_sweeprotate.z = GetRegistryValue("Duplicator HXT", "RotateZ", 0.F);
    m_parameters->m_offsetdisttocenter = GetRegistryValue("Duplicator HXT", "OffsetDistToCenter", 0.F);
    m_parameters->m_stopatdist = GetRegistryValue("Duplicator HXT", "StopAtDist", 0.F);
    m_parameters->m_repeat = GetRegistryValue("Duplicator HXT", "Repeat", 10);
    m_parameters->m_isextrude = GetRegistryValue("Duplicator HXT", "IsExtrude", TRUE);
    m_parameters->m_tumblerotate.x = GetRegistryValue("Duplicator HXT", "TumbleRotateX", 0.F);
    m_parameters->m_tumblerotate.y = GetRegistryValue("Duplicator HXT", "TumbleRotateY", 0.F);
    m_parameters->m_tumblerotate.z = GetRegistryValue("Duplicator HXT", "TumbleRotateZ", 0.F);
    m_parameters->m_tumblepivotoffset.x = GetRegistryValue("Duplicator HXT", "TumblePivotX", 0.F);
    m_parameters->m_tumblepivotoffset.y = GetRegistryValue("Duplicator HXT", "TumblePivotY", 0.F);
    m_parameters->m_tumblepivotoffset.z = GetRegistryValue("Duplicator HXT", "TumblePivotZ", 0.F);
    m_parameters->m_tumblescale.x = GetRegistryValue("Duplicator HXT", "TumbleScaleX", 100.F);
    m_parameters->m_tumblescale.y = GetRegistryValue("Duplicator HXT", "TumbleScaleY", 100.F);
    m_parameters->m_tumblescale.z = GetRegistryValue("Duplicator HXT", "TumbleScaleZ", 100.F);
    //}}AFX_DATA_INIT
}

void CDupDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TRANSX, m_parameters->m_translate.x);
    DDV_MinMaxFloat(pDX, m_parameters->m_translate.x, -1000.0F, 1000.0F);
    DDX_Text(pDX, IDC_TRANSY, m_parameters->m_translate.y);
    DDV_MinMaxFloat(pDX, m_parameters->m_translate.y, -1000.0F, 1000.0F);
    DDX_Text(pDX, IDC_TRANSZ, m_parameters->m_translate.z);
    DDV_MinMaxFloat(pDX, m_parameters->m_translate.x, -1000.0F, 1000.0F);
    DDX_Text(pDX, IDC_ROTATEX, m_parameters->m_sweeprotate.x);
    DDV_MinMaxFloat(pDX, m_parameters->m_sweeprotate.x, -360.0F, 360.0F);
    DDX_Text(pDX, IDC_ROTATEY, m_parameters->m_sweeprotate.y);
    DDV_MinMaxFloat(pDX, m_parameters->m_sweeprotate.y, -360.0F, 360.0F);
    DDX_Text(pDX, IDC_ROTATEZ, m_parameters->m_sweeprotate.z);
    DDV_MinMaxFloat(pDX, m_parameters->m_sweeprotate.z, -360.0F, 360.0F);
    DDX_Text(pDX, IDC_OFFSETDISTTOCENTER, m_parameters->m_offsetdisttocenter);
    DDV_MinMaxFloat(pDX, m_parameters->m_offsetdisttocenter, -1000.0F, 1000.0F);
    DDX_Text(pDX, IDC_STOPATDIST, m_parameters->m_stopatdist);
    DDV_MinMaxFloat(pDX, m_parameters->m_stopatdist, -1000.0F, 1000.0F);

    DDX_Radio(pDX, IDC_COPY, m_parameters->m_isextrude);
    DDX_Text(pDX, IDC_REPEAT, m_parameters->m_repeat);
    DDV_MinMaxInt(pDX, m_parameters->m_repeat, 1, 10000);

    DDX_Text(pDX, IDC_PIVOTX, m_parameters->m_tumblepivotoffset.x);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblepivotoffset.x, -10000.0F, 10000.0F);
    DDX_Text(pDX, IDC_PIVOTY, m_parameters->m_tumblepivotoffset.y);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblepivotoffset.y, -10000.0F, 10000.0F);
    DDX_Text(pDX, IDC_PIVOTZ, m_parameters->m_tumblepivotoffset.z);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblepivotoffset.z, -10000.0F, 10000.0F);
    DDX_Text(pDX, IDC_TUMBLEROTATEX, m_parameters->m_tumblerotate.x);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblerotate.x, -360.0F, 360.0F);
    DDX_Text(pDX, IDC_TUMBLEROTATEY, m_parameters->m_tumblerotate.y);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblerotate.y, -360.0F, 360.0F);
    DDX_Text(pDX, IDC_TUMBLEROTATEZ, m_parameters->m_tumblerotate.z);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblerotate.z, -360.0F, 360.0F);
    DDX_Text(pDX, IDC_SCALEX, m_parameters->m_tumblescale.x);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblescale.x, .01F, 1000.0F);
    DDX_Text(pDX, IDC_SCALEY, m_parameters->m_tumblescale.y);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblescale.y, .01F, 1000.0F);
    DDX_Text(pDX, IDC_SCALEZ, m_parameters->m_tumblescale.z);
    DDV_MinMaxFloat(pDX, m_parameters->m_tumblescale.z, .01F, 1000.0F);

    //{{AFX_DATA_MAP(CDupDialog)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDupDialog, CDialog)
    //{{AFX_MSG_MAP(CDupDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDupDialog message handlers
BOOL CDupDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    return FALSE;
}

void CDupDialog::OnOK() {
    CPluginDialog::OnOK();
    SetRegistryValue("Duplicator HXT", "TranslateX", m_parameters->m_translate.x);
    SetRegistryValue("Duplicator HXT", "TranslateY", m_parameters->m_translate.y);
    SetRegistryValue("Duplicator HXT", "TranslateZ", m_parameters->m_translate.z);
    SetRegistryValue("Duplicator HXT", "RotateX", m_parameters->m_sweeprotate.x);
    SetRegistryValue("Duplicator HXT", "RotateY", m_parameters->m_sweeprotate.y);
    SetRegistryValue("Duplicator HXT", "RotateZ", m_parameters->m_sweeprotate.z);
    SetRegistryValue("Duplicator HXT", "OffsetDistToCenter", m_parameters->m_offsetdisttocenter);
    SetRegistryValue("Duplicator HXT", "StopAtDist", m_parameters->m_stopatdist);
    SetRegistryValue("Duplicator HXT", "Repeat", m_parameters->m_repeat);
    SetRegistryValue("Duplicator HXT", "IsExtrude", m_parameters->m_isextrude);
    SetRegistryValue("Duplicator HXT", "TumbleRotateX", m_parameters->m_tumblerotate.x);
    SetRegistryValue("Duplicator HXT", "TumbleRotateY", m_parameters->m_tumblerotate.y);
    SetRegistryValue("Duplicator HXT", "TumbleRotateZ", m_parameters->m_tumblerotate.z);
    SetRegistryValue("Duplicator HXT", "TumblePivotX", m_parameters->m_tumblepivotoffset.x);
    SetRegistryValue("Duplicator HXT", "TumblePivotY", m_parameters->m_tumblepivotoffset.y);
    SetRegistryValue("Duplicator HXT", "TumblePivotZ", m_parameters->m_tumblepivotoffset.z);
    SetRegistryValue("Duplicator HXT", "TumbleScaleX", m_parameters->m_tumblescale.x);
    SetRegistryValue("Duplicator HXT", "TumbleScaleY", m_parameters->m_tumblescale.y);
    SetRegistryValue("Duplicator HXT", "TumbleScaleZ", m_parameters->m_tumblescale.z);
}
