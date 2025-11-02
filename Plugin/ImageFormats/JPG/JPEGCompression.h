#pragma once
#include "afxwin.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// JPEGCompression dialog

class JPEGCompression final : public CPluginDialog {
    DECLARE_DYNAMIC(JPEGCompression)
    // Construction
public:
    enum { IDD = IDD_COMPRESSION };

    int m_compression;
    int m_optimal;

    CSliderCtrl m_quality;
    CEdit m_percentedit;

    JPEGCompression(CWnd *pParent = nullptr); // standard constructor

    // Dialog Data

    // Overrides
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support

    // Implementation
    afx_msg void OnChangePercent();
    BOOL OnInitDialog() override;
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);

    DECLARE_MESSAGE_MAP()
};
