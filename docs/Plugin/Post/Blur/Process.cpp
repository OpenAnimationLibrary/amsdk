// NAP  1/12/2005  \Noel120\Plugin\Post\Blur\Process.cpp

#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"
#include "SDK/Misc.h"

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
    //Blur( this, m_prendersettings->m_softness.GetValue() * ((float)GetRealWidth()/WIDTHUNIT)))
    //int BitmapNode::Soften( RenderInfo *rinfo, float radius )

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    if (!inbuffer)
        return false;
    const int width = inbuffer->GetWidth();
    const int height = inbuffer->GetHeight();
    //get property values
    const float radius = m_softness->GetValue() * width / WIDTHUNIT; //((float)rinfo->GetRealWidth()/WIDTHUNIT);
    if (radius == 0.F) {
        output->SetBuffer(inbuffer->MakeCopy());
        return TRUE;
    }

    const int lutwidth = MIN(MIN(width, MAX(2, (int)(radius * 2.F))), height);
    const int halflutwidth = lutwidth / 2;
    const size_t alloc_size = hash_math::sqr(lutwidth + 1) * sizeof(float);
    auto *lut = (float *)AllocExt(alloc_size);//(lutwidth + 1) * (lutwidth + 1) * sizeof(float));
    float sum = 0.F;
    float *lutptr;
    if (radius >= 1.F) {
        lutptr = lut;
        for (int luty = 0; luty <= lutwidth; ++luty) {
            const float b = radius - (luty + 0.5F);
            const float bsqr = hash_math::sqr(b);
            for (int lutx = 0; lutx <= lutwidth; ++lutx, ++lutptr) {
                const float a = radius - (lutx + 0.5F);
                const float asqr = hash_math::sqr(a);
                const float distance = hash_math::sqrt(asqr + bsqr);
                *lutptr = MAX(0.F, (radius - distance) / radius);
                sum += *lutptr;
            }
        }
    } else {
        lut[0] = lut[2] = lut[6] = lut[8] = radius * 0.707F;
        lut[1] = lut[3] = lut[5] = lut[7] = radius;
        lut[4] = 1.F;
        for (int i = 0; i < 9; ++i)
            sum += lut[i];
    }
    lutptr = lut;
    for (int luty = 0; luty <= lutwidth; ++luty) {
        // normalize
        for (int lutx = 0; lutx <= lutwidth; ++lutx, ++lutptr) {
            *lutptr /= sum;
        }
    }

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    RGBAFloat *sourcerows = inbuffer->GetRGBAFloatData();
    RGBAFloat *destrows = outbuffer->GetRGBAFloatData();
    for (int y = 0; y < height; ++y) {
        RGBAFloat totalcolor; //MUST Stay out otherwise initialised with false alpha value 
        const int rowoffset = y * width;
        RGBAFloat *dstpixel = destrows + rowoffset;
        RGBAFloat *srcpixel = sourcerows + rowoffset;
        for (int x = 0; x < width; ++x, ++dstpixel, ++srcpixel) {
            if (srcpixel->m_alpha < 0.F)
                continue;

            totalcolor.Set(0.F);
            float DOFdivisor = 0.F;
            float *lutptr1 = lut;
            for (int luty = 0; luty <= lutwidth; ++luty) {
                int tempy = y + luty - halflutwidth;
                if (tempy < 0)
                    tempy = -tempy;
                if (tempy >= height)
                    tempy = height - (tempy - height) - 1;
                const int temprowoffset = tempy * width;
                for (int lutx = 0; lutx <= lutwidth; ++lutx, ++lutptr1) {
                    int tempx = x + lutx - halflutwidth;
                    if (tempx < 0)
                        tempx = -tempx;
                    if (tempx >= width)
                        tempx = width - (tempx - width) - 1;
                    const RGBAFloat *tempcolorptr = sourcerows + temprowoffset + tempx;
                    RGBAFloat color = *tempcolorptr;
                    const float factor = *lutptr1;
                    if (factor) {
                        if (color.m_alpha > 0.F) {
                            // for DOF softening
                            color *= factor;
                            totalcolor += color;
                            DOFdivisor += factor;
                        }
                    }
                }
            }
            if (DOFdivisor)
                totalcolor /= DOFdivisor;
            *dstpixel = totalcolor;
        }
    }

    FreeExt(lut);

    output->SetBuffer(outbuffer);
    return TRUE;
}
