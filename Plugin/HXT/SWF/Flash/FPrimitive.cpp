// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FPrimitive.cpp

  This source file contains the definition for all low-level primitive-related functions,
  grouped by classes:

		Class						Member Function
  
	FColor						FColor(U32, U32, U32);
								FColor(U32, U32, U32, U32);
								FColor(FRGB);
								FColor(FRGBA);
								void WriteToSWFStream(FSWFStream*, int);

	FMatrix						FMatrix(U32, SFIXED, SFIXED,
										U32, SFIXED, SFIXED,
										SCOORD , SCOORD);
								Matrix();
								U32 MinBits(S32, S32);
								void WriteToSWFStream(FSWFStream*);

	FRect						FRect(SCOORD, SCOORD, SCOORD, SCOORD);
								unsigned long MinBits();
								void WriteToSWFStream(FSWFStream *);

	FString						FString(const U8*);
								void WriteToSWFStream(FSWFStream*, bool);

****************************************************************************************/

#include "StdAfx.h"
#include "FPrimitive.h"
#include "FSWFStream.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  FColor  ----------------------------------------------------------------

FColor::FColor(const U32 _red, const U32 _green, const U32 _blue) : red(_red), green(_green), blue(_blue), alpha(0xff), alphaT(false) {}

FColor::FColor(const U32 _red, const U32 _green, const U32 _blue, const U32 _alpha) : red(_red), green(_green), blue(_blue), alpha(_alpha), alphaT(true) {}

FColor::FColor(const FRGB rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue), alpha(0xff), alphaT(false) {}

FColor::FColor(const FRGBA rgba) : red(rgba.red), green(rgba.green), blue(rgba.blue), alpha(rgba.alpha), alphaT(true) {}

void FColor::WriteToSWFStream(FSWFStream *_SWFStream) const {
    //no filling, everything should already be byte aligned
    _SWFStream->WriteByte(red);
    _SWFStream->WriteByte(green);
    _SWFStream->WriteByte(blue);
    if (alphaT) {
        _SWFStream->WriteByte(alpha);
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//  --------  FMatrix  ---------------------------------------------------------------

//	The Matrix class constructor
FMatrix::FMatrix(const U32 _hasScale, const SFIXED _scaleX, const SFIXED _scaleY, const U32 _hasRotate, const SFIXED _rotateSkew0, const SFIXED _rotateSkew1, const SCOORD _translateX, const SCOORD _translateY) {

    hasScale = _hasScale;

    scaleX = _scaleX;
    scaleY = _scaleY;

    hasRotate = _hasRotate;
    rotateSkew0 = _rotateSkew0;
    rotateSkew1 = _rotateSkew1;

    translateX = _translateX;
    translateY = _translateY;

    nScaleBits = MinBits(scaleX, scaleY);
    nRotateBits = MinBits(rotateSkew0, rotateSkew1);
    nTranslateBits = MinBits(translateX, translateY);

    identity = false;
}

//	Creates an identity matrix.

FMatrix::FMatrix() {

    identity = true;

}

//	Calculates the minimum number of bits necessary to represent the given 2 signed numbers.
//	This is used to calculate the 3 nbit fields in the Matrix class.  Takes two signed 
//	numbers, sees which has the greatest magnitude, and calls FileWrite::MinBits with the 
//	unsigned magnitude of the larger number and the sign flag equal to 1 to account for the 
//	fact that the numbers are signed.

U32 FMatrix::MinBits(const S32 x, const S32 y) const {

    const int xAbs = abs(x);
    const int yAbs = abs(y);

    if (xAbs > yAbs)
        return FSWFStream::MinBits((U32)xAbs, 1);
    return FSWFStream::MinBits((U32)yAbs, 1);

}

//	Writes the Matrix to the given _SWFStream.

void FMatrix::WriteToSWFStream(FSWFStream *_SWFStream) const {

    if (identity) {

        _SWFStream->WriteByte(0);

    } else {

        _SWFStream->WriteBits(hasScale, 1);

        if (hasScale) {

            _SWFStream->WriteBits(nScaleBits, 5);
            _SWFStream->WriteBits((U32)scaleX, nScaleBits);
            _SWFStream->WriteBits((U32)scaleY, nScaleBits);

        }

        _SWFStream->WriteBits(hasRotate, 1);

        if (hasRotate) {

            _SWFStream->WriteBits(nRotateBits, 5);
            _SWFStream->WriteBits((U32)rotateSkew0, nRotateBits);
            _SWFStream->WriteBits((U32)rotateSkew1, nRotateBits);

        }

        _SWFStream->WriteBits(nTranslateBits, 5);

        _SWFStream->WriteBits((U32)translateX, nTranslateBits);
        _SWFStream->WriteBits((U32)translateY, nTranslateBits);

        _SWFStream->FlushBits();
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//  --------  FRect ------------------------------------------------------------------

//	Rectangle class constructor.
FRect::FRect(const SCOORD _xmin, const SCOORD _ymin, const SCOORD _xmax, const SCOORD _ymax) {

    xmin = _xmin;
    xmax = _xmax;
    ymin = _ymin;
    ymax = _ymax;
}

//	FRect's MinBits function.  Calls MinBits with number being the absolute value of the 
//  rectangle coordinate with the greatest magnitude, and sign being 1 since a rectangle 
//	coord is signed.

unsigned long FRect::MinBits() const {
    const unsigned long maxCoord = FSWFStream::MaxNum(xmin, xmax, ymin, ymax);

    return FSWFStream::MinBits(maxCoord, 1);
}

//	Writes the rectangle to the given buffer.

void FRect::WriteToSWFStream(FSWFStream *_SWFStream) const {
    const int nBits = MinBits();
    _SWFStream->WriteBits(nBits, 5);

    _SWFStream->WriteBits((U32)xmin, nBits);
    _SWFStream->WriteBits((U32)xmax, nBits);
    _SWFStream->WriteBits((U32)ymin, nBits);
    _SWFStream->WriteBits((U32)ymax, nBits);

    _SWFStream->FlushBits();
}

//////////////////////////////////////////////////////////////////////////////////////
//  --------  FString  ---------------------------------------------------------------

FString::FString(const U8 *_string) {
    text = (const char *)_string;
}

void FString::WriteToSWFStream(FSWFStream *_SWFStream, const bool null_end) const {
    for (size_t i = 0; i < text.length(); i++) {
        _SWFStream->WriteByte((U32)text[i]);
    }
    if (null_end)
        _SWFStream->WriteByte(0);
}
