#pragma once

//#include "StdAfx.h"
//#include "F_Protos.h"
//#include "SDK/Misc.h"

// CExportXformsDialog dialog

class CExportXformsDialog final : public CPluginDialog {
public:
    CExportXformsDialog(CWnd *pParent = nullptr); // standard constructor
    CExportXformsDialog(const String &filename);
    ~CExportXformsDialog() override;

    enum {
        IDD = IDD_EXPORTXFORMSDIALOG
    };

    //String m_filename;
    int start_frame;
    int end_frame;
    String m_filename;

protected: // Don't touch these
    void DoDataExchange(CDataExchange *pDX) override;
    BOOL OnInitDialog() override;
    afx_msg void OnBrowse();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    void UpdateTimecode(int src, int trg) const;
    void UpdateStartTimecode();
    void UpdateEndTimecode();
};
