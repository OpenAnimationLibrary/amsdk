// TimeLog.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "TimeLog.h"
#include "TimerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeLogApp

BEGIN_MESSAGE_MAP(CTimeLogApp, CWinApp)
        //{{AFX_MSG_MAP(CTimeLogApp)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeLogApp Konstruktion

CTimeLogApp::CTimeLogApp(): m_timerdialog{nullptr},
                            m_projectproperties_info{nullptr},
                            m_uselog_info{nullptr},
                            m_overridethreshold_info{nullptr},
                            m_treshold_info{nullptr},
                            m_savetime_info{nullptr},
                            m_logfile_info{nullptr},
                            m_projectproperties_index{0},
                            m_uselog_index{0},
                            m_overridethreshold_index{0},
                            m_treshold_index{0},
                            m_savetime_index{0},
                            m_logfile_index{0} {
    thresholdtime = 300;
    savetime = 1800;
    filename = "";
    logging = false;
    endload = false;
    overridethreshold = false;
}

CTimeLogApp::~CTimeLogApp() {
    if (m_timerdialog) {
        if (logging)
            m_timerdialog->SaveLog(true);
        if (m_timerdialog->m_hWnd)
            m_timerdialog->DestroyWindow();
        delete m_timerdialog;
        m_timerdialog = nullptr;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CTimeLogApp-Objekt

CTimeLogApp theApp;

void CTimeLogApp::OnSelectionChanged() const {
    if (logging) {
        if (m_timerdialog)
            m_timerdialog->SetActiveSeconds();
    }
}

void CTimeLogApp::StartDialog() {
    if (!m_timerdialog) {
        CWnd *hwnd = CWnd::FromHandle(GetMainApplicationWnd());
        m_timerdialog = new TimerDialog;
        m_timerdialog->Create(TimerDialog::IDD, nullptr);
        hwnd->SetFocus();
        m_timerdialog->StartTimer(thresholdtime, savetime);
        m_timerdialog->SetLogState(logging);
        m_timerdialog->SetOverrideState(overridethreshold);
        m_timerdialog->SetValues(filename, GetHProject()->GetFileName(), endload);
    } else {
        m_timerdialog->StartTimer(thresholdtime, savetime);
        m_timerdialog->SetLogState(logging);
        m_timerdialog->SetOverrideState(overridethreshold);
        m_timerdialog->SetValues(filename, GetHProject()->GetFileName(), true);
    }
}

void CTimeLogApp::StopDialog() {
    if (m_timerdialog) {
        if (logging)
            m_timerdialog->SaveLog(true);
        if (m_timerdialog->m_hWnd)
            m_timerdialog->DestroyWindow();

        delete m_timerdialog;
        m_timerdialog = nullptr;
    }
}

LRESULT CTimeLogApp::OnProjectPropertiesMessage(HProject *project, const PtrMessage ptrmessage, const LONG_PTR lparam, Time time) {
    switch (ptrmessage) {
        case PTM_PROJECTCLOSE:
        {
            StopDialog();
            return false;
        }
        case PTM_ENDLOAD:
        {
            if (logging)
                StartDialog();
            else
                StopDialog();
            endload = true;
            return false;
        }
        case PTM_VALUESTORED:
        case PTM_VALUECHANGED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            const HPropertyInfo *dueto_info = dueto->GetPropertyInfo();
            if (dueto_info == m_overridethreshold_info) {
                auto *myproperties = (HCategoryProperty *)project->GetPluginProperties()->GetPropertyAt(m_projectproperties_index);
                const HBoolProperty *mybool = (HBoolProperty *)myproperties->GetPropertyAt(m_overridethreshold_index);
                overridethreshold = mybool->GetValue() != 0;
                if (m_timerdialog && endload)
                    m_timerdialog->SetOverrideState(overridethreshold);
                return true;
            }
            if (dueto_info == m_uselog_info) {
                auto *myproperties = (HCategoryProperty *)project->GetPluginProperties()->GetPropertyAt(m_projectproperties_index);
                const HBoolProperty *mybool = (HBoolProperty *)myproperties->GetPropertyAt(m_uselog_index);
                const HBoolProperty *mybool1 = (HBoolProperty *)myproperties->GetPropertyAt(m_overridethreshold_index);
                const HFilenameProperty *mystring = (HFilenameProperty *)myproperties->GetPropertyAt(m_logfile_index);
                const HStringProperty *mytreshold = (HStringProperty *)myproperties->GetPropertyAt(m_treshold_index);
                const HStringProperty *mysavetime = (HStringProperty *)myproperties->GetPropertyAt(m_savetime_index);
                if (mybool->GetValue()) {
                    logging = true;
                    mystring->Show(true);
                    mybool1->Show(true);
                    mytreshold->Show(true);
                    mysavetime->Show(true);
                    if (endload) {
                        StartDialog();
                    }
                    //					if ((endload) && (m_timerdialog)) 
                    //                  m_timerdialog->SetLogState(logging);
                } else {
                    logging = false;
                    mystring->Show(false);
                    mybool1->Show(false);
                    mytreshold->Show(false);
                    mysavetime->Show(false);
                    if (endload) {
                        StopDialog();
                    }
                    //					if ((endload) && (m_timerdialog))
                    //                  m_timerdialog->SetLogState(logging);
                }
                return true;
            }
            if (dueto_info == m_treshold_info) {
                auto *myproperties = (HCategoryProperty *)project->GetPluginProperties()->GetPropertyAt(m_projectproperties_index);
                auto *mytreshold = (HStringProperty *)myproperties->GetPropertyAt(m_treshold_index);
                String stringvalue = mytreshold->GetValue();
                UINT datavalue;
                char *stopstring;
                if (stringvalue.IsEmpty()) {
                    stringvalue = "5";
                    datavalue = 5;
                    mytreshold->SetValue(stringvalue.Get());
                } else {
                    datavalue = strtoul(stringvalue.Get(), &stopstring, 10);
                    if (datavalue < 1) {
                        datavalue = 1;
                        const String temp(datavalue);
                        mytreshold->SetValue(temp.Get());
                    } else {
                        if (datavalue > 60) {
                            datavalue = 60;
                            const String temp(datavalue);
                            mytreshold->SetValue(temp.Get());
                        } else {
                            const String temp(datavalue); //remove leading Nulls
                            mytreshold->SetValue(temp.Get());
                        }
                    }
                }
                thresholdtime = datavalue * 60;
                if (endload && m_timerdialog)
                    m_timerdialog->StartTimer(thresholdtime, savetime);
                return true;
            }
            if (dueto_info == m_savetime_info) {
                auto *myproperties = (HCategoryProperty *)project->GetPluginProperties()->GetPropertyAt(m_projectproperties_index);
                auto *mysavetime = (HStringProperty *)myproperties->GetPropertyAt(m_savetime_index);
                String stringvalue = mysavetime->GetValue();
                UINT datavalue;
                char *stopstring;
                if (stringvalue.IsEmpty()) {
                    stringvalue = "30";
                    datavalue = 30;
                    mysavetime->SetValue(stringvalue.Get());
                } else {
                    datavalue = strtoul(stringvalue.Get(), &stopstring, 10);
                    if (datavalue < 5) {
                        datavalue = 5;
                        const String temp(datavalue);
                        mysavetime->SetValue(temp.Get());
                    } else {
                        if (datavalue > 1440) {
                            datavalue = 1440;
                            const String temp(datavalue);
                            mysavetime->SetValue(temp.Get());
                        } else {
                            const String temp(datavalue); //remove leading Nulls
                            mysavetime->SetValue(temp.Get());
                        }
                    }
                }
                savetime = datavalue * 60;
                if (endload && m_timerdialog)
                    m_timerdialog->StartTimer(thresholdtime, savetime);
                return true;
            }
            if (dueto_info == m_logfile_info) {
                auto *myproperties = (HCategoryProperty *)project->GetPluginProperties()->GetPropertyAt(m_projectproperties_index);
                auto *mystring = (HFilenameProperty *)myproperties->GetPropertyAt(m_logfile_index);
                String name = mystring->GetValue();
                if (name.IsEmpty()) {
                    name = String::GetMyDocumentsPath() + "\\AM\\TimeLog.csv";
                    //					name = String::GetAppPath()+"\\TimeLog.csv";
                    mystring->SetValue(name.Get());
                    filename = name;
                } else {
                    if (name != filename) {
                        filename = name;
                    }
                    if (endload && m_timerdialog) {
                        m_timerdialog->SetValues(filename, GetHProject()->GetFileName(), endload);
                    }
                }
                return true;
            }
        }
            break;
        default: ;
    }
    return false;
}

BOOL CTimeLogApp::AddProjectProperties(const HProject *hproject, HCategoryProperty *pluginproperties) {
    if (!hproject)
        return false;
    endload = false;
    HCategoryProperty *myprojectproperties = HCategoryProperty::New(m_projectproperties_info);
    m_projectproperties_index = pluginproperties->AddProperty(myprojectproperties);

    HBoolProperty *myuselog = HBoolProperty::New(m_uselog_info);
    m_uselog_index = myprojectproperties->AddProperty(myuselog);

    HBoolProperty *myoverride = HBoolProperty::New(m_overridethreshold_info);
    m_overridethreshold_index = myprojectproperties->AddProperty(myoverride);
    myoverride->Show(false);

    HStringProperty *mytreshold = HStringProperty::New(m_treshold_info);
    m_treshold_index = myprojectproperties->AddProperty(mytreshold);
    mytreshold->Show(false);

    HStringProperty *mysavetime = HStringProperty::New(m_savetime_info);
    m_savetime_index = myprojectproperties->AddProperty(mysavetime);
    mysavetime->Show(false);

    HFilenameProperty *mylog = HFilenameProperty::New(m_logfile_info);
    m_logfile_index = myprojectproperties->AddProperty(mylog);
    mylog->Show(false);
    return true;
}

void CTimeLogApp::AllocPropertyInfos() {
    m_projectproperties_info = HPropertyInfo::New("TimeLog", "TimeLogProject");
    m_projectproperties_info->SetReadOnly(TRUE);
    m_projectproperties_info->SetConstant(TRUE);

    m_uselog_info = HBoolPropertyInfo::New("Enable Logging", "TimeLogUse");
    m_uselog_info->SetDefaultValue(FALSE);
    m_uselog_info->SetConstant(TRUE);

    m_overridethreshold_info = HBoolPropertyInfo::New("Override Threshold while rendering", "TimeLogOveride");
    m_overridethreshold_info->SetDefaultValue(FALSE);
    m_overridethreshold_info->SetConstant(TRUE);

    m_treshold_info = HStringPropertyInfo::New("Threshold time", "TimeLogThreshold");
    m_treshold_info->SetConstant(TRUE);
    m_treshold_info->SetDefaultValue("5");
    m_treshold_info->SetIllegalChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW,.-;:_!()=?}][{><|@&%$\"*+#~`");
    m_treshold_info->SetVisibleWhen(HPropertyInfo::VISIBLESOMETIMES);

    m_savetime_info = HStringPropertyInfo::New("Save log every", "TimeLogSaveTime");
    m_savetime_info->SetConstant(TRUE);
    m_savetime_info->SetDefaultValue("30");
    m_savetime_info->SetIllegalChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW,.-;:_!()=?}][{><|@&%$\"*+#~`");
    m_savetime_info->SetVisibleWhen(HPropertyInfo::VISIBLESOMETIMES);

    m_logfile_info = HFilenamePropertyInfo::New("Logfile", "TimeLogFile");
    const String name = String::GetMyDocumentsPath() + "\\AM\\TimeLog.csv";
    filename = name;
    m_logfile_info->SetDefaultValue(name.Get());
    m_logfile_info->SetDefaultExtension("csv");
    m_logfile_info->SetFileDialogTitle("Save Logfile as");
    m_logfile_info->SetFileDialogFilter("CSV (*.csv)|*.csv|TEXT|Text (*.txt)|*.txt|TEXT||");
    m_logfile_info->SetIsPromptForMissingFileOnLoad(false);
    m_logfile_info->SetConstant(true);
    m_logfile_info->SetIsOpenDialog(false);
    m_logfile_info->SetVisibleWhen(HPropertyInfo::VISIBLESOMETIMES);
}

void CTimeLogApp::FreePropertyInfos() const {
    delete m_projectproperties_info;
    delete m_uselog_info;
    delete m_overridethreshold_info;
    delete m_treshold_info;
    delete m_savetime_info;
    delete m_logfile_info;
}

BOOL CTimeLogApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    AllocPropertyInfos();
    return CPluginApp::InitInstance();
}

int CTimeLogApp::ExitInstance() {
    FreePropertyInfos();
    return CPluginApp::ExitInstance();
}
