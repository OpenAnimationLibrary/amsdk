// Yves  03/11/17  \My Plugins\Turb\Musgrave\Evaluate.cpp

#include "Custom.h"

HProperty *CustomTurbulence::GetPropertyAt(int i) {
    HProperty *Property = m_FractalNoiser.GetPropertyAt(i);
    if (Property)
        return Property;
    Property = m_Transferer.GetPropertyAt(i);
    if (Property)
        return Property;
    Property = m_Sampler.GetPropertyAt(i);
    if (Property)
        return Property;
    return nullptr;
}

bool CustomTurbulence::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    return m_FractalNoiser.OnPtrMessage(ptrmessage, ptruplink, lparam, time);
}

// Value to return should be in the range 0.0 to 1.0
// But any negative values between 0.0 and -1.0 will be ABSed by A:M

float CustomTurbulence::Evaluate(const Vector &evalp) {
    const int samples = m_Sampler.InitSampler(evalp);
    float Value = 0.F;
    for (int i = 0; i < samples; i++)
        Value += m_FractalNoiser.Evaluate(m_Sampler.Sample());
    Value /= (float)samples;
    return m_Transferer.Transfer(Value);
}
