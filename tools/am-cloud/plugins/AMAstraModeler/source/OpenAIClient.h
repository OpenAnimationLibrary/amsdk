#pragma once

#include <atomic>
#include <string>
#include <string_view>

namespace amastra {

struct HttpResponse {
    unsigned status = 0;
    std::string requestId;
    std::string body;
};

std::wstring ProgramDirectory();
std::string Utf8FromWide(std::wstring_view text);
std::wstring WideFromUtf8(std::string_view text);
std::string LoadApiKey();
void SecureErase(std::string& value) noexcept;

HttpResponse PostResponses(const std::string& apiKey, const std::string& requestBody,
                           const std::atomic_bool& cancelRequested);

} // namespace amastra
