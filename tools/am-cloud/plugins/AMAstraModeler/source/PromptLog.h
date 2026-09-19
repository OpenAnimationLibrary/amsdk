#pragma once

#include "ModelPlan.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstddef>
#include <string>
#include <string_view>

namespace amastra {

class PromptLog {
public:
    PromptLog();
    ~PromptLog();
    PromptLog(const PromptLog&) = delete;
    PromptLog& operator=(const PromptLog&) = delete;

    void Begin(std::string_view prompt, std::size_t componentLimit, std::size_t patchLimit);
    void Finish(std::string_view status, const ApiResult* api, const PreparedPlan* plan,
                std::string_view detail = {});

    const std::wstring& path() const { return path_; }
    const std::string& attemptId() const { return attemptId_; }

private:
    void Open();
    void Write(const amjson::Value& record);

    HANDLE handle_ = INVALID_HANDLE_VALUE;
    std::wstring path_;
    std::string attemptId_;
    bool begun_ = false;
    bool finished_ = false;
};

} // namespace amastra
