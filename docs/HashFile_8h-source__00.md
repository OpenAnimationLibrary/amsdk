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

# HashFile.h

[Go to the documentation of this file.](HashFile_8h.md)

<div class="fragment">

``` fragment
00001 // BC  1/10/2005  \BobL120\Include\HashFile.h
00002 
00003 #define __HASHFILE_H
00004 
00005 #ifndef __STRCLASS_H
00006 #include "StrClass.h"
00007 #endif
00008 #include <afxtempl.h>
00009 
00010 #define NUMSTATUSSUBDIVISIONS  100
00011 
00012 // productversion = 5.0 // original version 5.0 set in constructor
00013 // productversion = 6.0 // bitfields were moved from CP to SegmentCP/ChannelCP to add ZEROSLOPE interpolation
00014 // productversion = 6.1 // 0-based/time-based frame numbering, focallength corrected
00015 // productversion = 7.0 // time written in ticks (1/135000 second)
00016 // productversion = 8.51 // fixed spherical combiner ring sizes scaled by UNIT
00017 // productversion = 9.0 // Um... total rewrite
00018 // productversion = 9.01 // 9.0 now has compact muscle
00019 // productversion = 9.02 // 9.0o stores default pose application on userproperty not relation
00020 // PRODUCTVERSION = 9.03 // stores constdrivers different
00021 // PRODUCTVERSION = 9.04 // loads > 8.5, < 9.04 camera.m_globalambience with correct factor
00022 // PRODUCTVERSION = 9.50 // property drivers that are not in actions now save as regular children of the HashObject instead of embedded in the Property
00023 // PRODUCTVERSION = 9.51 // attempt to fix 9.5o animobjectshortcuts and emptydrivers with m_matchname == ""
00024 // PRODUCTVERSION = 9.52 // ignore defalutvalue and displayposeslider labels on load on constdrivers
00025 // PRODUCTVERSION = 9.53 // destroy bogus (all) constdrivers on object cache property from < 9.53
00026 // PRODUCTVERSION = 10.00 // same as 9.53
00027 // PRODUCTVERSION = 10.01 // matchnames of linked objects contains full path in memory and relative path on disk objects|((char)254)thom((char)255)mdl.property
00028 // PRODUCTVERSION = 10.02 // repairs previous versions bogus emptydrivers under root folders
00029 // PRODUCTVERSION = 10.03 // uses quotes to seperate linked object matchnames objects|"thom.mdl".property
00030 // PRODUCTVERSION = 10.04 // distort boxes are modeled longer if the res is larger.
00031 // PRODUCTVERSION = 10.05 // removed unnecessary leaf level empty drivers from motion files
00032 // PRODUCTVERSION = 10.06 // to fix earlier texture node properties being not set on blobby caches etc
00033 // PRODUCTVERSION = 10.07 // to fix fig cache actionshortcutcontainer being at head instead of tail so it loads constdrivers correctly
00034 
00035 // PRODUCTVERSION = 10.50  // Same as 10.05
00036 // PRODUCTVERSION = 10.51  // Same as 10.07
00037 // PRODUCTVERSION = 10.52  // New specularsize calculation
00038 // PRODUCTVERSION = 10.53  // Duplicate constraints are no longer caused by copy/paste, or removed on load.
00039 // PRODUCTVERSION = 10.54  // Fixed lightlist nodes using cache treename in figure::onnotifyendprojectload and save
00040 // PRODUCTVERSION = 10.55  // Moved constraints that are under transforms to be under parent (Poses still had bug and now are fixed)
00041 // PRODUCTVERSION = 10.56  // Changed ambiance to be a color
00042 
00043 // PRODUCTVERSION = 11.00  // New release, also rotatedrivers in poses don't save parenttobone
00044 // PRODUCTVERSION = 11.01  // Move chor group container to top of sibling list
00045 // PRODUCTVERSION = 11.02  // Fixed reversed z for XY plane vertical markers (left or right view in horizontal ruler) 
00046 // PRODUCTVERSION = 11.03  // Convert 1DMultiDs to Channels for niels
00047 // PRODUCTVERSION = 11.04  // Convert hair density from density along side to area density (so its linear) 
00048 // PRODUCTVERSION = 11.50  // 
00049 // PRODUCTVERSION = 11.51  // Convert hair density from density along side to area density (so its linear) 
00050 // PRODUCTVERSION = 12.00  // BufferShortcut relative paths to image 08/08/05
00051 
00052 #define PRODUCTVERSION  12.00f
00053 
00054 class FileStream;
00055 class MemoryStream;
00056 class Time;
00057 class Vector2;
00058 class Vector;
00059 class Vector4;
00060 class RGBFloat;
00061 class ColorBuf;
00062 class TimeRange;
00063 class HashMarker;
00064 class PatchID;
00065 class Rotate;
00066 class Matrix33;
00067 class Matrix34;
00068 class Matrix44;
00069 class Quaternion;
00070 class RenderInfoParms;
00071 class RenderStatusInfo;
00072 class StreamMsg;
00073 
00074 class FILEIOEXPORT Label {
00075 public:
00076    LONG   id;
00077    char   string[80];
00078    
00079    Label() {}
00080    Label( LONG id );
00081    Label( char *text );
00082    char *GetText() { return string; }
00083 };
00084 
00085 class FILEIOEXPORT Header {
00086 public:
00087    LONG   id;
00088    char   string[80];
00089    
00090    Header() {}
00091    Header( LONG id );
00092    Header( LONG pid, const char *buffer )
00093    {
00094       id = pid;
00095       strcpy( string, buffer );
00096    }
00097    int operator == ( const Header &header ) const { return (id == header.id); }
00098    char *GetText() { return string; }
00099 };
00100 
00101 class FILEIOEXPORT StreamBOOL {
00102 public:
00103    BOOL m_bool;
00104 
00105    StreamBOOL() {}
00106    StreamBOOL( BOOL pbool ) { m_bool = pbool; }
00107 };
00108 
00109 LONG GetLabelIDFromString( char *string );
00110 LONG GetHeaderIDFromString( char *string );
00111 BOOL GetLabelStringFromID( LONG pid, char *string );
00112 void GetHeaderStringFromID( LONG pid, char *string );
00113 FILEIOEXPORT BOOL IsFileOfType( const String &filename, LONG headerid );
00114 FILEIOEXPORT BOOL IsFileOfTypeHash( String &filename );
00115 FILEIOEXPORT void FreeHashFileToken();
00116 
00117 class FILEIOEXPORT HashStream {
00118 protected:
00119    LONG       filesize, mode;
00120    LONG       nextstatuspos, statusposincrement;
00121    String     m_prevprogresstext;
00122    BOOL       m_bwasprogressinitializedbyme;
00123 
00124 public:
00125    String filename;
00126    float      m_productversion;
00127 
00128    enum { HS_STORE=0, HS_LOAD=1, HS_ASCII=0, HS_BINARY=2, HS_BYTESWAP=4, HS_APPEND=8, 
00129                HS_FAILED=16, HS_HASH=32 };
00130 
00131    enum SeekMode { HS_BEGINNING, HS_END, HS_OFFSET };
00132    
00133    HashStream() { m_bwasprogressinitializedbyme = FALSE; }
00134    virtual ~HashStream();
00135 
00136 #if _MEMDEBUG
00137    void *operator new( size_t size, char *file, const int line ) { return ALLOCEXT( size, file, line ); }
00138 #else
00139    void *operator new( size_t size ) { return AllocExt( size ); }
00140 #endif   
00141    void  operator delete( void *ptr ) { FreeExt( ptr ); }
00142 
00143 // Attributes
00144    BOOL IsLoading() const { return mode & HS_LOAD; }
00145    BOOL IsStoring() const { return !IsLoading(); }
00146    BOOL IsAppend() const { return mode & HS_APPEND; }
00147    BOOL IsBinary() const { return mode & HS_BINARY; }
00148    void OnBinary() { mode |= HS_BINARY; }
00149    BOOL IsAscii() const { return !IsBinary(); }
00150    void OnAscii() { mode |= HS_ASCII; }
00151    BOOL IsHash() const { return mode & HS_HASH; }
00152    BOOL IsByteSwap() const { return mode & HS_BYTESWAP; }
00153    void OnFailed() { mode |= HS_FAILED; }
00154    void OffFailed() { mode &= ~HS_FAILED; }
00155    BOOL IsFailed() { BOOL rval = mode&HS_FAILED; OffFailed(); return rval; }
00156    void SetMode( LONG pmode ) { mode = pmode; }
00157    LONG GetMode() { return mode; }
00158    BOOL SkipPast( UINT id );
00159 
00160    CRuntimeClass* PASCAL LoadRuntimeClass(UINT* pwSchemaNum);
00161    void StoreRuntimeClass(CRuntimeClass *rtc);
00162 
00163 // Operations
00164    // PURE VIRTUALS
00165    virtual UINT ReadC( void* buf, LONG count ) = 0;
00166    virtual void Read( void* buf, LONG count ) = 0;
00167    virtual void Write( const void* buf, LONG count ) = 0;
00168    virtual void Flush() = 0;
00169    virtual void Close() = 0;
00170    virtual BOOL ReadLine( String &line ) = 0;           // READS UP TO nl, STORES IN STRING
00171    virtual BOOL ReadLine( MemoryStream &stream ) = 0;   // READS UP TO nl, STORES IN MemoryStream (BINARY OR ASCII matches this)
00172    virtual void ParseString( String &token ) = 0;
00173    virtual void ParseToken( String &token ) = 0;
00174    virtual void ParseToken( char *token, char delim ) = 0;
00175    virtual void Seek( int pos, SeekMode seekmode ) = 0;
00176    virtual LONG GetPos() = 0;
00177 
00178    // reading and writing strings
00179    void WriteLine( String &line );          // AUTOMATICALLY APPENDS A nl AT END OF STRING (BINARY OR ASCII)
00180    void SetStatusMeter();
00181    BOOL SkipHeader(Header &header);
00182    String ReadString( char delimit );
00183    void ParseToken( String &token, char delim );
00184 
00185 public:
00186    // Object I/O is pointer based to avoid added construction overhead.
00187    // Use the Serialize member function directly for embedded objects.
00188 /*   friend HashStream&  operator<<(HashStream& hs, const HashObject* hob);
00189    friend HashStream& AFXAPI operator>>(HashStream& hs, HashObject*& hob);
00190    friend HashStream& AFXAPI operator>>(HashStream& hs, const HashObject*& hob);*/
00191 
00192    // insertion operations
00193    HashStream& operator<<(SBYTE sb);
00194    HashStream& operator<<(UBYTE ub);
00195    HashStream& operator<<(SWORD w);
00196    HashStream& operator<<(UWORD w);
00197    HashStream& operator<<(LONG l);
00198    HashStream& operator<<(ULONG ul);
00199    HashStream& operator<<(float f);
00200    HashStream& operator<<(double d);
00201    HashStream& operator<<(int i);
00202    HashStream& operator<<(UINT i);
00203    HashStream& operator<<(char ch);
00204    HashStream& operator<<(char *text);
00205    HashStream& operator<<(const String &st);
00206    HashStream& operator<<(Time time);
00207    HashStream& operator<<(const Vector2 &v);
00208    HashStream& operator<<(const Vector &v);
00209    HashStream& operator<<(const RGBFloat &cv);
00210    HashStream& operator<<(const ColorBuf &cb);
00211    HashStream& operator<<(const BITMAPINFO &bi);
00212    HashStream& operator<<(const BITMAPINFOHEADER &h);
00213    HashStream& operator<<(const BITMAPFILEHEADER &h);
00214    HashStream& operator<<(const HICON &hicon);
00215    HashStream& operator<<(const TimeRange &fr);
00216    HashStream& operator<<(const HashMarker *fr);
00217    HashStream& operator<<(const PatchID &patchid);
00218    HashStream& operator<<(const Label &lb);
00219    HashStream& operator<<(const Header &hd);
00220    HashStream& operator<<(const StreamBOOL& obj);
00221    HashStream& operator<<(const Rotate &rot);
00222    HashStream& operator<<(const Vector4 &v );
00223    HashStream& operator<<(const Matrix33 &m );
00224    HashStream& operator<<(const Matrix34 &m );
00225    HashStream& operator<<(const Matrix44 &m );
00226    HashStream& operator<<(const Quaternion &q );
00227    HashStream& operator<<(const COleDateTime &dateSrc);
00228    HashStream& operator<<(const CTime &dateSrc);
00229    
00230    HashStream& operator<<( HashStream& (__cdecl * function)(HashStream&))
00231     { (*function)(*this); return *this; }
00232 
00233    // extraction operations
00234    HashStream& operator>>(SBYTE &sb);
00235    HashStream& operator>>(UBYTE &ub);
00236    HashStream& operator>>(SWORD &sw);
00237    HashStream& operator>>(UWORD &uw);
00238    HashStream& operator>>(LONG &l);
00239    HashStream& operator>>(ULONG &ul);
00240    HashStream& operator>>(float &f);
00241    HashStream& operator>>(double &d);
00242    HashStream& operator>>(int &i);
00243    HashStream& operator>>(UINT &i);
00244    HashStream& operator>>(char &ch);
00245    HashStream& operator>>(String &st);
00246    HashStream& operator>>(Time &time);
00247    HashStream& operator>>(Vector2 &v);
00248    HashStream& operator>>(Vector &v);
00249    HashStream& operator>>(RGBFloat &cv);
00250    HashStream& operator>>(ColorBuf &cb);
00251    HashStream& operator>>(HICON &hicon);
00252    HashStream& operator>>(TimeRange &fr);
00253    HashStream& operator>>(HashMarker *fr);
00254    HashStream& operator>>(PatchID &patchid);
00255    HashStream& operator>>(Label &lb);
00256    HashStream& operator>>(Header &hd);
00257    HashStream& operator>>(StreamBOOL &obj);
00258    HashStream& operator>>(Rotate &rot);
00259    HashStream& operator>>(Vector4& v);
00260    HashStream& operator>>(Matrix33& m);
00261    HashStream& operator>>(Matrix34& m);
00262    HashStream& operator>>(Matrix44& m);
00263    HashStream& operator>>(Quaternion& q);
00264    HashStream& operator>>(BITMAPINFOHEADER &h);
00265    HashStream& operator>>(BITMAPFILEHEADER &h);
00266    HashStream& operator>>(COleDateTime& dateSrc);
00267    HashStream& operator>>(CTime& dateSrc);
00268 };
00269 
00270 FILEIOEXPORT HashStream& sp( HashStream& hs );
00271 FILEIOEXPORT HashStream& spb( HashStream& hs );
00272 FILEIOEXPORT HashStream& nl( HashStream& hs );
00273 FILEIOEXPORT HashStream& nlb( HashStream& hs );
00274 FILEIOEXPORT HashStream& tab( HashStream& hs );
00275 FILEIOEXPORT HashStream& tabb( HashStream& hs );
00276 
00277 class PathAlias;
00278 class FileAlias;
00279 
00280 class FILEIOEXPORT FileStream : public HashStream
00281 {
00282 protected:
00283    static  CList<String, String &> failedloadlist;
00284    static  PathAlias *pathaliashead;
00285    static  FileAlias *filealiashead;
00286    static  BOOL       m_bCancelAll;
00287    CStdioFile         file;
00288    String             m_tempname;
00289 
00290 public:
00291    FileStream();
00292    
00293    virtual ~FileStream();
00294 
00295    
00296    BOOL    Open( const String &filename, LONG mode=0 ); // DEFAULT IS 0, WHICH IS STORING, ASCII NOBYTESWAP, NOTAPPENDING
00297    BOOL    Open( String &filename, LONG mode=0 );//Keep for backward compat w/ plugins
00298    BOOL    Open( int filenumber );
00299    BOOL    Eof();
00300    long GetLength() {return filesize;}
00301 
00302    virtual UINT ReadC(void* buf, LONG count );
00303    virtual void Read(void* buf, LONG count );
00304    virtual void Write(const void* buf, LONG count );
00305    virtual void Flush();
00306    virtual void Close();
00307    virtual BOOL ReadLine( String &line );           // READS UP TO nl, STORES IN STRING
00308    virtual BOOL ReadLine( MemoryStream &stream );   // READS UP TO nl, STORES IN MemoryStream (BINARY OR ASCII matc