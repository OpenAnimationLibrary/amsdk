// Yves  10/11/2006  \Plugin\Post\Merge\Process.cpp

#include "StdAfx.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_mergetype;
        case 1:
            return m_percent;
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
    //get property values
    const float percent = m_percent->GetValue();
    m_merge = m_mergetype->GetValue();

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

    const RGBAFloat *rows1 = inbuffer1->GetRGBAFloatData();
    const RGBAFloat *rows2 = inbuffer2->GetRGBAFloatData();
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    for (int y = 0; y < height; ++y) {
        const RGBAFloat *inptr1 = rows1;
        const RGBAFloat *inptr2 = rows2;
        for (int x = 0; x < width; ++x) {
            const float alpha = inptr2->m_alpha * percent;
            outptr->m_color.m_red = Blend(inptr1->m_color.m_red, inptr2->m_color.m_red, alpha);
            outptr->m_color.m_green = Blend(inptr1->m_color.m_green, inptr2->m_color.m_green, alpha);
            outptr->m_color.m_blue = Blend(inptr1->m_color.m_blue, inptr2->m_color.m_blue, alpha);
            outptr->m_color.ClampBounds();
            outptr->m_alpha = inptr1->m_alpha;
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

#define SD(a) ((a) != 0.F ? (a) : 1.F)

float CustomPostPlugin::Blend(const float &a, const float &b, const float alpha) const {
    switch (m_merge) {
        case ID_ADD:
            return (1.F - alpha) * a + alpha * (a + b);
        case ID_SUBTRACT:
            return (1.F - alpha) * a + alpha * (a + b - 1.F);
        case ID_MULTIPLY:
            return (1.F - alpha) * a + alpha * (a * b);
        case ID_DIVIDE:
            return (1.F - alpha) * a + alpha * (a / SD(b));
        case ID_SCREEN:
            return (1.F - alpha) * a + alpha * (1.F - (1.F - a) * (1.F - b));
        case ID_DARKEN:
            return (1.F - alpha) * a + alpha * (a < b ? a : b);
        case ID_LIGHTEN:
            return (1.F - alpha) * a + alpha * (a > b ? a : b);
        case ID_DIFFERENCE:
            return (1.F - alpha) * a + alpha * hash_math::abs(a - b);
        case ID_NEGATION:
            return (1.F - alpha) * a + alpha * (1.F - hash_math::abs(1.F - a - b));
        case ID_EXCLUSION:
            return (1.F - alpha) * a + alpha * (a + b - 2.F * a * b);
        case ID_OVERLAY:
            return (1.F - alpha) * a + alpha * (a < 0.5F ? 2.F * a * b : 1.F - 2.F * (1.F - a) * (1.F - b));
        case ID_HARDLIGHT:
            return (1.F - alpha) * a + alpha * (b < 0.5F ? 2.F * a * b : 1.F - 2.F * (1.F - a) * (1.F - b));
        case ID_SOFTLIGHT:
            return (1.F - alpha) * a + alpha * (2.F * a * b + a * a - 2.F * a * a * b);
        case ID_DODGE:
            return (1.F - alpha) * a + alpha * (a / SD(1.F - b));
        case ID_SOFTDODGE:
            return (1.F - alpha) * a + alpha * (a + b < 1.F ? 0.5F * a / SD(1.F - b) : 1.F - 0.5F * (1.F - b) / SD(a));
        case ID_INVDODGE:
            return (1.F - alpha) * a + alpha * (b / SD(1.F - a));
        case ID_BURN:
            return (1.F - alpha) * a + alpha * (1.F - (1.F - a) / SD(b));
        case ID_SOFTBURN:
            return (1.F - alpha) * a + alpha * (a + b < 1.F ? 0.5F * b / SD(1.F - a) : 1.F - 0.5F * (1.F - a) / SD(b));
        case ID_INVBURN:
            return (1.F - alpha) * a + alpha * (1.F - (1.F - b) / SD(a));
        case ID_REFLECT:
            return (1.F - alpha) * a + alpha * (a * a / SD(1.F - b));
        case ID_GLOW:
            return (1.F - alpha) * a + alpha * (b * b / SD(1.F - a));
        case ID_FREEZE:
            return (1.F - alpha) * a + alpha * (1.F - (1.F - a) * (1.F - a) / SD(b));
        case ID_HEAT:
            return (1.F - alpha) * a + alpha * (1.F - (1.F - b) * (1.F - b) / SD(a));
        case ID_STAMP:
            return (1.F - alpha) * a + alpha * (a + 2.F * b - 1.F);
    }
    ASSERT(false && "Unrecognized Blend Style");
    return -1.F;
}
