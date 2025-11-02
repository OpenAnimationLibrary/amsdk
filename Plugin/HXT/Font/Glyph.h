// KB  11/27/01  \Ken90\Plugin\HXT\FontMac\Glyph.h
// include geom.h before this
#pragma once

BOOL GetGlyphSplines(Subdiv *subdiv, int ch, const CString &facename, int weight, int is_italic, Vector *porigin, float scale);
BOOL GetSfnt(CString &facename);
void CloseSfnt();
