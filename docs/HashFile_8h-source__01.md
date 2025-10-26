hes this)
00309    virtual void ParseString( String &token );
00310    virtual void ParseToken( String &token );
00311    virtual void ParseToken( char *token, char delim );
00312    virtual void Seek( int pos, SeekMode seekmode );
00313    virtual LONG GetPos();
00314 
00315    static BOOL FindAliasAsk( String &filename );
00316    static BOOL FindFileAlias( String &filename );
00317    static BOOL FindFileAliasNameOnly( String &filename );
00318    static BOOL FindPathAlias( String &pathname );
00319    static void AddFileAlias( const String &oldfilename, const String &newfilename );
00320    static void AddPathAlias( const String &oldpathname, const String &newpathname );
00321    static void FreeFileAliases();
00322    static void FreePathAliases();
00323    static BOOL FindAlias( String &filename );
00324    static BOOL IsInFailedList(String &filename);
00325    static void ClearFailedList();
00326    static void ResetCancelAll();
00327 };
00328 
00329 class StreamError
00330 {
00331 public:
00332    StreamError() {}
00333 };
00334 
00335 class FILEIOEXPORT MemoryStream : public HashStream
00336 {
00337 public:
00338    char *buf;
00339    LONG pos;
00340    LONG len;
00341    LONG blocklen;
00342 
00343    MemoryStream() { Init(); mode = HS_ASCII; }
00344    MemoryStream( int size );
00345    MemoryStream( LONG mode ) { Init(); Open(mode); }
00346    MemoryStream( const MemoryStream &ms ) { Init(); Open( ms.buf, ms.len, ms.mode ); }
00347    virtual ~MemoryStream();
00348    void Init();
00349    void SetSize(int size);
00350 
00351    MemoryStream &operator = ( const MemoryStream &other ) {
00352       Empty();
00353       Open( other.buf, other.len, other.mode );
00354       return *this;
00355    }
00356 
00357    BOOL Open( LONG mode );
00358    BOOL Open( String &filename, LONG mode=0 ); // DEFAULT IS 0, WHICH IS STORING, ASCII NOBYTESWAP, NOTAPPENDING
00359    BOOL Open( char *initbuf, LONG count, LONG mode );
00360    BOOL Eof() { return pos >= len; }
00361    void Empty();
00362    LONG GetLength() { return len; }
00363 
00364    void SetStatusMeter();
00365 
00366    virtual UINT ReadC(void* buf, LONG count );
00367    virtual void Read(void* buf, LONG count );
00368    virtual void Write(const void* buf, LONG count );
00369    virtual void Flush() {}
00370    virtual void Close() {}
00371    virtual BOOL ReadLine( String &line );           // READS UP TO nl, STORES IN STRING
00372    virtual BOOL ReadLine( MemoryStream &stream );   // READS UP TO nl, STORES IN MemoryStream (BINARY OR ASCII matches this)
00373    virtual void ParseString( String &token );
00374    virtual void ParseToken( String &token );
00375    virtual void ParseToken( char *token, char delim );
00376    virtual void Seek( int pos, SeekMode seekmode );
00377    virtual LONG GetPos() { return pos; }
00378 
00379    BOOL MemoryStream::IsLabel()
00380    {
00381       char *ch;
00382       for (ch=buf+pos; ch < buf+len-1 && *ch != '='; ch++);
00383       return *ch == '=';
00384    }
00385    BOOL MemoryStream::IsHeader()
00386    {
00387       return (buf[pos] == '[');
00388    }
00389    BOOL MemoryStream::IsHeaderAt0()
00390    {
00391       return (buf[0] == '[');
00392    }
00393    BOOL IsEndHeaderAt0() { return len>=4 && buf[0]=='[' && buf[1]=='E' && buf[2]=='n' && buf[3]=='d'; }
00394 };
00395 
00396 inline Header LabelAsHeader( const Label &label )
00397 {
00398    return Header( label.id, label.string );
00399 }
00400 
00401 inline Header LabelAsEndHeader( const Label &label )
00402 {
00403    return Header( label.id, (String("End") + label.string).Get());
00404 }
00405 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
