#pragma once
#include <cstdint>
#include <cwchar>
#include <type_traits>

constexpr std::uint32_t FW2_API_VERSION = 1;
constexpr std::size_t FW2_MAX_TEXT = 512;
enum FW2Status : std::int32_t {
    FW2_COMPLETED = 0, FW2_CANCELLED = 1, FW2_INVALID_INPUT = 2,
    FW2_FAILED = 3, FW2_BUSY = 4, FW2_WRONG_THREAD = 5
};
struct FW2Request {
    std::uint32_t size = sizeof(FW2Request);
    std::uint32_t version = FW2_API_VERSION;
    void *model = nullptr;  // Borrowed HModelCache; null permits a new model only.
    void *owner = nullptr;  // Borrowed HWND. Synchronous call, A:M UI thread only.
    wchar_t text[FW2_MAX_TEXT + 1]{};
};
struct FW2Reply {
    std::uint32_t size = sizeof(FW2Reply);
    std::uint32_t version = FW2_API_VERSION;
    void *model = nullptr;  // Host-owned result; the caller must never delete it.
    std::uint32_t splines = 0;
    wchar_t text[FW2_MAX_TEXT + 1]{};
    wchar_t detail[256]{};
};
static_assert(std::is_standard_layout_v<FW2Request>);
static_assert(std::is_standard_layout_v<FW2Reply>);
inline bool FW2ValidRequest(const FW2Request *request, const FW2Reply *reply) {
    if (!request || !reply || request->size != sizeof(FW2Request) ||
        request->version != FW2_API_VERSION || reply->size != sizeof(FW2Reply) ||
        reply->version != FW2_API_VERSION) return false;
    const wchar_t *end = std::wmemchr(request->text, L'\0', FW2_MAX_TEXT + 1);
    if (!end || end == request->text) return false;
    // GDI's native outlines here support BMP characters; reject surrogate pairs
    // explicitly, rather than splitting or silently substituting them.
    bool visible = false;
    for (const wchar_t *c = request->text; c != end; ++c) {
        if ((*c >= 0xD800 && *c <= 0xDFFF) ||
            (*c < 32 && *c != L'\r' && *c != L'\n' && *c != L'\t')) return false;
        if (*c > 32) visible = true;
    }
    return visible;
}
