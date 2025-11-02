// KB  11/2/00  \Ken90\Plugin\Volume\Steam\Opacity.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Perlin.h"

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

    const float noise = Noise3(turbp); // random swirls
    const float swirl = m_swirl->GetValue() * noise * hash_constants::pi * 2.F;
    const float s = hash_math::sin(swirl);
    const float c = hash_math::cos(swirl);

    const Vector tempp(turbp.x * s + turbp.y * c + noise, turbp.y + m_seconds + noise, turbp.z - m_scaledspeed);
    const float turbulence = m_volbuf.GetTurbulenceValue(tempp);
    turbp.x += turbulence;
    turbp.y += turbulence;

    float radius = turbp.x * turbp.x + turbp.y * turbp.y;
    radius = Brighten(radius, .8f);
    const float s2 = hash_math::abs(hash_math::sin(hash_constants::pi * radius));

    return (1.F - s2 * s2) * falloff;
}
