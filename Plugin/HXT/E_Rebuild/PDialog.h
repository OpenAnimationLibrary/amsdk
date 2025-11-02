#if !defined(AFX_PDIALOG_H__DD55413E_89AD_472C_852B_D87500220DC0__INCLUDED_)
#define AFX_PDIALOG_H__DD55413E_89AD_472C_852B_D87500220DC0__INCLUDED_

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
    PParameter *m_para{};
    PDialog() noexcept = default;
    explicit PDialog(PParameter *parameters);
    void Update();

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG1 };

    BOOL m_groups{};
    BOOL m_strict{};
    BOOL m_forceextrude{};
    int m_maxpatch{};
    float m_scale{};
    float m_extrude{};
    BOOL m_reverse{};
    BOOL m_randomextrude{};
    float m_near{};
    float m_minscale{};
    float m_maxscale{};
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
    BOOL OnInitDialog() override;
    afx_msg void OnCheck1();
    void OnOK() override;
    afx_msg void OnCheck3();
    afx_msg void OnCheck5();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__DD55413E_89AD_472C_852B_D87500220DC0__INCLUDED_
