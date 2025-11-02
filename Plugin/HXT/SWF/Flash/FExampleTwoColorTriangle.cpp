// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/18/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleTwoColorTriangle.cpp

   Creates a one frame two color triangle movie with:
   
	1) a standard 1 pixel wide, black line style, drawing the first two edges with red 
	   and the last edge in blue. However, the result is unexpected.
 
****************************************************************************************/

#include "StdAfx.h"
#include "F3SDK.h"
#include "FExample.h"

void CreateTwoColorTriangleMovie() {

    FObjCollection allTags;

    // background color
    const FColor white(0xff, 0xff, 0xff);
    auto *background = new FCTSetBackgroundColor(new FColor(white));
    allTags.AddFObj(background);

    // Set bounding rectangle.
    auto *rectBounds = new FRect(0, 0, 10000, 6000);
    auto *triangle = new FDTDefineShape(rectBounds);
    const U16 triangleID = triangle->ID();

    // Define two fill colors: red and blue.
    const FColor red = FColor(0xff, 0, 0);
    const FColor blue = FColor(0, 0, 0xff);
    [[maybe_unused]] U32 redfillID = triangle->AddSolidFillStyle(new FColor(red));
    const U32 bluefillID = triangle->AddSolidFillStyle(new FColor(blue));

    // Define the line style: black, 1 pixel (20 twips) wide.
    const FColor black = FColor(0, 0, 0);
    //add a black, 1 pixel (20 TWIPS) wide line style to triangle, remembering to store the
    // position of the line style just as in the fill style.
    const U32 blackLineStyleID = triangle->AddLineStyle(20, new FColor(black));
    triangle->FinishStyleArrays();

    // Constructing the triangle shape.
    // Draw the first two edges with red color fill.

    //	FShapeRec* triangleShapeRecords[11];

    /*	triangle->AddShapeRec(	new FShapeRecChange(false, true, true, false, true, 6000, 4000, 0, 
                                                       redfillID, blackLineStyleID, 0, 0)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight( -3000, 0)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight( 0, 2000)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight(3000, 0)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight(0, -2000)	);
    
        triangle->AddShapeRec(	new FShapeRecChange(false, true, true, false, true, 5000, 3000, 0, 
                                                       redfillID, blackLineStyleID, 0, 0)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight( -3000, 0)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight( 0, 2000)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight(3000, 0)	);
        triangle->AddShapeRec(	new FShapeRecEdgeStraight(0, -2000)	);
    */

    //	triangle->AddShapeRec(	new FShapeRecEnd()	);

    triangle->AddShapeRec(new FShapeRecChange(false, true, true, false, true, 5000, 5000, 0, bluefillID, blackLineStyleID, nullptr, nullptr));
    triangle->AddShapeRec(new FShapeRecEdgeStraight(-1000, 0));
    triangle->AddShapeRec(new FShapeRecEdgeStraight(0, 1000));
    triangle->AddShapeRec(new FShapeRecEdgeStraight(1000, -1000));

    triangle->AddShapeRec(new FShapeRecChange(false, true, true, false, true, 5000, 5000, 0, bluefillID, blackLineStyleID, nullptr, nullptr));
    triangle->AddShapeRec(new FShapeRecEdgeStraight(-1000, 0));
    triangle->AddShapeRec(new FShapeRecEdgeStraight(0, -1000));
    triangle->AddShapeRec(new FShapeRecEdgeStraight(1000, 1000));

    triangle->AddShapeRec(new FShapeRecEnd());

    //	for (int i = 0;  i < 11 ;  i++)
    //		triangle->AddShapeRec(triangleShapeRecords[i]);

    //Add the triangle to the given object collection
    allTags.AddFObj(triangle);

    //create a place object tag which puts the triangle on the display list
    auto *placeTriangle = new FCTPlaceObject2(false, // ~ _hasClipDepth
                                              false,
                                              true,
                                              false,
                                              1,
                                              triangleID,
                                              nullptr,
                                              nullptr,
                                              0,
                                              nullptr,
                                              0/**/);

    //add the place object tag to the FObjCollection
    allTags.AddFObj(placeTriangle);

    //construct a show frame object
    auto *showFrame = new FCTShowFrame();

    //add the show frame object to the FObj collection;
    allTags.AddFObj(showFrame);

    //now create the movie
    allTags.CreateMovie("FExampleTwoColorTriangle.swf", 11000, 8000, 12);

}
