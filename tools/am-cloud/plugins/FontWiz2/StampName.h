#pragma once
#include <string>
#include <algorithm>
#include <cwctype>

namespace fw2 {
inline std::wstring StampName(const std::wstring &text, unsigned instance = 1) {
    std::wstring base;
    for (wchar_t c : text) {
        if (iswspace(c)) c = L' ';
        if (iswcntrl(c) || (base.empty() && c == L' ')) continue;
        base += c;
        if (base.size() == 10) break;
    }
    while (!base.empty() && base.back() == L' ') base.pop_back();
    if (base.empty()) base = L"Text";
    if (instance > 1) {
        const auto suffix = L" " + std::to_wstring(instance);
        base.resize((std::min)(base.size(), 10 - suffix.size()));
        base += suffix;
    }
    return base;
}
}
