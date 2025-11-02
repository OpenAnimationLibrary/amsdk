// RC  10/1/2001  \Randy90\Plugin\Textures\Grid\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_lcolor;
        case 1:
            return m_transp;
        case 2:
            return m_gtype;
        case 3:
            return m_origin;
        case 4:
            return m_width;
        case 5:
            return m_interval;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const int val = (int)m_gtype->GetValue();
    const int gtype = val % GRIDTYPE_NUMBER;

    switch (gtype) {
        case GRIDTYPE_PLANE:
            return EvaluatePlane(evalp, texinfo);
        case GRIDTYPE_LINE:
            return EvaluateLine(evalp, texinfo);
        case GRIDTYPE_CUBE:
            return EvaluateCube(evalp, texinfo);
        case GRIDTYPE_DOT:
            return EvaluateDot(evalp, texinfo);
        default:;
    }
    return TRUE;
}

BOOL CustomTexture::EvaluatePlane(const Vector &evalp, HTexInfo *texinfo) const {
    if (EvalElement(m_width->GetX()->GetValue(), m_origin->GetX()->GetValue(), m_interval->GetX()->GetValue(), evalp.x, nullptr)) {
        return SetLineColor(texinfo);
    }
    if (EvalElement(m_width->GetY()->GetValue(), m_origin->GetY()->GetValue(), m_interval->GetY()->GetValue(), evalp.y, nullptr)) {
        return SetLineColor(texinfo);
    }
    if (EvalElement(m_width->GetZ()->GetValue(), m_origin->GetZ()->GetValue(), m_interval->GetZ()->GetValue(), evalp.z, nullptr)) {
        return SetLineColor(texinfo);
    }
    return TRUE;
}

BOOL CustomTexture::SetLineColor(HTexInfo *texinfo) const {
    const RGBFloat linecolor = m_lcolor->GetNormalizedRGBFloat();
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(linecolor);
    const float t = m_transp->GetValue() / 100.F;
    texinfo->GetAttr()->GetTransparency()->SetValue(t);
    return TRUE;
}

int CustomTexture::EvalElement(const float w, const float o, const float i, const float evalp, float *np) {
    if (w == 0.F)
        return 0;
    float e = evalp - o;
    const float totalWidth = w + i;
    const int count = fast_ftol_signed(e / totalWidth);
    e -= count * totalWidth;
    if (e >= -w / 2.F && e <= w / 2.F) {
        if (np)
            *np = count * totalWidth + o;
        return 1;
    }
    return 0;
}

BOOL CustomTexture::EvaluateLine(const Vector &evalp, HTexInfo *texinfo) const {
    int cross = 0;

    if (EvalElement(m_width->GetX()->GetValue(), m_origin->GetX()->GetValue(), m_interval->GetX()->GetValue(), evalp.x, nullptr)) {
        cross ++;
    }
    if (EvalElement(m_width->GetY()->GetValue(), m_origin->GetY()->GetValue(), m_interval->GetY()->GetValue(), evalp.y, nullptr)) {
        cross ++;
    }
    if (cross >= 2) {
        return SetLineColor(texinfo);
    }
    if (cross >= 1 && EvalElement(m_width->GetZ()->GetValue(), m_origin->GetZ()->GetValue(), m_interval->GetZ()->GetValue(), evalp.z, nullptr)) {
        return SetLineColor(texinfo);
    }
    return TRUE;
}

BOOL CustomTexture::EvaluateCube(const Vector &evalp, HTexInfo *texinfo) const {
    if (!EvalElement(m_width->GetX()->GetValue(), m_origin->GetX()->GetValue(), m_interval->GetX()->GetValue(), evalp.x, nullptr)) {
        return TRUE;
    }
    if (!EvalElement(m_width->GetY()->GetValue(), m_origin->GetY()->GetValue(), m_interval->GetY()->GetValue(), evalp.y, nullptr)) {
        return TRUE;
    }
    if (!EvalElement(m_width->GetZ()->GetValue(), m_origin->GetZ()->GetValue(), m_interval->GetZ()->GetValue(), evalp.z, nullptr)) {
        return TRUE;
    }
    return SetLineColor(texinfo);
}

BOOL CustomTexture::EvaluateDot(const Vector &evalp, HTexInfo *texinfo) const {
    float nx, ny, nz;
    float rx = m_width->GetX()->GetValue();
    float ry = m_width->GetY()->GetValue();
    float rz = m_width->GetZ()->GetValue();
    if (rx == 0.F || ry == 0.F || rz == 0.F)
        return TRUE;

    if (!EvalElement(rx, m_origin->GetX()->GetValue(), m_interval->GetX()->GetValue(), evalp.x, &nx)) {
        return TRUE;
    }
    if (!EvalElement(ry, m_origin->GetY()->GetValue(), m_interval->GetY()->GetValue(), evalp.y, &ny)) {
        return TRUE;
    }
    if (!EvalElement(rz, m_origin->GetZ()->GetValue(), m_interval->GetZ()->GetValue(), evalp.z, &nz)) {
        return TRUE;
    }

    rx *= 0.5F;
    ry *= 0.5F;
    rz *= 0.5F;
    const float sx = hash_math::rcp(rx);
    const float sy = hash_math::rcp(ry);
    const float sz = hash_math::rcp(rz);

    const float dx = (nx - evalp.x) * sx;
    const float dy = (ny - evalp.y) * sy;
    const float dz = (nz - evalp.z) * sz;
    const float d = hash_math::sqrt(dx * dx + dy * dy + dz * dz);
    if (d <= 1.F)
        SetLineColor(texinfo);

    return TRUE;
}
