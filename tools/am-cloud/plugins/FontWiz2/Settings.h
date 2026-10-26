#pragma once
#include "Options.h"
#include <string>

namespace fw2 {
std::string SettingsToJson(const Options &options);
Options SettingsFromJson(const std::string &json);
void SaveSettingsFile(const std::wstring &filename, const Options &options);
Options LoadSettingsFile(const std::wstring &filename);
}
