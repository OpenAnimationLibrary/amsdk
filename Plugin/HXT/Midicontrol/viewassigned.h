#if !defined(AFX_VIEWASSIGNED_H__4CE52D68_B81D_4FBB_8768_E238F70D76FB__INCLUDED_)
#define AFX_VIEWASSIGNED_H__4CE52D68_B81D_4FBB_8768_E238F70D76FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// viewassigned.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld viewassigned 

class viewassigned final : public CPluginDialog {
    // Konstruktion
public:
    PARAMETER *m_para{};
    viewassigned() = default;
    viewassigned(PARAMETER *para);

    // Dialogfelddaten
    //{{AFX_DATA(viewassigned)
    enum { IDD = IDD_DIALOG4 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(viewassigned)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(viewassigned)
    BOOL OnInitDialog() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_VIEWASSIGNED_H__4CE52D68_B81D_4FBB_8768_E238F70D76FB__INCLUDED_
