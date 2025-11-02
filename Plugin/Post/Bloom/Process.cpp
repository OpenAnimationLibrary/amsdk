// MH  6/30/2005  \Mart120\Plugin\Post\Bloom\Process.cpp

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
    const float radius = (float)m_radius->GetValue(),
                strength = m_strength->GetValue(),
                threshold = m_threshold->GetValue(),
                radiussqr = radius * radius;

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *outdata = outbuffer->GetRGBAFloatData();
    RGBAFloat *outptr = outdata;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, ++inptr, ++outptr) {
            float value = MAKELUMINANCE( inptr->m_color.m_red, inptr->m_color.m_green, inptr->m_color.m_blue );
            float factor = value / threshold;
            if (factor > 1)
                factor = 1;
            value /= radiussqr * hash_constants::pi;
            value *= strength * factor;

            *outptr += *inptr;

            for (int i = (int)-radius; i <= radius; ++i) {
                const int isqr = i * i;
                const int newy = y + i;
                int newx;
                if (newy < 0 || newy >= height)
                    continue;
                RGBAFloat *outptr2 = outdata + newy * width;
                for (int j = (int)-radius; j <= radius; ++j) {
                    if ((newx = x + j) < 0 || newx >= width)
                        continue;
                    if (j * j + isqr <= radiussqr) {
                        RGBAFloat *temp = outptr2 + newx;
                        temp->m_color.m_red += value;
                        temp->m_color.m_green += value;
                        temp->m_color.m_blue += value;
                    }
                }
            }
        }
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
