// Yves 03/11/07  \My Plugins\Turb\Musgrave\Blender.cpp

// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
//#include "StdAfx.h"
#include "Custom.h"
#include "Blender.h"

BlenderUI::~BlenderUI() {
    delete m_BlendTypeInfo;
}

void BlenderUI::InitProperties() {
    CString string;

    m_BlendTypeInfoArray.SetArraySize(23);
    for (int i = 0; i < 23; i++) {
        HTypeInfo *typeinfo = m_BlendTypeInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Add");
                string.LoadString(IDS_B_ADD);
                break;
            case 1:
                typeinfo->SetMatchName("Subtract");
                string.LoadString(IDS_B_SUBTRACT);
                break;
            case 2:
                typeinfo->SetMatchName("Multiply");
                string.LoadString(IDS_B_MULTIPLY);
                break;
            case 3:
                typeinfo->SetMatchName("Screen");
                string.LoadString(IDS_B_SCREEN);
                break;
            case 4:
                typeinfo->SetMatchName("Darken");
                string.LoadString(IDS_B_DARKEN);
                break;
            case 5:
                typeinfo->SetMatchName("Lighten");
                string.LoadString(IDS_B_LIGHTEN);
                break;
            case 6:
                typeinfo->SetMatchName("Difference");
                string.LoadString(IDS_B_DIFFERENCE);
                break;
            case 7:
                typeinfo->SetMatchName("Negation");
                string.LoadString(IDS_B_NEGATION);
                break;
            case 8:
                typeinfo->SetMatchName("Exclusion");
                string.LoadString(IDS_B_EXCLUSION);
                break;
            case 9:
                typeinfo->SetMatchName("Overlay");
                string.LoadString(IDS_B_OVERLAY);
                break;
            case 10:
                typeinfo->SetMatchName("Hard Light");
                string.LoadString(IDS_B_HARDLIGHT);
                break;
            case 11:
                typeinfo->SetMatchName("Soft Light");
                string.LoadString(IDS_B_SOFTLIGHT);
                break;
            case 12:
                typeinfo->SetMatchName("Dodge");
                string.LoadString(IDS_B_DODGE);
                break;
            case 13:
                typeinfo->SetMatchName("Dodge");
                string.LoadString(IDS_B_SOFTDODGE);
                break;
            case 14:
                typeinfo->SetMatchName("Dodge");
                string.LoadString(IDS_B_INVDODGE);
                break;
            case 15:
                typeinfo->SetMatchName("Burn");
                string.LoadString(IDS_B_BURN);
                break;
            case 16:
                typeinfo->SetMatchName("Burn");
                string.LoadString(IDS_B_SOFTBURN);
                break;
            case 17:
                typeinfo->SetMatchName("Burn");
                string.LoadString(IDS_B_INVBURN);
                break;
            case 18:
                typeinfo->SetMatchName("Reflect");
                string.LoadString(IDS_B_REFLECT);
                break;
            case 19:
                typeinfo->SetMatchName("Glow");
                string.LoadString(IDS_B_GLOW);
                break;
            case 20:
                typeinfo->SetMatchName("Freeze");
                string.LoadString(IDS_B_FREEZE);
                break;
            case 21:
                typeinfo->SetMatchName("Heat");
                string.LoadString(IDS_B_HEAT);
                break;
            case 22:
                typeinfo->SetMatchName("Stamp");
                string.LoadString(IDS_B_STAMP);
                break;
        }
        typeinfo->SetLocalizedName(string.GetBuffer());
    }
    string.LoadString(IDS_COMBINER);
    m_BlendTypeInfo = HTypePropertyInfo::New(string, "Blend Mode", &m_BlendTypeInfoArray);
    m_BlendTypeInfo->SetDefaultIndex(0);
}

Blender::~Blender() {
    delete m_BlendType;
}

void Blender::LinkProperties(const BlenderUI &UI) {
    m_BlendType = HTypeProperty::New(UI.m_BlendTypeInfo);
}

// ReSharper disable once CppMemberFunctionMayBeConst
HProperty *Blender::GetPropertyAt(int &i) {
    if (i == 0)
        return m_BlendType;
    i --;
    return nullptr;
}

void Blender::Reset() {
    m_Mode = m_BlendType->GetValue();
    if (m_Mode + IDS_B_ADD == IDS_B_MULTIPLY) {
        a = 1.F;
    } else {
        a = 0.F;
    }
/*
    switch (m_Mode + IDS_B_ADD) {
        case IDS_B_ADD:
        case IDS_B_SUBTRACT:
            a = 0.F;
            return;
        case IDS_B_MULTIPLY:
            a = 1.F;
            return;
        case IDS_B_SCREEN:
        case IDS_B_DARKEN:
        case IDS_B_LIGHTEN:
        case IDS_B_DIFFERENCE:
        case IDS_B_NEGATION:
        case IDS_B_EXCLUSION:
        case IDS_B_OVERLAY:
        case IDS_B_HARDLIGHT:
        case IDS_B_SOFTLIGHT:
        case IDS_B_DODGE:
        case IDS_B_SOFTDODGE:
        case IDS_B_INVDODGE:
        case IDS_B_BURN:
        case IDS_B_SOFTBURN:
        case IDS_B_INVBURN:
        case IDS_B_REFLECT:
        case IDS_B_GLOW:
        case IDS_B_FREEZE:
        case IDS_B_HEAT:
        case IDS_B_STAMP:
            a = 0.F;
    }
   */ 
}

void Blender::Blend(const float b) {
    switch (m_Mode + IDS_B_ADD) {
        case IDS_B_ADD:
            a = a + b;
            return;
        case IDS_B_SUBTRACT:
            a = a + b - 1.F;
            return;
        case IDS_B_MULTIPLY:
            a = a * b;
            return;
        case IDS_B_SCREEN:
            a = 1.F - (1.F - a) * (1.F - b);
            return;
        case IDS_B_DARKEN:
            a = a < b ? a : b;
            return;
        case IDS_B_LIGHTEN:
            a = a > b ? a : b;
            return;
        case IDS_B_DIFFERENCE:
            a = hash_math::abs(a - b);
            return;
        case IDS_B_NEGATION:
            a = 1.F - hash_math::abs(1.F - a - b);
            return;
        case IDS_B_EXCLUSION:
            a = a + b - 2.F * a * b;
            return;
        case IDS_B_OVERLAY:
            a = a < 0.5F ? 2.F * a * b : 1.F - 2.F * (1.F - a) * (1.F - b);
            return;
        case IDS_B_HARDLIGHT:
            a = b < 0.5F ? 2.F * a * b : 1.F - 2.F * (1.F - a) * (1.F - b);
            return;
        case IDS_B_SOFTLIGHT:
            a = 2.F * a * b + a * a - 2.F * a * a * b;
            return;
        case IDS_B_DODGE:
            a = a / (1.F - b);
            return;
        case IDS_B_SOFTDODGE:
            a = a + b < 1.F ? 0.5F * a / (1.F - b) : 1.F - 0.5F * (1.F - b) / a;
            return;
        case IDS_B_INVDODGE:
            a = b / (1.F - a);
            return;
        case IDS_B_BURN:
            a = 1.F - (1.F - a) / b;
            return;
        case IDS_B_SOFTBURN:
            a = a + b < 1.F ? 0.5F * b / (1.F - a) : 1.F - 0.5F * (1.F - a) / b;
            return;
        case IDS_B_INVBURN:
            a = 1.F - (1.F - b) / a;
            return;
        case IDS_B_REFLECT:
            a = a * a / (1.F - b);
            return;
        case IDS_B_GLOW:
            a = b * b / (1.F - a);
            return;
        case IDS_B_FREEZE:
            a = 1.F - (1.F - a) * (1.F - a) / b;
            return;
        case IDS_B_HEAT:
            a = 1.F - (1.F - b) * (1.F - b) / a;
            return;
        case IDS_B_STAMP:
            a = a + 2.F * b - 1.F;
            return;
    }
    a = a + b;
}
