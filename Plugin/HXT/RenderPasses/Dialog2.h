#if !defined(AFX_DIALOG2_H__B0142178_535D_4538_A0FB_83DB4278837F__INCLUDED_)
#define AFX_DIALOG2_H__B0142178_535D_4538_A0FB_83DB4278837F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog2.h : Header-Datei
//
#include "RenderPasses.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dialog2 

class Dialog2 final : public CDialog {
    // Konstruktion
public:
    PARAMETER *m_para{};
    Dialog2() = default;
    explicit Dialog2(PARAMETER *para);
    void Change() const;
    void Change1() const;
    void Change2() const;
    void SetID() const;

    COLORREF diffuse{}, ambience{}, specular{};
    int radiostate{};

    // Dialogfelddaten
    //{{AFX_DATA(Dialog2)
    enum { IDD = IDD_DIALOG2 };

    float m_edit1{};
    float m_edit2{};
    float m_edit3{};
    float m_edit4{};
    BOOL m_diffuse_color{};
    BOOL m_ambience_color{};
    BOOL m_ambience_intensity{};
    BOOL m_specular_color{};
    BOOL m_specular_intensity{};
    BOOL m_reflection_intensity{};
    BOOL m_decal_intensity{};
    BOOL m_decal_all{};
    BOOL m_specular_size{};
    float m_edit5{};
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(Dialog2)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:
    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(Dialog2)
    BOOL OnInitDialog() override;
    afx_msg void OnCheck1();
    afx_msg void OnCheck2();
    afx_msg void OnCheck3();
    afx_msg void OnCheck4();
    afx_msg void OnCheck5();
    afx_msg void OnCheck6();
    afx_msg void OnCheck7();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnRadio5();
    afx_msg void OnButton1();
    afx_msg void OnButton2();
    afx_msg void OnButton3();
    void OnOK() override;
    afx_msg void OnCheck9();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOG2_H__B0142178_535D_4538_A0FB_83DB4278837F__INCLUDED_
