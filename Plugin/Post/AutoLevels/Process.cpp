// NAP  1/26/2005  \Noel120\Plugin\Post\AutoLevels\Process.cpp

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
    const int numpixels = width * height;

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();

    RGBAFloat *sourcepixels = inbuffer->GetRGBAFloatData();
    RGBAFloat *destpixel = outbuffer->GetRGBAFloatData();
    const RGBAFloat *tofar = sourcepixels + numpixels;
    //COMEBACK figure out what the implementation of this would be.
    //photoshop says: By default, this feature clips the white and black pixels by 0.5%--that is, it ignores the first 0.5% of either extreme when identifying the lightest and darkest pixels in the image. This ensures that white and black values are based on representative rather than extreme pixel values.
    //must mean that it loops through filling min max buckets(more like turnstiles) until it the count of pixels in the buckets at each end contain more than .5% then it uses the value of the inside most buckets?  
    //this probably matters more when the source format was origionaly non float
    float redmin = hash_constants::max_float, redmax = -hash_constants::max_float, greenmin = hash_constants::max_float, greenmax = -hash_constants::max_float, bluemin = hash_constants::max_float, bluemax = -hash_constants::max_float;
    RGBAFloat *sourcepixel;
    for (sourcepixel = sourcepixels; sourcepixel < tofar; sourcepixel++) {
        const float blue = sourcepixel->Blue();
        if (blue < bluemin && IsFinite(blue))
            bluemin = blue;
        if (blue > bluemax && IsFinite(blue))
            bluemax = blue;
        const float green = sourcepixel->Green();
        if (green < greenmin && IsFinite(green))
            greenmin = green;
        if (green > greenmax && IsFinite(green))
            greenmax = green;
        const float red = sourcepixel->Red();
        if (red < redmin && IsFinite(red))
            redmin = red;
        if (red > redmax && IsFinite(red))
            redmax = red;
    }
    float redscale = redmax - redmin;
    if (redscale != 0.F && IsFinite(redscale))
        redscale = 1.F / redscale;
    else
        redscale = -0.999F;
    float greenscale = greenmax - greenmin;
    if (greenscale != 0.F && IsFinite(greenscale))
        greenscale = 1.F / greenscale;
    else
        greenscale = -0.999F;
    float bluescale = bluemax - bluemin;
    if (bluescale != 0.F && IsFinite(bluescale))
        bluescale = 1.F / bluescale;
    else
        bluescale = -0.999F;
    if ((redscale >= 0.F && bluescale >= 0.F) || greenscale >= 0.F) {
        //no !_finite scales, take the fast path
        for (sourcepixel = sourcepixels; sourcepixel < tofar; sourcepixel++) {
            destpixel->SetBlue((sourcepixel->Blue() - bluemin) * bluescale);
            destpixel->SetGreen((sourcepixel->Green() - greenmin) * greenscale);
            destpixel->SetRed((sourcepixel->Red() - redmin) * redscale);
            destpixel->SetAlpha(sourcepixel->Alpha());
            destpixel++;
        }
    } else {
        //bad data or something bad happened, do what we can. FEATURE add stringproperty to notify users of an error
        for (sourcepixel = sourcepixels; sourcepixel < tofar; sourcepixel++) {
            if (bluescale >= 0.F)
                destpixel->SetBlue((sourcepixel->Blue() - bluemin) * bluescale);
            else
                destpixel->SetBlue(sourcepixel->Blue());
            if (greenscale >= 0.F)
                destpixel->SetGreen((sourcepixel->Green() - greenmin) * greenscale);
            else
                destpixel->SetGreen(sourcepixel->Green());
            if (redscale >= 0.F)
                destpixel->SetRed((sourcepixel->Red() - redmin) * redscale);
            else
                destpixel->SetRed(sourcepixel->Red());
            destpixel->SetAlpha(sourcepixel->Alpha());
            destpixel++;
        }
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
