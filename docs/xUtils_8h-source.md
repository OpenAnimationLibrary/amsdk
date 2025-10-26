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

# xUtils.h

[Go to the documentation of this file.](xUtils_8h.md)

<div class="fragment">

``` fragment
00001 /* KB  07/16/97  \ken5\include\3rdparty\xUtils.h
00002 * @doc
00003 * $Workfile: xUtils.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 11 $ $Author: Yury $ $Date: 4/29/97 4:00a $
00013 ************************************************************************/
00014 #ifndef __XUTILS_H
00015 #define __XUTILS_H
00016 
00017 CString     RandomStr         (DWORD min, DWORD max);
00018 DWORD    RandomInt         (DWORD min, DWORD max);
00019 char     RandomChar        (void);
00020 
00021 // I just can't remember CDialog::UpdateData()
00022 #define     TO_DLG         FALSE
00023 #define     FROM_DLG    TRUE
00024 
00025 
00026 #ifdef _OS9
00027 //@func void | SwapBytes | Swaps the bytes from Intel to Motorola format and
00028 //    vise versa.
00029 //@parm datatype *| data | Pointer to the data to be swapped. This can one of the: <nl>
00030 //<tab><tab>   int *    - pointer to the integer<nl>
00031 //<tab><tab>   WORD *   - pointer to the WORD<nl>
00032 //<tab><tab>   short *  - pointer to the short<nl>
00033 //<tab><tab>   long *   - pointer to the long<nl>
00034 //<tab><tab>   float *  - pointer to the float<nl>
00035 //<tab><tab>   double * - pointer to the double<nl>
00036 //<tab><tab>   CSize *  - pointer to <c CSize> structure<nl>
00037 //<tab><tab>   CPoint * - pointer to <c CPoint> structure<nl>
00038 //<tab><tab>   CRect *  - pointer to <c CRect> structure<nl>
00039 //<tab><tab>   BITMAPFILEHEADER *  - pointer to <c BITMAPFILEHEADER> structure<nl>
00040 //<tab><tab>   BITMAPINFOHEADER *  - pointer to <c BITMAPINFOHEADER> structure<nl>
00041 //<tab><tab>   DWORD *  - pointer to <c DWORD> structure<nl>
00042 //<tab><tab>   XFORM * - pointer to <c XFORM> structure<nl>
00043 //<tab><tab>   LOGPEN * - pointer to <c LOGPEN> structure<nl>
00044 //<tab><tab>   LOGPALETTE pointer to <c LOGPALETTE> structure<nl>
00045 //<tab><tab>   LOGFONT *  - pointer to <c LOGFONT> structure<nl>
00046 //<tab><tab>   EXTLOGFONTW *  - pointer to <c EXTLOGFONTW> structure<nl>
00047 //<tab><tab>   RGNDATAHEADER *  - pointer to <c RGNDATAHEADER> structure<nl>
00048 
00049 void SwapBytes(POINTL *aptl, DWORD cnt);
00050 void SwapBytes(POINTS *aptl, DWORD cnt);
00051 void SwapBytes(DWORD *adw, DWORD cnt);
00052 void SwapBytes(XFORM *xform);
00053 void SwapBytes(LOGPEN *lp);
00054 void SwapBytes(LOGBRUSH *lb);
00055 void SwapBytes(LOGPALETTE *lpal);
00056 void SwapBytes(LOGFONT *lf);
00057 //void   SwapBytes(EXTLOGFONTW *lfw); // KB
00058 void SwapBytes(BITMAPFILEHEADER* bmfHeader);
00059 void SwapBytes(BITMAPINFOHEADER *lpBMIH);
00060 void SwapBytes(RGNDATAHEADER *rgnHdr);
00061 
00062 
00063 
00064 //@devnote This portable function operates only on the Mac platform. It's defined to be nothing on Win32.
00065 inline void   SwapBytes(int *pLong)
00066 {  
00067    BYTE *pByte = (BYTE *)pLong;
00068    *pLong = (long)(pByte[3] << 24) 
00069          + (long)(pByte[2] << 16) 
00070          + (long)(pByte[1] << 8) 
00071          + pByte[0];
00072 }
00073 
00074 inline void   SwapBytes(unsigned int *pLong)
00075 {  
00076    BYTE *pByte = (BYTE *)pLong;
00077    *pLong = (long)(pByte[3] << 24) 
00078          + (long)(pByte[2] << 16) 
00079          + (long)(pByte[1] << 8) 
00080          + pByte[0];
00081 }
00082 
00083 inline void   SwapBytes(WORD *pWord)
00084 {  
00085    BYTE *pByte = (BYTE *)pWord;
00086    *pWord = (WORD)((WORD)(pByte[1] << 8) + pByte[0]);
00087 }
00088 
00089 inline void   SwapBytes(short *pWord)
00090 {  
00091    BYTE *pByte = (BYTE *)pWord;
00092    *pWord = (short)((short)(pByte[1] << 8) + pByte[0]);
00093 }
00094 
00095 inline void   SwapBytes(long *pLong)
00096 {  
00097    BYTE *pByte = (BYTE *)pLong;
00098    *pLong = (long)(pByte[3] << 24) 
00099          + (long)(pByte[2] << 16) 
00100          + (long)(pByte[1] << 8) 
00101          + pByte[0];
00102 }
00103 
00104 inline void   SwapBytes(DWORD *pDWord)
00105 {  
00106    BYTE *pByte = (BYTE *)pDWord;
00107    *pDWord = (DWORD)(pByte[3] << 24) 
00108          + (DWORD)(pByte[2] << 16) 
00109          + (DWORD)(pByte[1] << 8) 
00110          + pByte[0];
00111 }
00112 
00113 inline void   SwapBytes(float *pFloat)
00114 {  
00115    BYTE *pByte = (BYTE *)pFloat;
00116    *pFloat = (float) ((long)(pByte[3] << 24) 
00117          + (long)(pByte[2] << 16) 
00118          + (long)(pByte[1] << 8) 
00119          + pByte[0]);
00120 }
00121 
00122 inline void   SwapBytes(double *pDouble)
00123 {  
00124    DWORD *dwPtr = (DWORD *)(pDouble);
00125    DWORD dw;
00126    SwapBytes(&dwPtr[0]);
00127    SwapBytes(&dwPtr[1]);
00128    dw = dwPtr[0];
00129    dwPtr[0] = dwPtr[1];
00130    dwPtr[1] = dw;
00131 }
00132 
00133 inline void   SwapBytes(CRect *pRect)
00134 {
00135    SwapBytes(&pRect->top);
00136    SwapBytes(&pRect->bottom);
00137    SwapBytes(&pRect->left);
00138    SwapBytes(&pRect->right);
00139 }
00140 
00141 inline void   SwapBytes(CPoint *pPoint)
00142 {
00143    SwapBytes(&pPoint->x);
00144    SwapBytes(&pPoint->y);
00145 }
00146 
00147 inline void   SwapBytes(CSize *pSize)
00148 {
00149    SwapBytes(&pSize->cx);
00150    SwapBytes(&pSize->cy);
00151 }
00152 
00153 inline void   SwapBytes(RECTL *pRect)
00154 {
00155    SwapBytes(&pRect->top);
00156    SwapBytes(&pRect->bottom);
00157    SwapBytes(&pRect->left);
00158    SwapBytes(&pRect->right);
00159 }
00160 
00161 inline void   SwapBytes(POINTL *pPoint)
00162 {
00163    SwapBytes(&pPoint->x);
00164    SwapBytes(&pPoint->y);
00165 }
00166 
00167 inline void   SwapBytes(POINT *pPoint)
00168 {
00169    SwapBytes(&pPoint->x);
00170    SwapBytes(&pPoint->y);
00171 }
00172 
00173 inline void   SwapBytes(SIZEL *pSize)
00174 {
00175    SwapBytes(&pSize->cx);
00176    SwapBytes(&pSize->cy);
00177 }
00178 
00179 void   SwapBytes(POINTL *aptl, DWORD cnt);
00180 void   SwapBytes(POINTS *aptl, DWORD cnt);
00181 void   SwapBytes(DWORD *adw, DWORD cnt);
00182 void   SwapBytes(XFORM *xform);
00183 void   SwapBytes(LOGPEN *lp);
00184 void   SwapBytes(LOGBRUSH *lb);
00185 void   SwapBytes(LOGPALETTE *lpal);
00186 void   SwapBytes(LOGFONT *lf);
00187 //void   SwapBytes(EXTLOGFONTW *lfw); // KB
00188 void   SwapBytes(BITMAPFILEHEADER* bmfHeader);
00189 void   SwapBytes(BITMAPINFOHEADER *lpBMIH);
00190 void   SwapBytes(RGNDATAHEADER *rgnHdr);
00191 
00192 
00193 void   SwapBits (unsigned char * dp, unsigned char * sp, int len);
00194 
00195 // Some Pascal string helpers
00196 char *pStrCat(char * pStr1, char * pStr2);
00197 char *pStrCopy(char * pDesString, char * SrcString);
00198 
00199 
00200 // Dialog utilities
00201 #define ON 1
00202 #define OFF 0
00203 #define DI_ENABLE    0
00204 #define DI_DISABLE      255
00205 // Keys
00206 #define     KEY_HOME    01
00207 #define     KEY_END     04
00208 #define     KEY_ENTRKEY 03
00209 #define     KEY_BACK    8
00210 #define     KEY_TAB     9
00211 #define     KEY_PAGEUP     11
00212 #define     KEY_PAGEDOWN   12
00213 #define     KEY_RETURNKEY  13
00214 #define     KEY_ESCAPEKEY  27
00215 #define     KEY_LEFT    28
00216 #define     KEY_RIGHT      29
00217 #define     KEY_UP         30
00218 #define     KEY_DOWN    31
00219 #define     KEY_PLUS    43
00220 #define     KEY_MINUS      45
00221 #define     KEY_PERIODKEY  46
00222 #define     KEY_ZERO    48
00223 #define     KEY_NINE    57
00224 #define     KEY_DELKEY     127
00225 
00226 void    MacToggleCheck     (DialogPtr d, short i);
00227 void    MacToggleRadio     (DialogPtr d, short i, short first, short last);
00228 
00229 void    MacSetItemText     (DialogPtr d, short i, Str255 newText);
00230 void    MacGetItemText     (DialogPtr d, short i, Str255 getText);
00231 Boolean   MacIsDIHidden    (DialogPtr d, short i);
00232 void    MacEnableDItem     (DialogPtr d, short i, Boolean on);
00233 void    MacEnableDIText    (DialogPtr d, short i, Boolean on );
00234 void    MacSetButtonText   (DialogPtr d, short i, Str255 s);
00235 short   MacGetCtlMax    (DialogPtr d, short i);
00236 short   MacGetCtlMin    (DialogPtr d, short i);
00237 short   MacSetCtlMax    (DialogPtr d, short i, short v);
00238 short   MacSetCtlMin    (DialogPtr d, short i, short v);
00239 short   MacGetCtlValue     (DialogPtr d, short i);
00240 void    MacSetCtlValue     (DialogPtr d, short i, short newVal);
00241 
00242 
00243 
00244 // Note:  For the Mac, the X swap functions do nothing. This is the opposite of SwapBytes.
00245 #define  SwapBytesX(x)
00246 
00247 #else // Windows
00248 
00249 // For Intel platforms define them to nothing
00250 #define  SwapBytes(x)
00251 #define  SwapBits(x,y,z)
00252 
00253 inline void SwapBytesX(WORD *pWord)
00254 {  
00255    BYTE *pByte = (BYTE *)pWord;
00256    *pWord = (WORD)((WORD)(pByte[0] << 8) + pByte[1]);
00257 }
00258 
00259 inline void SwapBytesX(short *pWord)
00260 {  
00261    BYTE *pByte = (BYTE *)pWord;
00262    *pWord = (WORD)((WORD)(pByte[0] << 8) + pByte[1]);
00263 }
00264 
00265 inline void SwapBytesX(long *pLong)
00266 {  
00267    BYTE *pByte = (BYTE *)pLong;
00268    *pLong = (long)(pByte[0] << 24) 
00269          + (long)(pByte[1] << 16) 
00270          + (long)(pByte[2] << 8) 
00271          + pByte[3];
00272 }
00273 
00274 #endif
00275 
00276 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
