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

# TimeRang.h

[Go to the documentation of this file.](TimeRang_8h.md)

<div class="fragment">

``` fragment
00001 // BC  4/25/2003  \Bob105\Include\TimeRang.h
00002 
00003 #define __TIMERANG_H
00004 
00005 #ifndef __DATATYPE_H
00006 #include "DataType.h"
00007 #endif
00008 #ifndef __HASHTIME_H
00009 #include "HashTime.h"
00010 #endif
00011 #include <afxtempl.h>
00012 
00013 #define NEVER   TimeRange( TimeRange::RT_NEVER )
00014 #define FOREVER TimeRange( TimeRange::RT_FOREVER )
00015 
00016 class TimeRange {
00017 public:
00018    Time m_start, m_end;
00019 
00020    enum RangeType { RT_NEVER, RT_FOREVER };
00021    
00022    TimeRange()
00023    {
00024       SetNever();
00025    }
00026    TimeRange( RangeType rt )
00027    {
00028       switch (rt) {
00029          case RT_NEVER:
00030             SetNever();
00031             return;
00032          case RT_FOREVER:
00033             SetForever();
00034             return;
00035       }
00036    }
00037    TimeRange( Time time )
00038    {
00039       m_start = time;
00040       m_end = time;
00041    }
00042    TimeRange( const TimeRange &other )
00043    {
00044       m_start = other.m_start;
00045       m_end = other.m_end;
00046    }
00047    TimeRange( Time start, Time end )
00048    {
00049       m_start = start;
00050       m_end = end;
00051    }
00052    ~TimeRange() {}
00053 
00054    TimeRange &operator = ( const TimeRange &other )
00055    {
00056       m_start = other.m_start;
00057       m_end = other.m_end;
00058       return *this;
00059    }
00060    void Set( Time start, Time end )
00061    {
00062       m_start = start;
00063       m_end = end;
00064    }
00065    void SetNever()
00066    {
00067       m_start = MAXTIME;
00068       m_end = -MAXTIME;
00069    }
00070    void SetForever()
00071    {
00072       m_start = -MAXTIME;
00073       m_end = MAXTIME;
00074    }
00075    Time GetLength() const 
00076    {
00077       return m_end - m_start;
00078    }
00079    BOOL IsValid()
00080    {
00081       return m_end >= m_start;
00082    }
00083    BOOL IsIntersect( const TimeRange &range ) const
00084    {
00085       return (m_end > range.m_start && m_start < range.m_end);
00086    }
00087    BOOL IsTimeInRange( Time time ) const
00088    { 
00089       return time>=m_start && time<=m_end;
00090    }
00091    BOOL IsTimeWithinRange( Time time ) const
00092    { 
00093       return time>m_start && time<m_end;
00094    }
00095    BOOL IsRangeInRange( const TimeRange &range ) const
00096    {
00097       return range.m_start>=m_start && range.m_end<=m_end;
00098    }
00099    BOOL IsActiveHere( Time time ) const
00100    { 
00101       return time>=m_start && time<m_end;
00102    }
00103    BOOL operator == ( const TimeRange &other )
00104    {
00105       return m_start==other.m_start && m_end==other.m_end;
00106    }
00107    BOOL operator != ( const TimeRange &other )
00108    {
00109       return !(*this == other);
00110    }
00111    void operator |= ( const TimeRange &other ) // union
00112    {
00113       m_start = MIN(m_start, other.m_start);
00114       m_end = MAX(m_end, other.m_end);
00115    }
00116    void operator |= ( Time time ) // union
00117    {
00118       m_start = MIN(m_start, time);
00119       m_end = MAX(m_end, time);
00120    }
00121    void operator &= ( const TimeRange &other ) // intersect
00122    {
00123       m_start = MAX(m_start, other.m_start);
00124       m_end = MIN(m_end, other.m_end);
00125       if (m_start > m_end)
00126          SetNever();
00127    }
00128    void operator &= ( Time time ) // intersect
00129    {
00130       if (IsTimeInRange(time)) {
00131          m_start = time;
00132          m_end = time;
00133       }
00134       else
00135          SetNever();
00136    }
00137    void operator += ( Time time ) // slide
00138    {
00139       m_start += time;
00140       if (m_end != MAXTIME)
00141          m_end += time;
00142    }
00143    TimeRange operator + ( Time time ) const
00144    {
00145       TimeRange result( *this );
00146       result += time;
00147       return result;
00148    }
00149    void operator -= ( Time time ) // slide
00150    {
00151       if (m_start != MINTIME)
00152          m_start -= time;
00153       m_end -= time;
00154    }
00155    TimeRange operator - ( Time time ) const
00156    {
00157       TimeRange result( *this );
00158       result -= time;
00159       return result;
00160    }
00161    void operator *= ( float n ) // scale
00162    {
00163       m_start *= n;
00164       m_end *= n;
00165    }
00166    TimeRange operator * ( float n ) const // scale
00167    {
00168       TimeRange result( *this );
00169       result *= n;
00170       return result;
00171    }
00172    void Union( Time time )
00173    {
00174       m_start = MIN(m_start, time);
00175       m_end = MAX(m_end, time);
00176    }
00177    BOOL IsInstance()
00178    {
00179       return m_start == m_end;
00180    }
00181 };
00182 
00183 class TimeLineSelection 
00184 {
00185 public:
00186    TimeRange          m_timerange;
00187    CArray< int, int > m_linearray;
00188 
00189    TimeLineSelection()
00190    {
00191    }
00192 
00193    TimeLineSelection( const TimeLineSelection &other )
00194    {
00195       *this = other;
00196    }
00197 
00198    TimeLineSelection( Time start, Time end )
00199    {
00200       m_timerange.m_start = start;
00201       m_timerange.m_end   = end;
00202    }
00203 
00204    void Clear()
00205    {
00206       m_timerange.SetNever();
00207       m_linearray.RemoveAll();
00208    }
00209 
00210    void operator += ( const TimeLineSelection &other ) // union
00211    {
00212       m_timerange |= other.m_timerange;
00213       for (int i=0; i<other.m_linearray.GetSize(); i++)
00214          if (!IsInSelection( other.m_linearray[i] ))
00215             m_linearray.Add( other.m_linearray[i] );
00216    }
00217 
00218    void operator += ( int line )
00219    {
00220       if (line>=0 && !IsInSelection( line ))
00221          m_linearray.Add( line );
00222    }
00223 
00224    void operator = ( const TimeLineSelection &other )
00225    {
00226       m_timerange = other.m_timerange;
00227       m_linearray.RemoveAll();
00228       for (int i=0; i<other.m_linearray.GetSize(); i++)
00229          m_linearray.Add( other.m_linearray[i] );
00230    }
00231 
00232    BOOL IsInSelection( int line )
00233    {
00234       for (int i=0; i<m_linearray.GetSize(); i++)
00235          if (m_linearray[i] == line)
00236             return TRUE;
00237       return FALSE;
00238    }
00239 };
00240 
00241 class TimeLineRect
00242 {
00243 public:
00244    TimeRange m_timerange;
00245    int       m_top, m_bottom;
00246 
00247    TimeLineRect()
00248    {
00249       m_top = BIG_INT;
00250       m_bottom = -BIG_INT;
00251    }
00252 
00253    TimeLineRect( Time start, Time end, int top=BIG_INT, int bottom=-BIG_INT )
00254    {
00255       m_timerange.m_start = start;
00256       m_timerange.m_end   = end;
00257       m_top               = top;
00258       m_bottom            = bottom;
00259    }
00260 
00261    void Clear()
00262    {
00263       m_timerange.SetNever();
00264       m_top = BIG_INT;
00265       m_bottom = -BIG_INT;
00266    }
00267 
00268    void operator |= ( const TimeLineRect &other ) // union
00269    {
00270       m_timerange |= other.m_timerange;
00271 
00272       m_top = MIN(m_top, other.m_top);
00273       m_bottom = MAX(m_bottom, other.m_bottom);
00274    }
00275 
00276    void operator |= ( const TimeLineSelection &other ) // union
00277    {
00278       m_timerange |= other.m_timerange;
00279 
00280       for (int i=0; i<other.m_linearray.GetSize(); i++) {
00281          m_top = MIN(m_top, other.m_linearray[i]);
00282          m_bottom = MAX(m_bottom, other.m_linearray[i]);
00283       }
00284    }
00285 };
00286 
00287 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
