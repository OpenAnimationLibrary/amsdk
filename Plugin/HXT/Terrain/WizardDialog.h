// KB  2/1/00  \Ken85\Plugin\Wizards\Grid\WizardDialog.h

#ifndef __WIZARDDIALOG_H
#define __WIZARDDIALOG_H
// WizardDialog.h : header file
//
#include "Wizard.h"
#include "SDK/Misc.h"
#include "resource.h"

#define MAXX 50
#define MAXY 50
#define MAXZ 2

/////////////////////////////////////////////////////////////////////////////
// CWizardDialog dialog

class CWizardDialog final : public CPluginDialog {
    // Construction
public:
    WizardParameters *m_parameters{};
    short m_noiz_tbl[MAXX][MAXY][MAXZ];

    CWizardDialog() noexcept = default; // standard constructor
    ~CWizardDialog() override {
        DeleteObject(m_hbitmap);
    }
    explicit CWizardDialog(WizardParameters *parameters);

    float Noise(const Vector &p) const;
    float SNoise(const Vector &p) const;
    [[nodiscard]] float getDisplacement(int x, int y) const;

    // Dialog Data
    //{{AFX_DATA(CWizardDialog)
    enum { IDD = IDD_WIZARD };

    CSliderCtrl m_greyctrl;
    CComboBox m_filtertype;
    CComboBox m_noisetype;
    float m_height{0.F};
    float m_stepheight{0.F};
    float m_stepwidth{0.F};
    float m_width{0.F};
    float m_scale{0.F};
    int m_grey{0};
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWizardDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

    // Implementation
    BITMAPINFO m_bitmap{};
    BYTE m_bits[200][200][3]{};
    HBITMAP m_hbitmap{};
    bool m_createdbitmap{};
    void InitNoiseTable();
    float fBm(const Vector &p, float oct, float lac, float gain) const;
    [[nodiscard]] float sineN(const Vector &p, float oct, float lac, float gain) const;
    [[nodiscard]] float Ripples(const Vector &p, float oct, float lac, float gain) const;
    float fBmM(const Vector &p, float oct, float lac, float gain) const;
    [[nodiscard]] float turbulence(const Vector &p, float oct, float lac, float gain) const;
    [[nodiscard]] float turbulenceM(const Vector &p, float oct, float lac, float gain) const;
    [[nodiscard]] float turbulenceM2(const Vector &p, float oct, float lac, float gain) const;
    void filterMountain();
    void filterKernal(int type);
    void filterErode();
    void filterDilate();
    void filterNoise();
    void filterScale(float scalar);
    void PaintSplodge(int x, int y);
    void PaintRaise(int x, int y);
    void PaintLower(int x, int y);

    void filterWeather();

    float m_octaves{};
    float m_gain{};
    float m_lacunarity{};
    float m_smoothfrom{};
    float m_smoothto{};
    BOOL m_invert{};
    int m_seed{};
    int m_paintmode{};
    float m_bitsmall[3][3]{};
    RECT m_imagerect{};
    bool m_painting{};
    // Generated message map functions
    //{{AFX_MSG(CWizardDialog)
    void OnOK() override;
    void OnCancel() override;
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnRendernoise();
    afx_msg void OnKillfocusScale();
    afx_msg void OnKillfocusGain();
    afx_msg void OnInvert();
    afx_msg void OnKillfocusLacunarity();
    afx_msg void OnKillfocusOctaves();
    afx_msg void OnKillfocusSmoothFrom();
    afx_msg void OnKillfocusSmoothTo();
    BOOL OnInitDialog() override;
    afx_msg void OnFilter();
    afx_msg void OnLoad();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnKillfocusSeed();
    afx_msg void OnPaint();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnReleasedcaptureGreyValue(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnFill();
    afx_msg void OnRendershaped();
    afx_msg void OnLower();
    afx_msg void OnModePaint();
    afx_msg void OnRaise();
    afx_msg void OnVScroll(UINT, UINT, CScrollBar *);
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
#endif //WIZARDDIALOG_H
