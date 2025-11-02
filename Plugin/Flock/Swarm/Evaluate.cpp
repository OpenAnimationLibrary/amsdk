// KB  6/13/2003  \Ken105\Plugin\Flock\Swarm\Evaluate.cpp

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
                p.x = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_cap - ((Cone *)m_flockbuf.m_influenceshape)->m_cap / 2.F;
                p.y = Rnd() * ((Cone *)m_flockbuf.m_influenceshape)->m_cap - ((Cone *)m_flockbuf.m_influenceshape)->m_cap / 2.F;
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
    m_flockbuf.m_boids[id].direction.Set(0);
    //   p *= m_flockbuf.m_influenceshape->worldmatrix; // transform to world coords
    actionoffset = Rnd() * m_flockbuf.m_maxactionoffset; // set action offset
    tsq.translate = p;
}

void CustomFlock::UpdateParticlePos(const int id, TSQ &tsq, Vector &d, const float frametime) {
    //   p += d;
    Vector p = tsq.translate;
    Boid *boid = &m_flockbuf.m_boids[id], *near2;
    float speed;
    float brakes;
    float dist;
    Vector newaim;
    Vector newdirection;
    Vector jitter;
    const float maxspeed = m_maxspeed->GetValue() * frametime;
    const float acceleration = m_acceleration->GetValue() * frametime;
    const Vector direction = boid->direction * m_lasttimeframe; // velocity 

    m_lasttimeframe = frametime;
    newaim.Set(0);
    Vector center = (m_flockbuf.m_ulbounds + m_flockbuf.m_lrbounds) * 0.5f;
    jitter.x = Rnd() * m_jitter->GetValue() * 2.F - m_jitter->GetValue();
    jitter.y = Rnd() * m_jitter->GetValue() * 2.F - m_jitter->GetValue();
    jitter.z = Rnd() * m_jitter->GetValue() * 2.F - m_jitter->GetValue();
    Boid *near1 = FlockBuf::FindClosestNeighbor(boid, nullptr);
    if (near1) {
        near2 = FlockBuf::FindClosestNeighbor(near1, boid);
        dist = (near1->location - boid->location).Norm();
    } else {
        // no close neighbor, steer back to center of influence region
        newaim = center.Normalize() - boid->location.Normalize() + jitter;
        newaim *= acceleration;
        newdirection = direction + newaim;
        if ((speed = newdirection.Norm()) > maxspeed) {
            brakes = maxspeed / speed;
            newdirection *= brakes;
        }
        p += newdirection + d;
        m_flockbuf.m_boids[id].location = p;
        m_flockbuf.m_boids[id].direction = newdirection;
        tsq.translate = p;
        return;
    }

    // obstacle avoidance goes here

    // steer away from neighbor
    newaim += jitter;
    if (near2)
        newaim = (near1->location.Normalize() + near2->location.Normalize()) * 0.5f;
    else
        newaim = near1->location.Normalize();
    newaim *= acceleration;
    if (dist > m_mindistance->GetValue()) {
        newdirection = direction - newaim;
        // observe the speed limit
        if ((speed = newdirection.Norm()) > maxspeed) {
            brakes = maxspeed / speed;
            newdirection *= brakes;
        }
    } else
    // steer towards neighbor
        newdirection = direction + newaim;

    // observe the speed limit
    if ((speed = newdirection.Norm()) > maxspeed) {
        brakes = maxspeed / speed;
        newdirection *= brakes;
    }

    p += newdirection + d;
    m_flockbuf.m_boids[id].location = p;
    m_flockbuf.m_boids[id].direction = newdirection;
    tsq.translate = p;
}
