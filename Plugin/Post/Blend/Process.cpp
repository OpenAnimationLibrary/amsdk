// NAP  12/28/2004  \Noel120\Plugin\Post\Blend\Process.cpp

#include "StdAfx.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_style;
        case 1:
            return m_percent1;
        case 2:
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
    Blend based on style see switch for their comments
    */

    //get property values
    const auto style = (BStyle)m_style->GetValue();

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

//    RGBFloat newcolor;
    RGBAFloat *rows1 = inbuffer1->GetRGBAFloatData();
    RGBAFloat *rows2 = inbuffer2->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    RGBAFloat *inptr1, *inptr2;

    switch (style) {
        case SCREEN:
        {
            /*
            screen = 1 - (1-base * 1-blend)
            */
            for (int y = 0; y < height; ++y) {
                inptr1 = rows1;
                inptr2 = rows2;
                for (int x = 0; x < width; ++x) {
                    outptr->m_color.m_red = 1.F - (1.F - inptr1->m_color.m_red) * (1.F - inptr2->m_color.m_red);
                    outptr->m_color.m_green = 1.F - (1.F - inptr1->m_color.m_green) * (1.F - inptr2->m_color.m_green);
                    outptr->m_color.m_blue = 1.F - (1.F - inptr1->m_color.m_blue) * (1.F - inptr2->m_color.m_blue);
                    outptr->m_alpha = MAX(inptr1->m_alpha, inptr2->m_alpha);
                    //outptr->m_alpha = (inptr1->m_alpha * abspercent1 + inptr2->m_alpha * abspercent2)/abspercents;
                    ++inptr1;
                    ++inptr2;
                    ++outptr;
                }
                rows1 += width1;
                rows2 += width2;
            }
            break;
        }
        case OVERLAY:
        {
            /*
               if (Base > ½) R = 1 - (1-2×(Base-½)) × (1-Blend) 
               if (Base <= ½) R = (2×Base) × Blend 
            */
            for (int y = 0; y < height; ++y) {
                inptr1 = rows1;
                inptr2 = rows2;
                for (int x = 0; x < width; ++x) {
                    if (inptr1->m_color.m_red < 0.5F)
                        outptr->m_color.m_red = 2.F * inptr1->m_color.m_red * inptr2->m_color.m_red;
                    else
                        outptr->m_color.m_red = 1.F - (1.F - 2.F * (inptr1->m_color.m_red - 0.5F)) * (1.F - inptr2->m_color.m_red);
                    //for testing do greyscale need to walk float instead of RGBAFloat, and just handle A different
                    outptr->m_color.m_green = outptr->m_color.m_blue = outptr->m_color.m_red;
                    outptr->m_alpha = MAX(inptr1->m_alpha, inptr2->m_alpha);
                    //outptr->m_alpha = (inptr1->m_alpha * abspercent1 + inptr2->m_alpha * abspercent2)/abspercents;
                    ++inptr1;
                    ++inptr2;
                    ++outptr;
                }
                rows1 += width1;
                rows2 += width2;
            }
            break;
        }
        default: 
        break;
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
