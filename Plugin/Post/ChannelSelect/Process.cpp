// Yves  10/11/2006  \Master14.0\Plugin\Post\ChannelSelect\Process.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    if (i == 0)
        return m_channeltype;
    return nullptr;
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth();
    const int height = inbuffer->GetHeight();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    const int channel = m_channeltype->GetValue();
    const int numpixels = height * width;
    // ReSharper disable once CppDeclaratorNeverUsed
    const int omp_mode = GetOpenMPMode();
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
    for (int y = 0; y < numpixels; ++y) {
        switch (channel) {
            case 0:
                outptr[y].m_color.Set(inptr[y].m_color.m_red, inptr[y].m_color.m_red, inptr[y].m_color.m_red);
                break;
            case 1:
                outptr[y].m_color.Set(inptr[y].m_color.m_green, inptr[y].m_color.m_green, inptr[y].m_color.m_green);
                break;
            case 2:
                outptr[y].m_color.Set(inptr[y].m_color.m_blue, inptr[y].m_color.m_blue, inptr[y].m_color.m_blue);
                break;
            case 3:
                outptr[y].m_color.Set(inptr[y].m_alpha, inptr[y].m_alpha, inptr[y].m_alpha);
                break;
            default:;
        }
        outptr[y].m_alpha = inptr[y].m_alpha;
    }
    /*
       for ( int y=0; y < height; ++y ) {
          for ( int x = 0; x < width; ++x ) {
             switch ( channel ) {
                case 0:
                   outptr->m_color.Set( inptr->m_color.m_red, inptr->m_color.m_red, inptr->m_color.m_red );
                   break;
                case 1:
                   outptr->m_color.Set( inptr->m_color.m_green, inptr->m_color.m_green, inptr->m_color.m_green );
                   break;
                case 2:
                   outptr->m_color.Set( inptr->m_color.m_blue, inptr->m_color.m_blue, inptr->m_color.m_blue );
                   break;
                case 3:
                   outptr->m_color.Set( inptr->m_alpha, inptr->m_alpha, inptr->m_alpha );
                   break;
             }
             outptr->m_alpha = inptr->m_alpha;
             ++inptr;
             ++outptr;
          }
       }
    */
    output->SetBuffer(outbuffer);
    return TRUE;
}
