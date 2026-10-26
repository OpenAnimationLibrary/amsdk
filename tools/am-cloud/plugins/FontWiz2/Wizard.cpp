#include "Wizard.h"
#include "Settings.h"
#include "FontWiz2Api.h"
#include "resource.h"
#include "geometry/extrude.h"
#include <commdlg.h>
#include <array>
#include <algorithm>
#include <cmath>
#include <cwchar>
#include <cwctype>
#include <limits>
#include <stdexcept>

namespace fw2 {
namespace {
struct State {
    Options &options;
    bool hasModel;
    const GenerateText &generate;
    HFONT preview = nullptr;
    bool applying = false;
    bool busy = false;
    std::wstring settingsPath;
    WizardResult result;
};
const std::array<int, 8> controlIDs = {IDC_FW2_FRONT, IDC_FW2_SIDES, IDC_FW2_BACK,
    IDC_FW2_BEVFRONT, IDC_FW2_BEVSIDE, IDC_FW2_BEVBACK, IDC_FW2_ROUND, IDC_FW2_INWARD};
const std::array<unsigned, 8> controlFlags = {EX_CLOSE_FRONT, EX_BACK, EX_CLOSE_BACK,
    EX_BEV_FRONT, EX_BEV_SIDE, EX_BEV_BACK, EX_ROUND, EX_INWARD};
void number(HWND dialog, int id, double value) {
    wchar_t text[64]{}; swprintf_s(text, L"%.9g", value); SetDlgItemTextW(dialog, id, text);
}
double number(HWND dialog, int id, double minimum, double maximum) {
    wchar_t text[64]{}; GetDlgItemTextW(dialog, id, text, 64);
    wchar_t *end = nullptr; const double value = wcstod(text, &end);
    while (end && iswspace(*end)) ++end;
    if (end == text || !end || *end || !std::isfinite(value) || value < minimum || value > maximum)
        throw std::runtime_error("Enter em height/extrusion from 0.01 to 10000 cm and bevel from 0 to 1000 mm.");
    return value;
}
void preview(HWND dialog, State &state) {
    std::wstring name = state.options.font.lfFaceName;
    if (state.options.font.lfWeight >= FW_BOLD) name += L" Bold";
    if (state.options.font.lfItalic) name += L" Italic";
    SetDlgItemTextW(dialog, IDC_FW2_FONT, name.c_str());
    wchar_t text[FW2_MAX_TEXT + 1]{};
    GetDlgItemTextW(dialog, IDC_FW2_TEXT, text, static_cast<int>(FW2_MAX_TEXT + 1));
    SetDlgItemTextW(dialog, IDC_FW2_SAMPLE, text);
    LOGFONTW font = state.options.font; font.lfHeight = -24;
    HFONT replacement = CreateFontIndirectW(&font);
    if (replacement) {
        SendDlgItemMessageW(dialog, IDC_FW2_SAMPLE, WM_SETFONT, reinterpret_cast<WPARAM>(replacement), TRUE);
        if (state.preview) DeleteObject(state.preview);
        state.preview = replacement;
    }
}
Options readControls(HWND dialog, const State &state) {
    Options options = state.options;
    wchar_t text[FW2_MAX_TEXT + 1]{};
    GetDlgItemTextW(dialog, IDC_FW2_TEXT, text, static_cast<int>(FW2_MAX_TEXT + 1));
    options.text = text;
    options.height = static_cast<float>(number(dialog, IDC_FW2_HEIGHT, 0.01F, 10000));
    options.depth = static_cast<float>(number(dialog, IDC_FW2_DEPTH, 0.01F, 10000));
    options.bevel = static_cast<float>(number(dialog, IDC_FW2_BEVEL, 0, 1000) / 10.0);
    options.flags = 0;
    for (std::size_t i = 0; i < controlIDs.size(); ++i)
        if (IsDlgButtonChecked(dialog, controlIDs[i]) == BST_CHECKED) options.flags |= controlFlags[i];
    const LRESULT subdivision = SendDlgItemMessageW(dialog, IDC_FW2_SUBDIVIDE, CB_GETCURSEL, 0, 0);
    if (subdivision > 0) options.flags |= EX_SUB;
    if (subdivision == 2) options.flags |= EX_SUB_ALL;
    options.newModel = IsDlgButtonChecked(dialog, IDC_FW2_NEW) == BST_CHECKED;
    options.keepOpen = IsDlgButtonChecked(dialog, IDC_FW2_KEEP_OPEN) == BST_CHECKED;
    return options;
}
void populate(HWND dialog, State &state, const Options &options) {
    state.applying = true;
    state.options = options;
    SetDlgItemTextW(dialog, IDC_FW2_TEXT, options.text.c_str());
    number(dialog, IDC_FW2_HEIGHT, options.height);
    number(dialog, IDC_FW2_DEPTH, options.depth);
    number(dialog, IDC_FW2_BEVEL, double(options.bevel) * 10.0);
    for (std::size_t i = 0; i < controlIDs.size(); ++i)
        CheckDlgButton(dialog, controlIDs[i], options.flags & controlFlags[i] ? BST_CHECKED : BST_UNCHECKED);
    SendDlgItemMessageW(dialog, IDC_FW2_SUBDIVIDE, CB_SETCURSEL,
                       options.flags & EX_SUB_ALL ? 2 : options.flags & EX_SUB ? 1 : 0, 0);
    CheckDlgButton(dialog, IDC_FW2_NEW, options.newModel || !state.hasModel ? BST_CHECKED : BST_UNCHECKED);
    CheckDlgButton(dialog, IDC_FW2_KEEP_OPEN, options.keepOpen ? BST_CHECKED : BST_UNCHECKED);
    EnableWindow(GetDlgItem(dialog, IDC_FW2_NEW), state.hasModel);
    state.applying = false;
    preview(dialog, state);
}
std::wstring settingsFile(HWND dialog, const State &state, bool save) {
    std::array<wchar_t, 32768> filename{};
    const std::wstring initial = !state.settingsPath.empty() ? state.settingsPath : save ? L"FontWiz2-settings.json" : L"";
    wcsncpy_s(filename.data(), filename.size(), initial.c_str(), _TRUNCATE);
    OPENFILENAMEW choice{}; choice.lStructSize = sizeof(choice); choice.hwndOwner = dialog;
    choice.lpstrFile = filename.data(); choice.nMaxFile = static_cast<DWORD>(filename.size());
    choice.lpstrFilter = L"JSON settings (*.json)\0*.json\0All files (*.*)\0*.*\0\0";
    choice.lpstrDefExt = L"json";
    choice.lpstrTitle = save ? L"Save FontWiz2 Settings" : L"Load FontWiz2 Settings";
    choice.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY |
                   (save ? OFN_OVERWRITEPROMPT : OFN_FILEMUSTEXIST);
    if (save ? GetSaveFileNameW(&choice) : GetOpenFileNameW(&choice)) return filename.data();
    if (CommDlgExtendedError()) throw std::runtime_error("The settings file dialog could not be opened.");
    return {};
}
struct Working {
    HWND dialog; State &state; HCURSOR previous;
    Working(HWND window, State &value) : dialog(window), state(value),
        previous(SetCursor(LoadCursorW(nullptr, MAKEINTRESOURCEW(32514)))) {
        state.busy = true; EnableWindow(dialog, FALSE);
    }
    ~Working() { EnableWindow(dialog, TRUE); state.busy = false; SetCursor(previous); }
};
void createText(HWND dialog, State &state) {
    Options values = readControls(dialog, state);
    FW2Request request; FW2Reply reply;
    wcscpy_s(request.text, values.text.c_str());
    if (!FW2ValidRequest(&request, &reply))
        throw std::runtime_error("Enter visible text (up to 512 BMP characters). Emoji/surrogate pairs are not supported yet.");
    if (!(values.flags & (EX_CLOSE_FRONT | EX_BACK | EX_CLOSE_BACK)))
        throw std::runtime_error("Select at least one geometry piece.");
    // Preserve raw checkboxes in JSON; normalize only for model generation.
    Options generation = values;
    if (generation.flags & EX_CLOSE_BACK) generation.flags |= EX_BACK;
    if (!(generation.flags & EX_CLOSE_FRONT)) generation.flags &= ~EX_BEV_FRONT;
    if (!(generation.flags & EX_BACK)) generation.flags &= ~(EX_BEV_SIDE | EX_BEV_BACK);
    StampResult stamp;
    { Working working(dialog, state); stamp = state.generate(generation); }
    state.options = values;
    state.result.model = stamp.model;
    const auto total = static_cast<std::uint64_t>(state.result.splines) + stamp.splines;
    state.result.splines = static_cast<std::uint32_t>((std::min)(total, std::uint64_t(std::numeric_limits<std::uint32_t>::max())));
    if (state.result.stamps < std::numeric_limits<std::uint32_t>::max()) ++state.result.stamps;
    state.result.text = values.text;
    if (!values.keepOpen) { EndDialog(dialog, IDOK); return; }
    wchar_t status[160]{};
    swprintf_s(status, L"Created %u splines. Ready for the next stamp (%u completed).", stamp.splines, state.result.stamps);
    SetDlgItemTextW(dialog, IDC_FW2_STATUS, status);
    SetDlgItemTextW(dialog, IDCANCEL, L"Close");
    SetForegroundWindow(dialog);
    SetFocus(GetDlgItem(dialog, IDC_FW2_TEXT));
    SendDlgItemMessageW(dialog, IDC_FW2_TEXT, EM_SETSEL, 0, -1);
}
INT_PTR CALLBACK procedure(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam) {
    State *state = reinterpret_cast<State *>(GetWindowLongPtrW(dialog, DWLP_USER));
    if (message == WM_INITDIALOG) {
        state = reinterpret_cast<State *>(lparam); SetWindowLongPtrW(dialog, DWLP_USER, lparam);
    }
    if (!state) return FALSE;
    if (state->busy) return message == WM_COMMAND || message == WM_CLOSE;
    try {
        if (message == WM_INITDIALOG) {
            SendDlgItemMessageW(dialog, IDC_FW2_TEXT, EM_SETLIMITTEXT, FW2_MAX_TEXT, 0);
            for (const wchar_t *label : {L"None", L"Auto", L"All"})
                SendDlgItemMessageW(dialog, IDC_FW2_SUBDIVIDE, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label));
            populate(dialog, *state, state->options); return TRUE;
        }
        if (message == WM_CLOSE || (message == WM_COMMAND && LOWORD(wparam) == IDCANCEL)) {
            EndDialog(dialog, state->result.stamps ? IDOK : IDCANCEL); return TRUE;
        }
        if (message == WM_COMMAND) {
            const WORD id = LOWORD(wparam);
            if (id == IDC_FW2_TEXT && HIWORD(wparam) == EN_CHANGE && !state->applying) { preview(dialog, *state); return TRUE; }
            if (id == IDC_FW2_PICKFONT) {
                LOGFONTW font = state->options.font; font.lfHeight = -24;
                CHOOSEFONTW choice{}; choice.lStructSize = sizeof(choice);
                choice.hwndOwner = dialog; choice.lpLogFont = &font;
                choice.Flags = CF_SCREENFONTS | CF_TTONLY | CF_INITTOLOGFONTSTRUCT | CF_NOSIZESEL;
                if (ChooseFontW(&choice)) { state->options.font = font; preview(dialog, *state); }
                return TRUE;
            }
            if (id == IDC_FW2_SAVE) {
                const Options values = readControls(dialog, *state);
                const auto path = settingsFile(dialog, *state, true);
                if (!path.empty()) { SaveSettingsFile(path, values); state->settingsPath = path; }
                return TRUE;
            }
            if (id == IDC_FW2_LOAD) {
                const auto path = settingsFile(dialog, *state, false);
                if (!path.empty()) {
                    const Options loaded = LoadSettingsFile(path); // Validate before changing any control.
                    populate(dialog, *state, loaded); state->settingsPath = path;
                }
                return TRUE;
            }
            if (id == IDOK) { createText(dialog, *state); return TRUE; }
        }
    } catch (const std::exception &error) {
        MessageBoxA(dialog, error.what(), "FontWiz2", MB_OK | MB_ICONERROR);
    } catch (...) {
        MessageBoxW(dialog, L"FontWiz2 could not process this action.", L"FontWiz2", MB_OK | MB_ICONERROR);
    }
    return FALSE;
}
}
WizardResult ShowWizard(HINSTANCE module, HWND owner, Options &options, bool hasModel, const GenerateText &generate) {
    State state{options, hasModel, generate};
    const INT_PTR result = DialogBoxParamW(module, MAKEINTRESOURCEW(IDD_FW2_WIZARD), owner, procedure, reinterpret_cast<LPARAM>(&state));
    if (state.preview) DeleteObject(state.preview);
    if (result == -1) throw std::runtime_error("The FontWiz2 dialog could not be opened.");
    return state.result;
}
}
