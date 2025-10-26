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

# FlockBuf.h

[Go to the documentation of this file.](FlockBuf_8h.md)

<div class="fragment">

``` fragment
00001 // KB  3/5/01  \Ken90\Include\FlockBuf.h
00002 
00003 #define __FLOCKBUF_H
00004 
00005 #ifndef __EXPORTS_H
00006 #include "Exports.h"
00007 #endif
00008 #ifndef __VECTOR_H
00009 #include "Vector.h"
00010 #endif
00011 #ifndef __FLOCKMAN_H
00012 #include "Flockman.h"
00013 #endif
00014 #ifndef __HASHTIME_H
00015 #include "HashTime.h"
00016 #endif
00017 #ifndef __ALLOCATE_H
00018 #include "Allocate.h"
00019 #endif
00020 
00021 class InfluenceShape;
00022 class PLUGINEXPORT  FlockBuf {
00023 public:
00024    Vector           p, worldp, worlddirection, prevpos, ulbounds, lrbounds;
00025    float            pbwidth, pbheight, pbdepth;
00026    InfluenceShape  *influenceshape;
00027    Vector           subdiv; // peerbox lattice dimensions
00028    int              numboids;
00029    Boid            *boids;
00030    PeerBox         *peerboxlist;
00031    Time             prevframe,
00032                     m_maxactionoffset;
00033 
00034    FlockBuf();
00035    ~FlockBuf() { Clear(); }
00036    FlockBuf &operator = ( const FlockBuf &other ) {
00037 //      don't allow flockbuf members to be copied.
00038       return *this;
00039    }
00040 
00041    PeerBox *CreatePeerBoxList();
00042    void DistributeBoids();
00043    void InitBoidList( int num );
00044    void Clear( void );
00045    float GetFallOffValue(const Vector &p);
00046    Boid *FindClosestNeighbor( Boid *boid, Boid *excludedboid );
00047 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
