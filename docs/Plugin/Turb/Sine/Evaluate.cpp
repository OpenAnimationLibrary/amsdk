// KB  11/3/00  \Ken90\Plugin\Turb\Sine\Evaluate.cpp

#include "Custom.h"
#include "Perlin.h"

HProperty *CustomTurbulence::GetPropertyAt(const int i) {
    if (i == 0)
        return m_octaves;
    return nullptr;
}

float CustomTurbulence::Evaluate(const Vector &evalp) {
    return (hash_math::sin(FractalTurb(evalp, m_octaves->GetValue()) * hash_constants::pi * 2.F) + 1.F) / 2.F;
}
