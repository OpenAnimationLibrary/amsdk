// Yves  04/11/02  \Plugins\Turb\Musgrave\Sampler.cpp
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered

// ReSharper disable once CppUnusedIncludeDirective
#include "StdAfx.h"
#include "Custom.h"

SamplerUI::~SamplerUI() {
    delete m_OptionsInfo;
    delete m_SamplesInfo;
    delete m_SampleTypeInfo;
    delete m_LengthInfo;
    delete m_AxisInfo;
}

void SamplerUI::InitProperties() {
    CString string;

    string.LoadString(IDS_SAMPLOPTIONS);
    m_OptionsInfo = HPropertyInfo::New(string, "SamplingOptions");

    // Sampling Patterns
    m_SampleTypeInfoArray.SetArraySize(7);
    for (int i = 0; i < 7; i++) {
        HTypeInfo *typeinfo = m_SampleTypeInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("PointSample");
                string.LoadString(IDS_S_POINT);
                break;
            case 1:
                typeinfo->SetMatchName("RadCylindrical");
                string.LoadString(IDS_S_RADCYLINDRICAL);
                break;
            case 2:
                typeinfo->SetMatchName("RadSpherical");
                string.LoadString(IDS_S_RADSPHERICAL);
                break;
            case 3:
                typeinfo->SetMatchName("PolAngle");
                string.LoadString(IDS_S_POLANGLE);
                break;
            case 4:
                typeinfo->SetMatchName("PolArc");
                string.LoadString(IDS_S_POLARC);
                break;
            case 5:
                typeinfo->SetMatchName("CirAngle");
                string.LoadString(IDS_S_CIRANGLE);
                break;
            case 6:
                typeinfo->SetMatchName("CirArc");
                string.LoadString(IDS_S_CIRARC);
                break;
        }
        typeinfo->SetLocalizedName(string.GetBuffer());
    }
    string.LoadString(IDS_SAMPLEFN);
    m_SampleTypeInfo = HTypePropertyInfo::New(string, "SampleFn", &m_SampleTypeInfoArray);
    m_SampleTypeInfo->SetDefaultIndex(0);
    m_SampleTypeInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Number of samples for integration
    string.LoadString(IDS_NSAMPLES);
    m_SamplesInfo = HIntPropertyInfo::New(string, "Samples");
    m_SamplesInfo->SetDefaultValue(5);
    m_SamplesInfo->SetMinValue(2);
    m_SamplesInfo->SetMaxValue(25);
    m_SamplesInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Length of samples in degrees or in units
    string.LoadString(IDS_SAMPLELEN);
    m_LengthInfo = HFloatPropertyInfo::New(string, "Samples Length");
    m_LengthInfo->SetDefaultValue(2.F);
    m_LengthInfo->SetMinValue(0.F);
    m_LengthInfo->SetMaxValue(100.F);
    m_LengthInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Axis
    string.LoadString(IDS_SAMPLEAXIS);
    m_AxisInfo = HVectorPropertyInfo::New(string, "Sampling Axis");
    m_AxisInfo->SetDefaultValue(Vector(0.F, 0.F, 1.F));
    m_AxisInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
}

Sampler::~Sampler() {
    if (m_SampleType) {
        if (m_Options)
            m_Options->RemoveProperty(m_SampleType);
        delete m_SampleType;
    }
    if (m_Samples) {
        if (m_Options)
            m_Options->RemoveProperty(m_Samples);
        delete m_Samples;
    }
    if (m_Length) {
        if (m_Options)
            m_Options->RemoveProperty(m_Length);
        delete m_Length;
    }
    if (m_Axis) {
        if (m_Options)
            m_Options->RemoveProperty(m_Axis);
        delete m_Axis;
    }

    delete m_Options;
}

void Sampler::LinkProperties(const SamplerUI &UI) {
    m_Options = HCategoryProperty::New(UI.m_OptionsInfo);
    m_SampleType = HTypeProperty::New(UI.m_SampleTypeInfo);
    m_Options->AddProperty(m_SampleType);
    m_Samples = HIntProperty::New(UI.m_SamplesInfo);
    m_Options->AddProperty(m_Samples);
    m_Length = HFloatProperty::New(UI.m_LengthInfo);
    m_Options->AddProperty(m_Length);
    m_Axis = HVectorProperty::New(UI.m_AxisInfo);
    m_Options->AddProperty(m_Axis);
}

// ReSharper disable once CppMemberFunctionMayBeConst
HProperty *Sampler::GetPropertyAt(int &i) {
    if (i == 0)
        return m_Options;
    i--;
    return nullptr;
}

int Sampler::InitSampler(const Vector &evalp) {
    m_Sampled = 0;
    m_Sampler = m_SampleType->GetValue();
    switch (m_Sampler) {
        case 0: // No Sampling
            m_Samplep = evalp;
            return 1;

        case 1: // Radial Cylindrical
        case 2: // Radial Spherical
        {
            const int Samples = m_Samples->GetValue();
            const float Length = m_Length->GetValue();
            Vector Xlate(evalp);
            if (m_Sampler == 1) {
                // Find point on axis nearest to evalp for pivot
                // axis*t where t=f/g and f=-evalp.x*Axis.x-evalp.y*Axis.y-evalp.z*Axis.z
                // and g=Axis.x*Axis.x+Axis.y*Axis.y+Axis.z*Axis.z
                Vector P(evalp);
                P.Negate();
                const Vector Axis = GetAxis();
                const Vector Pivot = Axis * (-P.Dot(Axis) / Axis.Dot());
                Xlate -= Pivot;
            }
            Xlate.Normalize();
            m_Trans.SetIdentity();
            m_Trans.SetTranslate(Xlate * (Length / -2.F));
            m_Samplep = evalp * m_Trans;
            m_Trans.SetTranslate(Xlate * (Length / (float)(Samples - 1)));
            return Samples;
        }
        case 3: // Pole to pole - Angle
        case 4: // Pole to pole - Arc
        {
            Vector Axis = GetAxis();
            // Normal between evalp and Pole
            Axis = Axis.Cross(evalp);
            const int Samples = m_Samples->GetValue();
            const float Length = m_Length->GetValue();
            // lets assume we are working in angle units
            float Angle = Length / hash_constants::radians;
            if (m_Sampler == 4) {
                // we are working in length units...
                const float Radius = evalp.Norm();
                if (Radius > Length)
                    // scale angle according to radius.
                    Angle = Length / Radius;
            }
            // first rotate backward the sample point to half the angle
            // the rotation is performed around the Axis which is the
            // normal between the pole vector and the eval point. 
            // So we have a pole to pole rotation.
            m_Trans = RotateVRadians(-Angle / 2.F, Axis);
            m_Samplep = evalp * m_Trans;
            // then prepare for incremental rotations
            m_Trans = RotateVRadians(Angle / (float)(Samples - 1), Axis);
            return Samples;
        }
        case 5: // Circular Cylindrical - Angle
        case 6: // Circular Cylindrical - Arc
        {
            const Vector Axis = GetAxis();
            const int Samples = m_Samples->GetValue();
            // lets assume we are working in angle units
            const float Length = m_Length->GetValue();
            float Angle = Length / hash_constants::radians;
            if (m_Sampler == 6) {
                // we are working in length units...
                // compute the projection of evalp onto the pole vector
                // then subtract the projection from evalp in order to
                // bring evalp relative to origin to compute rotations.
                const Vector scaledp = evalp - Axis * Axis.Dot(evalp);
                const float Radius = scaledp.Norm();
                if (Radius > Length)
                    // scale angle according to radius.
                    Angle = Length / Radius;
            }
            // first rotate backward the sample point to half the angle
            // the rotation is performed around the pole. 
            // So we have a cylindrical rotation.
            m_Trans = RotateVRadians(-Angle / 2.F, Axis);
            m_Samplep = evalp * m_Trans;
            // then prepare for incrememtal rotations
            m_Trans = RotateVRadians(Angle / (float)(Samples - 1), Axis);
            return Samples;
        }
    }
    return 0;
}

Vector &Sampler::Sample() {
    if (m_Sampler && m_Sampled)
        m_Samplep = m_Samplep * m_Trans;
    m_Sampled ++;
    return m_Samplep;
}

Vector Sampler::GetAxis() const {
    Vector Axis = m_Axis->GetValue();
    if (Axis.IsZero())
        Axis.z = 1.F;
    else
        Axis.NormalizeLength();
    return Axis;
}
