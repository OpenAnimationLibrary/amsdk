#include "Settings.h"
#include "FontWiz2Api.h"
#include "geometry/extrude.h"
#include "StampName.h"
#include "SurfaceColor.h"
#include <filesystem>
#include <fstream>
#include <limits>
#include <cmath>
#include <stdexcept>

namespace {
void require(bool condition) { if (!condition) throw std::runtime_error("FontWiz2 settings test failed."); }
std::string replace(std::string value, const std::string &from, const std::string &to) {
    const auto at = value.find(from); require(at != std::string::npos); value.replace(at, from.size(), to); return value;
}
void rejects(const std::string &text) {
    bool failed = false; try { (void)fw2::SettingsFromJson(text); } catch (const std::exception &) { failed = true; }
    require(failed);
}
}

void TestFontWiz2Settings() {
    fw2::Options original;
    require(!original.newModel && original.keepOpen && !original.applyColor && !original.saveModelCopy);
    require(fw2::NormalizedSurfaceColor(RGB(0, 0, 0)) == std::array<float, 3>{0, 0, 0});
    require(fw2::NormalizedSurfaceColor(RGB(255, 255, 255)) == std::array<float, 3>{1, 1, 1});
    require(fw2::NormalizedSurfaceColor(RGB(255, 0, 0)) == std::array<float, 3>{1, 0, 0});
    const auto color = fw2::NormalizedSurfaceColor(RGB(17, 128, 249));
    require(std::abs(color[0] - 0.06666667F) < 0.000001F &&
        std::abs(color[1] - 0.5019608F) < 0.000001F && std::abs(color[2] - 0.9764706F) < 0.000001F);
    original.text = L"Caf\x00e9 \x03a9\r\n\"quoted\" \\ path\t\xD83D\xDE00";
    wcscpy_s(original.font.lfFaceName, L"Times New Roman");
    original.font.lfHeight = -24; original.font.lfWidth = 1;
    original.font.lfEscapement = 100; original.font.lfOrientation = 200;
    original.font.lfWeight = 700; original.font.lfItalic = 1; original.font.lfUnderline = 1;
    original.font.lfStrikeOut = 1; original.font.lfCharSet = 2;
    original.font.lfOutPrecision = 3; original.font.lfClipPrecision = 4;
    original.font.lfQuality = 5; original.font.lfPitchAndFamily = 6;
    original.height = 12.345678F; original.depth = 0.01F; original.bevel = 0.237F;
    original.flags = EX_CLOSE_FRONT | EX_CLOSE_BACK | EX_BEV_FRONT | EX_BEV_SIDE |
        EX_BEV_BACK | EX_ROUND | EX_INWARD | EX_SUB | EX_SUB_ALL;
    original.newModel = false; original.keepOpen = true;
    original.saveModelCopy = true; original.applyColor = true; original.surfaceColor = RGB(17, 128, 249);
    const std::string json = fw2::SettingsToJson(original);
    require(fw2::SettingsToJson(fw2::SettingsFromJson(json)) == json);
    require(fw2::SettingsToJson(fw2::SettingsFromJson("\xEF\xBB\xBF" + json)) == json);
    for (unsigned flags : {0U, unsigned(EX_CLOSE_FRONT), unsigned(EX_BACK | EX_SUB), unsigned(EX_SUB | EX_SUB_ALL)}) {
        fw2::Options draft = original; draft.text.clear(); draft.flags = flags;
        const auto saved = fw2::SettingsToJson(draft);
        require(fw2::SettingsToJson(fw2::SettingsFromJson(saved)) == saved);
    }
    rejects("{}"); rejects(json.substr(0, json.size() / 2)); rejects(json + "garbage");
    rejects(std::string(65537, ' ')); rejects("[[[[[[[[[0]]]]]]]]]");
    const auto legacy = fw2::SettingsFromJson(replace(json, "\"version\": 2", "\"version\": 1"));
    require(!legacy.saveModelCopy);
    const auto oldV2 = fw2::SettingsFromJson(replace(json, "  \"save_model_copy_after_creation\": true,\n", ""));
    require(!oldV2.saveModelCopy);
    rejects(replace(json, "\"save_model_copy_after_creation\": true", "\"save_model_copy_after_creation\": 1"));
    require(!legacy.applyColor && legacy.surfaceColor == RGB(255, 255, 255));
    require(!fw2::Options().applyColor);
    rejects(replace(json, "\"version\": 2", "\"version\": 3"));
    rejects(replace(json, "\"red\": 17", "\"red\": 256"));
    rejects(replace(json, "\"green\": 128", "\"green\": 1.5"));
    rejects(replace(json, "\"apply_color\": true", "\"apply_color\": 1"));
    rejects(replace(json, "\"keep_window_open\": true", "\"keep_window_open\": \"true\""));
    rejects(replace(json, "\"em_height_cm\": ", "\"em_height_cm\": -"));
    rejects(replace(json, "\"charset\": 2", "\"charset\": 256"));
    rejects(replace(json, "\"weight\": 700", "\"weight\": 700.5"));
    rejects(replace(json, "\"subdivision\": \"all\"", "\"subdivision\": \"unknown\""));
    rejects(replace(json, "Times New Roman", std::string(40, 'A')));
    rejects(replace(json, "Times New Roman", std::string("\xC3\x28", 2)));
    const std::filesystem::path path = std::filesystem::current_path() / L"FontWiz2-\x00e9-settings.json";
    fw2::SaveSettingsFile(path.wstring(), original);
    require(fw2::SettingsToJson(fw2::LoadSettingsFile(path.wstring())) == json);
    fw2::Options changed = original; changed.text = L"second save"; changed.keepOpen = false;
    fw2::SaveSettingsFile(path.wstring(), changed);
    require(fw2::SettingsToJson(fw2::LoadSettingsFile(path.wstring())) == fw2::SettingsToJson(changed));
    fw2::Options invalid = original; invalid.height = std::numeric_limits<float>::quiet_NaN();
    bool failed = false; try { fw2::SaveSettingsFile(path.wstring(), invalid); } catch (const std::exception &) { failed = true; }
    require(failed && fw2::LoadSettingsFile(path.wstring()).text == changed.text);
    { std::ofstream file(path, std::ios::binary | std::ios::trunc); file << "{invalid"; }
    fw2::Options unchanged = changed; failed = false;
    try { unchanged = fw2::LoadSettingsFile(path.wstring()); } catch (const std::exception &) { failed = true; }
    require(failed && fw2::SettingsToJson(unchanged) == fw2::SettingsToJson(changed));
    std::filesystem::remove(path);
    require(fw2::StampName(L"Hello World!") == L"Hello World!");
    require(fw2::StampName(L"123456789012345678901234") == L"12345678901234567890");
    require(fw2::StampName(L"\r\n  Hello\tA") == L"Hello A");
    require(fw2::StampName(L"123456789012345678901234", 2) == L"123456789012345678 2");
    require(fw2::StampName(L"123456789012345678901234", 100) == L"1234567890123456 100");
    require(fw2::StampName(L"\t\n ") == L"Text");
}
