#if !defined(AFX_PDIALOG_H__43804CDF_5CC5_4FF0_A7C2_23A82E523C24__INCLUDED_)
#define AFX_PDIALOG_H__43804CDF_5CC5_4FF0_A7C2_23A82E523C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PDialog 

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    Parameter *m_para{};
    PDialog() noexcept = default;
    explicit PDialog(Parameter *parameters);
    void Calculate();

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG1 };

    double m_surface{};
    int m_photoncast{};
    int m_photonsample{};
    float m_samplingarea{};
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(PDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(PDialog)
    afx_msg void OnButton1();
    BOOL OnInitDialog() override;
    void OnOK() override;
    afx_msg void OnButton2();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__43804CDF_5CC5_4FF0_A7C2_23A82E523C24__INCLUDED_
