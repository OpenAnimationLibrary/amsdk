// KB  11/2/00  \Ken90\Plugin\Volume\Dust\Opacity.cpp

#include "StdAfx.h"
#include "Perlin.h"
#include "Custom.h"

HProperty *CustomVolumetric::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_speed;
        case 1:
            return m_swirl;
        case 2:
            return m_scale;
        default:
            return nullptr;
    }
}

float CustomVolumetric::GetOpacity(const float falloff) {
    Vector turbp = m_volbuf.m_p;
    turbp /= m_scale->GetValue();
    const float noise = Noise3(turbp);

    turbp.x += noise;
    turbp.y += noise;

    ASSERT(m_costheta != -1.F); //Must call Init first
    turbp.x += m_costheta;
    turbp.z -= m_depth + noise;
    turbp.y += m_sintheta;

    const float opacity = m_volbuf.GetTurbulenceValue(turbp);

    return opacity * falloff;
}
