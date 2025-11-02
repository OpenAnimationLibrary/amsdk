// MH  6/30/2005  \Mart120\Plugin\Post\AliasEdges\Process.cpp

#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

#include "RGBHalf.inl"

extern CPostApp theApp;

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //someday maybe to choose to use a colorproperty or the inputs bkcolor
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    const RGBFloat bkcolor = inbuffer->GetBackground();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy(); //copys background

    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    const UINT count = width * height;
    for (UINT p = 0; p < count; ++p) {
        if (const float opacity = inptr[p].m_alpha) {
            if (opacity == 1.F)
                outptr[p] = inptr[p];
            else {
                if (opacity > 0.5F) {
                    outptr[p].m_color = inptr[p].m_color / opacity;
                    outptr[p].m_alpha = 1.F;
                } else {
                    outptr[p].m_color = bkcolor;
                    outptr[p].m_alpha = 0.F;
                }
            }
        } else
            outptr[p].m_color = bkcolor;
    }
    /*
       int count = width * height;
       for (int p = 0; p < count; ++p) {
          float opacity = inptr->m_alpha;
          if (opacity) {
             if (opacity == 1.F)
                *outptr = *inptr;
             else {
                if (opacity > 0.5F) {
                   outptr->m_color = inptr->m_color/opacity;
                   outptr->m_alpha = 1.F;
                } else {
                   outptr->m_color = bkcolor;
                   outptr->m_alpha = 0.F;
                }
             }
          } else 
             outptr->m_color = bkcolor;
    
          ++inptr; ++outptr;
       }
    */
    output->SetBuffer(outbuffer);
    return TRUE;
}
