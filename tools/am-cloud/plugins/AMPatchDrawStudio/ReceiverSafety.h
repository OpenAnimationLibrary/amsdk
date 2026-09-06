#pragma once
// Ordinary-data guards; no SDK calls, HWNDs or cross-thread ownership.
#include <array>
#include <cstddef>

namespace patchstudio {
struct ReceiverLifetime {
    unsigned callbackDepth = 0;
    bool windowOwns = false;
    bool detached = false;
};

// A modeless receiver can be destroyed inside a nested confirmation message
// loop. WM_NCDESTROY releases window ownership only after the last active
// callback unwinds. The command's unique_ptr owns failed creation until then.
// All callbacks and ownership changes occur on A:M's UI thread.
template<class State> class ReceiverCallbackLease {
    State* state_;
public:
    explicit ReceiverCallbackLease(State* state) noexcept : state_(state) {
        ++state_->callbackDepth;
    }
    ReceiverCallbackLease(const ReceiverCallbackLease&) = delete;
    ReceiverCallbackLease& operator=(const ReceiverCallbackLease&) = delete;
    ~ReceiverCallbackLease() noexcept {
        if (--state_->callbackDepth == 0 && state_->windowOwns && state_->detached)
            delete state_;
    }
};

// Canonical sorting establishes identity but does not prove boundary order.
// Accept cyclic rotations and reversed winding, never a crossed permutation.
inline bool SameFaceCycle(const std::array<std::size_t,4>& actual,
                          const std::array<std::size_t,4>& expected) noexcept {
    for (std::size_t start=0; start<4; ++start) {
        bool forward=true, backward=true;
        for (std::size_t i=0; i<4; ++i) {
            forward = forward && actual[i] == expected[(start+i)%4];
            backward = backward && actual[i] == expected[(start+4-i)%4];
        }
        if (forward || backward) return true;
    }
    return false;
}
} // namespace patchstudio
