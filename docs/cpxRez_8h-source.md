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

# cpxRez.h

[Go to the documentation of this file.](cpxRez_8h.md)

<div class="fragment">

``` fragment
00001 /* KB  09/08/97  \ken5\include\3rdParty\cpxRez.h
00002 * @doc
00003 * $Workfile: cpxRez.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 3 $ $Author: Yury $ $Date: 5/13/97 7:57p $
00013 ************************************************************************/
00014 #ifndef __CPX_REZ_H
00015 #define __CPX_REZ_H
00016 
00017 #ifdef _MAC
00018 #define SystemSevenOrLater 1
00019 
00020 // File Open Dilaog resourses
00021 #define ID_FOPEN_REZ 25000
00022 #define ID_FLIST_REZ 25011
00023 #define ID_FPOPUP_REZ   25011
00024 #define  IDC_OK         1
00025 #define  IDC_CANCEL     2
00026 #define  IDC_EJECT      5
00027 #define  IDC_DESKTOP    6
00028 #define  IDC_FILELIST   7
00029 #define  IDC_HELPBTN    10
00030 #define  IDC_TYPELIST   11
00031 #define  IDC_RDONLY     12
00032 #define IDC_DLGTITLE 13
00033 #define  IDC_NEW        15
00034 #define IDC_FEDIT    16
00035 #define IDC_USER     17
00036 #define IDC_MYNEW       17
00037 
00038 #define ID_FSAVE_REZ 26000
00039 #define IDC_SAVETYPELIST 15
00040 #define IDC_NEWFOLDER    12
00041 #define IDC_SAVEEDIT     10
00042 
00043 #define ID_YESNO_ALERT  25100
00044 // CDEF resources
00045 #define  CDR_POPUP      1101
00046 #define CDR_HSLIDER     1105
00047 
00048 // Choose Directory Dialog
00049 #define  ID_CHOOSEDIR_REZ  25200
00050 #define ID_SELDIR       11
00051 
00052 #else //_MAC
00053 
00054 // Choose Directory Dialog
00055 // Note: these resource values must exactly
00056 // match the values the common dialog code
00057 // expects.  So, don't change these values.
00058 #define IDD_CPX_CHOOSEDIR               2000
00059 #define IDC_CPX_STATIC_FILE_NAME        1090
00060 #define IDC_CPX_FILE_NAME               1152
00061 #define IDC_CPX_FILE_LIST               1120
00062 #define IDC_CPX_STATIC_DIR              1088
00063 #define IDC_CPX_DIR_LIST                1121
00064 #define IDC_CPX_STATIC_TYPE             1089
00065 #define IDC_CPX_TYPE_LIST               1136
00066 #define IDC_CPX_STATIC_DRIVE            1091
00067 #define IDC_CPX_DRIVE_LIST              1137
00068 #define IDC_CPX_READ_ONLY               1040
00069 #define IDC_CPX_NETWORK                 1037
00070 #define IDC_CPX_HELP_BUTTON             1038
00071 #define IDC_CPX_NEW_BUTTON              1039
00072 
00073 
00074 #endif   //_MAC
00075 
00077 // NewDir dialog
00078 #define IDD_CPX_NEWDIR              2001
00079 #define IDC_CPX_NEW_DIR             1090
00080 //Comm Config dialog
00081 /*
00082 #define  IDD_COMM_CNFG  27100 // was 25100
00083 #define IDC_BUADRATE    1070
00084 #define IDC_BYTESIZE    1071
00085 #define IDC_STOPBITS    1072
00086 #define IDC_PARITY      1073
00087 */
00088 
00089 #endif//_CPX_REZ_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
