// YP  01/05/2005  \Plugin\Image Formats\TGA\CompressionDlg.cpp

#include "StdAfx.h"
#include "resource.h"
#include "ImageIO.h"
#include "CompressionDlg.h"
#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompressionDlg dialog

IMPLEMENT_DYNAMIC(CCompressionDlg, CPluginDialog)

CCompressionDlg::CCompressionDlg(CWnd *pParent) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), m_compression(TRUE) {
    //{{AFX_DATA_INIT(CCompressionDlg)

    //}}AFX_DATA_INIT
}

void CCompressionDlg::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCompressionDlg)
    DDX_Check(pDX, IDC_COMPRESS, m_compression);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompressionDlg, CPluginDialog)
    //{{AFX_MSG_MAP(CCompressionDlg)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressionDlg message handlers
