// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleSprite.cpp

   Creates a one frame sprite movie with:
   
	1) a red square sprite flickering in white background.
	
****************************************************************************************/

#include "StdAfx.h"
#include "F3SDK.h"
#include "FExample.h"

void MakeSpriteMovie() {

    const FColor red(0xff, 0, 0);
    const FColor black(0, 0, 0);

    const U32 xmin = 1000;
    const U32 ymin = 1000;
    const U32 xmax = 4000;
    const U32 ymax = 4000;

    //construct a rectangle that defines the shape's bounds 
    auto *rectBounds = new FRect(xmin, ymin, xmax, ymax); //coordinate values are in TWIPS

    //construct the FDTDefineShape which will be the rectangle image
    auto *rectangle = new FDTDefineShape(rectBounds);

    //record its ID so that we can later refer to it
    const U16 rectangleID = rectangle->ID();

    //construct a solid fill style of the given color
    //add the fill style to the rectangle
    //you must record the position of the fill style in the fill style array 
    //so that you can later refer to it.  the Add funcion of rectangle returns
    //the position so record that in a field called fillID
    const U32 fillID = rectangle->AddSolidFillStyle(new FColor(red));

    //add a black, 1 pixel (20 TWIPS) wide line style to rectangle, remembering to store the
    // position of the line style just as in the fill style.
    const U32 blackLineStyleID = rectangle->AddLineStyle(20, new FColor(black));

    //since we are done with styles, indicate so
    rectangle->FinishStyleArrays();

    //construct the shape records which will describe the button down image
    FShapeRec *rectangleShapeRecords[6];
    rectangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, xmax, ymin, 0, fillID, blackLineStyleID, nullptr, nullptr);
    rectangleShapeRecords[1] = new FShapeRecEdgeStraight(0, ymax - ymin);
    rectangleShapeRecords[2] = new FShapeRecEdgeStraight(xmin - xmax, 0);
    rectangleShapeRecords[3] = new FShapeRecEdgeStraight(0, ymin - ymax);
    rectangleShapeRecords[4] = new FShapeRecEdgeStraight(xmax - xmin, 0);
    rectangleShapeRecords[5] = new FShapeRecEnd();

    //Add the shape records to the rectangle shape object
    for (auto &rectangleShapeRecord: rectangleShapeRecords)
        rectangle->AddShapeRec(rectangleShapeRecord);

    FObjCollection flashObjects;

    flashObjects.AddFObj(rectangle);

    auto *transformMatrix = new FMatrix();

    // Create third object, a control object which places the triangle object we just defined
    auto *placeRectangle = new FCTPlaceObject2(false, // ~ _hasClipDepth
                                               true,
                                               true,
                                               false,
                                               1,
                                               rectangleID,
                                               transformMatrix,
                                               nullptr,
                                               0,
                                               nullptr,
                                               0 /**/);

    auto *theSprite = new FDTSprite();

    theSprite->AddFObj(placeRectangle);
    //flashObjects.AddFObj(placeRectangle);

    theSprite->AddFObj(new FCTShowFrame());
    //flashObjects.AddFObj( new FCTShowFrame() );

    const U16 spriteID = theSprite->ID();

    flashObjects.AddFObj(theSprite);

    transformMatrix = new FMatrix();

    // Create third object, a control object which places the triangle object we just defined
    auto *placeSprite = new FCTPlaceObject2(false, // ~ _hasClipDepth
                                            true,
                                            true,
                                            false,
                                            1,
                                            spriteID,
                                            transformMatrix,
                                            nullptr,
                                            0,
                                            nullptr,
                                            0/**/);

    flashObjects.AddFObj(placeSprite);

    flashObjects.AddFObj(new FCTShowFrame());

    auto *remove = new FCTRemoveObject2(1);

    flashObjects.AddFObj(remove);

    flashObjects.AddFObj(new FCTShowFrame());

    flashObjects.CreateMovie("FExampleSprite.swf");

}
