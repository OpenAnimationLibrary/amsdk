// ReSharper disable once CppUnusedIncludeDirective
#include "StdAfx.h"
#include "EPatch.h"

inline double elength(const Vector v) {
    return hash_math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline double elength(const Vector v1, const Vector v2) {
    return elength(v2 - v1);
}

inline void CalcTangent(const Vector& p0, const Vector& p1, const Vector& p2, const Vector& p3, Vector& t) {
    t = (-p0 - p1 + p2 + p3) * 0.75F;
}

Vector emidPoint(const Vector A, const Vector B) {
    Vector m = A + B;
    m *= 0.5F;
    return m;
}

Vector espMid(const Vector p1, const Vector p2, const Vector p3, const Vector p4) {
    const Vector l2 = emidPoint(p1, p2);
    const Vector h = emidPoint(p2, p3);
    const Vector r3 = emidPoint(p3, p4);
    const Vector l3 = emidPoint(l2, h);
    const Vector r2 = emidPoint(h, r3);
    const Vector c = emidPoint(l3, r2);
    return c;
}

void eGetPatchMid_3(EPatch* ep) {
    Vector pos[16];

    pos[0] = ep->pos[0];
    pos[2] = ep->pos[3];
    pos[4] = ep->pos[6];
    ep->sdpos[1] = pos[1] = espMid(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3]);
    ep->sdpos[2] = pos[3] = espMid(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6]);
    ep->sdpos[3] = pos[5] = espMid(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9]);
    const Vector mp_temp = (pos[1] + pos[3] + pos[5]) / 3.F;
    ep->sdpos[0] = mp_temp;
}

void eGetPatchMid_4(EPatch* ep) {
    Vector pos[16];

    pos[0] = ep->pos[0];
    pos[2] = ep->pos[3];
    pos[4] = ep->pos[6];
    pos[6] = ep->pos[9];
    ep->sdpos[1] = pos[1] = espMid(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3]);
    ep->sdpos[2] = pos[3] = espMid(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6]);
    ep->sdpos[3] = pos[5] = espMid(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9]);
    ep->sdpos[4] = pos[7] = espMid(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[0]);
    Vector mp_temp = (pos[1] - pos[0] + (pos[5] - pos[6])) * 0.5F;
    mp_temp += (pos[1] - pos[2] + (pos[5] - pos[4])) * 0.5F;
    mp_temp += (pos[3] - pos[2] + (pos[7] - pos[0])) * 0.5F;
    mp_temp += (pos[3] - pos[4] + (pos[7] - pos[6])) * 0.5F;
    mp_temp /= 4.F;
    pos[8] = (pos[1] + pos[3] + pos[5] + pos[7]) / 4.F;
    ep->sdpos[0] = pos[8] + mp_temp;
}

void eGetPatchMid_5(EPatch* ep) {
    Vector pos[16];

    pos[0] = ep->pos[0];
    pos[2] = ep->pos[3];
    pos[4] = ep->pos[6];
    pos[6] = ep->pos[9];
    pos[8] = ep->pos[12];
    ep->sdpos[1] = pos[1] = espMid(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3]);
    ep->sdpos[2] = pos[3] = espMid(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6]);
    ep->sdpos[3] = pos[5] = espMid(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9]);
    ep->sdpos[4] = pos[7] = espMid(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[12]);
    ep->sdpos[5] = pos[9] = espMid(ep->pos[12], ep->pos[13], ep->pos[14], ep->pos[0]);
    Vector mp_temp = (pos[1] - pos[0] + (pos[7] - pos[8])) * 0.5F;
    mp_temp += (pos[3] - pos[2] + (pos[9] - pos[0])) * 0.5F;
    mp_temp += (pos[5] - pos[4] + (pos[1] - pos[2])) * 0.5F;
    mp_temp += (pos[7] - pos[6] + (pos[3] - pos[4])) * 0.5F;
    mp_temp += (pos[9] - pos[8] + (pos[5] - pos[6])) * 0.5F;
    mp_temp /= 5.F;
    pos[10] = (pos[1] + pos[3] + pos[5] + pos[7] + pos[9]) / 5.F;
    ep->sdpos[0] = pos[10] + mp_temp;
}

void eGetNormal_3(EPatch* ep) {
    Vector t;
    CalcTangent(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3], t);
    Vector delta1 = ep->pos[0];
    delta1 -= ep->pos[11];
    Vector delta2 = ep->pos[3];
    delta2 -= ep->pos[4];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (ep->opatch->GetCP1()->IsFlip())
        normal1.Negate();
    ep->ndir[1] = normal1;
    CalcTangent(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6], t);
    delta1 = ep->pos[3];
    delta1 -= ep->pos[2];
    delta2 = ep->pos[6];
    delta2 -= ep->pos[7];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (ep->opatch->GetCP2()->IsFlip())
        normal2.Negate();
    ep->ndir[2] = normal2;
    CalcTangent(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[0], t);
    delta1 = ep->pos[6];
    delta1 -= ep->pos[5];
    delta2 = ep->pos[0];
    delta2 -= ep->pos[1];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal3 = Cross(delta1, t);
    normal3.Normalize();
    if (ep->opatch->GetCP3()->IsFlip())
        normal3.Negate();
    ep->ndir[3] = normal3;
    const Vector normal = (normal1 + normal2 + normal3) / 3.F;
    ep->ndir[0] = normal;
}

void eGetNormal_4(EPatch* ep) {
    Vector t;
    CalcTangent(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3], t);
    Vector delta1 = ep->pos[0];
    delta1 -= ep->pos[11];
    Vector delta2 = ep->pos[3];
    delta2 -= ep->pos[4];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (ep->opatch->GetCP1()->IsFlip())
        normal1.Negate();
    ep->ndir[1] = normal1;
    CalcTangent(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6], t);
    delta1 = ep->pos[3];
    delta1 -= ep->pos[2];
    delta2 = ep->pos[6];
    delta2 -= ep->pos[7];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (ep->opatch->GetCP2()->IsFlip())
        normal2.Negate();
    ep->ndir[2] = normal2;
    CalcTangent(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9], t);
    delta1 = ep->pos[6];
    delta1 -= ep->pos[5];
    delta2 = ep->pos[9];
    delta2 -= ep->pos[10];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal3 = Cross(delta1, t);
    normal3.Normalize();
    if (ep->opatch->GetCP3()->IsFlip())
        normal3.Negate();
    ep->ndir[3] = normal3;
    CalcTangent(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[0], t);
    delta1 = ep->pos[9];
    delta1 -= ep->pos[8];
    delta2 = ep->pos[0];
    delta2 -= ep->pos[1];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal4 = Cross(delta1, t);
    normal4.Normalize();
    if (ep->opatch->GetCP4()->IsFlip())
        normal4.Negate();
    ep->ndir[4] = normal4;
    const Vector normal = (normal1 + normal2 + normal3 + normal4) / 4.F;
    ep->ndir[0] = normal;
}

void eGetNormal_5(EPatch* ep) {
    Vector t;
    CalcTangent(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3], t);
    Vector delta1 = ep->pos[0];
    delta1 -= ep->pos[11];
    Vector delta2 = ep->pos[3];
    delta2 -= ep->pos[4];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (ep->opatch5->GetCP1()->IsFlip())
        normal1.Negate();
    ep->ndir[1] = normal1;
    CalcTangent(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6], t);
    delta1 = ep->pos[3];
    delta1 -= ep->pos[2];
    delta2 = ep->pos[6];
    delta2 -= ep->pos[7];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (ep->opatch5->GetCP2()->IsFlip())
        normal2.Negate();
    ep->ndir[2] = normal2;
    CalcTangent(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9], t);
    delta1 = ep->pos[6];
    delta1 -= ep->pos[5];
    delta2 = ep->pos[9];
    delta2 -= ep->pos[10];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal3 = Cross(delta1, t);
    normal3.Normalize();
    if (ep->opatch5->GetCP3()->IsFlip())
        normal3.Negate();
    ep->ndir[3] = normal3;
    CalcTangent(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[12], t);
    delta1 = ep->pos[9];
    delta1 -= ep->pos[8];
    delta2 = ep->pos[12];
    delta2 -= ep->pos[13];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal4 = Cross(delta1, t);
    normal4.Normalize();
    if (ep->opatch5->GetCP4()->IsFlip())
        normal4.Negate();
    ep->ndir[4] = normal4;
    CalcTangent(ep->pos[12], ep->pos[13], ep->pos[14], ep->pos[0], t);
    delta1 = ep->pos[12];
    delta1 -= ep->pos[11];
    delta2 = ep->pos[0];
    delta2 -= ep->pos[1];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal5 = Cross(delta1, t);
    normal5.Normalize();
    if (ep->opatch5->GetCP5()->IsFlip())
        normal5.Negate();
    ep->ndir[5] = normal5;
    const Vector normal = (normal1 + normal2 + normal3 + normal4 + normal5) / 5.F;
    ep->ndir[0] = normal;
}

BOOL EPatch::IsNeighbor(const EPatch* ep, const BOOL side) const {
    if (this == ep)
        return false;
    int found = 0;
    // 2 x 5 pointers
    if (this->numpoint == 5 && ep->numpoint == 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4 || this->pid1 == ep->pid5)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4 || this->pid2 == ep->pid5)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4 || this->pid3 == ep->pid5)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4 || this->pid4 == ep->pid5)
            found++;
        if (this->pid5 == ep->pid1 || this->pid5 == ep->pid2 || this->pid5 == ep->pid3 || this->pid5 == ep->pid4 || this->pid5 == ep->pid5)
            found++;
    }
    // 2 x 4 pointers
    if (this->numpoint == 4 && ep->numpoint == 4) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4)
            found++;
    }
    // 2 x 3 pointers
    if (this->numpoint == 3 && ep->numpoint == 3) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3)
            found++;
    }
    // 5 point - 4 point
    if (this->numpoint == 5 && ep->numpoint != 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4)
            found++;
        if (this->pid5 == ep->pid1 || this->pid5 == ep->pid2 || this->pid5 == ep->pid3 || this->pid5 == ep->pid4)
            found++;
    }
    // 5 point - 3 point
    if (this->numpoint == 5 && ep->numpoint == 3) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3)
            found++;
        if (this->pid5 == ep->pid1 || this->pid5 == ep->pid2 || this->pid5 == ep->pid3)
            found++;
    }
    // 4 point - 3 point
    if (this->numpoint == 4 && ep->numpoint == 3) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3)
            found++;
    }
    // 3 point - 4 point
    if (this->numpoint == 3 && ep->numpoint == 4) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4)
            found++;
    }
    // 4 point - 5 point
    if (this->numpoint == 4 && ep->numpoint == 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4 || this->pid1 == ep->pid5)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4 || this->pid2 == ep->pid5)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4 || this->pid3 == ep->pid5)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4 || this->pid4 == ep->pid5)
            found++;
    }
    // 3 point - 5 point
    if (this->numpoint == 3 && ep->numpoint == 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4 || this->pid1 == ep->pid5)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4 || this->pid2 == ep->pid5)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4 || this->pid3 == ep->pid5)
            found++;
    }
    if (side) {
        if (found > 1) {
            return true; // 1 side neighbor  // NOLINT(readability-simplify-boolean-expr)
        }
        return false;
    }
    if (found > 0) {
        return true; // 1 point neighbor
    }
    return false;
}

UINT EPatch::LowestPID() const {
    UINT pid = this->pid1;
    if (this->pid2 < pid)
        pid = this->pid2;
    if (this->pid3 < pid)
        pid = this->pid3;
    if (this->numpoint == 4) {
        if (this->pid4 < pid)
            pid = this->pid4;
    }
    if (this->numpoint == 5) {
        if (this->pid4 < pid)
            pid = this->pid4;
        if (this->pid5 < pid)
            pid = this->pid5;
    }
    return pid;
}

void EPatch::Init(HPatch* hp) {
    Vector local_pos[16];

    this->opatch5 = nullptr;
    this->opatch = hp;
    const PatchID pid = hp->GetPatchID();
    this->pid1 = pid.m_id1;
    this->pid2 = pid.m_id2;
    this->pid3 = pid.m_id3;
    this->pid4 = pid.m_id4;
    this->pid5 = 0;
    this->isinuse = false;
    hp->GetPatchPoints(local_pos); //works only for frontview
    for (int i = 0; i < 16; ++i) {
        this->pos[i] = local_pos[i];
    }

    this->cppos[1] = local_pos[0];
    this->cppos[2] = local_pos[3];
    this->cppos[3] = local_pos[6];
    switch (hp->GetNumPoints()) {
    case 3:
        this->pid4 = 0;
        this->numpoint = 3;
        this->ishooked = hp->IsUseHook1() || hp->IsUseHook2() || hp->IsUseHook3();
        eGetPatchMid_3(this);
        eGetNormal_3(this);
        this->bb_min[1] = this->bb_max[1] = this->pos[0]; //bbox Subdivided Patch1
        this->sdpos[1].PushMinMax(this->bb_min[1], this->bb_max[1]);
        this->sdpos[0].PushMinMax(this->bb_min[1], this->bb_max[1]);
        this->sdpos[3].PushMinMax(this->bb_min[1], this->bb_max[1]);
        this->bb_min[2] = this->bb_max[2] = this->sdpos[1]; //bbox Subdivided Patch2
        this->pos[3].PushMinMax(this->bb_min[2], this->bb_max[2]);
        this->sdpos[2].PushMinMax(this->bb_min[2], this->bb_max[2]);
        this->sdpos[0].PushMinMax(this->bb_min[2], this->bb_max[2]);
        this->bb_min[3] = this->bb_max[3] = this->sdpos[2]; //bbox Subdivided Patch3
        this->pos[6].PushMinMax(this->bb_min[3], this->bb_max[3]);
        this->sdpos[3].PushMinMax(this->bb_min[3], this->bb_max[3]);
        this->sdpos[0].PushMinMax(this->bb_min[3], this->bb_max[3]);
        this->bb_min[0] = this->bb_max[0] = this->pos[0]; //bbox Patch
        this->pos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->pos[6].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[0].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[1].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[2].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
        break;
    case 4:
        this->cppos[4] = local_pos[9];
        this->numpoint = 4;
        this->ishooked = hp->IsUseHook1() || hp->IsUseHook2() || hp->IsUseHook3() || hp->IsUseHook4();
        eGetPatchMid_4(this);
        eGetNormal_4(this);
        this->bb_min[1] = this->bb_max[1] = this->pos[0]; //bbox Subdivided Patch1
        this->sdpos[1].PushMinMax(this->bb_min[1], this->bb_max[1]);
        this->sdpos[0].PushMinMax(this->bb_min[1], this->bb_max[1]);
        this->sdpos[4].PushMinMax(this->bb_min[1], this->bb_max[1]);
        this->bb_min[2] = this->bb_max[2] = this->sdpos[1]; //bbox Subdivided Patch2
        this->pos[3].PushMinMax(this->bb_min[2], this->bb_max[2]);
        this->sdpos[2].PushMinMax(this->bb_min[2], this->bb_max[2]);
        this->sdpos[0].PushMinMax(this->bb_min[2], this->bb_max[2]);
        this->bb_min[3] = this->bb_max[3] = this->sdpos[2]; //bbox Subdivided Patch3
        this->pos[6].PushMinMax(this->bb_min[3], this->bb_max[3]);
        this->sdpos[3].PushMinMax(this->bb_min[3], this->bb_max[3]);
        this->sdpos[0].PushMinMax(this->bb_min[3], this->bb_max[3]);
        this->bb_min[4] = this->bb_max[4] = this->sdpos[3]; //bbox Subdivided Patch4
        this->pos[9].PushMinMax(this->bb_min[4], this->bb_max[4]);
        this->sdpos[4].PushMinMax(this->bb_min[4], this->bb_max[4]);
        this->sdpos[0].PushMinMax(this->bb_min[4], this->bb_max[4]);
        this->bb_min[0] = this->bb_max[0] = this->pos[0]; //bbox Patch
        this->pos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->pos[6].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->pos[9].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[0].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[1].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[2].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
        this->sdpos[4].PushMinMax(this->bb_min[0], this->bb_max[0]);
        break;
    default:ASSERT(false);
        break;
    }
    this->cppos[0] = this->sdpos[0];
}

void EPatch::Init(HPatch5* hp) {
    Vector local_pos[16];

    this->opatch = nullptr;
    this->opatch5 = hp;
    this->numpoint = 5;
    const PatchID5 pid = hp->GetPatchID();
    this->pid1 = pid.m_id1;
    this->pid2 = pid.m_id2;
    this->pid3 = pid.m_id3;
    this->pid4 = pid.m_id4;
    this->pid5 = pid.m_id5;
    this->isinuse = false;
    hp->GetPatchPoints(local_pos); //works only for frontview
    for (int i = 0; i < 16; ++i) {
        this->pos[i] = local_pos[i];
    }
    this->cppos[1] = local_pos[0];
    this->cppos[2] = local_pos[3];
    this->cppos[3] = local_pos[6];
    this->cppos[4] = local_pos[9];
    this->cppos[5] = local_pos[12];
    this->ishooked = hp->IsUseHook1() || hp->IsUseHook2() || hp->IsUseHook3() || hp->IsUseHook4();
    eGetPatchMid_5(this);
    eGetNormal_5(this);
    this->bb_min[1] = this->bb_max[1] = this->pos[0]; //bbox Subdivided Patch1
    this->sdpos[1].PushMinMax(this->bb_min[1], this->bb_max[1]);
    this->sdpos[0].PushMinMax(this->bb_min[1], this->bb_max[1]);
    this->sdpos[5].PushMinMax(this->bb_min[1], this->bb_max[1]);
    this->bb_min[2] = this->bb_max[2] = this->sdpos[1]; //bbox Subdivided Patch2
    this->pos[3].PushMinMax(this->bb_min[2], this->bb_max[2]);
    this->sdpos[2].PushMinMax(this->bb_min[2], this->bb_max[2]);
    this->sdpos[0].PushMinMax(this->bb_min[2], this->bb_max[2]);
    this->bb_min[3] = this->bb_max[3] = this->sdpos[2]; //bbox Subdivided Patch3
    this->pos[6].PushMinMax(this->bb_min[3], this->bb_max[3]);
    this->sdpos[3].PushMinMax(this->bb_min[3], this->bb_max[3]);
    this->sdpos[0].PushMinMax(this->bb_min[3], this->bb_max[3]);
    this->bb_min[4] = this->bb_max[4] = this->sdpos[3]; //bbox Subdivided Patch4
    this->pos[9].PushMinMax(this->bb_min[4], this->bb_max[4]);
    this->sdpos[4].PushMinMax(this->bb_min[4], this->bb_max[4]);
    this->sdpos[0].PushMinMax(this->bb_min[4], this->bb_max[4]);
    this->bb_min[5] = this->bb_max[5] = this->sdpos[4]; //bbox Subdivided Patch5
    this->pos[12].PushMinMax(this->bb_min[5], this->bb_max[5]);
    this->sdpos[5].PushMinMax(this->bb_min[5], this->bb_max[5]);
    this->sdpos[0].PushMinMax(this->bb_min[5], this->bb_max[5]);
    this->bb_min[0] = this->bb_max[0] = this->pos[0]; //bbox Patch
    this->pos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->pos[6].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->pos[9].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->pos[12].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[0].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[1].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[2].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[4].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[5].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->cppos[0] = this->sdpos[0];
}

EPatch::EPatch(HPatch* hp) {
    Init(hp);
}

EPatch::EPatch(HPatch5* hp) {
    Init(hp);
}

PatchList::PatchList() {
    patchlist.SetSize(0, 100);
    neighborlist.SetSize(0, 100);
}

PatchList::PatchList(const EPatch &epatch) {
    patchlist.Add(epatch);
}

PatchList::PatchList(const NachBar &neighbor) {
    neighborlist.Add(neighbor);
}

void PatchList::LowestID() {
    const int azpatch = patchlist.GetSize();
    UINT lpid = patchlist[0].LowestPID();
    int lowestidpatch = 0;
    for (int i = 1; i < azpatch; ++i) {
        const UINT lpid1 = patchlist[i].LowestPID();
        if (lpid > lpid1) {
            lpid = lpid1;
            lowestidpatch = i;
        }
    }

    if (lowestidpatch > 0) {
        const EPatch ep_temp = patchlist[0];
        patchlist[0] = patchlist[lowestidpatch];
        patchlist[lowestidpatch] = ep_temp;
    }
}

void PatchList::Sort(HProgressBar* p_bar) {
    //ueberarbeiten 
    int j, counter = 0;
    EPatch ep_temp;

    if (p_bar)
        p_bar->SetMessage2("Sorting Patches");

    const int azpatch = patchlist.GetSize();
    const float factor = 100.F / (azpatch - 1);
    if (p_bar) {
        p_bar->SetProgress(counter);
    }
    LowestID();
    for (int i = 0; i < azpatch - 1; ++i) {
        if (p_bar) {
            const int t_counter = (int)(factor * i);
            if (t_counter != counter) {
                counter = t_counter;
                p_bar->SetProgress(counter);
            }
        }
        if (!patchlist[i].IsNeighbor(&patchlist[i + 1], true)) {
            bool found = false;
            for (j = i + 1; j < azpatch; ++j) {
                if (patchlist[i].IsNeighbor(&patchlist[j], true)) {
                    ep_temp = patchlist[i + 1];
                    patchlist[i + 1] = patchlist[j];
                    patchlist[j] = ep_temp;
                    found = true;
                    break;
                }
            }

            if (!found) {
                for (j = i + 1; j < azpatch; ++j) {
                    if (patchlist[i].IsNeighbor(&patchlist[j], false)) {
                        ep_temp = patchlist[i + 1];
                        patchlist[i + 1] = patchlist[j];
                        patchlist[j] = ep_temp;
                        //                        found = true;
                        break;
                    }
                }
            }
        }
    }
}

void PatchList::HitDistance(HProgressBar* p_bar, HModelCache* hmc) {
    HChor* hchor = HChor::New();
    //    HModel *hmodel = hmc->NewInstance(hchor);
    Vector hitp, hitn;
    int counter = 0;
    float length;

    const int azpatch = patchlist.GetSize();
    const float factor = 100.F / (azpatch - 1);
    if (p_bar) {
        p_bar->SetMessage2("Calculate collision distances");
        p_bar->SetProgress(counter);
    }
    for (int i = 0; i < azpatch; ++i) {
        if (p_bar) {
            const int t_counter = (int)(factor * i);
            if (t_counter != counter) {
                counter = t_counter;
                p_bar->SetProgress(counter);
            }
        }
        for (int j = 0; j <= patchlist[i].numpoint; ++j) {
            constexpr float maxdist = 10000.F;
            constexpr float flatness = 0.16f;
            const Vector pos = patchlist[i].cppos[j];
            Vector dir = patchlist[i].ndir[j];
            dir.Negate();
            float factor_l = 0.01f;
            Vector pos1 = pos + dir * factor_l;
            hchor->Intersect(pos1, dir, hitp, hitn, maxdist, flatness);
            while ((length = (float)elength(pos, hitp)) < 0.5f) {
                factor_l *= 2;
                pos1 = pos + dir * factor_l;
                hchor->Intersect(pos1, dir, hitp, hitn, maxdist, flatness);
                if (factor_l > 10000) {
                    break; //prevent endless loop
                }
            }
            if (length < 10000) {
                patchlist[i].dist[j] = length / 2.F;
            }
            else {
                patchlist[i].dist[j] = 1.F;
            }
        }
    }
    HProject::DeleteHandle(hchor);
//    GetHProject()->DeleteHandle(hchor);
}

BOOL IsNeighbor(const EPatch* ep1, const EPatch* ep2, const BOOL side) {
    if (ep1 == ep2)
        return false;
    int found = 0;
    // 2 x 5 pointers
    if (ep1->numpoint == 5 && ep2->numpoint == 5) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3 || ep1->pid1 == ep2->pid4 || ep1->pid1 == ep2->pid5)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3 || ep1->pid2 == ep2->pid4 || ep1->pid2 == ep2->pid5)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3 || ep1->pid3 == ep2->pid4 || ep1->pid3 == ep2->pid5)
            found++;
        if (ep1->pid4 == ep2->pid1 || ep1->pid4 == ep2->pid2 || ep1->pid4 == ep2->pid3 || ep1->pid4 == ep2->pid4 || ep1->pid4 == ep2->pid5)
            found++;
        if (ep1->pid5 == ep2->pid1 || ep1->pid5 == ep2->pid2 || ep1->pid5 == ep2->pid3 || ep1->pid5 == ep2->pid4 || ep1->pid5 == ep2->pid5)
            found++;
    }
    // 2 x 4 pointers
    if (ep1->numpoint == 4 && ep2->numpoint == 4) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3 || ep1->pid1 == ep2->pid4)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3 || ep1->pid2 == ep2->pid4)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3 || ep1->pid3 == ep2->pid4)
            found++;
        if (ep1->pid4 == ep2->pid1 || ep1->pid4 == ep2->pid2 || ep1->pid4 == ep2->pid3 || ep1->pid4 == ep2->pid4)
            found++;
    }
    // 2 x 3 pointers
    if (ep1->numpoint == 3 && ep2->numpoint == 3) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3)
            found++;
    }
    // 5 point - 4 point
    if (ep1->numpoint == 5 && ep2->numpoint != 5) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3 || ep1->pid1 == ep2->pid4)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3 || ep1->pid2 == ep2->pid4)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3 || ep1->pid3 == ep2->pid4)
            found++;
        if (ep1->pid4 == ep2->pid1 || ep1->pid4 == ep2->pid2 || ep1->pid4 == ep2->pid3 || ep1->pid4 == ep2->pid4)
            found++;
        if (ep1->pid5 == ep2->pid1 || ep1->pid5 == ep2->pid2 || ep1->pid5 == ep2->pid3 || ep1->pid5 == ep2->pid4)
            found++;
    }
    // 5 point - 3 point
    if (ep1->numpoint == 5 && ep2->numpoint == 3) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3)
            found++;
        if (ep1->pid4 == ep2->pid1 || ep1->pid4 == ep2->pid2 || ep1->pid4 == ep2->pid3)
            found++;
        if (ep1->pid5 == ep2->pid1 || ep1->pid5 == ep2->pid2 || ep1->pid5 == ep2->pid3)
            found++;
    }
    // 4 point - 3 point
    if (ep1->numpoint == 4 && ep2->numpoint == 3) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3)
            found++;
        if (ep1->pid4 == ep2->pid1 || ep1->pid4 == ep2->pid2 || ep1->pid4 == ep2->pid3)
            found++;
    }
    // 3 point - 4 point
    if (ep1->numpoint == 3 && ep2->numpoint == 4) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3 || ep1->pid1 == ep2->pid4)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3 || ep1->pid2 == ep2->pid4)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3 || ep1->pid3 == ep2->pid4)
            found++;
    }
    // 4 point - 5 point
    if (ep1->numpoint == 4 && ep2->numpoint == 5) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3 || ep1->pid1 == ep2->pid4 || ep1->pid1 == ep2->pid5)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3 || ep1->pid2 == ep2->pid4 || ep1->pid2 == ep2->pid5)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3 || ep1->pid3 == ep2->pid4 || ep1->pid3 == ep2->pid5)
            found++;
        if (ep1->pid4 == ep2->pid1 || ep1->pid4 == ep2->pid2 || ep1->pid4 == ep2->pid3 || ep1->pid4 == ep2->pid4 || ep1->pid4 == ep2->pid5)
            found++;
    }
    // 3 point - 5 point
    if (ep1->numpoint == 3 && ep2->numpoint == 5) {
        if (ep1->pid1 == ep2->pid1 || ep1->pid1 == ep2->pid2 || ep1->pid1 == ep2->pid3 || ep1->pid1 == ep2->pid4 || ep1->pid1 == ep2->pid5)
            found++;
        if (ep1->pid2 == ep2->pid1 || ep1->pid2 == ep2->pid2 || ep1->pid2 == ep2->pid3 || ep1->pid2 == ep2->pid4 || ep1->pid2 == ep2->pid5)
            found++;
        if (ep1->pid3 == ep2->pid1 || ep1->pid3 == ep2->pid2 || ep1->pid3 == ep2->pid3 || ep1->pid3 == ep2->pid4 || ep1->pid3 == ep2->pid5)
            found++;
    }
    if (side) {
        if (found > 1) {
            return true; // 1 side neighbor  // NOLINT(readability-simplify-boolean-expr)
        }
        return false;
    }
    if (found > 0) {
        return true; // 1 point neighbor
    }
    return false;
}

void PatchList::GetNeighbors(HProgressBar* p_bar, const BOOL strict) {
    int counter = 0;
    NachBar nachbar{};

    if (p_bar)
        p_bar->SetMessage2("Search for neighbor patches");
    const int azpatch = patchlist.GetSize();
    const float factor = 100.F / (azpatch - 1);
    if (p_bar) {
        p_bar->SetProgress(counter);
    }
    for (int i = 0; i < azpatch; ++i) {
        if (p_bar) {
            const int t_counter = (int)(factor * i);
            if (t_counter != counter) {
                counter = t_counter;
                p_bar->SetProgress(counter);
            }
        }

        nachbar.azneighbor = 0;
        for (int j = 0; j < azpatch; ++j) {
            if (IsNeighbor(&patchlist[i], &patchlist[j], strict)) {
                nachbar.neighbor[nachbar.azneighbor] = j;
                nachbar.azneighbor++;
            }
        }
        neighborlist.Add(nachbar);
    }
}
