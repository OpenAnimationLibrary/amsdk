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

# StrClass.h

[Go to the documentation of this file.](StrClass_8h.md)

<div class="fragment">

``` fragment
00001 // WEP  3/31/2005  \will120\Include\StrClass.h
00002 
00003 #ifndef __STRCLASS_H
00004 #define __STRCLASS_H
00005 
00006 #ifndef __MACROS_H
00007 #include "Macros.h"
00008 #endif
00009 
00010 #ifndef __ALLOCATE_H
00011 #include "Allocate.h"
00012 #endif
00013 
00014 class Time;
00015 
00016 #define STRINGALLOC( baz )          (char *)AllocString((size_t)baz )
00017 #define STRINGFREE( baz )           {if (baz){FreeString( baz );baz=NULL;}}
00018 #define STRINGSIZE                  255
00019 
00020 #define periodch '.' //these were for linked file matchnames v10.01 v10.02,
00021 #define periodch_r ((char)255)
00022 #define pathch_r ((char)254)
00023 #define quotech '\"' //this now seperates linked file matchnames v10.03
00024 
00025 #ifdef _OSX
00026 #define NATIVESEPARATOR '/'
00027 #elif defined(_OS9)
00028 #define NATIVESEPARATOR ':'
00029 #else
00030 #define NATIVESEPARATOR '\\' 
00031 #endif
00032 
00033 class CWnd;
00034 
00035 class FILEIOEXPORT String {
00036 public:
00037    char *buf;             // SHOULD CHANGE THIS TO PROTECTED OR PRIVATE
00038 
00039 #if _MEMDEBUG
00040    void *operator new( size_t size, char *file, const int line ) { return ALLOCACT( size, file, line ); }
00041 #else
00042    void *operator new( size_t size ) { return AllocAct( size ); }
00043 #endif   
00044    void  operator delete( void *ptr ) { FreeAct( ptr ); }
00045 
00046    String() { buf = NULL; }
00047 
00048    String( int size, BOOL unused ) { buf = STRINGALLOC(size); }
00049 
00050    String( const String & );
00051    String( const char * );                 // CONVERT CHAR * TO STRING
00052    String( char );
00053    String( SWORD );
00054    String( ULONG );
00055    String( LONG );
00056    String( float );
00057    String( double );
00058    String( float, float precision );
00059    String( int );
00060    String( char, int count );
00061    void Set(const char *other, int len );
00062    ~String() { STRINGFREE( buf ); buf = NULL; }
00063    char *Get() const { return buf; }
00064    char operator [] ( int index ) const
00065    {
00066       if (buf)
00067          return buf[index];
00068       else
00069          return 0;
00070    }
00071 //   operator char * () const;         // CONVERT STRING TO CHAR *, THE CAN'T USE COMPILER OFTEN GETS CONFUSED ON WHICH OVERLOADED FUNCTION TO CALL
00072 
00073    BOOL IsEmpty() const { return (buf == NULL) || (*buf=='\0'); }
00074    void Empty() { STRINGFREE( buf ); buf = NULL; }
00075    BOOL operator==( const String & ) const;
00076    BOOL operator!=( const String &other ) const { return !(*this == other); }
00077    String &operator=( const String & );  
00078    String &operator=( const char * );  
00079    void operator+=( const String & );
00080    size_t length() const;
00081 
00082    String Left( int count ) const;
00083    String Right( int count ) const;
00084    String Mid( int start, int count ) const;
00085    String ToUpper() const;
00086    String ToLower() const;
00087    String GetPathOnly() const;
00088    String GetNameOnly() const;
00089    String GetSuffixOnly() const;
00090    String GetWithoutSuffix() const;
00091    String GetNameOnlyWithoutSuffix() const;
00092    String GetWithoutDigits() const;
00093    String GetFileDigits() const;
00094    int    GetEndingNumber() const;
00095    String GetWithoutCRLFs() const;
00096    String GetAbbreviated( int cchMax, BOOL bAtLeastName = TRUE ) const;
00097    String GetAbbreviated( CWnd *window ) const;
00098    String GetRelativePath() const; //Always UNC
00099    String GetNonRelativePath() const;
00100    String GetAbsolutePath() const;
00101    String GetAbsolutePath(BOOL forceunc) const;
00102    String GetUNCFileName() const;
00103    String GetServerFileName() const;
00104    String NumberFrame(LONG frame) const;
00105    String StripLeadingSlash() const;
00106    String StripPunctuation();
00107    String NetSharePlaceHolder() const;
00108    String GetFileNamesMatchName() const; //assumes string is an UNC filename on pc for speed
00109    String GetMatchNameRelativeForFile() const;
00110    String GetMatchNameAbsoluteFromFile() const;
00111    void   ReplaceWackyForMac(char find, char replace); //only to convert v10.01 v10.02 files
00112    String ToRelativePathDescription() const;  //converts descriptions to linked files
00113    String ToAbsolutePathDescription( float productversion, BOOL &askforfile ) const;
00114    
00115    PLUGINEXPORT float  GetCM() const;
00116    String FitWidth(CDC *dc, int maxwidth, const String &padwith) const;
00117 
00118    String GetEncrypted( String password ) const;
00119    void   Decrypt( String password );
00120 
00121    BOOL operator < ( const String & ) const;
00122    BOOL operator > ( const String & ) const;
00123    BOOL operator <= ( const String & ) const;
00124    BOOL operator >= ( const String & ) const;
00125    friend String operator + ( const String &, const String & );
00126 
00127    void TrimRight();                      // new functions like MFC CString
00128    void TrimLeft();
00129    int Find(char ch) const;               // like "C" strchr -1 if not found
00130    int Find(int startindex, char ch) const;
00131    int Find(const String &sub) const;     // like "C" strstr
00132    int Find(int startindex, const String &sub) const;     // like "C" strstr
00133    int ReverseFind(char ch) const;
00134    void Format(const String &format, ...);
00135    int FindOneOf(const String &charset) const;
00136    String SpanIncluding(const String &charset) const;
00137    String SpanExcluding(const String &charset) const;
00138    void Replace(const String &find, const String &replace);
00139    String GetFileTitle() const;
00140    String GetToolTip();
00141    String GetStatusMessageText();
00142    Time ToTime(int fps, int timeunits, BOOL treatasdelta=FALSE) const;
00143 
00144    static String GetAppPath();
00145    static String GetOsPath();
00146    static String GetTempPath();
00147    static String GetAppDataPath();
00148    
00149    FILEIOEXPORT friend String GetRegisteredOwner();
00150    String StrTok(String separators);
00151 
00152 };
00153 
00154 inline String::String( const String &init )
00155 {
00156    if (init.buf && (buf = STRINGALLOC((init.length()+1 ))))
00157       strcpy( buf, init.buf ); 
00158    else
00159       buf = NULL;    
00160 }
00161 
00162 inline String::String( const char *init )
00163 {
00164    if (init && (buf = STRINGALLOC((strlen(init)+1 ))))
00165       strcpy( buf, init );
00166    else
00167       buf = NULL;    
00168 }
00169 
00170 inline String::String( char init )
00171 {
00172    if (buf = STRINGALLOC( 2 )) {
00173       buf[0] = init;
00174       buf[1] = '\0';
00175    }   
00176 }
00177 
00178 inline String::String( char init, int count )
00179 {
00180    if ( buf = STRINGALLOC(( count+1 ))) {
00181       for (int i = 0; i < count; ++i)
00182          buf[i] = init;
00183       buf[count] = '\0';
00184    }   
00185 }
00186 
00187 inline String::String( SWORD number )
00188 {
00189    char init[20];
00190    
00191    sprintf( init, "%hd", number );
00192    if (buf = STRINGALLOC(( strlen(init)+1 )))
00193       strcpy( buf, init ); 
00194 }
00195 
00196 inline String::String( LONG number )
00197 {
00198    char init[20];
00199    
00200    sprintf( init, "%ld", number );
00201    if (buf = STRINGALLOC(( strlen(init)+1 )))
00202       strcpy( buf, init ); 
00203 }
00204 
00205 inline String::String( ULONG number )
00206 {
00207    char init[20];
00208    
00209    sprintf( init, "%lu", number );
00210    if (buf = STRINGALLOC(( strlen(init)+1 )))
00211       strcpy( buf, init ); 
00212 }
00213 
00214 inline String::String( float number )
00215 {
00216    char init[20];
00217    
00218    sprintf( init, "%g", number );
00219    if (buf = STRINGALLOC(( strlen(init)+1 )))
00220       strcpy( buf, init ); 
00221 }
00222 
00223 inline String::String( double number )
00224 {
00225    char init[20];
00226    
00227    sprintf( init, "%g", number );
00228    if (buf = STRINGALLOC(( strlen(init)+1 )))
00229       strcpy( buf, init ); 
00230 }
00231 
00232 inline String::String( float number, float precision )
00233 {
00234    char init[20];
00235 
00236    Round( number, precision );
00237 /*
00238    double dnum = number;  // same code as Round()
00239    double modulo = precision;
00240    dnum += SIGN(dnum) * 0.5 * modulo;
00241    dnum -= fmod(dnum, modulo);
00242    number = (float)dnum;
00243 */
00244    sprintf( init, "%g", number );
00245    if (buf = STRINGALLOC(( strlen(init)+1 )))
00246       strcpy( buf, init ); 
00247 }
00248 
00249 inline String::String( int number )
00250 {
00251    char init[20];
00252    
00253    sprintf( init, "%d", number );
00254    if (buf = STRINGALLOC(( strlen(init)+1 )))
00255       strcpy( buf, init ); 
00256 }
00257 
00258 inline size_t String::length() const
00259 {
00260    if(buf)
00261       return strlen(buf); 
00262    else
00263       return 0;   
00264 }
00265 
00266 inline String operator + ( const String &left, const String &right )
00267 {
00268    String result( left );
00269    result += right;
00270    return result;
00271 }   
00272 
00273 inline String &String::operator=(const char *other )
00274 {
00275    STRINGFREE(buf);
00276    if (other && (buf = STRINGALLOC((strlen(other)+1 ))))
00277       strcpy( buf, other );
00278    else
00279       buf = NULL;
00280    return *this;
00281 }
00282 
00283 inline void String::Set(const char *other, int len )
00284 {
00285    STRINGFREE(buf);
00286    if (other && len && (buf = STRINGALLOC(len+1 ))) {
00287       memcpy( buf, other, len );
00288       buf[len] = '\0';
00289    }
00290    else
00291       buf = NULL;
00292 }
00293 
00294 inline BOOL String::operator==(const String &other ) const 
00295 {
00296    if (buf == NULL)
00297       return (other.buf == NULL);
00298    if (other.buf == NULL)
00299       return FALSE;
00300    return ( _stricmp( buf, other.buf ) == 0);
00301 }
00302 
00303 FILEIOEXPORT String FormatTime(LONG sec, BOOL force = FALSE);
00304 void StripOffName( String & );
00305 FILEIOEXPORT void AddNameToPath( String &, const String & );
00306 FILEIOEXPORT String CombineNameToPath(const String &path, const String &name);
00307 FILEIOEXPORT String AddNameToExeDirectory(String name);
00308 FILEIOEXPORT String AddNameToDataDirectory(String name);
00309 FILEIOEXPORT void FreeAppPath();
00310 
00311 FILEIOEXPORT void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, String& value);
00312 FILEIOEXPORT String NativeToUniversal( const String &nativepath );
00313 FILEIOEXPORT String UniversalToNative( const String &puniversalpath );
00314 
00315 enum { UNIT_NONE, UNIT_CENTIMETERS, UNIT_METERS, UNIT_FEET, UNIT_INCHES, UNIT_FEETANDINCHES, UNIT_PERCENTAGE, UNIT_ANGLE, UNIT_SMPTE, UNIT_FRAMES };
00316 PLUGINEXPORT int GetMeasurementUnits();
00317 PLUGINEXPORT void SetMeasurementUnits( int pmeasurementunits );
00318 PLUGINEXPORT CString UnitToString( float cm, int pmeasurementunits=-1, int fps=-1, float modulo=.01f );
00319 PLUGINEXPORT void AFXAPI DDX_Unit(CDataExchange *pDX, int nIDC, float &cm);
00320 PLUGINEXPORT void AFXAPI DDV_MinMaxUnit(CDataExchange* pDX, float const& value, float minVal, float maxVal);
00321 
00322 #endif  // __STRCLASS_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
