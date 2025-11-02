#if !defined(AFX_PDIALOG_H__557A0A85_F0C0_4A19_BCF7_DAD7C0281CF8__INCLUDED_)
#define AFX_PDIALOG_H__557A0A85_F0C0_4A19_BCF7_DAD7C0281CF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Amplitude.h"
#include "SpectrumGraph.h"
#include "BandDlg.h"

// ImportDlg-Dialogfeld
class ImportDlg final : public CPluginDialog {
public:
    ImportDlg() noexcept = default;
    explicit ImportDlg(Parameter &para);
    ~ImportDlg() override;

    void WaveLoaded(BOOL load_success = FALSE);
    void UpdateTiming() const;
    void UpdateDisplay();
    void UpdateWaveform() const;
    void Visualize();

    Parameter *dlg_para{};
    int timing{};
    int repeat{};
    float min_valuef{}, max_valuef{};
    int min_valuei{}, max_valuei{};
    BOOL isplaying{};
    CFrequencyGraph m_graph_left;
    CFrequencyGraph m_graph_right;
    // Dialogfelddaten
    enum {
        IDD = IDD_DIALOG1
    };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung

    BOOL OnInitDialog() override;
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnEnKillfocusEdit2();
    afx_msg void OnEnKillfocusEdit3();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
};

#endif // AFX_PDIALOG_H__557A0A85_F0C0_4A19_BCF7_DAD7C0281CF8__INCLUDED_
