// KB  6/19/2003  \Ken105\Plugin\Flock\Birds\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Influenc.h"
#include "Rnd.h"

HProperty *CustomFlock::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_mindistance;
        case 1:
            return m_jitter;
        case 2:
            return m_maxspeed;
        case 3:
            return m_acceleration;
        default:
            return nullptr;
    }
}

void CustomFlock::InitParticlePos(const int id, TSQ &tsq, Time &actionoffset) {
    BOOL inshape = FALSE;
    Vector p = tsq.translate;

    while (!inshape) {
        switch (m_flockbuf.m_influenceshape->GetRType()) {
            case RBOX:
                p.x = Rnd() * ((Slab *)m_flockbuf.m_influenceshape)->m_halfwidth * 2.F - ((Slab *)m_flockbuf.m_influenceshape)->m_halfwidth;
                p.y = Rnd() * ((Slab *)m_flockbuf.m_influenceshape)->m_halfwidth * 2.F - ((Slab *)m_flockbuf.m_influenceshape)->m_halfwidth;
                p.z = Rnd() * ((Slab *)m_flockbuf.m_influenceshape)->m_length;
                break;
            case RCYLINDER:
                p.x = Rnd() * ((Cylinder *)m_flockbuf.m_influenceshape)->m_radius * 2.F - ((Cylinder *)m_flockbuf.m_influenceshape)->m_radius;
                p.y = Rnd() * ((Cylinder *)m_flockbuf.m_influenceshape)->m_radius * 2.F - ((Cylinder *)m_flockbuf.m_influenceshape)->m_radius;
                p.z = Rnd() * ((Cylinder *)m_flockbuf.m_influenceshape)->m_length;
                break;
            case RSPHERE:
                p.x = Rnd() * ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance * 2.F - ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance;
                p.y = Rnd() * ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance * 2.F - ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance;
                p.z = Rnd() * ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance * 2.F - ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance;
                break;
            case RCONE:
                p.x = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_cap - ((Cone *)m_flockbuf.m_influenceshape)->m_cap * 0.5f;
                p.y = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_cap - ((Cone *)m_flockbuf.m_influenceshape)->m_cap * 0.5f;
                p.z = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_length;
                break;
            default:
                break;
        }
        if (m_flockbuf.m_influenceshape->GetRType() == RSPHERE)
            inshape = p.Norm() < ((RSphere *)m_flockbuf.m_influenceshape)->m_falloffdistance ? TRUE : FALSE;
        else
            inshape = m_flockbuf.m_influenceshape->IsInside(p);

        // check proximity to other particles?
    }
    m_flockbuf.m_boids[id].location = p; // set boid list position
    m_flockbuf.m_boids[id].direction = m_flockbuf.m_worlddirection; //.Set(0.F, 0.F, 0.F);
    actionoffset = Rnd() * m_flockbuf.m_maxactionoffset; // set action offset
    tsq.translate = p;
}

void CustomFlock::UpdateParticlePos(const int id, TSQ &tsq, Vector &d, const float frametime) {
    const Boid *boid = &m_flockbuf.m_boids[id];
    const Boid *closest = FlockBuf::FindClosestNeighbor(boid, nullptr);
    Vector newdirection, p = tsq.translate, jitter;
    float speed, brakes;
    const float maxspeed = m_maxspeed->GetValue() * frametime;
    const float acceleration = m_acceleration->GetValue() * frametime;

    // calculate aim towards center of flock+d, factor it with distance outside radius
    const Vector center = (m_flockbuf.m_ulbounds + m_flockbuf.m_lrbounds) * 0.5f;

    jitter.x = Rnd() * m_jitter->GetValue() * 2.F - m_jitter->GetValue();
    jitter.y = Rnd() * m_jitter->GetValue() * 2.F - m_jitter->GetValue();
    jitter.z = Rnd() * m_jitter->GetValue() * 2.F - m_jitter->GetValue();

    if (!closest) {
        // no close neighbor, steer back to center of influence region
        //      newaim = boid->location - center + jitter; // old code
        Vector newaim = center - boid->location + jitter;
        newaim = newaim.Normalize();
        newaim *= acceleration;
        newdirection = newaim + boid->direction * frametime;
        if ((speed = newdirection.Norm()) > maxspeed) {
            brakes = maxspeed / speed;
            newdirection *= brakes;
        }
        p += newdirection + d;
        m_flockbuf.m_boids[id].location = p;
        m_flockbuf.m_boids[id].direction = newdirection + m_flockbuf.m_worlddirection;
        tsq.translate = p;
        return;
    }

    const float dist = (closest->location - boid->location).Norm();

    // obstacle avoidance goes here

    // basic velocity matching and flock centering
    // steer toward from neighbor 
    if (dist > m_mindistance->GetValue())
        newdirection = closest->location + closest->direction * frametime - m_mindistance->GetValue() - (boid->location + boid->direction);
    else
        // steer away from neighbor
        newdirection = boid->location + boid->direction * frametime - (closest->location + closest->direction * frametime - m_mindistance->GetValue());

    newdirection += jitter;
    newdirection = newdirection.Normalize();
    newdirection *= acceleration;

    //   newdirection += boid->direction; // to keep them in the region

    // observe the speed limit
    if ((speed = newdirection.Norm()) > maxspeed) {
        brakes = maxspeed / speed;
        newdirection *= brakes;
    }

    p += newdirection + d;
    m_flockbuf.m_boids[id].location = p;
    m_flockbuf.m_boids[id].direction = newdirection + m_flockbuf.m_worlddirection;
    tsq.translate = p;
}
