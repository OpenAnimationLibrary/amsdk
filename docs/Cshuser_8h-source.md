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

# Cshuser.h

[Go to the documentation of this file.](Cshuser_8h.md)

<div class="fragment">

``` fragment
00001 /***************************************************************************
00002  *
00003  * File: CSHUSER.H
00004  *
00005  * Descripton: ContextHelp Initialization Definition File
00006  *
00007  * Notes:
00008  *
00009  ****************************************************************************
00010  *
00011  * Copyright (c) 1995, 1996 - Blue Sky Software Corp. - All Rights Reserved
00012  *
00013  ***************************************************************************/
00014 
00015 #ifndef CSHUSER_H
00016 #define CSHUSER_H
00017 
00018 #ifdef __cplusplus
00019 extern "C" {
00020 #endif
00021 
00022 #ifdef __SC__
00023  #define WINAPI 
00024 #endif
00025 
00026 //**************************************************************************
00027 
00028 // User Application Initialization Functions
00029 
00030 BOOL WINAPI CSHInitialize (LPSTR a_pHelpFile, BOOL bContextMenu);
00031 BOOL WINAPI CSHRegisterDialog (HWND a_hDialog, long a_UniqueID);
00032 typedef BOOL (WINAPI *fnCSHREGISTERDIALOG) (HWND a_hDialog, long a_UniqueID);
00033 
00034 // Special Advanced Functionality Routines                             
00035 BOOL WINAPI CSHContextMenu(HWND hDlg, HWND hWndPoint, LPPOINT pPt);
00036 BOOL WINAPI CSHContextHelp(HWND hDlg, HWND hCtrl, int iContextType);
00037 
00038 #ifdef __cplusplus
00039  #define CSHHelpEnabled(_pCshOn) ::SendMessage(::GetFocus(), (UINT)RegisterWindowMessage("WM_CSHHASHELP"), (WPARAM)(0), (LPARAM)(LPINT)_pCshOn)
00040 #else
00041  #define CSHHelpEnabled(_pCshOn) SendMessage(GetFocus(), (UINT)RegisterWindowMessage("WM_CSHHASHELP"), (WPARAM)(0), (LPARAM)(LPINT)_pCshOn)
00042 #endif
00043 
00044 #define CSH_DLLNAME             "CSH.DLL"
00045 #define CSH_INITFUNCNAME        "CSHInitialize"
00046 #define CSH_REGISTERFUNCNAME    "CSHRegisterDialog"
00047 
00048 //**************************************************************************
00049 
00050 #ifdef __cplusplus
00051 }
00052 #endif
00053 
00054 #endif // CSHUSER_H
00055 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
