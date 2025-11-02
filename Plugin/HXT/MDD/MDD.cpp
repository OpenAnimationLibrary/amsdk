// MDD.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "MDD.h"
#include "ImportDialog.h"
#include "ExportDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDDApp

BEGIN_MESSAGE_MAP(CMDDApp, CWinApp)
        //{{AFX_MSG_MAP(CMDDApp)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDDApp Konstruktion

CMDDApp::CMDDApp() = default;

CMDDApp::~CMDDApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMDDApp-Objekt

CMDDApp theApp;

void CMDDApp::LoadSettings() const {
    parameter->filename = GetRegistryString("MDD HXT", "LastFile", "FileName");
    parameter->fps = GetRegistryValue("MDD HXT", "FPS", GetHProject()->GetFPS());
    parameter->scale = GetRegistryValue("MDD HXT", "Scale", 1.F);
    parameter->tolerance = GetRegistryValue("MDD HXT", "Tolerance", 0.F);
    parameter->subtype = GetRegistryValue("MDD HXT", "SubType", 0);
}

void CMDDApp::SaveSettings() const {
    SetRegistryString("MDD HXT", "LastFile", parameter->filename);
    SetRegistryValue("MDD HXT", "FPS", parameter->fps);
    SetRegistryValue("MDD HXT", "Scale", parameter->scale);
    SetRegistryValue("MDD HXT", "Tolerance", parameter->tolerance);
    SetRegistryValue("MDD HXT", "SubType", parameter->subtype);
}

BOOL CMDDApp::OnImportModel(HModel *hm) {
    parameter = new W_PARA;
    parameter->start = hm->GetChor()->GetTime();
    parameter->end = hm->GetChor()->GetTotalTime()->GetValue();
    parameter->startatcurrenttime = FALSE;
    LoadSettings();
    ImportDialog cdlg(parameter);
    if (cdlg.DoModal() != IDOK) {
        delete parameter;
        return TRUE;
    }
    if (!FileExists(parameter->filename.Get())) {
        const String temp = "File \"" + parameter->filename + "\" doesn't exist !\nAborting";
        AfxMessageBox(temp.Get(),MB_ICONERROR);
        delete parameter;
        return true;
    }
    CWaitCursor wait;
    OnImport(hm);
    SaveSettings();
    delete parameter;
    return true;
}

BOOL CMDDApp::OnExportModel(HModel *hm) {
    parameter = new W_PARA;
    parameter->start = 0;
    LoadSettings();
    parameter->start = hm->GetChor()->GetTime();
    parameter->end = hm->GetChor()->GetTotalTime()->GetValue();
    parameter->fps = GetHProject()->GetFPS();

    //   parameter->scale = 1.F;
    //   parameter->tolerance = 0.F;
    ExportDialog cdlg(parameter);
    if (cdlg.DoModal() != IDOK) {
        delete parameter;
        return TRUE;
    }
    CWaitCursor wait;
    OnExport(hm);
    SaveSettings();
    delete parameter;
    return true;
}

BOOL CMDDApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMDDApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
