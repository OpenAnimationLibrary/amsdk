// Dan  9/18/2003  \DanLP110\Plugin\HXT\Grid\Evaluate.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"

#define OCTAVES 2

static float octaves2[] = {.6666f, .3333f};
static float octaves3[] = {.5714f, .2857f, .1428f};
static float octaves4[] = {.5333f, .2666f, .1333f, .0666f};
static float octaves5[] = {.5161f, .2580f, .1290f, .0645f, .0322f};

static float MyGetTurbulence(const Vector &p) {
    Vector evalp = p;

    float result = 0.F;
    for (int octave = 0; octave < OCTAVES; ++octave, evalp *= 2.F) {
        switch (OCTAVES) {
            case 1:
                result += hash_math::abs(GetTurbulence(evalp));
                break;
            case 2:
                result += hash_math::abs(GetTurbulence(evalp)) * octaves2[octave];
                break;
            case 3:
                result += hash_math::abs(GetTurbulence(evalp)) * octaves3[octave];
                break;
            case 4:
                result += hash_math::abs(GetTurbulence(evalp)) * octaves4[octave];
                break;
            case 5:
                result += hash_math::abs(GetTurbulence(evalp)) * octaves5[octave];
                break;
        }
    }
    return result * 2.F;
}

static HCP *GetIndexedCP(HSpline *sph, const int index) {
    HCP *cp = sph->GetHeadCP();
    for (int i = 0; cp && i < index; cp = cp->GetNext(), ++i) { }
    return cp;
}

static HSpline *BuildSpline(const GridParameters *wp, const BOOL vertical, HModelCache *hmc, HSpline **sphptr, const float over, const float from, const float to, const float step, const BOOL needturbulence) {
    int count = 0;
    Vector firstpos, pos, tempv;
    HCP *lastcp = nullptr;
    float turboffset;
    const int maxindex = ROUNDOFF((to - from) / step);
    const float turbver = over;
    //comeback need to remember , why I have added this ... 
    //   if (needturbulence) {
    //      if (turbver < from) turbver = from;
    //      if (turbver > to ) turbver = to;
    //   }

    for (float i = from; count <= maxindex /*i < to*/; i += step, ++count) {
        // get turbulence offset from plane only if we have a magnitude !
        if (needturbulence) {
            tempv.Set(turbver, 0.F, i);
            if (wp->m_turbscale)
                tempv /= wp->m_turbscale;
            turboffset = MyGetTurbulence(tempv) * 2.F - 1.F;
            turboffset *= wp->m_turbmagnitude;
        } else {
            turboffset = 0.F;
        }
        if (vertical) {
            switch (wp->m_orientation) {
                case GridParameters::XY:
                    if (count == 0)
                        firstpos.Set(over, turboffset, i);
                    else
                        pos.Set(over, turboffset, i);
                    break;
                case GridParameters::YZ:
                    if (count == 0)
                        firstpos.Set(turboffset, over, i);
                    else
                        pos.Set(turboffset, over, i);
                    break;
                case GridParameters::XZ:
                    if (count == 0)
                        firstpos.Set(over, i, turboffset);
                    else
                        pos.Set(over, i, turboffset);
                    break;
            }
        } else {
            // horizontal
            switch (wp->m_orientation) {
                case GridParameters::XY:
                    if (count == 0)
                        firstpos.Set(i, turboffset, over);
                    else
                        pos.Set(i, turboffset, over);
                    break;
                case GridParameters::YZ:
                    if (count == 0)
                        firstpos.Set(turboffset, i, over);
                    else
                        pos.Set(turboffset, i, over);
                    break;
                case GridParameters::XZ:
                    if (count == 0)
                        firstpos.Set(i, over, turboffset);
                    else
                        pos.Set(i, over, turboffset);
                    break;
            }
        }
        // Begin the spline, must have 2 points or it isn't a spline
        if (count == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (count > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    return *sphptr;
}

BOOL CHxtApp::NewShape(HModelCache *mch) {
    int index;
    float u, v;
    HGroupCP *group = nullptr;

    //   unumsplines = (int)(m_parameters.m_width/m_parameters.m_stepwidth);
    //   vnumsplines = (int)(m_parameters.m_height/m_parameters.m_stepheight);
    int unumsplines = ROUNDOFF(m_parameters.m_width / m_parameters.m_stepwidth);
    int vnumsplines = ROUNDOFF(m_parameters.m_height / m_parameters.m_stepheight);

    if (unumsplines == 0)
        unumsplines = 1; //prevent a zero division
    if (vnumsplines == 0)
        vnumsplines = 1;
    m_parameters.m_stepwidth = m_parameters.m_width / unumsplines;
    m_parameters.m_stepheight = m_parameters.m_height / vnumsplines;
    unumsplines++;
    vnumsplines++;

    auto **usplines = new HSpline *[unumsplines];
    auto **vsplines = new HSpline *[vnumsplines];

    const float startu = -m_parameters.m_width / 2.F;
    const float endu = -startu;
    const float stepu = m_parameters.m_stepwidth;
    const float startv = -m_parameters.m_height / 2.F;
    const float endv = -startv;
    const float stepv = m_parameters.m_stepheight;

    const BOOL needturbulence = m_parameters.m_turbmagnitude != 0.F;

    // build vertical splines
    for (u = startu, index = 0; index < unumsplines /*u < endu*/; u += stepu, ++index)
        BuildSpline(&m_parameters, TRUE, mch, &usplines[index], u, startv, endv, stepv, needturbulence);
// build horizontal splines
    for (v = startv, index = 0; index < vnumsplines /*v < endv*/; v += stepv, ++index)
        BuildSpline(&m_parameters, FALSE, mch, &vsplines[index], v, startu, endu, stepu, needturbulence);
// walk through splines and attach CPs

    if (mch->GetHeadInstance()) // There is at least one visible model, so lets selected the points
        makegroup = TRUE;

    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    for (int uindex = 0; uindex < unumsplines; ++uindex) {
        for (int vindex = 0; vindex < vnumsplines; ++vindex) {
            HCP *cp1 = GetIndexedCP(usplines[uindex], vindex);
            HCP *cp2 = GetIndexedCP(vsplines[vindex], uindex);
            if (cp1 && cp2) {
                const BOOL cp2deleted = mch->AttachCPs(cp1, cp2);
                // Note: if AttachCPs causes loopback, A:M deletes tail cp
                // before attaching, so can't add it to group
                if (makegroup) {
                    cp1->AddToGroup(&group);
                    if (!cp2deleted)
                        cp2->AddToGroup(&group);
                }
            }
        }
    }
    if (makegroup)
        mch->AddToTemporaryGroup(group); // makes sure all new points are selected when plugin exits
    delete[] usplines;
    delete[] vsplines;

    mch->SetChanged(TRUE);
    mch->OpenView();
    if (!makegroup)
        mch->HilightInProjectBar();
    return TRUE;
}
