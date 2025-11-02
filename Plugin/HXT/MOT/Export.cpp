// Dan  8/20/2002  \Dan100\Plugin\HXT\MOT\Export.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "resource.h"
#include "F_Protos.h"
#include "Matrix34.h"
#include "ExportActionsDialog.h"

#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/HProgres.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"
#include "SDK/Misc.h"

BOOL CHxtApp::OnExportActionCache(HActionCache *hac) const {
    HModelCache *hmc = hac->GetDefaultModelCache();
    if (hmc == nullptr) {
        CString msg, title;
        msg.LoadString(IDS_ACTIONHASNOMODELASSIGNED);
        String temp = msg;
        temp.Replace("%1", hac->GetName());
        msg = temp.Get();
        title.LoadString(IDS_EXPORTTITLE);

        MessageBox(GetMainApplicationWnd(), msg, title, MB_OK);
        return FALSE;
    }

    String filename;
    if (!GetFileName(hac, filename))
        return TRUE;

    ExportMOT(filename, hac, hmc);
    return TRUE;
}

BOOL CHxtApp::OnExportActionCacheContainer(HActionCacheContainer *hocc) {
    CExportActionsDialog dlg(hocc);
    if (dlg.DoModal() != IDOK)
        return TRUE;

    for (POSITION pos = dlg.m_selected.GetHeadPosition(); pos;) {
        HActionCache *hac = dlg.m_selected.GetNext(pos);
        HModelCache *hmc = hac->GetDefaultModelCache();
        if (hmc == nullptr) {
            CString msg, title;
            msg.LoadString(IDS_ACTIONHASNOMODELASSIGNED);
            String temp = msg;
            temp.Replace("%1", hac->GetName());
            msg = temp.Get();
            title.LoadString(IDS_EXPORTTITLE);
            MessageBox(GetMainApplicationWnd(), msg, title, MB_OK);
            continue;
        }
        String filename = hac->GetName();
        filename = filename.GetNameOnlyWithoutSuffix();
        filename += ".mot";
        filename = CombineNameToPath(dlg.m_dir, filename);
        ExportMOT(filename, hac, hmc);
    }
    return TRUE;
}

void CHxtApp::ReportExportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_EXPORTTITLE);
    CString text;
    text.LoadString(IDS_ERROREXPORTINGACTION);
    String temp = text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

BOOL CHxtApp::ExportMOT(String &filename, HActionCache *hac, HModelCache *hmc) {
    FileStream fs;

    if (!fs.Open(filename, FileMode::HS_BINARY | FileMode::HS_DONTPROGRESS))
        return FALSE;
    fs.SetWriteStringCounts(FALSE);

    CWaitCursor wait;
    HProgressBar *progress = GetProgressBar();
    if (progress) {
        progress->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        progress->SetMessage1(text);
    }

    HModel *hm = hac->EditWithModelCache(hmc); // tell AM what model we want the action on
    if (hm == nullptr)
        return FALSE;

    // This plugin walks the shortcuts in the actioncache, and only exports the bones which have drivers there.
    // This technique is only works if the action has first been baked.
    // This is because Calf Right may have geometry, and have motion, but it has no channels in the action.
    // It could be moved through constraints in relationships.  So if you don't want to create a baked action first,
    // then, you should either save all bone motion, or at least all bones which control geometry.

    HActionCache *hbakedac = hac->BakeUnconstrainedAction(hm, 0.F); // bake out the constraints
    hac->EndEditWithModelCache(hm); // we are done with the original action now

    hm = hbakedac->EditWithModelCache(hmc); // edit the new baked action
    if (hm == nullptr)
        return FALSE;

    HChor *chor = hm->GetChor();
    if (chor == nullptr)
        return FALSE;

    fs << MOTVERSION;
    String name = hmc->GetName();
    name = name.GetNameOnly();
    fs << name.Get() << '\0'; // We don't want Strings << operator to be called because it will prefix the string with its length, invalidating the file format

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();

    const Time totaltime = hac->GetTotalTime();

    fs << (WORD)totaltime.GetCell(fps);

    WORD count = 0;
    HAnimObjectShortcut *boneshortcut;

    // Count bone shortcuts, these are bones that have drivers
    // We only want boneshorts that are hooked to a geometry in our model
    auto *bonesfolder = (HAnimObjectShortcut *)hbakedac->FindChildByName("Bones"); // Finds "Bones" shortcut under driver folder

    if (bonesfolder) {
        for (boneshortcut = (HAnimObjectShortcut *)bonesfolder->GetChild(), count = 0; boneshortcut; boneshortcut = (HAnimObjectShortcut *)boneshortcut->GetSibling()) {
            if (boneshortcut->GetAnimObject())
                count++;
        }
    }

    fs << count;

    if (bonesfolder) {
        int i = 0;
        for (boneshortcut = (HAnimObjectShortcut *)bonesfolder->GetChild(), count = 0; boneshortcut; boneshortcut = (HAnimObjectShortcut *)boneshortcut->GetSibling()) {
            auto *bone = (HBone *)boneshortcut->GetAnimObject();
            if (bone) {
                HBoneCache *bonec = bone->GetBoneCache();
                bone = (HBone *)hm->FindAnimObjectFromCache(bonec); // ensure that we get our instance, as opposed to one from some other window or chor
                if (!bone)
                    continue;
                if (progress)
                    progress->SetMessage2(bone->GetName());

                fs << bone->GetName() << '\0';

                for (Time time; time <= totaltime; time.StepFrame(fps)) {
                    chor->CreateFrame(time); // this actually solves all bones for the given time, but it is our only solution
                    fs << bone->GetLocalMatrix();
                }

                if (progress && 0 != count)
                    progress->SetProgress((int)((float)++i / count * 100));
            }
        }
    }

    hbakedac->EndEditWithModelCache(hm);
    if (progress)
        progress->Uninitialize();
    return TRUE;
}

BOOL CHxtApp::GetFileName(HActionCache *hac, String &filename) const {
    filename = hac->GetName();
    filename = filename.GetNameOnly().GetWithoutSuffix() + ".mot";
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);

    const String ext("mot");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, filename, ext.Get(), ext.Get()))
            return FALSE;
    }
    return TRUE;
}
