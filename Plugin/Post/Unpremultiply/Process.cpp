// NAP  1/26/2005  \Noel120\Plugin\Post\Clamp\Process.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    const int numpixels = width * height;

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();

    const RGBAFloat *source = inbuffer->GetRGBAFloatData();
    RGBAFloat *dest = outbuffer->GetRGBAFloatData();
    /*
       RGBAFloat *tofar = dest + numpixels;
       for (; dest < tofar; dest++, source++) {
          if (source->m_alpha != 0 && source->m_alpha!=1)
             dest->m_color = source->m_color/source->m_alpha;
          dest->m_alpha = source->m_alpha;
       }   
    */
    // ReSharper disable once CppDeclaratorNeverUsed
    const int omp_mode = GetOpenMPMode();
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
    for (int i = 0; i < numpixels; ++i) {
        if (source[i].m_alpha > 0.F && source[i].m_alpha < 1.F)
            dest[i].m_color = source[i].m_color / source[i].m_alpha;
        dest[i].m_alpha = source[i].m_alpha;
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
