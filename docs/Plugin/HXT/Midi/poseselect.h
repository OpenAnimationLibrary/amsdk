#if !defined(AFX_POSESELECT_H__F556C0C6_AB51_476C_B614_1FF7F827D9FE__INCLUDED_)
#define AFX_POSESELECT_H__F556C0C6_AB51_476C_B614_1FF7F827D9FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// poseselect.h : Header-Datei
//
#include "Midi.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld poseselect 

class poseselect final : public CPluginDialog {
    // Konstruktion
public:
    Parameter *m_parameters{};
    poseselect() = default;
    poseselect(Parameter *parameters);

    // Dialogfelddaten
    //{{AFX_DATA(poseselect)
    enum { IDD = IDD_DIALOG1 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(poseselect)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(poseselect)
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_POSESELECT_H__F556C0C6_AB51_476C_B614_1FF7F827D9FE__INCLUDED_
