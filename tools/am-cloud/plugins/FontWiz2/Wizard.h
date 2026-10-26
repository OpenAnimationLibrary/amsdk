#pragma once
#include "Options.h"
#include <cstdint>
#include <functional>

namespace fw2 {
struct StampResult { void *model = nullptr; std::uint32_t splines = 0; };
struct WizardResult : StampResult {
    std::uint32_t stamps = 0;
    std::wstring text;
};
using GenerateText = std::function<StampResult(const Options &)>;
WizardResult ShowWizard(HINSTANCE module, HWND owner, Options &options,
                        bool hasModel, const GenerateText &generate);
}
