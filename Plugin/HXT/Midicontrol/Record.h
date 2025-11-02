#if !defined(AFX_RECORD_H__EE37E369_8A94_4C5B_91D9_90AB6A957FB4__INCLUDED_)
#define AFX_RECORD_H__EE37E369_8A94_4C5B_91D9_90AB6A957FB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Record.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Record 

class Record final : public CPluginDialog {
    // Konstruktion
public:
    PARAMETER *m_para{nullptr};
    UINT_PTR timer_id{0};
    int changed{0}, update_run{0}, force_update{0};
    UINT m_frame{0};
    BOOL m_deletebeforerecord{FALSE};

    Record() = default;
    explicit Record(PARAMETER *para);
    static void CALLBACK CBMidiOpen(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
    void MidiOpenNotify(HMIDIIN midi_in, UINT msg_type, DWORD midi_msg, DWORD param2);
    BOOL StartMidiIn();
    void StopMidiIn() const;
    void DisableAll() const;
    void EnableAll() const;
    void SetFirstFrame(BOOL store) const;
    void CreateChannels() const;
    void DeleteBeforeRecord();

    // Dialogfelddaten
    //{{AFX_DATA(Record)
    enum { IDD = IDD_DIALOG3 };

    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(Record)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(Record)
    BOOL OnInitDialog() override;
    afx_msg void OnButton1();
    afx_msg void OnButton2();
    afx_msg void OnButton3();
    afx_msg void OnButton4();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnClose();
    void OnOK() override;
    void OnCancel() override;
    afx_msg void OnButton6();
    afx_msg void OnChangeEdit1();
    afx_msg void OnCheck1();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RECORD_H__EE37E369_8A94_4C5B_91D9_90AB6A957FB4__INCLUDED_
