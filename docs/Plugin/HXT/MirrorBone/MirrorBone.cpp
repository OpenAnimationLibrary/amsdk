// MirrorBone.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "MirrorBone.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMirrorBoneApp

BEGIN_MESSAGE_MAP(CMirrorBoneApp, CWinApp)
        //{{AFX_MSG_MAP(CMirrorBoneApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMirrorBoneApp Konstruktion

CMirrorBoneApp::CMirrorBoneApp() = default;
CMirrorBoneApp::~CMirrorBoneApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMirrorBoneApp-Objekt

CMirrorBoneApp theApp;

void CMirrorBoneApp::Cleanup() {
#ifdef _DEBUG
    fs.Close();
#endif
    SaveSettings();
    if (para->write_log)
        fs_log.Close();
    bone_list.RemoveAll();
    cps_list.RemoveAll();
    cpw_list.RemoveAll();
    if (bar)
        bar->Uninitialize();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    delete para;
}

BOOL CMirrorBoneApp::OnBone(HModelCache *hmc, HBoneCache *hbc) {
    para = new Parameter;
    para->hmc = hmc;
    para->model_ischanged = false;
    para->start_from_group = false;
    String projectname = GetHProject()->GetFileName().GetPathOnly();
    if (projectname.IsEmpty()) {
        para->path = String::GetAppPath();
    } else {
        para->path = projectname;
    }
    para->path += "\\";
    projectname = GetHProject()->GetFileName();

    LoadSettings();
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete para;
        return TRUE;
    }
    bar = GetProgressBar();
    if (bar) {
        bar->Initialize();
        bar->SetMessage1("MirrorBone");
        bar->SetMessage2("Collect Bones");
        bar->SetProgress(0);
    }

    CWaitCursor wait;
#ifdef _DEBUG
    fs.Open("e:\\mirrorbone.txt", FileMode::HS_ASCII);
#endif
    if (para->write_log) {
        String logname;
        if (projectname.IsEmpty()) {
            logname = para->path + "mirrorbone.txt";
            projectname = para->path + "mirrorbone.txt";
        } else {
            logname = para->path + "mb_" + projectname.GetNameOnlyWithoutSuffix() + ".txt";
            logname_ext = para->path + projectname.GetNameOnlyWithoutSuffix();
        }
        fs_log.Open(logname, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
        fs_log << "   Model     " << hmc->GetName() << nl;
        fs_log << "   StartBone " << hbc->GetName() << nl << nl;
    }

    if (!para->casesensitive)
        para->removestring.MakeLower();
    if (Worker(hmc, hbc)) {
        Cleanup();
        return TRUE;
    }

    Cleanup();
    return TRUE;
}

BOOL CMirrorBoneApp::OnGroup(HModelCache *hmc, HGroup *hg) {
    para = new Parameter;
    para->hmc = hmc;
    para->model_ischanged = false;
    para->start_from_group = true;
    String projectname = GetHProject()->GetFileName().GetPathOnly();
    if (projectname.IsEmpty()) {
        para->path = String::GetAppPath();
    } else {
        para->path = projectname;
    }
    para->path += "\\";
    projectname = GetHProject()->GetFileName();

    LoadSettings();
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete para;
        return TRUE;
    }
    bar = GetProgressBar();
    if (bar) {
        bar->Initialize();
        bar->SetMessage1("MirrorBone");
        bar->SetMessage2("Collect Bones");
        bar->SetProgress(0);
    }

    CWaitCursor wait;
#ifdef _DEBUG
    fs.Open("e:\\mirrorbone.txt", FileMode::HS_ASCII);
#endif
    if (para->write_log) {
        String logname;
        if (projectname.IsEmpty()) {
            logname = para->path + "mirrorbone.txt";
            projectname = para->path + "mirrorbone.txt";
        } else {
            logname = para->path + "mb_" + projectname.GetNameOnlyWithoutSuffix() + ".txt";
            logname_ext = para->path + projectname.GetNameOnlyWithoutSuffix();
        }
        fs_log.Open(logname, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
        fs_log << "   Model      " << hmc->GetName() << nl;
        fs_log << "   StartGroup " << hg->GetName() << nl;
    }

    if (!para->casesensitive)
        para->removestring.MakeLower();
    if (WorkerGroup(hmc, hg)) {
        Cleanup();
        return TRUE;
    }

    Cleanup();
    return TRUE;
}

void CMirrorBoneApp::SaveSettings() {
    if (para->write_log) {
        fs_log << nl << "   Pluginsettings" << nl;
        fs_log << "logfile           " << para->write_log << nl;
        fs_log << "ex_logfile        " << para->extended_log << nl;
        fs_log << "name_only         " << para->name_only << nl;
        fs_log << "correct_pos       " << para->correct_pos_mirrorbone << nl;
        fs_log << "sourceside        " << para->sourceside << nl;
        fs_log << "group_unassigned  " << para->groupunassigned << nl;
        fs_log << "group_no_mirror   " << para->groupnotmirrors << nl;
        fs_log << "use_tol_bon       " << para->use_tolerance_bones << nl;
        fs_log << "use_tol_cp        " << para->use_tolerance_cps << nl;
        fs_log << "tol_bone          " << para->tolerance_bones << nl;
        fs_log << "tol_cp            " << para->tolerance_cps << nl;
        fs_log << "tol_midbone       " << para->tolerance_midbone << nl;
        fs_log << "exclude_sb        " << para->excludestartbone << nl;
        fs_log << "replace           " << para->addstring.GetBuffer(para->addstring.GetLength()) << nl;
        fs_log << "match             " << para->removestring.GetBuffer(para->removestring.GetLength()) << nl;
        fs_log << "weight_unweightet " << para->weight_unweighted << nl;
        fs_log << "clear_target      " << para->clear_target << nl;
        fs_log << "casesensitive     " << para->casesensitive << nl;
    }
    SetRegistryValue("MirrorBone HXT", "clear_target", para->clear_target);
    SetRegistryValue("MirrorBone HXT", "weight_unweightet", para->weight_unweighted);
    SetRegistryValue("MirrorBone HXT", "logfile", para->write_log);
    SetRegistryValue("MirrorBone HXT", "ext_logfile", para->extended_log);
    SetRegistryValue("MirrorBone HXT", "name_only", para->name_only);
    SetRegistryValue("MirrorBone HXT", "correct_pos", para->correct_pos_mirrorbone);
    SetRegistryValue("MirrorBone HXT", "sourceside", para->sourceside);
    SetRegistryValue("MirrorBone HXT", "make_group", para->groupunassigned);
    SetRegistryValue("MirrorBone HXT", "group_nomirror", para->groupnotmirrors);
    SetRegistryValue("MirrorBone HXT", "use_tol_bon", para->use_tolerance_bones);
    SetRegistryValue("MirrorBone HXT", "use_tol_cp", para->use_tolerance_cps);
    SetRegistryValue("MirrorBone HXT", "tol_bone", para->tolerance_bones);
    SetRegistryValue("MirrorBone HXT", "tol_cp", para->tolerance_cps);
    SetRegistryValue("MirrorBone HXT", "tol_midbone", para->tolerance_midbone);
    SetRegistryValue("MirrorBone HXT", "exclude_sb", para->excludestartbone);
    SetRegistryValue("MirrorBone HXT", "casesensitive", para->casesensitive);
    String temp = para->addstring.GetBuffer(para->addstring.GetLength());
    SetRegistryString("MirrorBone HXT", "replace", temp);
    temp = para->removestring.GetBuffer(para->removestring.GetLength());
    SetRegistryString("MirrorBone HXT", "match", temp);
}

void CMirrorBoneApp::LoadSettings() const {
    para->extended_log = GetRegistryValue("MirrorBone HXT", "ext_logfile", true);
    para->write_log = GetRegistryValue("MirrorBone HXT", "logfile", true);
    para->clear_target = GetRegistryValue("MirrorBone HXT", "clear_target", false);
    para->weight_unweighted = GetRegistryValue("MirrorBone HXT", "weight_unweightet", false);
    para->name_only = GetRegistryValue("MirrorBone HXT", "name_only", true);
    para->correct_pos_mirrorbone = GetRegistryValue("MirrorBone HXT", "correct_pos", true);
    para->sourceside = GetRegistryValue("MirrorBone HXT", "sourceside", true);
    para->groupunassigned = GetRegistryValue("MirrorBone HXT", "make_group", false);
    para->groupnotmirrors = GetRegistryValue("MirrorBone HXT", "group_nomirror", true);
    para->use_tolerance_bones = GetRegistryValue("MirrorBone HXT", "use_tol_bon", false);
    para->use_tolerance_cps = GetRegistryValue("MirrorBone HXT", "use_tol_cp", false);
    para->tolerance_bones = GetRegistryValue("MirrorBone HXT", "tol_bone", 0.01F);
    para->tolerance_cps = GetRegistryValue("MirrorBone HXT", "tol_cp", 0.01F);
    para->tolerance_midbone = GetRegistryValue("MirrorBone HXT", "tol_midbone", 0.01F);
    para->excludestartbone = GetRegistryValue("MirrorBone HXT", "exclude_sb", false);
    para->casesensitive = GetRegistryValue("MirrorBone HXT", "casesensitive", true);
    String temp = GetRegistryString("MirrorBone HXT", "replace", "left");
    para->addstring = temp.Get();
    temp = GetRegistryString("MirrorBone HXT", "match", "right");
    para->removestring = temp.Get();
}

BOOL CMirrorBoneApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMirrorBoneApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
