// Yves Poissant  2004-01-26  \My Plugins\Shaders\Skin\EvaluateSkin.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_Falloff;
        case 1:
            return m_Roughness;
        case 2:
            return m_ShiftStart;
        case 3:
            return m_ShiftEnd;
        case 4:
            return m_Saturation;
        case 5:
            return m_HueShift;
        case 6:
            return m_BloodColor;
        case 7:
            return m_HueStrength;
        default:
            return nullptr;
    }
}

const char *CustomShader::GetShaderDiffuseFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

const char *CustomShader::GetShaderSpecularFilters() {
    return nullptr;
}

float CustomShader::OrenNayar(HShading *shading) const {
    HTexInfo *htexinfo = shading->GetTexInfo();
    const Vector &N = *htexinfo->GetN();
    const Vector &L = *shading->GetL();
    const Vector V = htexinfo->GetD();
    float l = shading->GetLDot();
    if (l > 1.F) {
        l = 1.F;
    }
    if (l < -1.F) {
        l = -1.F;
    }
    float v = shading->GetEDot();
    if (v > 1.F) {
        v = 1.F;
    }
    if (v < -1.F) {
        v = -1.F;
    }

    const Vector PhiEye = N ^ V;
    const Vector PhiLight = N ^ L;

    float SigmaSquare = m_Roughness->GetValue();
    SigmaSquare *= SigmaSquare;
    const float A = 1.F - 0.5f * SigmaSquare / (SigmaSquare + 0.33f);
    const float B = 0.45f * SigmaSquare / (SigmaSquare + 0.09f);
    const float ThetaEye = hash_math::cos(v);
    const float ThetaLight = hash_math::cos(l);
    const float Alpha = MAX(ThetaEye, ThetaLight);
    const float Beta = MIN(ThetaEye, ThetaLight);

    if (float temp; (temp = PhiEye.Dot(PhiLight)) > 0.F)
        return l * (A + B * temp * hash_math::sin(Alpha) * hash_math::tan(Beta));
    return l * A;
}

void CustomShader::GetDiffuse(HShading *shading) {
    RGBFloat dcol = shading->GetDCol();
    const RGBFloat Skin = ToHSV(&dcol);
    if (Skin.Green() == 0.F)
        return; // Skin color doesn't have a hue (no saturation)
    const double theta1 = m_ShiftStart->GetValue();
    const double theta2 = m_ShiftEnd->GetValue();
    if (theta1 == theta2)
        return;
    double sine = shading->GetLDot();
    sine = hash_math::sqrt(1.0 - sine * sine);

    // Compute Hue shift
    RGBFloat Blood = m_BloodColor->GetNormalizedRGBFloat();
    Blood = ToHSV(&Blood);
    double fn = (sine - theta1 - m_HueShift->GetValue()) / (theta2 - theta1);
    fn = 1.0 / (1.0 + hash_math::exp((fn - 0.5) * -9.0));
    float hue = Skin.Red();
    float delta = Blood.Red() - hue;
    if (delta > 0.5F)
        delta -= 1.F;
    else if (delta < -0.5F)
        delta += 1.F;
    hue += (float)(delta * fn * m_HueStrength->GetValue());
    if (hue < 0.F)
        hue += 1.F;
    else if (hue > 1.F)
        hue -= 1.F;
    // Compute Saturation shift
    fn = (sine - theta1) / (theta2 - theta1);
    fn = 1.0 / (1.0 + hash_math::exp((fn - 0.5) * -9.0));
    float saturation = Skin.Green();
    saturation += (float)(fn * m_Saturation->GetValue() * (1.0 - saturation));
    // Compute Value (falloff)
    //	double fn = pow ( sine * sine * sine, falloff );
    //	Skin.blue *= (float) sqrt ( 1.0 - ( fn * fn ) ) ;

    const float value = Skin.Blue() * OrenNayar(shading);
    const RGBFloat temp1(hue, saturation, value);
    dcol = ToRGB(&temp1);
    //	dcol = ToRGB( &RGBFloat( hue, saturation, value ) );//Taking adress of temporary
    shading->SetDCol(dcol);
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}

RGBFloat CustomShader::ToHSV(const RGBFloat *RGBColor) {
    const double r = RGBColor->Red();
    const double g = RGBColor->Green();
    const double b = RGBColor->Blue();
    const double min = r > g ? g > b ? b : g : r > b ? b : r;
    const double max = r < g ? g < b ? b : g : r < b ? b : r;
    const double v = max; // v
    const double delta = max - min;
    double h, s;
    if (max == 0.0) {
        // r = g = b = 0					// s = 0, v is undefined
        s = 0.0;
        h = 0.0;
    } else {
        s = delta / max; // s
        if (r == max)
            h = (g - b) / delta; // between yellow & magenta
        else if (g == max)
            h = 2.0 + (b - r) / delta; // between cyan & yellow
        else
            h = 4.0 + (r - g) / delta; // between magenta & cyan
        h /= 6.0;
        if (h < 0.0)
            h += 1.0;
    }
    RGBFloat HSV;
    // H, S and V are all in [0 .. 1]
    HSV.SetRed((float)h);
    HSV.SetGreen((float)s);
    HSV.SetBlue((float)v);
    return HSV;
}

RGBFloat CustomShader::ToRGB(const RGBFloat *HSVColor) {
    double h = (double)HSVColor->Red() * 360.0;
    const double s = HSVColor->Green();
    const double v = HSVColor->Blue();
    if (s == 0.0) {
        const RGBFloat RGB = (float)v;
        return RGB;
    }
    if (h == 360.0)
        h = 0.0;
    h /= 60.0;
    const int i = (int)h;
    const double f = h - (double)i;
    const double p = v * (1.0 - s);
    const double q = v * (1.0 - s * f);
    const double t = v * (1.0 - s * (1.0 - f));
    double r = 0, g = 0, b = 0;
    switch (i) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        case 5:
            r = v;
            g = p;
            b = q;
        default: 
            break;
    }
    RGBFloat RGB;
    RGB.SetRed((float)r);
    RGB.SetGreen((float)g);
    RGB.SetBlue((float)b);
    return RGB;
}
