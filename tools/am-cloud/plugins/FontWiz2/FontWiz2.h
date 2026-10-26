#pragma once
#include "StdAfx.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "FontWiz2Api.h"
#include "GlyphOutline.h"
#include <string>

class HModelCache;
class HTreeObject;
namespace fw2 {
struct Options {
    LOGFONTW font{};
    float height = 10.0F;
    float depth = 2.5F;
    float bevel = 0.2F;  // cm, UI expresses mm
    unsigned flags = 0x4 | 0x2 | 0x100;
    bool newModel = true;
    std::wstring text = L"FontWiz2";
    Options() {
        font.lfWeight = FW_NORMAL; font.lfCharSet = DEFAULT_CHARSET;
        wcscpy_s(font.lfFaceName, L"Arial");
    }
};
bool ShowWizard(HWND owner, Options &options, bool hasModel);
HModelCache *ResolveModel(HTreeObject *object);
HModelCache *Generate(HModelCache *model, const Options &options, std::uint32_t &splines);
}
