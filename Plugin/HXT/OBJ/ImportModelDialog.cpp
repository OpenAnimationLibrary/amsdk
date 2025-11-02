// ImportModelDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ImportModelDialog.h"
#include "F_Protos.h"

#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog dialog

CImportModelDialog::CImportModelDialog(): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_peaktolerance = GetRegistryValue("OBJ Plugin", "Peak Tolerance", 45.0F);
    m_oldimportscale = m_importscale = GetRegistryValue("OBJ Plugin", "ImportScale", 1.F);
    m_displayinfo = GetRegistryBOOL("OBJ Plugin", "DisplayInfo", TRUE);
    m_openview = GetRegistryBOOL("OBJ Plugin", "OpenView", FALSE);
    //{{AFX_DATA_INIT(CImportModelDialog)
    //}}AFX_DATA_INIT
}

void CImportModelDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CImportModelDialog)
    DDX_Text(pDX, IDC_PEAKTOLERANCE, m_peaktolerance);
    DDV_MinMaxFloat(pDX, m_peaktolerance, 0.F, 360.F);
    DDX_Text(pDX, IDC_IMPORTSCALE, m_importscale);
    DDV_MinMaxFloat(pDX, m_importscale, 1.F, 10000.F);
    DDX_Check(pDX, IDC_CHECK1, m_displayinfo);
    DDX_Check(pDX, IDC_CHECK2, m_openview);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImportModelDialog, CDialog)
    //{{AFX_MSG_MAP(CImportModelDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog message handlers

void CImportModelDialog::OnOK() {
    UpdateData(true);
    CPluginDialog::OnOK();
    SetRegistryValue("OBJ Plugin", "Peak Tolerance", m_peaktolerance);
    SetRegistryValue("OBJ Plugin", "ImportScale", m_importscale);
    if (m_oldimportscale != m_importscale)
        SetRegistryValue("OBJ Plugin", "ExportScale", hash_math::rcp(m_importscale));
    SetRegistryBOOL("OBJ Plugin", "DisplayInfo", m_displayinfo);
    SetRegistryBOOL("OBJ Plugin", "OpenView", m_openview);
}
