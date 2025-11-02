//Dan  8/3/2004  \DanLP115\Include\HalfColorBuf.inl
#pragma once

#include "RGBHalf.h"
#include "RGBFloat.h"
#include "RGBByte.h"
#include "ColorBuf.h"
//******************************************************************************
//*** RGBHalf
//******************************************************************************

HASH_INLINE RGBHalf::RGBHalf(const RGBFloat &other) noexcept {
    m_red = other.Red();
    m_green = other.Green();
    m_blue = other.Blue();
}

#pragma warning (disable : 522) // message #522: function "GetAsFloat()" redeclared "inline" after being called
HASH_INLINE RGBFloat RGBHalf::GetAsFloat() const noexcept {
    return RGBFloat(m_red, m_green, m_blue);
}

HASH_INLINE RGBHalf &RGBHalf::operator=(const RGBFloat &other) noexcept {
    SetRed(other.Red());
    SetGreen(other.Green());
    SetBlue(other.Blue());
    return *this;
}

HASH_INLINE RGBHalf &RGBHalf::operator+=(const RGBFloat &other) noexcept {
    m_red += other.Red();
    m_green += other.Green();
    m_blue += other.Blue();
    return *this;
}

HASH_INLINE RGBHalf &RGBHalf::operator*=(const RGBFloat &other) noexcept {
    m_red *= other.Red();
    m_green *= other.Green();
    m_blue *= other.Blue();
    return *this;
}

//******************************************************************************
//*** RGBAHalf
//******************************************************************************

HASH_INLINE RGBAHalf::RGBAHalf(const RGBFloat &other, const float alpha) noexcept {
    m_color.SetRed(other.Red());
    m_color.SetGreen(other.Green());
    m_color.SetBlue(other.Blue());
    m_alpha = alpha;
}

HASH_INLINE RGBAHalf::RGBAHalf(const RGBAFloat &other) noexcept {
    m_color.SetRed(other.Red());
    m_color.SetGreen(other.Green());
    m_color.SetBlue(other.Blue());
    m_alpha = other.m_alpha;
}

HASH_INLINE RGBAHalf::RGBAHalf(const ColorBuf &other) noexcept {
    m_color.Set((float)other.Red() / MAXCOLOR, (float)other.Green() / MAXCOLOR, (float)other.Blue() / MAXCOLOR);
    m_alpha = (float)other.Alpha() / MAXCOLOR;
}

HASH_INLINE RGBAHalf &RGBAHalf::operator=(const RGBAFloat &other) noexcept {
    //    m_color = other.Color(); ?? Todo 
    m_color.SetRed(other.Color().Red());
    m_color.SetGreen(other.Color().Green());
    m_color.SetBlue(other.Color().Blue());
    m_alpha = other.Alpha();
    return *this;
}

HASH_INLINE RGBAFloat RGBAHalf::GetAsFloat() const noexcept {
    return RGBAFloat(m_color.m_red, m_color.m_green, m_color.m_blue, m_alpha);
}

HASH_INLINE RGBFloat RGBAHalf::GetColorAsFloat() const noexcept {
    return RGBFloat(m_color.m_red, m_color.m_green, m_color.m_blue);
}

//******************************************************************************
//*** YAHalf
//******************************************************************************
HASH_INLINE YAHalf::YAHalf(const YAFloat &other) noexcept {
    m_luminance = other.Luminance();
    m_alpha = other.Alpha();
}

HASH_INLINE YAHalf::YAHalf(const YAByte &other) noexcept {
    m_luminance = (float)other.Luminance() / MAXCOLOR;
    m_alpha = (float)other.Alpha() / MAXCOLOR;
}

HASH_INLINE YAHalf &YAHalf::operator=(const YAFloat &other) noexcept {
    m_luminance = other.Luminance();
    m_alpha = other.Alpha();
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator=(const YAByte &other) noexcept {
    m_luminance = (float)other.Luminance() / MAXCOLOR;
    m_alpha = (float)other.Alpha() / MAXCOLOR;
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator=(const ColorBuf &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = (other.red * 0.2125F + other.green * 0.7154F + other.blue * 0.0721F) / MAXCOLOR;
    m_alpha = 1.F;
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator=(const RGBFloat &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = other.Red() * 0.2125F + other.Green() * 0.7154F + other.Blue() * 0.0721F;
    m_alpha = 1.F;
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator=(const RGBAFloat &other) noexcept {
    //Compute the CIE Rec.709 luminance
    m_luminance = other.Red() * 0.2125F + other.Green() * 0.7154F + other.Blue() * 0.0721F;
    m_alpha = other.Alpha();
    return *this;
}
