// Dan  11/26/2001  \Dan90\Plugin\Textures\Wave\Construc.cpp

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
    m_amplitude = HFloatProperty::New(theApp.m_amplitudeinfo);
    m_wavelength = HFloatProperty::New(theApp.m_wavelengthinfo);
    m_damping = HFloatProperty::New(theApp.m_dampinginfo);
    m_propagate = HFloatProperty::New(theApp.m_propagateinfo);
    m_cycle = HFloatProperty::New(theApp.m_cycleinfo);

}

CustomTexture::~CustomTexture() {
    delete m_amplitude;
    delete m_wavelength;
    delete m_damping;
    delete m_propagate;
    delete m_cycle;
}
