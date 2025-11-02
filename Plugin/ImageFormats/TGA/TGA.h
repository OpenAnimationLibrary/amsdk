// RC  4/24/2002  \HRandy95\Include\TGA.H
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

//#define __TGA_H

#include "DataType.h"

#define TGA_MAPRGBTYPE        1
#define TGA_RAWRGBTYPE        2
#define TGA_RAWMONOTYPE       3
#define TGA_MAPENCODETYPE     9
#define TGA_RAWENCODETYPE     10
#define TGA_MONOENCODETYPE    11

#define COLOR                 0x01
#define MAPPED                0x02
#define RLENCD                0x04
#define INTERL                0x08
#define FOURWY                0x10
#define GREYSC                0x20

struct TGA_ImageHeader {
    UBYTE idlength, // length of identifier string
          comaptype, // 0 = nomap
          imgtype, // image type (1,2,3,9,10,11)
          index_lo, index_hi, // index of first colormap entry
          length_lo, length_hi, // length of colormap (number of entries)
          cosize, // length of colormap entry
          x_org_lo, x_org_hi, // X origin of image
          y_org_lo, y_org_hi, // Y origin of image
          width_lo, width_hi, // width of image
          height_lo, height_hi, // height of image
          pixelsize; // pixel size (8,16,24)
    UBYTE attbits:4,rsrvd:1,orgbit:1,intrlve:2;
    /*    
        UBYTE      attbits : 4,          // number of attribes bits per pixel
                   rsrvd   : 1,          // reserved
                   orgbit  : 1,          // origin bit (0=lower, 1=upperleft)
                   intrlve : 2;          // interleaving flag
    */
};

#define SIZEOFHEADER          18
#define DEPTHOFFSET           16
#define COMPRESSEDOFFSET      2
#define INDEXFIELD            3L
#define LENGTHFIELD           5L
#define SIZEFIELD             7L
#define XORIGIN               8L

struct TGA_ImageFooter {
    int extoffset;
    int devoffset;
    char signature[18];
};

#define SIZEOFFOOTER          26
#define KEYCOLOR              470
#define GAMMA                 478
#define ATTRTYPE              494

#define HASH MakeID('H','A','S','H')
#define DEVREV                5
#define DEVREVWITHOUTASPECT   3
#define TBACK                 0x01
#define SHADOWMASK            0xFE

#define MAXSHADOW             127

class TGABuf {
    union {
        struct {
            UBYTE red, green, blue, alpha;
        } values;

        UINT color{0};
    };

public:
    [[nodiscard]] UBYTE Red() const {
        return values.red;
    }

    [[nodiscard]] UBYTE Green() const {
        return values.green;
    }

    [[nodiscard]] UBYTE Blue() const {
        return values.blue;
    }

    [[nodiscard]] UBYTE Alpha() const {
        return values.alpha;
    }

    [[nodiscard]] UINT Color() const {
        return color;
    }

    void SetRed(const UBYTE red) {
        values.red = red;
    }

    void SetGreen(const UBYTE green) {
        values.green = green;
    }

    void SetBlue(const UBYTE blue) {
        values.blue = blue;
    }

    void SetAlpha(const UBYTE alpha) {
        values.alpha = alpha;
    }

    void SetColor(const UINT pcolor) {
        color = pcolor;
    }

    void SetRedBack(const bool flag) {
        flag ? (values.red |= TBACK) : values.red &= ~TBACK;
    }

    void SetGreenBack(const bool flag) {
        flag ? (values.green |= TBACK) : values.green &= ~TBACK;
    }

    void SetBlueBack(const bool flag) {
        flag ? (values.blue |= TBACK) : values.blue &= ~TBACK;
    }
};
