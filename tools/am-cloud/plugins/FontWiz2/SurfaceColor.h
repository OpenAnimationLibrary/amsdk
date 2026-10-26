#pragma once
#include "GlyphOutline.h"

namespace fw2 {
inline std::array<float, 3> NormalizedSurfaceColor(COLORREF color) {
    return {GetRValue(color) / 255.0F, GetGValue(color) / 255.0F, GetBValue(color) / 255.0F};
}
}
