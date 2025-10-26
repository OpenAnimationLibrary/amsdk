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

# MessageR.h

[Go to the documentation of this file.](MessageR_8h.md)

<div class="fragment">

``` fragment
00001 // RC  12/23/97  \randy5\include\MessageR.h
00002 
00003 #define __MESSAGER_H
00004 
00005 #ifndef __DATATYPE_H
00006 #include "DataType.h"
00007 #endif
00008 #ifndef __EXPORTS_H
00009 #include "Exports.h"
00010 #endif
00011 
00012 class String;
00013 
00014 #define MR_OK               0
00015 #define MR_OKCANCEL         1
00016 #define MR_RETRYCANCEL      2
00017 #define MR_YESNO            3
00018 #define MR_YESNOCANCEL      4
00019 #define MR_ABORTRETRYIGNORE 5
00020 #define MR_SAVE             6
00021 #define MR_WARNING          7
00022 
00023 /* RETURN VALUES */
00024 #define MR_RETABORT   0
00025 #define MR_RETNO      0
00026 #define MR_RETCANCEL  -1
00027 #define MR_RETIGNORE  2
00028 #define MR_RETOK      1
00029 #define MR_RETRETRY   1
00030 #define MR_RETYES     1
00031 
00032 FILEIOEXPORT UINT MessageRequest( UINT  messageid,      UINT style = MR_OK, void *parent = NULL, UINT stringid = 128 /*IDR_MAINFRAME*/ );
00033 FILEIOEXPORT UINT MessageRequest( const String &message, UINT style = MR_OK, void *parent = NULL, UINT stringid = 128 /*IDR_MAINFRAME*/ );
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
