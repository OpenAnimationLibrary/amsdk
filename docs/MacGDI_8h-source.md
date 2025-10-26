<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# MacGDI.h

[Go to the documentation of this file.](MacGDI_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: MacGDI.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 2 $ $Author: Yury $ $Date: 6/22/97 10:30p $
00013 ************************************************************************/
00014 #ifndef __OS9GDI_H
00015 #define __OS9GDI_H
00016 
00017 #ifndef _OS9
00018 #define  cpxPolyBezier        PolyBezier
00019 #define cpxPolyBezierTo       PolyBezierTo
00020 #define cpxPolyPolygon        PolyPolygon
00021 #define cpxPolyPolyline       PolyPolyline
00022 #define cpxPolylineTo         PolylineTo
00023 #define cpxStrokePath         StrokePath
00024 #define cpxMaskBlt            MaskBlt
00025 #define cpxExtSelectClipRgn      ExtSelectClipRgn
00026 #define cpxExtCreateRegion    ExtCreateRegion
00027 #define cpxAbortPath       AbortPath
00028 #define cpxSelectClipPath     SelectClipPath
00029 #define cpxWidenPath       WidenPath
00030 #define cpxFlattenPath        FlattenPath
00031 #define cpxFillPath           FillPath
00032 #define cpxStrokeAndFillPath  StrokeAndFillPath
00033 #define cpxBeginPath       BeginPath
00034 #define cpxEndPath            EndPath
00035 #define cpxCloseFigure        CloseFigure
00036 #define cpxSetMiterLimit      SetMiterLimit
00037 #define cpxSetArcDirection    SetArcDirection
00038 #define cpxPolyDraw           PolyDraw
00039 #define cpxExtFloodFill       ExtFloodFill
00040 #define cpxArcTo           ArcTo
00041 #define cpxChord           Chord
00042 #define cpxAngleArc           AngleArc
00043 #define cpxSetMetaRgn         SetMetaRgn
00044 #define cpxSetColorAdjustment SetColorAdjustment
00045 
00046 
00047 #else // for _OS9
00048 
00049 BOOL XMAC_API cpxPolyBezier(HDC hdc,CONST POINT *lppt,DWORD cPoints);
00050 BOOL XMAC_API cpxPolyBezierTo(HDC hdc,CONST POINT *lppt,DWORD cCount);
00051 BOOL XMAC_API cpxMaskBlt(HDC hdcDest,int nXDest,int nYDest,int nWidth,int nHeight,
00052          HDC hdcSrc,int nXSrc,int nYSrc,HBITMAP hbmMask,int xMask,int yMask,DWORD dwRop);
00053 int    XMAC_API cpxExtSelectClipRgn(HDC hdc,HRGN hrgn,int fnMode);   
00054 HRGN XMAC_API cpxExtCreateRegion(CONST XFORM *lpXform,DWORD nCount,CONST RGNDATA *lpRgnData); 
00055 BOOL XMAC_API cpxAbortPath(HDC hdc);
00056 BOOL XMAC_API cpxSelectClipPath(HDC hdc,int iMode);
00057 BOOL XMAC_API cpxWidenPath(HDC hdc);   
00058 BOOL XMAC_API cpxFlattenPath(HDC hdc); 
00059 BOOL XMAC_API cpxFillPath(HDC hdc); 
00060 BOOL XMAC_API cpxStrokeAndFillPath(HDC hdc); 
00061 BOOL XMAC_API cpxStrokePath(HDC hdc);  
00062 BOOL XMAC_API cpxBeginPath(HDC hdc);   
00063 BOOL XMAC_API cpxEndPath(HDC hdc);  
00064 BOOL XMAC_API cpxCloseFigure(HDC hdc); 
00065 BOOL XMAC_API cpxSetMiterLimit(HDC hdc,FLOAT eNewLimit,PFLOAT peOldLimit); 
00066 int    XMAC_API cpxSetArcDirection(HDC hdc,int ArcDirection);  
00067 BOOL XMAC_API cpxPolyDraw(HDC hdc,CONST POINT *lppt,CONST BYTE *lpbTypes,int cCount);
00068 BOOL XMAC_API cpxPolyPolygon(HDC hdc,CONST POINT *lpPoints,CONST INT *lpPolyCounts,int nCount);
00069 BOOL XMAC_API cpxPolyPolyline(HDC hdc,CONST POINT *lppt,CONST DWORD *lpdwPolyPoints,DWORD cCount);
00070 BOOL XMAC_API cpxPolylineTo(HDC hdc,CONST POINT *lppt,DWORD cCount);
00071 BOOL XMAC_API cpxExtFloodFill(HDC hdc,int nXStart,int nYStart,COLORREF crColor,UINT fuFillType);
00072 BOOL XMAC_API cpxArcTo(HDC hdc,int nLeftRect,int nTopRect,int nRightRect,int nBottomRect,
00073          int nXRadial1,int nYRadial1,int nXRadial2,int nYRadial2);   
00074 BOOL XMAC_API cpxChord(HDC hdc,int nLeftRect,int nTopRect,int nRightRect,int nBottomRect,
00075           int nXRadial1,int nYRadial1,int nXRadial2,int nYRadial2); 
00076 BOOL XMAC_API cpxAngleArc(HDC hdc,int X,int Y,DWORD dwRadius,FLOAT eStartAngle,FLOAT eSweepAngle); 
00077 int  XMAC_API cpxSetMetaRgn(HDC hdc);  
00078 BOOL XMAC_API cpxSetColorAdjustment(HDC hdc,CONST COLORADJUSTMENT *lpca);  
00079  
00080 
00081  
00082 
00083 
00084 
00085 #endif // _OS9
00086 
00087 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
