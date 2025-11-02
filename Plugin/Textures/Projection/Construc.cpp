// Dan  11/26/2001  \Dan90\Plugin\Textures\Projection\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

extern "C" __declspec(dllexport) Texture *CreateTexture(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomTexture(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return TEXTUREDLLVERSION;
}

CustomTexture::CustomTexture(HTreeObject *treeobject) : Texture(treeobject) {
    m_clip = HClipProperty::New(theApp.m_clipinfo);
    m_type = HTypeProperty::New(theApp.m_typeinfo);
    m_kind = HTypeProperty::New(theApp.m_kindinfo);
    m_value = HFloatProperty::New(theApp.m_valueinfo);
    m_size = HVector2Property::New(theApp.m_sizeinfo);
}

CustomTexture::~CustomTexture() {
    delete m_clip;
    delete m_kind;
    delete m_type;
    delete m_value;
    delete m_size;
}

bool CustomTexture::ParseArg(const char *label, const char *value) {
    // pre 9.0 backward compatability
    if (_stricmp(label, "ImageName") == 0) {
        String filename = value;
        if (filename != "EMPTY") {
            filename = filename.GetAbsolutePath();
            m_clip->LoadImageHash(filename);
        }
        return TRUE;
    }
    return FALSE;
}
