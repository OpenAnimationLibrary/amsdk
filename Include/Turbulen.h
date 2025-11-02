//Dan  11/26/2001  \Dan90\Include\Turbulen.h
#pragma once

#include "DllPlugi.h"

constexpr int TURBULENCEDLLVERSION = 2;

class Vector;

// ReSharper disable once CppClassCanBeFinal
class Turbulence : public DLLPlugin {
public:
    explicit Turbulence(HTreeObject *treeobject) : DLLPlugin(treeobject) {}
    //RENDERING
    virtual float Evaluate(const Vector &evalp) = 0;
};
