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

# xMfcExt.h

[Go to the documentation of this file.](xMfcExt_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: xMfcExt.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 6 $ $Author: Yury $ $Date: 6/23/97 5:22p $
00013 ************************************************************************/
00014 #ifndef __XMFCEXT_H
00015 #define __XMFCEXT_H
00016 
00017 //@class Extension manipulation. 
00018 //@base public | CString.
00019 class CExtension : public CString
00020 {
00021 public:
00022          BOOL     IsEqual     (LPCSTR ext);
00023    const CExtension& operator=(LPCTSTR lpsz);
00024    CString GetDefault   (void);
00025 
00026 };
00027 
00028 #ifdef _OS9
00029 #if !defined(_AFXWIN_INLINE) && defined (_AFXDLL)
00030 // Yury Kosov:
00031 // The EqualRect API provided by the Windows Portability Libraries for Macintosh
00032 // returns true if the input rectangles are both empty, even if they do not have
00033 // identical coordinates.
00034 inline BOOL CRect::EqualRect(LPCRECT lpRect) const 
00035 {
00036    return memcmp(this, lpRect, sizeof(RECT)) == 0;
00037 }
00038 inline BOOL CRect::operator==(const RECT& rect) const
00039 {
00040    return memcmp(this, &rect, sizeof(RECT)) == 0;
00041 }
00042 inline BOOL CRect::operator!=(const RECT& rect) const
00043 {
00044    return memcmp(this, &rect, sizeof(RECT)) != 0;
00045 }
00046 #endif
00047 #endif
00048 #endif//__XMFCEXT_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
