#pragma once
#include "GlyphOutline.h"
#include <string>

namespace fw2 {
struct Options {
    LOGFONTW font{};
    float height = 10.0F;
    float depth = 2.5F;
    float bevel = 0.2F;  // cm; UI and JSON express mm
    unsigned flags = 0x4 | 0x2 | 0x100;
    bool newModel = false;
    bool keepOpen = true;
    bool applyColor = false;
    COLORREF surfaceColor = RGB(255, 255, 255);
    std::wstring text = L"FontWiz2";
    Options() {
        font.lfWeight = FW_NORMAL; font.lfCharSet = DEFAULT_CHARSET;
        wcscpy_s(font.lfFaceName, L"Arial");
    }
};
}
