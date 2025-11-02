// MH  6/30/2005  \Mart120\Plugin\Post\MinMedMax\Process.cpp

#include "StdAfx.h"

//#include "Allocate.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_style;
        case 1:
            return m_radius;
        case 2:
            return m_isround;
        default:
            return nullptr;
    }
}

class ColorList final {
    RGBFloat *m_colornodes;
    int m_maxlength;
    int m_length;
public:
    explicit ColorList(const int maxlength) {
        m_length = 0;
        m_maxlength = maxlength;
        m_colornodes = (RGBFloat *)AllocExt(m_maxlength * sizeof(RGBFloat));
    }

    ~ColorList() {
        FreeExt(m_colornodes);
    }

    ColorList(const ColorList&) = delete;
    ColorList &operator= (const ColorList&) = delete; 
    ColorList(ColorList &&) = delete; 
    ColorList &operator=(ColorList &&) = delete; 

    void AddColor(const RGBFloat color) {
        if (m_length == m_maxlength)
            return;
        m_colornodes[m_length] = color;
        m_length++;
    }

    void Reset() {
        m_length = 0;
    }

    [[nodiscard]] float GetSortedColorAt(const float target, const int channel) const
    //target 0.0, 0.5, 1.0 for minimum, median, maximum
    {
        int i = 0, left = 0, right = m_length - 1;
        const int targeti = (int)(right * target);

        while (TRUE) {
            int guessi = targeti;
            const float value = m_colornodes[guessi][channel];
            const RGBFloat tempcol = m_colornodes[guessi];

            if (targeti != left) {
                for (i = left; i <= right && left < right; ++i) {
                    if (i == guessi)
                        break;

                    if (m_colornodes[i][channel] <= value)
                        ++left;
                    else {
                        m_colornodes[guessi] = m_colornodes[i];
                        guessi = i;
                        break;
                    }
                }
            } else if (left == right)
                i = right; //to fix 0,0 radius 1 max
            while (left < right) {
                for (i = right; i >= left && left < right; --i) {
                    if (i == guessi)
                        continue;
                    if (m_colornodes[i][channel] >= value)
                        --right;
                    else {
                        m_colornodes[guessi] = m_colornodes[i];
                        guessi = i;
                        break;
                    }
                }
                for (i = left; i <= right && left < right; ++i) {
                    if (i == guessi)
                        continue;
                    if (m_colornodes[i][channel] <= value)
                        ++left;
                    else {
                        m_colornodes[guessi] = m_colornodes[i];
                        guessi = i;
                        break;
                    }
                }
            }

            if (i == targeti)
                return tempcol[channel];
            if (i < targeti) {
                left = i + 1;
                right = m_length - 1;
            } else {
                left = 0;
                right = i - 1;
            }
            m_colornodes[i] = tempcol;
        }
    }
};

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //get property values
    const int radius = m_radius->GetValue();
    if (radius <= 0)
        return TRUE;
    const float pos = m_pos->GetValue();
    const BOOL round = m_isround->GetValue() && radius > 1; //otherwise 1 radius round misses adjacent corner pixels

    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();

    const int diameter = 2 * radius + 1;
    const int dxd = diameter * diameter;

    BOOL *radiustable = nullptr;
    if (round) {
        radiustable = (BOOL *)AllocExt(dxd * sizeof(BOOL));
        const int center = radius;
        const int radiussqrd = radius * radius;
        for (int y = 0; y < diameter; ++y) {
            int yradiussqrd = y - center;
            const int dy = diameter * y;
            yradiussqrd *= yradiussqrd;
            for (int x = 0; x < diameter; ++x) {
                if ((x - center) * (x - center) + yradiussqrd <= radiussqrd)
                    radiustable[dy + x] = TRUE;
                else
                    radiustable[dy + x] = FALSE;
            }
        }
    }
    ColorList list(dxd);
    RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *inrow = inptr;
    RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, ++outptr, ++inptr) {
            //add suroundings to list
            list.Reset();
            //            int radiustablepos = 0;
            const int maxsy = MIN(y + radius, height - 1);
            const int minsx = MAX(x - radius, 0);
            const int maxsx = MIN(x + radius, width - 1);
            const int radiusminusx = radius - x;
            const int radiusminusy = radius - y;
            RGBAFloat *instart = inrow + minsx;
            for (int sy = MAX(y - radius, 0); sy <= maxsy; ++sy) {
                int dsy = 0;
                if (round)
                    dsy = diameter * (sy + radiusminusy);
                RGBAFloat *in = instart;
                for (int sx = minsx; sx <= maxsx; ++sx, ++in) {
                    if (round) {
                        if (radiustable[dsy + sx + radiusminusx])
                            list.AddColor(in->m_color);
                    } else
                        list.AddColor(in->m_color);
                }
                instart += width;
            }
            outptr->m_color.m_red = list.GetSortedColorAt(pos, 0);
            outptr->m_color.m_green = list.GetSortedColorAt(pos, 1);
            outptr->m_color.m_blue = list.GetSortedColorAt(pos, 2);
            outptr->m_alpha = inptr->m_alpha;
        }
        if (y - radius >= 0)
            inrow += width;
    }
    output->SetBuffer(outbuffer);

    if (round)
        FreeExt(radiustable);

    return TRUE;
}
