// MH  6/30/2005  \Mart120\Plugin\Post\FilmGrain\Process.cpp

#include "StdAfx.h"
#include "Allocate.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"
#include "Rnd.h"

#include "RGBHalf.inl"

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

namespace {
    void AddGrain(const RGBAFloat *in, RGBAFloat *out, const float magnitude, const float blur) {
        const float value = 1 - MAKELUMINANCE(in->m_color.m_red, in->m_color.m_green, in->m_color.m_blue);

        const float filmgrain = value * magnitude * blur;

        out->m_color.m_red = in->m_color.m_red + filmgrain * 0.67F;
        out->m_color.m_green = in->m_color.m_green + filmgrain * 0.2F;
        out->m_color.m_blue = in->m_color.m_blue + filmgrain * 0.13F;
        out->m_alpha = in->m_alpha;
        //if (out.m_color.m_red > 1.F) //to clip or not to clip that is the question
        //   out.m_color.m_red = 1.F;
        //if (out.m_color.m_red < 0.F)
        //   out.m_color.m_red = 0.F;
    }
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //get property values
    const float magnitude = m_amount->GetValue();
    const float size = m_size->GetValue();

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();

    if (width < 2 || height < 2)
        return FALSE;

    float *array1 = (float *)AllocExt(width * sizeof(float)), *ptr1 = array1, *array2 = (float *)AllocExt(width * sizeof(float)), *ptr2 = array2;
    int x;
    for (x = 0; x < width; ++x) {
        ptr1[x] = Rnd() - 0.5F;
        ptr2[x] = Rnd() - 0.5F;
    }

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();

    float blur = (ptr1[0] + size * (ptr1[1] + ptr2[0]) + size / 2 * ptr2[x + 1]) / (1 + 5 / 2.F * size);
    AddGrain(inptr++, outptr++, magnitude, blur);
    for (x = 1; x < width - 1; ++x) {
        blur = (ptr1[x] + size * (ptr1[x - 1] + ptr1[x + 1] + ptr2[x]) + size / 2 * (ptr2[x - 1] + ptr2[x + 1])) / (1 + 4 * size);
        AddGrain(inptr++, outptr++, magnitude, blur);
    }
    blur = (ptr1[width - 1] + size * (ptr1[width - 2] + ptr2[width - 1]) + size / 2 * ptr2[width - 2]) / (1 + 5 / 2.F * size);
    AddGrain(inptr++, outptr++, magnitude, blur);

    for (int y = 1; y < height - 1; ++y) {
        //        int ywidth = y * width;
        float bl = Rnd() - 0.5F;
        float b = Rnd() - 0.5F;
        float br = Rnd() - 0.5F;
        blur = (ptr2[0] + size * (ptr1[0] + ptr2[1] + b) + size / 2 * (ptr1[1] + br)) / (1 + 4 * size);
        AddGrain(inptr++, outptr++, magnitude, blur);
        for (x = 1; x < width - 1; ++x) {
            blur = (ptr2[x] + size * (ptr1[x] + ptr2[x - 1] + ptr2[x + 1] + b) + size / 2 * (ptr1[x - 1] + ptr1[x + 1] + bl + br)) / (1 + 6 * size);
            AddGrain(inptr++, outptr++, magnitude, blur);
            ptr2[x - 1] = bl;
            bl = b;
            b = br;
            br = Rnd() - 0.5F;
        }
        blur = (ptr2[x] + size * (ptr1[x] + ptr2[x - 1] + b) + size / 2 * (ptr1[x - 1] + b)) / (1 + 4 * size);
        AddGrain(inptr++, outptr++, magnitude, blur);
        ptr2[x - 1] = b;
        ptr2[x] = br;

        float *temp = ptr1;
        ptr1 = ptr2;
        ptr2 = temp;
    }
    //NOTICE there is a difference here between v12.0 and v11.1. v11.1 did y=0, but I think it should have been y=width-1
    blur = (ptr1[0] + size * (ptr1[1] + ptr2[0]) + size / 2.F * ptr2[x + 1]) / (1.F + 5.F / 2.F * size);
    AddGrain(inptr++, outptr++, magnitude, blur);
    for (x = 1; x < width - 1; ++x) {
        blur = (ptr1[x] + size * (ptr1[x - 1] + ptr1[x + 1] + ptr2[x]) + size / 2.F * (ptr2[x - 1] + ptr2[x + 1])) / (1.F + 4.F * size);
        AddGrain(inptr++, outptr++, magnitude, blur);
    }
    blur = (ptr1[width - 1] + size * (ptr1[width - 2] + ptr2[width - 1]) + size / 2.F * ptr2[width - 2]) / (1.F + 5.F / 2.F * size);
    AddGrain(inptr++, outptr++, magnitude, blur);

    FreeExt(array1);
    FreeExt(array2);
    output->SetBuffer(outbuffer);

    return TRUE;
}
