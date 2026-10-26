#pragma once
#include "Options.h"
#include "Inspector.h"
#include "ModelCopy.h"
#include <cstdint>
#include <functional>

namespace fw2 {
struct StampResult { void *model = nullptr; std::uint32_t splines = 0; };
struct WizardResult : StampResult {
    std::uint32_t stamps = 0;
    std::wstring text;
};
using GenerateText = std::function<StampResult(const Options &)>;
using WizardClosed = std::function<void(const Options &, const WizardResult &)>;
HWND OpenWizard(HINSTANCE module, HWND owner, const Options &options,
                bool hasModel, GenerateText generate, WizardClosed closed, InspectModel inspect = {}, SaveModelCopy saveCopy = {});
WizardResult ShowWizard(HINSTANCE module, HWND owner, Options &options,
                        bool hasModel, const GenerateText &generate,
                        const std::function<bool(MSG &)> &preTranslate = {}, InspectModel inspect = {}, SaveModelCopy saveCopy = {});
}
