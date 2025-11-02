// RC  5/3/2002  \Randy95\Plugin\HXT\MOT\Import.cpp

#include "StdAfx.h"
#include "StringLi.h"
#include "Hxt.h"
#include "F_Protos.h"
#include "HashFile.h"
//#include "Vector2.h"
#include "Matrix34.h"

#include "SDK/HAction.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/Misc.h"
#include "ChooseModelDialog.h"

BOOL CHxtApp::OnImportActionCache(HActionCache *hac) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("MOT");
    StringList *namelist = nullptr;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }
    if (namelist == nullptr) {
        CString caption1;
        caption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTING);
        MessageBox(GetMainApplicationWnd(), text, caption1, MB_OK);
        return FALSE;
    }

    CWaitCursor wait;
    const BOOL bMultipleActions = namelist->GetCount() > 1;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        HModelCache *hmc = m_hmc;
        if (!hmc) {
            // used m_mch for all actions
            CChooseModelDialog dlg(GetHProject()->GetChildObjectCacheContainer(), filename, hac->GetDefaultModelCache(), bMultipleActions);
            if (dlg.DoModal() != IDOK)
                return TRUE;
            if (dlg.m_bUseForAllActions)
                m_hmc = dlg.m_hmc;
            hmc = dlg.m_hmc;
            m_fFps = dlg.m_fFps;
            m_fErrorTol = dlg.m_fErrorTol;
        }
        if (!ImportMOT(filename, hmc, hac, bMultipleActions)) {
            ReportImportError(filename);
        }
    }
    DeleteStringList(namelist);

    return TRUE;
}

BOOL CHxtApp::OnImportActionCacheContainer(HActionCacheContainer *hacc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("MOT");
    StringList *namelist = nullptr;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }
    if (namelist == nullptr) {
        CString caption1;
        caption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTING);
        MessageBox(GetMainApplicationWnd(), text, caption1, MB_OK);
        return FALSE;
    }

    CWaitCursor wait;
    const BOOL bMultipleActions = namelist->GetCount() > 1;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        String nameonly = filename.GetNameOnly();
        HModelCache *hmc = m_hmc;
        if (!hmc) {
            // used m_mch for all actions
            CChooseModelDialog dlg(GetHProject()->GetChildObjectCacheContainer(), nameonly, nullptr, bMultipleActions);
            if (dlg.DoModal() != IDOK)
                return TRUE;
            if (dlg.m_bUseForAllActions)
                m_hmc = dlg.m_hmc;
            hmc = dlg.m_hmc;
            m_fFps = dlg.m_fFps;
            m_fErrorTol = dlg.m_fErrorTol;
        }
        HActionCache *hac = HActionCache::New(nameonly.Get());
        if (hac == nullptr) {
            ReportImportError(filename);
            continue;
        }

        if (!ImportMOT(filename, hmc, hac, bMultipleActions)) {
            ReportImportError(filename);
        }
    }
    DeleteStringList(namelist);

    return TRUE;
}

void CHxtApp::ReportImportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_IMPORTTITLE);
    CString text;
    text.LoadString(IDS_ERRORIMPORTINGACTION);
    String temp = text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

BOOL CHxtApp::ImportMOT(const String &pfilename, HModelCache *hmc, HActionCache *hdstac, BOOL bMultipleActions) const {
    FileStream fs;
    String filename = pfilename;
    HActionCache *hac;

    hdstac->SetDefaultModelCache(hmc);

    if (!fs.Open(filename, FileMode::HS_BINARY | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS))
        return FALSE;

    if (m_fErrorTol)
        hac = HActionCache::New(nullptr, FALSE, FALSE); // need a hactioncache to reduce in
    else
        hac = hdstac;

    int iVersion;
    fs >> iVersion;
    if (iVersion != MOTVERSION) {
        CString msg, title;
        msg.LoadString(IDS_INVALIDVERSION);
        title.LoadString(IDS_IMPORTTITLE);
        MessageBox(GetMainApplicationWnd(), msg, title, MB_ICONEXCLAMATION);
        return FALSE;
    }

    HModel *hm = hac->EditWithModelCache(hmc);
    if (hm == nullptr)
        return FALSE;

    String modelname = fs.ReadString('\0');

    WORD framecount;
    fs >> framecount;

    WORD bonecount;
    fs >> bonecount;

    for (int boneindex = 0; boneindex < bonecount; ++boneindex) {
        String bonename = fs.ReadString('\0');
        HBone *hb = hm->FindBone(bonename.Get());
        Matrix34 matrix;
        for (int frame = 0; frame < framecount; frame++) {
            fs >> matrix;
            if (hb) {
                const Time time(frame, m_fFps);
                hb->SetLocalMatrix(time, matrix);
            }
        }
    }

    if (m_fErrorTol) {
        // now lets merge into the hdestac;
        // we will do this by Editing the hdestac with the same modelcache we are using
        // with hact.  We will walk the boneshortcuts in hac, use the animobject pointer and retrieve the real bones.
        // With thess bones I can get to the transform variables, were I can read the values, and jam them in the hdestac
        // drivers.  Here it goes!

        // lets hook up our modelcache to the dest action also
        HModel *hdstm = hdstac->EditWithModelCache(hmc);

        auto *bonesfolder = (HAnimObjectShortcut *)hac->FindChildByName("Bones"); // Finds "Bones" shortcut under driver folder (aka ActionCache )

        for (auto *boneshortcut = (HAnimObjectShortcut *)bonesfolder->GetChild(); boneshortcut; boneshortcut = (HAnimObjectShortcut *)boneshortcut->GetSibling()) {
            auto *srcbone = (HBone *)boneshortcut->GetAnimObject();
            if (srcbone) {
                // Lets find dest bone now
                HBone *dstbone = hdstm->FindBone(srcbone->GetName());

                HTransformProperty *srctransform = srcbone->GetTransform();
                HTransformProperty *dsttransform = dstbone->GetTransform();

                HFloatProperty *srcvar = nullptr;
                const HFloatProperty *dstvar = nullptr;

                enum {
                    XTRANS,
                    YTRANS,
                    ZTRANS,
                    XSCALE,
                    YSCALE,
                    ZSCALE,
                    TOTALDRIVERS
                };
                for (int i = XTRANS; i < TOTALDRIVERS; ++i) {
                    switch (i) {
                        case XTRANS:
                            srcvar = srctransform->GetTranslate()->GetX();
                            dstvar = dsttransform->GetTranslate()->GetX();
                            break;
                        case YTRANS:
                            srcvar = srctransform->GetTranslate()->GetY();
                            dstvar = dsttransform->GetTranslate()->GetY();
                            break;
                        case ZTRANS:
                            srcvar = srctransform->GetTranslate()->GetZ();
                            dstvar = dsttransform->GetTranslate()->GetZ();
                            break;
                        case XSCALE:
                            srcvar = srctransform->GetScale()->GetX();
                            dstvar = dsttransform->GetScale()->GetX();
                            break;
                        case YSCALE:
                            srcvar = srctransform->GetScale()->GetY();
                            dstvar = dsttransform->GetScale()->GetY();
                            break;
                        case ZSCALE:
                            srcvar = srctransform->GetScale()->GetZ();
                            dstvar = dsttransform->GetScale()->GetZ();
                            break;
                    }
                    srcvar->Reduce(m_fErrorTol); // reduce driver

                    Time prevtime;
                    prevtime.SetTagged();
                    for (Time time = srcvar->GetFirstKey(); time != prevtime; time = srcvar->GetNextKey(time)) {
                        prevtime = time;
                        dstvar->StoreValue(time, srcvar->GetValue(time));
                    }
                }
                // now lets do the rotate
                HRotateProperty *srcrotate = srctransform->GetRotate();
                HRotateProperty *dstrotate = dsttransform->GetRotate();
                srcrotate->Reduce(m_fErrorTol); // reduce driver
                Time prevtime;
                prevtime.SetTagged();
                for (Time time = srcrotate->GetFirstKey(); time != prevtime; time = srcrotate->GetNextKey(time)) {
                    prevtime = time;
                    dstrotate->StoreValue(time, srcrotate->GetValue(time));
                }
            }
        }
        hdstac->EndEditWithModelCache(hdstm);
        hac->EndEditWithModelCache(hm);
        HTreeObject::DeleteHandle(hac);
    } else
        hac->EndEditWithModelCache(hm);
    return TRUE;
}
