// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FDTText.h

	This header-file contains the declarations of low-level text-related classes.
	All parent classes are in the parentheses:

		class FTextRecord;
		class FDTDefineEditText; (public FDT)
		class FDTDefineText; (public FDT)
		class FDTDefineText2; (public FDT)
		class FTextChangeRecord; (public FTextRecord)
		class FTextGlyphRecord; (public FTextRecord)

****************************************************************************************/

#ifndef _F_DEFINE_TEXT_H_
#define _F_DEFINE_TEXT_H_

#include "Macromedia.h"
#include "FDT.h"
#include "FSWFStream.h"
#include "FPrimitive.h"

class FGlyphEntry;

class FTextRecord {
public:
    virtual U32 MinAdvanceBits() = 0; // the computed minimum # of bits to record the advance values
    virtual U32 MinCodeBits() = 0; // the computed minimum # of bits to record the character code values
    virtual ~FTextRecord() = default;

    // Because of multiple text records, the DefineText will specify the code and advance bits
    // when it writes.
    virtual void WriteToSWFStream(FSWFStream *_SWFStream, int codeBits, int advanceBits) = 0;
};

// A flash object that defines a font's appearance

class FDTDefineEditText : public FDT {

public:
    FDTDefineEditText(FRect *_bounds,
                      U8 _hasFont,
                      U8 _hasMaxLength,
                      U8 _hasTextColor,
                      U8 _readOnly,
                      U8 _password,
                      U8 _multiline,
                      U8 _wordWrap,
                      U8 _hasText,
                      U8 _useOutlines,
                      U8 _border,
                      U8 _noSelect,
                      U8 _hasLayout,
                      U16 _fontID,
                      U16 _fontHeight,
                      FColor *_textColor,
                      U16 _maxLength,
                      U8 _alignment,
                      U16 _leftMargin,
                      U16 _rightMargin,
                      U16 _indent,
                      U16 _leading,
                      FString *_variableName,
                      FString *_initialText);
    ~FDTDefineEditText() override;

    U16 ID() override {
        return characterID;
    }

    void WriteToSWFStream(FSWFStream *_SWFStream) override;

private:
    FRect *bounds;
    U8 hasFont;
    U8 hasMaxLength;
    U8 hasTextColor;
    U8 readOnly;
    U8 password;
    U8 multiline;
    U8 wordWrap;
    U8 hasText;
    U8 useOutlines;
    U8 border;
    U8 noSelect;
    U8 hasLayout;
    U16 fontID;
    U16 fontHeight;
    FColor *textColor;
    U16 maxLength;
    U8 alignment;
    U16 leftMargin;
    U16 rightMargin;
    U16 indent;
    U16 leading;
    FString *variableName;
    FString *initialText;
    U16 characterID;

};

// A flash object that defines the font and formating of text characters in the record (flash 1.0)
// takes only RGB color values

class FDTDefineText : public FDT {

public:
    FDTDefineText(FRect *_textBounds, FMatrix *_textMatrix, int glyhpsInFont); // glyhpsInFont: how many characters are in the font?
    ~FDTDefineText() override;
    void AddTextRecord(FTextRecord *_textRec);
    U16 ID() override;
    void WriteToSWFStream(FSWFStream *_SWFStream) override;

private:
    U32 characterID;
    FRect *textBounds;
    FMatrix *textMatrix;
    std::list<FTextRecord *> textRecords{};
    U16 nIndexBits;

};

// A flash object that defines the font and formating of text characters in the record (flash 1.0)
// takes RGBA color values

class FDTDefineText2 : public FDT {

public:
    FDTDefineText2(FRect *_textBounds, FMatrix *_textMatrix, int glyhpsInFont);
    ~FDTDefineText2() override;
    void AddTextRecord(FTextRecord *_textRec);
    U16 ID() override;
    void WriteToSWFStream(FSWFStream *_SWFStream) override;

private:
    U32 characterID;
    FRect *textBounds;
    FMatrix *textMatrix;
    std::list<FTextRecord *> textRecords{};
    U16 nIndexBits;
};

// specifies text format changes in a flash DefineText object

class FTextChangeRecord : public FTextRecord {

public:
    FTextChangeRecord(U16 _hasFontFlag, U16 _hasColorFlag, U16 _hasXOffsetFlag, U16 _hasYOffsetFlag, U16 _fontID, U16 _fontHeight, FColor *_fontColor, S16 _xOffset, S16 _yOffset);
    ~FTextChangeRecord() override;

    U32 MinAdvanceBits() override {
        return 0;
    }

    U32 MinCodeBits() override {
        return 0;
    }

    void WriteToSWFStream(FSWFStream *_SWFStream, int advanceBits, int codeBits) override;

private:
//    U16 reserved;
    U16 hasFontFlag;
    U16 hasColorFlag;
    U16 hasYOffsetFlag;
    U16 hasXOffsetFlag;
    U16 fontID;
    FColor *fontColor;
    S16 xOffset;
    S16 yOffset;
    U16 fontHeight;
};

class FTextGlyphRecord : public FTextRecord {

public:
    FTextGlyphRecord();
    ~FTextGlyphRecord() override;

    void AddGlyphEntry(U16 code, U16 advance);
    void WriteToSWFStream(FSWFStream *_SWFStream, int advanceBits, int codeBits) override;

    U32 MinAdvanceBits() override; // number of bits needed to write the advance data
    U32 MinCodeBits() override; // number of bits needed to write the character code data

private:
    struct GlyphEntry {
        U16 code;
        U16 advance;
    };

    std::list<GlyphEntry> glyphEntries{};
};

#endif
