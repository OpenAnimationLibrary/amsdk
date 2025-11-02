// RC  10/1/2001  \Randy90\Plugin\Textures\Villa\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_noise;
        case 1:
            return m_freq;
        case 2:
            return m_fo;
        case 3:
            return m_bo;
//        case 4:
//            return m_ir;
        default:
            return nullptr;
    }
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const float arefl = m_noise->GetValue() / 100.F;
    const float arefr = m_freq->GetValue() / 100.F;
    const float falloff = m_fo->GetValue();
    const auto invert = m_bo->GetValue();
//    float invertr = (float)m_ir->GetValue();

    Vector nn = *texinfo->GetN();
    nn.Normalize();
    const Vector I = texinfo->GetD();
    float alpha = nn.Dot(-I);
    alpha = alpha < 0.F ? 0.F : alpha;
    float alphar = alpha;

    if (invert) {
        alpha = 1.F - alpha;
        alphar = 1.F - alphar;
    }

    alpha = hash_math::pow(alpha, falloff);
    alphar = hash_math::pow(alphar, falloff);

    // mix it
    float mirror = texinfo->GetAttr()->GetReflectivity()->GetValue();
    Vector glass(texinfo->GetAttr()->GetTransparency()->GetValue());
    mirror -= alphar * (arefl * mirror);
    glass -= alpha * (arefr * glass);
    texinfo->GetAttr()->GetReflectivity()->SetValue(mirror);
    texinfo->GetAttr()->GetTransparency()->SetValue(glass.x);

    return TRUE;
}
