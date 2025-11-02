// MH  6/30/2005  \Mart120\Plugin\Post\Dither\Process.cpp

#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    if (i == 0)
        return m_bittype;
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
    const int levels = m_levels->GetValue() - 1;

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();

    auto *ditherdown = (RGBFloat *)AllocExt(sizeof(RGBFloat) * width);

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    RGBAFloat *inptr = inbuffer->GetRGBAFloatData();

    for (int y = 0; y < height; ++y) {
        RGBFloat ditherright(0.F), ditherdownright(0.F), ditherdownleft, mydown;
        for (int x = 0; x < width; ++x, ++outptr, ++inptr) {
            //add earlier contributions from above and last pixels contribution to the right
            outptr->m_color = inptr->m_color + ditherright + ditherdown[x];
            outptr->m_alpha = inptr->m_alpha;
            //calculate change to a level
            RGBFloat change = outptr->m_color * (float)levels;
            change.m_red = (change.m_red - fast_floor(change.m_red)) / levels;
            change.m_green = (change.m_green - fast_floor(change.m_green)) / levels;
            change.m_blue = (change.m_blue - fast_floor(change.m_blue)) / levels;

            //remove the change;
            outptr->m_color -= change;

            //spread the change down and right
            ditherright = 7.0F / 16 * change;
            if (x) {
                //typical
                //this pixel's down plus last's downright
                mydown = 5.0F / 16 * change;
                ditherdown[x] = mydown + ditherdownright;
                //downleft
                ditherdown[x - 1] += ditherdownleft = 3.0F / 16 * change;
                //save leftover to downright so it doesn't mess up next pixel's contribution from above
                ditherdownright = change - mydown - ditherdownleft - ditherright;
            } else {
                //first pixel can't go downleft
                mydown = 8.0F / 16 * change;
                ditherdown[x] = mydown + ditherdownright; //this pixel's down plus last's downright
                ditherdownright = change - mydown - ditherright;
            }
        }
    }
    FreeExt(ditherdown);
    output->SetBuffer(outbuffer);
    return TRUE;
}
