// NAP  12/28/2004  \Noel120\Plugin\Post\Add\Process.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    if (i == 0)
        return m_percent;
    return nullptr;
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 2;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    /*
    designed for combining light buffers
    for each x,y < min input width,height 
    sets output color to percent * buffer1->m_color * buffer2->m_color
    not sure what I should do with alpha but for now
    sets alph to MAX(buffer1->m_alpha, buffer2->m_alpha)
    //sets alpha to (buffer1->m_alpha * abspercent1 + buffer2->m_alpha * abspercent2)/(abspercent1+abspercent2);
    */

    //get property values
    const float percent = m_percent->GetValue();

    //get bitmap info
    HBufferShortcut *input = inputs;
    HRGBAFloatBuffer *inbuffer1 = input->GetRGBAFloatBuffer(time);
    if (!inbuffer1)
        return FALSE;
    if (percent == 0.F) {
        output->SetBuffer(inbuffer1->MakeCopy()); //NAP Bitmap COME-back
        return TRUE;
    }
    const int width1 = inbuffer1->GetWidth(), height1 = inbuffer1->GetHeight();
    input = input->GetNextBufferShortcut();
    if (!input || width1 < 1 || height1 < 1)
        return FALSE;
    HRGBAFloatBuffer *inbuffer2 = input->GetRGBAFloatBuffer(time);
    if (!inbuffer2)
        return FALSE;
    const int width2 = inbuffer2->GetWidth(), height2 = inbuffer2->GetHeight();
    if (width2 < 1 || height2 < 1)
        return FALSE;
    const int width = MIN(width1, width2);
    const int height = MIN(height1, height2);
    HRGBAFloatBuffer *outbuffer = HBitmapNode::CreateRGBAFloatBuffer("RGBA", width, height);
    outbuffer->SetBackground(inbuffer1->GetBackground());
    outbuffer->AllocateData();

    const RGBAFloat *inptr1 = inbuffer1->GetRGBAFloatData();
    const RGBAFloat *inptr2 = inbuffer2->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    const int numpixels = height * width;
    // ReSharper disable once CppDeclaratorNeverUsed
    const int omp_mode = GetOpenMPMode();
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
    for (int y = 0; y < numpixels; ++y) {
        outptr[y].m_color.m_red = inptr1[y].m_color.m_red * percent * inptr2[y].m_color.m_red;
        outptr[y].m_color.m_green = inptr1[y].m_color.m_green * percent * inptr2[y].m_color.m_green;
        outptr[y].m_color.m_blue = inptr1[y].m_color.m_blue * percent * inptr2[y].m_color.m_blue;
        outptr[y].m_alpha = MAX(inptr1[y].m_alpha, inptr2[y].m_alpha);
    }
    /*
       RGBFloat newcolor;
       RGBAFloat *rows1 = inbuffer1->GetRGBAFloatData();
       RGBAFloat *rows2 = inbuffer2->GetRGBAFloatData();
       RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
       RGBAFloat *inptr1, *inptr2;
       for (int y=0; y < height; ++y) {
          inptr1 = rows1;
          inptr2 = rows2;
          for (int x = 0; x < width; ++x) {
             outptr->m_color.m_red = inptr1->m_color.m_red * percent * inptr2->m_color.m_red;
             outptr->m_color.m_green = inptr1->m_color.m_green * percent * inptr2->m_color.m_green;
             outptr->m_color.m_blue = inptr1->m_color.m_blue * percent * inptr2->m_color.m_blue;
             outptr->m_alpha = MAX(inptr1->m_alpha, inptr2->m_alpha);
             //outptr->m_alpha = (inptr1->m_alpha * abspercent1 + inptr2->m_alpha * abspercent2)/abspercents;
             ++inptr1; ++inptr2; ++outptr;
          }
          rows1+=width1; rows2+=width2;
       }
    */
    output->SetBuffer(outbuffer);
    return TRUE;
}
