// NAP  11/19/2002  \Noel100\Plugin\HXT\BVH\Import.cpp

#include "StdAfx.h"
#include "StringLi.h"
#include "Hxt.h"
#include "F_Protos.h"
#include "HashFile.h"
#include "Vector2.h"

#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HPropDri.h"

class Keyframe {
public:
    enum INTERPOLATIONMETHOD {
        HOLD,
        LINEAR,
        SPLINE
    };

    Time m_time;
    float m_value{};

    union {
        BYTE m_flags{};

        struct {
            BYTE m_defaulttangents : 1, m_interpmethod : 2;
        };
    };

    Keyframe() {  // NOLINT(cppcoreguidelines-pro-type-member-init)
        m_defaulttangents = TRUE;
    }
};

BOOL CHxtApp::OnImportActionCache(HActionCache *hac) const {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("KFM");
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
        return TRUE;
    }

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        if (!ImportBVH(filename, nullptr, hac, FALSE)) {
            ReportImportError(filename);
        }
    }
    DeleteStringList(namelist);

    return TRUE;
}

BOOL CHxtApp::OnImportActionCacheContainer(HActionCacheContainer *hacc) const {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("KFM");
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
        return TRUE;
    }

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        String nameonly = filename.GetNameOnly();
        HActionCache *hac = HActionCache::New(nameonly.Get());
        if (!hac) {
            ReportImportError(filename);
        }
        if (!ImportBVH(filename, nullptr, hac, FALSE)) {
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

HDriverShortcut *FindDriverShortcut(HBone *hbone, const HProperty *hproperty);

BOOL CHxtApp::ImportBVH(const String &pfilename, HModelCache *hmc, HActionCache *hac, BOOL bMultipleActions) {
    FileStream fs;
    String filename = pfilename;
    float fTemp;
    int iTemp;

    if (!fs.Open(filename, FileMode::HS_BINARY | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS))
        return FALSE;

    fs >> iTemp;
    /*   if (iTemp != KFMVERSION) {
          CString msg, title;
          msg.LoadString(IDS_INVALIDVERSION);
          title.LoadString(IDS_IMPORTTITLE);
          MessageBox(GetMainApplicationWnd(), msg, title, MB_ICONEXCLAMATION);
          return FALSE;
       }*/

    fs >> fTemp;
    Time totaltime;
    totaltime.SetSeconds(fTemp);

    WORD bonecount;
    fs >> bonecount;

    /*
    The easiest way for the Driver Hierachy for the imported bones to be build is to build
    a temporary model and add one bone.  I will then change the name of this bone to each of the names
    of the bones being loaded from the kfm file, and simply use the Property under the bone to set the keyframes,
    another solution would be to force the user to pick a model to import the kfm action on to.  The last solution would be to just
    allocate all of the nessessary classes to build the hierarchy and drivers and stitch them all together yourself.  This
    method would be more tedious and bug prone, plus a lot more confusing, */

    // Lets build temporary modelcache with one bone
    HModelCache *temphmc = HModelCache::New();
    HBoneCacheContainer *hbcc = HBoneCacheContainer::New();

    temphmc->InsertChildAtTail(hbcc);

    HSegmentCache *hsc = HSegmentCache::New("Testing");
    hbcc->InsertChildAtTail(hsc);

    // ModelCache is build now lets attach it to our actioncache and build a HModel and HAction
    HModel *hm = hac->EditWithModelCache(temphmc);

    // We are ready to start storing keyframes, lets grab our HBone from our HModel instance and then retrieve the Transform variables
    HBoneContainer *hbcontainer = hm->GetChildBoneContainer();
    HBone *hbone = hbcontainer->GetChildBone();

    HTranslateProperty *translate = hbone->GetTransform()->GetTranslate();
    HScaleProperty *scale = hbone->GetTransform()->GetScale();
    HRotateProperty *rotate = hbone->GetTransform()->GetRotate();

    Vector bonedirection, rolldirection, parentbonedirection, parentrolldirection;

    for (int boneindex = 0; boneindex < bonecount; ++boneindex) {
        String bonename = fs.ReadString('\0');
        //Because we simply want to keep renaming the bones and calling store value for each of the bones in the KFM file
        // We must keep removing the drivers so to trick the software into rebuilding new drivers under the new bone name
        hbone->RemoveDrivers();
        hsc->SetName(bonename.Get()); //this will rename the Hbone also, because it is an instance
        bonename = hsc->GetName();
        hbone->SetName(bonename.Get());

        // Need this info for storing Rotate later
        fs >> bonedirection >> rolldirection;
        fs >> parentbonedirection >> parentrolldirection;

        WORD numkf;

        enum {
            XTRANSLATE,
            YTRANSLATE,
            ZTRANSLATE,
            XSCALE,
            YSCALE,
            ZSCALE,
            TOTAL
        };
        // We'll handle the quaternion rotate separately because we can't set it a component at a time (x, y, z, w)
        // We also don't really know if the driver attached to the variable will be a quaternion anyways, could be Vector, or Euler
        HFloatProperty *var{nullptr};
        int i;
        for (i = 0; i < TOTAL; ++i) {
            switch (i) {
                case XTRANSLATE:
                    var = translate->GetX();
                    break;
                case YTRANSLATE:
                    var = translate->GetY();
                    break;
                case ZTRANSLATE:
                    var = translate->GetZ();
                    break;
                case XSCALE:
                    var = scale->GetX();
                    break;
                case YSCALE:
                    var = scale->GetY();
                    break;
                case ZSCALE:
                    var = scale->GetZ();
                    break;
                default:;
            }

            HChannelCP *prevcp{nullptr};
            Vector2 previt, prevot;

            fs >> numkf;
            for (int keyindex = 0; keyindex < numkf; ++keyindex) {
                Keyframe kf;
                float seconds;
                fs >> seconds;
                kf.m_time.SetSeconds(seconds);
                fs >> kf.m_value;
                fs >> kf.m_flags;
                var->StoreValue(kf.m_time, kf.m_value); // This will automatically multiply the scales 100 factor

                if (prevcp)
                    prevcp->SetBias(previt, prevot);

                if (!kf.m_defaulttangents) {
                    HDriverShortcut *drivershortcut = FindDriverShortcut(hbone, var);
                    auto *driver = (HChannelDriver *)drivershortcut->GetDriver();
                    prevcp = driver->GetCPFromTime(kf.m_time);
                    fs >> previt;
                    fs >> prevot;
                } else
                    prevcp = nullptr;
            }

            if (prevcp)
                prevcp->SetBias(previt, prevot);
        }
        // Lets Handle the rotate case now
        // We'll create the storagedriver which will build a QuaternionRotateDriver
        // Once the driver is created we can store the keyframes.
        // After all keyframes are built I will set the bonetoparent rotation in the driver.
        // This quaternion rotation is built by the bone directions of the bone and its parent bone.
        // These directions were read in above from the KFM file, and were originally created
        // when the user first created the action.
        // This rotation tells the driver how the bones were positioned when the original keyframes
        // were built.  We can use this information to allow this action to be put on models that have the
        // same bone hierachy, but with bones not neccessarily positioned the same.direction as the model the action was
        // originally built on.
        // The bonetoparent quat will be used by the software when the action gets hooked up to a model.  
        // It will build a parent compensation quaternion in the drivershortcut under the rotate variable.
        // This parent compensation will be created using the model's bone position and the actions rotate driver's
        // bonetoparent rotation.

        //This way doesn't ensure it is a quaternion driver, if you do this then you must be able to load into euler and vector drivers too
        //HDriverShortcut *drivershortcut = (HDriverShortcut *)hac->CreateStorageDriver(rotate);
        //HQuaternionRotateDriver *quatdriver = (HQuaternionRotateDriver *)drivershortcut->GetDriver();

        HHashObject *parent = rotate->CreateParentForDriver();
        HQuaternionRotateDriver *quatdriver = HQuaternionRotateDriver::New(rotate);
        parent->InsertChildAlpha(quatdriver);
        quatdriver->SetProperty(var);
        HDriverShortcut *drivershortcut = quatdriver->NewShortcut(hac);
        rotate->GetDriverProperty()->AddDriver(drivershortcut);

        enum {
            QUATX,
            QUATY,
            QUATZ,
            QUATW,
            QUATTOTAL
        };
        HChannelDriver *chandriver{nullptr};
        for (i = 0; i < QUATTOTAL; ++i) {
            switch (i) {
                case QUATX:
                    chandriver = (HChannelDriver *)quatdriver->GetX();
                    break;
                case QUATY:
                    chandriver = (HChannelDriver *)quatdriver->GetY();
                    break;
                case QUATZ:
                    chandriver = (HChannelDriver *)quatdriver->GetZ();
                    break;
                case QUATW:
                    chandriver = (HChannelDriver *)quatdriver->GetW();
                    break;
                default:;
            }

            HChannelCP *prevcp{nullptr};
            Vector2 previt, prevot;

            fs >> numkf;
            for (int keyindex = 0; keyindex < numkf; ++keyindex) {
                Keyframe kf;
                float seconds;
                fs >> seconds;
                kf.m_time.SetSeconds(seconds);
                fs >> kf.m_value;
                kf.m_value *= 100.F;
                fs >> kf.m_flags;

                chandriver->StoreValue(kf.m_time, kf.m_value);

                if (prevcp)
                    prevcp->SetBias(previt, prevot);

                if (!kf.m_defaulttangents) {
                    prevcp = chandriver->GetCPFromTime(kf.m_time);
                    fs >> previt;
                    previt.y *= 100;
                    fs >> prevot;
                    prevot.y *= 100;
                } else
                    prevcp = nullptr;
            }
            if (prevcp)
                prevcp->SetBias(previt, prevot);
        }
        quatdriver->ComputeBoneToParent(bonedirection, rolldirection, parentbonedirection, parentrolldirection);
    }

    hac->EndEditWithModelCache(hm);
    HTreeObject::DeleteHandle(temphmc);

    return TRUE;
}
