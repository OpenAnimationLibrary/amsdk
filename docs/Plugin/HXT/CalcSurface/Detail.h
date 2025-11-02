#if !defined(AFX_DETAIL_H__CB048105_5AEE_4645_9EB5_32FD7C2888EB__INCLUDED_)
#define AFX_DETAIL_H__CB048105_5AEE_4645_9EB5_32FD7C2888EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Detail.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDetail 

class CDetail final : public CPluginDialog {
    // Konstruktion
public:
    Parameter *m_para{nullptr};
    CDetail() = default;
    CDetail(Parameter *parameters, HWND pParent);

    // Dialogfelddaten
    //{{AFX_DATA(CDetail)
    enum { IDD = IDD_DIALOG2 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(CDetail)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(CDetail)
    BOOL OnInitDialog() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DETAIL_H__CB048105_5AEE_4645_9EB5_32FD7C2888EB__INCLUDED_
