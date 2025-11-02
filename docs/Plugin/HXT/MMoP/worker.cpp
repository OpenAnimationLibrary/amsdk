#include "StdAfx.h"
#include "MMoP.h"
#include <random>

float random_range(const int ra, const float min1, const float max1) {
    if (min1 == 0 && max1 == 0)
        return 0;
    float factor_value;
    if (min1 == 0 && max1 == 1) {
        factor_value = 10000.F;
    } else {
        if (hash_math::abs(max1 - min1) > 100) {
            factor_value = 10.F;
        } else {
            if (hash_math::abs(max1 - min1) > 10) {
                factor_value = 100.F;
            } else {
                factor_value = 1000.F;
            }
        }
    }
    const float min_start = min1 * factor_value;
    const float max_start = max1 * factor_value;
    const int rnd_max = (int)(max_start - min_start);
    const int rnd_wert = ra % rnd_max;
    const float ret_value = min1 + rnd_wert / factor_value;
    return ret_value;
}

void GetBoundsModel(HModelCache *hmc, Vector &min1, Vector &max1, Vector &extents) {
    /*
    HSpline *hsp;
    HCP *cp;
    Vector pos;
    for (hsp = hmc->GetHeadSpline();hsp;hsp = hsp->GetNextSpline()) {
    for (cp = hsp->GetHeadCP();cp;cp = cp->GetNext()) {
    pos = *cp->GetModelPosition();
    PushMinMax(pos,min1,max1);
    if (cp->IsLoop()) break;
    }
    }
    */
    const Vector *bounds = hmc->GetBounds();
    Vector minv(hash_constants::big_float);
    Vector maxv(-hash_constants::big_float);
    for (int j = 0; j < 8; ++j) {
        PushMinMax(bounds[j], minv, maxv);
    }
    min1 = minv;
    max1 = maxv;
    extents.x = (hash_math::abs(min1.x) + hash_math::abs(max1.x)) * 0.5F;
    extents.y = (hash_math::abs(min1.y) + hash_math::abs(max1.y)) * 0.5F;
    extents.z = (hash_math::abs(min1.z) + hash_math::abs(max1.z)) * 0.5F;

}

void CMMoPApp::SetPoses(HModel *hm) {
    HProperty *prop;
    HUserCategoryProperty *hucp = hm->GetUserCategoryProperty();
    if (!hucp)
        return;
    for (int i = 0; (prop = hucp->GetPropertyAt(i)) != nullptr; ++i) {
        if (prop->GetObjectType() == HOT_PERCENT) {
            for (int j = 0; j < para->azprop; ++j) {
                CString t1 = prop->GetName();
                CString t2 = para->props[j]->GetName();
                if (t1 == t2) {
                    const HPercentProperty *hprop = (HPercentProperty *)prop;
                    const HPercentPropertyInfo *hpropinfo = (HPercentPropertyInfo *)hprop->GetPropertyInfo();
                    const float random = random_range(rnd[rndnumber], hpropinfo->GetMinValue(), hpropinfo->GetMaxValue());
                    hprop->StoreValue(Time(), random);
                    rndnumber++;
                }
            }
        }
    }
}

void CMMoPApp::SetAction(HModel *hm) {
    if (para->azaction > 0) {
        const float rv = random_range(rnd1[rndnumber1], 0, (float)para->azaction - 1);
        const int random = ROUNDOFF(rv);
        hm->ApplyAction(para->hac[random]);
        rndnumber1++;
    } else {
        hm->ApplyAction(para->hac[0]);
    }
}

static bool OBBOverlap(const Vector a, const Vector Pa, const Quaternion Aq, const Vector b, const Vector Pb, const Quaternion Bq) {
    /*
        //A
        Vector a, //extents
        Vector Pa, //position
        Quaternion Aq, //orthonormal basis
        //B
        Vector b, //extents
        Vector Pb, //position
        Quaternion Bq //orthonormal basis
    */

    Vector A[3], B[3];
    A[0] = Aq.GetXAxis();
    A[1] = Aq.GetYAxis();
    A[2] = Aq.GetZAxis();
    B[0] = Bq.GetXAxis();
    B[1] = Bq.GetYAxis();
    B[2] = Bq.GetZAxis();
    //translation, in parent frame
    const Vector v = Pb - Pa;
    //translation, in A's frame
    Vector T(v.Dot(A[0]), v.Dot(A[1]), v.Dot(A[2]));
    //B's basis with respect to A's local frame
    float R[3][3];
    float ra, rb, t;
    long i, k;
    //calculate rotation matrix
    for (i = 0; i < 3; ++i) {
        for (k = 0; k < 3; ++k) {
            R[i][k] = A[i].Dot(B[k]);
        }
    }
    /*ALGORITHM: Use the separating axis test for all 15 potential
        separating axes. If a separating axis could not be found, the two
        boxes overlap. */

    //A's basis vectors
    for (i = 0; i < 3; ++i) {
        ra = a[i];
        rb = b[0] * hash_math::abs(R[i][0]) + b[1] * hash_math::abs(R[i][1]) + b[2] * hash_math::abs(R[i][2]);
        t = hash_math::abs(T[i]);
        if (t > ra + rb)
            return false;
    }

    //B's basis vectors
    for (k = 0; k < 3; ++k) {
        ra = a[0] * hash_math::abs(R[0][k]) + a[1] * hash_math::abs(R[1][k]) + a[2] * hash_math::abs(R[2][k]);
        rb = b[k];
        t = hash_math::abs(T[0] * R[0][k] + T[1] * R[1][k] + T[2] * R[2][k]);
        if (t > ra + rb)
            return false;
    }
    //9 cross products
    //L = A0 x B0
    ra = a[1] * hash_math::abs(R[2][0]) + a[2] * hash_math::abs(R[1][0]);
    rb = b[1] * hash_math::abs(R[0][2]) + b[2] * hash_math::abs(R[0][1]);
    t = hash_math::abs(T[2] * R[1][0] - T[1] * R[2][0]);
    if (t > ra + rb)
        return false;
    //L = A0 x B1
    ra = a[1] * hash_math::abs(R[2][1]) + a[2] * hash_math::abs(R[1][1]);
    rb = b[0] * hash_math::abs(R[0][2]) + b[2] * hash_math::abs(R[0][0]);
    t = hash_math::abs(T[2] * R[1][1] - T[1] * R[2][1]);
    if (t > ra + rb)
        return false;
    //L = A0 x B2
    ra = a[1] * hash_math::abs(R[2][2]) + a[2] * hash_math::abs(R[1][2]);
    rb = b[0] * hash_math::abs(R[0][1]) + b[1] * hash_math::abs(R[0][0]);
    t = hash_math::abs(T[2] * R[1][2] - T[1] * R[2][2]);
    if (t > ra + rb)
        return false;
    //L = A1 x B0
    ra = a[0] * hash_math::abs(R[2][0]) + a[2] * hash_math::abs(R[0][0]);
    rb = b[1] * hash_math::abs(R[1][2]) + b[2] * hash_math::abs(R[1][1]);
    t = hash_math::abs(T[0] * R[2][0] - T[2] * R[0][0]);
    if (t > ra + rb)
        return false;
    //L = A1 x B1
    ra = a[0] * hash_math::abs(R[2][1]) + a[2] * hash_math::abs(R[0][1]);
    rb = b[0] * hash_math::abs(R[1][2]) + b[2] * hash_math::abs(R[1][0]);
    t = hash_math::abs(T[0] * R[2][1] - T[2] * R[0][1]);
    if (t > ra + rb)
        return false;
    //L = A1 x B2
    ra = a[0] * hash_math::abs(R[2][2]) + a[2] * hash_math::abs(R[0][2]);
    rb = b[0] * hash_math::abs(R[1][1]) + b[1] * hash_math::abs(R[1][0]);
    t = hash_math::abs(T[0] * R[2][2] - T[2] * R[0][2]);
    if (t > ra + rb)
        return false;
    //L = A2 x B0
    ra = a[0] * hash_math::abs(R[1][0]) + a[1] * hash_math::abs(R[0][0]);
    rb = b[1] * hash_math::abs(R[2][2]) + b[2] * hash_math::abs(R[2][1]);
    t = hash_math::abs(T[1] * R[0][0] - T[0] * R[1][0]);
    if (t > ra + rb)
        return false;
    //L = A2 x B1
    ra = a[0] * hash_math::abs(R[1][1]) + a[1] * hash_math::abs(R[0][1]);
    rb = b[0] * hash_math::abs(R[2][2]) + b[2] * hash_math::abs(R[2][0]);
    t = hash_math::abs(T[1] * R[0][1] - T[0] * R[1][1]);
    if (t > ra + rb)
        return false;
    //L = A2 x B2
    ra = a[0] * hash_math::abs(R[1][2]) + a[1] * hash_math::abs(R[0][2]);
    rb = b[0] * hash_math::abs(R[2][1]) + b[1] * hash_math::abs(R[2][0]);
    t = hash_math::abs(T[1] * R[0][2] - T[0] * R[1][2]);
    if (t > ra + rb)
        return false;  // NOLINT(readability-simplify-boolean-expr)

    /*no separating axis found, the two boxes overlap */
    return true;
}

bool CMMoPApp::Work(HSpline *hsp) {

    srand((unsigned int)time(nullptr) * clock());

    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("MMoP");
        p_bar->SetMessage2("Calculate Positions");
        p_bar->SetProgress(0);
    }

    PVOID oldrinfo = nullptr;
    PVOID newrinfo = nullptr;
    PVOID thread = nullptr;
    Vector min_b(hash_constants::max_float);
    Vector max_b(-hash_constants::max_float);
    Vector extents;
    GetBoundsModel(para->hmc, min_b, max_b, extents);
    if (para->align) {
        para->chor->OpenView(0);
        constexpr float flatness = 0.0016F;
        para->chor->MultIntersect_Init(flatness, oldrinfo, newrinfo, thread);
    }

    HTreeObject *parent = hsp->GetParent();
    do {
        parent = parent->GetParent();
    } while (parent != nullptr && parent->GetObjectType() != HOT_MODEL);

    if (parent != nullptr) {
        auto *hm = (HModel *)parent;
        if (hm)
            hm->MakeCurrent();
    }
    int az_import = 0;
    int j = 0;
    float counter;
    float akt_count;
    MMOP_POSITION pos_temp;
    pos_temp.quat.Set(0.F, 0.707106769F, 0.F, 0.707106769F);
    Vector orig(0.F, 0.F, 1.F);
    Vector direction(0.F, -1.F, 0.F);
    CArray<MMOP_POSITION, MMOP_POSITION> pos_array;
    Vector temp_start, hitp, hitn;
    BOOL found;
    BOOL found1;

    if (para->random == 0) {
        //regular distribution along the path
        az_import = FLOOR_INT(para->spline_length/para->distance);
        if (az_import == 0)
            az_import = 1;
        const float ease = hash_math::rcp((float)az_import);
        counter = 100.F / az_import;
        az_import++;
        for (int i = 0; i < az_import; ++i) {
            if (p_bar) {
                akt_count = counter * i;
                p_bar->SetProgress((int)akt_count);
            }
            hsp->GetPositionAndDirection(ease * i, pos_temp.pos, pos_temp.dir);
            if (para->hm_target)
                pos_temp.pos *= para->hm_target->GetModelToWorldMatrix();
            Vector norm_dir = pos_temp.dir;
            norm_dir.Normalize();

            if (para->align) {
                temp_start = pos_temp.pos;
                temp_start.y += 10000;
                found1 = para->chor->MultIntersect(temp_start, direction, hitp, hitn, hash_constants::big_float, thread);
                //                found1 = para->chor->Intersect(temp_start, direction, hitp, hitn, hash_constants::big_float, 0.016f);
                if (found1) {
#ifdef _DEBUG
                    fsd << "Goodhit" << i + 1 << nl;
#endif
                    hitp.y -= min_b.y;
                    pos_temp.pos = hitp;
                    if (para->store_rotate) {
                        pos_temp.quat = Rotate2VQ(orig, norm_dir) * Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                    } else {
                        pos_temp.quat = Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                    }
                } else {
#ifdef _DEBUG
                    fsd << "Falsehit " << i + 1 << nl;
#endif
                    found1 = para->chor->MultIntersect(temp_start, direction, hitp, hitn, hash_constants::max_float, thread);
                    if (para->store_rotate) {
                        pos_temp.quat = Rotate2VQ(orig, norm_dir);
                    }
                }
            } else {
                if (para->use_offset)
                    pos_temp.pos += para->offset;
                pos_temp.quat = Rotate2VQ(orig, norm_dir);
            }
            pos_array.Add(pos_temp);
        }
    }

    const int maxtries = para->max_az * 500;
    counter = 100.F / maxtries;
    if (para->random == 1) {
        //random distribution along the path
        j = 0;
        //		maxtries = (FLOOR_INT(para->spline_length/smallest_dist(min_b,max_b))+1)*10;
        while (j < maxtries && az_import < para->max_az) {
            if (p_bar) {
                akt_count = counter * j;
                p_bar->SetProgress((int)akt_count);
            }
            hsp->GetPositionAndDirection(random_range(Rnd_RandMax(), 0, 1), pos_temp.pos, pos_temp.dir);
            if (para->hm_target)
                pos_temp.pos *= para->hm_target->GetModelToWorldMatrix();
            if (para->use_offset)
                pos_temp.pos += para->offset;
            if (para->align) {
                temp_start = pos_temp.pos;
                temp_start.y += 10000;
                found1 = para->chor->MultIntersect(temp_start, direction, hitp, hitn, hash_constants::big_float, thread);
                //                found1 = para->chor->Intersect(temp_start,direction,hitp,hitn,hash_constants::max_float,0.0016f);
                if (found1) {
#ifdef _DEBUG
                    fsd << "Goodhit" << nl;
#endif
                    hitp.y -= min_b.y;
                    pos_temp.pos = hitp;
                    if (para->store_rotate) {
                        pos_temp.quat = Rotate2VQ(orig, pos_temp.dir.Normalized()) * Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                    } else {
                        pos_temp.quat = Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                    }
                } else {
#ifdef _DEBUG
                    fsd << "Falsehit" << nl;
#endif
                    if (para->store_rotate) {
                        pos_temp.quat = Rotate2VQ(orig, pos_temp.dir.Normalized());
                    }
                }
            } else {
                if (para->store_rotate) {
                    pos_temp.quat = Rotate2VQ(orig, pos_temp.dir.Normalized());
                }
            }
#ifdef _DEBUG
            fsd << "Pos    " << pos_temp.pos << nl;
#endif
            if (para->allow_overlap) {
                pos_array.Add(pos_temp);
#ifdef _DEBUG
                fsd << "Added" << nl;
#endif
            } else {
                if (pos_array.GetSize() == 0) {
                    pos_array.Add(pos_temp);
                } else {
                    found = false;
                    for (int i = 0; i < pos_array.GetSize(); ++i) {
                        if (OBBOverlap(extents, pos_temp.pos, pos_temp.quat, extents, pos_array[i].pos, pos_array[i].quat)) {
                            //					if (BBox_Intersect(pos_temp.b_min,pos_temp.b_max,pos_array[i].b_min,pos_array[i].b_max)) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        pos_array.Add(pos_temp);
#ifdef _DEBUG
                        fsd << "Added" << nl;
#endif
                    }
                }
            }
            j++;
            az_import = pos_array.GetSize();
        }
    }

    if (para->random == 2) {
        Vector rand_value;
        //random distribution beside the path
        j = 0;
        while (j < maxtries && az_import < para->max_az) {
            if (p_bar) {
                akt_count = counter * j;
                p_bar->SetProgress((int)akt_count);
            }
            hsp->GetPositionAndDirection(random_range(Rnd_RandMax(), 0, 1), pos_temp.pos, pos_temp.dir);
            if (para->hm_target)
                pos_temp.pos *= para->hm_target->GetModelToWorldMatrix();
            rand_value.Set(0.F);
            if (para->offset.x != 0)
                rand_value.x = random_range(Rnd_RandMax(), -para->offset.x, para->offset.x);
            if (para->offset.y != 0)
                rand_value.y = random_range(Rnd_RandMax(), -para->offset.y, para->offset.y);
            if (para->offset.z != 0)
                rand_value.z = random_range(Rnd_RandMax(), -para->offset.z, para->offset.z);
            pos_temp.pos += rand_value;
            if (para->align) {
                temp_start = pos_temp.pos;
                temp_start.y += 10000;
                found1 = para->chor->MultIntersect(temp_start, direction, hitp, hitn, hash_constants::big_float, thread);
                //                found1 = para->chor->Intersect(temp_start,direction,hitp,hitn,hash_constants::max_float,0.0016f);
                if (found1) {
#ifdef _DEBUG
                    fsd << "Goodhit" << nl;
#endif
                    hitp.y -= min_b.y;
                    pos_temp.pos = hitp;
                    if (para->store_rotate) {
                        pos_temp.quat = Rotate2VQ(orig, pos_temp.dir.Normalized()) * Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                    } else {
                        pos_temp.quat = Rotate2VQ(Vector(0.F, 1.F, 0.F), hitn);
                    }
                } else {
#ifdef _DEBUG
                    fsd << "Falsehit" << nl;
#endif
                    if (para->store_rotate) {
                        pos_temp.quat = Rotate2VQ(orig, pos_temp.dir.Normalized());
                    }
                }
            } else {
                if (para->store_rotate) {
                    pos_temp.quat = Rotate2VQ(orig, pos_temp.dir.Normalized());
                }
            }
#ifdef _DEBUG
            fsd << "Pos    " << pos_temp.pos << nl;
#endif
            if (para->allow_overlap) {
                pos_array.Add(pos_temp);
#ifdef _DEBUG
                fsd << "Added" << nl;
#endif
            } else {
                if (pos_array.GetSize() == 0) {
                    pos_array.Add(pos_temp);
                } else {
                    found = false;
                    for (int i = 0; i < pos_array.GetSize(); ++i) {
                        if (OBBOverlap(extents, pos_temp.pos, pos_temp.quat, extents, pos_array[i].pos, pos_array[i].quat)) {
                            //					if (BBox_Intersect(pos_temp.b_min,pos_temp.b_max,pos_array[i].b_min,pos_array[i].b_max)) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        pos_array.Add(pos_temp);
#ifdef _DEBUG
                        fsd << "Added" << nl;
#endif
                    }
                }
            }
            j++;
            az_import = pos_array.GetSize();
        }
    }

    if (para->align) {
        para->chor->MultIntersect_Exit(oldrinfo, newrinfo, thread);
    }

    if (p_bar) {
        p_bar->SetProgress(100);
    }

#ifdef _DEBUG
    fsd << "versuche  " << j << nl;
    fsd << "maxtries  " << maxtries << nl;
    fsd << "az_import " << az_import << nl;
#endif
    if (az_import == 0)
        return false;

    if (para->azprop > 0) {
        SetSeed((unsigned int)time(nullptr) * clock());
        for (int i = 0; i <= (az_import + 1) * (para->azprop + 1); ++i) {
            rnd.Add(Rnd_RandMax());
        }
    }

    if (para->azaction > 0) {
        SetSeed((unsigned int)time(nullptr) * clock());
        for (int i = 0; i < az_import + 1; ++i) {
            rnd1.Add(Rnd_RandMax());
        }
    }

    if (p_bar) {
        p_bar->SetMessage2("Add Models");
        p_bar->SetProgress(0);
    }
    HHashObject *usercontainer = nullptr;
    HModel *sibling = nullptr;
    if (az_import > 0) {
        usercontainer = para->chor->InsertUserFolder();
        usercontainer->SetName("Path models");
    }
    counter = 100.F / az_import;
    for (int i = 0; i < az_import; ++i) {
        if (p_bar) {
            akt_count = counter * i;
            p_bar->SetProgress((int)akt_count);
        }
        HModel *hm1 = para->hmc->NewInstance(para->chor);
        if (hm1) {
            hm1->GetTransform()->GetTranslate()->StoreValue(Time(), pos_array[i].pos, true);
            if (para->store_rotate || para->align) {
                hm1->GetTransform()->GetRotate()->StoreValue(Time(), pos_array[i].quat, true, false);
            }
            if (para->azprop > 0)
                SetPoses(hm1);
            if (para->azaction > 0)
                SetAction(hm1);
            if (usercontainer) {
                hm1->MoveWithChildren(usercontainer, sibling, FALSE);
                sibling = hm1;
            }
        }
    }
    if (p_bar) {
        p_bar->SetMessage2("Finished");
        p_bar->SetProgress(100);
    }
    pos_array.RemoveAll();
    rnd.RemoveAll();
    rnd1.RemoveAll();
    if (p_bar)
        p_bar->Uninitialize();
    return true;
}
