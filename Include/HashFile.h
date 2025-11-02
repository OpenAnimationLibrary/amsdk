//BC  1/10/2005  \BobL120\Include\HashFile.h
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeMemberInit
// ReSharper disable CppClangTidyHicppMemberInit
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

#include "StrClass.h"
#include <afxtempl.h>
#include <exception>

class StreamErrorException final : public std::exception {};

constexpr UINT ENDHEADERFLAG = 0x20000000;//536870912;
constexpr UINT BINARYLABELFLAG = 0x40000000;//1073741824;
constexpr UINT BINARYHEADERFLAG = 0x80000000; //KNC , INT_MAX+1 !

//productversion = 5.0 // original version 5.0 set in constructor
//productversion = 6.0 // bitfields were moved from CP to SegmentCP/ChannelCP to add ZEROSLOPE interpolation
//productversion = 6.1 // 0-based/time-based frame numbering, focallength corrected
//productversion = 7.0 // time written in ticks (1/135000 second)
//productversion = 8.51 // fixed spherical combiner ring sizes scaled by UNIT
//productversion = 9.0 // Um... total rewrite
//productversion = 9.01 // 9.0 now has compact muscle
//productversion = 9.02 // 9.0o stores default pose application on userproperty not relation
//PRODUCTVERSION = 9.03 // stores constdrivers different
//PRODUCTVERSION = 9.04 // loads > 8.5, < 9.04 camera.m_globalambience with correct factor
//PRODUCTVERSION = 9.50 // property drivers that are not in actions now save as regular children of the HashObject instead of embedded in the Property
//PRODUCTVERSION = 9.51 // attempt to fix 9.5o animobjectshortcuts and emptydrivers with m_matchname == ""
//PRODUCTVERSION = 9.52 // ignore defalutvalue and displayposeslider labels on load on constdrivers
//PRODUCTVERSION = 9.53 // destroy bogus (all) constdrivers on object cache property from < 9.53
//PRODUCTVERSION = 10.00 // same as 9.53
//PRODUCTVERSION = 10.01 // matchnames of linked objects contains full path in memory and relative path on disk objects|((char)254)thom((char)255)mdl.property
//PRODUCTVERSION = 10.02 // repairs previous versions bogus emptydrivers under root folders
//PRODUCTVERSION = 10.03 // uses quotes to seperate linked object matchnames objects|"thom.mdl".property
//PRODUCTVERSION = 10.04 // distort boxes are modeled longer if the res is larger.
//PRODUCTVERSION = 10.05 // removed unnecessary leaf level empty drivers from motion files
//PRODUCTVERSION = 10.06 // to fix earlier texture node properties being not set on blobby caches etc
//PRODUCTVERSION = 10.07 // to fix fig cache actionshortcutcontainer being at head instead of tail so it loads constdrivers correctly
//PRODUCTVERSION = 10.50  // Same as 10.05
//PRODUCTVERSION = 10.51  // Same as 10.07
//PRODUCTVERSION = 10.52  // New specularsize calculation
//PRODUCTVERSION = 10.53  // Duplicate constraints are no longer caused by copy/paste, or removed on load.
//PRODUCTVERSION = 10.54  // Fixed lightlist nodes using cache treename in figure::onnotifyendprojectload and save
//PRODUCTVERSION = 10.55  // Moved constraints that are under transforms to be under parent (Poses still had issue and now are fixed)
//PRODUCTVERSION = 10.56  // Changed ambiance to be a color
//PRODUCTVERSION = 11.00  // New release, also rotatedrivers in poses don't save parenttobone
//PRODUCTVERSION = 11.01  // Move chor group container to top of sibling list
//PRODUCTVERSION = 11.02  // Fixed reversed z for XY plane vertical markers (left or right view in horizontal ruler)
//PRODUCTVERSION = 11.03  // Convert 1DMultiDs to Channels for niels
//PRODUCTVERSION = 11.04  // Convert hair density from density along side to area density (so its linear)
//PRODUCTVERSION = 11.50  //
//PRODUCTVERSION = 11.51  // Convert hair density from density along side to area density (so its linear)
//PRODUCTVERSION = 12.00  // BufferShortcut relative paths to image 08/08/05
//PRODUCTVERSION = 13.00  // Subversion compatible files  // Support for binary files (HAMR).
//PRODUCTVERSION = 13.01  // .hinfo files to remove data that doesn't effect renderings to lower SVN conflicts
//PRODUCTVERSION = 13.02  // bias values in channels are scaled to make the surrounding bounds nearly square
//PRODUCTVERSION = 13.03  // marker values along the Z axis are negated to have the correct value.
//PRODUCTVERSION = 13.04  // camera view indexes always count non-hierarchical cameras first.
//PRODUCTVERSION = 13.05  // hooks don't save modelp
//PRODUCTVERSION = 13.06  // correctly load old nested post effect caches (sub post effects become root post effects)
//PRODUCTVERSION = 13.07  // Property Save crash and extra attributes in figure, for possible backward load
//PRODUCTVERSION = 13.08  // prior v13 ChannelCP flags corrupted by intel mac
//PRODUCTVERSION = 13.08  // Alpah 1
//PRODUCTVERSION = 14.00  // unknown see svn log
//PRODUCTVERSION = 14.01  // DummyBufferShortcuts creation on backward load
//PRODUCTVERSION = 14.02  // Orphaned CameraDummyBufferShortcut not saved to prevent spread
//PRODUCTVERSION = 14.03  // image.timing.frame instead of image.frame
//PRODUCTVERSION = 14.04  // aob lights name set on load
//PRODUCTVERSION = 14.05  // clip property crop within cache option
//PRODUCTVERSION = 14.06  // clip property range IDL changed to not collide with camera range via camera.rendersettings.fog image
//PRODUCTVERSION = 14.07  // puts camera rotos in a RotoContainer
//PRODUCTVERSION = 15.00  // light lists use matchname
//#define PRODUCTVERSION  18.00
//#define PRODUCTVERSION 19.00
#define PRODUCTVERSION 19.50f

//define OLDESTOVERWRITABLEVERSION 8.5F
//define OLDESTOVERWRITABLEVERSION 9.0f
//#define OLDESTOVERWRITABLEVERSION 13.00f //used with m_disableoldsave, ie v9-v12 can't load v13 for sure so force a save as in v13
#define OLDESTOVERWRITABLEVERSION 15.00f//temp to protect people from alpha

//this will probably usually be a guess until the handoff when a version goes from alpha to beta, ie v13's use in two, when v14 was getting usable, and we wanted sss etc
//define NEWESTOVERWRITABLEVERSION 14.0 /v13 when TWO was getting ready to switch to v14.0
//#define TO_NEW_TOOVERWRITEVERSION 15.0 //used with DISABLESAVEOVERNEW, ie v13 should warn when saving over a v14 file
#define TO_NEW_TOOVERWRITEVERSION 20.00f

class FileStream;
class MemoryStream;
class Time;
class Vector2;
class Vector;
class Vector4;
class RGBFloat;
class ColorBuf;
class TimeRange;
class PatchID;
class Rotate;
class Matrix33;
class Matrix34;
class Matrix44;
class Quaternion;
class RenderInfoParms;
class RenderStatusInfo;
class StreamMsg;
class TreeObject;

constexpr int MAXSTRING = 256;
constexpr int NUMSTATUSSUBDIVISIONS = 100;
constexpr int HEADERSTRINGSIZE = 80;

class FILEIOEXPORT Label final {
public:
    char labelstring[HEADERSTRINGSIZE]{};
    int id{-1};

    Label() noexcept = default;
    // ReSharper disable once CppNonExplicitConvertingConstructor
    Label(int pid);
    explicit Label(const char *text);

    friend bool operator==(const Label &li,const Label &re) {
        const std::string li_string = li.labelstring;
        const std::string re_string = re.labelstring;
        return li_string == re_string;
    }

    friend bool operator!=(const Label &li,const Label &re) {
        return !operator==(li, re);
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    char *GetText() noexcept {
        return (char *)labelstring;
    }
};

class FILEIOEXPORT Header {
public:
    char headerstring[HEADERSTRINGSIZE]{};
    int id{-1};

    Header() noexcept = default;
    explicit Header(int pid);

    Header(const int pid, const char *buffer) noexcept : id(pid) {
        strcpy_s((char *)headerstring, HEADERSTRINGSIZE, buffer);
    }

    friend bool operator==(const Header &li, const Header &re) noexcept {
        return li.id == re.id;
    }

    friend bool operator!=(const Header &li, const Header &re) noexcept {
        return li.id != re.id;
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    char *GetText() noexcept {
        return (char *)headerstring;
    }
};

class FILEIOEXPORT EndHeader final : public Header {
public:
    EndHeader() noexcept = default;
    explicit EndHeader(int pid);

    EndHeader(const int pid, const char *buffer) noexcept {
        id = (UINT)pid | ENDHEADERFLAG; //may already be tagged as endheader, but just in case.
        strcpy_s((char *)headerstring, HEADERSTRINGSIZE, buffer);
    }

    friend bool operator==(const EndHeader &li, const EndHeader &re) noexcept {
        return li.id == re.id;
    }

    friend bool operator!=(const EndHeader &li, const EndHeader &re) noexcept {
        return li.id != re.id;
    }
};

class FILEIOEXPORT StreamBOOL final {
public:
    bool m_bool{false};

    StreamBOOL() noexcept = default;
    explicit StreamBOOL(const bool pbool) noexcept : m_bool(pbool) {}
};

FILEIOEXPORT int GetLabelIDFromText(const char *string);
FILEIOEXPORT int GetHeaderIDFromText(const char *string);
FILEIOEXPORT bool GetLabelTextFromID(int pid, char *string);
FILEIOEXPORT void GetHeaderTextFromID(int keyid, char *resultstring) noexcept;
FILEIOEXPORT void HeaderMapSetAt(const char *text, int hotid);
FILEIOEXPORT void FreeHeaderMap();
FILEIOEXPORT String GetHeaderStringFromID(int keyid);
FILEIOEXPORT bool IsFileOfType(const String &pfilename, int headerid);
FILEIOEXPORT bool IsFileOfTypeHash(String &pfilename);
FILEIOEXPORT void FreeHashFileToken() noexcept;

#include"EnumClass.h"

enum class FileMode : uint16_t {
    HS_ASCII        = 0,
    HS_STORE        = 0,
    HS_LOAD         = 1,
    HS_BINARY       = 2,
    HS_BYTESWAP     = 4,
    HS_APPEND       = 8,
    HS_FAILED       = 16,
    HS_HASH         = 32,
    HS_DONTASK      = 64,
    HS_DONTPROGRESS = 128,
};

template<>
struct EnableBitMaskOperators<FileMode> {
    static constexpr bool Enable = true;
};

//TODO change m_filesize to ULONGLONG, because LONG can handle only files smaller 2 Gigabyte (can be exceeded by baked particle systems)
//seek need changes too ,see FileStream::Seek for description (fseek can fail for textmode opened files)
class FILEIOEXPORT HashStream {
public:
    enum SeekMode {
        HS_BEGINNING,
        HS_END,
        HS_OFFSET
    };

protected:
    String m_prevprogresstext;
    ULONGLONG m_filesize{0};
    ULONGLONG m_nextstatuspos{0};
    LONG m_statusposincrement{0};
    FileMode m_mode{FileMode::HS_ASCII};

// @formatter:off
    union {
        BITFIELDS8 m_HashStream_flags{16}; // m_writestringcounts = true;
        struct {
            BITFIELDS8 m_bwasprogressinitializedbyme : 1,//
            m_passedeol : 1,//
            m_IsHeaderLine : 1, //KNC added for binary file parsing
            m_IsLabelLine : 1, //KNC added for binary file parsing
            m_writestringcounts : 1,//
            m_isdisplayingmessage : 1,//
            m_isprogressinited : 1;//
        };
    };
// @formatter:on

    void InitProgress(const String &filename);
    void UnInitProgress() noexcept;

public:
    String m_filename;
    float m_productversion{5.F};
    ULONGLONG m_BeginLinePos{0}; //KNC added for binary file parsing
    TreeObject *m_loadchildobject{nullptr};

    HashStream() noexcept = default;

    virtual ~HashStream() {
        UnInitProgress();
    }

    HashStream(const HashStream &) = delete;
    HashStream(HashStream &&) = delete;
    HashStream &operator=(const HashStream &) = delete;
    HashStream &operator=(HashStream &&) = delete;

#ifdef _MEMDEBUG
    void      *operator new(const size_t size, char *file, const int line) {
        return ALLOCEXT(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocExt(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeExt(ptr);
    }

    //Attributes
    [[nodiscard]] bool IsLoading() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_LOAD);
    }

    [[nodiscard]] bool IsStoring() const noexcept {
        return !IsLoading();
    }

    [[nodiscard]] bool IsAppend() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_APPEND);
    }

    [[nodiscard]] bool IsBinary() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_BINARY);
    }

    void OnBinary() noexcept {
        m_mode |= FileMode::HS_BINARY;
    }

    [[nodiscard]] bool IsAscii() const noexcept {
        return !IsBinary();
    }

    void OnAscii() noexcept {
        m_mode |= FileMode::HS_ASCII;
    }

    [[nodiscard]] bool IsHash() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_HASH);
    }

    [[nodiscard]] bool IsByteSwap() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_BYTESWAP);
    }

    [[nodiscard]] bool IsDontAsk() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_DONTASK);
    }

    [[nodiscard]] bool IsDontProgress() const noexcept {
        return static_cast<bool>(m_mode & FileMode::HS_DONTPROGRESS);
    }

    void OnFailed() noexcept {
        m_mode |= FileMode::HS_FAILED;
    }

    void OffFailed() noexcept {
        m_mode &= ~FileMode::HS_FAILED;
    }

    bool IsFailed() noexcept {
        const bool rval = static_cast<bool>(m_mode & FileMode::HS_FAILED);
        OffFailed();
        return rval;
    }

    void SetMode(const FileMode pmode) noexcept {
        m_mode = pmode;
    }

    [[nodiscard]] FileMode GetMode() const noexcept {
        return m_mode;
    }

    bool SkipPast(UINT pid);
    void SkipWhite();
    void ReadPastEOL();

    [[nodiscard]] bool DidPassEOL() const noexcept {
        return (bool)m_passedeol;
    }

    [[nodiscard]] bool IsWriteStringCounts() const noexcept {
        return (bool)m_writestringcounts;
    }

    void SetWriteStringCounts(const bool writestringcounts) noexcept {
        m_writestringcounts = writestringcounts;
    }

    CRuntimeClass *PASCAL LoadRuntimeClass(UINT *pwSchemaNum);
    void StoreRuntimeClass(const CRuntimeClass *rtc);

    //Operations
    //PURE VIRTUALS
    virtual ULONGLONG ReadC(void *buf, ULONGLONG count) = 0;
    virtual void Read(void *buf, LONG count) = 0;// Leave for Backward Compatibility with Plugins
    virtual void Write(const void *buf, ULONGLONG count) = 0;
    virtual void Flush() = 0;
    virtual void Close() = 0;
    virtual bool ReadLine(String &line) = 0; //READS UP TO nl, STORES IN STRING
    virtual bool ReadLine(MemoryStream &stream) = 0; //READS UP TO nl, STORES IN MemoryStream (BINARY OR ASCII matches this)
    virtual void ParseString(String &token) = 0;
    virtual void ParseToken(String &token) = 0;
    virtual void ParseToken(char *token, char delim) = 0;
    virtual void Seek(LONGLONG pos, SeekMode seekmode) = 0;
    virtual ULONGLONG GetPos() = 0;
    virtual bool VirtualEof() = 0;
    //VIRTUALS
    virtual bool IsHeader();
    virtual bool IsHeaderFromAnyVersion();
    virtual bool IsLabel();
    virtual HashStream *GetInfoStream() noexcept; //returns this. FileStreams should override to a filename.ext.hinfo file to place .hinfo settings to reduce SVN conflicts
    virtual void SetStatusMeter();

    //reading and writing strings
    void WriteLine(const String &string); //AUTOMATICALLY APPENDS A nl AT END OF STRING (BINARY OR ASCII)
    bool SkipHeader(const Header &header);
    String ReadString(char delimit);
    void ParseToken(String &token, char delim);

    //Object I/O is pointer based to avoid added construction overhead.
    //Use the Serialize member function directly for embedded objects.
    /*   friend HashStream&  operator<<(HashStream& hs, const HashObject* hob);
       friend HashStream& AFXAPI operator>>(HashStream& hs, HashObject*& hob);
       friend HashStream& AFXAPI operator>>(HashStream& hs, const HashObject*& hob);*/

    //insertion operations
    HashStream &operator <<(bool bo);
    HashStream &operator <<(char ch);
    HashStream &operator <<(SBYTE sb);
    HashStream &operator <<(UBYTE ub);
    HashStream &operator <<(SSHORT ss);
    HashStream &operator <<(USHORT us);
    HashStream &operator <<(int i);
    HashStream &operator <<(UINT ui);
    HashStream &operator <<(LONG l);
    HashStream &operator <<(ULONG ul);
    HashStream &operator <<(LONGLONG ll); //the same as int64_t
    HashStream &operator <<(ULONGLONG ull);//the same as uint64_t
    HashStream &operator <<(float float_value);
    HashStream &operator <<(double double_value);
    HashStream &operator <<(const char *text);
    HashStream &operator <<(const std::string &stdstring);//duplicate with newstring
    HashStream &operator <<(const String &string);
    HashStream &operator <<(Time time);
    HashStream &operator <<(const Vector2 &v);
    HashStream &operator <<(const Vector &v);
    HashStream &operator <<(const RGBFloat &v);
    HashStream &operator <<(const ColorBuf &cb);
    HashStream &operator <<(const BITMAPINFO &bi);
    HashStream &operator <<(const BITMAPINFOHEADER &h);
    HashStream &operator <<(const BITMAPFILEHEADER &h);
    HashStream &operator <<(HICON &hicon);
    HashStream &operator <<(const TimeRange &tr);
    HashStream &operator <<(const PatchID &patchid);
    HashStream &operator <<(const Label &lb);
    HashStream &operator <<(const Header &hd);
    HashStream &operator <<(const StreamBOOL &sb);
    HashStream &operator <<(const Rotate &rot);
    HashStream &operator <<(const Vector4 &v);
    HashStream &operator <<(const Matrix33 &m);
    HashStream &operator <<(const Matrix34 &m);
    HashStream &operator <<(const Matrix44 &m);
    HashStream &operator <<(const Quaternion &q);
    HashStream &operator <<(const COleDateTime &dateSrc);
    HashStream &operator <<(const CTime &dateSrc);

    HashStream &operator <<(HashStream & (__cdecl *function)(HashStream &)) noexcept {
        (*function)(*this);
        return *this;
    }

    //extraction operations
    HashStream &operator >>(bool &bo);
    HashStream &operator >>(char &ch);
    HashStream &operator >>(SBYTE &sb);
    HashStream &operator >>(UBYTE &ub);
    HashStream &operator >>(SSHORT &sw);
    HashStream &operator >>(USHORT &uw);
    HashStream &operator >>(int &i);
    HashStream &operator >>(UINT &ui);
    HashStream &operator >>(LONG &l);
    HashStream &operator >>(ULONG &ul);
    HashStream &operator >>(LONGLONG &ll);//the same as int64_t
    HashStream &operator >>(ULONGLONG &ull);
    HashStream &operator >>(float &float_value);
    HashStream &operator >>(double &d);
    HashStream &operator >>(String &string);
    HashStream &operator >>(Vector2 &v);
    HashStream &operator >>(Vector &v);
    HashStream &operator >>(Vector4 &v);
    HashStream &operator >>(Matrix33 &m);
    HashStream &operator >>(Matrix34 &m);
    HashStream &operator >>(Matrix44 &m);
    HashStream &operator >>(Quaternion &q);
    HashStream &operator >>(Rotate &rot);
    HashStream &operator >>(Time &time);
    HashStream &operator >>(TimeRange &tr);
    HashStream &operator >>(RGBFloat &c);
    HashStream &operator >>(ColorBuf &cb);
    HashStream &operator >>(HICON &hicon);
    HashStream &operator >>(PatchID &patchid);
    HashStream &operator >>(Label &lb);
    HashStream &operator >>(Header &hd);
    HashStream &operator >>(StreamBOOL &sb);
    HashStream &operator >>(BITMAPINFOHEADER &h);
    HashStream &operator >>(BITMAPFILEHEADER &h);
    HashStream &operator >>(COleDateTime &dateSrc);
    HashStream &operator >>(CTime &dateSrc);
};

FILEIOEXPORT HashStream &sp(HashStream &hs);
FILEIOEXPORT HashStream &spb(HashStream &hs);
FILEIOEXPORT HashStream &nl(HashStream &hs);
FILEIOEXPORT HashStream &nlb(HashStream &hs);
FILEIOEXPORT HashStream &tab(HashStream &hs);
FILEIOEXPORT HashStream &tabb(HashStream &hs);

class PathAlias;
class FileAlias;

class FILEIOEXPORT FileStream final : public HashStream {
protected:
    static CList<String, String &> m_failedloadlist;
    static PathAlias *m_pathaliashead;
    static FileAlias *m_filealiashead;
    static BOOL m_bCancelAll;

    CStdioFile m_file{};
    String m_tempname;
    FileStream *m_infofs{nullptr};

public:
    FileStream() noexcept = default;
    ~FileStream() override;

    FileStream(const FileStream &) = delete;
    FileStream(FileStream &&) = delete;
    FileStream &operator=(const FileStream &) = delete;
    FileStream &operator=(FileStream &&) = delete;

    bool Open(const String &filename, FileMode fmode = FileMode::HS_ASCII); //DEFAULT IS 0, WHICH IS STORING, ASCII NOBYTESWAP, NOTAPPENDING
    bool Open(String &filename, FileMode fmode = FileMode::HS_ASCII); //Keep for backward compat w/ plugins
    //bool    Open(int filenumber);
    [[nodiscard]] bool Eof() const; //gotta keep this old one around, or it invalidates plugins
    [[nodiscard]] ULONGLONG GetLength() const noexcept {
        return m_filesize;
    }

    bool VirtualEof() override;
    ULONGLONG ReadC(void *buf, ULONGLONG count) override;
    void Read(void *buf, LONG count) override;// Leave for Backward Compatibility with Plugins
    void Write(const void *buf, ULONGLONG count) override;
    void Flush() override;
    void Close() override;
    bool ReadLine(String &line) override; //READS UP TO nl, STORES IN STRING
    bool ReadLine(MemoryStream &stream) override; //READS UP TO nl, STORES IN MemoryStream (BINARY OR ASCII matches this)
    void ParseString(String &token) override;
    void ParseToken(String &token) override;
    void ParseToken(char *token, char delim) override;
    void Seek(LONGLONG pos, SeekMode seekmode) override;
    ULONGLONG GetPos() override;
    HashStream *GetInfoStream() noexcept override; //creates and opens filename.ext.hinfo or returns it if it already exists. close closes it too

    static bool FindAliasAsk(String &filename);
    static bool FindFileAlias(String &filename) noexcept;
    static bool FindFileAliasNameOnly(String &filename);
    static bool FindPathAlias(String &pathname);
    static bool HasFileAliases() noexcept ;
    static void AddFileAlias(const String &oldfilename, const String &newfilename);
    static void AddPathAlias(const String &oldpathname, const String &newpathname);
    static void FreeFileAliases() noexcept;
    static void FreePathAliases() noexcept;
    static bool FindAlias(String &filename);
    static bool IsInFailedList(const String &filename);
    static void ClearFailedList();
    static void ResetCancelAll() noexcept;
};

class FILEIOEXPORT MemoryStream : public HashStream {
public:
    char *m_buf{nullptr};
    ULONGLONG m_pos{0};
    ULONGLONG m_len{0};
    LONG m_blocklen{0};
    MemoryStream *m_infoms{nullptr};

    MemoryStream() noexcept = default;

    explicit MemoryStream(const int size) {
        SetSize(size);
    }

    explicit MemoryStream(const FileMode filemode) noexcept {
        Open(filemode);
    }

    MemoryStream(const MemoryStream &ms) {
        Open(ms.m_buf, ms.m_len, ms.m_mode);
    }

    ~MemoryStream() override;

    MemoryStream &operator=(const MemoryStream &other) {
        if (this == &other)
            return *this;
        Empty();
        Open(other.m_buf, other.m_len, other.m_mode);
        return *this;
    }

    MemoryStream(MemoryStream &&) = delete;
    MemoryStream &operator=(MemoryStream &&) = delete;

    void Init() noexcept;
    void SetSize(int size);

    bool Open(FileMode mode) noexcept;
    bool Open(const String &filename, FileMode mode = FileMode::HS_ASCII); //DEFAULT IS 0, WHICH IS STORING, ASCII NOBYTESWAP, NOTAPPENDING
    bool Open(String &filename, FileMode mode = FileMode::HS_ASCII); //Keep for backward compat w/ plugins
    bool Open(const char *initbuf, ULONGLONG count, FileMode mode);

    [[nodiscard]] bool Eof() const noexcept {
        return m_pos >= m_len;
    }

    void Empty() noexcept;

    [[nodiscard]] ULONGLONG GetLength() const noexcept {
        return m_len;
    }

    void SetStatusMeter() override;

    bool IsLabel() noexcept override {
        if (IsAscii()) {
            // ReSharper disable CppJoinDeclarationAndAssignment
            char *ch;
            for (ch = m_buf + m_pos; ch < m_buf + m_len - 1 && *ch != '='; ch++) { }
            return *ch == '=';
            // ReSharper restore CppJoinDeclarationAndAssignment
        }
        //KNC
        ASSERT(false);
        const LONG lv = *((LONG *)(&m_buf[m_pos]));
        return (UINT)lv & BINARYLABELFLAG;
    }

    bool IsHeader() noexcept override {
        if (IsAscii()) {
            if (m_productversion < 13.0F) {
                return m_buf[m_pos] == '[';
            }
            return m_buf[m_pos] == '<';
        }
        //KNC
        ASSERT(false);
        const LONG lv = *((LONG *)(&m_buf[m_pos]));
        return (UINT)lv & BINARYHEADERFLAG;
    }

    bool IsHeaderFromAnyVersion() noexcept override {
        if (IsAscii()) {
            if (m_productversion < 13.0F) {
                if (m_productversion == 5.0F) //to check in files without version loaded yet
                    return (m_buf[m_pos] == '<' || m_buf[m_pos] == '[');
                return m_buf[m_pos] == '[';
            }
            return m_buf[m_pos] == '<';
        }
        //KNC
        ASSERT(false);
        const LONG lv = *((LONG *)(&m_buf[m_pos]));
        return ((UINT)lv & BINARYHEADERFLAG);
    }

    [[nodiscard]] bool IsHeaderAt0() const noexcept {
        if (IsAscii()) {
            if (m_productversion < 13.0F) {
                return m_buf[0] == '[';
            }
            return m_buf[0] == '<';
        }
        //KNC
        return m_IsHeaderLine;
    }

    [[nodiscard]] bool IsEndHeaderAt0() const noexcept {
        if (IsAscii()) {
            if (m_productversion < 13.0F) {
                return m_len >= 4 && m_buf[0] == '[' && m_buf[1] == 'E' && m_buf[2] == 'n' && m_buf[3] == 'd';
            }
            return m_len >= 2 && m_buf[0] == '<' && m_buf[1] == SEPARATOR;
        }
        //KNC
        return m_IsHeaderLine && m_IsLabelLine;
    }

    bool VirtualEof() noexcept final {
        return m_pos >= m_len;
    }

    ULONGLONG ReadC(void *outbuf, ULONGLONG count) noexcept final;
    void Read(void *outbuf, LONG count) final;// Leave for Backward Compatibility with Plugins
    void Write(const void *inbuf, ULONGLONG count) noexcept final;
    void Flush() noexcept final {}
    void Close() noexcept final;
    bool ReadLine(String &line) final; //READS UP TO nl, STORES IN STRING
    bool ReadLine(MemoryStream &stream) final; //READS UP TO nl, STORES IN MemoryStream (BINARY OR ASCII matches this)
    void ParseString(String &token) final;
    void ParseToken(String &token) final;
    void ParseToken(char *token, char delim) final;
    void Seek(LONGLONG ppos, SeekMode seekmode) noexcept final;

    ULONGLONG GetPos() noexcept final {
        return m_pos;
    }

    HashStream *GetInfoStream() noexcept final; //if opened with a filename, opens filename.ext.hinfo or returns it if it is. if opened with out it clears .hinfo ms
};

HASH_INLINE Header LabelAsHeader(const Label &label) noexcept {
    return Header(label.id, (char *)label.labelstring);
}

HASH_INLINE Header LabelAsEndHeader(const Label &label) noexcept {
    const String temp = "/" + (String)label.labelstring;
    return Header(label.id, temp.Get());
}

constexpr bool isSpaceAll(const char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

constexpr bool isLineFeed(const char c) {
    return c == '\n' || c == '\r';
}

constexpr bool isSpaceOrTab(const char c) {
    return c == ' ' || c == '\t';
}
