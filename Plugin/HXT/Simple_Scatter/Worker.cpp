#include "StdAfx.h"
#include "Simple_Scatter.h"
#include "SDK/HConstra.h"
#include <random>

void CSimple_ScatterApp::SaveSettings() const {
    SetRegistryValue("Scatter HXT", "copies", para->azimport);
    SetRegistryValue("Scatter HXT", "align", para->align);
    SetRegistryValue("Scatter HXT", "xrot", para->xrotate);
    SetRegistryValue("Scatter HXT", "xr_min", para->rotate_min.x);
    SetRegistryValue("Scatter HXT", "xr_max", para->rotate_max.x);
    SetRegistryValue("Scatter HXT", "yrot", para->yrotate);
    SetRegistryValue("Scatter HXT", "yr_min", para->rotate_min.y);
    SetRegistryValue("Scatter HXT", "yr_max", para->rotate_max.y);
    SetRegistryValue("Scatter HXT", "zrot", para->zrotate);
    SetRegistryValue("Scatter HXT", "zr_min", para->rotate_min.z);
    SetRegistryValue("Scatter HXT", "zr_max", para->rotate_max.z);
    SetRegistryValue("Scatter HXT", "xscale", para->xscale);
    SetRegistryValue("Scatter HXT", "xs_min", para->scale_min.x);
    SetRegistryValue("Scatter HXT", "xs_max", para->scale_max.x);
    SetRegistryValue("Scatter HXT", "yscale", para->yscale);
    SetRegistryValue("Scatter HXT", "ys_min", para->scale_min.y);
    SetRegistryValue("Scatter HXT", "ys_max", para->scale_max.y);
    SetRegistryValue("Scatter HXT", "zscale", para->zscale);
    SetRegistryValue("Scatter HXT", "zs_min", para->scale_min.z);
    SetRegistryValue("Scatter HXT", "zs_max", para->scale_max.z);
    SetRegistryValue("Scatter HXT", "uscale", para->uniformscale);
    SetRegistryValue("Scatter HXT", "us_min", para->uscale_min);
    SetRegistryValue("Scatter HXT", "us_max", para->uscale_max);
    SetRegistryValue("Scatter HXT", "AddBullet", para->add_bullet);
    SetRegistryValue("Scatter HXT", "B_Bounce", para->b_bounce);
    SetRegistryValue("Scatter HXT", "B_Friction", para->b_friction);
    SetRegistryValue("Scatter HXT", "B_Density", para->b_density);
    SetRegistryValue("Scatter HXT", "B_Weight", para->b_weight);
    SetRegistryValue("Scatter HXT", "B_CalcWeight", para->b_calcweight);
    SetRegistryValue("Scatter HXT", "B_Shape", para->b_shape);
}

void CSimple_ScatterApp::GetSettings() const {
    para->azimport = GetRegistryValue("Scatter HXT", "copies", 10);
    para->align = GetRegistryValue("Scatter HXT", "align", FALSE);
    para->xrotate = GetRegistryValue("Scatter HXT", "xrot", FALSE);
    para->rotate_min.x = GetRegistryValue("Scatter HXT", "xr_min", -180.F);
    para->rotate_max.x = GetRegistryValue("Scatter HXT", "xr_max", 180.F);
    para->yrotate = GetRegistryValue("Scatter HXT", "yrot", FALSE);
    para->rotate_min.y = GetRegistryValue("Scatter HXT", "yr_min", -180.F);
    para->rotate_max.y = GetRegistryValue("Scatter HXT", "yr_max", 180.F);
    para->zrotate = GetRegistryValue("Scatter HXT", "zrot", FALSE);
    para->rotate_min.z = GetRegistryValue("Scatter HXT", "zr_min", -180.F);
    para->rotate_max.z = GetRegistryValue("Scatter HXT", "zr_max", 180.F);
    para->xscale = GetRegistryValue("Scatter HXT", "xscale", FALSE);
    para->scale_min.x = GetRegistryValue("Scatter HXT", "xs_min", 80.F);
    para->scale_max.x = GetRegistryValue("Scatter HXT", "xs_max", 120.F);
    para->yscale = GetRegistryValue("Scatter HXT", "yscale", FALSE);
    para->scale_min.y = GetRegistryValue("Scatter HXT", "ys_min", 80.F);
    para->scale_max.y = GetRegistryValue("Scatter HXT", "ys_max", 120.F);
    para->zscale = GetRegistryValue("Scatter HXT", "zscale", FALSE);
    para->scale_min.z = GetRegistryValue("Scatter HXT", "zs_min", 80.F);
    para->scale_max.z = GetRegistryValue("Scatter HXT", "zs_max", 120.F);
    para->uniformscale = GetRegistryValue("Scatter HXT", "uscale", FALSE);
    para->uscale_min = GetRegistryValue("Scatter HXT", "us_min", 80.F);
    para->uscale_max = GetRegistryValue("Scatter HXT", "us_max", 120.F);
    para->add_bullet = GetRegistryValue("Scatter HXT", "AddBullet", FALSE);
    para->b_bounce = GetRegistryValue("Scatter HXT", "B_Bounce", 0.5F);
    para->b_friction = GetRegistryValue("Scatter HXT", "B_Friction", 0.5F);
    para->b_density = GetRegistryValue("Scatter HXT", "B_Density", 0.9998F);
    para->b_weight = GetRegistryValue("Scatter HXT", "B_Weight", 1.F);
    para->b_calcweight = GetRegistryValue("Scatter HXT", "B_CalcWeight", FALSE);
    para->b_shape = GetRegistryValue("Scatter HXT", "B_Shape", 0);
}

bool BBox_Intersect(const Vector box1min, const Vector box1max, const Vector box2min, const Vector box2max) {
    return box1min.x < box2max.x && box1max.x > box2min.x && box1min.y < box2max.y && box1max.y > box2min.y && box1min.z < box2max.z && box1max.z > box2min.z;
}


void GetBBox_ModelCache(HModelCache *hmc, Vector &bbmin, Vector &bbmax) {
    bbmin.Set(hash_constants::max_float);
    bbmax.Set(-hash_constants::max_float);
    for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (HCP *hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
            const Vector pos = *hcp->GetModelPosition();
            pos.PushMinMax( bbmin, bbmax);
            if (hcp->IsLoop())
                break;
        }
    }
}

BOOL GetBBox_Model(HModel *hm, Vector &bbmin, Vector &bbmax) {
    IEPolyModelParms m_iemp;
    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = ST_VARIABLE;
    m_iemp.m_ignorevisibility = TRUE;

    bbmin.Set(hash_constants::max_float);
    bbmax.Set(-hash_constants::max_float);
    IEPolyModel *model = hm->BuildExportModel(&m_iemp, Time(), nullptr);
    const int count = model->m_vertexlist.GetSize();
    for (int j = 0; j < count; ++j) {
        model->m_vertexlist[j].PushMinMax( bbmin, bbmax);
    }
    DeleteIEModel(model);
    if (count > 0)
        return TRUE;
    return FALSE;
}

BOOL GetBBox_Group(HModel *hm, HGroup *hg, Vector &bbmin, Vector &bbmax) {
    IEPolyModelParms m_iemp;
    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = ST_VARIABLE;
    m_iemp.m_ignorevisibility = TRUE;

    bbmin.Set(hash_constants::max_float);
    bbmax.Set(-hash_constants::max_float);
    IEPolyModel *model = hm->BuildExportModel(&m_iemp, Time(), nullptr);
    const int count = model->m_polyarray.GetSize();
    IEPoly **polyarray = model->m_polyarray.GetArray();
    for (int i = 0; i < count; ++i) {
        if (hg->IsPatchInGroup(polyarray[i]->m_origpatch)) {
            model->m_vertexlist[polyarray[i]->m_vertexid[0]].PushMinMax( bbmin, bbmax);
            model->m_vertexlist[polyarray[i]->m_vertexid[1]].PushMinMax( bbmin, bbmax);
            model->m_vertexlist[polyarray[i]->m_vertexid[2]].PushMinMax( bbmin, bbmax);
            if (polyarray[i]->m_vertexid[0] != polyarray[i]->m_vertexid[3]) {
                model->m_vertexlist[polyarray[i]->m_vertexid[3]].PushMinMax( bbmin, bbmax);
            }
        }
    }
    DeleteIEModel(model);
    if (count > 0)
        return TRUE;
    return FALSE;
}

float GetMinValueVector(const Vector p) {
    float minvalue = hash_constants::max_float;
    if (minvalue > p.x)
        minvalue = p.x;
    if (minvalue > p.z)
        minvalue = p.z;
    return minvalue;
}

float GetMaxValueVector(const Vector p) {
    float maxvalue = -hash_constants::max_float;
    if (maxvalue < p.x)
        maxvalue = p.x;
    if (maxvalue < p.z)
        maxvalue = p.z;
    return maxvalue;
}

bool CSimple_ScatterApp::ImportandSimulate() const {
    HChor *hchor = para->hm_target->GetChor();
    hchor->OpenView(0); //Frontview needed
    CWaitCursor wait;
    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("Simple Scatter");
        p_bar->SetMessage2("Init");
        p_bar->SetProgress(0);
    }

    BOOL is_minmax_computed;
    Vector bbmin_static;
    Vector bbmax_static;
    if (para->isgroup) {
        is_minmax_computed = GetBBox_Group(para->hm_target, para->hgroup, bbmin_static, bbmax_static);
    } else {
        is_minmax_computed = GetBBox_Model(para->hm_target, bbmin_static, bbmax_static);
    }
    if (!is_minmax_computed) {
        AfxMessageBox("This plugin needs as target a model\nwith at minimum one patch\nTry using the Multiple Models on Path plugin", MB_OK | MB_ICONSTOP);
        if (p_bar)
            p_bar->Uninitialize();
        return true;
    }

    bbmin_static *= 0.9F;
    bbmax_static *= 0.9F;
    bbmax_static.y += 5000.F;

    Vector bbmin;
    Vector bbmax;
    GetBBox_ModelCache(para->hmc_source, bbmin, bbmax);
    if (p_bar) {
        p_bar->SetMessage2("Import");
    }
    HHashObject *usercontainer = nullptr;
    HModel *sibling = nullptr;
    usercontainer = hchor->InsertUserFolder();
    usercontainer->SetName("Scattered models");

    float counter = 100.F / para->azimport;
    float akt_count = 0.;
    CArray<MODELLIST, MODELLIST &> activelist;
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < para->azimport; ++i) {
        if (p_bar) {
            akt_count = counter * i;
            p_bar->SetProgress((int)akt_count);
        }
        RotateEuler rotate_pos(0.F,0.F,0.F);
        Vector scale_pos(1.F);
        if (para->xrotate) {
            if (para->rotate_min.x != para->rotate_max.x) {
                std::uniform_real_distribution dist(para->rotate_min.x, para->rotate_max.x);
                rotate_pos.x = dist(mt);
            } else {
                rotate_pos.x = para->rotate_min.x;
            }
        }
        if (para->yrotate) {
            if (para->rotate_min.y != para->rotate_max.y) {
                std::uniform_real_distribution dist(para->rotate_min.y, para->rotate_max.y);
                rotate_pos.y = dist(mt);
            } else {
                rotate_pos.y = para->rotate_min.y;
            }
        }
        if (para->zrotate) {
            if (para->rotate_min.z != para->rotate_max.z) {
                std::uniform_real_distribution dist(para->rotate_min.z, para->rotate_max.z);
                rotate_pos.z = dist(mt);
            } else {
                rotate_pos.z = para->rotate_min.z;
            }
        }
        if (para->uniformscale) {
            if (para->uscale_min != para->uscale_max) {
                std::uniform_real_distribution dist(para->uscale_min, para->uscale_max);
                scale_pos.x = scale_pos.y = scale_pos.z = dist(mt) / 100.F;
            } else {
                scale_pos.x = scale_pos.y = scale_pos.z = para->uscale_max / 100.F;
            }
        } else {
            if (para->xscale) {
                if (para->scale_min.x != para->scale_max.x) {
                    std::uniform_real_distribution dist(para->scale_min.x, para->scale_max.x);
                    scale_pos.x = dist(mt) / 100.F;
                } else {
                    scale_pos.x = para->scale_min.x / 100.F;
                }
            }
            if (para->yscale) {
                if (para->scale_min.y != para->scale_max.y) {
                    std::uniform_real_distribution dist(para->scale_min.y, para->scale_max.y);
                    scale_pos.y = dist(mt) / 100.F;
                } else {
                    scale_pos.y = para->scale_min.y / 100.F;
                }
            }
            if (para->zscale) {
                if (para->scale_min.z != para->scale_max.z) {
                    std::uniform_real_distribution dist(para->scale_min.z, para->scale_max.z);
                    scale_pos.z = dist(mt) / 100.F;
                } else {
                    scale_pos.z = para->scale_min.z / 100.F;
                }
            }
        }
        Vector t_bbmin = bbmin * scale_pos;
        Vector t_bbmax = bbmax * scale_pos;
        float minv = GetMinValueVector(t_bbmin);
        float maxv = GetMaxValueVector(t_bbmax);
        t_bbmin.Set(minv);
        t_bbmax.Set(maxv);
        bool found;
        int k = 0;
        Vector start_pos;
        MODELLIST temp_list;
        do {
            found = false;
            std::uniform_real_distribution dist(bbmin_static.x, bbmax_static.x);
            start_pos.x = dist(mt);
            start_pos.y = bbmax_static.y;
            std::uniform_real_distribution dist1(bbmin_static.z, bbmax_static.z);
            start_pos.z = dist1(mt);
            temp_list.bbmin = t_bbmin + start_pos;
            temp_list.bbmax = t_bbmax + start_pos;
            for (int j = 0; j < activelist.GetSize(); ++j) {
                if (BBox_Intersect(temp_list.bbmin, temp_list.bbmax, activelist[j].bbmin, activelist[j].bbmax)) {
                    found = true;
                    break;
                }
            }
            k++;
        } while (found && k < 10000);
        if (k < 10000) {
            Vector hitp;
            Vector hitn;
            Vector direction(0.F, -1.F, 0.F);
            if (hchor->Intersect(start_pos, direction, hitp, hitn, 20000.F, 0.0016F)) {
                if (bbmin.y * scale_pos.y < 0.F) {
                    start_pos.y = hitp.y + hash_math::abs(bbmin.y * scale_pos.y);
                } else {
                    start_pos.y = hitp.y;
                }
                HModel *hm = para->hmc_source->NewInstance(hchor);
                if (para->uniformscale || para->xscale || para->yscale || para->zscale) {
                    HScaleProperty *hsp = hm->GetTransform()->GetScale();
                    hsp->StoreValue(Time(), scale_pos, FALSE);
                }
                if (para->align || para->xrotate || para->yrotate || para->zrotate) {
                    Quaternion quat;
                    if (para->align) {
                        quat = Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                        if (para->yrotate) {
                            rotate_pos.x = 0.F;
                            rotate_pos.z = 0.F;
                            quat = Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn) * (Quaternion)rotate_pos;
                        }
                    } else {
                        quat = (Quaternion)rotate_pos;
                    }
                    HRotateProperty *hrp = hm->GetTransform()->GetRotate();
                    hrp->StoreValue(Time(), quat, TRUE, FALSE);
                }
                HTranslateProperty *htp = hm->GetTransform()->GetTranslate();
                htp->StoreValue(Time(), start_pos, FALSE);
                activelist.Add(temp_list);
                if (usercontainer) {
                    hm->MoveWithChildren(usercontainer, sibling, FALSE);
                    sibling = hm;
                }
                if (para->add_bullet) {
                    if (HBulletConstraint *hb1 = HBulletConstraint::New(hm)) {
                        hb1->GetBounce()->SetValue(para->b_bounce);
                        hb1->GetFriction()->SetValue(para->b_friction);
                        hb1->GetDensity()->SetValue(para->b_density);
                        hb1->GetWeight()->SetValue(para->b_weight);
                        HTypeCategoryProperty *hcp = hb1->GetShapeHull();
                        hcp->SetValue(para->b_shape);
                        hb1->AddSelfAppliedDrivers();
                        if (para->b_calcweight)
                            hb1->CalculateWeight();
                    }
                }
            }
        }
    }
    if (p_bar) {
        p_bar->SetMessage2("Finish");
        p_bar->SetProgress(100);
    }
    if (activelist.GetSize() == 0) {
        AfxMessageBox("Start this plugin from the frontview", MB_OK | MB_ICONSTOP);
    }
    activelist.RemoveAll();
    if (p_bar)
        p_bar->Uninitialize();
    return true;
}
