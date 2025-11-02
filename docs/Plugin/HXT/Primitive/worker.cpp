#include "StdAfx.h"
#include "primitive.h"

static double double_round(const double n, const int d) {
    return hash_math::floor(n * hash_math::pow(10., d) + .5) / hash_math::pow(10., d);
}

static void SetTypeCP(HSpline *sph, const BOOL cptyp) {
    HCP *cp = sph->GetHeadCP();

    if (cptyp)
        cp->SetPeaked();
    else
        cp->SetSmooth();
    while ((cp = cp->GetNext()) != nullptr) {
        if (cptyp)
            cp->SetPeaked();
        else
            cp->SetSmooth();
        if (cp->IsLoop())
            break;
    }
}

static void SetMagnitude(HSpline *sph, const float magnitude) {
    HCP *cp = sph->GetHeadCP();

    cp->SetInMagnitude(magnitude / 100.F);
    cp->SetOutMagnitude(magnitude / 100.F);
    while ((cp = cp->GetNext()) != nullptr) {
        cp->SetInMagnitude(magnitude / 100.F);
        cp->SetOutMagnitude(magnitude / 100.F);
        if (cp->IsLoop())
            break;
    }
}

static void SetMagnitudeSpecial(HSpline *sph, const float magnitude) {
    HCP *cp = sph->GetHeadCP();

    cp->SetInMagnitude(118.F / 100.F);
    cp->SetOutMagnitude(118.F / 100.F);
    cp = cp->GetNext();
    cp->SetInMagnitude(magnitude / 100.F);
    cp->SetOutMagnitude(magnitude / 100.F);
    cp = cp->GetNext();
    cp->SetInMagnitude(118.F / 100.F);
    cp->SetOutMagnitude(118.F / 100.F);
}

static HCP *GetIndexedCP(HSpline *sph, const int index) {
    HCP *cp = sph->GetHeadCP();

    for (int i = 0; cp && i < index; cp = cp->GetNext(), ++i) {}
    return cp;
}

static HCP *GetCPFromPos(HModelCache *hmc, const HSpline *sph, HCP *cp) {
    HCP *ret_cp = nullptr;
    const Vector pos_tofind = *cp->GetPosition();
    for (HSpline *sp = hmc->GetHeadSpline(); sp; sp = sp->GetNextSpline()) {
        if (sp == sph)
            continue;
        for (HCP *tempcp = sp->GetHeadCP(); tempcp; tempcp = tempcp->GetNext()) {
            if (const Vector pos_other = *tempcp->GetPosition(); pos_tofind.IsEqual(pos_other, 0.1F)) {
                ret_cp = tempcp;
                break;
            }
            if (tempcp->IsLoop())
                break;
        }
    }
    return ret_cp;
}

static void Fill_Table_Feder(const PParameters *wp, Vector **FArray, const double theta, const int array_n) {

    const double theta_sin = hash_math::sin(theta);
    const double theta_cos = hash_math::cos(theta);
    for (int i = 0; i <= wp->m_segment1; ++i) {
        const double phi = hash_math::cos(S_PI * i / wp->m_segment1);
        const double x = wp->m_radius2 * phi * theta_cos + wp->m_radius1 * theta_cos;
        const double z = wp->m_radius2 * phi * theta_sin + wp->m_radius1 * theta_sin;
        FArray[array_n][i].x = (float)double_round(x, 12);
        FArray[array_n][i].z = (float)double_round(z, 12);
        FArray[array_n][i].y = 0.F;
    }
}

static void Fill_Table1(Vector *table, const double winkel, const int segmente, const float radius, const BOOL direction) {
    if (int i; direction) {
        int j = segmente;
        for (i = 0; i <= segmente; i++, j--) {
            table[j].x = (float)double_round(hash_math::cos(winkel * i) * radius, 12);
            table[j].z = (float)double_round(hash_math::sin(winkel * i) * radius, 12);
            table[j].y = 0.F;
        }
    } else {
        for (i = 0; i <= segmente; ++i) {
            table[i].x = (float)double_round(hash_math::cos(winkel * i) * radius, 12);
            table[i].z = (float)double_round(hash_math::sin(winkel * i) * radius, 12);
            table[i].y = 0.F;
        }
    }
}

static HSpline *BuildFeder(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const float ofs_y, const int array_n, Vector **FArray) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    BOOL firstrun = TRUE;

    double hoehe = wp->m_radius2 * hash_math::sin(S_PI * 0 / wp->m_segment1);

    firstpos = FArray[array_n][0];
    firstpos.y = (float)(ofs_y + hoehe);
    for (int i = 1; i <= wp->m_segment1; ++i) {
        hoehe = wp->m_radius2 * hash_math::sin(S_PI * i / wp->m_segment1);
        pos = FArray[array_n][i];
        pos.y = (float)(ofs_y + hoehe);
        if (firstrun) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
            firstrun = FALSE;
        } else {
            lastcp = hmc->AddCP(lastcp, &pos);
        }
    }

    hmc->AttachCPs(lastcp, (*sphptr)->GetHeadCP());

    return *sphptr;
}

static HSpline *BuildSpirale(const PParameters *wp, HModelCache *hmc, HSpline **sphptr) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    BOOL firstrun = TRUE;

    const double winkel = S_PI / wp->m_segment1;
    const float hoehe = wp->m_hoehe / (wp->m_turn * wp->m_segment1);
    float y = wp->m_hoehe * -0.5F;

    auto *table = new Vector[wp->m_segment1 + 1];

    Fill_Table1(table, winkel, wp->m_segment1, wp->m_radius1, wp->m_richtung);

    firstpos = table[0];
    firstpos.y = y;
    for (int j = 0; j < wp->m_turn; ++j) {
        for (int i = 1; i <= wp->m_segment1; ++i) {
            y += hoehe;
            pos = table[i];
            pos.y = y;
            if (firstrun) {
                *sphptr = hmc->StartSpline(&firstpos, &pos);
                lastcp = (*sphptr)->GetHeadCP()->GetNext();
                firstrun = FALSE;
            } else {
                lastcp = hmc->AddCP(lastcp, &pos);
            }
        }
    }
    delete [] table;
    return *sphptr;
}

static HSpline *BuildTorus(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const float theta) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;

    const float d = wp->m_radius2; //Dicke des Rings 
    const float r = wp->m_radius1; //Durchmesser des Rings
    auto phi = (float)double_round(S_PI * 0 / wp->m_segment1, 12);
    auto x = (float)double_round(d * hash_math::cos(phi) * hash_math::cos(theta), 12);
    auto z = (float)double_round(d * hash_math::cos(phi) * hash_math::sin(theta), 12);
    x += (float)double_round(r * hash_math::cos(theta), 12);
    z += (float)double_round(r * hash_math::sin(theta), 12);
    auto y = (float)double_round(d * hash_math::sin(phi), 12);
    firstpos.Set(x, y, z);
    for (int i = 1; i <= wp->m_segment1; ++i) {
        phi = (float)double_round(S_PI * i / wp->m_segment1, 12);
        x = (float)double_round(d * hash_math::cos(phi) * hash_math::cos(theta), 12);
        z = (float)double_round(d * hash_math::cos(phi) * hash_math::sin(theta), 12);
        x += (float)double_round(r * hash_math::cos(theta), 12);
        z += (float)double_round(r * hash_math::sin(theta), 12);
        y = (float)double_round(d * hash_math::sin(phi), 12);
        pos.Set(x, y, z);
        if (i == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (i > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    hmc->AttachCPs(lastcp, (*sphptr)->GetHeadCP());
    return *sphptr;
}

static HSpline *BuildCircle(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const float hoehe, const int achse) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    float x = 0.F, y = 0.F, z = 0.F;

    const double winkel = S_PI / wp->m_segment1;
    switch (achse) {
        case 0:
            // Y-Achse
            z = (float)double_round(hash_math::sin(winkel * 0) * wp->m_radius1, 12);
            x = (float)double_round(hash_math::cos(winkel * 0) * wp->m_radius1, 12);
            y = hoehe;
            break;
        case 1:
            // Z-Achse
            x = (float)double_round(hash_math::sin(winkel * 0) * wp->m_radius1, 12);
            y = (float)double_round(hash_math::cos(winkel * 0) * wp->m_radius1, 12);
            z = hoehe;
            break;
        case 2:
            // X-Achse
            y = (float)double_round(hash_math::sin(winkel * 0) * wp->m_radius1, 12);
            z = (float)double_round(hash_math::cos(winkel * 0) * wp->m_radius1, 12);
            x = hoehe;
            break;
    }
    firstpos.Set(x, y, z);

    for (int i = 1; i <= wp->m_segment1; ++i) {
        switch (achse) {
            case 0:
                // Y-Achse
                z = (float)double_round(hash_math::sin(winkel * i) * wp->m_radius1, 12);
                x = (float)double_round(hash_math::cos(winkel * i) * wp->m_radius1, 12);
                break;
            case 1:
                // Z-Achse
                x = (float)double_round(hash_math::sin(winkel * i) * wp->m_radius1, 12);
                y = (float)double_round(hash_math::cos(winkel * i) * wp->m_radius1, 12);
                break;
            case 2:
                // X-Achse
                y = (float)double_round(hash_math::sin(winkel * i) * wp->m_radius1, 12);
                z = (float)double_round(hash_math::cos(winkel * i) * wp->m_radius1, 12);
                break;
        }
        pos.Set(x, y, z);
        if (i == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (i > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    hmc->AttachCPs(lastcp, (*sphptr)->GetHeadCP());
    return *sphptr;
}

static HSpline *BuildHalfCircle(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const int j) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    int i = 0;

    const int az_segment = wp->m_segment1 * 0.5F;
    const int ofs_segment = wp->m_segment1 / 4;
    const double winkel = S_PI / wp->m_segment1;
    auto z = (float)double_round(hash_math::sin(winkel * j) * 0.005, 12);
    auto x = (float)double_round(hash_math::cos(winkel * j) * 0.005, 12);
    //   x = 0;
    //   z = 0;
    auto y = (float)double_round(hash_math::sin(winkel * (i + ofs_segment)) * wp->m_radius1, 12);

    firstpos.Set(x, y, z);
    for (i = 1; i <= az_segment; ++i) {
        y = (float)double_round(hash_math::sin(winkel * (i + ofs_segment)) * wp->m_radius1, 12);
        if (i == az_segment) {
            z = (float)double_round(hash_math::sin(winkel * j) * 0.005, 12);
            x = (float)double_round(hash_math::cos(winkel * j) * 0.005, 12);
            //		  x = 0;
            //		  z = 0;
        } else {
            x = (float)double_round(hash_math::cos(winkel * (i - ofs_segment)) * hash_math::cos(winkel * j) * wp->m_radius1, 12);
            z = (float)double_round(hash_math::cos(winkel * (i - ofs_segment)) * hash_math::sin(winkel * j) * wp->m_radius1, 12);
        }
        pos.Set(x, y, z);
        if (i == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (i > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    return *sphptr;
}

static HSpline *BuildRechteckPatch(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const float hoehe, const bool stumpf) {
    float x1, z1, x2, z2;

    if (stumpf) {
        x1 = wp->m_breite / 4.F * -1.F;
        x2 = wp->m_breite / 4.F;
        z1 = wp->m_tiefe / 4.F * -1.F;
        z2 = wp->m_tiefe / 4.F;
    } else {
        x1 = wp->m_breite / 2.F * -1.F;
        x2 = wp->m_breite / 2.F;
        z1 = wp->m_tiefe / 2.F * -1.F;
        z2 = wp->m_tiefe / 2.F;
    }
    Vector firstpos, pos;
    firstpos.Set(x1, hoehe, z2);
    pos.Set(x2, hoehe, z2);
    *sphptr = hmc->StartSpline(&firstpos, &pos);
    HCP *lastcp = (*sphptr)->GetHeadCP()->GetNext();
    pos.Set(x2, hoehe, z1);
    lastcp = hmc->AddCP(lastcp, &pos);
    pos.Set(x1, hoehe, z1);
    // ReSharper disable once CppAssignedValueIsNeverUsed
    lastcp = hmc->AddCP(lastcp, &pos);
    return *sphptr;
}

static HSpline *BuildRechteck(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const float hoehe) {
    const float x1 = wp->m_breite / 2.F * -1.F;
    const float x2 = wp->m_breite / 2.F;
    const float z1 = wp->m_tiefe / 2.F * -1.F;
    const float z2 = wp->m_tiefe / 2.F;
    Vector firstpos, pos;
    firstpos.Set(x1, hoehe, z2);
    pos.Set(x2, hoehe, z2);
    *sphptr = hmc->StartSpline(&firstpos, &pos);
    HCP *lastcp = (*sphptr)->GetHeadCP()->GetNext();
    pos.Set(x2, hoehe, z1);
    lastcp = hmc->AddCP(lastcp, &pos);
    pos.Set(x1, hoehe, z1);
    lastcp = hmc->AddCP(lastcp, &pos);
    pos.Set(x1, hoehe, z1);
    lastcp = hmc->AddCP(lastcp, &pos);
    hmc->AttachCPs(lastcp, (*sphptr)->GetHeadCP());
    return *sphptr;
}

static HSpline *BuildRechteckSubD(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const float hoehe, const float delta_breite, const float delta_tiefe, const float delta_hoehe, const int subdivisions, const int axis) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    float x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0;

    switch (axis) {
        case 0: //xz
            x1 = x2 = wp->m_breite / 2.F * -1.F;
            z1 = z2 = wp->m_tiefe / 2.F * -1.F;
            y1 = y2 = hoehe;
            break;
        case 1: //xy
            x1 = x2 = wp->m_breite / 2.F * -1.F;
            z1 = z2 = hoehe;
            y1 = y2 = wp->m_hoehe / 2.F * -1.F;
            break;
        case 2: //yz
            x1 = x2 = hoehe;
            z1 = z2 = wp->m_tiefe / 2.F * -1.F;
            y1 = y2 = wp->m_hoehe / 2.F * -1.F;
            break;
    }

    BOOL isFirst = TRUE;
    firstpos.Set(x1, y1, z1);
    for (int i = 0; i < subdivisions; ++i) {
        switch (axis) {
            case 0:
                x2 += delta_breite;
                break;
            case 1:
                x2 += delta_breite;
                break;
            case 2:
                y2 += delta_hoehe;
                break;
        }
        pos.Set(x2, y2, z2);
        if (isFirst) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
            isFirst = FALSE;
        } else {
            lastcp = hmc->AddCP(lastcp, &pos);
        }
    }
    for (int i = 0; i < subdivisions; ++i) {
        switch (axis) {
            case 0:
                z2 += delta_tiefe;
                break;
            case 1:
                y2 += delta_hoehe;
                break;
            case 2:
                z2 += delta_tiefe;
                break;
        }
        pos.Set(x2, y2, z2);
        lastcp = hmc->AddCP(lastcp, &pos);
    }
    for (int i = 0; i < subdivisions; ++i) {
        switch (axis) {
            case 0:
                x2 -= delta_breite;
                break;
            case 1:
                x2 -= delta_breite;
                break;
            case 2:
                y2 -= delta_hoehe;
                break;
        }
        pos.Set(x2, y2, z2);
        lastcp = hmc->AddCP(lastcp, &pos);
    }
    for (int i = 0; i < subdivisions; ++i) {
        switch (axis) {
            case 0:
                z2 -= delta_tiefe;
                break;
            case 1:
                y2 -= delta_hoehe;
                break;
            case 2:
                z2 -= delta_tiefe;
                break;
        }
        pos.Set(x2, y2, z2);
        lastcp = hmc->AddCP(lastcp, &pos);
    }
    hmc->AttachCPs(lastcp, (*sphptr)->GetHeadCP());
    return *sphptr;
}

static HSpline *BuildSpline(const PParameters *wp, HModelCache *hmc, HSpline **sphptr, const int az_points) {
    Vector firstpos, pos;
    HCP *lastcp = nullptr;

    firstpos.Set(wp->m_breite, wp->m_hoehe, wp->m_tiefe);
    pos.Set(wp->m_breite, wp->m_hoehe, wp->m_tiefe);
    for (int i = 1; i < az_points; ++i) {
        if (i == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (i > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    return *sphptr;
}

static HSpline *BuildVSpline(HModelCache *hmc, HSpline **sphptr, const int az_points) {
    HCP *lastcp = nullptr;
    Vector firstpos{0.F};
    for (int i = 1; i < az_points; ++i) {
        Vector pos(0.F);
        if (i == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (i > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    return *sphptr;
}

BOOL CPrimitiveApp::BuildModel(HModelCache *hmc) {
    PParameters *Pp = &m_parameters;
    BOOL work_ok = FALSE;
    Vector pos;
    auto *hm = (HModel *)hmc;

    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        m_hprogressbar->SetMessage1("");
        m_hprogressbar->SetMessage2("");
    }
    Vector **FArray;
    div_t div_result;
    HCP *cp2;
    HCP *cp1;
    float ofs_y = 0.F;
    float ofs_hoehe = 0.F;
    int gesamt_schritte = 0;
    int az_schritte = 0;
    int gesamt_segmente = 0;
    int k = 0;
    int j = 0;
    int i = 0;
    HSpline **vsplines;
    HSpline **usplines;
    double winkel = 0.0;
    switch (Pp->m_type) {
        case 0: //Circle
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Circle");
            usplines = new HSpline *[1];
            BuildCircle(&m_parameters, hmc, &usplines[0], 0.F, 0);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            if (Pp->m_typcp)
                SetTypeCP(usplines[0], Pp->m_typcp);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            if (Pp->m_magnitude != 100)
                SetMagnitude(usplines[0], Pp->m_magnitude);
            delete [] usplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            break;
        case 1: //Spirale
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Spiral");
            usplines = new HSpline *[1];
            BuildSpirale(&m_parameters, hmc, &usplines[0]);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            if (Pp->m_typcp)
                SetTypeCP(usplines[0], Pp->m_typcp);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            if (Pp->m_magnitude != 100)
                SetMagnitude(usplines[0], Pp->m_magnitude);
            delete [] usplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 2: //Cube
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Cube");
            usplines = new HSpline *[2];
            vsplines = new HSpline *[6];
            BuildRechteckPatch(&m_parameters, hmc, &usplines[0], Pp->m_hoehe * -0.5F, FALSE);
            BuildVSpline(hmc, &vsplines[4], 2);
            cp1 = GetIndexedCP(usplines[0], 0);
            cp2 = GetIndexedCP(vsplines[4], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 3);
            cp2 = GetIndexedCP(vsplines[4], 1);
            hmc->AttachCPs(cp2, cp1);
            BuildRechteckPatch(&m_parameters, hmc, &usplines[1], Pp->m_hoehe * 0.5F, FALSE);
            BuildVSpline(hmc, &vsplines[5], 2);
            cp1 = GetIndexedCP(usplines[1], 0);
            cp2 = GetIndexedCP(vsplines[5], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[1], 3);
            cp2 = GetIndexedCP(vsplines[5], 1);
            hmc->AttachCPs(cp2, cp1);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            for (i = 0; i < 4; ++i) {
                BuildVSpline(hmc, &vsplines[i], 2);
                cp1 = GetIndexedCP(usplines[0], i);
                cp2 = GetIndexedCP(vsplines[i], 0);
                pos = *cp1->GetHead()->GetModelPosition();
                cp2->SetPosition(&pos);
                hmc->AttachCPs(cp1, cp2);
                cp1 = GetIndexedCP(usplines[1], i);
                cp2 = GetIndexedCP(vsplines[i], 1);
                pos = *cp1->GetHead()->GetModelPosition();
                cp2->SetPosition(&pos);
                hmc->AttachCPs(cp1, cp2);
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            if (Pp->m_typcp) {
                SetTypeCP(usplines[0], Pp->m_typcp);
                SetTypeCP(usplines[1], Pp->m_typcp);
                for (i = 0; i < 6; ++i) {
                    SetTypeCP(vsplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                SetMagnitude(usplines[0], Pp->m_magnitude);
                SetMagnitude(usplines[1], Pp->m_magnitude);
            }
            delete [] usplines;
            delete [] vsplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 3:
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Cylinder");
            usplines = new HSpline *[Pp->m_segment3 + 1];
            vsplines = new HSpline *[Pp->m_segment1 + 1];
            ofs_hoehe = Pp->m_hoehe / Pp->m_segment3;
            //	   ofs_y = 0.F;
            ofs_y = Pp->m_hoehe * -0.5F;
            for (i = 0; i <= Pp->m_segment3; ++i) {
                BuildCircle(&m_parameters, hmc, &usplines[i], ofs_y, 0);
                ofs_y += ofs_hoehe;
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            for (j = 0; j < Pp->m_segment1; ++j) {
                BuildVSpline(hmc, &vsplines[j], Pp->m_segment3 + 1);
                for (i = 0; i <= Pp->m_segment3; ++i) {
                    cp1 = GetIndexedCP(usplines[i], j);
                    cp2 = GetIndexedCP(vsplines[j], i);
                    hmc->AttachCPs(cp2, cp1);
                }
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            if (Pp->m_typcp) {
                for (i = 0; i <= Pp->m_segment3; ++i) {
                    SetTypeCP(usplines[i], Pp->m_typcp);
                }
                for (i = 0; i < Pp->m_segment1; ++i) {
                    SetTypeCP(vsplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                for (i = 0; i <= Pp->m_segment3; ++i) {
                    SetMagnitude(usplines[i], Pp->m_magnitude);
                }
            }
            delete [] usplines;
            delete [] vsplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 4: //Zylinder closed
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Cylinder closed");
            usplines = new HSpline *[Pp->m_segment3 + 3];
            vsplines = new HSpline *[Pp->m_segment1 + 1];
            ofs_hoehe = Pp->m_hoehe / Pp->m_segment3;
            //	   ofs_y = 0.F;
            ofs_y = Pp->m_hoehe * -0.5F;
            for (i = 1; i <= Pp->m_segment3 + 1; ++i) {
                BuildCircle(&m_parameters, hmc, &usplines[i], ofs_y, 0);
                ofs_y += ofs_hoehe;
            }
            ofs_y -= ofs_hoehe;
            Pp->m_radius1 = 0.01F; //changed 0,001 
            BuildCircle(&m_parameters, hmc, &usplines[0], Pp->m_hoehe * -0.5F, 0);
            BuildCircle(&m_parameters, hmc, &usplines[i], ofs_y, 0);

            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            for (j = 0; j < Pp->m_segment1; ++j) {
                BuildVSpline(hmc, &vsplines[j], Pp->m_segment3 + 3);
                for (i = 0; i <= Pp->m_segment3 + 2; ++i) {
                    cp1 = GetIndexedCP(usplines[i], j);
                    cp2 = GetIndexedCP(vsplines[j], i);
                    hmc->AttachCPs(cp2, cp1);
                }
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            for (i = 0; i < Pp->m_segment1; ++i) {
                SetTypeCP(vsplines[i], TRUE);
            }
            if (Pp->m_typcp) {
                for (i = 1; i <= Pp->m_segment3 + 1; ++i) {
                    SetTypeCP(usplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                for (i = 0; i <= Pp->m_segment3 + 1; ++i) {
                    SetMagnitude(usplines[i], Pp->m_magnitude);
                }
            }
            delete [] usplines;
            delete [] vsplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 5:
            i = Pp->m_segment2;
            Pp->m_segment2 = Pp->m_segment1;
            Pp->m_segment1 = i;
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Ring");
            winkel = S_PI / Pp->m_segment2;
            gesamt_segmente = Pp->m_segment1 * Pp->m_segment2 + 1;
            gesamt_schritte = Pp->m_segment1 + Pp->m_segment2;
            usplines = new HSpline *[gesamt_segmente];
            vsplines = new HSpline *[Pp->m_segment1 + 1];
            if (m_hprogressbar)
                m_hprogressbar->SetMessage2("create segments");
            for (i = 0; i < Pp->m_segment2; i++, az_schritte++) {
                BuildTorus(&m_parameters, hmc, &usplines[i], (float)(winkel * i));
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
            }
            if (m_hprogressbar)
                m_hprogressbar->SetMessage2("join segments");
            for (j = 0; j < Pp->m_segment1; j++, az_schritte++) {
                BuildVSpline(hmc, &vsplines[j], Pp->m_segment2 + 1);
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                for (i = 0; i < Pp->m_segment2; ++i) {
                    cp1 = GetIndexedCP(usplines[i], j);
                    cp2 = GetIndexedCP(vsplines[j], i);
                    hmc->AttachCPs(cp2, cp1);
                }
                cp1 = GetIndexedCP(usplines[0], j);
                cp2 = GetIndexedCP(vsplines[j], Pp->m_segment2);
                hmc->AttachCPs(cp2, cp1);
            }
            if (Pp->m_typcp) {
                for (i = 0; i < Pp->m_segment2; ++i) {
                    SetTypeCP(usplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                for (i = 0; i < Pp->m_segment2; ++i) {
                    SetMagnitude(usplines[i], Pp->m_magnitude2);
                }
            }
            if (Pp->m_magnitude2 != 100) {
                for (j = 0; j < Pp->m_segment1; ++j) {
                    SetMagnitude(vsplines[j], Pp->m_magnitude);
                }
            }
            delete [] vsplines;
            delete [] usplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 6: //Feder
            i = Pp->m_segment2;
            Pp->m_segment2 = Pp->m_segment1;
            Pp->m_segment1 = i;
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Spring");
            gesamt_segmente = Pp->m_turn * Pp->m_segment2;
            gesamt_schritte = Pp->m_segment2 + Pp->m_turn * Pp->m_segment2 + Pp->m_segment1;
            az_schritte = 0;
            ofs_hoehe = Pp->m_hoehe / gesamt_segmente;
            ofs_y = Pp->m_hoehe / 2 * -1;
            winkel = S_PI / Pp->m_segment2;
            usplines = new HSpline *[gesamt_segmente * Pp->m_segment1 + 1];
            vsplines = new HSpline *[Pp->m_segment1 + 1];
            if (m_hprogressbar)
                m_hprogressbar->SetMessage2("create segments");
            FArray = new Vector *[Pp->m_segment2 + 1];
            for (i = 0; i <= Pp->m_segment2; ++i) {
                FArray[i] = new Vector [Pp->m_segment1 + 1];
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
            if (Pp->m_richtung) {
                j = Pp->m_segment2;
                for (i = 0; i <= Pp->m_segment2; i++, j--, az_schritte++) {
                    Fill_Table_Feder(&m_parameters, FArray, winkel * i, j);
                    ofs_y += ofs_hoehe;
                    if (m_hprogressbar)
                        m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                }
            } else {
                for (i = 0; i <= Pp->m_segment2; i++, az_schritte++) {
                    Fill_Table_Feder(&m_parameters, FArray, winkel * i, i);
                    ofs_y += ofs_hoehe;
                    if (m_hprogressbar)
                        m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                }
            }
            ofs_y = Pp->m_hoehe / 2 * -1;
            k = 0;
            BuildFeder(&m_parameters, hmc, &usplines[k], ofs_y, 0, FArray);
            k++;
            for (j = 0; j < Pp->m_turn; ++j) {
                for (i = 1; i <= Pp->m_segment2; i++, k++, az_schritte++) {
                    ofs_y += ofs_hoehe;
                    BuildFeder(&m_parameters, hmc, &usplines[k], ofs_y, i, FArray);
                    if (m_hprogressbar)
                        m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                }
            }
            if (m_hprogressbar)
                m_hprogressbar->SetMessage2("join segments");

            //Normalen Flipping, wenn Hoehe ueber 89  
            for (j = 0; j < Pp->m_segment1; j++, az_schritte++) {
                BuildVSpline(hmc, &vsplines[j], gesamt_segmente + 1);
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                for (i = 0; i <= gesamt_segmente; ++i) {
                    cp1 = GetIndexedCP(usplines[i], j);
                    cp2 = GetIndexedCP(vsplines[j], i);
                    if (cp1 && cp2) {
                        pos = *cp1->GetHead()->GetModelPosition();
                        cp2->SetPosition(&pos);
                        hmc->AttachCPs(cp1, cp2);
                    }
                }
            }

            if (Pp->m_typcp) {
                for (i = 0; i <= gesamt_segmente; ++i) {
                    SetTypeCP(usplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                for (i = 0; i <= gesamt_segmente; ++i) {
                    SetMagnitude(usplines[i], Pp->m_magnitude2);
                }
            }
            if (Pp->m_magnitude2 != 100) {
                for (i = 0; i < Pp->m_segment1; ++i) {
                    SetMagnitude(vsplines[i], Pp->m_magnitude);
                }
            }
            if (Pp->m_autobone && hm->FindBone("FMaster_1") == nullptr) {
                CString temp_name;
                String t_name;
                CString bonenumber;
                Vector position;
                auto **hsc = new HSegmentCache *[gesamt_segmente + 1];
                auto **segment_bc = new HBoneCache *[gesamt_segmente + 1];
                auto *table = new Vector[Pp->m_segment2 + 1];
                gesamt_schritte = gesamt_segmente + gesamt_segmente + gesamt_segmente * Pp->m_segment1 + Pp->m_turn * Pp->m_segment2;
                az_schritte = 0;
                // Create Bones
                if (m_hprogressbar)
                    m_hprogressbar->SetMessage2("create bones");
                // Root
                temp_name.Format("FMaster_1");
                t_name.Set(temp_name, temp_name.GetLength());
                [[maybe_unused]] HSegmentCache *hsc_master = hmc->AddSegment(nullptr, nullptr, t_name, GetColor(hmc->CountBones()));
                HBoneCache *master_bone = hmc->GetChildBoneCacheContainer()->GetChildBoneCache();
                // Attach oben
                temp_name.Format("FAttach_o_1");
                t_name.Set(temp_name, temp_name.GetLength());
                [[maybe_unused]] HSegmentCache *hsc_attach_o = hmc->AddSegment(master_bone, nullptr, t_name, GetColor(hmc->CountBones()));
                HBoneCache *attach_o = master_bone->GetChildBoneCache();

                // Attach unten
                temp_name.Format("FAttach_u_1");
                t_name.Set(temp_name, temp_name.GetLength());
                [[maybe_unused]] HSegmentCache *hsc_attach_u = hmc->AddSegment(master_bone, nullptr, t_name, GetColor(hmc->CountBones()));
                HBoneCache *attach_u = attach_o->GetSiblingBoneCache();

                // Segment Bones
                // Attach unten
                temp_name.Format("FSDummy_1");
                t_name.Set(temp_name, temp_name.GetLength());
                [[maybe_unused]] HSegmentCache *hsc_dummy = hmc->AddSegment(master_bone, nullptr, t_name, GetColor(hmc->CountBones()));
                HBoneCache *dummy_bone = attach_u->GetSiblingBoneCache();

                for (j = 0; j <= gesamt_segmente; j++, az_schritte++) {
                    bonenumber.Format("%04u", j + 1);
                    CString bonename = "FS_" + bonenumber + "_1";
                    t_name.Set(bonename, bonename.GetLength());
                    hsc[j] = hmc->AddSegment(dummy_bone, nullptr, t_name, GetColor(hmc->CountBones()));
                    if (m_hprogressbar)
                        m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                }
                segment_bc[0] = dummy_bone->GetChildBoneCache();
                for (i = 1; i <= gesamt_segmente; i++, az_schritte++) {
                    segment_bc[i] = segment_bc[i - 1]->GetSiblingBoneCache();
                    if (m_hprogressbar)
                        m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                }

                // Add CP's to bones
                if (m_hprogressbar)
                    m_hprogressbar->SetMessage2("attaching cp's");
                for (i = 0; i <= gesamt_segmente; ++i) {
                    for (j = 0; j < Pp->m_segment1; j++, az_schritte++) {
                        cp1 = GetIndexedCP(usplines[i], j);
                        cp2 = GetIndexedCP(vsplines[j], i);
                        hsc[i]->AquireCP(cp1);
                        hsc[i]->AquireCP(cp2);
                        if (m_hprogressbar)
                            m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                    }
                }

                // Bone Position
                if (m_hprogressbar)
                    m_hprogressbar->SetMessage2("set position");
                // Root
                HVectorProperty *bone_pos = master_bone->GetPivot();
                position.x = 0.F;
                position.y = 0.F;
                position.z = 0.F;
                bone_pos->SetValue(position);
                bone_pos = master_bone->GetEnd();
                position.x = 0.F;
                position.y = 0.F;
                position.z = Pp->m_radius1 * 2;
                bone_pos->SetValue(position);
                HFloatProperty *bone_length = master_bone->GetLength();
                float length = Pp->m_radius1 * 2;
                bone_length->SetValue(length);
                // Attach oben
                bone_pos = attach_o->GetPivot();
                position.x = 0.F;
                position.y = Pp->m_hoehe / 2;
                position.z = 0.F;
                bone_pos->SetValue(position);
                bone_pos = attach_o->GetEnd();
                position.x = 0.F;
                position.y = Pp->m_hoehe / 2;
                position.z = Pp->m_radius1;
                bone_pos->SetValue(position);
                bone_length = attach_o->GetLength();
                length = Pp->m_radius1;
                bone_length->SetValue(length);
                // Attach unten
                bone_pos = attach_u->GetPivot();
                position.x = 0.F;
                position.y = Pp->m_hoehe / 2 * -1;
                position.z = 0.F;
                bone_pos->SetValue(position);
                bone_pos = attach_u->GetEnd();
                position.x = 0.F;
                position.y = Pp->m_hoehe / 2 * -1;
                position.z = Pp->m_radius1;
                bone_pos->SetValue(position);
                bone_length = attach_u->GetLength();
                length = Pp->m_radius1;
                bone_length->SetValue(length);
                // Dummy
                bone_pos = dummy_bone->GetPivot();
                position.x = 0.F;
                position.y = 0.F;
                position.z = 0.F;
                bone_pos->SetValue(position);
                bone_pos = dummy_bone->GetEnd();
                position.x = 0.F;
                position.y = 0.F;
                position.z = 0.1F;
                bone_pos->SetValue(position);
                bone_length = dummy_bone->GetLength();
                length = 0.1F;
                bone_length->SetValue(length);
                // Segment Bones
                Fill_Table1(table, winkel, Pp->m_segment2, Pp->m_radius1, Pp->m_richtung);
                ofs_y = Pp->m_hoehe / 2 * -1;
                i = 0;
                k = 0;
                bone_pos = segment_bc[k]->GetPivot();
                position = table[i];
                position.y = ofs_y;
                bone_pos->SetValue(position);
                bone_pos = segment_bc[k]->GetEnd();
                position.z += Pp->m_radius2;
                bone_pos->SetValue(position);
                bone_length = segment_bc[k]->GetLength();
                length = Pp->m_radius2;
                bone_length->SetValue(length);
                ofs_y += ofs_hoehe;
                k++;
                for (j = 0; j < Pp->m_turn; ++j) {
                    for (i = 1; i <= Pp->m_segment2; i++, k++, az_schritte++) {
                        bone_pos = segment_bc[k]->GetPivot();
                        position = table[i];
                        position.y = ofs_y;
                        bone_pos->SetValue(position);
                        bone_pos = segment_bc[k]->GetEnd();
                        position.z += Pp->m_radius2;
                        bone_pos->SetValue(position);
                        bone_length = segment_bc[k]->GetLength();
                        length = Pp->m_radius2;
                        bone_length->SetValue(length);
                        ofs_y += ofs_hoehe;
                        if (m_hprogressbar)
                            m_hprogressbar->SetProgress((int)((float)az_schritte / gesamt_schritte * 100));
                    }
                }
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress(100);
                delete [] table;
                delete [] hsc;
                delete [] segment_bc;
            }
            delete [] vsplines;
            delete [] usplines;
            delete [] FArray;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 7:
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Pyramid stump");
            usplines = new HSpline *[2];
            vsplines = new HSpline *[6];
            BuildRechteckPatch(&m_parameters, hmc, &usplines[0], Pp->m_hoehe * -0.5F, FALSE);
            BuildVSpline(hmc, &vsplines[4], 2);
            cp1 = GetIndexedCP(usplines[0], 0);
            cp2 = GetIndexedCP(vsplines[4], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 3);
            cp2 = GetIndexedCP(vsplines[4], 1);
            hmc->AttachCPs(cp2, cp1);
            BuildRechteckPatch(&m_parameters, hmc, &usplines[1], Pp->m_hoehe * 0.5F, TRUE);
            BuildVSpline(hmc, &vsplines[5], 2);
            cp1 = GetIndexedCP(usplines[1], 0);
            cp2 = GetIndexedCP(vsplines[5], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[1], 3);
            cp2 = GetIndexedCP(vsplines[5], 1);
            hmc->AttachCPs(cp2, cp1);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            for (i = 0; i < 4; ++i) {
                BuildVSpline(hmc, &vsplines[i], 2);
                cp1 = GetIndexedCP(usplines[0], i);
                cp2 = GetIndexedCP(vsplines[i], 0);
                pos = *cp1->GetHead()->GetModelPosition();
                cp2->SetPosition(&pos);
                hmc->AttachCPs(cp1, cp2);
                cp1 = GetIndexedCP(usplines[1], i);
                cp2 = GetIndexedCP(vsplines[i], 1);
                pos = *cp1->GetHead()->GetModelPosition();
                cp2->SetPosition(&pos);
                hmc->AttachCPs(cp1, cp2);
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            if (Pp->m_typcp) {
                SetTypeCP(usplines[0], Pp->m_typcp);
                SetTypeCP(usplines[1], Pp->m_typcp);
                for (i = 0; i < 6; ++i) {
                    SetTypeCP(vsplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                SetMagnitude(usplines[0], Pp->m_magnitude);
                SetMagnitude(usplines[1], Pp->m_magnitude);
            }
            delete [] usplines;
            delete [] vsplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 8:
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Pyramid");
            usplines = new HSpline *[1];
            vsplines = new HSpline *[2];
            BuildRechteck(&m_parameters, hmc, &usplines[0], Pp->m_hoehe * -0.5F);
            Pp->m_breite = 0.F;
            Pp->m_tiefe = 0.F;
            Pp->m_hoehe *= 0.5F;
            BuildSpline(&m_parameters, hmc, &vsplines[0], 3);
            BuildSpline(&m_parameters, hmc, &vsplines[1], 3);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            cp1 = GetIndexedCP(usplines[0], 0);
            cp2 = GetIndexedCP(vsplines[0], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 2);
            cp2 = GetIndexedCP(vsplines[0], 2);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 1);
            cp2 = GetIndexedCP(vsplines[1], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 3);
            cp2 = GetIndexedCP(vsplines[1], 2);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(vsplines[0], 1);
            cp2 = GetIndexedCP(vsplines[1], 1);
            hmc->AttachCPs(cp2, cp1);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            SetTypeCP(usplines[0], Pp->m_typcp);
            SetTypeCP(vsplines[0], Pp->m_typcp);
            SetTypeCP(vsplines[1], Pp->m_typcp);
            if (Pp->m_magnitude != 100) {
                SetMagnitude(usplines[0], Pp->m_magnitude);
                SetMagnitude(vsplines[0], Pp->m_magnitude);
                SetMagnitude(vsplines[1], Pp->m_magnitude);
            }
            delete [] usplines;
            delete [] vsplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 9:
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Tetrahedron");
            usplines = new HSpline *[3];
            BuildCircle(&m_parameters, hmc, &usplines[0], 0.F, 0);
            BuildCircle(&m_parameters, hmc, &usplines[1], 0.F, 1);
            BuildCircle(&m_parameters, hmc, &usplines[2], 0.F, 2);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);
            cp1 = GetIndexedCP(usplines[0], 0);
            cp2 = GetIndexedCP(usplines[1], 1);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 2);
            cp2 = GetIndexedCP(usplines[1], 3);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 1);
            cp2 = GetIndexedCP(usplines[2], 0);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[0], 3);
            cp2 = GetIndexedCP(usplines[2], 2);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[1], 0);
            cp2 = GetIndexedCP(usplines[2], 1);
            hmc->AttachCPs(cp2, cp1);
            cp1 = GetIndexedCP(usplines[1], 2);
            cp2 = GetIndexedCP(usplines[2], 3);
            hmc->AttachCPs(cp2, cp1);
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            SetTypeCP(usplines[0], Pp->m_typcp);
            SetTypeCP(usplines[1], Pp->m_typcp);
            SetTypeCP(usplines[2], Pp->m_typcp);
            if (Pp->m_magnitude != 100) {
                SetMagnitude(usplines[0], Pp->m_magnitude);
                SetMagnitude(usplines[1], Pp->m_magnitude);
                SetMagnitude(usplines[2], Pp->m_magnitude);
            }
            delete [] usplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 10:
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Sphere");
            div_result = div(Pp->m_segment1, 4);
            if (div_result.rem != 0) {
                if (div_result.rem != 1) {
                    Pp->m_segment1 = (div_result.quot + 1) * 4;
                } else {
                    Pp->m_segment1 = div_result.quot * 4;
                }
            }
            usplines = new HSpline *[Pp->m_segment1];
            vsplines = new HSpline *[Pp->m_segment1];
            for (i = 0; i < Pp->m_segment1; ++i) {
                BuildHalfCircle(&m_parameters, hmc, &usplines[i], i);
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(25);
            for (i = 0; i < Pp->m_segment1 / 2 + 1; ++i) {
                BuildCircle(&m_parameters, hmc, &vsplines[i], 0, 0);
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(50);
            for (i = 0; i < Pp->m_segment1 / 2 + 1; ++i) {
                for (j = 0; j < Pp->m_segment1; ++j) {
                    cp1 = GetIndexedCP(usplines[j], i);
                    cp2 = GetIndexedCP(vsplines[i], j);
                    hmc->AttachCPs(cp2, cp1);
                }
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(75);
            if (Pp->m_typcp) {
                for (i = 0; i < Pp->m_segment1; ++i) {
                    SetTypeCP(usplines[i], Pp->m_typcp);
                }
                for (i = 0; i < Pp->m_segment1 / 2 + 1; ++i) {
                    SetTypeCP(vsplines[i], Pp->m_typcp);
                }
            }
            if (Pp->m_magnitude != 100) {
                if (Pp->m_segment1 == 4) {
                    for (i = 0; i < Pp->m_segment1; ++i) {
                        SetMagnitudeSpecial(usplines[i], Pp->m_magnitude);
                    }
                } else {
                    for (i = 0; i < Pp->m_segment1; ++i) {
                        SetMagnitude(usplines[i], Pp->m_magnitude);
                    }
                }
                for (i = 0; i < Pp->m_segment1 / 2 + 1; ++i) {
                    SetMagnitude(vsplines[i], Pp->m_magnitude);
                }
            }
            delete [] usplines;
            delete [] vsplines;
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            work_ok = TRUE;
            break;
        case 11:
        {
            if (m_hprogressbar)
                m_hprogressbar->SetMessage1("Subdivided Cube");
            const int sd = Pp->m_subdiv + 1;
            const float delta_breite = Pp->m_breite / sd;
            const float delta_tiefe = Pp->m_tiefe / sd;
            const float delta_hoehe = Pp->m_hoehe / sd;

            usplines = new HSpline *[sd + 2];
            ofs_hoehe = Pp->m_hoehe * -0.5F;
            for (i = 0; i < sd + 1; ++i) {
                BuildRechteckSubD(&m_parameters, hmc, &usplines[i], ofs_hoehe, delta_breite, delta_tiefe, delta_hoehe, sd, 0);
                SetTypeCP(usplines[i], TRUE);
                ofs_hoehe += delta_hoehe;
            }
            //splines für die Ecken bauen und verbinden
            auto **verspline = new HSpline *[4];
            BuildVSpline(hmc, &verspline[0], sd + 1);
            BuildVSpline(hmc, &verspline[1], sd + 1);
            BuildVSpline(hmc, &verspline[2], sd + 1);
            BuildVSpline(hmc, &verspline[3], sd + 1);
            for (int j1 = 0; j1 < sd + 1; ++j1) {
                cp1 = GetIndexedCP(usplines[j1], 0);
                cp2 = GetIndexedCP(verspline[0], j1);
                hmc->AttachCPs(cp2, cp1);
                cp1 = GetIndexedCP(usplines[j1], sd);
                cp2 = GetIndexedCP(verspline[1], j1);
                hmc->AttachCPs(cp2, cp1);
                cp1 = GetIndexedCP(usplines[j1], 2 * sd);
                cp2 = GetIndexedCP(verspline[2], j1);
                hmc->AttachCPs(cp2, cp1);
                cp1 = GetIndexedCP(usplines[j1], 3 * sd);
                cp2 = GetIndexedCP(verspline[3], j1);
                hmc->AttachCPs(cp2, cp1);
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(33);

            vsplines = new HSpline *[sd];
            ofs_hoehe = Pp->m_tiefe * -0.5F;
            ofs_hoehe += delta_tiefe;

            for (i = 0; i < sd - 1; ++i) {
                BuildRechteckSubD(&m_parameters, hmc, &vsplines[i], ofs_hoehe, delta_breite, delta_tiefe, delta_hoehe, sd, 1);
                SetTypeCP(vsplines[i], TRUE);
                ofs_hoehe += delta_tiefe;
                for (cp1 = vsplines[i]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
                    cp2 = GetCPFromPos(hmc, vsplines[i], cp1);
                    if (cp1 && cp2 && cp1 != cp2)
                        hmc->AttachCPs(cp2, cp1);
                    if (cp1->IsLoop())
                        break;
                }
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(66);
            auto **xsplines = new HSpline *[sd];
            ofs_hoehe = Pp->m_breite * -0.5F;
            ofs_hoehe += delta_breite;
            for (i = 0; i < sd - 1; ++i) {
                BuildRechteckSubD(&m_parameters, hmc, &xsplines[i], ofs_hoehe, delta_breite, delta_tiefe, delta_hoehe, sd, 2);
                SetTypeCP(xsplines[i], TRUE);
                ofs_hoehe += delta_breite;
                for (cp1 = xsplines[i]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
                    cp2 = GetCPFromPos(hmc, xsplines[i], cp1);
                    if (cp1 && cp2 && cp1 != cp2)
                        hmc->AttachCPs(cp2, cp1);
                    if (cp1->IsLoop())
                        break;
                }
            }
            if (m_hprogressbar)
                m_hprogressbar->SetProgress(100);
            delete [] xsplines;
            delete [] verspline;
            delete [] vsplines;
            delete [] usplines;
            work_ok = TRUE;
        }
        break;
    }

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }

    if (work_ok) {
        hmc->SetChanged(TRUE);
        hmc->OpenView();
        hmc->HilightInProjectBar();
    }

    return TRUE;
}
