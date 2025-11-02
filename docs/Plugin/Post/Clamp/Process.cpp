// NAP  1/26/2005  \Noel120\Plugin\Post\Clamp\Process.cpp

#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    const int numcomponents = width * height * 4;

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();

    const auto *sourcecomponent = (float *)inbuffer->GetRGBAFloatData();
    auto *destcomponent = (float *)outbuffer->GetRGBAFloatData();
    /*
       yves suggested trying a soft clamp with the Sigmoid function at http://en.wikipedia.org/wiki/Logistic_function.
       It looks like you would make mincomponent to maxcompoent fit on -6 to 6 and then run it.
    */
    const float *tofar = destcomponent + numcomponents;
    for (; destcomponent < tofar; destcomponent++) {
        if (*sourcecomponent >= 1.F)
            *destcomponent = 1.F;
        else if (*sourcecomponent <= 0.F)
            *destcomponent = 0.F;
        else
            *destcomponent = *sourcecomponent;
        sourcecomponent++;
    }

    output->SetBuffer(outbuffer);
    return TRUE;
}
