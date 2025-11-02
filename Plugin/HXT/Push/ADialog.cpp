// ADialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Push.h"
#include "ADialog.h"

// ADialog dialog

//IMPLEMENT_DYNAMIC(ADialog, CDialog)

ADialog::ADialog(PARAMETER *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    mp = para;
}

ADialog::~ADialog() = default;

void ADialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, mp->distance[0]);
    DDV_MinMaxFloat(pDX, mp->distance[0], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT2, mp->frame[0]);
    DDV_MinMaxInt(pDX, mp->frame[0], 0, 10000);
}

BEGIN_MESSAGE_MAP(ADialog, CDialog)END_MESSAGE_MAP()

// ADialog message handlers
