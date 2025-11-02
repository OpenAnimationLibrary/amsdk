// YP  10/02/2005  \Yves120\Plugin\Post\Exposure\Process.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"
#include "Matrix34.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_hue;
        case 1:
            return m_saturation;
        case 2:
            return m_exposure;
        default:
            return nullptr;
    }
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    // Exposure is 
    const float hue = m_hue->GetValue();
    const float saturation = m_saturation->GetValue();
    const float exposure = hash_math::pow(2.F, m_exposure->GetValue());

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth();
    const int height = inbuffer->GetHeight();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    if (!outbuffer)
        return FALSE;

    const RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    if (!outptr) {
        delete outbuffer;
        return FALSE;
    }
    // Following code is after Paul Aeberli, "Matrix Operations for Image Processing", Grafica Obscura, 1993,
    Matrix34 xform;
    xform.SetIdentity();
    if (hue != 0.F) {
        xform *= Matrix34(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 0.7071068F, 0.7071068F, 0.F), Vector4(0.F, -0.7071068F, 0.7071068F, 0.F));
        xform *= Matrix34(Vector4(0.8164966F, 0.F, 0.5773503F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(-0.5773503F, 0.F, 0.8164966F, 0.F));
        Vector lum(0.2125F, 0.7154F, 0.0721F);
        lum *= xform;
        const float zsx = lum.x / lum.z;
        const float zsy = lum.y / lum.z;
        xform *= Matrix34(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(zsx, zsy, 1.F, 0.F));
        xform *= ZRotate(hue);
        xform *= Matrix34(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(-zsx, -zsy, 1.F, 0.F));
        xform *= Matrix34(Vector4(0.8164966F, 0.F, -0.5773503F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(0.5773503F, 0.F, 0.8164966F, 0.F));
        xform *= Matrix34(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 0.7071068F, -0.7071068F, 0.F), Vector4(0.F, 0.7071068F, 0.7071068F, 0.F));
    }
    if (saturation != 1.F) {
        const float rwgt = (1.F - saturation) * 0.2125F;
        const float gwgt = (1.F - saturation) * 0.7154F;
        const float bwgt = (1.F - saturation) * 0.0721F;
        const Matrix34 sat(Vector4(rwgt + saturation, gwgt, bwgt, 0.F), Vector4(rwgt, gwgt + saturation, bwgt, 0.F), Vector4(rwgt, gwgt, bwgt + saturation, 0.F));
        xform *= sat;
    }
    if (exposure != 1.F) {
        const Matrix34 scale = Scalef(exposure, exposure, exposure);
        xform *= scale;
    }
    const int numpixels = height * width;
    // ReSharper disable once CppDeclaratorNeverUsed
    const int omp_mode = GetOpenMPMode();
#pragma omp parallel for if(omp_mode) num_threads(omp_mode)
    for (int y = 0; y < numpixels; ++y) {
        Vector vcolor(inptr[y].m_color.m_red, inptr[y].m_color.m_green, inptr[y].m_color.m_blue);
        vcolor *= xform;
        outptr[y].m_color.Set(vcolor.x, vcolor.y, vcolor.z);
        outptr[y].m_alpha = inptr[y].m_alpha;
    }
    output->SetBuffer(outbuffer);
    return TRUE;
}
