#if !defined(AFX_NDIALOG_H__F1205173_6E2B_497F_97F4_392DC551DAA7__INCLUDED_)
#define AFX_NDIALOG_H__F1205173_6E2B_497F_97F4_392DC551DAA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld NDialog 

class NDialog final : public CPluginDialog {
    // Konstruktion
public:
    Parameter *m_parameters{};
    NDialog() = default;
    explicit NDialog(Parameter *parameters);

    BOOL GetMidiFrameEvents();
    CString mnote[128]{};

    // Dialogfelddaten
    //{{AFX_DATA(NDialog)
    enum { IDD = IDD_DIALOG3 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(NDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(NDialog)
    BOOL OnInitDialog() override;
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_NDIALOG_H__F1205173_6E2B_497F_97F4_392DC551DAA7__INCLUDED_
