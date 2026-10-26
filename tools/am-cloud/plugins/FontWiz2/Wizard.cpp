#include "FontWiz2.h"
#include "resource.h"
#include "geometry/extrude.h"
#include <commdlg.h>
#include <array>
#include <stdexcept>
#include <cwchar>
#include <cwctype>

namespace fw2 {
namespace {
struct State { Options &options; bool hasModel; HFONT preview = nullptr; };
const std::array<int, 8> controlIDs = {IDC_FW2_FRONT, IDC_FW2_SIDES, IDC_FW2_BACK,
    IDC_FW2_BEVFRONT, IDC_FW2_BEVSIDE, IDC_FW2_BEVBACK, IDC_FW2_ROUND, IDC_FW2_INWARD};
const std::array<unsigned, 8> controlFlags = {EX_CLOSE_FRONT, EX_BACK, EX_CLOSE_BACK,
    EX_BEV_FRONT, EX_BEV_SIDE, EX_BEV_BACK, EX_ROUND, EX_INWARD};
void number(HWND dialog, int id, double value) {
    wchar_t text[64]{}; swprintf_s(text, L"%.6g", value); SetDlgItemTextW(dialog, id, text);
}
float number(HWND dialog, int id, double minimum, double maximum) {
    wchar_t text[64]{}; GetDlgItemTextW(dialog, id, text, 64);
    wchar_t *end = nullptr;
    const double value = wcstod(text, &end);
    while (end && iswspace(*end)) ++end;
    if (end == text || !end || *end || !std::isfinite(value) || value < minimum || value > maximum)
        throw std::runtime_error("Enter valid positive sizes within the supported range.");
    return static_cast<float>(value);
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
INT_PTR CALLBACK procedure(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam) {
    State *state = reinterpret_cast<State *>(GetWindowLongPtrW(dialog, DWLP_USER));
    if (message == WM_INITDIALOG) {
        state = reinterpret_cast<State *>(lparam);
        SetWindowLongPtrW(dialog, DWLP_USER, lparam);
    }
    if (!state) return FALSE;
    try {
        Options &options = state->options;
        if (message == WM_INITDIALOG) {
            SendDlgItemMessageW(dialog, IDC_FW2_TEXT, EM_SETLIMITTEXT, FW2_MAX_TEXT, 0);
            SetDlgItemTextW(dialog, IDC_FW2_TEXT, options.text.c_str());
            number(dialog, IDC_FW2_HEIGHT, options.height);
            number(dialog, IDC_FW2_DEPTH, options.depth);
            number(dialog, IDC_FW2_BEVEL, options.bevel * 10.0F);
            for (std::size_t i = 0; i < controlIDs.size(); ++i)
                CheckDlgButton(dialog, controlIDs[i], options.flags & controlFlags[i] ? BST_CHECKED : BST_UNCHECKED);
            for (const wchar_t *label : {L"None", L"Auto", L"All"})
                SendDlgItemMessageW(dialog, IDC_FW2_SUBDIVIDE, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label));
            SendDlgItemMessageW(dialog, IDC_FW2_SUBDIVIDE, CB_SETCURSEL,
                               options.flags & EX_SUB_ALL ? 2 : options.flags & EX_SUB ? 1 : 0, 0);
            CheckDlgButton(dialog, IDC_FW2_NEW, options.newModel || !state->hasModel ? BST_CHECKED : BST_UNCHECKED);
            EnableWindow(GetDlgItem(dialog, IDC_FW2_NEW), state->hasModel);
            preview(dialog, *state);
            return TRUE;
        }
        if (message == WM_COMMAND) {
            const WORD id = LOWORD(wparam);
            if (id == IDCANCEL) { EndDialog(dialog, IDCANCEL); return TRUE; }
            if (id == IDC_FW2_TEXT && HIWORD(wparam) == EN_CHANGE) { preview(dialog, *state); return TRUE; }
            if (id == IDC_FW2_PICKFONT) {
                LOGFONTW font = options.font; font.lfHeight = -24;
                CHOOSEFONTW choice{}; choice.lStructSize = sizeof(choice);
                choice.hwndOwner = dialog; choice.lpLogFont = &font;
                choice.Flags = CF_SCREENFONTS | CF_TTONLY | CF_INITTOLOGFONTSTRUCT | CF_NOSIZESEL;
                if (ChooseFontW(&choice)) { options.font = font; preview(dialog, *state); }
                return TRUE;
            }
            if (id == IDOK) {
                FW2Request request; FW2Reply reply;
                GetDlgItemTextW(dialog, IDC_FW2_TEXT, request.text, static_cast<int>(FW2_MAX_TEXT + 1));
                if (!FW2ValidRequest(&request, &reply))
                    throw std::runtime_error("Enter visible text (up to 512 BMP characters). Emoji/surrogate pairs are not supported yet.");
                options.text = request.text;
                options.height = number(dialog, IDC_FW2_HEIGHT, 0.01, 10000);
                options.depth = number(dialog, IDC_FW2_DEPTH, 0.01, 10000);
                options.bevel = number(dialog, IDC_FW2_BEVEL, 0, 1000) * 0.1F;
                options.flags = 0;
                for (std::size_t i = 0; i < controlIDs.size(); ++i)
                    if (IsDlgButtonChecked(dialog, controlIDs[i]) == BST_CHECKED) options.flags |= controlFlags[i];
                if (!(options.flags & (EX_CLOSE_FRONT | EX_BACK | EX_CLOSE_BACK)))
                    throw std::runtime_error("Select at least one geometry piece.");
                if (options.flags & EX_CLOSE_BACK) options.flags |= EX_BACK;
                if (!(options.flags & EX_CLOSE_FRONT)) options.flags &= ~EX_BEV_FRONT;
                if (!(options.flags & EX_BACK)) options.flags &= ~(EX_BEV_SIDE | EX_BEV_BACK);
                const LRESULT subdivision = SendDlgItemMessageW(dialog, IDC_FW2_SUBDIVIDE, CB_GETCURSEL, 0, 0);
                if (subdivision > 0) options.flags |= EX_SUB;
                if (subdivision == 2) options.flags |= EX_SUB_ALL;
                options.newModel = IsDlgButtonChecked(dialog, IDC_FW2_NEW) == BST_CHECKED;
                EndDialog(dialog, IDOK);
                return TRUE;
            }
        }
    } catch (const std::exception &error) {
        MessageBoxA(dialog, error.what(), "FontWiz2", MB_OK | MB_ICONERROR);
    } catch (...) {
        MessageBoxW(dialog, L"FontWiz2 could not process this dialog action.", L"FontWiz2", MB_OK | MB_ICONERROR);
    }
    return FALSE;
}
}
bool ShowWizard(HWND owner, Options &options, bool hasModel) {
    State state{options, hasModel};
    const INT_PTR result = DialogBoxParamW(AfxGetInstanceHandle(), MAKEINTRESOURCEW(IDD_FW2_WIZARD),
                                           owner, procedure, reinterpret_cast<LPARAM>(&state));
    if (state.preview) DeleteObject(state.preview);
    if (result == -1) throw std::runtime_error("The FontWiz2 dialog could not be opened.");
    return result == IDOK;
}
}
