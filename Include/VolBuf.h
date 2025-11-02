//MH  16 Jul 1998
#pragma once

#include "Exports.h"
#include "Vector.h"

class TurbulenceNode;
class InfluenceShape;

class VolBuf final {
public:
    Vector m_p;
    Vector m_worldp;
    TurbulenceNode *turbnodehead{nullptr};
    InfluenceShape *influenceshape{nullptr};

    VolBuf() noexcept = default;
    ~VolBuf() = default;

    VolBuf(const VolBuf &) = delete;
    VolBuf(VolBuf &&) = delete;
    VolBuf &operator=(VolBuf &&) = delete;
    VolBuf &operator=(const VolBuf &) = delete;

#if defined (__INTEL_LLVM_COMPILER)
    PLUGINEXPORT float GetTurbulenceValue(const Vector &turbp) const;
    PLUGINEXPORT float GetFallOffValue(const Vector &p) const;
#else
    PLUGINEXPORT [[nodiscard]] float GetTurbulenceValue(const Vector &turbp) const;
    PLUGINEXPORT [[nodiscard]] float GetFallOffValue(const Vector &p) const;
#endif
};
