#pragma once
#include <windows.h>
#include <functional>
#include <string>

namespace fw2 {
using SaveModelCopy = std::function<bool(void *, HWND)>;
std::wstring ChooseModelCopy(HWND owner);
void WriteModelCopy(const std::wstring &path, const std::string &bytes);
}
