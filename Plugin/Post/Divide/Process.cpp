// NAP  12/28/2004  \Noel120\Plugin\Post\Add\Process.cpp

#include "StdAfx.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    if (i == 0) {
        return m_percent;
    }
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
    sets output color to buffer1->m_color) / (percent * buffer2->m_color)
    any color components of input2 that are zero are changed to 1e-8f
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
        output->SetBuffer(inbuffer1->MakeCopy());
        return TRUE;
    }
    const int width1 = inbuffer1->GetWidth(), height1 = inbuffer1->GetHeight();
    input = input->GetNextBufferShortcut();
    if (!input || width1 < 1 || height1 < 1)
        return FALSE;
    if (percent == 0.F) {
        output->SetBuffer(inbuffer1->MakeCopy());
        return TRUE;
    }
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

    //    RGBFloat newcolor;
    const RGBAFloat *rows1 = inbuffer1->GetRGBAFloatData();
    const RGBAFloat *rows2 = inbuffer2->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    for (int y = 0; y < height; ++y) {
        const RGBAFloat *inptr1 = rows1;
        const RGBAFloat *inptr2 = rows2;
        for (int x = 0; x < width; ++x) {
            float abscomponent = hash_math::abs(inptr2->m_color.m_red);
            if (abscomponent >= 0.F && abscomponent < HALF_NRM_MIN)
                outptr->m_color.m_red = inptr1->m_color.m_red / (percent * HALF_NRM_MIN);
            else
                outptr->m_color.m_red = inptr1->m_color.m_red / (percent * inptr2->m_color.m_red);

            abscomponent = hash_math::abs(inptr2->m_color.m_green);
            if (abscomponent >= 0.F && abscomponent < HALF_NRM_MIN)
                outptr->m_color.m_green = inptr1->m_color.m_green / (percent * HALF_NRM_MIN);
            else
                outptr->m_color.m_green = inptr1->m_color.m_green / (percent * inptr2->m_color.m_green);

            abscomponent = hash_math::abs(inptr2->m_color.m_blue);
            if (abscomponent >= 0.F && abscomponent < HALF_NRM_MIN)
                outptr->m_color.m_blue = inptr1->m_color.m_blue / (percent * HALF_NRM_MIN);
            else
                outptr->m_color.m_blue = inptr1->m_color.m_blue / (percent * inptr2->m_color.m_blue);

            outptr->m_alpha = MAX(inptr1->m_alpha, inptr2->m_alpha);
            //outptr->m_alpha = (inptr1->m_alpha * abspercent1 + inptr2->m_alpha * abspercent2)/abspercents;
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
