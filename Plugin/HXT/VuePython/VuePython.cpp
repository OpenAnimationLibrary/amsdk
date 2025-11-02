// VuePython.cpp : Definiert die Initialisierungsroutinen für die DLL.
//

#include "StdAfx.h"
#include "VuePython.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CVuePythonApp, CWinApp)
END_MESSAGE_MAP()

CVuePythonApp::CVuePythonApp() = default;

CVuePythonApp::~CVuePythonApp() = default;

CVuePythonApp theApp;

BOOL CVuePythonApp::GetPropRecurseCamera(HProperty *akt_prop) const {
    HProperty *prop;

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (!prop)
            return TRUE;
        if (!GetPropRecurseCamera(prop)) {
            String temp = prop->GetFullName();
            if (temp.Find(".Resolution.Width") != -1) {
                para->width = ((HIntProperty *)prop)->GetValue();
            }
            if (temp.Find(".Resolution.Height") != -1) {
                para->height = ((HIntProperty *)prop)->GetValue();
            }
        }
    }
    return FALSE;
}

void CVuePythonApp::GetPropCamera(HHashObject *obj) const {
    HProperty *prop;
    for (int i = 0; (prop = obj->GetPropertyAt(i)); ++i) {
        if (prop) {
            String temp = prop->GetFullName();
            if (temp.Find(".OutputOptions") != -1) {
                GetPropRecurseCamera(prop);
            }
        }
    }
}

void CVuePythonApp::GetPropLight(HHashObject *obj) const {
    HProperty *prop;
    for (int i = 0; (prop = obj->GetPropertyAt(i)); ++i) {
        if (prop) {
            String temp = prop->GetFullName();
            if (temp.Find(".Type") != -1) {
                para->light_type = ((HIntProperty *)prop)->GetValue();
            }
        }
    }
}

float AM_VUE_FOV(const float am_fov) {
    const float max_fov = 2.F * hash_math::atan(35.F / (2.F * am_fov)) * (180.F / hash_constants::pi);
    return max_fov;
}

Vector AM_VUE_POS(const Vector am_pos) {
    Vector max_pos;
    max_pos.x = am_pos.x;
    max_pos.y = -am_pos.z; //switch y with z
    max_pos.z = am_pos.y;
    if (abs(max_pos.x) < 1.e-04F) {
        max_pos.x = 0.F;
    } else {
        max_pos.x /= 10.F;
    }
    if (abs(max_pos.y) < 1.e-04F) {
        max_pos.y = 0.F;
    } else {
        max_pos.y /= 10.F;
    }
    if (abs(max_pos.z) < 1.e-04F) {
        max_pos.z = 0.F;
    } else {
        max_pos.z /= 10.F;
    }
    return max_pos;
}

RotateEuler AM_VUE_ROT(const Quaternion am_rot) {
    RotateEuler re(am_rot.Normalized());
    if (abs(re.x) < 1.e-04F)
        re.x = 0.F;
    if (abs(re.y) < 1.e-04F)
        re.y = 0.F;
    if (abs(re.z) < 1.e-04F)
        re.z = 0.F;
    re.x += 90;
    return re;
}

void CVuePythonApp::WriteOutCamera(HCamera *hcam, FileStream &fs) const {
    Time akt_time;

    HTranslateProperty *htranslate_cam = hcam->GetTransform()->GetTranslate();
    HRotateProperty *hrotate_cam = hcam->GetTransform()->GetRotate();
    GetPropCamera(hcam);

    fs << "DeselectAll()" << nl;
    fs << "cam=StoreCamera()" << nl;
    fs << "SelectByType(VuePython.VUEBasicObject.VOT_Camera)" << nl;
    fs << "cam = GetSelectedObjectByIndex(0)" << nl;
    String name = hcam->GetName();
    name = name.GetNameOnly();
    fs << "cam.SetName(\"" << name.Get() << "\")" << nl;
    for (int frame = para->start; frame <= para->end; ++frame) {
        fs << "SetCurrentFrame(" << frame << ")" << nl;
        akt_time.SetFrame(frame, para->fps);
        //		focal = AM_VUE_FOV(hcam->GetFocalLength()->GetValue(akt_time));
        //		fs << "cam.SetFocal(" << focal << ")" << nl;
        const Vector pos_cam = AM_VUE_POS(htranslate_cam->GetValue(akt_time));
        fs << "cam.SetPosition(" << pos_cam.x << "," << pos_cam.y << "," << pos_cam.z << ")" << nl; //for z up
        const RotateEuler re_cam = AM_VUE_ROT(hrotate_cam->GetValue(akt_time));
        fs << "cam.SetRotationAngles(" << re_cam.x << "," << re_cam.z << "," << re_cam.y << ",true)" << nl; //for z up
    }
    hrotate_cam->GetValue(Time(para->start));
}

void CVuePythonApp::WriteOutLight(HLight *hlight, FileStream &fs) const {
    Time akt_time;

    HTranslateProperty *htranslate_light = hlight->GetTransform()->GetTranslate();
    HRotateProperty *hrotate_light = hlight->GetTransform()->GetRotate();

    fs << "DeselectAll()" << nl;
    GetPropLight(hlight);
    switch (para->light_type) {
        case 0:
            fs << "light=AddPointLight()" << nl;
            break;
        case 1:
            fs << "light=AddDirectionalLight()" << nl;
            break;
        case 2:
            fs << "light=AddSpotLight()" << nl;
            break;
        default:
            fs << "light=AddDirectionalLight()" << nl;
            break;
    }

    String name = hlight->GetName();
    name = name.GetNameOnly();
    fs << "light.SetName(\"" << name.Get() << "\")" << nl;
    fs << "SelectOnly(light)" << nl;
    for (int frame = para->start; frame <= para->end; ++frame) {
        fs << "SetCurrentFrame(" << frame << ")" << nl;
        akt_time.SetFrame(frame, para->fps);
        const Vector pos_cam = AM_VUE_POS(htranslate_light->GetValue(akt_time));
        fs << "light.SetPosition(" << pos_cam.x << "," << pos_cam.y << "," << pos_cam.z << ")" << nl; //for z up
        const RotateEuler re_cam = AM_VUE_ROT(hrotate_light->GetValue(akt_time));
        fs << "light.SetRotationAngles(" << re_cam.x << "," << re_cam.z << "," << re_cam.y << ",true)" << nl; //for z up
        if (para->light_type == 1) {
            const Vector color = hlight->GetColor()->GetValue(akt_time) * 255.;
            fs << "light.SetColor((" << (int)color.x << "," << (int)color.y << "," << (int)color.z << "))" << nl;
        } else {
            fs << "light.SetPower(" << hlight->GetIntensity()->GetValue(akt_time) * 100 << ")" << nl;
        }
    }
    hrotate_light->GetValue(Time(para->start));
}

BOOL CVuePythonApp::OnCamera(HCamera *hcam) {
    FileStream fs;

    para = new W_PARA;
    para->mode = 1;

    HChor *hchor = hcam->GetChor();
    const Time chor_time = hchor->GetTotalTime()->GetValue();

    para->start = 0;
    para->fps = (int)GetHProject()->GetFPS();
    para->end = (int)chor_time.GetFrame(para->fps);
    para->cameraname.Format("%s", ((HCameraCache *)hcam->GetCache())->GetName());
    String temp = para->cameraname.GetBuffer();
    const String path = GetHProject()->GetFileName();
    para->path.Format("%s\\", path.GetPathOnly().Get());
    para->filename.Format("%s\\%s.py", path.GetPathOnly().Get(), temp.Get());

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    temp = para->filename;
    fs.Open(temp.Get(), FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    fs.SetWriteStringCounts(FALSE);
    WriteOutCamera(hcam, fs);
    fs << "DeselectAll()" << nl;
    fs << "SetCurrentFrame (0)" << nl;
    fs << "Refresh()" << nl;
    /*	
    fs << "renderWidth = " << para->width << nl;
    fs << "renderHeight = " << para->height << nl;
    fs << "frameRate = " << para->fps << nl;
    fs << "animationRange = interval 0f " << para->end << "f" << nl;
 
    fs << "in coordsys world animate on" << nl; 
    fs << "(" << nl; 
    fs << "c = freecamera name:\"" << para->cameraname.GetString() << "\"" << nl;
    fs << "c.showRanges = true" << nl;
    fs << "c.rotation.controller = Euler_XYZ()" << nl;
    fs << "c.position.controller = Bezier_Position()" << nl;
    fs << "select c" << nl;
 
    for (frame = para->start;frame<=para->end;++frame) {
    akt_time.SetFrame(frame,para->fps);
    focal = AM_MAX_FOV(hcam->GetFocalLength()->GetValue(akt_time));
    fs << "at time " << frame << "f c.Fov=" << focal << nl;
    rot_cam = AM_MAX_ROT(hrotate_cam->GetValue(akt_time))*mat;
    rot_vec = rot_cam.GetV();
    fs << "at time " << frame << "f c.rotation = ( quat " << -rot_vec.x << " " << rot_vec.y << " " << rot_vec.z << " " << rot_cam.GetW() << ")" << nl;
    //		fs << "at time " << frame << "f c.transform = c.transform * (matrix3 [-1,0,0] [0,0,1] [0,1,0] [0,0,0])" << nl;
    pos_cam = AM_MAX_POS(htranslate_cam->GetValue(akt_time));
    fs << "at time " << frame << "f c.position = [" << pos_cam.x << "," << pos_cam.y << "," << pos_cam.z << "]" << nl;
    }
 
    fs << ")" << nl;
    */
    //	fs.Close();

    delete para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}

BOOL CVuePythonApp::OnLight(HLight *hlight) {
    FileStream fs;

    para = new W_PARA;
    para->mode = 2;

    HChor *hchor = hlight->GetChor();
    const Time chor_time = hchor->GetTotalTime()->GetValue();

    para->start = 0;
    para->fps = (int)GetHProject()->GetFPS();
    para->end = (int)chor_time.GetFrame(para->fps);
    para->cameraname.Format("%s", ((HCameraCache *)hlight->GetCache())->GetName());
    String temp = para->cameraname.GetBuffer();
    const String path = GetHProject()->GetFileName();
    para->path.Format("%s\\", path.GetPathOnly().Get());
    para->filename.Format("%s\\%s.py", path.GetPathOnly().Get(), temp.Get());

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    temp = para->filename;
    fs.Open(temp.Get(), FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    fs.SetWriteStringCounts(FALSE);
    WriteOutLight(hlight, fs);
    fs << "DeselectAll()" << nl;
    fs << "SetCurrentFrame (0)" << nl;
    fs << "Refresh()" << nl;

    delete para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}

BOOL CVuePythonApp::OnChor(HChor *hchor) {
    FileStream fs;

    para = new W_PARA;
    para->mode = 2;

    const Time chor_time = hchor->GetTotalTime()->GetValue();

    para->start = 0;
    para->fps = (int)GetHProject()->GetFPS();
    para->end = (int)chor_time.GetFrame(para->fps);
    para->cameraname.Format("%s", hchor->GetName());

    const String path = GetHProject()->GetFileName();
    para->path.Format("%s\\", path.GetPathOnly().Get());
    String temp = para->cameraname.GetBuffer();
    para->filename.Format("%s\\%s.py", path.GetPathOnly().Get(), temp.Get());

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    temp = para->cameraname;
    fs.Open(temp.Get(), FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    fs.SetWriteStringCounts(FALSE);
    for (HCamera *hcam = hchor->GetChildCamera(); hcam; hcam = hcam->GetNextCameraInChor()) {
        WriteOutCamera(hcam, fs);
    }
    for (HLightListNode *hlightlist = hchor->GetHeadLightList(); hlightlist; hlightlist = hlightlist->GetNextLightListNode()) {
        HLight *hlight = hlightlist->GetLight();
        WriteOutLight(hlight, fs);
    }
    fs << "DeselectAll()" << nl;
    fs << "SetCurrentFrame (0)" << nl;
    fs << "Refresh()" << nl;

    delete para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}

BOOL CVuePythonApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CVuePythonApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
