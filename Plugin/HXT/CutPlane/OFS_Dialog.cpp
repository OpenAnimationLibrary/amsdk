// OFS_Dialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "CutPlane.h"
#include "OFS_Dialog.h"

OFS_Dialog::OFS_Dialog(CWnd *pParent /*=nullptr*/) : CPluginDialog(IDD, pParent) {}

OFS_Dialog::~OFS_Dialog() = default;

void OFS_Dialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, theApp.plane.offset);
    DDV_MinMaxFloat(pDX, theApp.plane.offset, 0.F, 10000.F);
}

BEGIN_MESSAGE_MAP(OFS_Dialog, CDialog)
END_MESSAGE_MAP()

// OFS_Dialog-Meldungshandler
