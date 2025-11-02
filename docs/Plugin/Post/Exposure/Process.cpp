// YP  10/02/2005  \Yves120\Plugin\Post\Exposure\Process.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_exposure;
        case 1:
            return m_brightness;
        case 2:
            return m_contrast;
        default:
            return nullptr;
    }
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    // Exposure is 
    const float exposure = hash_math::pow(2.F, m_exposure->GetValue());
    const float brightness = m_brightness->GetValue() * 2.F - 1.5F;
    const float contrast = hash_math::tan(m_contrast->GetValue() * 1.57079F);

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth();
    const int height = inbuffer->GetHeight();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    if (!outbuffer)
        return FALSE;

//    RGBFloat newcolor;
    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    if (!outptr) {
        delete outbuffer;
        return FALSE;
    }
    const int numpixels = height * width;
    // ReSharper disable once CppDeclaratorNeverUsed
    const int omp_mode = GetOpenMPMode();
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
    for (int y = 0; y < numpixels; ++y) {
        outptr[y].m_color = (inptr[y].m_color * exposure + brightness) * contrast + 0.5F;
        outptr[y].m_color.ClampBounds();
        outptr[y].m_alpha = inptr[y].m_alpha;
    }
    /*
       for (int y=0; y < height; ++y) {
          for (int x = 0; x < width; ++x) {
             outptr->m_color = ( inptr->m_color * exposure + brightness ) * contrast + 0.5F;
             outptr->m_color.Min( 0.F );
             outptr->m_alpha = inptr->m_alpha;
             ++inptr;
             ++outptr;
          }
       }
    */
    output->SetBuffer(outbuffer);
    return TRUE;
}
