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

# PtrMessa.h

[Go to the documentation of this file.](PtrMessa_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  1/13/2004  \DanLP110\Include\PtrMessa.h
00002 
00003 #define __PTRMESSA_H
00004 
00005 enum PtrMessage { PTM_DELETED=0,
00006                   PTM_RENAMED=1,
00007                   PTM_VALUECHANGED=2,
00008                   PTM_VALUESTORED=3,
00009                   PTM_MARKDEPENDENT=4,
00010                   PTM_GETPOINTERLIST=5,
00011                   PTM_NULLCHANGED=6,
00012                   PTM_SELECTIONCHANGED=7,
00013                   PTM_FPSCHANGED=8,     // fps =*((float*)lparam)
00014                   PTM_WORLDSTORED=9,
00015                   PTM_ENDLOAD=10,      // productversion = *((float *)lparam)
00016                   PTM_FORCEDESCRIPTION=11,
00017                   PTM_BUTTONPRESSED=12,
00018                   PTM_DRAW=13,
00019 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
