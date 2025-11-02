// MH  6/30/2005  \Mart120\Plugin\Post\Gamma\Process.cpp

#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    if (i == 0)
        return m_style;
    return nullptr;
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //get property values
    const float gamma = m_gamma->GetValue();
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    if (!inbuffer)
        return FALSE;
    if (gamma == 0.F || gamma == 1.F) {
        output->SetBuffer(inbuffer->MakeCopy());
        return TRUE;
    }
    const float inversegamma = 1.F / gamma;

    //get bitmap info
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();

    const UINT count = width * height;
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    for (UINT p = 0; p < count; ++p) {
        outptr[p].m_color.m_red = hash_math::pow(inptr[p].m_color.m_red, inversegamma);
        outptr[p].m_color.m_green = hash_math::pow(inptr[p].m_color.m_green, inversegamma);
        outptr[p].m_color.m_blue = hash_math::pow(inptr[p].m_color.m_blue, inversegamma);
        outptr[p].m_alpha = inptr[p].m_alpha;
    }
    /*
       for (int p = 0; p < count; p++, ++outptr, ++inptr) {
          outptr->m_color.m_red = (float)pow( inptr->m_color.m_red, inversegamma );
          outptr->m_color.m_green = (float)pow( inptr->m_color.m_green, inversegamma );
          outptr->m_color.m_blue = (float)pow( inptr->m_color.m_blue, inversegamma );
          outptr->m_alpha = inptr->m_alpha;
       }
    */
    output->SetBuffer(outbuffer);
    return TRUE;
}
