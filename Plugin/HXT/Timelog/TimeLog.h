// TimeLog.h : Haupt-Header-Datei für die DLL TimeLog
//

#if !defined(AFX_TimeLog_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
#define AFX_TimeLog_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "HashFile.h"
#include "F_Protos.h"
#include "PtrMessa.h"
#include "Files.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "SDK/HProject.h"
#include "TimerDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTimeLogApp
// Siehe TimeLog.cpp für die Implementierung dieser Klasse
//

class HModel;
class HPropertyInfo;

//class CTimeLogApp : public CPluginApp
class CTimeLogApp final : public CPluginApp {
public:
    CTimeLogApp();
    ~CTimeLogApp() override;
    void AllocPropertyInfos();
    void FreePropertyInfos() const;
    LRESULT OnProjectPropertiesMessage(HProject *project, PtrMessage ptrmessage, LONG_PTR lparam, Time time);
    BOOL AddProjectProperties(const HProject *hproject, HCategoryProperty *pluginproperties);
    void OnSelectionChanged() const;
    void StartDialog();
    void StopDialog();

    TimerDialog *m_timerdialog;

    bool endload;
    UINT thresholdtime, savetime;
    bool logging;
    bool overridethreshold;
    String filename;

    //Properties Project
    HPropertyInfo *m_projectproperties_info;
    HBoolPropertyInfo *m_uselog_info;
    HBoolPropertyInfo *m_overridethreshold_info;
    HStringPropertyInfo *m_treshold_info;
    HStringPropertyInfo *m_savetime_info;
    HFilenamePropertyInfo *m_logfile_info;

    int m_projectproperties_index;
    int m_uselog_index;
    int m_overridethreshold_index;
    int m_treshold_index;
    int m_savetime_index;
    int m_logfile_index;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CTimeLogApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CTimeLogApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_TimeLog_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
