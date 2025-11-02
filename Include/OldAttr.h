//Dan  7/23/2004  \DanLP115\Include\OldAttr.h
#pragma once

#include "RGBFloat.inl"

class Attr final {
public:
    char m_name[256]{};
    RGBFloat m_diffusecolor;
    float m_diffusefalloff;
    RGBFloat m_ambiancecolor;
    float m_ambiance;
    RGBFloat m_specularcolor;
    float m_specularsize;
    float m_specularintensity;
    float m_roughness;
    float m_roughnessscale;
    float m_transparency;
    float m_density;
    float m_refraction;
    float m_translucency;
    float m_reflectivity;
    float m_reflectivityfalloff;
    float m_radiance;
    bool m_isglow;

    Attr() noexcept : m_diffusefalloff(1.F),
                      m_ambiance(0.F),
                      m_specularsize(0.F),
                      m_specularintensity(1.F),
                      m_roughness(0.F),
                      m_roughnessscale(1.F),
                      m_transparency(0.F),
                      m_density(0.F),
                      m_refraction(1.F),
                      m_translucency(0.F),
                      m_reflectivity(0.F),
                      m_reflectivityfalloff(0.F),
                      m_radiance(1.F),
                      m_isglow(false) {
        m_name[0] = '\0';
        m_diffusecolor.SetZero();
        m_ambiancecolor.SetZero();
        m_specularcolor.SetZero();
    }

    bool operator==(const Attr &other) const noexcept {
        return m_diffusecolor == other.m_diffusecolor && floatEQ(m_diffusefalloff, other.m_diffusefalloff) && m_ambiancecolor == other.m_ambiancecolor && floatEQ(m_ambiance, other.m_ambiance)
        && m_specularcolor == other.m_specularcolor && floatEQ(m_specularsize, other.m_specularsize) && floatEQ(m_specularintensity, other.m_specularintensity) && floatEQ(m_roughness, other.m_roughness)
        && floatEQ(m_roughnessscale, other.m_roughnessscale) && floatEQ(m_transparency, other.m_transparency) && floatEQ(m_density, other.m_density) && floatEQ(m_refraction, other.m_refraction)
        && floatEQ(m_translucency, other.m_translucency) && floatEQ(m_reflectivity, other.m_reflectivity) && floatEQ(m_reflectivityfalloff, other.m_reflectivityfalloff)
        && floatEQ(m_radiance, other.m_radiance) && m_isglow == other.m_isglow;
    }
};
