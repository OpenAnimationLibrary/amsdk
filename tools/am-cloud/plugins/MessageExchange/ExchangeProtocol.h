#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

// Versioned, caller-owned data. No CString, allocation, or exceptions cross DLLs.
constexpr std::uint32_t AM_MESSAGE_VERSION = 1;
constexpr std::size_t AM_MESSAGE_CAPACITY = 256;

enum AMMessageStatus : std::int32_t {
    AM_MESSAGE_OK = 0,
    AM_MESSAGE_CANCELLED = 1,
    AM_MESSAGE_INVALID = 2,
    AM_MESSAGE_BUSY = 3,
    AM_MESSAGE_FAILED = 4
};

struct AMMessageRequest {
    std::uint32_t size = sizeof(AMMessageRequest);
    std::uint32_t version = AM_MESSAGE_VERSION;
    void *context = nullptr;       // Borrowed A:M object, valid only during this call.
    void *owner_window = nullptr;  // Borrowed HWND; no ownership transfer.
    char message[AM_MESSAGE_CAPACITY]{};
};

struct AMMessageReply {
    std::uint32_t size = sizeof(AMMessageReply);
    std::uint32_t version = AM_MESSAGE_VERSION;
    char message[AM_MESSAGE_CAPACITY]{};
};

static_assert(std::is_standard_layout_v<AMMessageRequest>);
static_assert(std::is_standard_layout_v<AMMessageReply>);
#ifdef _WIN64
static_assert(sizeof(AMMessageRequest) == 280);
static_assert(sizeof(AMMessageReply) == 264);
#endif

// Called by the real DLL export and by the standalone protocol test.
// The callback represents the receiving plugin's modal task; true = completed.
template<class Task>
AMMessageStatus ReceiveAMMessage(const AMMessageRequest *request,
                                AMMessageReply *reply, const char *receiver,
                                Task task) {
    if (!request || !reply || !receiver ||
        request->size != sizeof(AMMessageRequest) ||
        request->version != AM_MESSAGE_VERSION ||
        reply->size != sizeof(AMMessageReply) ||
        reply->version != AM_MESSAGE_VERSION)
        return AM_MESSAGE_INVALID;
    reply->message[0] = '\0';
    if (!request->context || !request->message[0] ||
        !std::memchr(request->message, '\0', sizeof(request->message)))
        return AM_MESSAGE_INVALID;
    const bool completed = task(*request);
    std::snprintf(reply->message, sizeof(reply->message),
                  completed ? "%s received your message and completed its task."
                            : "%s cancelled its task.", receiver);
    return completed ? AM_MESSAGE_OK : AM_MESSAGE_CANCELLED;
}
