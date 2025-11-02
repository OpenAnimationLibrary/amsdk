// 

#include "StdAfx.h"
#include "StrClass.h"
#include "Custom.h"
#include "Shader.h"
#include "F_Protos.h"

extern CShaderApp theApp;

extern "C" __declspec(dllexport) Shader *CreateShader(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomShader(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return SHADERDLLVERSION;
}

//float* CustomShader::cosTable = nullptr;
//float* CustomShader::acosTable = nullptr;

CustomShader::CustomShader(HTreeObject *treeobject) : Shader(treeobject) {
    m_primWidth = HPercentProperty::New(theApp.m_primWidthInfo);
    m_scndryWidth = HPercentProperty::New(theApp.m_scndryWidthInfo);
    m_transWidth = HPercentProperty::New(theApp.m_transWidthInfo);

    m_primDev = HPercentProperty::New(theApp.m_primDevInfo);
    m_scndryDev = HPercentProperty::New(theApp.m_scndryDevInfo);
    m_transDev = HPercentProperty::New(theApp.m_transDevInfo);

    m_primStrength = HPercentProperty::New(theApp.m_primStrengthInfo);
    m_scndryStrength = HPercentProperty::New(theApp.m_scndryStrengthInfo);
    m_transStrength = HPercentProperty::New(theApp.m_transStrengthInfo);

    m_fresnelAmt = HPercentProperty::New(theApp.m_fresInfo);
    m_ior = HFloatProperty::New(theApp.m_iorInfo);

    m_directionAtten = HPercentProperty::New(theApp.m_directionAttenInfo);

    m_specBlend = HPercentProperty::New(theApp.m_specBlendInfo);
    /*	
       // cos lookup table
        // possible values range from -pi/2 to +pi/2
       if (cosTable == 0) {
            cosTable = new float[TABLE_SIZE];
    
            // arcosinus lookup table
            // possible values range from 0 to 1
            acosTable = new float[TABLE_SIZE];
    
            int i;
    
            for (i = 0; i < TABLE_SIZE; ++i)
            {
                cosTable[i] = hash_math::cos(((float)i / (float)TABLE_SIZE) * M_PI - M_PI/2.F);
                acosTable[i] = hash_math::cos((float)i / (float)TABLE_SIZE);
            }
       }
       */
}

CustomShader::~CustomShader() {
    delete m_primWidth;
    delete m_scndryWidth;
    delete m_transWidth;

    delete m_primDev;
    delete m_scndryDev;
    delete m_transDev;

    delete m_primStrength;
    delete m_scndryStrength;
    delete m_transStrength;

    delete m_fresnelAmt;
    delete m_ior;

    delete m_directionAtten;

    delete m_specBlend;
}
