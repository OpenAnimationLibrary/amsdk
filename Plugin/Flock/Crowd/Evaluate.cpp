// KB  6/12/2003  \Ken105\Plugin\Flock\Crowd\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Influenc.h"
#include "Rnd.h"

HProperty *CustomFlock::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_mindistance;
        case 1:
            return m_xzscaleoffset;
        case 2:
            return m_yscaleoffset;
        case 3:
            return m_rolloffset;
        case 4:
            return m_proportional;
        default:
            return nullptr;
    }
}

namespace {
    BOOL MinDistTest(const CustomFlock *flock, const int id) {
        for (int i = 0; i < id; ++i) {
            const float dist = (flock->m_flockbuf.m_boids[i].location - flock->m_flockbuf.m_boids[id].location).Norm();
            if (dist < flock->m_mindistance->GetValue())
                return FALSE;
        }
        return TRUE;
    }
}

void CustomFlock::InitParticlePos(const int id, TSQ &tsq, Time &actionoffset) {
    BOOL inshape = FALSE;
    Vector p = tsq.translate;
    int numtries = 0;

    while (!inshape) {
        switch (m_flockbuf.m_influenceshape->GetRType()) {
            case RBOX:
                p.x = Rnd() * ((Slab *)m_flockbuf.m_influenceshape)->m_halfwidth * 2 - ((Slab *)m_flockbuf.m_influenceshape)->m_halfwidth;
                p.y = 0.F;
                p.z = Rnd() * ((Slab *)m_flockbuf.m_influenceshape)->m_length;
                break;
            case RCYLINDER:
                p.x = Rnd() * ((Cylinder *)m_flockbuf.m_influenceshape)->m_radius * 2 - ((Cylinder *)m_flockbuf.m_influenceshape)->m_radius;
                p.y = 0.F;
                p.z = Rnd() * ((Cylinder *)m_flockbuf.m_influenceshape)->m_length;
                break;
            case RSPHERE:
                p.x = Rnd() * ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance * 2 - ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance;
                p.y = 0.F;
                p.z = Rnd() * ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance * 2 - ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance;
                break;
            case RCONE:
                p.x = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_cap - ((Cone *)m_flockbuf.m_influenceshape)->m_cap / 2.F;
                p.y = 0.F;
                p.z = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_length;
                break;
            default:
                break;
        }
        if (m_flockbuf.m_influenceshape->GetRType() == RSPHERE)
            inshape = p.Norm() < ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance ? TRUE : FALSE;
        else
            inshape = m_flockbuf.m_influenceshape->IsInside(p);

        m_flockbuf.m_boids[id].location = p; // set boid list position
        // check proximity to other particles?  After 10 tries, just give up
        if (!MinDistTest(this, id) && numtries < 10) {
            inshape = FALSE;
            ++numtries;
        }
    }

    // adjust scale and rotation
    const float xzscaleoffset = Rnd() * (2 * m_xzscaleoffset->GetValue()) - m_xzscaleoffset->GetValue();
    const float yscaleoffset = Rnd() * (2 * m_yscaleoffset->GetValue()) - m_yscaleoffset->GetValue();
    const float rolloffset = Rnd() * (2 * m_rolloffset->GetValue()) - m_rolloffset->GetValue();
    tsq.scale.x = xzscaleoffset / UNIT;
    tsq.scale.z = xzscaleoffset / UNIT;
    if (m_proportional->GetValue())
        tsq.scale.y = xzscaleoffset / UNIT;
    else
        tsq.scale.y = yscaleoffset / UNIT;
    tsq.roll = rolloffset;

    m_flockbuf.m_boids[id].direction.Set(0.F);
    actionoffset = Rnd() * m_flockbuf.m_maxactionoffset; // set action offset
    tsq.translate = p;
}

void CustomFlock::UpdateParticlePos(const int id, TSQ &tsq, Vector &d, float frametime) {
    Vector p = tsq.translate;
    p += d;
    m_flockbuf.m_boids[id].location = p;
    tsq.translate = p;
}
