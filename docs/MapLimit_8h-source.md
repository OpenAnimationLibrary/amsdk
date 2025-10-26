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

# MapLimit.h

[Go to the documentation of this file.](MapLimit_8h.md)

<div class="fragment">

``` fragment
00001 // RC  12/23/1999  \Randy85\Include\MapLimit.h
00002 
00003 #ifndef __MAPLIMIT_H
00004 #define __MAPLIMIT_H
00005 
00006 enum MapLimit { ML_0, ML_1, ML_2, ML_4, ML_8, ML_16, ML_32, ML_64, ML_128, ML_256 };
00007 
00008 inline int MLToInt(const MapLimit &ml)
00009 {
00010    switch (ml) {
00011       case ML_0:
00012          return 0;
00013       case ML_1:
00014          return 1;
00015       case ML_2:
00016          return 2;
00017       case ML_4:
00018          return 4;
00019       case ML_8:
00020          return 8;
00021       case ML_16:
00022          return 16;
00023       case ML_32:
00024          return 32;
00025       case ML_64:
00026          return 64;
00027       case ML_128:
00028          return 128;
00029       case ML_256:
00030          return 256;
00031    }
00032    return -1;
00033 }
00034 #endif __MAPLIMIT_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
