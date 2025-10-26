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

# Perlin.h

[Go to the documentation of this file.](Perlin_8h.md)

<div class="fragment">

``` fragment
00001 // MH  16 May 1998
00002 
00003 #include "Exports.h"
00004 
00005 class Vector;
00006 
00007 #define LERP(t, a, b) ( a + t * (b - a) )
00008 
00009 PLUGINEXPORT void Perturb( const Vector &p, Vector &delta );
00010 PLUGINEXPORT float Noise3( const Vector & );
00011 
00012 PLUGINEXPORT float Contrast( float, float );
00013 PLUGINEXPORT float Brighten( float, float );
00014 
00015 PLUGINEXPORT void InitPerlinNoise( void );
00016 PLUGINEXPORT void FreePerlinNoise( void );
00017 
00018 PLUGINEXPORT float FractalTurb( const Vector &p, int octaves );
00019 
00020 PLUGINEXPORT float Noise3ForSampling( const Vector & );
00021 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
