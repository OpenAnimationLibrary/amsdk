// KB  5/14/98  \KenB\Include\fontacce.h
#pragma once

#include "access.h"
void InitMatrix(fontMatrix);

/*	Return a handle to the sfnt in the given font family with the given style.
*/
Handle GetNamedSfntHandle(Str255 fontName, short styleWord);
Handle GetSfntHandle(short txFont, short styleWord);

/*	Allocate the initial arrays for the GlyphOutline.
*/
void InitGlyphOutline(GlyphOutline* out);

/*	Dispose the memory allocated for the GlyphOutline.
*/
void KillGlyphOutline(GlyphOutline* out);

/*	Lock/Unlock the arrays in the GlyphOutline.
*/
void LockGlyphOutline(GlyphOutline*);
void UnlockGlyphOutline(GlyphOutline*);

/*	These modify the outline, origin and advance.
*/
void MoveGlyphOutline(GlyphOutline*, Fixed xDelta, Fixed yDelta);
void MoveToGlyphOutline(GlyphOutline* out, Fixed xCoord, Fixed yCoord);
void ScaleGlyphOutline(GlyphOutline* out, Fixed xScale, Fixed yScale);
void MapGlyphOutline(GlyphOutline*, fontMatrix);

/*	Convert a glyph outline into a paths, allocated as a NewPtr.
*/
paths* OutlineToPaths(GlyphOutline* out);

/*	Works like StdText, but frames the outlines using FrameGlyphOutline.
*/
void FrameText( unsigned char* text, FixPoint* scale, int mark );

/*	Just like FrameText, but returns the paths. It also fills out finalPenPosition
 *	with the pen location for the end of the text.
*/
paths* Text2Paths( unsigned char* text, FixPoint* scale, FixPoint* finalPenPosition );
