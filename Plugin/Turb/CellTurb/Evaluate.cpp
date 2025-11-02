// RC  6/4/2002  \Randy95\Plugin\Turb\CellTurb\Evaluate.cpp

#include "Custom.h"
#include "texfuncs.h"
#include "TurbApp.h"

extern CTurbApp theApp;

HProperty *CustomTurbulence::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_celltype;
        case 1:
            return m_threshold;
        case 2:
            return m_oct;
        case 3:
            return m_density;
        case 4:
            return m_euclid;
        default:
            return nullptr;
    }
}

float CustomTurbulence::Voronoi2(const Vector *p, const int style) const {
    float dist;
    Vector add;
    Vector rpos;
    constexpr Vector arse(3.F, -2.F, 9.F);
    float f1 = 1000.0F;
    float f2 = 1000.0F;
    const Vector thiscell((fast_floor(p->x)), (fast_floor(p->y)), (fast_floor(p->z)));
    const float oneminusdensity = 1.F - m_density->GetValue() / 100.F;
    const BOOL iseuclid = m_euclid->GetValue();

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            for (int k = -1; k <= 1; ++k) {
                add.Set(i, j, k);
                Vector testcell = thiscell + add;
                if (CTurbApp::CellNoise(testcell + arse) > oneminusdensity) {
                    Vector pos;
                    pos.x = testcell.x + CTurbApp::CellNoise(testcell);
                    pos.y = testcell.y + CTurbApp::CellNoise(-testcell);
                    pos.z = testcell.z + CTurbApp::CellNoise(testcell + 2);
                    Vector offset = pos - *p;
                    if (iseuclid)
                        dist = offset.Dot(offset);
                    else
                        dist = hash_math::abs(pos.x - p->x) + hash_math::abs(pos.y - p->y) + hash_math::abs(pos.z - p->z);

                    if (dist < f1) {
                        f2 = f1;
                        f1 = dist;
                        rpos = pos;
                    } else if (dist < f2) {
                        f2 = dist;
                    }
                }
            }

    if (iseuclid)
        f1 = hash_math::sqrt(f1);

    switch (style) {
        case 1:
            return f1;
        case 2:
            return CTurbApp::Noise(rpos);
        case 3:
            if (iseuclid)
                f2 = hash_math::sqrt(f2);
            return f2 - f1;
        case 4:
            if (iseuclid)
                f2 = hash_math::sqrt(f2);
            return hash_math::sin((f2 - f1) * hash_constants::pi);
        case 5:
            if (iseuclid)
                f2 = hash_math::sqrt(f2);
            return f2;
        case 6:
            return hash_math::sin(f1 * (hash_constants::pi / 2.F));
        case 7:
        {
            if (iseuclid)
                f2 = hash_math::sqrt(f2);
            return step(m_threshold->GetValue() / 100.F, f2 - f1);
        }
        default:
            return f1;
    }
}

float CustomTurbulence::Evaluate(const Vector &evalp) {
    Vector P(evalp);
    float turb = 0.F;
    const int oct = m_oct->GetValue();
    const int style = m_celltype->GetValue() + 1;
    if (oct > 1) {
        float m = 1.F;
        for (int i = 0; i < oct; ++i) {
            turb += Voronoi2(&P, style) * m;
            P *= 2.17F;
            m *= 0.7F;
        }
        turb = turb > 1.F ? 1.F : turb;
    } else
        turb = Voronoi2(&P, style);

    if (style != 7)
        turb = smoothstep(m_threshold->GetValue() / 100.F, 1, turb);
    turb = turb > 1.F ? 1.F : turb;
    return turb;
}
