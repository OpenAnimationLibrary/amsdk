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
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"


#if (( defined(_MSC_VER) && _MSC_VER<=1200 ) || defined(__DMC__))
#define std
#endif

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_alpha;
        case 1:
            return m_sigma;
        case 2:
            return m_p;
        case 3:
            return m_anisotropy;
        case 4:
            return m_iter;
        case 5:
            return m_dt;
        default:
            return nullptr;
    }
}

PostPlugin::Styles CustomPostPlugin::GetAllowedInputBufferStyles() {
    return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs() {
    return 1;
}

BOOL DeNoise(RGBAFloat *sourcerows, RGBAFloat *destrows, int width, int height, float alpha = 0.5F, float sigma = 1.F, float p = 0.9F, float anisotrophy = 0.2F, int nb_iter = 1, float dt = 50.F);

bool CustomPostPlugin::Process(const Time time, HBufferShortcut *inputs, HBufferShortcut *output) {
    // get bitmap info
    HRGBAFloatBuffer *inbuffer = inputs->GetRGBAFloatBuffer(time);
    const int width = inbuffer->GetWidth(), height = inbuffer->GetHeight();
    RGBAFloat *sourcerows = inbuffer->GetRGBAFloatData();

    auto *outbuffer = (HRGBAFloatBuffer *)inbuffer->MakeBlankCopy();
    RGBAFloat *destrows = outbuffer->GetRGBAFloatData();

    DeNoise(sourcerows, destrows, width, height,
            m_alpha->GetValue(), // Noise scale (alpha >= 0). Default for image restoration is 0.5
            m_sigma->GetValue(), // Geometry regularity (sigma >= 0). Default for image restoration is 1.0
            m_p->GetValue(), // Contour preservation for regularization (p >= 0). Default for image restoration is 0.9
            m_anisotropy->GetValue(), // Regularization anisotropy (0 <= a <= 1). Default for image restoration is 0.2
            m_iter->GetValue(), // Number of regularization iterations (iter > 0). Default for image restoration is 1
            m_dt->GetValue() // Regularization strength for one iteration (dt >= 0). Default for image restoration is 50.0
    );

    output->SetBuffer(outbuffer);
    return TRUE;
}
