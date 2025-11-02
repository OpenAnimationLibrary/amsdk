//NAP  12/11/2004  \Noel120\Include\RGBFloat.inl
#pragma once

#include "RGBFloat.h"
#include "RGBHalf.h"
#include "RGBByte.h"
#include "ColorBuf.h"
#include "RGBByte.inl"

//*********************************************************************
//*** RGBFloat
//*********************************************************************
HASH_INLINE RGBFloat::RGBFloat(const RGBHalf &other) noexcept {
    *this = other.GetAsFloat();
}

HASH_INLINE RGBFloat &RGBFloat::operator +=(const RGBHalf &other) noexcept {
    *this += other.GetAsFloat();
    return *this;
}

HASH_INLINE RGBFloat &RGBFloat::operator *=(const RGBHalf &other) noexcept {
    *this *= other.GetAsFloat();
    return *this;
}

HASH_INLINE RGBFloat &RGBFloat::operator=(const RGBHalf &other) noexcept {
    *this = other.GetAsFloat();
    return *this;
}

HASH_INLINE RGBFloat::RGBFloat(const RGBByte &other) {
    *this = other.GetNormalizedRGBFloat();
}

HASH_INLINE RGBFloat &RGBFloat::operator +=(const RGBByte &other) {
    *this += other.GetNormalizedRGBFloat();
    return *this;
}

HASH_INLINE RGBFloat &RGBFloat::operator=(const ColorBuf &other) noexcept {
    *this = other.GetNormalizedRGBFloat();
    return *this;
}

HASH_INLINE RGBFloat::RGBFloat(const ColorBuf &other) noexcept {
    *this = other.GetNormalizedRGBFloat();
}

//*********************************************************************
//*** RGBAFloat
//*********************************************************************
HASH_INLINE RGBAFloat::RGBAFloat(const RGBAHalf &other) noexcept : m_color(other.Color()), m_alpha(other.Alpha()) {}
HASH_INLINE RGBAFloat::RGBAFloat(const RGBHalf &other) noexcept : m_color(other) {}

HASH_INLINE void RGBAFloat::SetColor(const RGBHalf &other) noexcept {
    m_color = other.GetAsFloat();
}

HASH_INLINE RGBAFloat::RGBAFloat(const RGBAByte &other) noexcept {
    //NAP Bitmap should I use Color() instead???
    *this = other.GetRGBAFloat();
}

HASH_INLINE RGBAFloat::RGBAFloat(const ColorBuf &other) noexcept {
    *this = other.GetNormalizedRGBAFloat();
}

//*********************************************************************
//*** RGBAFloat
//*********************************************************************
HASH_INLINE YAFloat::YAFloat(const YAHalf &other) noexcept : m_luminance(other.m_luminance) {
    m_alpha = other.m_alpha;
}

HASH_INLINE YAFloat::YAFloat(const YAByte &other) noexcept : m_luminance((float)other.m_luminance / MAXCOLOR) {
    //NAP Bitmap should I use Color() instead???
    m_alpha = (float)other.m_alpha / MAXCOLOR;
}

HASH_INLINE YAFloat::YAFloat(const RGBAHalf &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = other.Red() * 0.2125F + other.Green() * 0.7154F + other.Blue() * 0.0721F;
    m_alpha = other.Alpha();
}

HASH_INLINE YAFloat::YAFloat(const RGBAByte &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = ((float)other.Red() * 0.2125F + (float)other.Green() * 0.7154F + (float)other.Blue() * 0.0721F) / MAXCOLOR;
    m_alpha = (float)other.Alpha() / MAXCOLOR;
}

HASH_INLINE YAFloat::YAFloat(const ColorBuf &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = ((float)other.red * 0.2125F + (float)other.green * 0.7154F + (float)other.blue * 0.0721F) / MAXCOLOR;
    m_alpha = 1.F;
}

HASH_INLINE YAFloat::YAFloat(const RGBHalf &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = other.Red() * 0.2125F + other.Green() * 0.7154F + other.Blue() * 0.0721F;
    m_alpha = 1.F;
}

HASH_INLINE YAFloat::YAFloat(const RGBByte &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = ((float)other.Red() * 0.2125F + (float)other.Green() * 0.7154F + (float)other.Blue() * 0.0721F) / MAXCOLOR;
    m_alpha = 1.F;
}
