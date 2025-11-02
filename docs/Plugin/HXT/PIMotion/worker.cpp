// ReSharper disable CppAssignedValueIsNeverUsed
#include "StdAfx.h"
#include "PIMotion.h"

Vector GetModelCenter(HModelCache *modelcache) {
    Vector center;
    HCP *cp;
    HPatch5 *hpatch5;

    modelcache->FindPatches();
    const int azpatch = modelcache->GetPatchCount();
    int azpatch5 = 0;
    for (hpatch5 = modelcache->GetHeadPatch5(); hpatch5; hpatch5 = hpatch5->GetNextPatch5()) {
        azpatch5 ++;
    }

    center.Set(0.F);
    int azcp = 0;

    for (int i = 0; i < azpatch; ++i) {
        HPatch *hpatch = modelcache->GetPatch(i);
        cp = hpatch->GetCP1()->GetHead();
        center += *cp->GetModelPosition();
        cp = hpatch->GetCP2()->GetHead();
        center += *cp->GetModelPosition();
        cp = hpatch->GetCP3()->GetHead();
        center += *cp->GetModelPosition();
        cp = hpatch->GetCP4()->GetHead();
        center += *cp->GetModelPosition();
        azcp += 4;
    }
    if (azpatch5 > 0) {
        for (hpatch5 = modelcache->GetHeadPatch5(); hpatch5; hpatch5 = hpatch5->GetNextPatch5()) {
            cp = hpatch5->GetCP1()->GetHead();
            center += *cp->GetModelPosition();
            cp = hpatch5->GetCP2()->GetHead();
            center += *cp->GetModelPosition();
            cp = hpatch5->GetCP3()->GetHead();
            center += *cp->GetModelPosition();
            cp = hpatch5->GetCP4()->GetHead();
            center += *cp->GetModelPosition();
            cp = hpatch5->GetCP5()->GetHead();
            center += *cp->GetModelPosition();
            azcp += 5;
        }
    }

    center /= (float)azcp;
    return center;
}

Vector GetGroupCenter(HGroup *group) {

    const Matrix34 *groupmatrix = group->GetMatrix();
    const Vector center = groupmatrix->GetTranslate();

    return center;
}

BOOL CPIMotionApp::ChorWorking(HChor *hchor) {

    Vector camera_from, model_pos;
    RotateEuler camera_rotate;
    float focallength;
    Vector model_center, group_center;
    Time time;
    CWaitCursor wait;

    HTransformProperty *htransform_cam = m_para->hcam->GetTransform();
    HTranslateProperty *htranslate_cam = htransform_cam->GetTranslate();
    HRotateProperty *hrotate_cam = htransform_cam->GetRotate();

    HTransformProperty *htransform_obj = m_para->htracking->GetTransform();
    HTranslateProperty *htranslate_obj = htransform_obj->GetTranslate();
    HRotateProperty *hrotate_obj = htransform_obj->GetRotate();
    const double aspectratio = (double)m_para->width / (double)m_para->height;
    int i = 0;
    constexpr double h_pi = 0.5 * hash_constants::double_pi;
    const Time oldtime = hchor->GetTime();

    switch (m_para->trackpoint) {
        case 1:
            //Modelcenter
            model_center = GetModelCenter((HModelCache *)m_para->htracking->GetCache());
            break;
        case 2:
            //GroupPivot
            group_center = GetGroupCenter(m_para->hgroup);
            break;
        default:
            break;
    }
    //    fs.Open( "E:\\cam.txt", FileMode::HS_ASCII);
    fs.Open(m_para->filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    for (float frame = m_para->startframe; frame <= m_para->endframe; frame++, ++i) {
        time.SetFrame(frame, m_para->fps);
        camera_from = htranslate_cam->GetValue(time);
        camera_rotate = RotateEuler(hrotate_cam->GetValue(time));
        focallength = m_para->hcam->GetFocalLength()->GetValue(time);
        Matrix34 camera_local = m_para->hcam->GetLocalMatrix();

        model_pos = htranslate_obj->GetValue(time);
        switch (m_para->trackpoint) {
            case 1:
                //Modelcenter
                model_pos += model_center * hrotate_obj->GetValue(time);
                break;
            case 2:
                model_pos += group_center * hrotate_obj->GetValue(time);
                //Groupcenter
                break;
            default:
                break;
        }
        const Vector model_pos_transformed = model_pos * camera_local.Inverse();

        const double winkel = h_pi - hash_math::atan(2 * focallength / 35.0);
        const double Tx = model_pos_transformed.x / (model_pos_transformed.z * hash_math::tan(winkel)) * -1.;
        const double Ty = model_pos_transformed.y / (model_pos_transformed.z * hash_math::tan(winkel)) * aspectratio * -1.;
        const double Dx = (double)(m_para->width / 2) + (double)(m_para->width / 2) * Tx;
        const double Dy = (double)(m_para->height / 2) + (double)(m_para->height / 2) * Ty;
        fs << i << tab << ROUNDOFF(Dx) << tab << ROUNDOFF(Dy) << nl;
    }

    fs.Close();

    hchor->SetTime(oldtime);
    GetHProject()->SetTime(oldtime);
    model_pos = htranslate_obj->GetValue(oldtime);
    camera_from = htranslate_cam->GetValue(oldtime);
    camera_rotate = RotateEuler(hrotate_cam->GetValue(oldtime));
    focallength = m_para->hcam->GetFocalLength()->GetValue(oldtime);
    return FALSE;
}
