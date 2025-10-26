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

# Timehasp.h

[Go to the documentation of this file.](Timehasp_8h.md)

<div class="fragment">

``` fragment
00001 /*
00002  *  TIMEHASP.H - A C++ header for TimeHASP related classes.
00003  *
00004  *  Copyright (c) 1998 Aladdin Knowledge Systems Ltd.
00005  */
00006 
00007 #if !defined (TIMEHASP_H_)
00008 #define TIMEHASP_H_
00009 
00010 #include <time.h>
00011 
00012 #if !defined (LOCALHASP_H_)
00013 #include "loclhasp.h"
00014 #endif
00015 
00016 #if !defined (HASPMEM_H_)
00017 #include "haspmem.h"
00018 #endif
00019 
00020 
00021 // HASP namespace support.
00022 //
00023 BEGIN_HASP_NAMESPACE
00024 
00025 
00026 // Forward Declarations
00027 //
00028 class TimehaspDate;
00029 class TimehaspTime;
00030 
00031 
00032 // class TimeHasp
00033 // ~~~~~ ~~~~~~~~
00034 // class TimeHasp represents the real key TimeHASP.
00035 //
00036 class TimeHasp : public LocalHasp, public HaspWithMemory
00037 {
00038 public:
00039    typedef unsigned char  MemoType;
00040 
00041    // construction/destruction.
00042    //
00043    HASP_EXPORT TimeHasp( LocalHaspImp* );
00044    HASP_EXPORT TimeHasp( unsigned int  pass1,
00045                          unsigned int  pass2,
00046                          HaspErrorProc handler = 0,
00047                          unsigned int  lptnum = 0 );
00048 
00049    virtual      HASP_EXPORT ~TimeHasp();
00050    virtual void HASP_EXPORT Accept( HaspApplicator& );
00051 
00052    
00053    // Clock operations
00054    //
00055    void HASP_EXPORT GetTime(TimehaspTime& Time) const;
00056    void HASP_EXPORT SetTime(const TimehaspTime& Time);
00057    void HASP_EXPORT GetDate(TimehaspDate& Date) const;
00058    void HASP_EXPORT SetDate(const TimehaspDate& Date);
00059 
00060 private:
00061 
00062    // TimeHASP-4 support.
00063    //
00064    friend class MemohaspConverter;
00065    
00066    // not implemented copy ctor and operator =
00067    //
00068    TimeHasp(const TimeHasp&);
00069    TimeHasp& operator=(const TimeHasp& rhs);
00070 };
00071 
00072 
00073 // class MemohaspConverter
00074 // ~~~~~ ~~~~~~~~~~~~~~~~~
00075 // TimeHASP-4 is a combination of a TimeHASP and a MemoHASP-4.
00076 // When you create a TimeHasp object for a TimeHASP-4 key, the
00077 // memory operations access and modify the TimeHASP part.
00078 //
00079 // The role of MemohaspConverter is to change the memory region
00080 // to that of the MemoHASP-4 part.
00081 // 
00082 // MemohaspConverter has no effect if the TimeHasp object does not
00083 // represent a TimeHASP-4.
00084 //
00085 class MemohaspConverter
00086 {
00087 public:
00088    HASP_EXPORT MemohaspConverter(const TimeHasp& key);
00089    HASP_EXPORT ~MemohaspConverter();
00090 
00091    // returns 'true' for TimeHASP-4 and 'false' for TimeHASP
00092    //
00093    operator bool() const { return converted; }
00094 
00095    // restores default memory operations (i.e. TimeHASP). This operation
00096    // is done automatically in the destructor but can be done earlier.
00097    //
00098    HASP_EXPORT void Restore();
00099 
00100 private:
00101    const TimeHasp* pkey;
00102    bool converted;
00103    
00104    // prevent copy and assignment
00105    //
00106    MemohaspConverter(const MemohaspConverter&);
00107    MemohaspConverter& operator=(const MemohaspConverter&);
00108 };
00109 
00110 
00111 // THDay, THYear, THMonth
00112 // ~~~~~~~~~~~~~~~~~~~~~~
00113 // types to represent day, month, year for better type checking.
00114 //
00115 typedef int THDay;
00116 
00117 enum THYear
00118 {
00119    TH_MINYEAR = 1992,
00120    TH_MAXYEAR = 2091
00121 };
00122 
00123 enum THMonth
00124 {
00125    TH_JAN = 1,
00126    TH_FEB = 2,
00127    TH_MAR = 3,
00128    TH_APR = 4,
00129    TH_MAY = 5,
00130    TH_JUN = 6,
00131    TH_JUL = 7,
00132    TH_AUG = 8,
00133    TH_SEP = 9,
00134    TH_OCT = 10,
00135    TH_NOV = 11,
00136    TH_DEC = 12
00137 };
00138 
00139 
00140 // class TimehaspDate.
00141 // ~~~~~ ~~~~~~~~~~~~
00142 // helper class for GetDate and SetDate services.
00143 //
00144 class TimehaspDate
00145 {
00146    friend class TimeHasp;
00147 
00148 public:
00149    // Initialization constants.
00150    //
00151    enum { Default = -1, Today = 0 };
00152 
00153    // construction
00154    //
00155    explicit HASP_EXPORT TimehaspDate(time_t aTime = Default);
00156    HASP_EXPORT TimehaspDate(THMonth mm, THDay dd, THYear yy);
00157 
00158    bool Valid()   const { return valid; }
00159    int  Month()   const { return month; }
00160    int  Day()     const { return day;   }
00161    int  Year()    const { return year;  }
00162    int  APIYear() const { return year % 100; }
00163 
00164 private:
00165    void Init(time_t aTime);
00166    void Check();
00167 
00168    int month;
00169    int day;
00170    int year;
00171    bool valid;
00172 };
00173 
00174 
00175 
00176 // class TimehaspTime.
00177 // ~~~~~ ~~~~~~~~~~~~
00178 // helper class for GetTime and SetTime services.
00179 //
00180 class TimehaspTime
00181 {
00182    friend class TimeHasp;
00183    
00184 public:
00185    // Initialization constants.
00186    //
00187    enum { Default = -1, Now = 0 };
00188 
00189    // construction.
00190    // Note: default generated copy constructor and operator= are OK here.
00191    //
00192    explicit HASP_EXPORT TimehaspTime(time_t aTime = Default);
00193    HASP_EXPORT TimehaspTime(int hh, int mm, int ss);
00194 
00195    bool Valid()  const { return valid;  }
00196    int  Hour()   const { return hour;   }
00197    int  Minute() const { return minute; }
00198    int  Second() const { return second; }
00199 
00200 private:
00201    void Init(time_t aTime);
00202    void Check();
00203    
00204    int hour;
00205    int minute;
00206    int second;
00207    bool valid;
00208 };
00209 
00210 
00211 END_HASP_NAMESPACE
00212 
00213 
00214 #endif // TIMEHASP_H_
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
