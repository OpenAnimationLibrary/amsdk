// TimerDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "TimeLog.h"
#include "TimerDialog.h"

TimerDialog::TimerDialog() : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), end_time{0}, active_second{0}, threshold_second{0}, active{false} {
    thresholdtimer_id = (UINT_PTR)-1;
    savetimer_id = (UINT_PTR)-1;
    threshold_time = 0;
    save_time = 0;
    filename = "";
    projectname = "";
    logstate = false;
    m_override = false;
    time(&start_time);
    start_sec = GetClockTicks();
}

TimerDialog::~TimerDialog() = default;

String TimerDialog::GetLastLine(float &duration, int &oldlength) const {
    CFile file;
    CFileException fileexception;

    String lastline = "";
    if (!file.Open(filename.Get(), CFile::modeRead, &fileexception)) {
        duration = 0;
        oldlength = 0;
        return lastline;
    }
    BOOL fileend;
    CString inputline1, inputline2;
    char *stopstring;
    CArchive arLoad(&file, CArchive::load);
    do {
        inputline2 = inputline1;
        fileend = arLoad.ReadString(inputline1);
    } while (fileend);
    file.Close();
    lastline = inputline2;
    oldlength = lastline.GetLength() + 1;
    lastline = lastline.GetWithoutCRLFs();
    const String sep1 = ",";
    const String sep2 = "\n";
    const String temp = lastline.StrTok(sep1);
    const String temp1 = lastline.StrTok(sep1);
    const String temp3 = lastline.StrTok(sep2);
    if (!temp3.IsEmpty()) {
        duration = (float)strtoul(temp3.Get(), &stopstring, 10);
    } else {
        duration = 0;
    }
    lastline = temp + "," + temp1;
    return lastline;
}

void TimerDialog::SaveLog(const bool lastsave) {

    if (!active && !lastsave)
        return;
    float oldduration = 0;
    int laststringlength = 0;

    const String lastline = GetLastLine(oldduration, laststringlength);
    const float end_sec = GetClockTicks();
    float duration = (end_sec - start_sec) / 60.F;
    if (!active && lastsave)
        duration = 0;
    constexpr int buf_size = 26;
    char buf[buf_size];
    ctime_s(buf, buf_size, &start_time);
    String temp1 = buf;
    time(&end_time);
    memset(buf, 0, buf_size);
    ctime_s(buf, buf_size, &end_time);
    String temp2 = buf;
    temp1.RemoveAll("\n");
    temp2.RemoveAll("\n");
    String savestring = projectname + "," + temp1;
    if (savestring == lastline) {
        duration += oldduration;
        const String duration_string(duration);
        savestring = savestring + "," + temp2 + "," + duration_string + "\n";
    } else {
        const String duration_string(duration);
        savestring = savestring + "," + temp2 + "," + duration_string + "\n";
        laststringlength = 0;
    }

    CFileException fileexception;
    if (duration > 0.F || lastsave) {
        CFile file;
        String dir = filename.GetPathOnly();
        dir += "\\";
        if (!DirExists(dir.Get())) {
            MakeDirPath(dir.Get());
        }
        if (!file.Open(filename.Get(), CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate | CFile::modeNoTruncate, &fileexception)) {
            CString text;
            text.LoadString(IDS_FILEOPENERROR);
            String stext = text;
            stext.Replace("%1", filename);
            stext.Replace("%2", fileexception.m_cause);
            AfxMessageBox(stext.Get(), MB_OK | MB_ICONERROR);
            return;
        }

        ULONGLONG pos = file.GetLength();
        if (pos > 0) {
            ULONGLONG pos_neu;
            if (laststringlength != 0) {
                pos_neu = pos - laststringlength;
            } else {
                pos_neu = pos;
            }
            file.Seek(pos_neu, CFile::begin);
            // ReSharper disable once CppAssignedValueIsNeverUsed
            pos = file.GetPosition();
        }
        file.Write(savestring.Get(), savestring.GetLength());
        file.Flush();
        file.Close();
        start_sec = end_sec;
    }
}

void TimerDialog::SetOverrideState(const bool override_enabled) {
    m_override = override_enabled;
}

void TimerDialog::SetLogState(const bool logging_enabled) {
    if (logging_enabled) {
        if (thresholdtimer_id == (UINT_PTR)-1) {
            thresholdtimer_id = SetTimer(IDT_TIMER1, threshold_time, nullptr);
            time(&start_time);
            start_sec = GetClockTicks();
        }
        if (savetimer_id == (UINT_PTR)-1) {
            savetimer_id = SetTimer(IDT_TIMER2, save_time, nullptr);
        }
    } else {
        if (thresholdtimer_id != (UINT_PTR)-1) {
            KillTimer(thresholdtimer_id);
            thresholdtimer_id = (UINT_PTR)-1;
        }
        if (savetimer_id != (UINT_PTR)-1) {
            KillTimer(savetimer_id);
            savetimer_id = (UINT_PTR)-1;
            if (logstate != logging_enabled) {
                SaveLog(false);
            }
        }
    }
    logstate = logging_enabled;
}

void TimerDialog::SetValues(const String &_filename, const String &_projectname, const bool endload) {
    if (!endload) {
        filename = _filename;
        projectname = _projectname;
        return;
    }
    if (projectname != _projectname && filename != _filename) {
        //lastsave
        SaveLog(false);
        projectname = _projectname;
        filename = _filename;
        start_time = end_time;
    } else {
        if (filename != _filename) {
            //lastsave
            SaveLog(false);
            filename = _filename;
            start_time = end_time;
        }
        if (projectname != _projectname) {
            //lastsave
            SaveLog(false);
            projectname = _projectname;
            start_time = end_time;
        }
    }
}

void TimerDialog::StartTimer(const UINT threshold, const UINT save) {
    if (threshold_time != threshold) {
        threshold_time = threshold * 1000;
        threshold_second = (float)threshold;
        if (thresholdtimer_id != (UINT_PTR)-1)
            KillTimer(thresholdtimer_id);
        thresholdtimer_id = SetTimer(IDT_TIMER1, threshold_time, nullptr);
    }
    if (save_time != save) {
        save_time = save * 1000;
        if (savetimer_id != (UINT_PTR)-1)
            KillTimer(savetimer_id);
        savetimer_id = SetTimer(IDT_TIMER2, save_time, nullptr);
    }

}

void TimerDialog::StopTimer() {
    if (thresholdtimer_id != (UINT_PTR)-1)
        KillTimer(thresholdtimer_id);
    if (savetimer_id != (UINT_PTR)-1)
        KillTimer(savetimer_id);
}

void TimerDialog::SetActiveSeconds() {
    active_second = GetClockTicks();
    if (!active) {
        time(&start_time);
        start_sec = GetClockTicks();
        if (thresholdtimer_id == (UINT_PTR)-1)
            thresholdtimer_id = SetTimer(IDT_TIMER1, threshold_time, nullptr);
        if (savetimer_id == (UINT_PTR)-1)
            savetimer_id = SetTimer(IDT_TIMER2, save_time, nullptr);
        active = true;
    }
}

void TimerDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
}

bool TimerDialog::IsRendering() const {
    if (!m_override)
        return false;
    CString windowname;
    const CWnd *wnd = FromHandle(GetMainApplicationWnd());
    if (!wnd)
        return false;
    wnd->GetWindowText(windowname);
    return static_cast<bool>(windowname.Find('@', 0) != -1);
}

void TimerDialog::OnTimer(const UINT_PTR nIDEvent) {
    switch (nIDEvent) {
        case IDT_TIMER1:
        {
            const float actual_second = GetClockTicks();
            if (!IsRendering()) {
                if (actual_second - active_second >= threshold_second) {
                    //Stop logging User inactive
                    SaveLog(false);
                    if (thresholdtimer_id != (UINT_PTR)-1) {
                        KillTimer(thresholdtimer_id);
                        thresholdtimer_id = -1;
                    }
                    if (savetimer_id != (UINT_PTR)-1) {
                        KillTimer(savetimer_id);
                        savetimer_id = -1;
                    }
                    active = false;
                }
            }
        }
        break;
        case IDT_TIMER2:
        {
            SaveLog(false);
        }
        break;
        default: ;
    }
}

BEGIN_MESSAGE_MAP(TimerDialog, CDialog)
        ON_WM_TIMER()
END_MESSAGE_MAP()
