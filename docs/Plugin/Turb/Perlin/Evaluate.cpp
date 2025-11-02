// KB  9/26/01  \Ken90\Plugin\Turb\Perlin\Evaluate.cpp

#include "Custom.h"
#include "Perlin.h"

namespace {
    float octaves2[] = {.6666F, .3333F};
    float octaves3[] = {.5714F, .2857F, .1428F};
    float octaves4[] = {.5333F, .2666F, .1333F, .0666F};
    float octaves5[] = {.5161F, .2580F, .1290F, .0645F, .0322F};
}

HProperty *CustomTurbulence::GetPropertyAt(const int i) {
    if (i == 0)
        return m_octaves;
    return nullptr;
}

float CustomTurbulence::Evaluate(const Vector &evalp) {
    Vector evalp1(evalp);

    float result = 0.F;
    for (int octave = 0; octave < m_octaves->GetValue(); ++octave, evalp1 *= 2.F) {
        switch (m_octaves->GetValue()) {
        case 1:
            result += hash_math::abs(Noise3(evalp1));
            break;
        case 2:
            result += hash_math::abs(Noise3(evalp1)) * octaves2[octave];
            break;
        case 3:
            result += hash_math::abs(Noise3(evalp1)) * octaves3[octave];
            break;
        case 4:
            result += hash_math::abs(Noise3(evalp1)) * octaves4[octave];
            break;
        case 5:
            result += hash_math::abs(Noise3(evalp1)) * octaves5[octave];
            break;
        }
    }
    return result * 2.F;
}
