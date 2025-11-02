#if !defined(AFX_PDIALOG_H__557A0A85_F0C0_4A19_BCF7_DAD7C0281CF8__INCLUDED_)
#define AFX_PDIALOG_H__557A0A85_F0C0_4A19_BCF7_DAD7C0281CF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//
#include "Midi.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PDialog 
struct MidiNote {
    CString note{};
    float freq{};
};

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    Parameter *m_parameters{};
    PDialog() noexcept = default;
    explicit PDialog(Parameter *parameters);
    //    MidiNote *midinote;
    MidiNote midinote[128];
    BOOL Init();
    void UpdatePage() const;

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG2 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
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
    afx_msg void OnSelchangeCombo2();
    afx_msg void OnSelchangeCombo3();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnButton2();
    afx_msg void OnSelchangeCombo1();
    void OnOK() override;
    afx_msg void OnCheck2();
    afx_msg void OnRadio4();
    afx_msg void OnRadio5();
    afx_msg void OnRadio3();
    afx_msg void OnRadio6();
    afx_msg void OnButton3();
    afx_msg void OnCheck3();
    afx_msg void OnCheck4();
    afx_msg void OnCheck5();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__557A0A85_F0C0_4A19_BCF7_DAD7C0281CF8__INCLUDED_
