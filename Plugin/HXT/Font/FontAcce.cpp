// KB  12/3/01  \Ken90\Plugin\HXT\FontMac\FontAcce.cpp

#include "stdafx.h"
#include "resource.h"

#include "macname1.h"
//#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>
//#include "MacOS\Resource.h"
//#include "MacOS\Memory.h"
//#include "MacOS\Types.h"
//#include "MacOS\QuickDra.h"
//#include "MacOS\ToolUtil.h"
//#include "MacOS\Fonts.h"
#include "macname2.h"

#include "sfnt.h"
#include "Access.h"
#include "fontacce.h"
#include "MessageR.h"

void InitGlyphOutline(GlyphOutline* out);
void MoveGlyphOutline(GlyphOutline*, Fixed xDelta, Fixed yDelta);
void KillGlyphOutline(GlyphOutline* out);
void AppendGlyphOutline(GlyphOutline* a, GlyphOutline* b);

static char GetFontState(Handle sfnt)
{
	char state;

	CarbonLoadResource(sfnt);
	state = HGetState(sfnt);
	HNoPurge(sfnt);
	return state;
}

static void SetFontState(Handle sfnt, char state)
{
	HSetState(sfnt, state);
}

/*	Macro and glue routine to make handle growing easier.
*/
#define SHS(h, s)	NiceSetHandleSize((Handle)h, s)

static short NiceSetHandleSize(Handle h, long size)
{
	SetHandleSize(h, size);
	return MemError();
}

/*	Some private calls to return pointers to various sfnt pieces.
*/
static void* GetSfntTablePtr(Handle sfnt, long tag)
{
	FontTableInfo info;

	if (GetSfntTableInfo(sfnt, tag, &info))
		return 0;
	return *sfnt + info.offset;
}

static void* GetSfntGlyphPtr(Handle sfnt, long glyphIndex, long* length)
{
	void* loc;
	char* glyphStart;
	sfnt_FontHeader* head;

	if (!((head = (sfnt_FontHeader*)GetSfntTablePtr(sfnt, tag_FontHeader)) &&
		(loc = GetSfntTablePtr(sfnt, tag_IndexToLoc)) &&
		(glyphStart = (char *)GetSfntTablePtr(sfnt, tag_GlyphData))))
		return 0;

	if (EndianS16_BtoN( head->indexToLocFormat) == SHORT_INDEX_TO_LOC_FORMAT)
	{	
      unsigned short* offset = (unsigned short*)loc + glyphIndex;
      short temp1, temp2;  // KB: flip bytes for Intel Mac
      temp1 = EndianS16_BtoN( offset[1]);
      temp2 = EndianS16_BtoN( *offset );
		*length = (long)(temp1 -  temp2 ) << 1;
		return glyphStart + ((long)temp2 << 1);
	}
	else
	{
   	long* offset = (long*)loc + glyphIndex;
      long temp1, temp2;  // KB: flip bytes for Intel Mac
      temp1 = EndianS32_BtoN( offset[1]);
      temp2 = EndianS32_BtoN( *offset );
		*length = temp1 - temp2;
		return glyphStart + EndianS32_BtoN( *offset );
	}
}

/********************** Public Font Tool Calls *******************/

long CountSfntTables(Handle sfnt)
{
	char state = GetFontState(sfnt);
	short tables = EndianS16_BtoN(((sfnt_OffsetTable*)*sfnt)->numOffsets); // KB: flip bytes for Intel Mac
	SetFontState(sfnt, state);
	return tables;
}

long GetSfntTag(Handle sfnt, long index)
{
	long tag = 0;
	char state = GetFontState(sfnt);
	if (index < EndianS16_BtoN(((sfnt_OffsetTable*)*sfnt)->numOffsets)) // KB: flip bytes for Intel Mac
		tag = EndianS32_BtoN(((sfnt_OffsetTable*)*sfnt)->table[index].tableTag);
	SetFontState(sfnt, state);
	return tag;
}

long GetSfntTableInfo(Handle sfnt, long tag, FontTableInfo* fTable)
{
	char state = GetFontState(sfnt);
	sfnt_OffsetTable* dir = (sfnt_OffsetTable*)*sfnt;
	sfnt_DirectoryEntry* table = dir->table;
	short count = EndianU16_BtoN( dir->numOffsets ); // KB: flip bytes for Intel Mac
	long error = fNoError;

	for (; --count >= 0; table++)
		if (EndianU32_BtoN( table->tableTag ) == (unsigned long)tag) // KB: flip bytes for Intel Mac
		{	fTable->offset = EndianU32_BtoN( table->offset ); // KB: flip bytes for Intel Mac
			fTable->length = EndianU32_BtoN( table->length ); // KB: flip bytes for Intel Mac
			fTable->checkSum = EndianU32_BtoN( table->checkSum ); // KB: flip bytes for Intel Mac
			break;
		}
	if (count < 0)
		error = fTableNotFound;
	SetFontState(sfnt, state);
	return error;
}

long GetSfntTable(Handle sfnt, long tag, Handle userCopy)
{
	FontTableInfo info;
	long error;

	if (error = GetSfntTableInfo(sfnt, tag, &info))
		return error;

	SetHandleSize(userCopy, info.length);
	if (MemError())
		return fMemoryError;
	
	{	char state = GetFontState(sfnt);
		BlockMove(*sfnt + info.offset, *userCopy, info.length);
		SetFontState(sfnt, state);
	}
	return fNoError;
}

long GetSfntNameString(Handle sfnt, long nameID, Str255 name)
{
	sfnt_NamingTable* nameT;
	sfnt_NameRecord* nameR;
	short count;
	char state = GetFontState(sfnt);

	if (!(nameT = (sfnt_NamingTable*)GetSfntTablePtr(sfnt, tag_NamingTable)))
	{	SetFontState(sfnt, state);
		return fTableNotFound;
	}

	nameR = (sfnt_NameRecord*)(nameT + 1);
	count = EndianU16_BtoN( nameT->count ); // KB: flip bytes for Intel Mac

	/*	This section can be changed to get font names in other languages
	*/
	for (; --count >= 0; nameR++)
		if (EndianU16_BtoN( nameR->platformID ) == plat_Macintosh && // KB: flip bytes for Intel Mac
			EndianU16_BtoN( nameR->specificID ) == smRoman     && // KB: flip bytes for Intel Mac
			EndianU16_BtoN( nameR->languageID ) == lang_English   && // KB: flip bytes for Intel Mac
			EndianU16_BtoN( nameR->nameID ) == nameID) // KB: flip bytes for Intel Mac
		{
			name[0] = EndianU16_BtoN( nameR->length ) <= 255 ? EndianU16_BtoN( nameR->length ) : 255; // KB: flip bytes for Intel Mac
			BlockMove((Ptr)nameT + EndianU16_BtoN( nameT->stringOffset ) + EndianU16_BtoN( nameR->offset ), (Ptr)&name[1], name[0]); // KB: flip bytes for Intel Mac
			SetFontState(sfnt, state);
			return fNoError;
		}

	name[0] = 0;
	SetFontState(sfnt, state);
	return fNameNotFound;
}

/*	Returns the glyph index for the given character code, or
 *	an error code.
 */
long GetCharGlyphIndex(Handle sfnt, unsigned short charCode)
{
	sfnt_char2IndexDirectory* table;
	short i;
	long mapOffset = 0;
	long glyphIndex = 0;		/* missing character glyph */
	char state = GetFontState(sfnt);

	if (!(table = (sfnt_char2IndexDirectory*)GetSfntTablePtr(sfnt, tag_CharToIndexMap)))
	{	SetFontState(sfnt, state);
		return fTableNotFound;
	}

	{	
           sfnt_platformEntry* plat = table->platform;
	
		/* You can change this section to look for other scripts
		*/
		for ( i = EndianU16_BtoN( table->numTables ) - 1; i >= 0; --i ) // KB: flip bytes for Intel Mac
		{	if ( EndianU16_BtoN( plat->platformID ) == plat_Macintosh && EndianU16_BtoN( plat->specificID ) == smRoman) // KB: flip bytes for Intel Mac
			{	mapOffset = EndianU32_BtoN( plat->offset ); // KB: flip bytes for Intel Mac
				break;
			}
			++plat;
		}
	}
	
	if (mapOffset)
	{	sfnt_mappingTable* mapping = (sfnt_mappingTable*)((char*)table + mapOffset);
		
		switch ( EndianU16_BtoN( mapping->format ) ) { // KB: flip bytes for Intel Mac
		case 0:
			{	
            Byte* glyphs = (Byte*)(mapping + 1);
				glyphIndex = glyphs[charCode]; // KB: no flip
			}
			break;
		case 6:
			{	short* glyphs = (short*)(mapping + 1);
				short first =  EndianS16_BtoN( *glyphs++ ); // KB: flip bytes for Intel Mac
				short count =  EndianS16_BtoN( *glyphs++ ); // KB: flip bytes for Intel Mac
				charCode -= first;
				if (charCode < count)
					glyphIndex =  EndianS16_BtoN( glyphs[charCode] ); // KB: flip bytes for Intel Mac
			}
			break;
		default:
			glyphIndex = fUnimplemented;
		}
	}
	else
		glyphIndex = fCMapNotFound;

	SetFontState(sfnt, state);
	return glyphIndex;
}

long CountSfntGlyphs(Handle sfnt)
{
	sfnt_maxProfileTable* profile;
	short glyphs;

	if (!(profile = (sfnt_maxProfileTable*)GetSfntTablePtr(sfnt, tag_MaxProfile)))
		return fTableNotFound;

	{	char state = GetFontState(sfnt);
		glyphs = EndianU16_BtoN( profile->numGlyphs ); // KB: flip bytes for Intel Mac
		SetFontState(sfnt, state);
	}
	return glyphs;
}

#define GetUnsignedByte( p ) ((Byte)(*p++))

long GetGlyphOutlines(Handle sfnt, long glyphIndex, GlyphOutline* gOutline, fontMatrix xform)
{
   char state;
	short upem, sideBearing, adjustToLsb;
	short *glyph;
	sfnt_FontHeader* head;
	sfnt_HorizontalHeader* hhea;
	sfnt_HorizontalMetrics* hori;
	long length;
	long error = fNoError;

	state = GetFontState( sfnt );
	HLock( sfnt );

	if (!((head = (sfnt_FontHeader*)GetSfntTablePtr(sfnt, tag_FontHeader)) &&
		(hhea = (sfnt_HorizontalHeader*)GetSfntTablePtr(sfnt, tag_HoriHeader)) &&
		(hori = (sfnt_HorizontalMetrics*)GetSfntTablePtr(sfnt, tag_HorizontalMetrics))))
	{	error = fTableNotFound;
		goto EXIT;
	}

	upem = EndianU16_BtoN( head->unitsPerEm ); // KB: flip bytes for Intel Mac

	{	long longMetrics = EndianU16_BtoN( hhea->numberLongMetrics ); // KB: flip bytes for Intel Mac
		if ( glyphIndex < longMetrics )
		{	gOutline->advance.x = FixRatio( EndianU16_BtoN( hori[glyphIndex].advance ), upem ); // KB: flip bytes for Intel Mac
			sideBearing = EndianS16_BtoN( hori[glyphIndex].sideBearing ); // KB: flip bytes for Intel Mac
		}
		else
		{	short *lsb = (short *)&hori[longMetrics]; /* first entry after[AW,LSB] array */  // KB: flip bytes for Intel Mac
			
			gOutline->advance.x = FixRatio( EndianU16_BtoN( hori[longMetrics-1].advance ), upem ); // KB: flip bytes for Intel Mac
			sideBearing = EndianS16_BtoN( hori[glyphIndex - longMetrics].sideBearing ); // KB: flip bytes for Intel Mac
		}
		gOutline->advance.y = 0;
	}

	gOutline->origin.x = gOutline->origin.y = 0;

	if (!(glyph = (short *)GetSfntGlyphPtr(sfnt, glyphIndex, &length)))
	{	error = fGlyphNotFound;
		goto EXIT;
	}

	if (length == 0)
	{	gOutline->contourCount = gOutline->pointCount = 0;
		goto EXIT;
	}

	short tempcontourcount;
    tempcontourcount = EndianS16_BtoN( *glyph++ ); // KB: flip bytes for Intel Mac
	gOutline->contourCount = tempcontourcount; 
	adjustToLsb = EndianS16_BtoN( *glyph ) - sideBearing;		/* xmin - lsb */ // KB: flip bytes for Intel Mac
	glyph += 4;						/* skip bounds rect */

	if (gOutline->contourCount == 0)
		gOutline->pointCount = 0;
	else if (gOutline->contourCount == -1)
	{	short flags, index, newMatrix;

		gOutline->contourCount = gOutline->pointCount = 0;
		SHS(gOutline->endPoints, 0);
		SHS(gOutline->onCurve, 0);
		SHS(gOutline->x, 0);
		SHS(gOutline->y, 0);
		do
		{	fontMatrix compXform;
			short arg1, arg2;
			
			flags = EndianS16_BtoN( *glyph++ ); // KB: flip bytes for Intel Mac
			index = EndianS16_BtoN( *glyph++ ); // KB: flip bytes for Intel Mac
			newMatrix = false;

			if ( flags & ARG_1_AND_2_ARE_WORDS )
			{	arg1 = EndianS16_BtoN( *glyph++ ); // KB: flip bytes for Intel Mac
				arg2 = EndianS16_BtoN( *glyph++ ); // KB: flip bytes for Intel Mac
			}
			else
			{	char* byteP = (char*)glyph;
				if ( flags & ARGS_ARE_XY_VALUES )
				{	/* offsets are signed */
					arg1 = *byteP++;
					arg2 = *byteP;
				}
				else
				{	/* anchor points are unsigned */
					arg1 = (unsigned char)*byteP++;
					arg2 = (unsigned char)*byteP;
				}
				++glyph;
			}
#if IMPLEMENT_SCALED_COMPONENTS
			if ( flags & (WE_HAVE_A_SCALE | WE_HAVE_AN_X_AND_Y_SCALE | WE_HAVE_A_TWO_BY_TWO) )
			{	fontMatrix subXform;
				MakeIdentityMatrix(subXform);
				if ( flags & WE_HAVE_A_TWO_BY_TWO )
				{	compXform[0][0] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
					compXform[0][1] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
					compXform[1][0] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
					compXform[1][1] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
				}
				else if ( flags & WE_HAVE_AN_X_AND_Y_SCALE )
				{	compXform[0][0] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
					compXform[1][1] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
				}
				else
					compXform[0][0] = compXform[1][1] = (Fixed)EndianU16_BtoN( *glyph++ ) << 2; // KB: flip bytes for Intel Mac
				PostMulMatrix(compXform, xform);
				newMatrix = true;
			}
#endif			
			{	GlyphOutline out;
				InitGlyphOutline(&out);
				GetGlyphOutlines(sfnt, index, &out, newMatrix ? compXform : xform);
				{	Fixed dx, dy;
					if (flags & ARGS_ARE_XY_VALUES)
					{	dx = FixRatio(arg1, upem);
						dy = -FixRatio(arg2, upem);
					}
					else
					{	dx = (*gOutline->x)[arg1] - (*out.x)[arg2];
						dy = (*gOutline->y)[arg1] - (*out.y)[arg2];
					}
					MoveGlyphOutline(&out, dx, dy);
				}
				AppendGlyphOutline(gOutline, &out);
				KillGlyphOutline(&out);
			}
		} while (flags & MORE_COMPONENTS);
	}
	else if (gOutline->contourCount > 0)
	{	/*	Load in the end points.
		 */
		{	long size = gOutline->contourCount * sizeof(short);

			if (SHS(gOutline->endPoints, size))
			{	error = fMemoryError;
				goto EXIT;
			}
			BlockMove( (Ptr)glyph, (Ptr)*gOutline->endPoints, size );
         short *endpoints = (short *)*gOutline->endPoints;
         for (int l = 0; l < (size / 2); l++ ) {
            *endpoints = EndianS16_BtoN( *endpoints );
            endpoints++;
         }
			glyph += gOutline->contourCount;
		}

		gOutline->pointCount = (*gOutline->endPoints)[gOutline->contourCount - 1] + 1;
		if (SHS(gOutline->onCurve, gOutline->pointCount * sizeof(char)))
		{	error = fMemoryError;
			goto EXIT;
		}
		if (SHS(gOutline->x, gOutline->pointCount * sizeof(Fixed)))
		{	error = fMemoryError;
			goto EXIT;
		}
		if (SHS(gOutline->y, gOutline->pointCount * sizeof(Fixed)))
		{	error = fMemoryError;
			goto EXIT;
		}

		/*	Skip the word for instruction count + the instructions.
		 *	Then load in the onCurve bytes.
		 */
		{	Byte* p = (Byte*)glyph + sizeof(short) + EndianS16_BtoN( *glyph );
			Byte* onCurve = *gOutline->onCurve;
			Byte* stop = onCurve + gOutline->pointCount;
			Byte flag;

			while (onCurve < stop)
			{	*onCurve++ = flag = GetUnsignedByte( p );
				if ( flag & REPEAT_FLAGS ) {
					short count = GetUnsignedByte( p );
					for (--count; count >= 0; --count)
						*onCurve++ = flag;
				}
			}
			/*	Lets do X
			*/
			{	short coord = adjustToLsb;
				Fixed* x = *gOutline->x;

				onCurve = *gOutline->onCurve;
				while (onCurve < stop)
				{	if ( (flag = *onCurve++) & XSHORT ) {
						if ( flag & SHORT_X_IS_POS )
							coord += GetUnsignedByte( p );
						else
							coord -= GetUnsignedByte( p );
					}
					else if ( !(flag & NEXT_X_IS_ZERO) )
					{	coord += (short)(*p++) << 8;
						coord += (Byte)*p++;
					}
					*x++ = FixRatio( coord, upem );
				}
			}
			/*	Lets do Y
			*/
			{	short coord = 0;
				Fixed* y = *gOutline->y;

				onCurve = *gOutline->onCurve;
				while (onCurve < stop)
				{	if ( (flag = *onCurve) & YSHORT ) {
						if ( flag & SHORT_Y_IS_POS )
							coord += GetUnsignedByte( p );
						else
							coord -= GetUnsignedByte( p );
					}
					else if ( !(flag & NEXT_Y_IS_ZERO) )
					{	coord += (short)(*p++) << 8;
						coord += (Byte)*p++;
					}
					*y++ = -FixRatio( coord, upem );
					
					/*	Filter off the extra bits
					*/
					*onCurve++ = flag & ONCURVE;
				}
			}
		}
	}
	else
		error = fUnimplemented;
EXIT:
	SetFontState( sfnt, state );

	return error;
}

Handle GetNamedSfntHandle(unsigned char* name, short styleWord)
{
	Handle fond = GetNamedResource('FOND', name);
	if (fond && !ResError())
	{	FamRec* frec = (FamRec*)*fond;
// KB: flip bytes for Intel Mac
//      frec->ffFlags = EndianS16_BtoN( frec->ffFlags );                /*flags for family*/
//      frec->ffFamID = EndianS16_BtoN( frec->ffFamID );                /*family ID number*/
//      frec->ffFirstChar = EndianS16_BtoN( frec->ffFirstChar );        /*ASCII code of 1st character*/
//      frec->ffLastChar = EndianS16_BtoN( frec->ffLastChar );          /*ASCII code of last character*/
//      frec->ffAscent = EndianS16_BtoN( frec->ffAscent );              /*maximum ascent for 1pt font*/
//      frec->ffDescent = EndianS16_BtoN( frec->ffDescent );            /*maximum descent for 1pt font*/
//      frec->ffLeading = EndianS16_BtoN( frec->ffLeading );            /*maximum leading for 1pt font*/
//      frec->ffWidMax = EndianS16_BtoN( frec->ffWidMax );              /*maximum widMax for 1pt font*/
//      frec->ffWTabOff = EndianS32_BtoN( frec->ffWTabOff );            /*offset to width table*/
//      frec->ffKernOff = EndianS32_BtoN( frec->ffKernOff );            /*offset to kerning table*/
//      frec->ffStylOff = EndianS32_BtoN( frec->ffStylOff );            /*offset to style mapping table*/
//      for (int j = 0; j < 9; j++) 
//         frec->ffProperty[j] = (short)EndianS16_BtoN( frec->ffProperty[j] );          /*style property info*/
//      frec->ffIntl[0] = (short)EndianS16_BtoN( frec->ffIntl[0] );                  /*for international use*/
//      frec->ffIntl[1] = (short)EndianS16_BtoN( frec->ffIntl[1] );                  /*for international use*/
//      frec->ffVersion = (short)EndianS16_BtoN( frec->ffVersion );            /*version number*/

		short* assoc = (short*)(frec + 1);
		short sfntID = 0;
		short count = *assoc++;
      // KB: flip bytes for Intel Mac
      *assoc = EndianS16_BtoN( *assoc );

		while (count-- >= 0 && !sfntID) {
         // KB: flip bytes for Intel Mac
         *assoc = EndianS16_BtoN( *assoc );
      	if (*assoc++ == 0) {		/* size == 0 means sfnt */
            // KB: flip bytes for Intel Mac
            *assoc = EndianS16_BtoN( *assoc );
				if (*assoc++ == styleWord) {
               *assoc = EndianS16_BtoN( *assoc );
					sfntID = *assoc;
            }
				else
					assoc++;
         }
			else
				assoc += 2;
		}
		if (sfntID)
		{	Handle sfnt = GetResource('sfnt', sfntID);
			if (sfnt && !ResError())
				return sfnt;
		}
	}
	return 0;
}

static BOOL f_bTestOnly;

BOOL IsFontUsable( unsigned char *name )
{
   if (name && name[0] == '#')
      return FALSE;
   f_bTestOnly = TRUE;
	unsigned char *pname = (unsigned char *)strdup( (char *)name );
   pname = c2pstr((char *)pname);
   Handle handle = GetSfntHandle( FMGetFontFamilyFromName( pname ), 0 );
   free( pname );
   f_bTestOnly = FALSE;
   return handle ? TRUE : FALSE;
}

Handle GetSfntHandle( FMFontFamily iFontFamily,short styleWord )
{
   Handle *oHandle;
   FMFont font;
   Str255 fontFamilyName;
   SInt16 rsrcFRefNum;
   Handle rsrcHandle;
   FSSpec rsrcFSSpec;
   FSRef rsrcFSRef;
   HFSUniStr255 forkName;
   OSStatus status;
   Handle sfnt = nullptr;

   font = kInvalidFont;
   rsrcFRefNum = -1;
   rsrcHandle = nullptr;
   status = noErr;
   
   /* Get the font family name to use with the Resource
      Manager when grabbing the 'FOND' resource. */
   status = FMGetFontFamilyName(iFontFamily, fontFamilyName);
   require(status == noErr, FMGetFontFamilyName_Failed);
   
   /* Get a component font of the font family to obtain
      the file specification of the container of the font
      family. */
   status = FMGetFontFromFontFamilyInstance(iFontFamily, 0, &font, nil);
   require(status == noErr && font != kInvalidFont,
           FMGetFontFromFontFamilyInstance_Failed);
   
   status = FMGetFontContainer(font, &rsrcFSSpec);
   require(status == noErr, FMGetFontContainer_Failed);
   
   /* Open the resource fork of the file. */
   rsrcFRefNum = FSpOpenResFile(&rsrcFSSpec, fsRdPerm);
   
   /* If the font is based on the ".dfont" file format,
      we need to open the data fork of the file. */
   if ( rsrcFRefNum == -1 ) {
      
      /* The standard fork name is required to open
      the data fork of the file. */
      status = FSGetDataForkName(&forkName);
      require(status == noErr, FSGetDataForkName_Failed);
      
      /* The file specification (FSSpec) must be converted
         to a file reference (FSRef) to open the data fork
         of the file. */
      status = FSpMakeFSRef(&rsrcFSSpec, &rsrcFSRef);
      require(status == noErr, FSpMakeFSRef_Failed);
      
      status = FSOpenResourceFile(&rsrcFSRef,
                                  forkName.length, forkName.unicode,
                                  fsRdPerm, &rsrcFRefNum);
      require(status == noErr, FSOpenResourceFile_Failed);
   }
   
   UseResFile(rsrcFRefNum);
   
   /* On Mac OS X, the font family identifier may not
      match the resource identifier after resolution of
      conflicting and duplicate fonts. */
   rsrcHandle = Get1NamedResource(FOUR_CHAR_CODE('FOND'), fontFamilyName);
   require_action(rsrcHandle != nullptr,
                  Get1NamedResource_Failed, status = ResError());

/////////////////////////////////////////////////////////
	if (rsrcHandle && !ResError()) {
      FamRec* frec = (FamRec*)*rsrcHandle;
// KB: flip bytes for Intel Mac
//      frec->ffFlags = EndianS16_BtoN( frec->ffFlags );                /*flags for family*/
//      frec->ffFamID = EndianS16_BtoN( frec->ffFamID );                /*family ID number*/
//      frec->ffFirstChar = EndianS16_BtoN( frec->ffFirstChar );        /*ASCII code of 1st character*/
//      frec->ffLastChar = EndianS16_BtoN( frec->ffLastChar );          /*ASCII code of last character*/
//      frec->ffAscent = EndianS16_BtoN( frec->ffAscent );              /*maximum ascent for 1pt font*/
//      frec->ffDescent = EndianS16_BtoN( frec->ffDescent );            /*maximum descent for 1pt font*/
//      frec->ffLeading = EndianS16_BtoN( frec->ffLeading );            /*maximum leading for 1pt font*/
//      frec->ffWidMax = EndianS16_BtoN( frec->ffWidMax );              /*maximum widMax for 1pt font*/
//      frec->ffWTabOff = EndianS32_BtoN( frec->ffWTabOff );            /*offset to width table*/
//      frec->ffKernOff = EndianS32_BtoN( frec->ffKernOff );            /*offset to kerning table*/
//      frec->ffStylOff = EndianS32_BtoN( frec->ffStylOff );            /*offset to style mapping table*/
//      for (int j = 0; j < 9; j++) 
//         frec->ffProperty[j] = (short)EndianS16_BtoN( frec->ffProperty[j] );          /*style property info*/
//      frec->ffIntl[0] = (short)EndianS16_BtoN( frec->ffIntl[0] );                  /*for international use*/
//      frec->ffIntl[1] = (short)EndianS16_BtoN( frec->ffIntl[1] );                  /*for international use*/
//      frec->ffVersion = (short)EndianS16_BtoN( frec->ffVersion );            /*version number*/

		short* assoc = (short*)(frec + 1);
      // KB: flip bytes for Intel Mac
      *assoc = EndianS16_BtoN( *assoc );
		short sfntID = 0;
		short count = *assoc++;
      
		while (count-- >= 0 && !sfntID) {
         // KB: flip bytes for Intel Mac
         *assoc = EndianS16_BtoN( *assoc );
         if (*assoc++ == 0)	{	/* size == 0 means sfnt */
            // KB: flip bytes for Intel Mac
            *assoc = EndianS16_BtoN( *assoc );
            if (*assoc++ == styleWord) {
               *assoc = EndianS16_BtoN( *assoc );
               sfntID = *assoc;
            }
            else
               assoc++;
         }
			else
				assoc += 2;
		}

		if (sfntID) {
         sfnt = Get1Resource('sfnt', sfntID);

         if (sfnt && !ResError() && !f_bTestOnly)
            return sfnt;
      }
	}
/////////////////////////////////////////////////////////

   DetachResource(rsrcHandle);
   
Get1NamedResource_Failed:
      
      if ( rsrcFRefNum != -1 )
         CloseResFile(rsrcFRefNum);
   
FSOpenResourceFile_Failed:
FSpMakeFSRef_Failed:
FSGetDataForkName_Failed:
FMGetFontContainer_Failed:
FMGetFontFromFontFamilyInstance_Failed:
FMGetFontFamilyName_Failed:

   if (sfnt && !ResError() && f_bTestOnly)
		return (Handle)1;
   
   return nullptr;
}

void InitGlyphOutline(GlyphOutline* out)
{
	out->contourCount = 0;
	out->pointCount = 0;
	out->endPoints = (short**)NewHandle(0);
	out->onCurve = (Byte**)NewHandle(0);
	out->x = (Fixed**)NewHandle(0);
	out->y = (Fixed**)NewHandle(0);
}

void KillGlyphOutline(GlyphOutline* out)
{
	DisposeHandle((Handle)out->endPoints);
	DisposeHandle((Handle)out->onCurve);
	DisposeHandle((Handle)out->x);
	DisposeHandle((Handle)out->y);
}

void LockGlyphOutline(GlyphOutline* out)
{
	HLock((Handle)out->endPoints);
	HLock((Handle)out->onCurve);
	HLock((Handle)out->x);
	HLock((Handle)out->y);
}

void UnlockGlyphOutline(GlyphOutline* out)
{
	HUnlock((Handle)out->endPoints);
	HUnlock((Handle)out->onCurve);
	HUnlock((Handle)out->x);
	HUnlock((Handle)out->y);
}

void MoveGlyphOutline(GlyphOutline* out, Fixed xDelta, Fixed yDelta)
{	
	Fixed* x = *out->x;
	Fixed* y = *out->y;
	long count = out->pointCount;

	for (--count; count >= 0; --count)
	{	*x++ += xDelta;
		*y++ += yDelta;
	}
	out->origin.x += xDelta;
	out->origin.y += yDelta;
}

void MoveToGlyphOutline(GlyphOutline* out, Fixed xCoord, Fixed yCoord)
{
	MoveGlyphOutline(out, xCoord - out->origin.x, yCoord - out->origin.y);
}

void ScaleGlyphOutline(GlyphOutline* out, Fixed xScale, Fixed yScale)
{	
	Fixed* x = *out->x;
	Fixed* y = *out->y;
	long count = out->pointCount;

	for (--count; count >= 0; --count)
	{	*x = FixMul( *x, xScale );
		x++;
		*y = FixMul( *y, yScale );
		y++;
	}
	out->origin.x = FixMul( out->origin.x, xScale );
	out->origin.y = FixMul( out->origin.y, yScale );
	out->advance.x = FixMul( out->advance.x, xScale );
	out->advance.y = FixMul( out->advance.y, yScale );
}

#define APPENDHANDLE(a,b)	AppendHandle((Handle)a, (Handle)b)
void AppendHandle(Handle dst, Handle extra)
{
	long dstSize = GetHandleSize(dst);
	long extraSize = GetHandleSize(extra);
	
	SetHandleSize(dst, dstSize + extraSize);
	if (MemError())
		Debugger();
	else
		BlockMove(*extra, *dst + dstSize, extraSize);
}

//    a += b
void AppendGlyphOutline(GlyphOutline* a, GlyphOutline* b)
{
	APPENDHANDLE(a->endPoints, b->endPoints);
	{	short* p = *a->endPoints + a->contourCount;
		short* endp = p + b->contourCount;
		short newFirstPoint = a->contourCount ? p[-1] + 1 : 0;
		for (; p < endp; p++)
			*p = *p + newFirstPoint;
	}
	a->contourCount += b->contourCount;
	a->pointCount += b->pointCount;
	APPENDHANDLE(a->onCurve, b->onCurve);
	APPENDHANDLE(a->x, b->x);
	APPENDHANDLE(a->y, b->y);
}
