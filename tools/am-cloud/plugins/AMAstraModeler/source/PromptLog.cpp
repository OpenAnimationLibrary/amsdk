#include "PromptLog.h"

#include "OpenAIClient.h"

#include <atomic>
#include <iomanip>
#include <sstream>

namespace amastra {
namespace {

std::string UtcTimestamp() {
    SYSTEMTIME time{};
    GetSystemTime(&time);
    char buffer[32]{};
    sprintf_s(buffer, "%04u-%02u-%02uT%02u:%02u:%02u.%03uZ", time.wYear, time.wMonth,
              time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    return buffer;
}

std::string NewAttemptId() {
    static std::atomic<unsigned long> sequence{0};
    SYSTEMTIME time{};
    GetSystemTime(&time);
    char buffer[96]{};
    sprintf_s(buffer, "%04u%02u%02uT%02u%02u%02u-%lu-%llu-%lu", time.wYear, time.wMonth,
              time.wDay, time.wHour, time.wMinute, time.wSecond,
              static_cast<unsigned long>(GetCurrentProcessId()),
              static_cast<unsigned long long>(GetTickCount64()), ++sequence);
    return buffer;
}

std::wstring LocalAppDataLogPath() {
    DWORD needed = GetEnvironmentVariableW(L"LOCALAPPDATA", nullptr, 0);
    if (!needed) throw Error("Cannot locate LOCALAPPDATA for the prompt-log fallback");
    std::wstring root(needed, L'\0');
    const DWORD length = GetEnvironmentVariableW(L"LOCALAPPDATA", root.data(), needed);
    if (!length || length >= needed) throw Error("Cannot read LOCALAPPDATA for the prompt-log fallback");
    root.resize(length);
    const std::wstring first = root + L"\\AnimationMaster";
    const std::wstring second = first + L"\\AstraModeler";
    if (!CreateDirectoryW(first.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS)
        throw Error("Cannot create the AnimationMaster log folder in LOCALAPPDATA");
    if (!CreateDirectoryW(second.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS)
        throw Error("Cannot create the AstraModeler log folder in LOCALAPPDATA");
    return second + L"\\astra_modeler.log";
}

HANDLE OpenAppend(const std::wstring& path) {
    return CreateFileW(path.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                       OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
}

} // namespace

PromptLog::PromptLog() { Open(); }

PromptLog::~PromptLog() {
    if (begun_ && !finished_ && handle_ != INVALID_HANDLE_VALUE) {
        try { Finish("abandoned", nullptr, nullptr, "Attempt ended without a completion record"); }
        catch (...) {}
    }
    if (handle_ != INVALID_HANDLE_VALUE) CloseHandle(handle_);
}

void PromptLog::Open() {
    path_ = ProgramDirectory() + L"\\astra_modeler.log";
    handle_ = OpenAppend(path_);
    if (handle_ == INVALID_HANDLE_VALUE) {
        path_ = LocalAppDataLogPath();
        handle_ = OpenAppend(path_);
    }
    if (handle_ == INVALID_HANDLE_VALUE)
        throw Error("Cannot open astra_modeler.log beside master.exe or in LOCALAPPDATA");
    attemptId_ = NewAttemptId();
}

void PromptLog::Write(const amjson::Value& record) {
    std::string line = amjson::dump(record);
    line.push_back('\n');
    DWORD written = 0;
    if (line.size() > MAXDWORD ||
        !WriteFile(handle_, line.data(), static_cast<DWORD>(line.size()), &written, nullptr) ||
        written != static_cast<DWORD>(line.size()) || !FlushFileBuffers(handle_))
        throw Error("Cannot append a complete record to astra_modeler.log");
}

void PromptLog::Begin(std::string_view prompt, std::size_t componentLimit, std::size_t patchLimit,
                      const ReferenceImageMetadata* referenceImage) {
    if (begun_) throw Error("The prompt-log attempt was already started");
    amjson::Value imageRecord = nullptr;
    if (referenceImage) {
        imageRecord = amjson::Value::object({
            {"file_name", referenceImage->fileName},
            {"media_type", referenceImage->mimeType},
            {"byte_size", static_cast<double>(referenceImage->byteSize)},
            {"width_px", static_cast<double>(referenceImage->width)},
            {"height_px", static_cast<double>(referenceImage->height)},
            {"detail", "high"}
        });
    }
    Write(amjson::Value::object({
        {"timestamp_utc", UtcTimestamp()}, {"event", "attempt_started"},
        {"attempt_id", attemptId_}, {"plugin_version", "0.2.0"},
        {"model", "gpt-6-astra"}, {"prompt", std::string(prompt)},
        {"component_limit", static_cast<double>(componentLimit)},
        {"patch_limit", static_cast<double>(patchLimit)},
        {"reference_image", std::move(imageRecord)}
    }));
    begun_ = true;
}

void PromptLog::Finish(std::string_view status, const ApiResult* api, const PreparedPlan* plan,
                       std::string_view detail) {
    if (!begun_ || finished_) return;
    amjson::Value::Object record{
        {"timestamp_utc", UtcTimestamp()}, {"event", "attempt_finished"},
        {"attempt_id", attemptId_}, {"model", "gpt-6-astra"},
        {"status", std::string(status)}
    };
    if (api) {
        record.emplace("request_id", api->requestId);
        record.emplace("response_id", api->responseId);
        record.emplace("input_tokens", static_cast<double>(api->inputTokens));
        record.emplace("output_tokens", static_cast<double>(api->outputTokens));
    }
    if (plan) {
        record.emplace("model_name", plan->source.name);
        record.emplace("components", static_cast<double>(plan->parts.size()));
        record.emplace("materials", static_cast<double>(plan->source.materials.size()));
        record.emplace("patches", static_cast<double>(plan->patches));
        record.emplace("vertices", static_cast<double>(plan->vertices));
        record.emplace("spline_paths", static_cast<double>(plan->splinePaths));
        record.emplace("control_point_records", static_cast<double>(plan->controlPointRecords));
    }
    if (!detail.empty()) record.emplace("detail", SanitizeDiagnostic(detail));
    Write(amjson::Value(std::move(record)));
    finished_ = true;
}

} // namespace amastra
