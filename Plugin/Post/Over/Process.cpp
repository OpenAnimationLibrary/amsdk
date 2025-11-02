// NAP  1/20/2005  \Noel120\Plugin\Post\Over\Process.cpp

#include "StdAfx.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_percent1;
        case 1:
            return m_percent2;
        default:
            return nullptr;
    }
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 2;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    /*
    designed for Compositing two buffers buffer2 over buffer1
    for each x,y < min input width,height
    sets output color to buffer1->m_color - buffer1->m_color * buffer2->m_alpha + buffer2->m_color
    sets alpha to buffer1->m_alpha - buffer1->m_alpha * buffer2->m_alpha + buffer2->m_alpha
    */

    //get property values
    /*
       float percent1 = m_percent1->GetValue();
       float percent2 = m_percent2->GetValue();
       if (percent1 == 0.F && percent2 == 0.F)
          return TRUE;
    */
    //get bitmap info
    HBufferShortcut *input = inputs;
    HRGBAFloatBuffer *inbuffer1 = input->GetRGBAFloatBuffer(time);
    if (!inbuffer1)
        return FALSE;
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

    const RGBAFloat *rows1 = inbuffer1->GetRGBAFloatData();
    const RGBAFloat *rows2 = inbuffer2->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    for (int y = 0; y < height; ++y) {
        const RGBAFloat *inptr1 = rows1;
        const RGBAFloat *inptr2 = rows2;
        for (int x = 0; x < width; ++x) {
            *outptr = *inptr1 - *inptr1 * inptr2->m_alpha + *inptr2;
            ++inptr1;
            ++inptr2;
            ++outptr;
        }
        rows1 += width1;
        rows2 += width2;
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
