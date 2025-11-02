#include "StdAfx.h"
#include "Transfer_AW.h"

float Distance(const Vector v) {
    return v.Norm();
}

float Distance(const Vector v1, const Vector v2) {
    return Distance(v2 - v1);
}

bool PointinBBox(const ALIGN_BBOX &box, const Vector point) {
    if (box.bmax.x < point.x)
        return false;
    if (box.bmax.y < point.y)
        return false;
    if (box.bmax.z < point.z)
        return false;
    if (box.bmin.x > point.x)
        return false;
    if (box.bmin.y > point.y)
        return false;
    if (box.bmin.z > point.z)
        return false;
    return true;
}

void RemoveOldWeight(HCP *cp) {
    CArray<HCPWeight *, HCPWeight *> weightlist;
    weightlist.SetSize(0, 10);
    for (HCPWeight *cpweight = cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
        weightlist.Add(cpweight);
    }
    if (weightlist.GetSize() == 0)
        return;
    for (int i = 0; i < weightlist.GetSize(); ++i) {
        cp->RemoveCPWeight(weightlist[i]);
    }
    weightlist.RemoveAll();
}

int SortWeight(const void *Element0, const void *Element1) {
    //descending
    const auto *pInfo0 = (const MB_WEIGHT *)Element0;
    const auto *pInfo1 = (const MB_WEIGHT *)Element1;
    if (pInfo0->weight < pInfo1->weight)
        return +1;
    if (pInfo0->weight > pInfo1->weight)
        return -1;
    return 0;
}

int SortDist(const void *Element0, const void *Element1) {
    //ascending
    const auto *pInfo0 = (const TAW_DIST *)Element0;
    const auto *pInfo1 = (const TAW_DIST *)Element1;
    if (pInfo0->dist < pInfo1->dist)
        return -1;
    if (pInfo0->dist > pInfo1->dist)
        return +1;
    return 0;
}

int SortDistID(const void *Element0, const void *Element1) {
    //ascending
    const auto *pInfo0 = (const TAW_DIST *)Element0;
    const auto *pInfo1 = (const TAW_DIST *)Element1;
    if (pInfo0->dist < pInfo1->dist)
        return -1;
    if (pInfo0->dist > pInfo1->dist)
        return +1;
    if (pInfo0->cp_id < pInfo1->cp_id)
        return -1;
    if (pInfo0->cp_id > pInfo1->cp_id)
        return +1;
    return 0;
}

int SortBList(const void *Element0, const void *Element1) {
    //descending
    const auto *pInfo0 = (const TAW_DIST *)Element0;
    const auto *pInfo1 = (const TAW_DIST *)Element1;
    if (pInfo0->cp_nr < pInfo1->cp_nr)
        return +1;
    if (pInfo0->cp_nr > pInfo1->cp_nr)
        return -1;
    return 0;
}

void CTransfer_AWApp::Compute_Dist_LoRes(TAW_GROUP_LORES &lores, TAW_HIRES &hires) {
    int i;
    int az_dist = 0;
    for (i = 0; i < lores.cplist.GetSize(); ++i, ++az_dist) {
        _dist[i].dist = hash_math::abs(Distance(cp_list[lores.cplist[i].refer].pos, cp_list[hires.refer].pos));
        if (_dist[i].dist < 1e-5F)
            _dist[i].dist = 1e-5F;
        _dist[i].bone_nr = cp_list[lores.cplist[i].refer].bone_nr;
        _dist[i].cp_id = cp_list[lores.cplist[i].refer].id;
        _dist[i].cp_nr = i;
    }
    qsort(&_dist[0], az_dist, sizeof(TAW_DIST), SortDistID);
    for (i = 0; i < az_dist && i < 16; ++i) {
        hires.lores_dist[i] = _dist[i];
    }
    if (az_dist > 16) {
        hires.az_dist_lores = 16;
    } else {
        hires.az_dist_lores = az_dist;
    }
}

void CTransfer_AWApp::Compute_Dist_HiRes_alternate(TAW_GROUP_HIRES &hires_group, TAW_HIRES &hires) {
    int i;
    int az_dist = 0;
    for (i = 0; i < hires_group.cplist.GetSize(); ++i) {
        if (cp_list[hires_group.cplist[i].refer].id == cp_list[hires.refer].id)
            continue;
        _dist[az_dist].dist = hash_math::abs(Distance(cp_list[hires_group.cplist[i].refer].pos, cp_list[hires.refer].pos));
        if (_dist[az_dist].dist < 1e-5F)
            _dist[az_dist].dist = 1e-5F;
        _dist[az_dist].bone_nr = cp_list[hires_group.cplist[i].refer].bone_nr;
        _dist[az_dist].cp_nr = hires_group.cplist[i].refer;
        _dist[az_dist].cp_id = cp_list[hires_group.cplist[i].refer].id;
        _dist[az_dist].cp_nr_w = i;
        az_dist++;
    }
    qsort(&_dist[0], az_dist, sizeof(TAW_DIST), SortDist);
    for (i = 0; i < az_dist && i < 16; ++i) {
        hires.hires_dist[i] = _dist[i];
    }
    if (az_dist > 16) {
        hires.az_dist_hires = 16;
    } else {
        hires.az_dist_hires = az_dist;
    }
}

void CTransfer_AWApp::Compute_Dist_HiRes(TAW_GROUP_HIRES &hires_group, TAW_HIRES &hires) {
    int i;
    CArrayEx<HSpline *, HSpline *> sp_list;
    HSpline *hsp;
    HCP *cp;
    sp_list.SetSize(0, 10);
    int az_dist = 0;
    for (cp = cp_list[hires.refer].cp->GetHead(); cp; cp = cp->GetNextAttached()) {
        bool found = false;
        hsp = cp->GetSpline();
        for (i = 0; i < sp_list.GetSize(); ++i) {
            if (sp_list[i] == hsp) {
                found = true;
                break;
            }
        }
        if (!found)
            sp_list.Add(hsp);
    }
    for (int j = 0; j < sp_list.GetSize(); ++j) {
        hsp = sp_list[j];
        for (cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
            const HCP *cp1 = cp->GetHead();
            for (i = 0; i < hires_group.cplist.GetSize(); ++i) {
                if (cp1 == cp_list[hires.refer].cp)
                    continue;
                if (cp1 == cp_list[hires_group.cplist[i].refer].cp) {
                    _dist[az_dist].dist = hash_math::abs(Distance(cp_list[hires_group.cplist[i].refer].pos, cp_list[hires.refer].pos));
                    if (_dist[az_dist].dist < 1e-5F)
                        _dist[az_dist].dist = 1e-5F;
                    _dist[az_dist].bone_nr = cp_list[hires_group.cplist[i].refer].bone_nr;
                    _dist[az_dist].cp_nr = hires_group.cplist[i].refer;
                    _dist[az_dist].cp_id = cp_list[hires_group.cplist[i].refer].id;
                    _dist[az_dist].cp_nr_w = i;
                    az_dist++;
                    break;
                }
            }
            if (cp->IsLoop())
                break;
        }
    }

    sp_list.RemoveAll();

    if (az_dist == 0) {
        hires.az_dist_hires = 0;
        return;
    }
    if (az_dist == 1) {
        hires.hires_dist[0] = _dist[0];
        hires.az_dist_hires = 1;
        return;
    }

    qsort(&_dist[0], az_dist, sizeof(TAW_DIST), SortDist);

    for (i = 0; i < az_dist && i < 16; ++i) {
        hires.hires_dist[i] = _dist[i];
    }
    if (az_dist > 16) {
        hires.az_dist_hires = 16;
    } else {
        hires.az_dist_hires = az_dist;
    }
}

int SortBoneAZ(const void *Element0, const void *Element1) {
    //descending
    const auto *pInfo0 = (const TAW_BONESORT *)Element0;
    const auto *pInfo1 = (const TAW_BONESORT *)Element1;
    if (pInfo0->az < pInfo1->az)
        return +1;
    if (pInfo0->az > pInfo1->az)
        return -1;
    return 0;
}

int SortDistBoneAZ(const void *Element0, const void *Element1) {
    const auto *pInfo0 = (const TAW_DIST2 *)Element0;
    const auto *pInfo1 = (const TAW_DIST2 *)Element1;
    if (pInfo0->dist.dist < pInfo1->dist.dist)
        return -1;
    if (pInfo0->dist.dist > pInfo1->dist.dist)
        return +1;
    if (pInfo0->weight < pInfo1->weight)
        return -1;
    if (pInfo0->weight > pInfo1->weight)
        return +1;
    return 0;
}

void CTransfer_AWApp::Resort_Dist_HiRes(TAW_HIRES &hires) {
    if (hires.az_dist_hires < 2)
        return;
    int i;
    CArrayEx<TAW_BONESORT, TAW_BONESORT &> tempbone;
    CArrayEx<TAW_DIST2, TAW_DIST2 &> tempdist;
    TAW_DIST2 temp_dist;
    TAW_BONESORT temp_bone;
    tempbone.SetSize(0, 32);
    tempdist.SetSize(0, 32);
    temp_bone.bone_nr = cp_list[hires.refer].bone_nr;
    temp_bone.az = 1;
    tempbone.Add(temp_bone);
    for (i = 0; i < hires.az_dist_hires - 1; ++i) {
        if (hires.hires_dist[i].dist != hires.hires_dist[i + 1].dist) {
            break;
        }
        bool found = false;
        for (int j = 0; j < tempbone.GetSize(); ++j) {
            if (tempbone[j].bone_nr == hires.hires_dist[i].bone_nr) {
                tempbone[j].az ++;
                found = true;
                break;
            }
        }
        if (!found) {
            temp_bone.bone_nr = hires.hires_dist[i].bone_nr;
            temp_bone.az = 1;
            tempbone.Add(temp_bone);
        }
    }

    qsort(&tempbone[0], tempbone.GetSize(), sizeof(TAW_BONESORT), SortBoneAZ);
    for (i = 0; i < hires.az_dist_hires; ++i) {
        temp_dist.dist = hires.hires_dist[i];
        if (temp_dist.dist.bone_nr == tempbone[0].bone_nr) {
            temp_dist.weight = 0;
        } else {
            temp_dist.weight = 1;
        }
        tempdist.Add(temp_dist);
    }
    qsort(&tempdist[0], tempdist.GetSize(), sizeof(TAW_DIST2), SortDistBoneAZ);
    for (i = 0; i < tempdist.GetSize(); ++i) {
        hires.hires_dist[i] = tempdist[i].dist;
    }

    tempdist.RemoveAll();
    tempbone.RemoveAll();
}

void CTransfer_AWApp::CorrectBones_Dist_Hires(TAW_HIRES &hires) {
    for (int i = 0; i < hires.az_dist_hires; ++i) {
        if (hires.hires_dist[i].bone_nr == -1)
            hires.hires_dist[i].bone_nr = cp_list[hires.hires_dist[i].cp_nr].bone_nr;
    }
}

void CTransfer_AWApp::AssignBones_Hires_FirstPass(TAW_HIRES &hires) {
    for (int i = 0; i < hires.az_dist_lores; ++i) {
        if (PointinBBox(bone_list[hires.lores_dist[i].bone_nr].bbox, cp_list[hires.refer].pos)) {
            for (HCP *cp = cp_list[hires.refer].cp; cp; cp = cp->GetNextAttached()) {
                bone_list[hires.lores_dist[i].bone_nr].hsc->AquireCP(cp);
            }
            cp_list[hires.refer].bone_nr = hires.lores_dist[i].bone_nr;
            hires.isassigned = true;
            break;
        }
    }
}

void CTransfer_AWApp::AssignBones_Hires_SecondPass(TAW_HIRES &hires) {
    int i;
    HCP *cp;
    float dist = hash_constants::max_float;
    int bone_nr = -1;

    if (hires.az_dist_hires > -1) {
        for (i = hires.az_dist_hires - 1; i >= 0; --i) {
            if (hires.hires_dist[i].bone_nr != -1)
                bone_nr = hires.hires_dist[i].bone_nr;
        }
        if (bone_nr != -1) {
            for (cp = cp_list[hires.refer].cp; cp; cp = cp->GetNextAttached()) {
                bone_list[bone_nr].hsc->AquireCP(cp);
            }
            cp_list[hires.refer].bone_nr = bone_nr;
            hires.isassigned = true;
        }
    }

    if (hires.isassigned)
        return;

    for (i = 0; i < bone_list.GetSize(); ++i) {
        const float t_dist = (hash_math::abs(Distance(bone_list[i].start, cp_list[hires.refer].pos)) + hash_math::abs(Distance(bone_list[i].end, cp_list[hires.refer].pos))) * 0.5F;
        if (t_dist < dist) {
            dist = t_dist;
            bone_nr = i;
        }
    }
    if (bone_nr != -1) {
        for (cp = cp_list[hires.refer].cp; cp; cp = cp->GetNextAttached()) {
            bone_list[bone_nr].hsc->AquireCP(cp);
        }
        cp_list[hires.refer].bone_nr = bone_nr;
        hires.isassigned = true;
    }

    if (hires.isassigned)
        return;

    for (i = 0; i < hires.az_dist_lores; ++i) {
        ALIGN_BBOX box = bone_list[hires.lores_dist[i].bone_nr].bbox;
        box.bmax += box.bmax * 0.1F;
        box.bmin += box.bmin * 0.1F;
        if (PointinBBox(box, cp_list[hires.refer].pos)) {
            for (cp = cp_list[hires.refer].cp; cp; cp = cp->GetNextAttached()) {
                bone_list[hires.lores_dist[i].bone_nr].hsc->AquireCP(cp);
            }
            cp_list[hires.refer].bone_nr = hires.lores_dist[i].bone_nr;
            hires.isassigned = true;
            break;
        }
    }

    if (hires.isassigned)
        return;

    for (cp = cp_list[hires.refer].cp; cp; cp = cp->GetNextAttached()) {
        bone_list[hires.lores_dist[0].bone_nr].hsc->AquireCP(cp);
    }
    cp_list[hires.refer].bone_nr = hires.lores_dist[0].bone_nr;
    hires.isassigned = true;
}

void CTransfer_AWApp::CorrectBones_NoFlex(TAW_NOFLEX &noflex) {
    int i;
    int az_dist = 0;
    for (i = 0; i < noflex.refer.GetSize(); ++i) {
        bool found = false;
        for (int j = 0; j < az_dist; ++j) {
            if (cp_list[noflex.refer[i]].bone_nr == _dist[j].bone_nr) {
                _dist[j].cp_nr++;
                found = true;
                break;
            }
        }
        if (!found) {
            _dist[az_dist].bone_nr = cp_list[noflex.refer[i]].bone_nr;
            _dist[az_dist].cp_nr = 1;
            if (az_dist > cp_list.GetSize())
                AfxMessageBox("Memory Allocation Error",MB_OK);
            az_dist++;
        }
    }
    if (az_dist > 0) {
        qsort(&_dist[0], az_dist, sizeof(TAW_DIST), SortBList);
        const int bone_nr = _dist[0].bone_nr;
        for (i = 0; i < noflex.refer.GetSize(); ++i) {
            for (HCP *cp = cp_list[noflex.refer[i]].cp; cp; cp = cp->GetNextAttached()) {
                bone_list[bone_nr].hsc->AquireCP(cp);
            }
            cp_list[noflex.refer[i]].bone_nr = bone_nr;
        }
    }
}

void CTransfer_AWApp::Weight_FirstPass(TAW_GROUP_LORES &lores, TAW_HIRES &hires, int az) {
    if (az > 16)
        az = 16; //maximum number of influencing lores cps
    if (az > hires.az_dist_lores)
        az = hires.az_dist_lores;
    int cp_nr[16], bone_nr[16], i, k;
    float scale[16], value;

    for (i = 0; i < az; ++i) {
        cp_nr[i] = hires.lores_dist[i].cp_nr;
        bone_nr[i] = hires.lores_dist[i].bone_nr;
        scale[i] = hires.lores_dist[0].dist * 100.F / hires.lores_dist[i].dist;
        scale[i] *= 0.01F;
    }
    CArrayEx<MB_WEIGHT, MB_WEIGHT &> wlist;
    MB_WEIGHT tweight;
    bool found;
    for (i = 0; i < az; ++i) {
        if (lores.cplist[cp_nr[i]].has_weight) {
            for (int j = 0; j < lores.cplist[cp_nr[i]].weightlist.GetSize(); ++j) {
                found = false;
                for (k = 0; k < wlist.GetSize(); ++k) {
                    if (wlist[k].hsc == lores.cplist[cp_nr[i]].weightlist[j].hsc) {
                        found = true;
                        wlist[k].weight += lores.cplist[cp_nr[i]].weightlist[j].weight * scale[i];
                        break;
                    }
                }
                if (!found) {
                    value = lores.cplist[cp_nr[i]].weightlist[j].weight * scale[i];
                    if (value > 0.001F) {
                        tweight.hsc = lores.cplist[cp_nr[i]].weightlist[j].hsc;
                        tweight.weight = value;
                        wlist.Add(tweight);
                    }
                }
            }
        } else {
            found = false;
            for (k = 0; k < wlist.GetSize(); ++k) {
                if (wlist[k].hsc == bone_list[bone_nr[i]].hsc) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                value = scale[i];
                if (value > 0.001F) {
                    tweight.hsc = bone_list[bone_nr[i]].hsc;
                    tweight.weight = value;
                    wlist.Add(tweight);
                }
            }
        }
    }

    float factor = 0;
    for (i = 0; i < wlist.GetSize(); ++i) {
        factor += wlist[i].weight;
    }
    factor = hash_math::rcp(factor);
    for (i = 0; i < wlist.GetSize(); ++i) {
        wlist[i].weight *= factor;
    }
    for (i = 0; i < wlist.GetSize(); ++i) {
        hires.weight_first.Add(wlist[i]);
    }
    hires.has_weight = true;
    wlist.RemoveAll();
}

void CTransfer_AWApp::Weight_SecondPass(TAW_GROUP_HIRES &hires_group, TAW_HIRES &hires, int az) {
    if (hires.az_dist_hires == 0)
        return;
    if (az > 16)
        az = 16; //maximum number of influencing lores cps
    if (az > hires.az_dist_hires)
        az = hires.az_dist_hires;
    int cp_nr[16], bone_nr[16], i, k;
    float scale[16], value;

    for (i = 0; i < az; ++i) {
        cp_nr[i] = hires.hires_dist[i].cp_nr_w;
        bone_nr[i] = hires.hires_dist[i].bone_nr;
        scale[i] = hires.hires_dist[0].dist * 100.F / hires.hires_dist[i].dist;
        scale[i] *= 0.01F;
    }
    CArrayEx<MB_WEIGHT, MB_WEIGHT &> wlist;
    MB_WEIGHT tweight;
    bool found;
    for (i = 0; i < az; ++i) {
        if (hires_group.cplist[cp_nr[i]].has_weight) {
            for (int j = 0; j < hires_group.cplist[cp_nr[i]].weight_first.GetSize(); ++j) {
                found = false;
                for (k = 0; k < wlist.GetSize(); ++k) {
                    if (wlist[k].hsc == hires_group.cplist[cp_nr[i]].weight_first[j].hsc) {
                        found = true;
                        wlist[k].weight += hires_group.cplist[cp_nr[i]].weight_first[j].weight * scale[i];
                        break;
                    }
                }
                if (!found) {
                    value = hires_group.cplist[cp_nr[i]].weight_first[j].weight * scale[i];
                    if (value > 0.001F) {
                        tweight.hsc = hires_group.cplist[cp_nr[i]].weight_first[j].hsc;
                        tweight.weight = value;
                        wlist.Add(tweight);
                    }
                }
            }
        } else {
            found = false;
            for (k = 0; k < wlist.GetSize(); ++k) {
                if (wlist[k].hsc == bone_list[bone_nr[i]].hsc) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                value = scale[i];
                if (value > 0.001F) {
                    tweight.hsc = bone_list[bone_nr[i]].hsc;
                    tweight.weight = value;
                    wlist.Add(tweight);
                }
            }
        }
    }

    if (wlist.GetSize() < 2) {
        //nothing to weight
        wlist.RemoveAll();
        return;
    }

    float factor = 0;
    for (i = 0; i < wlist.GetSize(); ++i) {
        factor += wlist[i].weight;
    }
    factor = hash_math::rcp(factor);
    for (i = 0; i < wlist.GetSize(); ++i) {
        wlist[i].weight *= factor;
    }
    for (i = 0; i < wlist.GetSize(); ++i) {
        hires.weight_second.Add(wlist[i]);
    }
    wlist.RemoveAll();
}

void CTransfer_AWApp::Merge_WeightPasses(TAW_HIRES &hires, const float smooth) {
    int i;
    MB_WEIGHT tweight{};
    CArrayEx<MB_WEIGHT, MB_WEIGHT &> wlist;
    for (i = 0; i < hires.weight_first.GetSize(); ++i) {
        wlist.Add(hires.weight_first[i]);
    }
    for (int j = 0; j < hires.weight_second.GetSize(); ++j) {
        bool found = false;
        for (i = 0; i < wlist.GetSize(); ++i) {
            if (wlist[i].hsc == hires.weight_second[j].hsc) {
                wlist[i].weight += hires.weight_second[j].weight * smooth;
                found = true;
                break;
            }
        }
        if (!found) {
            tweight.hsc = hires.weight_second[j].hsc;
            tweight.weight = hires.weight_second[j].weight * smooth;
            wlist.Add(tweight);
        }
    }

    if (wlist.GetSize() < 2) {
        //nothing to weight
        wlist.RemoveAll();
        return;
    }

    float factor = 0;
    for (i = 0; i < wlist.GetSize(); ++i) {
        factor += wlist[i].weight;
    }
    factor = hash_math::rcp(factor);
    for (i = 0; i < wlist.GetSize(); ++i) {
        wlist[i].weight *= factor;
    }
    hires.weight_first.RemoveAll();
    hires.weight_second.RemoveAll();
    for (i = 0; i < wlist.GetSize(); ++i) {
        hires.weight_first.Add(wlist[i]);
    }
    wlist.RemoveAll();
}

void CTransfer_AWApp::CorrectWeight_NoFlex(TAW_NOFLEX &noflex) {
    int i, j;
    CArrayEx<MB_WEIGHT, MB_WEIGHT &> wlist;

    for (i = 0; i < noflex.ref.GetSize(); ++i) {
        for (j = 0; j < group_pair[noflex.ref[i].group_nr].hires.cplist[noflex.ref[i].cp_nr].weight_first.GetSize(); ++j) {
            bool found = false;
            for (int h = 0; h < wlist.GetSize(); ++h) {
                if (wlist[h].hsc == group_pair[noflex.ref[i].group_nr].hires.cplist[noflex.ref[i].cp_nr].weight_first[j].hsc) {
                    wlist[h].weight += group_pair[noflex.ref[i].group_nr].hires.cplist[noflex.ref[i].cp_nr].weight_first[j].weight;
                    found = true;
                    break;
                }
            }
            if (!found) {
                wlist.Add(group_pair[noflex.ref[i].group_nr].hires.cplist[noflex.ref[i].cp_nr].weight_first[j]);
            }
        }
    }
    if (wlist.GetSize() < 2) {
        //nothing to weight
        wlist.RemoveAll();
        return;
    }
    float factor = 0;
    for (i = 0; i < wlist.GetSize(); ++i) {
        factor += wlist[i].weight;
    }
    factor = hash_math::rcp(factor);
    for (i = 0; i < wlist.GetSize(); ++i) {
        wlist[i].weight *= factor;
    }
    for (i = 0; i < noflex.ref.GetSize(); ++i) {
        group_pair[noflex.ref[i].group_nr].hires.cplist[noflex.ref[i].cp_nr].weight_first.RemoveAll();
        for (j = 0; j < wlist.GetSize(); ++j) {
            group_pair[noflex.ref[i].group_nr].hires.cplist[noflex.ref[i].cp_nr].weight_first.Add(wlist[j]);
        }
    }
    wlist.RemoveAll();
}

void CTransfer_AWApp::Assign_Weight(TAW_HIRES &hires) {
    int i;
    CArrayEx<MB_WEIGHT, MB_WEIGHT &> wlist;

    RemoveOldWeight(cp_list[hires.refer].cp); //remove existing weights , if there are some

    for (i = 0; i < hires.weight_first.GetSize(); ++i) {
        wlist.Add(hires.weight_first[i]);
    }

    if (wlist.GetSize() < 2) {
        wlist.RemoveAll();
        return;
    }

    qsort(&wlist[0], wlist.GetSize(), sizeof(MB_WEIGHT), SortWeight);
    if (wlist[0].hsc != bone_list[cp_list[hires.refer].bone_nr].hsc) {
        //the first weight assigned to a cp must be the weight for the assigned bone, equal which weightvalue he has
        for (i = 0; i < wlist.GetSize(); ++i) {
            if (wlist[i].hsc == bone_list[cp_list[hires.refer].bone_nr].hsc) {
                const MB_WEIGHT tweight = wlist[i];
                for (int j = i; j > 0; --j) {
                    wlist[j] = wlist[j - 1];
                }
                wlist[0] = tweight;
            }
        }
    }
    HCPWeight *cpweight = nullptr;
    for (i = 0; i < wlist.GetSize(); ++i) {
        if (i == 0) {
            cpweight = cp_list[hires.refer].cp->AddCPWeight();
            cpweight->SetSegmentCache(wlist[i].hsc);
            cpweight->SetWeight(wlist[i].weight);
        } else {
            if (i != 1) {
                cpweight = cp_list[hires.refer].cp->AddCPWeight();
            }
            cpweight->SetSegmentCache(wlist[i].hsc);
            cpweight->SetWeight(wlist[i].weight);
        }
    }
    wlist.RemoveAll();
}

#ifdef _DEBUG
void CTransfer_AWApp::Debugoutput(TAW_HIRES hires) {
    const UINT id = cp_list[hires.refer].id;
    if (id != 80 && id != 81 && id != 82 && id != 83 && id != 84)
        return;
    fsd << nl << "Weights for CP #" << id << nl;
    for (int i = 0; i < hires.weight_first.GetSize(); ++i) {
        fsd << hires.weight_first[i].hsc->GetName() << "   " << fround(hires.weight_first[i].weight *100.F,2) << nl;
    }

}
#endif

void CTransfer_AWApp::Work(HModelCache *hmc) {
    int i, j;
    float akt_count;
    int k = cp_list.GetSize();
    k += k / 10;
    _dist = new TAW_DIST[k];
    ASSERT(_dist);
    //distances 
    if (para->p_bar) {
        para->p_bar->SetMessage2("Compute Distances");
        para->p_bar->SetProgress(0);
    }

    int az_count = 0;
    for (i = 0; i < group_pair.GetSize(); ++i) {
        az_count += group_pair[i].hires.cplist.GetSize() - 1;
    }
    float counter = 100.F / az_count;
    const float old_count = counter;
    int h = 0;
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            Compute_Dist_LoRes(group_pair[i].lores, group_pair[i].hires.cplist[j]);
            if (!para->alternate_hiresdist) {
                Compute_Dist_HiRes(group_pair[i].hires, group_pair[i].hires.cplist[j]);
            } else {
                Compute_Dist_HiRes_alternate(group_pair[i].hires, group_pair[i].hires.cplist[j]);
            }
        }
    }

    //first pass boning
    if (para->p_bar) {
        para->p_bar->SetMessage2("Assign Bones");
    }
    h = 0;
    counter /= 3.F;
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            AssignBones_Hires_FirstPass(group_pair[i].hires.cplist[j]);
        }
    }

    //correct the hires_dist bones
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            CorrectBones_Dist_Hires(group_pair[i].hires.cplist[j]);
        }
    }

    //second pass boning
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            if (!group_pair[i].hires.cplist[j].isassigned)
                AssignBones_Hires_SecondPass(group_pair[i].hires.cplist[j]);
        }
    }

    //correct boning for no-flex groups
    if (para->has_noflex) {
        if (para->p_bar) {
            para->p_bar->SetMessage2("Correct Bones NoFlex Groups");
        }
        counter = 100.F / flex_list.GetSize() - 1;
        for (i = 0; i < flex_list.GetSize(); ++i) {
            if (para->p_bar) {
                akt_count = counter * i;
                para->p_bar->SetProgress((int)akt_count);
            }
            CorrectBones_NoFlex(flex_list[i]);
        }
    }
    delete _dist;

    //resort hires distances in adjedance with bones  
    if (para->p_bar) {
        para->p_bar->SetMessage2("Sort Distances");
    }
    h = 0;
    counter = old_count;
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            Resort_Dist_HiRes(group_pair[i].hires.cplist[j]);
        }
    }

    hmc->SetChanged(TRUE);
    //weighting first pass
    if (para->p_bar) {
        para->p_bar->SetMessage2("Weight First Pass");
    }
    h = 0;
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            Weight_FirstPass(group_pair[i].lores, group_pair[i].hires.cplist[j], para->pass1_cp);
        }
    }

    if (para->smooth > 0.F) {
        if (para->p_bar) {
            para->p_bar->SetMessage2("Weight Second Pass");
        }
        counter = 100.F / para->az_smoothpass;
        for (i = 0; i < group_pair.GetSize(); ++i) {
            for (k = 0; k < para->az_smoothpass; ++k) {
                if (para->p_bar) {
                    akt_count = counter * k;
                    para->p_bar->SetProgress((int)akt_count);
                }
                for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j) {
                    Weight_SecondPass(group_pair[i].hires, group_pair[i].hires.cplist[j], para->pass2_cp);
                }
                for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j) {
                    Merge_WeightPasses(group_pair[i].hires.cplist[j], para->smooth);
                }
            }
            //#ifdef _DEBUG			
            //		for (j=0;j<group_pair[i].hires.cplist.GetSize();++j) {
            //			Debugoutput(group_pair[i].hires.cplist[j]);	
            //		}	
            //#endif			
        }
    }

    //correct weight for no-flex groups
    if (para->has_noflex) {
        if (para->p_bar) {
            para->p_bar->SetMessage2("Correct Weighting NoFlex Groups");
        }
        counter = 100.F / flex_list.GetSize() - 1;
        for (i = 0; i < flex_list.GetSize(); ++i) {
            if (para->p_bar) {
                akt_count = counter * i;
                para->p_bar->SetProgress((int)akt_count);
            }
            CorrectWeight_NoFlex(flex_list[i]);
        }
    }

    //assign weighting
    if (para->p_bar) {
        para->p_bar->SetMessage2("Assign Weights");
    }
    h = 0;
    counter = old_count;
    for (i = 0; i < group_pair.GetSize(); ++i, ++h) {
        for (j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j, ++h) {
            if (para->p_bar) {
                akt_count = counter * h;
                para->p_bar->SetProgress((int)akt_count);
            }
            Assign_Weight(group_pair[i].hires.cplist[j]);
        }
    }

    if (para->p_bar) {
        para->p_bar->SetMessage2("Finished");
        para->p_bar->SetProgress(100);
    }
    hmc->SetChanged(TRUE);
}
