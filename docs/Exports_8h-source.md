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

# Exports.h

[Go to the documentation of this file.](Exports_8h.md)

<div class="fragment">

``` fragment
00001 // NAP  2/26/2001  \Noel90\Include\Exports.h
00002 
00003 #define __EXPORTS_H
00004 
00005 #ifdef AGENTLIB
00006 #define AGENTEXPORT   __declspec(dllexport)
00007 #else
00008 #define AGENTEXPORT
00009 #endif
00010 
00011 #ifdef PATCHLIB
00012 #define PATCHEXPORT   __declspec(dllexport)
00013 #else
00014 #define PATCHEXPORT
00015 #endif
00016 
00017 #ifdef BITMAPLIB
00018 #define BITMAPEXPORT   __declspec(dllexport)
00019 #else
00020 #define BITMAPEXPORT
00021 #endif
00022 
00023 #ifdef FILEIOLIB
00024 #define FILEIOEXPORT   __declspec(dllexport)
00025 #else
00026 #define FILEIOEXPORT
00027 #endif
00028 
00029 #ifdef GASSISTLIB
00030 #define GASSISTEXPORT   __declspec(dllexport)
00031 #else
00032 #define GASSISTEXPORT
00033 #endif
00034 
00035 #ifdef MATRIXLIB
00036 #define MATRIXEXPORT   __declspec(dllexport)
00037 #else
00038 #define MATRIXEXPORT
00039 #endif
00040 
00041 #ifdef PLUGINLIB
00042 #define PLUGINEXPORT   __declspec(dllexport)
00043 #else
00044 #define PLUGINEXPORT
00045 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
