// MH  6/30/2005  \Mart120\Plugin\Post\VideoSafe\Process.cpp

#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

#include "ColorBuf.inl"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    if (i == 0)
        return m_style;
    return nullptr;
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

#define	CHROMA_LIM      50.0		   // chroma amplitude limit
#define	COMPOS_LIM      110.0		// max IRE amplitude

// RGB to YIQ encoding matrix.

namespace {
    double NTSCcode_matrix[3][3] = {{0.2989, 0.5866, 0.1144}, {0.5959, -0.2741, -0.3218}, {0.2113, -0.5227, 0.3113}};
}

#define	NTSCPEDESTAL   7.5	// 7.5 IRE black pedestal
#define	NTSC_GAMMA     2.2f

// RGB to YUV encoding matrix.

namespace {
    double PALcode_matrix[3][3] = {{0.2989, 0.5866, 0.1144}, {-0.1473, -0.2891, 0.4364}, {0.6149, -0.5145, -0.1004}};
}

#define	PALPEDESTAL 0.0		  // no pedestal in PAL
#define	PALGAMMA    2.8f

#define SCALE	8192            // scale factor: do floats with int math
//#define WID	 1024              // FB dimensions
//#define HGT	 768

typedef struct {
    unsigned char r, g, b;
} Pixel;

/*
 * pix_decode: decode an integer pixel value into a floating-point
 *	intensity in the range [0, 1].
 *
 * pix_encode: encode a floating-point intensity into an integer
 *	pixel value.
 *
 * The code given here assumes simple linear encoding; you must change
 * these routines if you use a different pixel encoding technique.
 */

namespace {
    double pix_decode(const int v) {
        return (double)v / MAXPIX;
    }

    int pix_encode(const double v) {
        return fast_round((float)(v * MAXPIX));
    }
}

/*
 * build_tab: Build multiply lookup table.
 *
 * For each possible pixel value, decode value into floating-point
 * intensity.  Then do gamma correction required by the video
 * standard.  Scale the result by our fixed-point scale factor.
 * Then calculate 9 lookup table entries for this pixel value.
 *
 * We also calculate floating-point and scaled integer versions
 * of our limits here.  This prevents evaluating expressions every pixel
 * when the compiler is too stupid to evaluate constant-valued
 * floating-point expressions at compile time.
 *
 * For convenience, the limits are #defined using IRE units.
 * We must convert them here into the units in which YIQ
 * are measured.  The conversion from IRE to internal units
 * depends on the pedestal level in use, since as Y goes from
 * 0 to 1, the signal goes from the pedestal level to 100 IRE.
 * Chroma is always scaled to remain consistent with Y.
 */

void CustomPostPlugin::NTSCbuild_tab() {
    for (int pv = 0; pv <= MAXPIX; pv++) {
        const double f = SCALE * gc(pix_decode(pv));
        m_tab[0][0][pv] = fast_round((float)(f * NTSCcode_matrix[0][0]));
        m_tab[0][1][pv] = fast_round((float)(f * NTSCcode_matrix[0][1]));
        m_tab[0][2][pv] = fast_round((float)(f * NTSCcode_matrix[0][2]));
        m_tab[1][0][pv] = fast_round((float)(f * NTSCcode_matrix[1][0]));
        m_tab[1][1][pv] = fast_round((float)(f * NTSCcode_matrix[1][1]));
        m_tab[1][2][pv] = fast_round((float)(f * NTSCcode_matrix[1][2]));
        m_tab[2][0][pv] = fast_round((float)(f * NTSCcode_matrix[2][0]));
        m_tab[2][1][pv] = fast_round((float)(f * NTSCcode_matrix[2][1]));
        m_tab[2][2][pv] = fast_round((float)(f * NTSCcode_matrix[2][2]));
    }

    m_chroma_lim = CHROMA_LIM / (100. - NTSCPEDESTAL);
    m_compos_lim = (COMPOS_LIM - NTSCPEDESTAL) / (100. - NTSCPEDESTAL);

    m_ichroma_lim2 = fast_round((float)(m_chroma_lim * SCALE));
    m_ichroma_lim2 *= m_ichroma_lim2;
    m_icompos_lim = fast_round((float)(m_compos_lim * SCALE));
}

void CustomPostPlugin::PALbuild_tab() {
    for (int pv = 0; pv <= MAXPIX; pv++) {
        const double f = SCALE * gc(pix_decode(pv));
        m_tab[0][0][pv] = fast_round((float)(f * PALcode_matrix[0][0]));
        m_tab[0][1][pv] = fast_round((float)(f * PALcode_matrix[0][1]));
        m_tab[0][2][pv] = fast_round((float)(f * PALcode_matrix[0][2]));
        m_tab[1][0][pv] = fast_round((float)(f * PALcode_matrix[1][0]));
        m_tab[1][1][pv] = fast_round((float)(f * PALcode_matrix[1][1]));
        m_tab[1][2][pv] = fast_round((float)(f * PALcode_matrix[1][2]));
        m_tab[2][0][pv] = fast_round((float)(f * PALcode_matrix[2][0]));
        m_tab[2][1][pv] = fast_round((float)(f * PALcode_matrix[2][1]));
        m_tab[2][2][pv] = fast_round((float)(f * PALcode_matrix[2][2]));
    }

    m_chroma_lim = CHROMA_LIM / (100. - PALPEDESTAL);
    m_compos_lim = (COMPOS_LIM - PALPEDESTAL) / (100. - PALPEDESTAL);

    m_ichroma_lim2 = fast_round((float)(m_chroma_lim * SCALE));
    m_ichroma_lim2 *= m_ichroma_lim2;
    m_icompos_lim = fast_round((float)(m_compos_lim * SCALE));
}

BOOL CustomPostPlugin::Hot(ColorBuf *p) const {
    int r, g, b;
    int y, i, q;
    int y2, c2;
    double pr, pg, pb;
#if REDUCE_SAT
	double		py;
#endif
    double fy, fc, t, scale;
#if !FLAG_HOT
    static int prev_r = 0, prev_g = 0, prev_b = 0;
    static int new_r = 0, new_g = 0, new_b = 0;
#endif
    r = p->Red();
    g = p->Green();
    b = p->Blue();

    /*
     * Pixel decoding, gamma correction, and matrix multiplication
     * all done by lookup table.
     *
     * "i" and "q" are the two chrominance components;
     * they are I and Q for NTSC.
     * For PAL, "i" is U (scaled B-Y) and "q" is V (scaled R-Y).
     * Since we only care about the length of the chroma vector,
     * not its angle, we don't care which is which.
     */
    y = m_tab[0][0][r] + m_tab[0][1][g] + m_tab[0][2][b];
    i = m_tab[1][0][r] + m_tab[1][1][g] + m_tab[1][2][b];
    q = m_tab[2][0][r] + m_tab[2][1][g] + m_tab[2][2][b];

    /*
     * Check to see if the chrominance vector is too long or the
     * composite waveform amplitude is too large.
     *
     * Chrominance is too large if
     *
     *	sqrt(i^2, q^2)  >  chroma_lim.
     *
     * The composite signal amplitude is too large if
     *
     *	y + sqrt(i^2, q^2)  >  compos_lim.
     *
     * We avoid doing the sqrt by checking
     *
     *	i^2 + q^2  >  chroma_lim^2
     * and
     *	y + sqrt(i^2 + q^2)  >  compos_lim
     *	sqrt(i^2 + q^2)  >  compos_lim - y
     *	i^2 + q^2  >  (compos_lim - y)^2
     *
     */

    c2 = (long)i * i + (long)q * q;
    y2 = (long)m_icompos_lim - y;
    y2 *= y2;
    if (c2 <= m_ichroma_lim2 && c2 <= y2) /* no problems */
        return 0;

    /*
     * Pixel is hot, choose desired (compilation time controlled) strategy
     */
#if FLAG_HOT
	/*
	 * Set the hot pixel to black to identify it.
	 */
	p->r = p->g = p->b = 0;
#else /* FLAG_HOT */
    /*
     * Optimization: cache the last-computed hot pixel.
     */
    if (r == prev_r && g == prev_g && b == prev_b) {
        p->SetRed(new_r);
        p->SetGreen(new_g);
        p->SetBlue(new_b);
        return 1;
    }
    prev_r = r;
    prev_g = g;
    prev_b = b;

    /*
     * Get Y and chroma amplitudes in floating point.
     *
     * If your C library doesn't have hypot(), just use
     * hypot(a,b) = sqrt(a*a + b*b);
     *
     * Then extract linear (un-gamma-corrected) floating-point
     * pixel RGB values.
     */
    fy = (double)y / SCALE;
    fc = _hypot((double)i / SCALE, (double)q / SCALE);
    // fc = sqrt((double)i/SCALE*(double)i/SCALE + (double)q/SCALE*(double)q/SCALE); this was for OS9
    pr = pix_decode(r);
    pg = pix_decode(g);
    pb = pix_decode(b);

    /*
     * Reducing overall pixel intensity by scaling
     * R, G, and B reduces Y, I, and Q by the same factor.
     * This changes luminance but not saturation, since saturation
     * is determined by the chroma/luminance ratio.
     *
     * On the other hand, by linearly interpolating between the
     * original pixel value and a grey pixel with the same
     * luminance (R=G=B=Y), we change saturation without
     * affecting luminance.
     */

#if !REDUCE_SAT
    /*
     * Calculate a scale factor that will bring the pixel
     * within both chroma and composite limits, if we scale
     * luminance and chroma simultaneously.
     *
     * The calculated chrominance reduction applies to the
     * gamma-corrected RGB values that are the input to
     * the RGB-to-YIQ operation.  Multiplying the
     * original un-gamma-corrected pixel values by
     * the scaling factor raised to the "gamma" power
     * is equivalent, and avoids calling gc() and inv_gc()
     * three times each.
     */
    scale = m_chroma_lim / fc;
    t = m_compos_lim / (fy + fc);
    if (t < scale)
        scale = t;
    scale = hash_math::pow(scale, (double)m_gamma);

    r = pix_encode(scale * pr);
    g = pix_encode(scale * pg);
    b = pix_encode(scale * pb);
#else /* REDUCE_SAT */
	/*
	 * Calculate a scale factor that will bring the pixel
	 * within both chroma and composite limits, if we scale
	 * chroma while leaving luminance unchanged.
	 *
	 * We have to interpolate gamma-corrected RGB values,
	 * so we must convert from linear to gamma-corrected
	 * before interpolation and then back to linear afterwards.
	 */
	scale = m_chroma_lim / fc;
	t = (m_compos_lim - fy) / fc;
	if (t < scale)
		scale = t;

	pr = gc(pr);
	pg = gc(pg);
	pb = gc(pb);
	py = pr * code_matrix[0][0] + pg * code_matrix[0][1]
		+ pb * code_matrix[0][2];
   r = pix_encode(inv_gc(py + scale * (pr - py)));
   g = pix_encode(inv_gc(py + scale * (pg - py)));
   b = pix_encode(inv_gc(py + scale * (pb - py)));
#endif /* REDUCE_SAT */

    new_r = r;
    new_g = g;
    new_b = b;
    p->SetRed(new_r);
    p->SetGreen(new_g);
    p->SetBlue(new_b);
#endif /* FLAG_HOT */
    return 1;
}

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    //COMEBACK make it process as RGBFloat instead of colorbuf
    if (m_style->GetValue() == STYLE_NTSC && m_tabbuilt != NTSC_TAB) {
        m_gamma = NTSC_GAMMA;
        NTSCbuild_tab();
    } else if (m_tabbuilt != PAL_TAB) {
        m_gamma = PALGAMMA;
        PALbuild_tab();
    }
    //get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy(); //copys background
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    const int count = width * height;
    RGBAFloat *inptr = inbuffer->GetRGBAFloatData();
    RGBAFloat *dstptr = outbuffer->GetRGBAFloatData();
    for (int p = 0; p < count; ++p, ++dstptr, ++inptr) {
        ColorBuf newcolor(fast_round(inptr->m_color.m_red * MAXCOLOR), fast_round(inptr->m_color.m_green * MAXCOLOR), fast_round(inptr->m_color.m_blue * MAXCOLOR));
        Hot(&newcolor);

        dstptr->m_color = newcolor.GetNormalizedRGBFloat();
        dstptr->m_alpha = inptr->m_alpha;
    }

    output->SetBuffer(outbuffer);
    return TRUE;
}
