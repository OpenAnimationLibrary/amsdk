//RC  4/24/2002  \HRandy95\Include\FlockMan.h
#pragma once

#include "Vector.h"

class PeerBox;

//particle flock object.
class Boid final {
public:
    Vector location;
    Vector direction;
    int id{0};
    PeerBox *peerbox{nullptr};
};

class BoidList final {
public:
    Boid *boid{nullptr};
    BoidList *next{nullptr};

    BoidList() noexcept = default;
};

class PeerBox final {
public:
    Vector center;
    Vector upperleft;
    Vector lowerright;
    float positionrating{0.F};
    BoidList *boidlist{nullptr};
    PeerBox *top{nullptr}, *bottom{nullptr}, *left{nullptr}, *right{nullptr}, *front{nullptr}, *back{nullptr};

    PeerBox() noexcept = default;

    void ClearBoidList();
};
