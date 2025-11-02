#if !defined(AFX_MIDIDEVICE_H__077107D6_E6E1_48A5_A94B_054332874C30__INCLUDED_)
#define AFX_MIDIDEVICE_H__077107D6_E6E1_48A5_A94B_054332874C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mididevice.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Mididevice 

class Mididevice final : public CPluginDialog {
    // Konstruktion
public:
    PARAMETER *m_para{};
    Mididevice() = default;
    Mididevice(PARAMETER *para);

    // Dialogfelddaten
    //{{AFX_DATA(Mididevice)
    enum { IDD = IDD_DIALOG1 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(Mididevice)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(Mididevice)
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_MIDIDEVICE_H__077107D6_E6E1_48A5_A94B_054332874C30__INCLUDED_
