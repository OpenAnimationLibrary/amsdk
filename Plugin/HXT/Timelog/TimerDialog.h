#pragma once

// TimerDialog-Dialogfeld

class TimerDialog final : public CPluginDialog {

public:
    TimerDialog();
    ~TimerDialog() override;
    void StartTimer(UINT threshold, UINT save);
    void StopTimer();
    void SetValues(const String &_filename, const String &_projectname, bool endload);
    void SetLogState(bool logging_enabled);
    void SetOverrideState(bool override_enabled);
    void SetActiveSeconds();
    void SaveLog(bool lastsave);
    String GetLastLine(float &duration, int &oldlength) const;
    [[nodiscard]] bool IsRendering() const;

    UINT_PTR thresholdtimer_id, savetimer_id;
    UINT threshold_time, save_time;
    String filename, projectname;
    time_t start_time{}, end_time;
    float start_sec, active_second, threshold_second;
    bool logstate, active, m_override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung

    //{{AFX_MSG(Record)
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
