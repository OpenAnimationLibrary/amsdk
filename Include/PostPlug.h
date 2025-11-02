//Dan  7/20/2004  \DanLP115\Include\PostPlug.h
#pragma once

#include "DllPlugi.h"

constexpr int POSTDLLVERSION = 2;

class HBufferShortcut;
class HPostInfo;

// ReSharper disable once CppClassCanBeFinal
class PostPlugin : public DLLPlugin {
public:
    enum Info : UINT {
        NORMAL       = 0U,
        USES_ZBUFFER = 1U << 0U,
        IS_BLUR      = 1U << 1U,
        //turns on enhanced multipass if effect is on camera
    };

    enum Styles : UINT {
        STYLE_ERROR  = 0U,
        STYLE_RGBA   = 1U << 0U,
        STYLE_SCALAR = 1U << 1U,
    };

//    PostPlugin() noexcept = default;
    explicit PostPlugin(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}

    virtual bool Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
        return true;
    }

    virtual int GetNumInputs() {
        return 1;
    }

    virtual Styles GetAllowedInputBufferStyles() = 0;

    virtual Info GetInfo() {
        return NORMAL;
    }
};
