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

std::string BaseNameOnly(std::string_view name) {
    const auto separator = name.find_last_of("\\/:");
    if (separator != std::string_view::npos) name.remove_prefix(separator + 1);
    return std::string(name);
}

amjson::Value ImageMetadataRecord(const ReferenceImageMetadata* metadata) {
    if (!metadata) return nullptr;
    return amjson::Value::object({
        {"source_type", std::string(ReferenceImageSourceName(metadata->source))},
        {"file_name", BaseNameOnly(metadata->fileName)},
        {"media_type", metadata->mimeType},
        {"byte_size", static_cast<double>(metadata->byteSize)},
        {"width_px", static_cast<double>(metadata->width)},
        {"height_px", static_cast<double>(metadata->height)},
        {"sha256", metadata->sha256}
    });
}

void ValidateReferenceImageOperation(std::string_view operation) {
    if (operation != "create" && operation != "refine")
        throw Error("Reference-image log operation must be create or refine");
}

std::string_view RequestedImageModel(std::string_view operation) {
    return operation == "refine" ? ImageEditModel : ImageGenerationModel;
}

amjson::Value RequestedImageSettings(std::string_view operation) {
    amjson::Value::Object settings{
        {"n", 1.0},
        {"size", "1024x1024"},
        {"quality", "medium"},
        {"background", "opaque"},
        {"output_format", "jpeg"},
        {"output_compression", 85.0},
        {"moderation", "auto"}
    };
    if (operation == "refine") settings.emplace("input_fidelity", "high");
    return amjson::Value(std::move(settings));
}

amjson::Value ImageResultSettings(const ImageApiResult& api) {
    amjson::Value::Object settings{
        {"size", api.size},
        {"output_format", api.outputFormat}
    };
    if (!api.quality.empty()) settings.emplace("quality", api.quality);
    if (!api.background.empty()) settings.emplace("background", api.background);
    if (api.hasOutputCompression)
        settings.emplace("output_compression", static_cast<double>(api.outputCompression));
    return amjson::Value(std::move(settings));
}

amjson::Value ImageUsageRecord(const ImageApiResult& api) {
    return amjson::Value::object({
        {"input_tokens", static_cast<double>(api.inputTokens)},
        {"output_tokens", static_cast<double>(api.outputTokens)},
        {"total_tokens", static_cast<double>(api.totalTokens)},
        {"input_text_tokens", static_cast<double>(api.inputTextTokens)},
        {"input_image_tokens", static_cast<double>(api.inputImageTokens)},
        {"output_text_tokens", static_cast<double>(api.outputTextTokens)},
        {"output_image_tokens", static_cast<double>(api.outputImageTokens)}
    });
}

} // namespace

PromptLog::PromptLog() { Open(); }

PromptLog::~PromptLog() {
    if (referenceImageBegun_ && handle_ != INVALID_HANDLE_VALUE) {
        try {
            FinishReferenceImage(referenceImageOperation_, "abandoned", nullptr, nullptr,
                                 "Reference-image request ended without a completion record");
        } catch (...) {}
    }
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
    amjson::Value imageRecord = ImageMetadataRecord(referenceImage);
    if (referenceImage) imageRecord.as_object().emplace("detail", "high");
    Write(amjson::Value::object({
        {"timestamp_utc", UtcTimestamp()}, {"event", "attempt_started"},
        {"attempt_id", attemptId_}, {"plugin_version", "0.3.0"},
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
        {"attempt_id", attemptId_}, {"plugin_version", "0.3.0"},
        {"model", "gpt-6-astra"},
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

void PromptLog::BeginReferenceImage(std::string_view operation, std::string_view prompt,
                                    const ReferenceImageMetadata* source) {
    ValidateReferenceImageOperation(operation);
    if (referenceImageBegun_)
        throw Error("A reference-image prompt-log operation is already in progress");
    Write(amjson::Value::object({
        {"timestamp_utc", UtcTimestamp()},
        {"event", "reference_image_started"},
        {"attempt_id", attemptId_},
        {"plugin_version", "0.3.0"},
        {"operation", std::string(operation)},
        {"prompt", std::string(prompt)},
        {"requested_model", std::string(RequestedImageModel(operation))},
        {"requested_settings", RequestedImageSettings(operation)},
        {"source_image", ImageMetadataRecord(source)}
    }));
    referenceImageOperation_ = operation;
    referenceImageBegun_ = true;
}

void PromptLog::FinishReferenceImage(std::string_view operation, std::string_view status,
                                     const ImageApiResult* api,
                                     const ReferenceImageMetadata* result,
                                     std::string_view detail) {
    ValidateReferenceImageOperation(operation);
    if (!referenceImageBegun_) return;
    if (operation != referenceImageOperation_)
        throw Error("Reference-image prompt-log completion operation does not match its start");

    amjson::Value::Object record{
        {"timestamp_utc", UtcTimestamp()},
        {"event", "reference_image_finished"},
        {"attempt_id", attemptId_},
        {"plugin_version", "0.3.0"},
        {"operation", std::string(operation)},
        {"status", std::string(status)},
        {"result_image", ImageMetadataRecord(result)}
    };
    if (api) {
        if (!api->model.empty()) record.emplace("model", api->model);
        if (!api->requestId.empty()) record.emplace("request_id", api->requestId);
        if (!api->revisedPrompt.empty())
            record.emplace("revised_prompt", SanitizeDiagnostic(api->revisedPrompt));
        if (api->usagePresent)
            record.emplace("usage", ImageUsageRecord(*api));
        if (!api->size.empty() && !api->outputFormat.empty())
            record.emplace("output_settings", ImageResultSettings(*api));
    }
    if (!detail.empty()) record.emplace("detail", SanitizeDiagnostic(detail));
    Write(amjson::Value(std::move(record)));
    referenceImageBegun_ = false;
    referenceImageOperation_.clear();
}

} // namespace amastra
