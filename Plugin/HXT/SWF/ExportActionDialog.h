#pragma once

#include "StrClass.h"
#include "NewLabel/NewLabel.h"

class HActionCache;

// ExportActionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportActionDialog dialog

class CExportActionDialog final : public CPluginDialog {
    // Construction
public:
    CExportActionDialog() : m_RegOK(true) {} // standard constructor
    CExportActionDialog(const String &filename, HChor *chor, CHxtApp *app);

    CNewLabel m_style_outline_col;

    // Dialog Data
    IEModelParms *m_iemp{};
    String m_filename;
    HChor *m_chor{};

    //{{AFX_DATA(CExportActionDialog)
    enum { IDD = IDD_EXPORTACTIONDIALOG };

    int m_subtype{};

    int m_style_fill{};
    COLORREF m_style_fill_color{};
    int m_style_outline{};
    int m_style_outline_thickness{};
    COLORREF m_style_outline_color{};
    int m_style_edge{};
    COLORREF m_style_edge_color{};
    float m_style_edgethresh{};

    int m_frame_range{};
    int m_frame_from{};
    int m_frame_to{};
    int m_frame_stepping{};

    String m_camera_name;
    int m_cameraindex{};
    int m_camera_perspective{};
    int m_camera_zero{};

    int m_lights_parallel{};

    int m_culling_mapsize{};
    int m_culling_minarea{};
    BOOL m_culling_occlusion{};
    BOOL m_culling_backface{};

    BOOL m_flat{};
    BOOL m_flat_spec{};
    float m_flat_minedgelength{};

    BOOL m_safe_frame1{};
    BOOL m_safe_all{};

    int m_preview_frame{};
    int m_preview{};

    BOOL m_RegOK;

    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExportActionDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CExportActionDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    afx_msg void OnBrowse();
    afx_msg void OnPreview();
    afx_msg void OnFrameRange();
    afx_msg void OnStyleOutlinePick();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
