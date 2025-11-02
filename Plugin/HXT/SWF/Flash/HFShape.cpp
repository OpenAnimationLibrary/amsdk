// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.
// Lee Thomason: fill code, bitmaps, matrix math, FRGBA bug "fix" 11/1999.

/****************************************************************************************

				File Summary: HFShape.cpp

  This source file contains the definition for high-level shape functions,

		Class						Member Function

	HFShape						HFShape(int, int, int, int);
								~HFShape();
								void SetLineColor(const FRGBA&);
								void SetSolidFill(const FRGBA&);
								int SetBitmapFillJpeg(int, int, void*, int);
								int	SetBitmapFillLossless(int, int, int, int, bool, void*, void*);
								void SetLinearFill(const FRGBA&, const FRGBA&);
								void SetLinearFillCenter(int, int);
								void AddLinearFillColor(U8, const FRGBA&);
								void SetRadialFill(const FRGBA&, const FRGBA&);
								void SetRadialFillCenter(int, int);
								void AddRadialFillColor(U8, const FRGBA&);
								void SetBounds(int, int, int, int);
								bool HasMatrix();
								FMatrix* CreateMatrix();
								void FillShapeHeader(std::list<FObj*>*, FDTDefineShape3*);

****************************************************************************************/

#include "StdAfx.h"
#include "HFShape.h"
#include "HFColors.h"
#include "FDTBitmaps.h"

#include "FFixed.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFShape  ---------------------------------------------------------------

HFShape::HFShape(int xmin, int ymin, int xmax, int ymax) : bounds(xmin, ymin, xmax, ymax) // bounding rectangle
{
    solidFillColor = White_RGBA;
    lineColor = Black_RGBA;

    colorFillID = 0x01; // default ID for solid color fill
    lineWidth = 20; // default line width: 20 twips(1 pixel)
    lineStyleID = 0x01; // default ID for line style

    fillType = SOLID_FILL; // default fill type: solid color fill

    memset(&bitmapFill, 0, sizeof(BitmapData)); // allocate enough memory for bitmap fill
    fillMatrix = new FMatrix(false, 0, 0, false, 0, 0, 0, 0);
    fillGradient = new FGradient();

    translateX = translateY = 0;
    rotation = 0;
    scaleX = fixed_1;
    scaleY = fixed_1;

}

HFShape::~HFShape() {
    delete fillMatrix;
    delete fillGradient;
}

//
void HFShape::SetLineColor(const FRGBA &_lineColor) {
    lineColor = _lineColor;
    defineWritten = false;
}

//
void HFShape::SetSolidFill(const FRGBA &fillColor) {
    solidFillColor = fillColor;
    defineWritten = false;
}

//
int HFShape::SetBitmapFillJpeg(const int bitmap_X, const int bitmap_Y, const void *data, const int JPEG_size) {
    defineWritten = false;

    fillType = BITMAP_FILL; // set shape's fill type

    bitmapFill.type = JPEG; // set bitmap's type
    bitmapFill.bitmap_X = bitmap_X;
    bitmapFill.bitmap_Y = bitmap_Y;
    // 	bitmapFill.data		= data;
    bitmapFill.JPEG_size = JPEG_size;

    bitmapFill.fdt = new FDTDefineBitsJPEG2((U8 *)data, // address of image data
                                            JPEG_size // and how big it is												     );
    );

    return bitmapFill.fdt->ID();

}

//
int HFShape::SetBitmapFillLossless(const int format, const int bitmap_X, const int bitmap_Y, const int numPaletteEntries, const bool alpha, const void *bitmap, const void *palette) {
    defineWritten = false;
    fillType = BITMAP_FILL; // set shape's fill type

    bitmapFill.type = LOSSLESS; // set bitmap's type
    bitmapFill.bitmap_X = bitmap_X;
    bitmapFill.bitmap_Y = bitmap_Y;
    // 	bitmapFill.data		= bitmap;

    bitmapFill.fdt = new FDTDefineBitsLosslessBase(format, // format	
                                                   bitmap_X, // width
                                                   bitmap_Y, // height
                                                   numPaletteEntries, // number of palette entries
                                                   palette, // address of palette
                                                   bitmap, // address of image data
                                                   alpha);

    return bitmapFill.fdt->ID();
}

//
void HFShape::SetLinearFill(const FRGBA &a, const FRGBA &b) {
    defineWritten = false;

    SetLinearFillCenter((bounds.Xmin() + bounds.Xmax()) / 2, (bounds.Ymin() + bounds.Ymax()) / 2);

    AddLinearFillColor(0, a);
    AddLinearFillColor(255, b);
}

//
void HFShape::SetLinearFillCenter(const int centerX, const int centerY) {
    defineWritten = false;
    fillType = LINEAR_GRADIENT_FILL;
    const double xScale = bounds.Width();
    const double yScale = bounds.Height();

    delete fillMatrix;
    fillMatrix = new FMatrix(true,
                             xScale,
                             yScale,
                             false,
                             0,
                             0, // no rotate
                             centerX,
                             centerY);
    defineWritten = false;
}

//
void HFShape::AddLinearFillColor(const U8 ratio, const FRGBA &linearFillColor) {
    defineWritten = false;
    fillType = LINEAR_GRADIENT_FILL;

    // Construct a FColor with alpha value.
    auto *color = new FColor(linearFillColor.red, linearFillColor.green, linearFillColor.blue, linearFillColor.alpha);

    if (!fillGradient) {
        fillGradient = new FGradient();
    }

    fillGradient->Add(new FGradRecord(ratio, color));
    defineWritten = false;
}

//
void HFShape::SetRadialFill(const FRGBA &a, const FRGBA &b) {
    defineWritten = false;
    SetRadialFillCenter((bounds.Xmin() + bounds.Xmax()) / 2, (bounds.Ymin() + bounds.Ymax()) / 2);
    AddRadialFillColor(0, a);
    AddRadialFillColor(255, b);
}

//
void HFShape::SetRadialFillCenter(const int centerX, const int centerY) {
    defineWritten = false;
    fillType = RADIAL_GRADIENT_FILL;
    const double xScale = fixed_1 * hash_math::sqrt((float)bounds.Width() * bounds.Width() + bounds.Height() * bounds.Height()) / 32768;
    const double yScale = xScale;

    delete fillMatrix;
    fillMatrix = new FMatrix(true,
                             xScale,
                             yScale,
                             false,
                             0,
                             0, // no rotate
                             centerX,
                             centerY);
    defineWritten = false;
}

//
void HFShape::AddRadialFillColor(const U8 ratio, const FRGBA &radialFillColor) {
    defineWritten = false;
    fillType = RADIAL_GRADIENT_FILL;

    // Construct a FColor with alpha value.
    auto *color = new FColor(radialFillColor.red, radialFillColor.green, radialFillColor.blue, radialFillColor.alpha);

    if (!fillGradient) {
        fillGradient = new FGradient();
    }

    FLASHASSERT(fillGradient);

    fillGradient->Add(new FGradRecord(ratio, color));

    defineWritten = false;
}

//
void HFShape::SetBounds(const int xmin, const int ymin, const int xmax, const int ymax) {
    bounds = FRect(xmin, ymin, xmax, ymax);
}

//
bool HFShape::HasMatrix() {
    return translateX || translateY || rotation || scaleX != fixed_1 || scaleY != fixed_1;
}

//
FMatrix *HFShape::CreateMatrix() {
    const double DegToRad = 3.14159265358979323 / 180.0; // pi/2

    const int centerX = int((bounds.Xmin() + bounds.Xmax()) / 2.0);
    const int centerY = int((bounds.Ymin() + bounds.Ymax()) / 2.0);
    const float sX = FixedToFloat(scaleX);
    const float sY = FixedToFloat(scaleY);
    const float rot = FixedToFloat(rotation);

    // 	float skewX = 1.0;
    // 	float skewY = 1.0;

    // We want to rotate the matrix about its own center, not the origin. So it is necessary
    // to move the object to the origin, rotate it, and move it back.

    const float deltaX = centerX * cos(DegToRad * rot) - centerY * sin(DegToRad * rot) - centerX;
    const float deltaY = centerX * sin(DegToRad * rot) + centerY * cos(DegToRad * rot) - centerY;

    // This is the code from David Michie to make a swf matrix (no skew)

    //   Assign(cos(rx)*sx,  sin(rx)*sx,  0.0,
    //          cos(ry)*sy,  sin(ry)*sy,  0.0,
    //          x,           y,           1.0);

    // lee: using the Folef and Van Damme gives a slightly different
    // matrix (a matrix rotated from Flash's, actually). So converting the
    // above given that cos(x+90) = -sin(x) & sin(x+90) = cos x,
    // gives the matrix below.

    // make the matrix:
    //	| a b tx|
    //	| c d ty|
    //

    const float a = cos(DegToRad * rot) * sX;
    const float b = sin(DegToRad * rot) * sX;
    const float c = -sin(DegToRad * rot) * sY;
    const float d = cos(DegToRad * rot) * sY;

    return new FMatrix(true, FloatToFixed(a), FloatToFixed(d), true, FloatToFixed(b), FloatToFixed(c), translateX - int(deltaX * sX), translateY - int(deltaY * sY));
}

//
void HFShape::FillShapeHeader(std::list<FObj *> *objList, FDTDefineShape3 *shapeTag) {
    FFillStyle *fill = nullptr;
    if (fillType == BITMAP_FILL) // bitmap fill
    {
        FLASHASSERT(bitmapFill.fdt);
        objList->push_back(bitmapFill.fdt);

        //This first matrix seems to be required by Flash.
        auto *matrix0 = new FMatrix(true, 10 * Fixed1, 10 * Fixed1, false, 0, 0, 0, 0);
        FFillStyle *fill0 = new FFillStyleBitmap(false, 0xffff, matrix0);

        // This is the actual bitmap.
        auto *matrix1 = new FMatrix(true, // has scale?
                                    Fixed1 * bounds.Width() / bitmapFill.bitmap_X,
                                    Fixed1 * bounds.Height() / bitmapFill.bitmap_Y,
                                    false, // no skew.
                                    0,
                                    0,
                                    bounds.Xmin(), // translate to the origin of the rectangle
                                    bounds.Ymin());
        // This is the real bitmap fill.
        fill = new FFillStyleBitmap(false, // not tiled
                                    bitmapFill.fdt->ID(), // use the bitmap we just created
                                    matrix1 // use the matrix we just created
        );

        // Now the fillstyles (bitmaps) are added to the FDTDefineShape3.
        shapeTag->AddFillStyle(fill0);
        bitmapFill.fdt = nullptr;
    } else if (fillType == SOLID_FILL) // solid fill
    {
        // Construct a FColor with alpha value.
        fill = new FFillStyleSolid(new FColor(solidFillColor.red, solidFillColor.green, solidFillColor.blue, solidFillColor.alpha));
    } else if (fillType == LINEAR_GRADIENT_FILL) // linear gradient fill
    {
        fill = new FFillStyleGradient(true, fillMatrix, fillGradient);
        fillMatrix = nullptr;
        fillGradient = nullptr;
    } else if (fillType == RADIAL_GRADIENT_FILL) // radial gradient fill
    {
        fill = new FFillStyleGradient(false, fillMatrix, fillGradient);
        fillMatrix = nullptr;
        fillGradient = nullptr;
    }

    // Set fill style and line style.
    if (fill) {
        colorFillID = shapeTag->AddFillStyle(fill);
    }

    if (lineWidth > 0) {
        lineStyleID = shapeTag->AddLineStyle(lineWidth, new FColor(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha));
    }

    //Since we are done creating fill and line styles, indicate so:
    shapeTag->FinishStyleArrays();
}
