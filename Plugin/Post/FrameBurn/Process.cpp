// MH  6/30/2005  \Mart120\Plugin\Post\FrameBurn\Process.cpp

// ReSharper disable CppCStyleCast
#include "StdAfx.h"
#include "Custom.h"
#include "PostApp.h"
#include "HashFile.h"
#include "SDK/HProject.h"
#include "SDK/Misc.h"
extern CPostApp theApp;

//constexpr float OPACITY = .75f;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_fontscale;
        case 1:
            return m_opacity;
        case 2:
            return m_displayname;
        case 3:
            return m_displayshadow;
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
    //comeback
    /*
    make it have opacity, text, position properties.
    text would have \filename \time etc that would be replaced with these values from the info
    position would be % across and down image
    
    then this plugin would be a combination .pst of with two of these //or add ability for more than one string
    "\filename" .75 opacity, 5%,5%
    and
    "\time" .75 opacity, 95%,5%
    
    could add font control etc too.
    */
    //   if (!postinfo)
    //      return FALSE;
    //get property values
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeCopy();
    String text = inputs->GetFileName().GetNameOnly();
    const String suffix = text.GetSuffixOnly();

    //COMEBACK NAP HIOReg *ioreg = FindImageHIORegFromSuffix();
    //if (ioreg->CanDoMultiFrames())
    if (suffix != "avi" && suffix != "mov")
        text = text.GetWithoutDigits();

    const String timestring = time.ToString(GetHProject()->GetFPS(), (TimeUnit)GetTimeMode());

    if (m_displayname->GetValue())
        BurnText(outbuffer, text, TRUE);
    BurnText(outbuffer, timestring, FALSE);

    //uncomment to Build FontData.cpp on the PC 
    //SaveFontFile("E:\\FontData.cpp");
    //
    output->SetBuffer(outbuffer);

    return TRUE;
}

BOOL CustomPostPlugin::BurnText(HRGBAFloatBuffer *inbuffer, const String &text, const BOOL leftside) const {
    //keep save fontfile up to date with changes here
    if (text.IsEmpty())
        return TRUE;
    //get bitmap info
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();


    CDC memdc;
//    if (!memdc.CreateCompatibleDC(nullptr))
    if (!memdc.Attach(::CreateCompatibleDC(nullptr)))
        return FALSE;

    CFont *font = CFont::FromHandle((HFONT)GetStockObject(ANSI_VAR_FONT));
    if (font == nullptr)
        font = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));

    CFont sizedfont;
    float fontscale = m_fontscale->GetValue();
    if (fontscale == 0.F)
        fontscale = 1.F;
    if (font && fontscale != 1.F) {
        LOGFONT logfont;
        if (font->GetLogFont(&logfont)) {
            //int devcaps = memdc.GetDeviceCaps(LOGPIXELSY);
            //int pointsize = 16;
            //logfont.lfHeight = -MulDiv(pointsize, devcaps, 72);
            logfont.lfHeight = (long)(logfont.lfHeight * fontscale);
            logfont.lfWidth = 0;
            if (sizedfont.CreateFontIndirect(&logfont))
                font = &sizedfont;
        }
    }

    CFont *oldfont = memdc.SelectObject(font);

    CRect rect(0, 0, 0, 0);
    memdc.DrawText(text.Get(), &rect, DT_CALCRECT | DT_SINGLELINE);

    const int rectheight = rect.Height();
    const int rectwidth = width;
    rect.right = width;

    if (rectheight > height) {
        memdc.SelectObject(oldfont);
        return FALSE;
    }

    CDC *dc = CDC::FromHandle(GetDC(GetMainApplicationWnd()));
    CBitmap cbitmap;

    if (!cbitmap.CreateCompatibleBitmap(dc, rectwidth, rectheight + 4)) {
        ReleaseDC(GetMainApplicationWnd(), dc->m_hDC);
        memdc.SelectObject(oldfont);
        return FALSE;
    }

    ReleaseDC(GetMainApplicationWnd(), dc->m_hDC);

    CBitmap *oldbitmap = memdc.SelectObject(&cbitmap);
    auto *oldbrush = (CBrush *)memdc.SelectStockObject(GRAY_BRUSH);
    auto *oldpen = (CPen *)memdc.SelectStockObject(NULL_PEN);

    const int right = rectwidth - 4;

    memdc.FillSolidRect(CRect(0, 0, rectwidth, rectheight + 4), RGB(255, 0, 0));
    if (m_displayshadow->GetValue()) {
        memdc.SetBkMode(TRANSPARENT);
        memdc.SetTextColor(RGB(0, 0, 0));
        memdc.DrawText(text.Get(), CRect(2, 3, right - 1, height + 3), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(1, 2, right - 2, height + 2), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(2, 1, right - 1, height + 1), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(3, 2, right + 0, height + 2), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(3, 4, right + 0, height + 4), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(4, 4, right + 1, height + 4), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(4, 3, right + 1, height + 3), leftside ? DT_LEFT : DT_RIGHT);
        memdc.DrawText(text.Get(), CRect(3, 3, right + 0, height + 3), leftside ? DT_LEFT : DT_RIGHT);
    }
    memdc.SetTextColor(RGB(255, 255, 255));
    memdc.DrawText(text.Get(), CRect(2, 2, right - 1, height + 2), leftside ? DT_LEFT : DT_RIGHT);

    const float OPACITY = m_opacity->GetValue();
    ColorBuf textcolor;
    for (int y = 0; y < rectheight + 4; ++y) {
        RGBAFloat *dstptr = inbuffer->GetRGBAFloatData() + y * width;
        for (int x = 0; x < rectwidth; ++x, ++dstptr) {
            textcolor.SetColor(memdc.GetPixel(x, y));
//            textcolor.SetColor((UINT)memdc.GetPixel(x, y));
            if ((textcolor.Red() == 0 && textcolor.Green() == 0 && textcolor.Blue() == 0) || (textcolor.Red() == 255 && textcolor.Green() == 255 && textcolor.Blue() == 255)) {
                const RGBFloat srccolor = dstptr->m_color;
                const float alpha = dstptr->m_alpha;
                dstptr->m_color = RGBFloat(OPACITY * (float)textcolor.Red() / 255.F + (1.F - OPACITY) * srccolor.m_red,
                                           OPACITY * (float)textcolor.Green() / 255.F + (1.F - OPACITY) * srccolor.m_green,
                                           OPACITY * (float)textcolor.Blue() / 255.F + (1.F - OPACITY) * srccolor.m_blue);
                dstptr->m_alpha = alpha + OPACITY * (255.F - alpha);
            }
        }
    }
    memdc.SelectObject(oldpen);
    memdc.SelectObject(oldbrush);
    memdc.SelectObject(oldfont);
    memdc.SelectObject(oldbitmap);
    return TRUE;
}
