// KB  12/3/01  \Ken90\Plugin\HXT\FontMac\GlyphMac.cpp

#include "stdafx.h"
#include "Vector.h"
#include "Vector2.h"

#include "geom.h"
#include "Glyph.h"

// includes specific to Mac
#include "macname1.h"
//#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>
//#include "MacOS\Types.h"
//#include "MacOS\ToolUtil.h"
#include "Access.h"
//#include "MacOS/Fonts.h"
//#include "MacOS\Resource.h"
#include "macname2.h"
#include "sfnt.h"
#include "fontacce.h"

// external routines for handling fonts and glyphs on Mac
//Handle GetSfntHandle( FMFontFamily iFontFamily, register short styleWord );
void         InitGlyphOutline(GlyphOutline*);
void         KillGlyphOutline(GlyphOutline*);
long         GetCharGlyphIndex(Handle, unsigned short);
long         GetGlyphOutlines(Handle, long, GlyphOutline*, fontMatrix);

#define SIZEFUDGE 210000000.0f //40000.

static Handle f_sfnt = 0;
static char f_state = 0;

BOOL GetSfnt(CString& facename) 
{
	if (facename.IsEmpty()) 
		return FALSE;

	// (HWT) Not sure how to convert CString facename
	// to form required by GetFNum.  This sequence
	// is a guess, looking at Font.cpp

	char* sfacename = (char*)facename.GetBuffer(0);
	c2pstr(sfacename);
   FMFontFamily fontfamily = FMGetFontFamilyFromName( (unsigned char *)sfacename );
	// (HWT) I couldn't see how/where Mac code set fontstylenum differently
	// so don't know how to account for our 'weight' and 'is_italic' args.
	short fontstylenum = 0;

	// (HWT) These must do something we want
	SetOutlinePreferred(TRUE);
	SetPreserveGlyph(TRUE);
	SetFractEnable(TRUE);

	f_sfnt = GetSfntHandle(fontfamily, fontstylenum);
	if(f_sfnt == nullptr) {
		// (HWT) Correct cleanup?
		SetOutlinePreferred(FALSE);
		SetPreserveGlyph(FALSE);
		SetFractEnable(FALSE);
		return FALSE;	// couldn't create font
	}
	// (HWT) No idea what this is for
	f_state = HGetState(f_sfnt);
	HNoPurge(f_sfnt);

   return TRUE;
}

void CloseSfnt()
{
   ReleaseResource( f_sfnt );
   f_sfnt = nullptr;
}

// Get contours for character ch in font with given name,
// putting the results into subdiv.
// Each contour is given a separate "spline" id.
// Scale the glyph coordinates by multiplying each by "scale",
// and use *porigin as the character origin.
// Update *porigin to place to put next character.
// Return TRUE if got the contours, else FALSE.
BOOL GetGlyphSplines(Subdiv* subdiv, int ch, CString& facename, int weight, int is_italic,
					 Vector* porigin, float scale)
{
	GlyphOutline outline;
	long glyphindex;
	WORD pointsize;
//   char string[256];

	gtrace("GetGlyphSplines ch='%c'=%d\n", ch, ch);

	if(ch < 0 || facename.IsEmpty()) 
		return FALSE;

   scale = scale / 30.0f; // KB: a hack to make it fit better for Mac 
   
	// (HWT) Don't know what to set pointsize.
	// On PC we get outlines on a 2048x2048 pixel
	// block, so that no hinting adjustments take place.
	// Postscaling in calling routine adjusts for that.
	// 2048 pixels = 20.48" on a 100 dpi monitor,
	// which is about 1475 points.
	pointsize = 65488;

	InitGlyphOutline(&outline);

	glyphindex = GetCharGlyphIndex(f_sfnt, ch);

	// (HWT) Don't know what a bad return value for GetCharGlyphIndex is,
	// but presumably GetGlyphOutlines will fail if got a bad one.

	long ret = GetGlyphOutlines(f_sfnt, glyphindex, &outline, 0);
	if(ret) {
		// (HWT) Correct cleanup?
		gtrace("GetGlyphOutlines failed\n");
		HSetState(f_sfnt, f_state);
		SetOutlinePreferred(FALSE);
		SetPreserveGlyph(FALSE);
		SetFractEnable(FALSE);
		return FALSE;
	}

	// (HWT) Not sure if following needs scaling, but copying Font.cpp code...
	Vector origin = *porigin;
//	origin.x += scale * (int)(outline.advance.x * ((float)pointsize / SIZEFUDGE));

	// (HWT) Following code adapts Font.cpp's FontChar::CreatePointList()
	// except that rather than accumulating a linked list of OnePoints,
	// we just add splines to the subdivision right away.
	Byte* onCurve = *outline.onCurve;
	Fixed* x = *outline.x;
	Fixed* y = *outline.y;
	short* ep = *outline.endPoints;
	long i,j, pointsused, pointsincontour;

	pointsused = 0;
	for(i = 0; i < outline.contourCount; i++) {
		Edge* econtour = 0;
		Edge* ecur = 0;
		int scontour = subdiv->NewSpline();
		pointsincontour =  *ep + 1 - pointsused;
		gtrace("Contour %d, pointsincontour=%d, pointsused=%d\n", i, pointsincontour, pointsused);
		if(pointsincontour >= 3) {
			int closed = 0;
			for(j = 0; j < pointsincontour && !closed; j++) {
				long cur = j + pointsused;
				long nextj = j+1;
				if(nextj == pointsincontour)
					nextj = 0;
				long next = nextj + pointsused;
				long anextj = nextj+1;
				if(anextj == pointsincontour)
					anextj = 0;
				long anext = anextj + pointsused;
				int ison = onCurve[cur];
				int isnexton = onCurve[next];
				int isanexton = onCurve[anext];
				gtrace("Point %d. ison=%d, isnexton=%d, isanexton=%d\n", j, ison, isnexton, isanexton);

				if(!ison && isnexton)
					continue;	// this case generates no spline segment

				Vector curv((float)(x[cur]),-(float)(y[cur]), 0.0f);	// flip y's
				curv = origin + scale*curv;
				Vector nextv((float)(x[next]),-(float)(y[next]), 0.0f);
				nextv = origin + scale*nextv;
				Vector anextv((float)(x[anext]),-(float)(y[anext]), 0.0f);
				anextv = origin + scale*anextv;
				gtrace(" curv=(%g,%g), nextv=(%g,%g), anextv=(%g,%g)\n", curv.x, curv.y, nextv.x, nextv.y, anextv.x, anextv.y);

				Vector curonv;		// on-curve pont at or after j
				Vector nextonv;		// on-curve point at or after nextj
				Vector ctlv;		// Quadratic Bezier control point between curonv and nextonv

				if(ison)
					curonv = curv;
				else
					// isnexton is false, because of continue above
					curonv = 0.5f*(curv+nextv);

				int nextonj = -1;
				if(isnexton) {
					nextonv = nextv;
					nextonj = nextj;
				}
				else if(isanexton) {
					nextonv = anextv;
					nextonj = anextj;
				}
				else
					nextonv = 0.5f*(nextv + anextv);
				gtrace(" curonv=(%g,%g) nextonv=(%g,%g) nextonj=%d\n", curonv.x, curonv.y, nextonv.x, nextonv.y, j);

				if(econtour == 0)
					ecur = econtour = subdiv->MakeEdge(curonv, nextonv, scontour);
				else {
					if(nextonj == 0 ||
						(nextonj == pointsincontour-1 && nextonv == subdiv->Coords(econtour->Org()))) {
						// use edge-to-first-edge Connect to close if we've wrapped around
						// including case where last point coincides with first (happens sometimes)
						// Note: assume first point is always an "on curve" point
						ecur = subdiv->Connect(ecur, econtour, scontour);
						closed = 1;
						gtrace(" close contour\n");
					}
					else
						// use edge-to-point connect if not ready to close contour yet
						ecur = subdiv->Connect(ecur, nextonv, scontour);
				}

				if(ison && isnexton)
					continue;	// a straight line segment, needs no bezier controls

				if(isnexton)
					ctlv = 0.5f*(curonv + nextv);
				else
					ctlv = nextv;
				gtrace(" ctlv=(%g,%g)\n", ctlv.x, ctlv.y);

				// Degree-elevation theory says that cubic control points
				// are 2/3 of the way from curonv and nextonv to controlv.

				Vector cp0 = LinInterp(2.0f/3.0f, curonv, ctlv);
				Vector cp1 = LinInterp(2.0f/3.0f, nextonv, ctlv);
				ecur->SetBezCP(0, cp0);
				ecur->SetBezCP(1, cp1);
			}
		}
		pointsused += pointsincontour;
		ep++;
	}


	// (HWT) Cleanup, not sure what this does
	KillGlyphOutline(&outline);
	HSetState(f_sfnt, f_state);
	SetOutlinePreferred(FALSE);
	SetPreserveGlyph(FALSE);
	SetFractEnable(FALSE);

	porigin->x += /*scale * (int)*/ (outline.advance.x * ((float)pointsize / SIZEFUDGE));

	return TRUE;
}
