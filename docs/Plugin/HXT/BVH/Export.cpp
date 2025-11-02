// NAP  12/13/2002  \Noel100\Plugin\HXT\BVH\Export.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "resource.h"
#include "F_Protos.h"
#include "Vector2.h"
#include "ExportActionDialog.h"
#include "ExportActionsDialog.h"
#include "Matrix34.h"

#include "SDK/Misc.h"
#include "SDK/HChor.h"
#include "SDK/HPropDri.h"
#include "SDK/HAction.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"

static HBone *masterbone;

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
        return TRUE;
    }

    CExportActionDialog dlg(hac);
    if (dlg.DoModal() != IDOK)
        return TRUE;

    BOOL export_all = FALSE, geom_only = FALSE, data_only = FALSE;
    switch (dlg.m_exportstate) {
        case 0:
            export_all = TRUE;
            break;
        case 1:
            geom_only = TRUE;
            break;
        case 2:
            data_only = TRUE;
            break;
        case 3:
            geom_only = TRUE;
            data_only = TRUE;
            break;
        default:
            break;
    }

    return ExportBVH(dlg.m_filename, dlg.m_errortolerance, hac, hmc, dlg.m_nomotion, dlg.m_ispadmotion, export_all, geom_only, data_only);
}

BOOL CHxtApp::OnExportActionCacheContainer(HActionCacheContainer *hocc) const {
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
        filename += ".bvh";
        filename = CombineNameToPath(dlg.m_dir, filename);
        BOOL export_all = FALSE, geom_only = FALSE, data_only = FALSE;
        switch (dlg.m_exportstate) {
            case 0:
                export_all = TRUE;
                break;
            case 1:
                geom_only = TRUE;
                break;
            case 2:
                data_only = TRUE;
                break;
            case 3:
                geom_only = TRUE;
                data_only = TRUE;
                break;
            default:
                break;
        }
        ExportBVH(filename, dlg.m_errortolerance, hac, hmc, dlg.m_nomotion, dlg.m_ispadmotion, export_all, geom_only, data_only);
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

static void Tabs(HashStream &hs, const int level) {
    for (int i = 0; i < level; ++i)
        hs << tab;
}

HDriverShortcut *FindDriverShortcut(HBone *hbone, const HProperty *hproperty) {
    for (HPropertyDriver *driver = hbone->GetTransform()->GetHeadDriver(); driver; driver = driver->GetNextDriver())
        if (driver->GetProperty() == hproperty && driver->IsSimpleDriverShortcut())
            return (HDriverShortcut *)driver;
    return nullptr;
}

static BOOL HasTranslateData(HBone *bone) {
    const HDriverShortcut *drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetX());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetY());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetZ());
    if (drivershortcut)
        return TRUE;
    return FALSE;
}

static BOOL HasRotateData(HBone *bone) {
    const HDriverShortcut *drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetRotate());
    if (drivershortcut)
        return TRUE;
    return FALSE;
}

static BOOL HasGeometry(HBone *bone) {
    auto *hsc = (HSegmentCache *)bone->GetCache();
    const HGroupCP *hgcp = hsc->GetGroupCP();
    if (hgcp)
        return TRUE;
    return FALSE;
}

static BOOL HasData(HBone *bone) {
    const HDriverShortcut *drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetX());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetY());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetZ());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetRotate());
    if (drivershortcut)
        return TRUE;

    auto *hsc = (HSegmentCache *)bone->GetCache();
    const HGroupCP *hgcp = hsc->GetGroupCP();
    if (hgcp)
        return TRUE;

    return FALSE;
}

static BOOL HasMotion(HBone *bone) {
    const HDriverShortcut *drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetX());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetY());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetTranslate()->GetZ());
    if (drivershortcut)
        return TRUE;
    drivershortcut = FindDriverShortcut(bone, bone->GetTransform()->GetRotate());
    if (drivershortcut)
        return TRUE;

    return FALSE;
}

//maybe add an option to skip writing bones with out motion that don't have geometry or that are also invisible
//then you would need to write functions to get child and parents that skip the above
static void ExportBVHBone(HBone *startbone, HashStream &hs, int &level, const BOOL nomotion, const BOOL ispadmotion, const BOOL export_all, const BOOL geometry_only, const BOOL motion_only, const BOOL geometry_or_motion) {
    for (HBone *bone = startbone; bone && (level || bone == startbone); bone = bone->GetSiblingBone()) {
#ifdef _DEBUG
        ATLTRACE2(atlTraceGeneral, 0, "slevel = %d\n", level);
#endif
        String name = bone->GetName();
        BOOL needexport = FALSE;
        if (bone == masterbone || export_all) {
            needexport = TRUE;
        } else {
            if (geometry_or_motion) {
                needexport = HasData(bone);
            } else {
                if (geometry_only) {
                    needexport = HasGeometry(bone);
                } else {
                    if (motion_only) {
                        needexport = HasMotion(bone);
                    } else {
                        needexport = TRUE;
                    }
                }
            }
        }
        if (needexport) {
            Tabs(hs, level);
            if (level == 0)
                hs << "ROOT "; // if multiple ROOT are allowed, remove condition 2 above: '&& (level || bone==startbone)' //NAP they are not
            else
                hs << "JOINT ";
            name.Replace(" ", "_");
            name.Replace("\t", "-");
            hs << name << nl;

            Tabs(hs, level);
            hs << '{' << nl;

            level++;
            Tabs(hs, level);
            Vector offset = bone->GetBoneCache()->GetPivot()->GetValue();
            if (bone->GetCache() && bone->GetCache()->GetParent() && bone->GetCache()->GetParent()->IsBone())
                offset = offset - bone->GetCache()->GetParent()->IsBone()->GetBoneCache()->GetPivot()->GetValue();
            offset /= CENTIMETERSPERINCH;
            hs << "OFFSET" << tab << offset.x << tab << offset.y << tab << offset.z << nl;

            Tabs(hs, level);
            if (nomotion || bone == masterbone) {
                hs << "CHANNELS 0" << nl;
            } else {
                const BOOL hasrotatedata = HasRotateData(bone);
                const BOOL writetranslate = HasTranslateData(bone) || (!hasrotatedata && ispadmotion);
                if (writetranslate) {
                    if (hasrotatedata)
                        hs << "CHANNELS 6 Xposition Yposition Zposition Yrotation Xrotation Zrotation" << nl;
                    else
                        hs << "CHANNELS 3 Xposition Yposition Zposition" << nl;
                } else if (hasrotatedata)
                    hs << "CHANNELS 3 Yrotation Xrotation Zrotation" << nl;
                else
                    hs << "CHANNELS 0" << nl;
            }
            //if (!bone->GetChildBone() || !bone->GetChildBone()->GetBoneCache()->GetChained()) {
            if (!bone->GetChildBone() || bone->GetChildBone()->GetBoneCache()->GetPivot() != bone->GetBoneCache()->GetEnd()) {
                Tabs(hs, level);
                hs << "End Site" << nl;
                Tabs(hs, level);
                hs << '{' << nl;
                level++;
                Tabs(hs, level);
                offset = bone->GetBoneCache()->GetEnd()->GetValue() - bone->GetBoneCache()->GetPivot()->GetValue();
                offset /= CENTIMETERSPERINCH;
                hs << "OFFSET" << tab << offset.x << tab << offset.y << tab << offset.z << nl;
                level--;
                Tabs(hs, level);
                hs << '}' << nl;
            }
        }
        if (bone->GetChildBone())
            ExportBVHBone(bone->GetChildBone(), hs, level, nomotion, ispadmotion, export_all, geometry_only, motion_only, geometry_or_motion);

        if (needexport) {
            level--;
            Tabs(hs, level);
            hs << '}' << nl;
        }
#ifdef _DEBUG
        ATLTRACE2(atlTraceGeneral, 0, "elevel = %d\n", level);
#endif
    }
}

static void ExportBVHMotion(HBone *startbone, HashStream &hs, const BOOL dosiblings, const BOOL ispadmotion, const BOOL export_all, const BOOL geometry_only, const BOOL motion_only, const BOOL geometry_or_motion) {
    for (HBone *bone = startbone; bone && (dosiblings || bone == startbone); bone = bone->GetSiblingBone()) {
        BOOL needexport = FALSE;
        if (bone == masterbone || export_all) {
            needexport = TRUE;
        } else {
            if (geometry_or_motion) {
                needexport = HasData(bone);
            } else {
                if (geometry_only) {
                    needexport = HasGeometry(bone);
                } else {
                    if (motion_only) {
                        needexport = HasMotion(bone);
                    } else {
                        needexport = TRUE;
                    }
                }
            }
        }
        if (needexport && bone != masterbone) {
            const BOOL hasrotate = HasRotateData(bone);
            const BOOL writetranslate = HasTranslateData(bone) || (!hasrotate && ispadmotion);
            if (writetranslate || hasrotate) {
                if (writetranslate) {
                    Vector t = bone->GetTransform()->GetTranslate()->GetValue() / CENTIMETERSPERINCH; //localmatrix.GetTranslate() ;
                    t *= ToMatrix33(bone->GetBoneCache()->GetBoneToStandard()).Transpose();
                    if (hash_math::abs(t.x) < 1e-4)
                        t.x = 0;
                    if (hash_math::abs(t.y) < 1e-4)
                        t.y = 0;
                    if (hash_math::abs(t.z) < 1e-4)
                        t.z = 0;
                    hs << t.x << tab << t.y << tab << t.z << tab;
                }

                if (hasrotate) {
                    Matrix34 localmatrix = bone->GetLocalMatrix();
                    RotateEuler euler(localmatrix);
                    if (hash_math::abs(euler.x) < 1e-4)
                        euler.x = 0;
                    if (hash_math::abs(euler.y) < 1e-4)
                        euler.y = 0;
                    if (hash_math::abs(euler.z) < 1e-4)
                        euler.z = 0;
                    hs << euler.y << tab << euler.x << tab << euler.z << tab;
                }
            }
        }
        if (bone->GetChildBone())
            ExportBVHMotion(bone->GetChildBone(), hs, TRUE, ispadmotion, export_all, geometry_only, motion_only, geometry_or_motion);
    }
}

BOOL CHxtApp::ExportBVH(String &filename, const float errortolerance, HActionCache *hac, HModelCache *hmc, const BOOL nomotiondata, const BOOL ispadmotion, const BOOL export_all, const BOOL geometry_only, const BOOL motion_only) {
    FileStream fs;

    if (!fs.Open(filename))
        return TRUE;

    CWaitCursor wait;
    HProgressBar *progress = GetProgressBar();
    if (progress) {
        progress->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        progress->SetMessage1(text);
        progress->SetProgress(0);
    }

    HModel *hm = hac->EditWithModelCache(hmc);

    // Convert all constraints to Keys
    HActionCache *hunconstrainedac = hac->BakeUnconstrainedAction(hm, errortolerance);
    hac->EndEditWithModelCache(hm);
    if (hunconstrainedac == nullptr) {
        ReportExportError(filename);
        return TRUE;
    }

    hm = hunconstrainedac->EditWithModelCache(hmc);

    //BVH Starts
    fs << "HIERARCHY" << nl;
    int level = 0;
    masterbone = (HBone *)hm;
    BOOL geometry_or_motion = FALSE;
    if (geometry_only && motion_only)
        geometry_or_motion = TRUE;

    ExportBVHBone(hm, fs, level, nomotiondata, ispadmotion, export_all, geometry_only, motion_only, geometry_or_motion); //model not progeny for multi root bones
    while (level > 0) {
        //should not happened
        level--;
        Tabs(fs, level);
        fs << '}' << nl;
    }
    if (progress) {
        progress->SetProgress(50);
    }

    if (!nomotiondata) {
        const float fps = GetHProject()->GetFPS();
        const Time totaltime = hunconstrainedac->GetTotalTime();
        fs << "MOTION" << nl;
        fs << "Frames: " << totaltime.GetCell(fps) << nl;
        fs << "Frame Time: " << hash_math::rcp(fps) << nl;

        Time steptime;
        steptime.SetSeconds(hash_math::rcp(fps));
        int framecount = 0;
        HChor *hchor = hm->GetChor();
        for (Time time; time <= totaltime; time = steptime * ++framecount) {
            hchor->CreateFrame(time);
            ExportBVHMotion(hm, fs, FALSE, ispadmotion, export_all, geometry_only, motion_only, geometry_or_motion);
            fs << nl;
        }
    }
    //BVH ENDS
    if (progress) {
        progress->SetProgress(100);
    }
    fs.Close();
    hunconstrainedac->EndEditWithModelCache(hm);
    HTreeObject::DeleteHandle(hunconstrainedac);
    if (progress)
        progress->Uninitialize();
    return TRUE;
}
