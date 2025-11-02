// Yves 03/11/07  \My Plugins\Turb\Musgrave\Blender.h
#pragma once
#include "SDK/HPropert.h"

class BlenderUI {
public:
    TypeInfoArray m_BlendTypeInfoArray;
    HTypePropertyInfo *m_BlendTypeInfo;

    BlenderUI() noexcept = default;
    ~BlenderUI();

    BlenderUI(const BlenderUI&) = delete;
    BlenderUI &operator= (const BlenderUI&) = delete; 
    BlenderUI(BlenderUI &&) = delete; 
    BlenderUI &operator=(BlenderUI &&) = delete; 

    void InitProperties();
};

class Blender {
public:
    float a{0.F};
    int m_Mode{0};
    HTypeProperty *m_BlendType{nullptr};

    Blender() noexcept = default;
    ~Blender();

    Blender(const Blender&) = delete;
    Blender &operator= (const Blender&) = delete; 
    Blender(Blender &&) = delete; 
    Blender &operator=(Blender &&) = delete; 

    void LinkProperties(const BlenderUI &UI);
    HProperty *GetPropertyAt(int &i);

    operator float() const {
        return a;
    }

    void Reset();
    void Blend(float b);
};
