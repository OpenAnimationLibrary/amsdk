// KB  9/26/01  \Ken90\Plugin\Turb\GridTurb\Evaluate.cpp

// ReSharper disable CppTooWideScope
#include "Custom.h"
#include "texfuncs.h"
#include "TurbApp.h"

extern CTurbApp theApp;

HProperty *CustomTurbulence::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_celltype;
        case 1:
            return m_octaves;
        case 2:
            return m_gridsize;
        default:
            return nullptr;
    }
}

float CustomTurbulence::Evaluate(const Vector &evalp) {
    const Vector P = evalp;
    const float size = 1.F - m_gridsize->GetValue() / 100.F;
    float x = P.x;
    float y = P.y;
    const float z = P.z;
    float v, scale, turb;
    const float r = m_octaves->GetValue() / 100.F;
    switch (m_celltype->GetValue()) {
        case 0:
            v = repeat(x, r);
            scale = pulse(size, 1.F, 0.1F, v);
            turb = scale;
            v = repeat(y, r);
            scale = pulse(size, 1.F, 0.1F, v);
            turb += scale;
            v = repeat(z, r);
            scale = pulse(size, 1.F, 0.1F, v);
            turb += scale;
            break;
        case 1:
            v = repeat(x, r);
            scale = pulse(size, 1.F, 0.1F, v);
            turb = scale;
            v = repeat(y, r);
            scale = pulse(size, 1.F, 0.1F, v);
            turb += scale;
            break;
        case 2:
            CalcUV(P, &x, &y, 0);
            v = repeat(x, r * 100.F);
            scale = pulse(size, 1.F, 0.1F, v);
            turb = scale;
            v = repeat(y, r * 100.F);
            scale = pulse(size, 1.F, 0.1F, v);
            turb += scale;
            break;
        case 3:

            CalcUV(P, &x, &y, 1);
            v = repeat(x, r * 100.F);
            scale = pulse(size, 1.F, 0.1F, v);
            turb = scale;
            v = repeat(y, r * 100.F);
            scale = pulse(size, 1.F, 0.1F, v);
            turb += scale;
            break;

        case 4:
            turb = EvaluateHex(P, size, r, 0.1F);
            break;
        default:
            turb = 0;
    }
    turb = turb > 1.F ? 1.F : turb;
    return turb;
}

void CustomTurbulence::CalcUV(const Vector &e, float *u, float *v, const int type) {
    float ele = 0.F;
    Vector temp(e);
    temp.Normalize();
    const float az = (-hash_math::atan2(temp.y, temp.x) + hash_constants::pi) / (2.F * hash_constants::pi);
    if (type == 0) // spherical
        ele = 0.5F - hash_math::cos(temp.z) / hash_constants::pi;
    else if (type == 1) // cylindrical
        ele = temp.z;
    *u = az;
    *v = ele;
}

float CustomTurbulence::EvaluateHex(const Vector &P, const float radius, float scale, float sfuzz) {
    constexpr float tileradius = .2f;
    const float mortarwidth = radius / 10.F;
    const Vector p(P);
    constexpr float tilewidth = tileradius * 1.7320508F; /* sqrt(3) */
    float ss, s, t;

    CalcUV(p, &s, &t, 0);
    sfuzz *= 1 - t;
    s *= 2.42F;
    t *= 2.42F;

    sfuzz /= 2.42F;
    scale *= 100.F;
    s = h_mod(s * scale, 2.42F);
    t = h_mod(t * scale, 2.42F);
    const float tt = hash_math::fmod(t, 1.5F * tileradius);
    auto ttile = (float)fast_floor(t / (1.5F * tileradius));
    if (hash_math::fmod(ttile / 2.F, 1.F) == 0.5F)
        ss = s + tilewidth / 2.F;
    else
        ss = s;
    auto stile = (float)fast_floor(ss / tilewidth);
    ss = hash_math::fmod(ss, tilewidth);
    float mortar;
    const float mw2 = mortarwidth / 2.F;
    if (tt < tileradius) {
        mortar = 1.F - smoothstep(mw2, mw2 + sfuzz, ss) * (1.F - smoothstep(tilewidth - mw2 - sfuzz, tilewidth - mw2, ss));
    } else {
        const float x = tilewidth / 2.F - hash_math::abs(ss - tilewidth / 2.F);
        const float y = 1.7320508F * (tt - tileradius);
        if (y > x) {
            if (hash_math::fmod(ttile / 2.F, 1.F) == 0.5F)
                stile -= 1.F;
            ttile += 1.F;
            if (ss > tilewidth / 2.F)
                stile += 1.F;
        }
        mortar = smoothstep(x - 1.73F * mw2 - sfuzz, x - 1.73F * mw2, y) * (1.F - smoothstep(x + 1.73F * mw2, x + 1.73F * mw2 + sfuzz, y));
    }

    [[maybe_unused]] float tileindex = stile + 41 * ttile;
    return mortar;
}

float CustomTurbulence::Voronoi2(const Vector *p, const int style) const {
    Vector rpos;
#ifdef _DEBUG
    Vector rpos2;
#endif
    float f1 = 1000.0F;
    float f2 = 1000.0F;
    const Vector thiscell((fast_floor(p->x)), (fast_floor(p->y)), (fast_floor(p->z)));
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            for (int k = -1; k <= 1; ++k) {
                Vector add;
                Vector pos;
                add.x = (float)i;
                add.y = (float)j;
                add.z = (float)k;

                Vector testcell = thiscell + add;

                pos.x = testcell.x + CTurbApp::CellNoise(testcell);
                pos.y = testcell.y + CTurbApp::Noise(-testcell);
                pos.z = testcell.z + CTurbApp::CellNoise(testcell + 2.F);
                Vector offset = pos - *p;
                const float dist = offset.Dot(offset);
                if (dist < f1) {
                    f2 = f1;
                    f1 = dist;
#ifdef _DEBUG
                    rpos2 = rpos;
#endif
                    rpos = pos;
                } else if (dist < f2) {
                    f2 = dist;
#ifdef _DEBUG
                    rpos2 = pos;
#endif
                }
            }
        }
    }
    f1 = hash_math::sqrt(f1);

    switch (style) {
        case 1:
            return f1;
        case 2:
            return CTurbApp::Noise(rpos);
        case 3:
            f2 = hash_math::sqrt(f2);
            return f2 - f1;
        case 4:
            f2 = hash_math::sqrt(f2);
            return hash_math::sin((f2 - f1) * hash_constants::pi);
        case 5:
            f2 = hash_math::sqrt(f2);
            return f2;
        case 6:
            return hash_math::sin(f1 * (hash_constants::pi / 2.F));
        case 7:
        {
            f2 = hash_math::sqrt(f2);
#ifdef _DEBUG
            const Vector testcell = rpos2 - rpos;
            const float dt = hash_math::sqrt(testcell.Dot(testcell));
            [[maybe_unused]] float sf = dt / (f1 + f2);
#endif
            return step(m_octaves->GetValue() / 100.F, f2 - f1);
        }
        default:
            return f1;
    }
}
