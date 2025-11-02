// RC  10/1/2001  \Randy90\Plugin\Textures\BBall\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

#define BBRADIUS     123.3f
#define COLORWIDTH   (4.775f/BBRADIUS)
#define CIRCPOS       66.5F
#define CIRCRAD       47.0f
//#define DOTRADIUS    (2.55f/BBRADIUS)
//#define DOTSPACING   (2.9f/BBRADIUS)
//#define NOSPOTWIDTH  (7.566666f/BBRADIUS)
//#define PIPCLOSE      .99994652f

HProperty *CustomTexture::GetPropertyAt(int i) {
    return nullptr;
}

BOOL inlines(const Vector &p, const float w) {
    /* This routine decides whether an XYZ point on the surface
       of the sphere is within a certain distance of one of
       the lines on the basketball. */

    /* easy tests... Z=0, Y=0 equator and meridian lines */
    if (hash_math::abs(p.z) < w || hash_math::abs(p.y) < w)
        return TRUE;

    /* 45 degree stripes outside of curve. Near the equator
       another case needs to be used, though  */
    if (hash_math::abs(p.y) > 35.F / BBRADIUS && hash_math::abs(p.z) > 35.F / BBRADIUS) {
        if (hash_math::abs(p.z - p.y) < 1.4142F * w)
            return TRUE;
        if (hash_math::abs(p.y + p.z) < 1.4142F * w)
            return TRUE;
        return FALSE;
    }

    /* Do a trivial rejection of areas far from the curved
       part of the lines */
    if (hash_math::abs(p.x) < 80.F / BBRADIUS)
        return FALSE;

    /* curved bit. We assume the curve is in the shape of a 
       circle defined by some (empirically determined)
       constants. We find the radius from this circle and
       see whether we are within w units of it. We use y and z
       symmetrically depending on which half (x positive or 
       negative) of the ball we are on.  */
    float r;
    if (p.x > 0.F) {
        if (p.y > 0.F)
            r = hash_math::sqrt(p.z * p.z + (p.y - CIRCPOS / BBRADIUS) * (p.y - CIRCPOS / BBRADIUS));
        else
            r = hash_math::sqrt(p.z * p.z + (p.y + CIRCPOS / BBRADIUS) * (p.y + CIRCPOS / BBRADIUS));
        if (hash_math::abs(r - CIRCRAD / BBRADIUS) < w)
            return TRUE;
    } else {
        if (p.z > 0.F)
            r = hash_math::sqrt(p.y * p.y + (p.z - CIRCPOS / BBRADIUS) * (p.z - CIRCPOS / BBRADIUS));
        else
            r = hash_math::sqrt(p.y * p.y + (p.z + CIRCPOS / BBRADIUS) * (p.z + CIRCPOS / BBRADIUS));
        if (hash_math::abs(r - CIRCRAD / BBRADIUS) < w)
            return TRUE;
    }
    return FALSE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(RGBFloat(1.F, 0.5F, 0.F));

    const RotateSphere rs(evalp.Normalized());
    const float phi = (rs.latitude - 90.F) / hash_constants::radians;
    const float theta = rs.longitude / hash_constants::radians;
    const float r = hash_math::cos(phi);
    Vector p;
    p.x = r * hash_math::cos(theta);
    p.y = r * hash_math::sin(theta);
    p.z = hash_math::sin(phi);

    if (inlines(p,COLORWIDTH / 2.F)) // inside line
        texinfo->GetAttr()->GetDiffuseColor()->SetValue(RGBFloat(0.F, 0.F, 0.F));
    /*
       else
          for (int i=0;i<numpips;++i) // go through pips
             if (p.Dot(pip[i]) > PIPCLOSE)
                texinfo->GetAttr()->GetDiffuseColor()->SetValue(RGBFloat(0.8f,0.4f,0.F));
    */
    return TRUE;
}

/*
void CustomTexture::ReadPips()
{
//   FILE *infile=fopen_s("c:\\pips.dat","r"); // file of spherically distributed points
   FILE *infile;
#if (_MSC_VER >= 1400)
   fopen_s(&infile,"c:\\pips.dat","r"); // file of spherically distributed points
#else
   infile = fopen("c:\\pips.dat","r");
#endif
   if (infile == nullptr)
      return;
   int i=0;
#if (_MSC_VER >= 1400)
   while (fscanf_s(infile,"%f%f%f",&pip[i].x,&pip[i].y,&pip[i].z)!=EOF) {
#else
   while (fscanf(infile,"%f%f%f",&pip[i].x,&pip[i].y,&pip[i].z)!=EOF) {
#endif
       // Normalize points to be at surface of the sphere
      pip[i].Normalize();
       // If the points are not too close to one of the lines
       //   of the ball, add them to the list of pips.
      if (!inlines(pip[i], NOSPOTWIDTH/2.F+DOTRADIUS))
         i++; 
   }
   fclose(infile);
   numpips=i;
}
*/
