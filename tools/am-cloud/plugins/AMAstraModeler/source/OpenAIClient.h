#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <atomic>
#include <string>
#include <string_view>

namespace amastra {

struct ReferenceImage;

struct HttpResponse {
    unsigned status = 0;
    std::string requestId;
    std::string body;
};

std::wstring ProgramDirectory();
std::string Utf8FromWide(std::wstring_view text);
std::wstring WideFromUtf8(std::string_view text);
std::string LoadApiKey();
ReferenceImage LoadReferenceImage(const std::wstring& path);
ReferenceImage LoadReferenceImageFromClipboard();
// The caller owns the returned bitmap and must release it with DeleteObject.
HBITMAP CreateReferenceImagePreviewBitmap(const ReferenceImage& image,
                                          unsigned maxWidth, unsigned maxHeight);
void SecureErase(std::string& value) noexcept;

HttpResponse PostOpenAIJson(const std::string& apiKey, std::wstring_view endpoint,
                            const std::string& requestBody,
                            const std::atomic_bool& cancelRequested);
HttpResponse PostResponses(const std::string& apiKey, const std::string& requestBody,
                           const std::atomic_bool& cancelRequested);
HttpResponse PostImageRequest(const std::string& apiKey, bool edit,
                              const std::string& requestBody,
                              const std::atomic_bool& cancelRequested);

} // namespace amastra
