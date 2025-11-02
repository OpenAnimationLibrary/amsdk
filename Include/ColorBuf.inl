//Dan  7/25/2004  \DanLP115\Include\ColorBuf.inl
#pragma once

#include "ColorBuf.h"

HASH_INLINE ColorBuf::ColorBuf(const RGBAFloat &s_color) noexcept {    // NOLINT(cppcoreguidelines-pro-type-member-init)
    red = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Red() * MAXCOLOR + .5F)));
    green = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Green() * MAXCOLOR + .5F)));
    blue = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Blue() * MAXCOLOR + .5F)));
    alpha = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Alpha() * MAXCOLOR + .5F)));
}

HASH_INLINE RGBFloat ColorBuf::Get() const noexcept {
    return RGBFloat((float)red / MAXCOLOR, (float)green / MAXCOLOR, (float)blue / MAXCOLOR);
}

HASH_INLINE RGBFloat ColorBuf::GetFactoredRGBFloat() const noexcept {
    return RGBFloat(red, green, blue);
}

HASH_INLINE RGBFloat ColorBuf::GetNormalizedRGBFloat() const noexcept {
    return RGBFloat((float)red / MAXCOLOR, (float)green / MAXCOLOR, (float)blue / MAXCOLOR);
}

HASH_INLINE RGBAFloat ColorBuf::GetNormalizedRGBAFloat() const noexcept {
    return RGBAFloat((float)red / MAXCOLOR, (float)green / MAXCOLOR, (float)blue / MAXCOLOR, (float)alpha / MAXCOLOR);
}
