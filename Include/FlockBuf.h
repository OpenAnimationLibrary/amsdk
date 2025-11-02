//KB  3/5/01  \Ken90\Include\FlockBuf.h
#pragma once

#include "Exports.h"
#include "Vector.h"
#include "FlockMan.h"
#include "HashTime.h"

class InfluenceShape;

class PLUGINEXPORT FlockBuf final {
public:
    Time m_prevframe;
    Time m_maxactionoffset;
    Vector m_p;
    Vector m_worldp;
    Vector m_worlddirection;
    Vector m_prevpos;
    Vector m_ulbounds;
    Vector m_lrbounds;
    Vector m_subdiv{10.F}; //peerbox lattice dimensions
    float m_pbwidth{0.F};
    float m_pbheight{0.F};
    float m_pbdepth{0.F};
    int m_numboids{0};
    InfluenceShape *m_influenceshape{nullptr};
    Boid *m_boids{nullptr};
    PeerBox *m_peerboxlist{nullptr};

    FlockBuf() noexcept = default;

    ~FlockBuf() {
        Clear();
    }

    FlockBuf(const FlockBuf &) = delete;
    FlockBuf(FlockBuf &&) = delete;
    FlockBuf &operator=(FlockBuf &&) = delete;
    FlockBuf &operator=(const FlockBuf &) = delete;

    PeerBox *CreatePeerBoxList();
    void DistributeBoids() const;
    void InitBoidList(int num);
    void Clear();
    [[nodiscard]] float GetFallOffValue(const Vector &p) const;
    static Boid *FindClosestNeighbor(const Boid *boid, const Boid *excludedboid);
};
