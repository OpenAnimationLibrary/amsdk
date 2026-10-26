#pragma once
#include <windows.h>
#include <functional>
#include <string>

namespace fw2 {
using InspectModel = std::function<std::wstring(void *, bool)>;
void ShowModelInspector(HINSTANCE module, HWND owner, void *model, const InspectModel &inspect);
std::wstring DiagnosticText(const std::string &bytes);
std::wstring ReadDiagnosticFile(const std::wstring &path);
void SaveDiagnosticFile(const std::wstring &path, const std::wstring &text);
}
