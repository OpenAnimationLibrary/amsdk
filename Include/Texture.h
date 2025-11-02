//BC  6/14/2005  \Master120\Include\Texture.h
#pragma once

#include "DllPlugi.h"

class HTexInfo;
class Vector;
class HModel;
class HGroup;
class HObjectListNode;
class HPointerPropertyBase;

constexpr int TEXTUREDLLVERSION = 2;

// ReSharper disable once CppClassCanBeFinal
class PLUGINEXPORT Texture : public DLLPlugin {
    //this has a chance of breaking old texture plugins, if so, just export the bottom two functions below
public:
    Texture() noexcept = default;
    explicit Texture(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}

    //RENDERING
    virtual bool Evaluate(const Vector &evalp, HTexInfo *texinfo) = 0;
    virtual bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) = 0;

    virtual HObjectListNode *GetPointerList(HPointerPropertyBase *prop, bool ignoreinvisible = false) {
        return nullptr;
    }

    virtual void CheckOut(HHashObject *cache) {} //used copy instead, could remove this function
    virtual void OnNotifyNewProperty(HProperty *prop, const String &matchname) {}

    //detect what we are currently applied to
    [[nodiscard]] HModel *GetModel() const; //this one should never be nullptr
    [[nodiscard]] HGroup *GetGroup() const; //this one can be nullptr, if not on a group
};
