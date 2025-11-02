//KB  6/12/2003  \Ken105\Include\flockdll.h
#pragma once

#include "DllPlugi.h"
#include "FlockBuf.h"
#include "Rotate.h"

#define FLOCKDLLVERSION 1  // NOLINT(cppcoreguidelines-macro-usage)

// ReSharper disable once CppClassCanBeFinal
class Flock : public DLLPlugin {
public:
    FlockBuf m_flockbuf;
    Flock *m_nextflock{nullptr};

    explicit Flock(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}
    virtual void InitParticlePos(int id, TSQ &tsq, Time &actionoffset) = 0;
    virtual void UpdateParticlePos(int id, TSQ &tsq, Vector &d, float frametime) = 0;
};
