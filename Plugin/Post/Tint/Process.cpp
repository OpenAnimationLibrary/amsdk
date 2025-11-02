// Dan  7/21/2004  \DanLP115\Plugin\Post\Tint\Process.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "RGBHalf.inl"
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
    const float percent = m_percent->GetValue();
    if (percent == 0.F)
        return TRUE;
    const BOOL israinbow = m_style->GetValue() == STYLE_RAINBOW;

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();

    const float oneminuspercent = 1.F - percent;
    float luminance;
    RGBFloat newcolor;
    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    const int count = width * height;
    // ReSharper disable once CppDeclaratorNeverUsed
    const int omp_mode = GetOpenMPMode();
    if (israinbow) {
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
        for (int p = 0; p < count; ++p) {
            luminance = 2.F * MAKELUMINANCE(inptr[p].m_color.m_red, inptr[p].m_color.m_green, inptr[p].m_color.m_blue);
            //luminance is doubled for speed as it is only needed as such
            if (luminance <= 1.F) {
                newcolor.SetBlue(MAX(0.F, 1.F - luminance));
                newcolor.SetGreen(MIN(1.F, luminance));
                newcolor.SetRed(0.F);
            } else {
                newcolor.SetBlue(0.F);
                newcolor.SetGreen(MIN(1.F, 1.F - (luminance - 1.F)));
                newcolor.SetRed(MIN(1.F, luminance - 1.F));
            }
            outptr[p].m_color = newcolor * percent + inptr[p].m_color * oneminuspercent;
            outptr[p].m_alpha = inptr[p].m_alpha;
        }
    } else {
        const RGBFloat lightcolor = m_lightcolor->GetNormalizedRGBFloat();
        const RGBFloat darkcolor = m_darkcolor->GetNormalizedRGBFloat();
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
        for (int p = 0; p < count; ++p) {
            luminance = MAKELUMINANCE(inptr[p].m_color.m_red, inptr[p].m_color.m_green, inptr[p].m_color.m_blue);
            newcolor = lightcolor * luminance;
            newcolor += darkcolor * (1.F - luminance);
            outptr[p].m_color = newcolor * percent + inptr[p].m_color * oneminuspercent;
            outptr[p].m_alpha = inptr[p].m_alpha;
        }
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
