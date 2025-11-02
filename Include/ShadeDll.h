//KB  8/27/2003  \Ken110\Include\ShadeDll.h
#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include "HashFile.h"
#include "DllPlugi.h"

class HModel;
class HGroup;
class HObjectListNode;
class HPointerPropertyBase;
class HShading;

//Starting with A:M v12 plugin versions are in sync with A:M versions.
//For instance, for A:M v12, PLUGINVERSION will be 120, and etc.
//Previous to v12, Shader versions were 1.
//Shader version 120 added GetPointerList, OnNotifyNewProperty, GetModel and GetGroup.

#define SHADERDLLVERSION PLUGINVERSION// NOLINT(cppcoreguidelines-macro-usage)

// ReSharper disable once CppClassCanBeFinal
class PLUGINEXPORT Shader : public DLLPlugin {
public:
    explicit Shader(HTreeObject *treeobject) : DLLPlugin(treeobject) {}
    virtual const char *GetShaderDiffuseFilters() = 0;
    virtual const char *GetShaderSpecularFilters() = 0;
    //RENDERING
    virtual void GetDiffuse(HShading *shading) = 0;
    virtual bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) = 0;

    virtual HObjectListNode *GetPointerList(HPointerPropertyBase *) {
        return nullptr;
    }

    virtual void OnNotifyNewProperty(HProperty *, const String &) {}

    enum ShaderType : UINT {
        ST_NORMAL,
        ST_BRDF,
        ST_HAIR
    }; //powers of 2

    virtual ShaderType GetShaderType() {
        return ST_NORMAL;
    }

    //detect what we are currently applied to
    HModel *GetModel(); //May be nullptr, if on a material attribute
    [[nodiscard]] HGroup *GetGroup() const; //May be nullptr, if not on a group
};

// ReSharper disable once CppClassCanBeFinal
class Shader2 : public Shader {
public:
    explicit Shader2(HTreeObject *treeobject) : Shader(treeobject) {}
    virtual const char *GetShaderAmbianceFilters() = 0;
    virtual void GetAmbiance(HShading *shading) = 0;
};
