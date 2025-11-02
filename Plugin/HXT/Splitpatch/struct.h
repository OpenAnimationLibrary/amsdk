#pragma once

#include "Splitpatch.h"

struct PointSP {
    Vector pos;
    HCP *cp{};
    bool attached{};
};

struct Parameter {
    BOOL insert; //CP insert
    BOOL connect; //CP connect
};

struct nSpline {
    CArrayEx<Vector, Vector> pos;
};
