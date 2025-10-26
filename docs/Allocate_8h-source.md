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

# Allocate.h

[Go to the documentation of this file.](Allocate_8h.md)

<div class="fragment">

``` fragment
00001 // BC  10/23/2003  \HBob110\Include\Allocate.h
00002 
00003 #define __ALLOCATE_H
00004 
00005 //#define _MEMDEBUG
00006 
00007 #ifndef __DATATYPE_H
00008 #include "DataType.h"
00009 #endif
00010 #ifndef __EXPORTS_H
00011 #include "Exports.h"
00012 #endif
00013 #ifndef __SINGLELO_H
00014 #include "SingleLo.h" // member
00015 #endif
00016 
00017 #ifdef _OS9
00018 #ifndef __CRITICAL_H
00019 #include "Critical.h"
00020 #endif
00021 #endif
00022 
00023 #ifdef _MEMDEBUG
00024    #define HASHNEW new (__FILE__, __LINE__)
00025 #else
00026    #define HASHNEW new
00027 #endif
00028 
00029 #ifdef _OS9
00030 #define BLOCKSIZE    0x100000  // 1meg
00031 #else
00032 #define BLOCKSIZE    0x008000  // 32k
00033 #endif
00034 #define USEDSIZE     (BLOCKSIZE/sizeof(Patch))
00035 #define NUMMEMHEADERS 100
00036 
00037 enum PoolType { POOL_EXT,
00038                 POOL_PATCH,
00039                 POOL_PARTICLE,
00040                 POOL_BITMAP,
00041                 POOL_SEG,
00042                 POOL_ACT,
00043                 POOL_CHOR,
00044                 POOL_ATT,
00045                 POOL_TEST,
00046                 POOL_SHADOW,
00047                 POOL_RADIOSITY,
00048                 POOL_STRING,
00049                 POOL_GASSIST,
00050                 POOL_LBUFF };
00051 
00052 class MemChunk {
00053 public:
00054    size_t                   size; // free size
00055    MemChunk                *next;
00056 #ifdef _MEMDEBUG
00057    MemChunk                *prev;
00058    char m_file[16];
00059    int m_line;
00060    PoolType type;
00061 #endif
00062 };
00063 
00064 class MemHeader {
00065 public:
00066    MemHeader               *next;
00067    MemChunk                *m_freehead;
00068 #ifdef _MEMDEBUG
00069    MemChunk                *m_allochead;
00070 #endif   
00071    char                    *block;
00072    char                    *lower;
00073    char                    *upper;   // actually upper + 1 
00074    size_t                   free, size, m_largestchunk;
00075 
00076    void FindLargestChunk();
00077 };
00078 
00079 class FILEIOEXPORT HashPool 
00080 {
00081 protected:
00082    MemHeader  *m_memheader;
00083 #ifdef _OSX
00084    CCriticalSection *m_criticalsection;
00085 #else
00086    CCriticalSection m_criticalsection;
00087 #endif
00088    size_t      m_total;
00089    PoolType    m_type;
00090    char       *m_name;
00091 
00092    MemHeader *m_freememheaders;
00093    char *m_memheaderlist;
00094 
00095 public:
00096    HashPool(PoolType type, char *name);
00097    ~HashPool();
00098 
00099 #ifdef _MEMDEBUG   
00100    void       *Alloc( size_t size, char *file, const int line );
00101 #else   
00102    void       *Alloc( size_t size );
00103 #endif   
00104    void        Free( void *p );
00105    void        FreePool();
00106    LONG        GetTotal() { return (LONG)m_total; }
00107    BOOL        IsEmpty() { return ( m_memheader == NULL ); }
00108 
00109 protected:
00110    MemHeader *GetFreeMemHeader();
00111    void MakeFreeMemHeaders();
00112    void PutFreeMemHeader( MemHeader *memheader );
00113    inline MemHeader *AllocateBlock( size_t minsize );
00114 };
00115 
00116 class SimpleChunk {
00117 public:
00118    SimpleChunk *next;
00119 };
00120 
00121 class FILEIOEXPORT SimplePool 
00122 {
00123 public:
00124    SimpleChunk *m_chunk;
00125    size_t       m_total, m_amount;
00126    UBYTE       *m_ptr;
00127 #ifdef _OSX
00128    CCriticalSection *m_criticalsection;
00129 #else
00130    CCriticalSection m_criticalsection;
00131 #endif
00132    
00133    SimplePool();
00134    ~SimplePool();
00135 
00136    void       *Alloc( size_t size );
00137    void        FreePool();
00138    void        Reset();
00139    size_t      GetTotal() { return (LONG)m_total; }
00140    void        AllocShitLoad( LONG size );
00141 };
00142 
00143 class Vector;
00144 #ifdef _MEMDEBUG
00145 #define AllocAct(s) ALLOCACT(s, __FILE__, __LINE__)
00146 FILEIOEXPORT void *ALLOCACT( size_t, char *file, const int line);
00147 
00148 #define AllocChor(s) ALLOCCHOR(s, __FILE__, __LINE__)
00149 FILEIOEXPORT void *ALLOCCHOR( size_t, char *file = __FILE__, const int line = __LINE__ );
00150 
00151 #define AllocAtt(s) ALLOCATT(s, __FILE__, __LINE__)
00152 FILEIOEXPORT void *ALLOCATT( size_t, char *file = __FILE__, const int line = __LINE__ );
00153 
00154 #define AllocSeg(s) ALLOCSEG(s, __FILE__, __LINE__)
00155 FILEIOEXPORT void *ALLOCSEG( size_t, char *file = __FILE__, const int line = __LINE__ );
00156 
00157 #define AllocExt(s) ALLOCEXT(s, __FILE__, __LINE__)
00158 FILEIOEXPORT void *ALLOCEXT( size_t, char *file = __FILE__, const int line = __LINE__ );
00159 
00160 #define AllocRadiosity(s) ALLOCRADIOSITY(s, __FILE__, __LINE__)
00161 FILEIOEXPORT void *ALLOCRADIOSITY( size_t, char *file = __FILE__, const int line = __LINE__ );
00162 
00163 #define AllocBitmap(s) ALLOCBITMAP(s, __FILE__, __LINE__)
00164 FILEIOEXPORT void *ALLOCBITMAP( size_t, char *file = __FILE__, const int line = __LINE__ );
00165 
00166 #define AllocParticle(s) ALLOCPARTICLE(s, __FILE__, __LINE__)
00167 FILEIOEXPORT void *ALLOCPARTICLE( size_t, char *file = __FILE__, const int line = __LINE__ );
00168 
00169 #define AllocPatch(s) ALLOCPATCH(s, __FILE__, __LINE__)
00170 FILEIOEXPORT void *ALLOCPATCH( size_t, char *file = __FILE__, const int line = __LINE__ );
00171 
00172 #define AllocLBuff(s) ALLOCLBUFF(s, __FILE__, __LINE__)
00173 FILEIOEXPORT void *ALLOCLBUFF( size_t, char *file = __FILE__, const int line = __LINE__ );
00174 
00175 #define AllocTest(s) ALLOCTEST(s, __FILE__, __LINE__)
00176 FILEIOEXPORT void *ALLOCTEST( size_t, char *file = __FILE__, const int line = __LINE__ );
00177 
00178 #define AllocShadow(s) ALLOCSHADOW(s, __FILE__, __LINE__)
00179 FILEIOEXPORT void *ALLOCSHADOW( size_t, char *file = __FILE__, const int line = __LINE__ );
00180 
00181 #define AllocString(s) ALLOCSTRING(s, __FILE__, __LINE__)
00182 FILEIOEXPORT void *ALLOCSTRING( size_t, char *file = __FILE__, const int line = __LINE__ );
00183 
00184 #define AllocGAssist(s) ALLOCGASSIST(s, __FILE__, __LINE__)
00185 FILEIOEXPORT void *ALLOCGASSIST( size_t, char *file, const int line);
00186 
00187 #else
00188 FILEIOEXPORT void *AllocAct( size_t );
00189 FILEIOEXPORT void *AllocChor( size_t );
00190 FILEIOEXPORT void *AllocAtt( size_t );
00191 FILEIOEXPORT void *AllocSeg( size_t );
00192 FILEIOEXPORT void *AllocExt( size_t );
00193 FILEIOEXPORT void *AllocBitmap( size_t );
00194 FILEIOEXPORT void *AllocParticle( size_t );
00195 FILEIOEXPORT void *AllocPatch( size_t );
00196 FILEIOEXPORT void *AllocLBuff( size_t );
00197 FILEIOEXPORT void *AllocTest( size_t );
00198 FILEIOEXPORT void *AllocShadow( size_t );
00199 FILEIOEXPORT void *AllocString( size_t );
00200 FILEIOEXPORT void *AllocRadiosity( size_t );
00201 FILEIOEXPORT void *AllocGAssist( size_t );
00202 #endif
00203 
00204 FILEIOEXPORT void  FreeAct( void * );
00205 FILEIOEXPORT void  FreeChor( void * );
00206 FILEIOEXPORT void  FreeAtt( void * );
00207 FILEIOEXPORT void  FreeSeg( void * );
00208 FILEIOEXPORT void  FreeExt( void * );
00209 FILEIOEXPORT void  FreeBitmap( void * );
00210 FILEIOEXPORT void  FreeParticle( void * );
00211 FILEIOEXPORT void  FreePatch( void * );
00212 FILEIOEXPORT void  FreeLBuff( void * );
00213 FILEIOEXPORT void  FreeTest( void * );
00214 FILEIOEXPORT void  FreeShadow( void * );
00215 FILEIOEXPORT void  FreeString( void * );
00216 FILEIOEXPORT void  FreeRadiosity( void * );
00217 FILEIOEXPORT void  FreeGAssist( void * );
00218 FILEIOEXPORT void *AllocZ( size_t );
00219 
00220 FILEIOEXPORT void *AllocSubPatch( size_t );
00221 FILEIOEXPORT void FreeSubPatchMemory();
00222 FILEIOEXPORT void FreeZBufferMemory();
00223 FILEIOEXPORT void FreePatchMemory();
00224 FILEIOEXPORT void FreeLBuffMemory();
00225 FILEIOEXPORT void FreeRadiosityMemory();
00226 FILEIOEXPORT void FreeAllPools();
00227 
00228 void FreePartialHSP( void );
00229 Vector *GetPtr( size_t );
00230 
00231 FILEIOEXPORT void *PlatformAlloc( size_t size );
00232 FILEIOEXPORT void PlatformFree( void *ptr );
00233 size_t PlatformSize( UBYTE *ptr );
00234 FILEIOEXPORT size_t TotalRAM();
00235 FILEIOEXPORT BOOL IsMemoryAvailable();
00236 FILEIOEXPORT void SetMemoryLimitBytes( size_t sizein_b);
00237 FILEIOEXPORT size_t GetMemoryLimitBytes();
00238 
00239 FILEIOEXPORT HashPool *GetActPool();
00240 FILEIOEXPORT HashPool *GetChorPool();
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
