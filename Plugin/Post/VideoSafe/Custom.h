// MH  6/30/2005  \Mart120\Plugin\Post\VideoSafe\Custom.h
#pragma once

#include "PostPlug.h"
#include "resource.h"
//#include "ColorBtn.h"
#include "SDK/HPropert.h"

constexpr int MAXPIX = 255;            /* white value */

class CustomPostPlugin final : public PostPlugin {
public:
    HTypeProperty *m_style;

    enum { NO_TAB, NTSC_TAB, PAL_TAB };

    int m_tabbuilt; //
    int m_tab[3][3][MAXPIX + 1]; // multiply lookup table
    double m_chroma_lim; // chroma limit 
    double m_compos_lim; // composite amplitude limit
    int m_ichroma_lim2; // chroma limit squared (scaled integer)
    int m_icompos_lim; // composite amplitude limit (scaled integer)
    float m_gamma;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomPostPlugin(HTreeObject *treeobject);
    ~CustomPostPlugin() override;
    CustomPostPlugin(const CustomPostPlugin&) = delete;
    CustomPostPlugin &operator= (const CustomPostPlugin&) = delete; 
    CustomPostPlugin(CustomPostPlugin &&) = delete; 
    CustomPostPlugin &operator=(CustomPostPlugin &&) = delete; 

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_POST;
    }

    UINT GetNameID() noexcept override {
        return IDS_POSTNAME;
    }

    const char *GetClassName() override {
        return "Hash\\VideoSafe";
    }

    // PROCESSING
    //virtual HProperty        *GetPropertyAt( int i );
    //virtual BOOL              OnPtrMessage( PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time );

    /*
     * gc: apply the gamma correction specified for this video standard.
     * inv_gc: inverse function of gc.
     *
     * These are generally just a call to pow(), but be careful!
     * Future standards may use more complex functions.
     * (e.g. SMPTE 240M's "electro-optic transfer characteristic").
     */
    [[nodiscard]] double gc(const double x) const {
        return hash_math::pow(x, 1. / m_gamma);
    }

    [[nodiscard]] double inv_gc(const double x) const {
        return hash_math::pow(x, (double)m_gamma);
    }

    void NTSCbuild_tab();
    void PALbuild_tab();
    BOOL Hot(ColorBuf *p) const;

    HProperty *GetPropertyAt(int i) override;
    bool Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output) override;
    int GetNumInputs() override;
    Styles GetAllowedInputBufferStyles() override;

    // CUSTOM POST FUNCTIONS
};
