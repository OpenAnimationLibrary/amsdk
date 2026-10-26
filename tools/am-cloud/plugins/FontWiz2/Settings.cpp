#include "Settings.h"
#include "FontWiz2Api.h"
#include "geometry/extrude.h"
#include "third_party/picojson.h"
#include <algorithm>
#include <cmath>
#include <cwchar>
#include <limits>
#include <stdexcept>

namespace fw2 {
namespace {
using Json = picojson::value;
using Object = picojson::object;
constexpr std::size_t maximumFileSize = 65536;
constexpr unsigned allowedFlags = EX_BACK | EX_CLOSE_FRONT | EX_CLOSE_BACK | EX_BEV_FRONT |
    EX_BEV_SIDE | EX_BEV_BACK | EX_ROUND | EX_INWARD | EX_SUB | EX_SUB_ALL;
const std::pair<const char *, unsigned> pieces[] = {
    {"front_cap", EX_CLOSE_FRONT}, {"sides", EX_BACK}, {"back_cap", EX_CLOSE_BACK}};
const std::pair<const char *, unsigned> bevels[] = {
    {"front", EX_BEV_FRONT}, {"sides", EX_BEV_SIDE}, {"back", EX_BEV_BACK},
    {"round", EX_ROUND}, {"inward", EX_INWARD}};

std::string utf8(const std::wstring &text) {
    if (text.empty()) return {};
    const int count = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(),
                                         static_cast<int>(text.size()), nullptr, 0, nullptr, nullptr);
    if (!count) throw std::runtime_error("Settings contain invalid Unicode text.");
    std::string result(static_cast<std::size_t>(count), '\0');
    if (!WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(),
                            static_cast<int>(text.size()), result.data(), count, nullptr, nullptr))
        throw std::runtime_error("Settings text could not be encoded.");
    return result;
}
std::wstring wide(const std::string &text) {
    if (text.empty()) return {};
    const int count = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                                         static_cast<int>(text.size()), nullptr, 0);
    if (!count) throw std::runtime_error("The settings file is not valid UTF-8.");
    std::wstring result(static_cast<std::size_t>(count), L'\0');
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                            static_cast<int>(text.size()), result.data(), count))
        throw std::runtime_error("Settings text could not be decoded.");
    return result;
}
void validate(const Options &options) {
    const auto bounded = [](double value, double low, double high) {
        return std::isfinite(value) && value >= low && value <= high;
    };
    if (options.text.size() > FW2_MAX_TEXT || options.text.find(L'\0') != std::wstring::npos)
        throw std::runtime_error("Settings text exceeds 512 UTF-16 code units or contains a null character.");
    (void)utf8(options.text);  // Blank/draft text is allowed; Create Text validates renderability.
    const wchar_t *end = std::wmemchr(options.font.lfFaceName, L'\0', LF_FACESIZE);
    if (!end || end == options.font.lfFaceName) throw std::runtime_error("Settings contain an invalid font name.");
    (void)utf8(std::wstring(options.font.lfFaceName, end));
    if (!bounded(options.height, 0.01F, 10000) || !bounded(options.depth, 0.01F, 10000) ||
        !bounded(options.bevel, 0, 100) || !bounded(options.font.lfWeight, 0, 1000) ||
        !bounded(options.font.lfHeight, -4096, 4096) || !bounded(options.font.lfWidth, -4096, 4096) ||
        !bounded(options.font.lfEscapement, -36000, 36000) || !bounded(options.font.lfOrientation, -36000, 36000) ||
        options.font.lfItalic > 1 || options.font.lfUnderline > 1 || options.font.lfStrikeOut > 1 ||
        (options.flags & ~allowedFlags) || ((options.flags & EX_SUB_ALL) && !(options.flags & EX_SUB)))
        throw std::runtime_error("Settings contain unsupported sizes, font properties or geometry options.");
}
const Json &field(const Object &object, const char *key) {
    const auto found = object.find(key);
    if (found == object.end()) throw std::runtime_error(std::string("Missing settings field: ") + key);
    return found->second;
}
template<class T> const T &as(const Json &value, const char *key) {
    if (!value.is<T>()) throw std::runtime_error(std::string("Invalid settings field: ") + key);
    return value.get<T>();
}
double number(const Object &object, const char *key, double low, double high, bool integer = false) {
    const double value = as<double>(field(object, key), key);
    if (!std::isfinite(value) || value < low || value > high || (integer && std::trunc(value) != value))
        throw std::runtime_error(std::string("Settings value is out of range: ") + key);
    return value;
}
bool boolean(const Object &object, const char *key) { return as<bool>(field(object, key), key); }

class File {
public:
    HANDLE handle = INVALID_HANDLE_VALUE;
    explicit File(HANDLE value) : handle(value) {}
    ~File() { close(); }
    bool close() {
        const HANDLE value = handle; handle = INVALID_HANDLE_VALUE;
        return value == INVALID_HANDLE_VALUE || CloseHandle(value) != FALSE;
    }
    File(const File &) = delete;
    File &operator=(const File &) = delete;
};
}

std::string SettingsToJson(const Options &options) {
    validate(options);
    const auto &f = options.font;
    Object font{{"face", Json(utf8(f.lfFaceName))}, {"height", Json(double(f.lfHeight))},
        {"width", Json(double(f.lfWidth))}, {"escapement", Json(double(f.lfEscapement))},
        {"orientation", Json(double(f.lfOrientation))}, {"weight", Json(double(f.lfWeight))},
        {"italic", Json(f.lfItalic != 0)}, {"underline", Json(f.lfUnderline != 0)},
        {"strikeout", Json(f.lfStrikeOut != 0)}, {"charset", Json(double(f.lfCharSet))},
        {"out_precision", Json(double(f.lfOutPrecision))}, {"clip_precision", Json(double(f.lfClipPrecision))},
        {"quality", Json(double(f.lfQuality))}, {"pitch_and_family", Json(double(f.lfPitchAndFamily))}};
    Object geometry{{"em_height_cm", Json(double(options.height))}, {"extrusion_cm", Json(double(options.depth))},
        {"subdivision", Json(std::string(options.flags & EX_SUB_ALL ? "all" : options.flags & EX_SUB ? "auto" : "none"))}};
    Object bevel{{"amount_mm", Json(double(options.bevel) * 10.0)}};
    for (const auto &[key, flag] : pieces) geometry.emplace(key, Json((options.flags & flag) != 0));
    for (const auto &[key, flag] : bevels) bevel.emplace(key, Json((options.flags & flag) != 0));
    Object surface{{"apply_color", Json(options.applyColor)},
        {"red", Json(double(GetRValue(options.surfaceColor)))},
        {"green", Json(double(GetGValue(options.surfaceColor)))},
        {"blue", Json(double(GetBValue(options.surfaceColor)))}};
    Object root{{"format", Json(std::string("FontWiz2.Settings"))}, {"version", Json(2.0)},
        {"text", Json(utf8(options.text))}, {"font", Json(font)}, {"geometry", Json(geometry)},
        {"bevel", Json(bevel)}, {"surface", Json(surface)},
        {"create_new_model", Json(options.newModel)}, {"keep_window_open", Json(options.keepOpen)},
        {"save_model_copy_after_creation", Json(options.saveModelCopy)}};
    return Json(root).serialize(true) + "\n";
}

Options SettingsFromJson(const std::string &input) {
    if (input.empty() || input.size() > maximumFileSize) throw std::runtime_error("Settings files must be UTF-8 JSON under 64 KiB.");
    std::string text = input;
    if (text.compare(0, 3, "\xEF\xBB\xBF") == 0) text.erase(0, 3);
    (void)wide(text);  // Reject invalid UTF-8 before parsing, including unknown fields.
    bool quoted = false, escaped = false;
    int depth = 0;
    for (char c : text) {
        if (quoted) {
            if (escaped) escaped = false;
            else if (c == '\\') escaped = true;
            else if (c == '"') quoted = false;
        } else if (c == '"') quoted = true;
        else if (c == '{' || c == '[') {
            if (++depth > 8) throw std::runtime_error("Settings JSON is nested too deeply.");
        } else if (c == '}' || c == ']') {
            if (--depth < 0) throw std::runtime_error("Invalid settings JSON.");
        }
    }
    Json parsed; std::string error;
    auto end = picojson::parse(parsed, text.cbegin(), text.cend(), &error);
    while (end != text.cend() && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) ++end;
    if (!error.empty() || end != text.cend()) throw std::runtime_error("The file is not valid settings JSON.");
    const Object &root = as<Object>(parsed, "root");
    if (as<std::string>(field(root, "format"), "format") != "FontWiz2.Settings")
        throw std::runtime_error("Unsupported FontWiz2 settings format/version.");
    const double version = number(root, "version", 1, 2, true);
    const Object &font = as<Object>(field(root, "font"), "font");
    const Object &geometry = as<Object>(field(root, "geometry"), "geometry");
    const Object &bevel = as<Object>(field(root, "bevel"), "bevel");
    Options options;
    options.text = wide(as<std::string>(field(root, "text"), "text"));
    const auto face = wide(as<std::string>(field(font, "face"), "face"));
    if (face.empty() || face.size() >= LF_FACESIZE || face.find(L'\0') != std::wstring::npos)
        throw std::runtime_error("The settings font name is too long or invalid.");
    wcscpy_s(options.font.lfFaceName, face.c_str());
    auto &f = options.font;
    f.lfHeight = static_cast<LONG>(number(font, "height", -4096, 4096, true));
    f.lfWidth = static_cast<LONG>(number(font, "width", -4096, 4096, true));
    f.lfEscapement = static_cast<LONG>(number(font, "escapement", -36000, 36000, true));
    f.lfOrientation = static_cast<LONG>(number(font, "orientation", -36000, 36000, true));
    f.lfWeight = static_cast<LONG>(number(font, "weight", 0, 1000, true));
    f.lfItalic = boolean(font, "italic"); f.lfUnderline = boolean(font, "underline"); f.lfStrikeOut = boolean(font, "strikeout");
    f.lfCharSet = static_cast<BYTE>(number(font, "charset", 0, 255, true));
    f.lfOutPrecision = static_cast<BYTE>(number(font, "out_precision", 0, 255, true));
    f.lfClipPrecision = static_cast<BYTE>(number(font, "clip_precision", 0, 255, true));
    f.lfQuality = static_cast<BYTE>(number(font, "quality", 0, 255, true));
    f.lfPitchAndFamily = static_cast<BYTE>(number(font, "pitch_and_family", 0, 255, true));
    options.height = static_cast<float>(number(geometry, "em_height_cm", 0.01F, 10000));
    options.depth = static_cast<float>(number(geometry, "extrusion_cm", 0.01F, 10000));
    options.bevel = static_cast<float>(number(bevel, "amount_mm", 0, 1000) / 10.0);
    options.flags = 0;
    for (const auto &[key, flag] : pieces) if (boolean(geometry, key)) options.flags |= flag;
    for (const auto &[key, flag] : bevels) if (boolean(bevel, key)) options.flags |= flag;
    const auto &subdivision = as<std::string>(field(geometry, "subdivision"), "subdivision");
    if (subdivision == "auto") options.flags |= EX_SUB;
    else if (subdivision == "all") options.flags |= EX_SUB | EX_SUB_ALL;
    else if (subdivision != "none") throw std::runtime_error("Unknown subdivision setting.");
    options.newModel = boolean(root, "create_new_model"); options.keepOpen = boolean(root, "keep_window_open");
    if (version >= 2) {
        const Object &surface = as<Object>(field(root, "surface"), "surface");
        options.applyColor = boolean(surface, "apply_color");
        options.surfaceColor = RGB(static_cast<BYTE>(number(surface, "red", 0, 255, true)),
            static_cast<BYTE>(number(surface, "green", 0, 255, true)),
            static_cast<BYTE>(number(surface, "blue", 0, 255, true)));
    }
    if (version >= 2 && root.find("save_model_copy_after_creation") != root.end())
        options.saveModelCopy = boolean(root, "save_model_copy_after_creation");
    validate(options);
    return options;
}

void SaveSettingsFile(const std::wstring &filename, const Options &options) {
    const std::string bytes = SettingsToJson(options);
    static LONG sequence = 0;
    for (int attempt = 0; attempt < 16; ++attempt) {
        const std::wstring temporary = filename + L".tmp-" + std::to_wstring(GetCurrentProcessId()) + L"-" +
            std::to_wstring(InterlockedIncrement(&sequence));
        File file(CreateFileW(temporary.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr));
        if (file.handle == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_FILE_EXISTS) continue;
            throw std::runtime_error("The settings file could not be created in this folder.");
        }
        try {
            DWORD written = 0;
            if (!WriteFile(file.handle, bytes.data(), static_cast<DWORD>(bytes.size()), &written, nullptr) ||
                written != bytes.size() || !FlushFileBuffers(file.handle) || !file.close())
                throw std::runtime_error("Settings could not be fully written. The previous file was preserved.");
            if (!MoveFileExW(temporary.c_str(), filename.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
                throw std::runtime_error("The settings file could not be replaced. The previous file was preserved.");
        } catch (...) { file.close(); DeleteFileW(temporary.c_str()); throw; }
        return;
    }
    throw std::runtime_error("A temporary settings file could not be created.");
}
Options LoadSettingsFile(const std::wstring &filename) {
    File file(CreateFileW(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
    LARGE_INTEGER size{};
    if (file.handle == INVALID_HANDLE_VALUE || !GetFileSizeEx(file.handle, &size) || size.QuadPart <= 0 ||
        size.QuadPart > static_cast<LONGLONG>(maximumFileSize))
        throw std::runtime_error("The settings file could not be read, is empty, or exceeds 64 KiB.");
    std::string bytes(static_cast<std::size_t>(size.QuadPart), '\0'); DWORD read = 0;
    if (!ReadFile(file.handle, bytes.data(), static_cast<DWORD>(bytes.size()), &read, nullptr) || read != bytes.size())
        throw std::runtime_error("The settings file could not be fully read.");
    return SettingsFromJson(bytes);
}
}
