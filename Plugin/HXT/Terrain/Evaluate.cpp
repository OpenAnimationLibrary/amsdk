// KB  6/8/00  \Ken85\Plugin\Wizards\Grid\Evaluate.cpp

// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
#include "StdAfx.h"
#include "Wizard.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"

//#define OCTAVES 2
/*
static float octaves2[] = { .6666f, .3333f };
static float octaves3[] = { .5714f, .2857f, .1428f };
static float octaves4[] = { .5333f, .2666f, .1333f, .0666f };
static float octaves5[] = { .5161f, .2580f, .1290f, .0645f, .0322f };
*/
static HCP *GetIndexedCP(HSpline *sph, const int index) {
    HCP *cp = sph->GetHeadCP();
    for (int i = 0; cp && i < index; cp = cp->GetNext(), ++i){}
    return cp;
}

static HSpline *BuildSpline(const WizardParameters *wp, const BOOL vertical, HModelCache *hmc, HSpline **sphptr, float over, const float from, const float to, const float step, const CWizardDialog *dlg) {
    int count = 0;
    Vector firstpos, pos, tempv;
    HCP *lastcp = nullptr;
    const int maxindex = ROUNDOFF((to - from) / step);
    if (over < from)
        over = from;
    if (over > to)
        over = to;

    for (float i = from; count <= maxindex; i += step, ++count) {
        // get turbulence offset from plane
        tempv.Set(over, 0.F, i);
        if (wp->m_turbscale)
            tempv /= wp->m_turbscale;
        float turboffset = dlg->getDisplacement(over, i) * 2.F - 1.F;
        turboffset *= wp->m_turbmagnitude;
        if (vertical) {
            switch (wp->m_orientation) {
                case WizardParameters::XY:
                    if (count == 0)
                        firstpos.Set(over, i, turboffset);
                    else
                        pos.Set(over, i, turboffset);
                    break;
                case WizardParameters::XZ:
                    if (count == 0)
                        firstpos.Set(over, turboffset, i);
                    else
                        pos.Set(over, turboffset, i);
                    break;
                case WizardParameters::YZ:
                    if (count == 0)
                        firstpos.Set(turboffset, over, i);
                    else
                        pos.Set(turboffset, over, i);
                    break;
            }
        } else {
            // horizontal
            switch (wp->m_orientation) {
                case WizardParameters::XY:
                    if (count == 0)
                        firstpos.Set(i, over, turboffset);
                    else
                        pos.Set(i, over, turboffset);
                    break;
                case WizardParameters::XZ:
                    if (count == 0)
                        firstpos.Set(i, turboffset, over);
                    else
                        pos.Set(i, turboffset, over);
                    break;
                case WizardParameters::YZ:
                    if (count == 0)
                        firstpos.Set(turboffset, i, over);
                    else
                        pos.Set(turboffset, i, over);
                    break;
            }
        }
        // Begin the spline, must have 2 points or it isn't a spline
        if (count == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else {
            if (count > 1)
                lastcp = hmc->AddCP(lastcp, &pos);
        }
    }
    return *sphptr;
}

BOOL CWizardApp::NewShape(HModelCache *hmc, const CWizardDialog *dlg) {
    int index, uindex, vindex;
    float u, v;
    HCP *cp1;
    HGroupCP *group = nullptr;

    int unumsplines = ROUNDOFF(m_parameters.m_width / m_parameters.m_stepwidth);
    int vnumsplines = ROUNDOFF(m_parameters.m_height / m_parameters.m_stepheight);
    // 2 splines for each dimension needed to for form a proper patch !
    if (unumsplines == 0)
        unumsplines = 1; //prevent a zero division
    if (vnumsplines == 0)
        vnumsplines = 1;
    m_parameters.m_stepwidth = m_parameters.m_width / unumsplines;
    m_parameters.m_stepheight = m_parameters.m_height / vnumsplines;
    unumsplines++;
    vnumsplines++;
    /*
       if (unumsplines < 2) {
          unumsplines = 2;
          m_parameters.m_stepwidth = m_parameters.m_width/unumsplines;
       }
       if (vnumsplines < 2) {
          vnumsplines = 2;
          m_parameters.m_stepheight = m_parameters.m_height/vnumsplines;
       }
       */
    auto **usplines = new HSpline *[unumsplines];
    auto **vsplines = new HSpline *[vnumsplines];

    const float startu = -m_parameters.m_width / 2.F;
    const float endu = -startu;
    const float stepu = m_parameters.m_stepwidth;
    const float startv = -m_parameters.m_height / 2.F;
    const float endv = -startv;
    const float stepv = m_parameters.m_stepheight;

    // build vertical splines
    for (u = startu, index = 0; index < unumsplines; u += stepu, ++index)
        BuildSpline(&m_parameters, TRUE, hmc, &usplines[index], u, startv, endv, stepv, dlg);
    // build horizontal splines
    for (v = startv, index = 0; index < vnumsplines; v += stepv, ++index)
        BuildSpline(&m_parameters, FALSE, hmc, &vsplines[index], v, startu, endu, stepu, dlg);
    // walk through splines and attach CPs

    if (m_parameters.m_flatedges) {
        Vector multiply;
        switch (m_parameters.m_orientation) {
            case WizardParameters::XY:
                multiply.Set(1, 1, 0);
                break;
            case WizardParameters::XZ:
                multiply.Set(1, 0, 1);
                break;
            case WizardParameters::YZ:
                multiply.Set(0, 1, 1);
                break;
        }
        HCP *lastcp = nullptr;
        Vector pos;
        for (uindex = 0; uindex < unumsplines; ++uindex) {
            for (cp1 = usplines[uindex]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
                lastcp = cp1;
            }
            cp1 = usplines[uindex]->GetHeadCP();
            pos = *cp1->GetPosition() * multiply;
            cp1->SetPosition(&pos);
            pos = *lastcp->GetPosition() * multiply;
            lastcp->SetPosition(&pos);
        }
        for (vindex = 0; vindex < vnumsplines; ++vindex) {
            for (cp1 = vsplines[vindex]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
                lastcp = cp1;
            }
            cp1 = vsplines[vindex]->GetHeadCP();
            pos = *cp1->GetPosition() * multiply;
            cp1->SetPosition(&pos);
            pos = *lastcp->GetPosition() * multiply;
            lastcp->SetPosition(&pos);
        }
        for (cp1 = usplines[0]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
            pos = *cp1->GetPosition() * multiply;
            cp1->SetPosition(&pos);
        }
        for (cp1 = usplines[unumsplines - 1]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
            pos = *cp1->GetPosition() * multiply;
            cp1->SetPosition(&pos);
        }
        for (cp1 = vsplines[0]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
            pos = *cp1->GetPosition() * multiply;
            cp1->SetPosition(&pos);
        }
        for (cp1 = vsplines[vnumsplines - 1]->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
            pos = *cp1->GetPosition() * multiply;
            cp1->SetPosition(&pos);
        }
    }

    if (hmc->GetHeadInstance()) // There is at least one visible model, so lets selected the points
        makegroup = TRUE;

    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    for (uindex = 0; uindex < unumsplines; ++uindex) {
        for (vindex = 0; vindex < vnumsplines; ++vindex) {
            cp1 = GetIndexedCP(usplines[uindex], vindex);
            HCP *cp2 = GetIndexedCP(vsplines[vindex], uindex);
            if (cp1 && cp2) {
                const BOOL cp2deleted = hmc->AttachCPs(cp1, cp2);
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
        hmc->AddToTemporaryGroup(group); // makes sure all new points are selected when plugin exits

    delete[] usplines;
    delete[] vsplines;

    hmc->OpenView();
    if (!makegroup)
        hmc->HilightInProjectBar();
    hmc->SetChanged(TRUE);

    return TRUE;
}
