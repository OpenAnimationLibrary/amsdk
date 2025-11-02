// Yves  04/11/02  \Plugins\Turb\Musgrave\Sampler.h
#pragma once

#include "Matrix34.h"

class SamplerUI {
public:
    TypeInfoArray m_SampleTypeInfoArray;
    HPropertyInfo *m_OptionsInfo;
    HTypePropertyInfo *m_SampleTypeInfo;
    HIntPropertyInfo *m_SamplesInfo;
    HFloatPropertyInfo *m_LengthInfo;
    HVectorPropertyInfo *m_AxisInfo;

    SamplerUI() noexcept = default;
    ~SamplerUI();

    SamplerUI(const SamplerUI&) = delete;
    SamplerUI &operator= (const SamplerUI&) = delete; 
    SamplerUI(SamplerUI &&) = delete; 
    SamplerUI &operator=(SamplerUI &&) = delete; 

    void InitProperties();
};

class Sampler {
public:
    HCategoryProperty *m_Options{nullptr};
    HTypeProperty *m_SampleType{nullptr};
    HIntProperty *m_Samples{nullptr};
    HFloatProperty *m_Length{nullptr};
    HVectorProperty *m_Axis{nullptr};

    int m_Sampler{0};
    int m_Sampled{0};
    Vector m_Samplep;
    Matrix34 m_Trans;

    Sampler() noexcept = default;
    ~Sampler();

    Sampler(const Sampler&) = delete;
    Sampler &operator= (const Sampler&) = delete; 
    Sampler(Sampler &&) = delete; 
    Sampler &operator=(Sampler &&) = delete; 

    void LinkProperties(const SamplerUI &UI);
    HProperty *GetPropertyAt(int &i);
    int InitSampler(const Vector &evalp);
    [[nodiscard]] Vector GetAxis() const;
    Vector &Sample();
};
