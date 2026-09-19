#include "OpenAIClient.h"

#include "ModelPlan.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winhttp.h>

#include <algorithm>
#include <array>
#include <limits>
#include <sstream>
#include <vector>

namespace amastra {
namespace {

class InternetHandle {
public:
    InternetHandle() = default;
    explicit InternetHandle(HINTERNET value) : value_(value) {}
    ~InternetHandle() { if (value_) WinHttpCloseHandle(value_); }
    InternetHandle(const InternetHandle&) = delete;
    InternetHandle& operator=(const InternetHandle&) = delete;
    InternetHandle(InternetHandle&& other) noexcept : value_(other.value_) { other.value_ = nullptr; }
    InternetHandle& operator=(InternetHandle&& other) noexcept {
        if (this != &other) {
            if (value_) WinHttpCloseHandle(value_);
            value_ = other.value_;
            other.value_ = nullptr;
        }
        return *this;
    }
    HINTERNET get() const { return value_; }
    explicit operator bool() const { return value_ != nullptr; }
private:
    HINTERNET value_ = nullptr;
};

std::string WindowsError(const char* operation) {
    const DWORD code = GetLastError();
    LPWSTR buffer = nullptr;
    const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS;
    const DWORD count = FormatMessageW(flags, nullptr, code, 0,
                                       reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);
    std::wstring message = count && buffer ? std::wstring(buffer, count) : L"unknown Windows error";
    if (buffer) LocalFree(buffer);
    while (!message.empty() && (message.back() == L'\r' || message.back() == L'\n' || message.back() == L' '))
        message.pop_back();
    return std::string(operation) + " failed (Windows error " + std::to_string(code) + "): " +
           Utf8FromWide(message);
}

std::vector<unsigned char> ReadSmallFile(const std::wstring& path) {
    HANDLE raw = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (raw == INVALID_HANDLE_VALUE)
        throw Error("Cannot open api_key.txt beside master.exe. " + WindowsError("Open api_key.txt"));
    struct CloseFile { HANDLE value; ~CloseFile() { CloseHandle(value); } } file{raw};
    LARGE_INTEGER size{};
    if (!GetFileSizeEx(raw, &size)) throw Error(WindowsError("Read api_key.txt size"));
    if (size.QuadPart <= 0 || size.QuadPart > 8192)
        throw Error("api_key.txt must contain one API key and be no larger than 8 KiB");
    std::vector<unsigned char> bytes(static_cast<std::size_t>(size.QuadPart));
    DWORD read = 0;
    if (!ReadFile(raw, bytes.data(), static_cast<DWORD>(bytes.size()), &read, nullptr) ||
        read != static_cast<DWORD>(bytes.size()))
        throw Error(WindowsError("Read api_key.txt"));
    return bytes;
}

std::string QueryHeader(HINTERNET request, const wchar_t* name) {
    DWORD bytes = 0;
    WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM, name, nullptr, &bytes, WINHTTP_NO_HEADER_INDEX);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || bytes < sizeof(wchar_t)) return {};
    std::vector<wchar_t> value(bytes / sizeof(wchar_t));
    if (!WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM, name, value.data(), &bytes,
                             WINHTTP_NO_HEADER_INDEX)) return {};
    const std::wstring_view text(value.data(), wcsnlen_s(value.data(), value.size()));
    return Utf8FromWide(text);
}

void CheckCancel(const std::atomic_bool& cancelRequested) {
    if (cancelRequested.load(std::memory_order_relaxed)) throw Error("Generation cancelled");
}

} // namespace

std::wstring ProgramDirectory() {
    std::vector<wchar_t> buffer(1024);
    for (;;) {
        const DWORD length = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (!length) throw Error(WindowsError("Locate master.exe"));
        if (length + 1 < buffer.size()) {
            std::wstring path(buffer.data(), length);
            const auto separator = path.find_last_of(L"\\/");
            if (separator == std::wstring::npos) throw Error("Cannot determine the master.exe directory");
            return path.substr(0, separator);
        }
        if (buffer.size() >= 32768) throw Error("The master.exe path is too long");
        buffer.resize(buffer.size() * 2);
    }
}

std::string Utf8FromWide(std::wstring_view text) {
    if (text.empty()) return {};
    if (text.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw Error("Text is too long to convert to UTF-8");
    const int needed = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0, nullptr, nullptr);
    if (!needed) throw Error(WindowsError("Convert text to UTF-8"));
    std::string result(static_cast<std::size_t>(needed), '\0');
    if (!WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()),
                             result.data(), needed, nullptr, nullptr))
        throw Error(WindowsError("Convert text to UTF-8"));
    return result;
}

std::wstring WideFromUtf8(std::string_view text) {
    if (text.empty()) return {};
    if (text.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw Error("UTF-8 text is too long to convert");
    const int needed = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0);
    if (!needed) throw Error(WindowsError("Convert UTF-8 text"));
    std::wstring result(static_cast<std::size_t>(needed), L'\0');
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()),
                             result.data(), needed))
        throw Error(WindowsError("Convert UTF-8 text"));
    return result;
}

void SecureErase(std::string& value) noexcept {
    if (!value.empty()) SecureZeroMemory(value.data(), value.size());
    value.clear();
    value.shrink_to_fit();
}

std::string LoadApiKey() {
    const std::wstring path = ProgramDirectory() + L"\\api_key.txt";
    auto bytes = ReadSmallFile(path);
    std::size_t begin = 0;
    if (bytes.size() >= 3 && bytes[0] == 0xef && bytes[1] == 0xbb && bytes[2] == 0xbf) begin = 3;
    std::size_t end = bytes.size();
    const auto whitespace = [](unsigned char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; };
    while (begin < end && whitespace(bytes[begin])) ++begin;
    while (end > begin && whitespace(bytes[end - 1])) --end;
    if (begin == end) throw Error("api_key.txt is empty");
    std::string key(reinterpret_cast<const char*>(bytes.data() + begin), end - begin);
    SecureZeroMemory(bytes.data(), bytes.size());
    if (key.size() < 20 || key.size() > 4096)
        throw Error("api_key.txt does not contain a plausible API key");
    for (unsigned char c : key) {
        if (c <= 0x20 || c == 0x7f) {
            SecureErase(key);
            throw Error("api_key.txt must contain only one API key, with no internal whitespace");
        }
    }
    return key;
}

HttpResponse PostResponses(const std::string& apiKey, const std::string& requestBody,
                           const std::atomic_bool& cancelRequested) {
    if (apiKey.empty()) throw Error("The API key is empty");
    if (requestBody.empty() || requestBody.size() > MaxResponseBytes)
        throw Error("The OpenAI request body has an invalid size");
    if (requestBody.size() > std::numeric_limits<DWORD>::max())
        throw Error("The OpenAI request body is too large for WinHTTP");
    CheckCancel(cancelRequested);

    InternetHandle session(WinHttpOpen(L"AnimationMaster-AstraModeler/0.1.0",
                                        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
                                        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0));
    if (!session) throw Error(WindowsError("Initialize HTTPS"));
    if (!WinHttpSetTimeouts(session.get(), 15000, 30000, 60000, 300000))
        throw Error(WindowsError("Configure HTTPS timeouts"));
    InternetHandle connection(WinHttpConnect(session.get(), L"api.openai.com",
                                              INTERNET_DEFAULT_HTTPS_PORT, 0));
    if (!connection) throw Error(WindowsError("Connect to api.openai.com"));
    InternetHandle request(WinHttpOpenRequest(connection.get(), L"POST", L"/v1/responses",
                                               nullptr, WINHTTP_NO_REFERER,
                                               WINHTTP_DEFAULT_ACCEPT_TYPES,
                                               WINHTTP_FLAG_SECURE));
    if (!request) throw Error(WindowsError("Create OpenAI request"));
    DWORD disabled = WINHTTP_DISABLE_REDIRECTS;
    if (!WinHttpSetOption(request.get(), WINHTTP_OPTION_DISABLE_FEATURE, &disabled, sizeof(disabled)))
        throw Error(WindowsError("Disable HTTPS redirects"));

    std::wstring authorization = L"Authorization: Bearer " + WideFromUtf8(apiKey) + L"\r\n";
    struct EraseAuthorization {
        std::wstring& text;
        ~EraseAuthorization() {
            if (!text.empty()) SecureZeroMemory(text.data(), text.size() * sizeof(wchar_t));
        }
    } eraseAuthorization{authorization};
    const wchar_t headers[] = L"Content-Type: application/json\r\nAccept: application/json\r\n";
    if (!WinHttpAddRequestHeaders(request.get(), headers, -1L,
                                  WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE))
        throw Error(WindowsError("Set OpenAI request headers"));
    if (!WinHttpAddRequestHeaders(request.get(), authorization.c_str(),
                                  static_cast<DWORD>(authorization.size()),
                                  WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE))
        throw Error(WindowsError("Set OpenAI authorization"));
    CheckCancel(cancelRequested);
    if (!WinHttpSendRequest(request.get(), WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                            const_cast<char*>(requestBody.data()),
                            static_cast<DWORD>(requestBody.size()),
                            static_cast<DWORD>(requestBody.size()), 0))
        throw Error(WindowsError("Send OpenAI request"));
    CheckCancel(cancelRequested);
    if (!WinHttpReceiveResponse(request.get(), nullptr))
        throw Error(WindowsError("Receive OpenAI response"));

    HttpResponse response;
    DWORD statusBytes = sizeof(response.status);
    if (!WinHttpQueryHeaders(request.get(), WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                             WINHTTP_HEADER_NAME_BY_INDEX, &response.status, &statusBytes,
                             WINHTTP_NO_HEADER_INDEX))
        throw Error(WindowsError("Read OpenAI status"));
    response.requestId = QueryHeader(request.get(), L"x-request-id");

    for (;;) {
        CheckCancel(cancelRequested);
        DWORD available = 0;
        if (!WinHttpQueryDataAvailable(request.get(), &available))
            throw Error(WindowsError("Read OpenAI response size"));
        if (!available) break;
        if (response.body.size() + available > MaxResponseBytes)
            throw Error("OpenAI response exceeds the 8 MiB safety limit");
        const std::size_t offset = response.body.size();
        response.body.resize(offset + available);
        DWORD read = 0;
        if (!WinHttpReadData(request.get(), response.body.data() + offset, available, &read))
            throw Error(WindowsError("Read OpenAI response"));
        response.body.resize(offset + read);
        if (!read) break;
    }
    return response;
}

} // namespace amastra
