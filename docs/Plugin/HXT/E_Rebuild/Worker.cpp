#include "StdAfx.h"
#include "E_Rebuild.h"
#include <random>

inline void CalcTangent(const Vector &p0, const Vector &p1, const Vector &p2, const Vector &p3, Vector &t) {
    t = (-p0 - p1 + p2 + p3) * 0.75F;
}


void BBox(GRUPPE *gruppe, Vector &mid, Vector &m_min, Vector &m_max) {
    Vector max, min;
    min.Set(hash_constants::max_float);
    max.Set(-hash_constants::max_float);
    mid.Set(0.F);
    for (int i = 0; i < gruppe->patchlist_new.GetSize(); ++i) {
        for (int j = 0; j < gruppe->patchlist_new[i].numpoint; ++j) {
            gruppe->patchlist_new[i].cppos[j].PushMinMax(min, max);
        }
    }
    min.PushMinMax(m_min, m_max);
    max.PushMinMax(m_min, m_max);
    mid = (max + min) * 0.5F;
}

double plength(const Vector v) {
    return hash_math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double plength(const Vector v1, const Vector v2) {
    return plength(v2 - v1);
}

Vector Normal_Patch(HPatch *hp) {
    Vector t;
    Vector normal, normal3;
    Vector pos[16];
    const int azpoint = hp->GetNumPoints();
    normal.Set(0.F);

    pos[0] = *hp->GetCP1()->GetModelPosition();
    pos[1] = hp->GetIT1();
    pos[2] = hp->GetOT1();
    pos[3] = *hp->GetCP2()->GetModelPosition();
    pos[4] = hp->GetIT2();
    pos[5] = hp->GetOT2();
    pos[6] = *hp->GetCP3()->GetModelPosition();
    pos[7] = hp->GetIT3();
    pos[8] = hp->GetOT3();
    if (azpoint == 4) {
        pos[9] = *hp->GetCP4()->GetModelPosition();
        pos[10] = hp->GetIT4();
        pos[11] = hp->GetOT4();
    }

    CalcTangent(pos[0], pos[1], pos[2], pos[3], t);
    Vector delta1 = pos[0];
    delta1 -= pos[11];
    Vector delta2 = pos[3];
    delta2 -= pos[4];
    delta1 += delta2;
    delta1 *= .5F;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (hp->GetCP1()->IsFlip())
        normal1.Negate();
    CalcTangent(pos[3], pos[4], pos[5], pos[6], t);
    delta1 = pos[3];
    delta1 -= pos[2];
    delta2 = pos[6];
    delta2 -= pos[7];
    delta1 += delta2;
    delta1 *= .5F;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (hp->GetCP2()->IsFlip())
        normal2.Negate();
    if (azpoint == 4) {
        CalcTangent(pos[6], pos[7], pos[8], pos[9], t);
        delta1 = pos[6];
        delta1 -= pos[5];
        delta2 = pos[9];
        delta2 -= pos[10];
        delta1 += delta2;
        delta1 *= .5F;
        normal3 = Cross(delta1, t);
        normal3.Normalize();
        if (hp->GetCP3()->IsFlip())
            normal3.Negate();
        CalcTangent(pos[9], pos[10], pos[11], pos[0], t);
        delta1 = pos[9];
        delta1 -= pos[8];
        delta2 = pos[0];
        delta2 -= pos[1];
        delta1 += delta2;
        delta1 *= .5F;
        Vector normal4 = Cross(delta1, t);
        normal4.Normalize();
        if (hp->GetCP4()->IsFlip())
            normal4.Negate();
        normal = (normal1 + normal2 + normal3 + normal4) / 4.F;
    } else {
        CalcTangent(pos[6], pos[7], pos[8], pos[0], t);
        delta1 = pos[6];
        delta1 -= pos[5];
        delta2 = pos[9];
        delta2 -= pos[10];
        delta1 += delta2;
        delta1 *= .5F;
        normal3 = Cross(delta1, t);
        normal3.Normalize();
        if (hp->GetCP3()->IsFlip())
            normal3.Negate();
        normal = (normal1 + normal2 + normal3) / 3.F;
    }
    return normal;
}

bool CheckToCreate(const Vector p0, const Vector p1, const Vector p2, GRUPPE *gruppe) {

    int azpoint = gruppe->pointlist.GetSize();
    if (azpoint < 3)
        return TRUE;
    azpoint -= 2;
    for (int i = 0; i < azpoint; i += 3) {
        if (gruppe->pointlist[i].cp && gruppe->pointlist[i + 1].cp && gruppe->pointlist[i + 2].cp) {
            int found = 0;
            if (p0 == gruppe->pointlist[i].pos)
                found ++;
            if (p0 == gruppe->pointlist[i + 1].pos)
                found ++;
            if (p0 == gruppe->pointlist[i + 2].pos)
                found ++;
            if (p1 == gruppe->pointlist[i].pos)
                found ++;
            if (p1 == gruppe->pointlist[i + 1].pos)
                found ++;
            if (p1 == gruppe->pointlist[i + 2].pos)
                found ++;
            if (p2 == gruppe->pointlist[i].pos)
                found ++;
            if (p2 == gruppe->pointlist[i + 1].pos)
                found ++;
            if (p2 == gruppe->pointlist[i + 2].pos)
                found ++;
            if (found > 2)
                return FALSE;
        }
    }
    return TRUE;
}

void RebuildPatch4(HModelCache *hmc_new, GRUPPE *gruppe, const int patchnr) {
    HSpline *hsp[6];
    NPOINT new_point;
    // 4 Point
    // pos0 pos1 pos2
    // pos7 pos8 pos3
    // pos6 pos5 pos4

    // cp1 sd1 cp2
    // sd4 cp0 sd2
    // cp4 sd3 cp3

    new_point.attached = FALSE;
    new_point.referpatch = patchnr;
    new_point.ismid = FALSE;
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[1], gruppe->patchlist_org[patchnr].sdpos[1], gruppe->patchlist_org[patchnr].cppos[2], gruppe)) {
        hsp[0] = hmc_new->CreateSpline();
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }

    if (CheckToCreate(gruppe->patchlist_org[patchnr].sdpos[4], gruppe->patchlist_org[patchnr].cppos[0], gruppe->patchlist_org[patchnr].sdpos[2], gruppe)) {
        hsp[1] = hmc_new->CreateSpline();
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
        new_point.ismid =TRUE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[2];
        new_point.ismid = FALSE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }

    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[4], gruppe->patchlist_org[patchnr].sdpos[3], gruppe->patchlist_org[patchnr].cppos[3], gruppe)) {
        hsp[2] = hmc_new->CreateSpline();
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }

    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[4], gruppe->patchlist_org[patchnr].sdpos[4], gruppe->patchlist_org[patchnr].cppos[1], gruppe)) {
        hsp[3] = hmc_new->CreateSpline();
        new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }

    if (CheckToCreate(gruppe->patchlist_org[patchnr].sdpos[3], gruppe->patchlist_org[patchnr].cppos[0], gruppe->patchlist_org[patchnr].sdpos[1], gruppe)) {
        hsp[4] = hmc_new->CreateSpline();
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
        new_point.ismid =TRUE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[1];
        new_point.ismid = FALSE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }

    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[3], gruppe->patchlist_org[patchnr].sdpos[2], gruppe->patchlist_org[patchnr].cppos[2], gruppe)) {
        hsp[5] = hmc_new->CreateSpline();
        new_point.cp = hsp[5]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[5]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[5]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
}

void RebuildPatch3(HModelCache *hmc_new, GRUPPE *gruppe, const int patchnr) {
    HSpline *hsp[6];
    NPOINT new_point;

    // 3Point
    // pos0	  pos1	 pos2
    //	 pos5 pos6 pos3
    //        pos4
    // cp1  sd1  cp2
    //  sd3 cp0 sd2
    //      cp3
    new_point.attached = FALSE;
    new_point.referpatch = patchnr;
    new_point.ismid = FALSE;
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[1], gruppe->patchlist_org[patchnr].sdpos[1], gruppe->patchlist_org[patchnr].cppos[2], gruppe)) {
        hsp[0] = hmc_new->CreateSpline();
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].sdpos[3], gruppe->patchlist_org[patchnr].cppos[0], gruppe->patchlist_org[patchnr].sdpos[2], gruppe)) {
        hsp[1] = hmc_new->CreateSpline();
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
        new_point.ismid =TRUE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[2];
        new_point.ismid = FALSE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[1], gruppe->patchlist_org[patchnr].sdpos[3], gruppe->patchlist_org[patchnr].cppos[3], gruppe)) {
        hsp[2] = hmc_new->CreateSpline();
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }

    hsp[3] = hmc_new->CreateSpline();
    new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[1]);
    new_point.pos = gruppe->patchlist_org[patchnr].sdpos[1];
    gruppe->pointlist.Add(new_point);
    gruppe->hgroup->AddCP(new_point.cp);
    new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
    new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
    new_point.ismid =TRUE;
    gruppe->pointlist.Add(new_point);
    gruppe->hgroup->AddCP(new_point.cp);
    new_point.cp = nullptr;
    new_point.ismid = FALSE;
    new_point.pos.Set(0.F);
    gruppe->pointlist.Add(new_point);

    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[2], gruppe->patchlist_org[patchnr].sdpos[2], gruppe->patchlist_org[patchnr].cppos[3], gruppe)) {
        hsp[4] = hmc_new->CreateSpline();
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
}

void RebuildPatch5(HModelCache *hmc_new, GRUPPE *gruppe, const int patchnr) {
    HSpline *hsp[8];
    NPOINT new_point;
    // 5Point
    //        pos2 
    //     pos1   pos3
    // pos0   pos10  pos4
    //  pos9        pos5
    //   pos8 pos7 pos6

    new_point.attached = FALSE;
    new_point.referpatch = patchnr;
    new_point.ismid = FALSE;
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[1], gruppe->patchlist_org[patchnr].sdpos[1], gruppe->patchlist_org[patchnr].cppos[2], gruppe)) {
        hsp[0] = hmc_new->CreateSpline();
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[0]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[2], gruppe->patchlist_org[patchnr].sdpos[2], gruppe->patchlist_org[patchnr].cppos[3], gruppe)) {
        hsp[1] = hmc_new->CreateSpline();
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[1]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[3], gruppe->patchlist_org[patchnr].sdpos[3], gruppe->patchlist_org[patchnr].cppos[4], gruppe)) {
        hsp[2] = hmc_new->CreateSpline();
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[3];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[2]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[4], gruppe->patchlist_org[patchnr].sdpos[4], gruppe->patchlist_org[patchnr].cppos[5], gruppe)) {
        hsp[3] = hmc_new->CreateSpline();
        new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[4]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[4];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[3]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[5]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[5];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].cppos[5], gruppe->patchlist_org[patchnr].sdpos[5], gruppe->patchlist_org[patchnr].cppos[1], gruppe)) {
        hsp[4] = hmc_new->CreateSpline();
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[5]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[5];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[5]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[5];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[4]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].sdpos[1], gruppe->patchlist_org[patchnr].cppos[0], gruppe->patchlist_org[patchnr].sdpos[3], gruppe)) {
        hsp[5] = hmc_new->CreateSpline();
        new_point.cp = hsp[5]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[1]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[1];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[5]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
        new_point.ismid =TRUE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[5]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[3]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[3];
        new_point.ismid = FALSE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    if (CheckToCreate(gruppe->patchlist_org[patchnr].sdpos[2], gruppe->patchlist_org[patchnr].cppos[0], gruppe->patchlist_org[patchnr].sdpos[5], gruppe)) {
        hsp[6] = hmc_new->CreateSpline();
        new_point.cp = hsp[6]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[2]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[2];
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[6]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
        new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
        new_point.ismid =TRUE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
        new_point.cp = hsp[6]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[5]);
        new_point.pos = gruppe->patchlist_org[patchnr].sdpos[5];
        new_point.ismid = FALSE;
        gruppe->pointlist.Add(new_point);
        gruppe->hgroup->AddCP(new_point.cp);
    }
    hsp[7] = hmc_new->CreateSpline();
    new_point.cp = hsp[7]->CreateCPAtTail(gruppe->patchlist_org[patchnr].cppos[0]);
    new_point.pos = gruppe->patchlist_org[patchnr].cppos[0];
    new_point.ismid =TRUE;
    gruppe->pointlist.Add(new_point);
    gruppe->hgroup->AddCP(new_point.cp);
    new_point.cp = hsp[7]->CreateCPAtTail(gruppe->patchlist_org[patchnr].sdpos[4]);
    new_point.pos = gruppe->patchlist_org[patchnr].sdpos[4];
    new_point.ismid = FALSE;
    gruppe->pointlist.Add(new_point);
    gruppe->hgroup->AddCP(new_point.cp);
    new_point.cp = nullptr;
    new_point.pos.Set(0.F);
    gruppe->pointlist.Add(new_point);
}

void ExtrudeGruppe(HModelCache *hmc_new, GRUPPE *gruppe) {

    HGroupCP *newgroup, *extrudegroup;
    CArrayEx<NPOINT, NPOINT &> plist;
    CArrayEx<NPOINT, NPOINT &> clist;
    NPOINT t_point;
    int i, j, k;
    bool found, found1;

    for (i = 0; i < gruppe->pointlist.GetSize(); ++i) {
        if (!gruppe->pointlist[i].ismid) {
            Vector pos = gruppe->pointlist[i].pos;
            int az = 0;
            for (j = 0; j < gruppe->patchlist_new.GetSize(); ++j) {
                Vector pos1 = *gruppe->patchlist_new[j].opatch->GetCP1()->GetModelPosition();
                if (pos == pos1)
                    az++;
                pos1 = *gruppe->patchlist_new[j].opatch->GetCP2()->GetModelPosition();
                if (pos == pos1)
                    az++;
                pos1 = *gruppe->patchlist_new[j].opatch->GetCP3()->GetModelPosition();
                if (pos == pos1)
                    az++;
                if (gruppe->patchlist_new[j].opatch->GetNumPoints() == 4) {
                    pos1 = *gruppe->patchlist_new[j].opatch->GetCP4()->GetModelPosition();
                    if (pos == pos1)
                        az++;
                }
            }
            if (az < 4) {
                found = FALSE;
                for (k = 0; k < clist.GetSize(); ++k) {
                    if (pos == clist[k].pos) {
                        found =TRUE;
                        break;
                    }
                }
                if (!found)
                    clist.Add(gruppe->pointlist[i]);
            }
        }
    }

    newgroup = extrudegroup = nullptr;
    extrudegroup = gruppe->hgroup->GetGroupCP();
    hmc_new->CopyExtrude(false, extrudegroup, &newgroup);
    // ReSharper disable once CppAssignedValueIsNeverUsed
    extrudegroup = newgroup;

    while (newgroup) {
        t_point.cp = newgroup->GetCP();
        t_point.pos = *t_point.cp->GetPosition();
        plist.Add(t_point);
        newgroup = newgroup->GetNext();
    }

    for (k = 0; k < clist.GetSize(); ++k) {
        HSpline *hsp = hmc_new->CreateSpline();
        HCP *cp1 = hsp->CreateCPAtTail(clist[k].pos);
        HCP *cp2 = hsp->CreateCPAtTail(clist[k].pos);
        found = found1 = FALSE;
        for (i = 0; i < gruppe->pointlist.GetSize(); ++i) {
            if (clist[k].pos == gruppe->pointlist[i].pos) {
                if (!hmc_new->AttachCPs(cp1, gruppe->pointlist[i].cp))
                    found =TRUE;
                break;
            }
        }
        for (i = 0; i < plist.GetSize(); ++i) {
            if (clist[k].pos == plist[i].pos) {
                if(!hmc_new->AttachCPs(cp2, plist[i].cp))
                    found1 =TRUE;
                break;
            }
        }
        if (found)
            gruppe->hgroup->AddCP(cp1);
        if (found1)
            gruppe->hgroup->AddCP(cp2);
#ifdef _DEBUG
        if (!found)
            AfxMessageBox("Extrude Attach not found",MB_OK);
        if (!found1)
            AfxMessageBox("Extrude Attach not found1",MB_OK);
#endif
    }

    for (i = 0; i < plist.GetSize(); ++i) {
        for (j = 0; j < gruppe->extrudelist.GetSize(); ++j) {
            if (plist[i].pos == gruppe->extrudelist[j].pos) {
                plist[i].cp->SetPosition(&gruppe->extrudelist[j].newpos);
                gruppe->hgroup->AddCP(plist[i].cp);
                break;
            }
        }
    }
    plist.RemoveAll();
    clist.RemoveAll();
}

void CorrectNormals(HModelCache *hmc, GRUPPE *group, const int azpatches) {
    Vector normal_org;

    for (int i = 0; i < azpatches; ++i) {
        HPatch *hp = hmc->GetPatch(i);
        if (group->hgroup->IsPatchInGroup(hp)) {
            const Vector normal = Normal_Patch(hp);
            const HCP *cp1 = hp->GetCP1();
            for (int j = 0; j < group->pointlist.GetSize(); ++j) {
                if (cp1 == group->pointlist[j].cp) {
                    normal_org = group->patchlist_org[group->pointlist[j].referpatch].ndir[0];
                    break;
                }
            }
            if (Dot(normal_org, normal) <= 0.F) {
                hp->ReverseNormal();
            }
        }
    }
}

BOOL CE_RebuildApp::RebuildModelVariabel(HModelCache *hmc_org) const {
    int groupnumber;
    int i, k;
    EPatch ep_temp;
    HPatch5 *hp5;
    CArrayEx<GRUPPE, GRUPPE &> grouplist;
    CString hmc_name;
    GRUPPE tempgroup;
    float random_scale;

    CWaitCursor waitcursor;

    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("Rebuild");
        p_bar->SetMessage2("Calculate Patches");
        p_bar->SetProgress(0);
    }

    hmc_org->FindPatches();
    int azpatches = hmc_org->GetPatchCount();
    int azpatches5 = 0;
    for (hp5 = hmc_org->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        azpatches5++;
    }

    if (azpatches + azpatches5 < 2) {
        AfxMessageBox("What Do you want to explode in this model ???",MB_OK | MB_ICONSTOP);
        if (p_bar)
            p_bar->Uninitialize();
        return FALSE;
    }
    auto *plist = new PatchList;

    for (i = 0; i < azpatches; ++i) {
        ep_temp.Init(hmc_org->GetPatch(i));
        plist->patchlist.Add(ep_temp);
    }

    for (hp5 = hmc_org->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        ep_temp.Init(hp5);
        plist->patchlist.Add(ep_temp);
        i++;
    }
    plist->Sort(p_bar);

    grouplist.SetSize(0, 10);
    tempgroup.hgroup = nullptr;

    plist->GetNeighbors(p_bar, para->groupstrict);
    //variable Anzahl Patches pro Gruppe
    int j = plist->patchlist.GetSize();
    for (i = 0; i < j; ++i) {
        if (!plist->patchlist[i].isinuse) {
            int az_temp = 0;
            grouplist.Add(tempgroup);
            groupnumber = grouplist.GetSize() - 1;
            grouplist[groupnumber].patchlist_org.Add(plist->patchlist[i]);
            plist->patchlist[i].isinuse =TRUE;
            az_temp++;
            for (k = 0; k < plist->neighborlist[i].azneighbor; ++k) {
                if (az_temp == para->maxPatches)
                    break;
                if (!plist->patchlist[plist->neighborlist[i].neighbor[k]].isinuse) {
                    plist->patchlist[plist->neighborlist[i].neighbor[k]].isinuse =TRUE;
                    grouplist[groupnumber].patchlist_org.Add(plist->patchlist[plist->neighborlist[i].neighbor[k]]);
                    az_temp++;
                }
            }
        }
    }

    delete plist;

    //Erzeuge neues model
    if (p_bar) {
        p_bar->SetMessage1("Recreate model");
        p_bar->SetProgress(0);
    }
    CString hmc_org_name = hmc_org->GetName();
    hmc_name.Format("Exp_%s_0", hmc_org_name.GetBuffer(hmc_org_name.GetLength() + 1));
    i = 1;
    while ((HModelCache *)GetHProject()->GetChildObjectCacheContainer()->FindChildByName(hmc_name.GetBuffer(hmc_name.GetLength() + 1))) {
        hmc_name.Format("Exp_%s_%u", hmc_org_name.GetBuffer(hmc_org_name.GetLength() + 1), i);
        i++;
    }
    HModelCache *hmc_new = HModelCache::New(hmc_name,TRUE);

    //	if (p_bar) p_bar->Uninitialize();
    //	returnTRUE;

    k = grouplist.GetSize();
    groupnumber = 0;
    const double counter = 100. / (grouplist.GetSize() - 1);
    double akt_count = 0.;
    for (groupnumber = 0; groupnumber < k; ++groupnumber) {
        // create new group
        hmc_name.Format("Explode_%04u", groupnumber);
        grouplist[groupnumber].name = hmc_name;
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetMessage2("Create " + grouplist[groupnumber].name);
            p_bar->SetProgress((int)akt_count);
        }
        grouplist[groupnumber].hgroup = hmc_new->CreateGroup(hmc_name);
        //Create Splines
        for (i = 0; i < grouplist[groupnumber].patchlist_org.GetSize(); ++i) {
            if (grouplist[groupnumber].patchlist_org[i].numpoint == 3)
                RebuildPatch3(hmc_new, &grouplist[groupnumber], i);
            if (grouplist[groupnumber].patchlist_org[i].numpoint == 4)
                RebuildPatch4(hmc_new, &grouplist[groupnumber], i);
            if (grouplist[groupnumber].patchlist_org[i].numpoint == 5)
                RebuildPatch5(hmc_new, &grouplist[groupnumber], i);
        }

        //remove dummy entries
        for (i = 0; i < grouplist[groupnumber].pointlist.GetSize(); ++i) {
            if (!grouplist[groupnumber].pointlist[i].cp)
                grouplist[groupnumber].pointlist.RemoveAt(i, 1);
        }

        //Connect CP's
        for (i = 0; i < grouplist[groupnumber].pointlist.GetSize() - 2; ++i) {
            for (j = i + 1; j < grouplist[groupnumber].pointlist.GetSize(); ++j) {
                if (grouplist[groupnumber].pointlist[i].cp != grouplist[groupnumber].pointlist[j].cp) {
                    if (grouplist[groupnumber].pointlist[i].pos == grouplist[groupnumber].pointlist[j].pos && !grouplist[groupnumber].pointlist[j].attached) {
                        hmc_new->AttachCPs(grouplist[groupnumber].pointlist[i].cp, grouplist[groupnumber].pointlist[j].cp);
                        grouplist[groupnumber].pointlist[j].attached =TRUE;
                    }
                }
            }
        }
    }

    if (p_bar) {
        p_bar->SetMessage2("Refind patches ");
        p_bar->SetProgress(0);
    }

    if (p_bar) {
        p_bar->SetMessage2("Correct normals");
        p_bar->SetProgress(0);
    }
    hmc_new->Update();
    //Correct Normals
    akt_count = 0.;
    hmc_new->FindPatches();
    azpatches = hmc_new->GetPatchCount();
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetProgress((int)akt_count);
        }
        CorrectNormals(hmc_new, &grouplist[groupnumber], azpatches);
    }

    plist = new PatchList;
    for (i = 0; i < azpatches; ++i) {
        ep_temp.Init(hmc_new->GetPatch(i));
        plist->patchlist.Add(ep_temp);
    }

    plist->HitDistance(p_bar, hmc_new);

    for (i = 0; i < plist->patchlist.GetSize(); ++i) {
        for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
            if (grouplist[groupnumber].hgroup->IsPatchInGroup(plist->patchlist[i].opatch)) {
                grouplist[groupnumber].patchlist_new.Add(plist->patchlist[i]);
                break;
            }
        }
    }

    akt_count = 0.;
    if (p_bar)
        p_bar->SetMessage2("Calculate extrusion");
    std::random_device rd;
    std::mt19937 mt(rd());
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetProgress((int)akt_count);
        }
        for (i = 0; i < grouplist[groupnumber].patchlist_new.GetSize(); ++i) {
            for (k = 1; k <= grouplist[groupnumber].patchlist_new[i].numpoint; ++k) {
                bool found = FALSE;
                for (j = 0; j < grouplist[groupnumber].extrudelist.GetSize(); ++j) {
                    if (grouplist[groupnumber].patchlist_new[i].cppos[k] == grouplist[groupnumber].extrudelist[j].pos) {
                        found =TRUE;
                        break;
                    }
                }
                if (!found) {
                    EXTRUDEPOINTLIST ed_temp;
                    ed_temp.pos = grouplist[groupnumber].patchlist_new[i].cppos[k];
                    ed_temp.distance = 0.F;
                    ed_temp.n_normal.Set(0.F);
                    ed_temp.az = 0;
                    ed_temp.newpos.Set(0.F);
                    grouplist[groupnumber].extrudelist.Add(ed_temp);
                }
            }
        }
        for (i = 0; i < plist->patchlist.GetSize(); ++i) {
            for (k = 1; k <= plist->patchlist[i].numpoint; ++k) {
                for (j = 0; j < grouplist[groupnumber].extrudelist.GetSize(); ++j) {
                    if (para->near_average == 0.F) {
                        if (plist->patchlist[i].cppos[k] == grouplist[groupnumber].extrudelist[j].pos) {
                            grouplist[groupnumber].extrudelist[j].n_normal += plist->patchlist[i].ndir[k];
                            grouplist[groupnumber].extrudelist[j].distance += plist->patchlist[i].dist[k];
                            grouplist[groupnumber].extrudelist[j].az++;
                        }
                    } else {
                        if (plength(plist->patchlist[i].cppos[k], grouplist[groupnumber].extrudelist[j].pos) < para->near_average) {
                            grouplist[groupnumber].extrudelist[j].n_normal += plist->patchlist[i].ndir[k];
                            grouplist[groupnumber].extrudelist[j].distance += plist->patchlist[i].dist[k];
                            grouplist[groupnumber].extrudelist[j].az++;
                        }
                    }
                }
            }
        }
        if (para->randomscale) {
            std::uniform_real_distribution dist(para->minscale, para->maxscale);
            random_scale = dist(mt);
        }
        for (i = 0; i < grouplist[groupnumber].extrudelist.GetSize(); ++i) {
            grouplist[groupnumber].extrudelist[i].n_normal /= (float)grouplist[groupnumber].extrudelist[i].az;
            grouplist[groupnumber].extrudelist[i].n_normal.Normalize();
            if (!para->reverseextrude)
                grouplist[groupnumber].extrudelist[i].n_normal.Negate();
            grouplist[groupnumber].extrudelist[i].distance /= (float)grouplist[groupnumber].extrudelist[i].az;
            if (para->randomscale) {
                grouplist[groupnumber].extrudelist[i].distance *= random_scale;
            } else {
                grouplist[groupnumber].extrudelist[i].distance *= para->scale;
                if (para->check_minextrude)
                    grouplist[groupnumber].extrudelist[i].distance = para->minextrude;
            }
            grouplist[groupnumber].extrudelist[i].newpos = grouplist[groupnumber].extrudelist[i].pos + grouplist[groupnumber].extrudelist[i].distance * grouplist[groupnumber].extrudelist[i].n_normal;
        }
    }

    delete plist;

    if (para->reverseextrude) {
        for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
            for (i = 0; i < grouplist[groupnumber].patchlist_new.GetSize(); ++i) {
                grouplist[groupnumber].patchlist_new[i].opatch->ReverseNormal();
            }
        }
    }

    //Extruding
    akt_count = 0.;
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetMessage2("Extrude " + grouplist[groupnumber].name);
            p_bar->SetProgress((int)akt_count);
        }
        ExtrudeGruppe(hmc_new, &grouplist[groupnumber]);
    }

    hmc_new->Update();
    hmc_new->FindPatches();
    azpatches = hmc_new->GetPatchCount();
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        grouplist[groupnumber].patchlist_new.RemoveAll();
    }
    for (i = 0; i < azpatches; ++i) {
        for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
            if (grouplist[groupnumber].hgroup->IsPatchInGroup(hmc_new->GetPatch(i))) {
                ep_temp.Init(hmc_new->GetPatch(i));
                grouplist[groupnumber].patchlist_new.Add(ep_temp);
                break;
            }
        }
    }

    if (p_bar) {
        p_bar->SetMessage2("Add bones");
        p_bar->SetProgress(0);
    }

    //Add Bones to groups
    Vector end, mid_average, mid, model_min;
    Quaternion quat;

    akt_count = 0.;
    end.Set(0.F, 0.F, 1.F);
    mid_average.Set(0.F);
    quat.SetIdentity();
    model_min.Set(3.402823466e+38F);
    Vector model_max = model_min;
    model_max.Negate();
    String hstring = "Explode_Root";
    HSegmentCache *master_sc = hmc_new->AddSegment(nullptr, nullptr, hstring, GetColor(hmc_new->CountBones()));
    HBoneCache *master_bc = hmc_new->GetChildBoneCacheContainer()->GetChildBoneCache();
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetProgress((int)akt_count);
        }
        hmc_name.Format("Explode_%04u", groupnumber);
        hstring.Set(hmc_name, hmc_name.GetLength());
        HSegmentCache *child_sc = hmc_new->AddSegment(master_bc, nullptr, hstring, GetColor(hmc_new->CountBones()));
        HGroupCP *ngroup = grouplist[groupnumber].hgroup->GetGroupCP();
        while (ngroup) {
            child_sc->AquireCP(ngroup->GetCP());
            ngroup = ngroup->GetNext();
        }
        BBox(&grouplist[groupnumber], mid, model_min, model_max);
        child_sc->GetPivot()->StoreValue(Time(), mid,TRUE);
        child_sc->GetRotate()->StoreValue(Time(), quat,TRUE,TRUE);
        child_sc->GetEnd()->StoreValue(Time(), mid + end,TRUE);
    }
    mid_average = (model_max + model_min) / 2.F;
    end.Set(0.F, 0.F, 10.F);
    master_sc->GetPivot()->StoreValue(Time(), mid_average,TRUE);
    mid_average += end;
    master_sc->GetRotate()->StoreValue(Time(), quat,TRUE,TRUE);
    master_sc->GetEnd()->StoreValue(Time(), mid_average,TRUE);

    if (p_bar) {
        p_bar->SetMessage2("Finishing new model");
        p_bar->SetProgress(0);
    }

    hmc_new->SetChanged(true);
    if (p_bar)
        p_bar->SetProgress(50);
    hmc_new->FindPatches();
    if (p_bar)
        p_bar->SetProgress(100);
    grouplist.RemoveAll();
    if (p_bar)
        p_bar->Uninitialize();
    return TRUE;
}

BOOL CE_RebuildApp::RebuildModelGroups(HModelCache *hmc_org) const {
    int groupnumber;
    int i, j;
    EPatch ep_temp;
    HPatch5 *hp5;
    CArrayEx<GRUPPE, GRUPPE &> grouplist;
    CString hmc_name;
    GRUPPE tempgroup;
    float random_scale = 0;

    CWaitCursor waitcursor;

    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("Rebuild");
        p_bar->SetMessage2("Calculate Patches");
        p_bar->SetProgress(0);
    }
    hmc_org->FindPatches();
    int azpatches = hmc_org->GetPatchCount();
//    int azpatches5 = 0;
//    for (hp5 = hmc_org->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
//        azpatches5++;
//    }

    auto *plist = new PatchList;

    for (i = 0; i < azpatches; ++i) {
        ep_temp.Init(hmc_org->GetPatch(i));
        plist->patchlist.Add(ep_temp);
    }

    for (hp5 = hmc_org->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        ep_temp.Init(hp5);
        plist->patchlist.Add(ep_temp);
        i++;
    }
    plist->Sort(p_bar);
    plist->HitDistance(p_bar, hmc_org);

    grouplist.SetSize(0, 10);
    tempgroup.hgroup = nullptr;
    const int az_temp = plist->patchlist.GetSize();

    HGroupContainer *hgc = hmc_org->GetChildGroupContainer();
    for (HGroup *hg = hgc->GetChildGroup(); hg; hg = (HGroup *)hg->GetSibling()) {
        String groupname = hg->GetName();
        if (groupname.Find("Exp_") != -1) {
            grouplist.Add(tempgroup);
            groupnumber = grouplist.GetSize() - 1;
            for (i = 0; i < az_temp; ++i) {
                if (plist->patchlist[i].numpoint == 5) {
                    if (hg->IsPatchInGroup(plist->patchlist[i].opatch5)) {
                        grouplist[groupnumber].patchlist_org.Add(plist->patchlist[i]);
                    }
                } else {
                    if (hg->IsPatchInGroup(plist->patchlist[i].opatch)) {
                        grouplist[groupnumber].patchlist_org.Add(plist->patchlist[i]);
                    }
                }
            }
        }
    }
    delete plist;

    //Erzeuge neues model
    if (p_bar) {
        p_bar->SetMessage1("Recreate model");
        p_bar->SetProgress(0);
    }
    CString hmc_org_name = hmc_org->GetName();
    hmc_name.Format("Exp_%s_0", hmc_org_name.GetBuffer(hmc_org_name.GetLength() + 1));
    i = 1;
    while ((HModelCache *)GetHProject()->GetChildObjectCacheContainer()->FindChildByName(hmc_name.GetBuffer(hmc_name.GetLength() + 1))) {
        hmc_name.Format("Exp_%s_%u", hmc_org_name.GetBuffer(hmc_org_name.GetLength() + 1), i);
        i++;
    }
    HModelCache *hmc_new = HModelCache::New(hmc_name,TRUE);

    int k = grouplist.GetSize();
    groupnumber = 0;
    const double counter = 100. / (grouplist.GetSize() - 1);
    double akt_count = 0.;
    for (groupnumber = 0; groupnumber < k; ++groupnumber) {
        // create new group
        hmc_name.Format("Explode_%04u", groupnumber);
        grouplist[groupnumber].hgroup = hmc_new->CreateGroup(hmc_name);
        grouplist[groupnumber].name = hmc_name;
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetMessage2("Create " + grouplist[groupnumber].name);
            p_bar->SetProgress((int)akt_count);
        }
        //Create Splines
        for (i = 0; i < grouplist[groupnumber].patchlist_org.GetSize(); ++i) {
            if (grouplist[groupnumber].patchlist_org[i].numpoint == 3)
                RebuildPatch3(hmc_new, &grouplist[groupnumber], i);
            if (grouplist[groupnumber].patchlist_org[i].numpoint == 4)
                RebuildPatch4(hmc_new, &grouplist[groupnumber], i);
            if (grouplist[groupnumber].patchlist_org[i].numpoint == 5)
                RebuildPatch5(hmc_new, &grouplist[groupnumber], i);
        }

        //remove dummy entries
        for (i = 0; i < grouplist[groupnumber].pointlist.GetSize(); ++i) {
            if (!grouplist[groupnumber].pointlist[i].cp)
                grouplist[groupnumber].pointlist.RemoveAt(i, 1);
        }

        //Connect CP's
        for (i = 0; i < grouplist[groupnumber].pointlist.GetSize() - 2; ++i) {
            for (j = i + 1; j < grouplist[groupnumber].pointlist.GetSize(); ++j) {
                if (grouplist[groupnumber].pointlist[i].cp != grouplist[groupnumber].pointlist[j].cp) {
                    if (grouplist[groupnumber].pointlist[i].pos == grouplist[groupnumber].pointlist[j].pos && !grouplist[groupnumber].pointlist[j].attached) {
                        hmc_new->AttachCPs(grouplist[groupnumber].pointlist[i].cp, grouplist[groupnumber].pointlist[j].cp);
                        grouplist[groupnumber].pointlist[j].attached =TRUE;
                    }
                }
            }
        }
    }

    if (p_bar) {
        p_bar->SetMessage2("Refind patches ");
        p_bar->SetProgress(0);
    }

    //Correct Normals
    hmc_new->Update();
    hmc_new->FindPatches();
    azpatches = hmc_new->GetPatchCount();
    akt_count = 0.;
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetProgress((int)akt_count);
        }
        CorrectNormals(hmc_new, &grouplist[groupnumber], azpatches);
    }

    plist = new PatchList;
    for (i = 0; i < azpatches; ++i) {
        ep_temp.Init(hmc_new->GetPatch(i));
        plist->patchlist.Add(ep_temp);
    }
    plist->HitDistance(p_bar, hmc_new);

    for (i = 0; i < plist->patchlist.GetSize(); ++i) {
        for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
            if (grouplist[groupnumber].hgroup->IsPatchInGroup(plist->patchlist[i].opatch)) {
                grouplist[groupnumber].patchlist_new.Add(plist->patchlist[i]);
                break;
            }
        }
    }

    akt_count = 0.;
    if (p_bar)
        p_bar->SetMessage2("Calculate extrusion");
    std::random_device rd;
    std::mt19937 mt(rd());
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetProgress((int)akt_count);
        }
        for (i = 0; i < grouplist[groupnumber].patchlist_new.GetSize(); ++i) {
            for (k = 1; k <= grouplist[groupnumber].patchlist_new[i].numpoint; ++k) {
                bool found = FALSE;
                for (j = 0; j < grouplist[groupnumber].extrudelist.GetSize(); ++j) {
                    if (grouplist[groupnumber].patchlist_new[i].cppos[k] == grouplist[groupnumber].extrudelist[j].pos) {
                        found =TRUE;
                        break;
                    }
                }
                if (!found) {
                    EXTRUDEPOINTLIST ed_temp;
                    ed_temp.pos = grouplist[groupnumber].patchlist_new[i].cppos[k];
                    ed_temp.distance = 0.F;
                    ed_temp.n_normal.Set(0.F);
                    ed_temp.az = 0;
                    ed_temp.newpos.Set(0.F);
                    grouplist[groupnumber].extrudelist.Add(ed_temp);
                }
            }
        }
        for (i = 0; i < plist->patchlist.GetSize(); ++i) {
            for (k = 1; k <= plist->patchlist[i].numpoint; ++k) {
                for (j = 0; j < grouplist[groupnumber].extrudelist.GetSize(); ++j) {
                    if (para->near_average == 0.F) {
                        if (plist->patchlist[i].cppos[k] == grouplist[groupnumber].extrudelist[j].pos) {
                            grouplist[groupnumber].extrudelist[j].n_normal += plist->patchlist[i].ndir[k];
                            grouplist[groupnumber].extrudelist[j].distance += plist->patchlist[i].dist[k];
                            grouplist[groupnumber].extrudelist[j].az++;
                        }
                    } else {
                        if (plength(plist->patchlist[i].cppos[k], grouplist[groupnumber].extrudelist[j].pos) < para->near_average) {
                            grouplist[groupnumber].extrudelist[j].n_normal += plist->patchlist[i].ndir[k];
                            grouplist[groupnumber].extrudelist[j].distance += plist->patchlist[i].dist[k];
                            grouplist[groupnumber].extrudelist[j].az++;
                        }
                    }
                }
            }
        }
        if (para->randomscale) {
            std::uniform_real_distribution dist(para->minscale, para->maxscale);
            random_scale = dist(mt);
        }
        for (i = 0; i < grouplist[groupnumber].extrudelist.GetSize(); ++i) {
            grouplist[groupnumber].extrudelist[i].n_normal /= (float)grouplist[groupnumber].extrudelist[i].az;
            grouplist[groupnumber].extrudelist[i].n_normal.Normalize();
            if (!para->reverseextrude)
                grouplist[groupnumber].extrudelist[i].n_normal.Negate();
            grouplist[groupnumber].extrudelist[i].distance /= (float)grouplist[groupnumber].extrudelist[i].az;
            if (para->randomscale) {
                grouplist[groupnumber].extrudelist[i].distance *= random_scale;
            } else {
                grouplist[groupnumber].extrudelist[i].distance *= para->scale;
                if (para->check_minextrude)
                    grouplist[groupnumber].extrudelist[i].distance = para->minextrude;
            }
            grouplist[groupnumber].extrudelist[i].newpos = grouplist[groupnumber].extrudelist[i].pos + grouplist[groupnumber].extrudelist[i].distance * grouplist[groupnumber].extrudelist[i].n_normal;
        }
    }

    delete plist;
    if (para->reverseextrude) {
        for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
            for (i = 0; i < grouplist[groupnumber].patchlist_new.GetSize(); ++i) {
                grouplist[groupnumber].patchlist_new[i].opatch->ReverseNormal();
            }
        }
    }
    //Extruding
    akt_count = 0.;
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetMessage2("Extrude " + grouplist[groupnumber].name);
            p_bar->SetProgress((int)akt_count);
        }
        ExtrudeGruppe(hmc_new, &grouplist[groupnumber]);
    }

    hmc_new->Update();
    hmc_new->FindPatches();
    azpatches = hmc_new->GetPatchCount();
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        grouplist[groupnumber].patchlist_new.RemoveAll();
    }
    for (i = 0; i < azpatches; ++i) {
        for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
            if (grouplist[groupnumber].hgroup->IsPatchInGroup(hmc_new->GetPatch(i))) {
                ep_temp.Init(hmc_new->GetPatch(i));
                grouplist[groupnumber].patchlist_new.Add(ep_temp);
                break;
            }
        }
    }
    if (p_bar) {
        p_bar->SetMessage2("Add bones");
        p_bar->SetProgress(0);
    }

    //Add Bones to groups
    Vector end, mid_average, mid, model_min;
    Quaternion quat;

    akt_count = 0.;
    end.Set(0.F, 0.F, 1.F);
    mid_average.Set(0.F);
    quat.SetIdentity();
    model_min.Set(3.402823466e+38F);
    Vector model_max = model_min;
    model_max.Negate();
    String hstring = "Explode_Root";
    HSegmentCache *master_sc = hmc_new->AddSegment(nullptr, nullptr, hstring, GetColor(hmc_new->CountBones()));
    HBoneCache *master_bc = hmc_new->GetChildBoneCacheContainer()->GetChildBoneCache();
    for (groupnumber = 0; groupnumber < grouplist.GetSize(); ++groupnumber) {
        if (p_bar) {
            akt_count = counter * groupnumber;
            p_bar->SetProgress((int)akt_count);
        }
        hmc_name.Format("Explode_%04u", groupnumber);
        hstring.Set(hmc_name, hmc_name.GetLength());
        HSegmentCache *child_sc = hmc_new->AddSegment(master_bc, nullptr, hstring, GetColor(hmc_new->CountBones()));
        HGroupCP *ngroup = grouplist[groupnumber].hgroup->GetGroupCP();
        while (ngroup) {
            child_sc->AquireCP(ngroup->GetCP());
            ngroup = ngroup->GetNext();
        }
        BBox(&grouplist[groupnumber], mid, model_min, model_max);
        child_sc->GetPivot()->StoreValue(Time(), mid,TRUE);
        child_sc->GetRotate()->StoreValue(Time(), quat,TRUE,TRUE);
        child_sc->GetEnd()->StoreValue(Time(), mid + end,TRUE);
    }
    mid_average = (model_max + model_min) / 2.F;
    end.Set(0.F, 0.F, 10.F);
    master_sc->GetPivot()->StoreValue(Time(), mid_average,TRUE);
    mid_average += end;
    master_sc->GetRotate()->StoreValue(Time(), quat,TRUE,TRUE);
    master_sc->GetEnd()->StoreValue(Time(), mid_average,TRUE);

    if (p_bar) {
        p_bar->SetMessage2("Finishing new model");
        p_bar->SetProgress(0);
    }
    hmc_new->SetChanged(true);
    if (p_bar)
        p_bar->SetProgress(50);
    hmc_new->FindPatches();
    if (p_bar)
        p_bar->SetProgress(100);
    grouplist.RemoveAll();
    if (p_bar)
        p_bar->Uninitialize();
    return TRUE;
}
