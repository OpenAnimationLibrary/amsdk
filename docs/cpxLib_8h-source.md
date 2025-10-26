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

# cpxLib.h

[Go to the documentation of this file.](cpxLib_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: cpxLib.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 9 $ $Author: Yury $ $Date: 6/22/97 10:30p $
00013 ************************************************************************/
00014 
00015 /*
00016 @topic Naming Convention |
00017    LibMac includes different classes and functions.
00018    All Macintosh specific functions are named <f MacFunctionName><nl>
00019    All portable functions are named <f cpxFunctionName><nl>
00020    Classes are named <f CPXClassName><nl>
00021 */
00022 
00023 #ifndef __CPX_LIB_H
00024 #define __CPX_LIB_H
00025 
00026 #if defined(VC_EXTRALEAN)
00027    #error Please, remove definition of VC_EXTRALEAN from stafx.h to use LibMac
00028 #endif
00029 
00030 
00031 #ifndef __XMAC_H
00032         #include "xMac.h"
00033 #endif
00034 
00035 #ifndef __XMFCEXT_H
00036    #include <xMfcExt.h>
00037 #endif
00038 
00039 #ifndef __XUTILS_H
00040    #include <xUtils.h>
00041 #endif
00042 
00043 #ifndef __OS9FILES_H
00044    #include <MacFiles.h>
00045 #endif
00046 
00047 #ifndef __CPX_REZ_H
00048    #include <cpxRez.h>
00049 #endif
00050 
00051 #ifndef __CPX_FILEDLG
00052    #include <cpxFileDlg.h>
00053 #endif
00054 
00055 #ifndef __MPROFILE_H
00056    #include <MProfile.h>
00057 #endif
00058 
00059 #ifndef __OS9SOUND_H
00060    #include <MacSound.h>
00061 #endif
00062 
00063 #ifndef __OS9GDI_H
00064    #include <MacGDI.h>
00065 #endif
00066 
00067 #ifndef __OS9PALETTE_H
00068    #include <Macintize.h>
00069 #endif
00070 
00071 #ifndef _OS9PRINT_H
00072    #include <MacPrint.h>
00073 #endif
00074 
00075 #ifndef __OS9_WPL_H
00076    #include <MacWPL.h>
00077 #endif
00078 
00079 #ifndef __CPXDIALOG_H
00080    #include <PXDialog.h>
00081 #endif
00082 
00083 #ifdef _DEBUG
00084    #if   defined(_MPPC_)
00085       #if !defined(_AFXDLL)   
00086          #define _XMAC_LIB_NAME "xMPMLibD.lib"
00087       #elif !defined(_XMAC_LIB)
00088          #define _XMAC_LIB_NAME "xPMxDllD.lib"
00089       #else 
00090          #define _XMAC_LIB_NAME "xMPMDllD.lib"
00091       #endif
00092    #elif defined(_68K_)
00093       #if !defined(_AFXDLL)   
00094          #define _XMAC_LIB_NAME "xM68LibD.lib"
00095       #else 
00096          #define _XMAC_LIB_NAME "xM68DllD.lib"
00097       #endif
00098    #elif !defined(_OS9)
00099       #if !defined(_AFXDLL)   
00100          #define _XMAC_LIB_NAME "xWLibD.lib"
00101       #elif !defined(_XMAC_LIB)
00102          #define _XMAC_LIB_NAME "xWxDllD.lib"
00103       #else
00104          #define _XMAC_LIB_NAME "xWDllD.lib"
00105       #endif
00106    #endif
00107 #else
00108    #if   defined(_MPPC_)
00109       #if !defined(_AFXDLL)   
00110          #define _XMAC_LIB_NAME "xMPMLibR.lib"
00111       #elif !defined(_XMAC_LIB)
00112          #define _XMAC_LIB_NAME "xPMxDllR.lib"
00113       #else 
00114          #define _XMAC_LIB_NAME "xMPMDllR.lib"
00115       #endif
00116    #elif defined(_68K_)
00117       #if !defined(_AFXDLL)   
00118          #define _XMAC_LIB_NAME "xM68LibR.lib"
00119       #else 
00120          #define _XMAC_LIB_NAME "xM68DllR.lib"
00121       #endif
00122    #elif !defined(_OS9)
00123       #if !defined(_AFXDLL)   
00124          #define _XMAC_LIB_NAME "xWLibR.lib"
00125       #elif !defined(_XMAC_LIB)
00126          #define _XMAC_LIB_NAME "xWxDllR.lib"
00127       #else 
00128          #define _XMAC_LIB_NAME "xWDllR.lib"
00129       #endif
00130    #endif
00131 #endif
00132 
00133 #ifndef _NOAUTOLIB
00134    #ifdef _XMAC_LIB_NAME
00135       #pragma message( "Requred linkage for LibMac: " _XMAC_LIB_NAME )
00136       #pragma comment(lib, _XMAC_LIB_NAME)
00137    #endif
00138 #endif 
00139 
00140 #endif//__CPX_LIB_H
00141 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
