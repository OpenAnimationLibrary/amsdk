// Yves  2005/03/03  \Plugin\Turb\Extended GridTurb\Evaluate.cpp

#include "Custom.h"
#include "texfuncs.h"
#include "TurbApp.h"

extern CTurbApp theApp;

HProperty *CustomTurbulence::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_GridType;
        case 1:
            return m_UseX;
        case 2:
            return m_UseY;
        case 3:
            return m_UseZ;
        case 4:
            return m_UseAzimuth;
        case 5:
            return m_UseElevation;
        case 6:
            return m_UseRadial;
        default:
            return nullptr;
    }
}

float CustomTurbulence::Evaluate(const Vector &evalp) {
    if (m_UIDirty)
        UpdateUI();

    const Vector P = evalp;
    float turb = 0.F;
    float x = P.x;
    float y = P.y;
    float z = P.z;
    float frequency;
    float scale;
    float v;
    switch (m_GridType->GetValue()) {
        case 0: //	CUBICAL
            if (m_UseX->GetValue()) {
                v = Repeat(x, hash_math::rcp(m_XSize->GetValue()));
                scale = SmoothPulse(1.F - m_XRatio->GetValue(), 1.F, m_XBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            if (m_UseY->GetValue()) {
                v = Repeat(y, hash_math::rcp(m_YSize->GetValue()));
                scale = SmoothPulse(1.F - m_YRatio->GetValue(), 1.F, m_YBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            if (m_UseZ->GetValue()) {
                v = Repeat(z, hash_math::rcp(m_ZSize->GetValue()));
                scale = SmoothPulse(1.F - m_ZRatio->GetValue(), 1.F, m_ZBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            break;

        case 1: //	Spherical
            MapSphere(P, x, y, z);
            if (m_UseAzimuth->GetValue()) {
                frequency = m_AzimuthSize->GetValue();
                v = Repeat(x, frequency);
                if (const float ratio = m_AzimuthRatio->GetValue(); float size = m_AzimuthStripe->GetValue()) {
                    if (v > 0.5F)
                        v -= 1.F;
                    v = hash_math::abs(hash_math::sin(hash_constants::pi_2 * v / frequency) * y);
                    const float fuzz = size * m_AzimuthBlur->GetValue();
                    size *= 0.5F;
                    scale = SmoothStep(size - fuzz, size + fuzz, v);
                } else
                    scale = SmoothPulse(1.F - ratio, 1.F, m_AzimuthBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            if (m_UseElevation->GetValue()) {
                frequency = m_ElevationSize->GetValue();
                v = Repeat(y, frequency);
                scale = SmoothPulse(1.F - m_ElevationRatio->GetValue(), 1.F, m_ElevationBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            if (m_UseZ->GetValue()) {
                v = Repeat(z, hash_math::rcp(m_ZSize->GetValue()));
                scale = SmoothPulse(1.F - m_ZRatio->GetValue(), 1.F, m_ZBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            break;

        case 2: //	Cylindrical
            MapCylinder(P, x, y);
            if (m_UseAzimuth->GetValue()) {
                frequency = m_AzimuthSize->GetValue();
                v = Repeat(x, frequency);
                if (const float ratio = m_AzimuthRatio->GetValue(); float size = m_AzimuthStripe->GetValue()) {
                    if (v > 0.5F)
                        v -= 1.F;
                    v = hash_math::abs(hash_math::sin(hash_constants::pi_2 * v / frequency) * y);
                    const float fuzz = size * m_AzimuthBlur->GetValue();
                    size *= 0.5F;
                    scale = SmoothStep(size - fuzz, size + fuzz, v);
                } else
                    scale = SmoothPulse(1.F - ratio, 1.F, m_AzimuthBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            if (m_UseRadial->GetValue()) {
                v = Repeat(y, hash_math::rcp(m_RadialSize->GetValue()));
                scale = SmoothPulse(1.F - m_RadialRatio->GetValue(), 1.F, m_RadialBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            if (m_UseZ->GetValue()) {
                v = Repeat(z, hash_math::rcp(m_ZSize->GetValue()));
                scale = SmoothPulse(1.F - m_ZRatio->GetValue(), 1.F, m_ZBlur->GetValue(), v);
                if (scale > turb)
                    turb = scale;
            }
            break;

        default:
            turb = 0.F;
    }
    turb = turb > 1.F ? 1.F : turb;
    return turb;
}

void CustomTurbulence::MapCylinder(Vector e, float &u, float &v) {
    // v = distance from x=0,y=0 axis
    v = hash_math::sqrt(e.x * e.x + e.y * e.y);
    e.Normalize();
    // u = angle position converted to [0..1] range
    u = (-hash_math::atan2(e.y, e.x) + hash_constants::pi) / hash_constants::pi_2; // azimuth
}

void CustomTurbulence::MapSphere(Vector e, float &u, float &v, float &w) {
    w = e.NormalizeLength(); // distance
    u = (-hash_math::atan2(e.y, e.x) + hash_constants::pi) / hash_constants::pi_2; // azimuth
    v = 0.5F - hash_math::acos(e.z) / hash_constants::pi; // elevation
}
