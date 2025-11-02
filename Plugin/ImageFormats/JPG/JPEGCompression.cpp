// JPEGCompression.cpp : implementation file
//

#include "StdAfx.h"
#include "ImageIO.h"
#include "resource.h"
#include "Custom.h"
#include "JPEGCompression.h"

/////////////////////////////////////////////////////////////////////////////
// JPEGCompression dialog

IMPLEMENT_DYNAMIC(JPEGCompression, CPluginDialog)

JPEGCompression::JPEGCompression(CWnd *pParent) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), m_compression{0}, m_optimal{0} {
    //{{AFX_DATA_INIT(JPEGCompression)
    //}}AFX_DATA_INIT
}

void JPEGCompression::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(JPEGCompression)
    DDX_Control(pDX, IDC_QUALITY, m_quality);
    DDX_Control(pDX, IDC_PERCENT, m_percentedit);
    DDX_Check(pDX, IDC_CHECKOPT, m_optimal);
    //}}AFX_DATA_MAP
    if (pDX->m_bSaveAndValidate) {
        m_compression = m_quality.GetPos();
    }
}

BEGIN_MESSAGE_MAP(JPEGCompression, CPluginDialog)
    //{{AFX_MSG_MAP(JPEGCompression)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_PERCENT, &JPEGCompression::OnChangePercent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JPEGCompression message handlers
/*
int atoi_replacedlg(const char *buf) {
    return (int)strtol(buf, (char **)nullptr, 10);
}
*/
void JPEGCompression::OnChangePercent() {
    char buf[256];
    m_percentedit.GetWindowText(buf, 255);
    m_compression = atoi_replace(buf);
    if (m_compression < 1 || m_compression > 100) {
        m_compression = MAX(MIN(m_compression, 100), 1);
        sprintf_s(buf, 256, "%d", m_compression);
        m_percentedit.SetWindowText(buf);
        m_percentedit.Invalidate();
    }
    m_quality.SetPos(m_compression);
    m_quality.Invalidate();
}

BOOL JPEGCompression::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    //   m_quality.SetBuddy( &m_percentedit, false );
    char buf[256];
    m_quality.SetRange(1, 100, TRUE);
    m_quality.SetTicFreq(10);
    m_quality.SetPos(m_compression);
    sprintf_s(buf, 256, "%d", m_compression);
    m_percentedit.SetWindowText(buf);
    return TRUE;
}

void JPEGCompression::OnHScroll(const UINT nSBCode, const UINT nPos, CScrollBar *pScrollBar) {
    char buf[256];
    m_compression = m_quality.GetPos();
    sprintf_s(buf, 256, "%d", m_compression);
    m_percentedit.SetWindowText(buf);
    m_percentedit.Invalidate();
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
