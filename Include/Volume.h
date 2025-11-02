//Dan  11/27/2001  \Dan90\Include\Volume.h
#pragma once

#include "VolBuf.h"
#include "DllPlugi.h"

#define VOLUMETRICDLLVERSION 2  // NOLINT(cppcoreguidelines-macro-usage)

class Volumetric : public DLLPlugin {
public:
   VolBuf m_volbuf;

   Volumetric() noexcept = default;
   explicit Volumetric(HTreeObject *treeobject) : DLLPlugin(treeobject) {}
//RENDERING
   virtual float GetOpacity(float falloff) = 0;
};
