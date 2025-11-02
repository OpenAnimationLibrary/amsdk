// KB  3/1/02  \Ken90\Plugin\HXT\Raw\Export.cpp

#include "StdAfx.h"
#include "Hxt.h"

#include "F_Protos.h"
#include "HashFile.h"

#include "Vector.h"
#include "Matrix34.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HDecal.h"
#include "SDK/HCamera.h"
#include "SDK/HLight.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HChor.h"
#include "StrClass.h"

BOOL CHxtApp::OnExportRaw(HCamera *hcamera) const {
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);

    const String ext("raw");
    String filename;
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, filename, ext.Get(), ext.Get()))
            return TRUE;
    }
    CWaitCursor wait;

    FileStream fs;
    if (!fs.Open(filename, FileMode::HS_ASCII | FileMode::HS_HASH | FileMode::HS_DONTPROGRESS))
        return TRUE;

    constexpr int numcolumns = 16;
    HProject *hproject = GetHProject();
    const float fps = hproject->GetFPS();
    Time time = hcamera->GetChor()->GetTotalTime()->GetValue();

    const int framecount = time.GetFrame(fps);
    fs << framecount << sp << numcolumns << nl;

    HTransformProperty *htransform = hcamera->GetTransform();
    HTranslateProperty *htranslate = htransform->GetTranslate();
    HRotateProperty *hrotate = htransform->GetRotate();
    const HFloatProperty *hfocaldistance = hcamera->GetFocalDistance();
    const HFloatProperty *hfocallength = hcamera->GetFocalLength();
    //   HFloatProperty *hfrontdof = hcamera->GetFrontDOFDistance(); // Dan: finish implementing this
    //   HFloatProperty *hbackdof = hcamera->GetBackDOFDistance();
    for (int frame = 0; frame < framecount; ++frame) {
        time.SetFrame(frame, fps);
        Vector eye = htranslate->GetValue(time);
        Vector poi(0.F);
        Quaternion quat = hrotate->GetValue(time);
        RotateVector rot(quat);
        const float dist = hfocaldistance->GetValue(time);
        const float fov = hfocallength->GetValue(time);
        constexpr float fnear = 0.0; //hfrontdof->GetValue( time );
        constexpr float ffar = 0.0; //hbackdof->GetValue( time );
        const float outframe = frame+1.F;
        //    Frame     EyeX EyeY EyeZ  Speed  POIX POIY POIZ   Speed    RotX RotY RotZ     Distance          Roll            FOV           Near           Far
        fs << outframe << sp << eye << sp << 0 << sp << poi << sp << 0 << sp << rot.end << sp << dist << sp << rot.roll << sp << fov << sp << fnear << sp << ffar << nl;
    }

    fs.Close();

    return TRUE;
}

/*
static HProperty *FindProperty(HAnimObject *parent, const String &name) {
    if (name.IsEmpty())
        return nullptr;

    String allpropertiesname;
    String currpropertyname(name);
    const int pos = name.Find('|');
    if (pos != -1) {
        currpropertyname = name.Left(pos);
        const int whatsleft = name.GetLength() - pos - 1;
        if (whatsleft > 0)
            allpropertiesname = name.Right(whatsleft);
    }
    HProperty *prop;
    for (int i = 0; (prop = parent->GetPropertyAt(i)); ++i) {
        HPropertyInfo *info = prop->GetPropertyInfo();
        String matchname = info->GetMatchName();
        if (matchname == currpropertyname) {
            if (allpropertiesname.IsEmpty())
                return prop;
            return FindProperty(prop, allpropertiesname);
        }
    }
    return nullptr;
}
*/
BOOL CHxtApp::OnImportRaw(HCamera *hcamera) const {
    String filename;
    CString title, filters;
    title.LoadString(IDS_OPENFILE);
    filters.LoadString(IDS_OPENFILTERS);
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(title, filters, filename, "txt", "MOC"))
            return TRUE;
    }
    FileStream fs;
    if (!fs.Open(filename, FileMode::HS_LOAD | FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS))
        return FALSE;

    MemoryStream ms(256);
    fs.ReadLine(ms);
    int lastframe, columns;
    ms >> lastframe >> columns;

    if (fs.IsFailed() || columns != 16)
        return FALSE;

    float frame;
//    float startframe = 0;
    do {
        fs.ReadLine(ms);
        if (fs.IsFailed())
            break;

        Vector eye, poi, rot;
        float eyespeed, poispeed, dist, roll, fov, fnear, ffar;
        ms >> frame >> eye >> eyespeed >> poi >> poispeed >> rot >> dist >> roll >> fov >> fnear >> ffar;
        if (fs.IsFailed())
            break;
        //      SetFrame( startframe + frame-1 );
        frame--;
        frame /= 30.0F;

        hcamera->GetTransform()->GetTranslate()->StoreValue(Time(frame), eye);

        Vector aim = poi - eye;
        aim.Normalize();
        RotateVector rv(aim, roll);

        //      Quaternion quat = RotateVectorToQuat( rv, FALSE );
        float y = hash_math::atan2(rv.end.x, rv.end.z);
        float x = hash_math::atan2(-rv.end.y, hash_math::sqrt(rv.end.x * rv.end.x + rv.end.z * rv.end.z));
        Quaternion quat = YXRotateRadiansQ(y, x);
        //      if ( rv.roll )
        //         quat *= ZRotateQ( rv.roll );

        hcamera->GetTransform()->GetRotate()->StoreValue(Time(frame), quat);

        float focallength = 35.0F / 2.F / hash_math::tan(fov / hash_constants::radians / 2.F);
        focallength *= 49.0F / 65.2F; // fudge factor where 65.2 = 49;
        hcamera->GetFocalLength()->StoreValue(Time(frame), focallength);

    } while (frame != lastframe && !fs.Eof() && !EscapeKeyDown());

    //   GetProject()->UpdateAllViews();

    return TRUE;
}
