//BC  10/23/2003  \HBob110\Include\Allocate.h
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once
//#define _MEMDEBUG

#include "StdAfx.h"
#include "Exports.h"
#include "SingleLo.h"
#ifndef _CSTDINT_
#include <cstdint>
#endif

#ifdef _MEMDEBUG
#define HASHNEW new (__FILE__, __LINE__)
#else
#define HASHNEW new
#endif

#ifdef _WIN64
constexpr uint64_t BLOCKSIZE = 0x0001FFF8; //128k
#else
constexpr uint64_t BLOCKSIZE = 0x0001FFFC; //128k
#endif

constexpr uint64_t BLOCKSIZE_RENDER = 0x00200000; //2 MB
constexpr int NUMMEMHEADERS = 100;

#define BLOCKSIZE_RENDER_CHUNK ((uint64_t)(BLOCKSIZE_RENDER - sizeof(SimpleChunk)))
#define USEDSIZE               (BLOCKSIZE / sizeof(Patch))

enum struct PoolType {
    POOL_EXT,
    POOL_PATCH,
    POOL_PARTICLE,
    POOL_BITMAP,
    POOL_SEG,
    POOL_ACT,
    POOL_CHOR,
    POOL_ATT,
    POOL_TEST,
    POOL_STRING,
    POOL_GASSIST,
    POOL_LBUFF,
    POOL_PROP,
    POOL_UNDO,
    POOL_POLY,
    POOL_SHADOW,
    POOL_RADIOSITY
};

class MemChunk final {
public:
    uint64_t m_size{0}; //free size
    MemChunk *m_next{nullptr};
#ifdef _MEMDEBUG
    MemChunk *prev;
    char      m_file[16];
    int       m_line;
    PoolType  type;
#endif
};

constexpr uint64_t MemChunkSize = sizeof(MemChunk);

class MemHeader final {
public:
    MemHeader *m_next{nullptr};
    MemChunk *m_freehead{nullptr};
#ifdef _MEMDEBUG
    MemChunk  *m_allochead{nullptr};
#endif
    uint64_t m_free{0};
    uint64_t m_size{0};
    uint64_t m_largestchunk{0};
    uint8_t *m_block{nullptr};
    uint8_t *m_lower{nullptr};
    uint8_t *m_upper{nullptr}; //actually upper + 1

    void FindLargestChunk() noexcept;
};

class FILEIOEXPORT HashPool final {
    uint64_t m_total{0};
    MemHeader *m_memheader{nullptr};
    MemHeader *m_freememheaders{nullptr};
    uint8_t *m_memheaderlist{nullptr};
    CCriticalSection m_criticalsection{};
#ifdef _MEMDEBUG
    const char *m_name{nullptr};
    PoolType m_type{};
#endif

public:
#ifdef _MEMDEBUG
    HashPool(const PoolType &type, const char *name) noexcept : m_name(name), m_type(type) {}
#else
    HashPool() noexcept = default;
#endif
    ~HashPool() noexcept;

    HashPool(const HashPool &) = delete;
    HashPool(HashPool &&) = delete;
    HashPool &operator=(const HashPool &) = delete;
    HashPool &operator=(HashPool &&) = delete;

#ifdef _MEMDEBUG
    void *HashAlloc(uint64_t size, char *file, const int line) noexcept;
#else
    void *HashAlloc(uint64_t size) noexcept;
#endif
    void HashFree(void *p1) noexcept;
    void FreePool() noexcept;

    [[nodiscard]] uint64_t GetTotal() const noexcept {
        return m_total;
    }

    [[nodiscard]] bool IsEmpty() const noexcept {
        return m_memheader == nullptr;
    }

    [[nodiscard]] bool IsNotEmpty() const noexcept {
        return m_memheader != nullptr;
    }

protected:
    HASH_INLINE void MakeFreeMemHeaders() noexcept;
    HASH_INLINE void PutFreeMemHeader(MemHeader *memheader) noexcept;
    HASH_INLINE MemHeader *AllocateBlock(uint64_t minsize) noexcept;
    HASH_INLINE MemHeader *GetFreeMemHeader() noexcept;
};

class SimpleChunk final {
public:
    SimpleChunk *m_next{nullptr};
};

class FILEIOEXPORT SimplePool final {
    uint64_t m_total{0};
    uint64_t m_amount{0};
    SimpleChunk *m_chunk{nullptr};
    uint8_t *m_ptr{nullptr};

public:
    SimplePool() noexcept = default;
    ~SimplePool() noexcept;

    SimplePool(const SimplePool &) = delete;
    SimplePool(SimplePool &&) = delete;
    SimplePool &operator=(const SimplePool &) = delete;
    SimplePool &operator=(SimplePool &&) = delete;

    void *Alloc(uint64_t minsize) noexcept;
    void FreePool() noexcept;

    [[nodiscard]] uint64_t GetTotal() const noexcept {
        return m_total;
    }
};

//for transparent polys no real pool
class FILEIOEXPORT OGLPool final {
    uint8_t *m_ptr{nullptr};

public:
    OGLPool() noexcept = default;
    ~OGLPool() noexcept;

    OGLPool(const OGLPool &) = delete;
    OGLPool(OGLPool &&) = delete;
    OGLPool &operator=(const OGLPool &) = delete;
    OGLPool &operator=(OGLPool &&) = delete;
    void *Alloc(uint64_t minsize) noexcept;
    void FreePool() noexcept;
};

#ifdef _MEMDEBUG
#define AllocAct(s)       ALLOCACT(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCACT(size_t, char *file, const int line) noexcept;

#define AllocChor(s)      ALLOCCHOR(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCCHOR(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocAtt(s)       ALLOCATT(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCATT(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocSeg(s)       ALLOCSEG(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCSEG(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocExt(s)       ALLOCEXT(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCEXT(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocRadiosity(s) ALLOCRADIOSITY(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCRADIOSITY(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocBitmap(s)    ALLOCBITMAP(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCBITMAP(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocParticle(s)  ALLOCPARTICLE(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCPARTICLE(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocPatch(s)     ALLOCPATCH(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCPATCH(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocLBuff(s)     ALLOCLBUFF(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCLBUFF(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocTest(s)      ALLOCTEST(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCTEST(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocShadow(s)    ALLOCSHADOW(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCSHADOW(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocString(s)    ALLOCSTRING(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCSTRING(size_t, char *file = __FILE__, const int line = __LINE__) noexcept;

#define AllocGAssist(s)   ALLOCGASSIST(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCGASSIST(size_t, char *file, const int line) noexcept;

#define AllocUndo(s)      ALLOCUNDO(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCUNDO(size_t, char *file, const int line) noexcept;

#define AllocProp(s)      ALLOCPROP(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCPROP(size_t, char *file, const int line) noexcept;

#define AllocPoly(s)      ALLOCPOLY(s, __FILE__, __LINE__)
FILEIOEXPORT void *ALLOCPOLY(size_t, char *file, const int line) noexcept;

#else
FILEIOEXPORT void *AllocAct(uint64_t) noexcept;
FILEIOEXPORT void *AllocChor(uint64_t) noexcept;
FILEIOEXPORT void *AllocAtt(uint64_t) noexcept;
FILEIOEXPORT void *AllocSeg(uint64_t) noexcept;
FILEIOEXPORT void *AllocExt(uint64_t) noexcept;
FILEIOEXPORT void *AllocBitmap(uint64_t) noexcept;
FILEIOEXPORT void *AllocParticle(uint64_t) noexcept;
FILEIOEXPORT void *AllocPatch(uint64_t) noexcept;
FILEIOEXPORT void *AllocLBuff(uint64_t) noexcept;
FILEIOEXPORT void *AllocProp(uint64_t) noexcept;
FILEIOEXPORT void *AllocTest(uint64_t) noexcept;
FILEIOEXPORT void *AllocShadow(uint64_t) noexcept;
FILEIOEXPORT void *AllocString(uint64_t) noexcept;
FILEIOEXPORT void *AllocRadiosity(uint64_t) noexcept;
FILEIOEXPORT void *AllocGAssist(uint64_t) noexcept;
FILEIOEXPORT void *AllocUndo(uint64_t) noexcept;
FILEIOEXPORT void *AllocPoly(uint64_t) noexcept;
#endif

FILEIOEXPORT void FreeAct(void *) noexcept;
FILEIOEXPORT void FreeChor(void *) noexcept;
FILEIOEXPORT void FreeAtt(void *) noexcept;
FILEIOEXPORT void FreeSeg(void *) noexcept;
FILEIOEXPORT void FreeExt(void *) noexcept;
FILEIOEXPORT void FreeBitmap(void *) noexcept;
FILEIOEXPORT void FreeParticle(void *) noexcept;
FILEIOEXPORT void FreePatch(void *) noexcept;
FILEIOEXPORT void FreeLBuff(void *) noexcept;
FILEIOEXPORT void FreeProp(void *) noexcept;
FILEIOEXPORT void FreeTest(void *) noexcept;
FILEIOEXPORT void FreeShadow(void *) noexcept;
FILEIOEXPORT void FreeString(void *) noexcept;
FILEIOEXPORT void FreeRadiosity(void *) noexcept;
FILEIOEXPORT void FreeGAssist(void *) noexcept;
FILEIOEXPORT void FreeUndo(void *) noexcept;
FILEIOEXPORT void FreePoly(void *) noexcept;

FILEIOEXPORT void FreePatchMemory() noexcept;
FILEIOEXPORT void FreeLBuffMemory() noexcept;
FILEIOEXPORT void FreeRadiosityMemory() noexcept;
FILEIOEXPORT void FreeShadowMemory() noexcept;

//SimplePools
FILEIOEXPORT void *AllocZ(uint64_t) noexcept;
FILEIOEXPORT void *AllocSubPatch(uint64_t) noexcept;
FILEIOEXPORT void *AllocTemp(uint64_t) noexcept;
FILEIOEXPORT void FreeSubPatchMemory() noexcept;
FILEIOEXPORT void FreeTempMemory() noexcept;
FILEIOEXPORT void *AllocOGL(uint64_t) noexcept;
FILEIOEXPORT void FreeOGL() noexcept;
FILEIOEXPORT void FreeZBufferMemory() noexcept;
FILEIOEXPORT void FreeAllPools() noexcept;
FILEIOEXPORT uint64_t GetSubPatchPoolAmount() noexcept;
FILEIOEXPORT uint64_t GetPatchAmount() noexcept;

//diverse
FILEIOEXPORT void *PlatformAlloc(uint64_t size) noexcept;
FILEIOEXPORT void PlatformFree(void *header) noexcept;
FILEIOEXPORT uint64_t TotalRAM() noexcept;
FILEIOEXPORT uint64_t PeakRAM() noexcept;
FILEIOEXPORT void SetPeakRAM(bool init = true) noexcept;
FILEIOEXPORT bool IsMemoryAvailable() noexcept;
#ifndef _WIN64
FILEIOEXPORT void SetMemoryLimitBytes(UINT plimit_inbytes);
FILEIOEXPORT UINT GetMemoryLimitBytes();
FILEIOEXPORT int GetMemoryLimitGigaByte();
#endif

#ifdef _TESTPROPERTYALLOCS
size_t              PlatformSize(UBYTE *ptr);
FILEIOEXPORT size_t GetNumAllocs();
FILEIOEXPORT size_t GetNumRealAllocs();
FILEIOEXPORT size_t GetNumRealFrees();
FILEIOEXPORT void FreeAllMainPools() noexcept;

class AllocCounter {
public:
    AllocCounter() : m_startcount(GetNumAllocs()) {}
    [[nodiscard]] size_t GetCount() const {
        return GetNumAllocs() - m_startcount;
    }
private:
    size_t m_startcount;
};

template <class TYPE>
class AllocInfo {
public:
    AllocInfo() : count(counter.GetCount()) {}
    [[nodiscard]] size_t GetNumAllocs() const {
        return count;
    }
private:
    AllocCounter counter;
    TYPE         t;
    size_t       count;
};
#endif
