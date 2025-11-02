// KB  11/2/00  \Ken90\Plugin\Volume\Mist\Opacity.cpp

//#include "StdAfx.h"
#include "Custom.h"

HProperty *CustomVolumetric::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_val;
        case 1:
            return m_height;
        case 2:
            return m_scale;
        default:
            return nullptr;
    }
}

float CustomVolumetric::GetOpacity(const float falloff) {
    const float opacity = m_val->GetValue();
    return opacity * falloff;
}
