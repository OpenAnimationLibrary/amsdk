// YP  06/06/2006  Plugin\Post\Denoise\Process.cpp

// The following Denoise plugin is based on greycstoration.cpp example file
// provided by David Tschumperle. So here is the comments at the begining of
// the greycstoration.cpp file for compliance with the CeCILL licence terms.
/*-----------------------------------------------------------------------------

    File        : greycstoration.cpp

    Description : GREYCstoration - A tool to denoise, inpaint and resize images.

    The GREYCstoration algorithm is an implementation of diffusion tensor-directed
    diffusion PDE's for image regularization and interpolation, published in

    "Fast Anisotropic Smoothing of Multi-Valued Images 
    using Curvature-Preserving PDE's"
    (D. Tschumperlé)
    Research Report "Cahiers du GREYC 05/01", February 2005),
    GREYC, CNRS UMR 6072
    (see also http://www.greyc.ensicaen.Fr/~dtschump/greycstoration)
    
    "Vector-Valued Image Regularization with PDE's : A Common Framework
    for Different Applications"
    (D. Tschumperlé, R. Deriche).
    IEEE Transactions on Pattern Analysis and Machine Intelligence,
    Vol 27, No 4, pp 506-517, April 2005.

    Copyright  : David Tschumperle - http://www.greyc.ensicaen.Fr/~dtschump/

  This software is governed by the CeCILL  license under French law and
  abiding by the rules of distribution of free software.  You can  use, 
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info". 
  
  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited
  liability. 
  
  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or 
  data to be ensured and,  more generally, to use and operate it in the 
  same conditions as regards security. 
  
  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ------------------------------------------------------------------------------*/

#include "StdAfx.h"

#define cimg_OS 2
#define cimg_display_type 0

#include "CImg.h"
#include "RGBFloat.h"

#if (( defined(_MSC_VER) && _MSC_VER<=1200 ) || defined(__DMC__))
#define std
#endif
using namespace cimg_library;

// Do one iteration of a Curvature-preserving PDE's.
//--------------------------------------------------
template <typename T, typename t>
CImg<T> &blur_anisotropicPDE(CImg<T> &img, const CImg<t> &G, const int iter, const int nb_iter, const bool curv_pres = true,
                             const float amplitude = 10.F, const float dl = 0.8f, const float da = 30.0f,
                             const float gauss_prec = 2.F, const unsigned int interpolation = 0,
                             const bool fast_approx = true) {
    // Check arguments and init variables
    if (img.is_empty())
        throw CImgArgumentException("GREYCstoration : Specified input image is empty.");
    if (amplitude == 0)
        return img;

    CImg<float> dest(img.width, img.height, 1, img.dim, 0), tmp(img.dim), W(img.width, img.height, 1, 3);
    const float sqrt2amplitude = std::sqrt(2.F * amplitude);
    const int dx1 = img.dimx() - 1,
              dy1 = img.dimy() - 1;
//    int counter = 0; 
    int N = 0;
//    const int countermax = (int)(img.width * img.height * (360 / da));

    for (float theta = 360 % (int)da / 2.F; theta < 360; theta += da, N++) {
        const float
            thetar = (float)(theta * cimg::PI / 180.F),
            vx = std::cos(thetar),
            vy = std::sin(thetar);

        const t *pa = G.ptr(0, 0, 0, 0), *pb = G.ptr(0, 0, 0, 1), *pc = G.ptr(0, 0, 0, 2);
        t *pd0 = W.ptr(0, 0, 0, 0), *pd1 = W.ptr(0, 0, 0, 1), *pd2 = W.ptr(0, 0, 0, 2);
        cimg_mapXY( G, xg, yg ) {
            const t
                a = *pa++, b = *pb++, c = *pc++,
                u = a * vx + b * vy, v = b * vx + c * vy,
                n = (t)std::sqrt(1e-5 + u * u + v * v),
                dln = dl / n;
            *pd0++ = u * dln;
            *pd1++ = v * dln;
            *pd2++ = n;
        }

        cimg_mapXY( img, x, y ) {
//            if (!((counter++) % 200000)) {
//                const unsigned int pc = (unsigned int)(100.0 * (counter + iter * countermax) / (nb_iter * countermax));
                //            std::fprintf(stderr,"\r- Processing : %u %% (iteration %u)              ",pc,iter+1);
//            }

            tmp.fill(0);
            const t cu = W(x, y, 0, 0), cv = W(x, y, 0, 1), n = W(x, y, 0, 2);
            const float
                fsigma = (float)(n * sqrt2amplitude),
                length = gauss_prec * fsigma,
                fsigma2 = 2 * fsigma * fsigma;
            float l, pu = cu, pv = cv, X = (float)x, Y = (float)y;

            if (fast_approx) {
                unsigned int S = 0;
                switch (interpolation) {
                    case 0: // Nearest-neighbor interpolation
                        for (l = 0; l < length; ) {
                            const float
                                Xn = X < 0 ? 0 : X >= dx1 ? dx1 : X,
                                Yn = Y < 0 ? 0 : Y >= dy1 ? dy1 : Y;
                            const int xi = (int)lround(Xn), yi = (int)lround(Yn);
                            t u = W(xi, yi, 0, 0), v = W(xi, yi, 0, 1);
                            if (pu * u + pv * v < 0) {
                                u = -u;
                                v = -v;
                            }
                            cimg_mapV( img, k )
                                tmp[k] += (t)img(xi, yi, 0, k);
                            X += pu = u;
                            Y += pv = v;
                            ++S;
                            l += dl;
                        }
                        break;
                    case 1: // Linear interpolation
                        for (l = 0; l < length; ) {
                            t u = (t)W.linear_pix2d(X, Y, 0, 0), v = (t)W.linear_pix2d(X, Y, 0, 1);
                            if (pu * u + pv * v < 0) {
                                u = -u;
                                v = -v;
                            }
                            cimg_mapV( img, k )
                                tmp[k] += (t)img.linear_pix2d(X, Y, 0, k);
                            X += pu = u;
                            Y += pv = v;
                            ++S;
                            l += dl;
                        }
                        break;
                    default: // 2nd-order Runge-kutta interpolation
                        for (l = 0; l < length; ) {
                            t u0 = (t)(0.5F * dl * W.linear_pix2d(X, Y, 0, 0)), v0 = (t)(0.5F * dl * W.linear_pix2d(X, Y, 0, 1));
                            if (pu * u0 + pv * v0 < 0) {
                                u0 = -u0;
                                v0 = -v0;
                            }
                            t u = (t)W.linear_pix2d(X + u0, Y + v0, 0, 0), v = (t)W.linear_pix2d(X + u0, Y + v0, 0, 1);
                            if (pu * u + pv * v < 0) {
                                u = -u;
                                v = -v;
                            }
                            cimg_mapV( img, k )
                                tmp[k] += (t)img.linear_pix2d(X, Y, 0, k);
                            X += pu = u;
                            Y += pv = v;
                            ++S;
                            l += dl;
                        }
                        break;
                }
                if (S > 0)
                    cimg_mapV( dest, k )
                        dest(x, y, 0, k) += tmp[k] / S;
                else
                    cimg_mapV( dest, k )
                        dest(x, y, 0, k) += (t)img(x, y, 0, k);
            } else {
                float S = 0;
                switch (interpolation) {
                    case 0: // Nearest-neighbor interpolation
                        for (l = 0; l < length; ) {
                            const float
                                coef = std::exp(-l * l / fsigma2),
                                Xn = X < 0 ? 0 : X >= dx1 ? dx1 : X,
                                Yn = Y < 0 ? 0 : Y >= dy1 ? dy1 : Y;
                            const int xi = (int)lround(Xn), yi = (int)lround(Yn);
                            t u = W(xi, yi, 0, 0), v = W(xi, yi, 0, 1);
                            if (pu * u + pv * v < 0) {
                                u = -u;
                                v = -v;
                            }
                            cimg_mapV( img, k)
                                tmp[k] += (t)(coef * img(xi, yi, 0, k));
                            X += pu = u;
                            Y += pv = v;
                            S += coef;
                            l += dl;
                        }
                        break;
                    case 1: // Linear interpolation
                        for (l = 0; l < length; ) {
                            const float coef = std::exp(-l * l / fsigma2);
                            t u = (t)W.linear_pix2d(X, Y, 0, 0), v = (t)W.linear_pix2d(X, Y, 0, 1);
                            if (pu * u + pv * v < 0) {
                                u = -u;
                                v = -v;
                            }
                            cimg_mapV( img, k )
                                tmp[k] += (t)(coef * img.linear_pix2d(X, Y, 0, k));
                            X += pu = u;
                            Y += pv = v;
                            S += coef;
                            l += dl;
                        }
                        break;
                    default: // 2nd-order Runge-kutta interpolation
                        for (l = 0; l < length; ) {
                            const float coef = std::exp(-l * l / fsigma2);
                            t u0 = (t)(0.5F * dl * W.linear_pix2d(X, Y, 0, 0)), v0 = (t)(0.5F * dl * W.linear_pix2d(X, Y, 0, 1));
                            if (pu * u0 + pv * v0 < 0) {
                                u0 = -u0;
                                v0 = -v0;
                            }
                            t u = (t)W.linear_pix2d(X + u0, Y + v0, 0, 0), v = (t)W.linear_pix2d(X + u0, Y + v0, 0, 1);
                            if (pu * u + pv * v < 0) {
                                u = -u;
                                v = -v;
                            }
                            cimg_mapV(img,k)
                                tmp[k] += (t)(coef * img.linear_pix2d(X, Y, 0, k));
                            X += pu = u;
                            Y += pv = v;
                            S += coef;
                            l += dl;
                        }
                        break;
                }
                if (S > 0)
                    cimg_mapV( dest, k )
                        dest(x, y, 0, k) += tmp[k] / S;
                else
                    cimg_mapV( dest, k )
                        dest(x, y, 0, k) += (t)img(x, y, 0, k);
            }
        }
    }
    const float *ptrs = dest.data + dest.size();
    cimg_map( img, ptrd, T )
        *ptrd = (T)(*--ptrs / N);
    return img;
}

// Do one iteration of Shock-Filter PDE
//--------------------------------------
template <typename T, typename t>
CImg<T> &shock_filterPDE(CImg<T> &img, const CImg<t> &G, const float dt = 10.F, const float edge = 1.F) {
    CImg<> val, vec, U(img.dimx(), img.dimy(), 1, 3), veloc(img);
    CImg_3x3( I, float );
    const float nedge = 0.5F * edge;
    cimg_mapXY( img, x, y ) {
        if (G(x, y, 0) == G(x, y, 1) && G(x, y, 1) == G(x, y, 2) && G(x, y, 2) == 0)
            U(x, y, 0) = U(x, y, 1) = U(x, y, 2) = 0;
        else {
            G.get_tensor(x, y).symeigen(val, vec);
            U(x, y, 0) = vec(0, 0);
            U(x, y, 1) = vec(0, 1);
            U(x, y, 2) = 1.F - std::pow(1.F + val[0] + val[1], -nedge);
        }
    }
    cimg_mapV( img, k )
        cimg_map3x3( img, x, y, 0, k, I ) {
            const float
                a = U(x, y, 0), b = U(x, y, 1), norm = U(x, y, 2),
                ixx = Inc + Ipc - 2 * Icc, iyy = Icn + Icp - 2 * Icc, ixy = 0.25f * (Inn + Ipp - Inp - Ipn),
                ixf = Inc - Icc, ixb = Icc - Ipc, iyf = Icn - Icc, iyb = Icc - Icp,
                itt = a * a * ixx + 2 * a * b * ixy + b * b * iyy,
                it = a * cimg::minmod(ixf, ixb) + b * cimg::minmod(iyf, iyb);
            veloc(x, y, k) = -norm * cimg::sign(itt) * cimg::abs(it);
        }
    const CImgStats stats(veloc, false);
    const float vmax = (float)cimg::max(cimg::abs(stats.min), cimg::abs(stats.max));
    if (vmax > 1e-5f)
        img += veloc * dt / vmax;
    return img;
}

BOOL DeNoise(RGBAFloat *sourcerows, RGBAFloat *destrows, const int width, const int height, const float alpha, const float sigma, const float p, const float anisotropy, const int nb_iter, const float dt) {
    ASSERT(alpha >= 0);
    ASSERT(sigma >= 0);
    ASSERT(p >= 0);
    ASSERT(anisotropy <=1 && anisotropy >=0);
    ASSERT(nb_iter > 0);
    ASSERT(dt >=0);
    // Copy the input buffer to a CImg buffer
    CImg<> dest(width, height, 1, 3, 0);
    cimg_mapXY( dest, x, y ) {
        RGBAFloat *srcpixel = sourcerows + y * width + x;
        dest(x, y, 0) = srcpixel->Red();
        dest(x, y, 1) = srcpixel->Green();
        dest(x, y, 2) = srcpixel->Blue();
    }
    const CImgStats stats(dest, false);
    const auto valmin = (float)stats.min;
    const auto valmax = (float)stats.max;
    /*
       // Some user settable properties.
       float alpha = m_alpha->GetValue();           // Noise scale (alpha >= 0). Default for image restoration is 0.5
       float sigma = m_sigma->GetValue();           // Geometry regularity (sigma >= 0). Default for image restoration is 1.0
       float p = m_p->GetValue();                   // Contour preservation for regularization (p >= 0). Default for image restoration is 0.9
       float anisotropy = m_anisotropy->GetValue(); // Regularization anisotropy (0 <= a <= 1). Default for image restoration is 0.2
       int   nb_iter = m_iter->GetValue();          // Number of regularization iterations (iter > 0). Default for image restoration is 1
       float dt = m_dt->GetValue();                 // Regularization strength for one iteration (dt >= 0). Default for image restoration is 50.0
    */
    // Some default values. Some of them could eventually be usefull as user settable properties.

    ///////////////////////////////////////////////////////////////////////////////////////////
    // The following loop is taken almost verbatim from Tschumfperle's greycstoration.cpp file
    // See comment at the begining of this file,
    bool stopflag = false;
    for (int iter = 0; iter < nb_iter && !stopflag; iter++) {

        // Compute smoothed structure tensor field G
        //-------------------------------------------
        CImg_3x3( I, float ); // float Ipp, Icp, Inp=0, Ipc, Icc, Inc=0, Ipn, Icn, Inn=0
        CImg<> G(dest.dimx(), dest.dimy(), 1, 3, 0); // width x height image with 1 plane of 3 channels floats initialized to 0;
        const CImg<> blur = dest.get_blur(alpha).normalize(0, 255); // alpha is noise scale, defaults to 0.5 for image restoration
        cimg_mapV( blur, k ) {
            cimg_map3x3( blur, x, y, 0 ,k, I) {
                const float ixf = Inc - Icc,
                            iyf = Icn - Icc,
                            ixb = Icc - Ipc,
                            iyb = Icc - Icp;
                G(x, y, 0) += 0.5F * (ixf * ixf + ixb * ixb);
                G(x, y, 1) += 0.25F * (ixf * iyf + ixf * iyb + ixb * iyf + ixb * iyb);
                G(x, y, 2) += 0.5F * (iyf * iyf + iyb * iyb);
            }
        }
        G.blur(sigma);

        // Compute tensor field sqrt(T)
        //------------------------------
        if (dt > 0) {
            constexpr int interp = 0;
            constexpr float gauss_prec = 2.F;
            constexpr bool fast_approx = true;
            constexpr float dl = 0.8F;
            constexpr float da = 30.0F;
            CImg<> T(G.dimx(), G.dimy(), 1, 3), val, vec;
            const float
                np1 = 0.5F * p,
                np2 = (float)(np1 / (1e-7 + 1 - anisotropy));
            float nmax = 0;
            cimg_mapXY( G, x, y ) {
                G.get_tensor(x, y).symeigen(val, vec);
                if (G(x, y, 0) == G(x, y, 1) && G(x, y, 1) == G(x, y, 2) && G(x, y, 2) == 0)
                    T(x, y, 0) = T(x, y, 1) = T(x, y, 2) = 0;
                else {
                    const float l1 = val[1],
                                l2 = val[0],
                                u = vec(1, 0),
                                v = vec(1, 1),
                                n1 = std::pow(1.F + l1 + l2, -np1),
                                n2 = std::pow(1.F + l1 + l2, -np2);
                    T(x, y, 0) = n1 * u * u + n2 * v * v;
                    T(x, y, 1) = u * v * (n1 - n2);
                    T(x, y, 2) = n1 * v * v + n2 * u * u;
                    if (n1 > nmax)
                        nmax = n1;
                }
            }
            T /= nmax;
            blur_anisotropicPDE(dest, T, iter, nb_iter, false, dt, dl, da, gauss_prec, interp, fast_approx);
        }
        if (float sdt = 0.F; sdt > 0) {
            constexpr float sp = 0.5F;
            shock_filterPDE(dest, G, sdt, sp);
            dest.cut(valmin, valmax);
        }
    }

    // Save result and exit
    //----------------------
    dest.cut(valmin, valmax);

    cimg_mapXY( dest, x, y ) {
        const int offset = y * width + x;
        RGBAFloat *destpixel = destrows + offset;
        destpixel->SetRed(dest(x, y, 0));
        destpixel->SetGreen(dest(x, y, 1));
        destpixel->SetBlue(dest(x, y, 2));
        destpixel->SetAlpha((sourcerows + offset)->Alpha());
    }
    return TRUE;
}
