// KB  5/13/2003  \Ken105\Plugin\Textures\Wave\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_amplitude;
        case 1:
            return m_wavelength;
        case 2:
            return m_damping;
        case 3:
            return m_propagate;
        case 4:
            return m_cycle;
        default:
            return nullptr;
    }
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    if (m_wavelength->GetValue() == 0.F)
        return TRUE;

    float riprad = evalp.Norm();
    if (riprad == 0.F)
        return TRUE;

    Vector ripple = evalp;
    ripple /= riprad;

    float damp, cycle = 0.F;
    if (m_cycle->GetValue())
        cycle = 2.F * fmod(texinfo->GetTime().GetSeconds(), m_cycle->GetValue()) / m_cycle->GetValue();
    riprad /= m_wavelength->GetValue() * 0.5F - m_propagate->GetValue() - cycle;

    if (m_damping->GetValue() == 100.F)
        damp = 1.F;
    else
        damp = hash_math::pow(m_damping->GetValue() / 100.F, riprad);

    int iriprad;
    if (ISODD(iriprad = (int)riprad))
        ripple.Negate();
    if ((riprad = riprad - iriprad) > 0.5F)
        riprad = 1.F - riprad;
    riprad *= damp * m_amplitude->GetValue() * 0.5F;
    ripple *= riprad;

    *texinfo->GetN() += ripple;
    texinfo->GetN()->Normalize();

    return TRUE;
}
