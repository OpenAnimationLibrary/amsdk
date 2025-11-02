// MotCam.cpp : Definiert die Initialisierungsroutinen für die DLL.
//

#include "StdAfx.h"
#include "MotCam.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMotCamApp, CWinApp)
END_MESSAGE_MAP()

CMotCamApp::CMotCamApp() = default;

CMotCamApp::~CMotCamApp() = default;

CMotCamApp theApp;

BOOL CMotCamApp::GetPropRecurseCamera(HProperty *akt_prop) const {
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

void CMotCamApp::GetPropCamera(HHashObject *obj) const {
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

float AM_MAX_FOV(const float am_fov) {
    const float max_fov = 2.F * hash_math::atan(35.F / (2.F * am_fov)) * (180.F / hash_constants::pi);
    return max_fov;
}

Vector AM_MAX_POS(const Vector am_pos) {
    Vector max_pos;
    max_pos.x = am_pos.x;
    max_pos.y = -am_pos.z; //switch y with z
    max_pos.z = am_pos.y;
    return max_pos;
}

Quaternion AM_MAX_ROT(const Quaternion am_rot) {
    RotateEuler re(am_rot);
    re.x *= -1; //negate x
    Quaternion max_rot(re);
    max_rot.Normalize();
    return max_rot;
}

BOOL CMotCamApp::OnCamera(HCamera *hcam) {
    //	float focal;
    Time akt_time;
    FileStream fs;
    Matrix34 mat;
    mat.Set(Vector4(-1, 0, 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 1, 0, 0));

    para = new W_PARA;

//    HTranslateProperty *htranslate_cam = hcam->GetTransform()->GetTranslate();
    HRotateProperty *hrotate_cam = hcam->GetTransform()->GetRotate();

    HChor *hchor = hcam->GetChor();
    Time chor_time = hchor->GetTotalTime()->GetValue();
    const Time start_time = hchor->GetTime();

    GetPropCamera(hcam);
    para->start = 0;
    para->fps = (int)GetHProject()->GetFPS();
    para->end = (int)chor_time.GetFrame(para->fps);
    para->cameraname.Format("%s", ((HCameraCache *)hcam->GetCache())->GetName());

    const String path = GetHProject()->GetFileName();
    para->path.Format("%s\\", path.GetPathOnly().Get());
    String temp = para->cameraname.GetBuffer();
    para->filename.Format("%s\\%s.mot", path.GetPathOnly().Get(), temp.Get());

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return FALSE;
    }

    temp = para->filename;
    fs.Open(temp.Get(), FileMode::HS_BINARY | FileMode::HS_DONTPROGRESS);
    fs.SetWriteStringCounts(FALSE);
    fs << MOTVERSION;
#ifdef _DEBUG 
    String name = "Model";
#else
    String name = ((HCameraCache *)hcam->GetCache())->GetName();
#endif
    name = name.GetNameOnly();
    fs << name.Get() << '\0';
    para->end++;
    chor_time.SetCell(para->end, para->fps);
    fs << (WORD)chor_time.GetCell(para->fps);
    WORD count = 0;
    count++;
    fs << count;
    HBone *bone = hcam;
    name = para->cameraname;
    fs << name.Get() << '\0';
    for (int frame = para->start; frame <= para->end; ++frame) {
        akt_time.SetFrame(frame, para->fps);
        hchor->CreateFrame(akt_time);
        fs << bone->GetLocalMatrix();
    }
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
          fs << "at time " << frame << "f c.fov=" << focal << nl;
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

    hrotate_cam->GetValue(start_time);
    delete para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return false;
}

BOOL CMotCamApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMotCamApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
