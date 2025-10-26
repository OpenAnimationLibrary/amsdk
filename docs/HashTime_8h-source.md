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

# HashTime.h

[Go to the documentation of this file.](HashTime_8h.md)

<div class="fragment">

``` fragment
00001 // BC  3/20/2003  \Bob105\Include\HashTime.h
00002 
00003 #define __HASHTIME_H
00004 
00005 #ifndef __OS9ROS_H
00006 #include "Macros.h"
00007 #endif
00008 #ifndef __EXPORTS_H
00009 #include "Exports.h"
00010 #endif
00011 
00012 #define MAX_TICKS   2147483647L
00013 #define MAX_SECONDS MAX_TICKS/Time::TICKSPERSECOND
00014 
00015 #define MINTIME     -Time( Time::TT_MAX )
00016 #define MAXTIME     Time( Time::TT_MAX )
00017 #define MINTIMESTEP Time( Time::TT_MINSTEP )
00018 
00019 class String;
00020 
00021 class FILEIOEXPORT Time {
00022 private:
00023    long m_ticks;
00024 
00025 public:
00026    enum { TICKSPERSECOND=135000 };
00027    enum TimeType { TT_MINSTEP, TT_MAX };
00028 
00029    Time()
00030    {
00031       m_ticks = 0L;
00032    }
00033 
00034    Time( double seconds )
00035    {
00036       m_ticks = (long)(seconds * TICKSPERSECOND);
00037    }
00038 
00039    Time( double frame, double fps )
00040    {
00041       SetSeconds( frame / fps );
00042    }
00043 
00044    Time( TimeType rt )
00045    {
00046       switch (rt) {
00047          case TT_MINSTEP:
00048             SetMinStep();
00049             return;
00050          case TT_MAX:
00051             SetMax();
00052             return;
00053       }
00054    }
00055 
00056    Time &operator = (const double seconds )
00057    {
00058       m_ticks = (long)(seconds * TICKSPERSECOND);
00059       return *this;
00060    }
00061 
00062    Time &operator = ( Time other )
00063    {
00064       m_ticks = other.m_ticks;
00065       return *this;
00066    }
00067 
00068    BOOL operator == ( Time other ) const
00069    {
00070       return m_ticks == other.m_ticks;
00071    }
00072 
00073    BOOL operator != ( Time other ) const
00074    {
00075       return m_ticks != other.m_ticks;
00076    }
00077 
00078    BOOL operator > ( Time other ) const
00079    {
00080       return m_ticks > other.m_ticks;
00081    }
00082 
00083    BOOL operator < ( Time other ) const
00084    {
00085       return m_ticks < other.m_ticks;
00086    }
00087 
00088    BOOL operator >= ( Time other ) const
00089    {
00090       return m_ticks >= other.m_ticks;
00091    }
00092 
00093    BOOL operator <= ( Time other ) const
00094    {
00095       return m_ticks <= other.m_ticks;
00096    }
00097 
00098    Time operator + ( Time other ) const
00099    {
00100       Time result( *this );
00101       result.m_ticks += other.m_ticks;
00102       return result;
00103    }
00104 
00105    Time operator - ( Time other ) const
00106    {
00107       Time result( *this );
00108       result.m_ticks -= other.m_ticks;
00109       return result;
00110    }
00111 
00112    Time operator * ( Time other ) const
00113    {
00114       Time result( *this );
00115       result.m_ticks *= other.m_ticks;
00116       return result;
00117    }
00118 
00119    Time operator * ( double n ) const
00120    {
00121       Time result( *this );
00122       result.m_ticks = RoundValue(result.m_ticks * n);
00123       return result;
00124    }
00125 
00126    float operator / ( Time other ) const
00127    {
00128       return (float)m_ticks / other.m_ticks;
00129    }
00130 
00131    Time operator / ( double n ) const
00132    {
00133       Time result( *this );
00134       result.m_ticks = RoundValue(result.m_ticks / n);
00135       return result;
00136    }
00137 
00138    Time operator % ( Time other ) const
00139    {
00140       Time result( *this );
00141       if (other.m_ticks)
00142          result.m_ticks %= other.m_ticks;
00143       return result;
00144    }
00145 
00146    void operator += ( Time other )
00147    {
00148       m_ticks += other.m_ticks;
00149    }
00150 
00151    void operator -= ( Time other )
00152    {
00153       m_ticks -= other.m_ticks;
00154    }
00155 
00156    void operator *= ( Time other )
00157    {
00158       m_ticks *= other.m_ticks;
00159    }
00160 
00161    void operator *= ( double n )
00162    {
00163       m_ticks = RoundValue(m_ticks * n);
00164    }
00165 
00166    void operator /= ( Time other )
00167    {
00168       m_ticks /= other.m_ticks;
00169    }
00170 
00171    void operator /= ( double n )
00172    {
00173       m_ticks = RoundValue(m_ticks / n);
00174    }
00175 
00176    Time operator - () const
00177    {
00178       Time result( *this );
00179       result.m_ticks = -result.m_ticks;
00180       return result;
00181    }
00182 /* USE GETSECONDS INSTEAD
00183    operator float() const
00184    {
00185       return (float)m_ticks/TICKSPERSECOND;
00186    }
00187 */
00188    float GetSeconds() const
00189    {
00190       return (float)((double)m_ticks/TICKSPERSECOND);
00191    }
00192 
00193    double GetSecondsDouble() const
00194    {
00195       return (double)m_ticks/TICKSPERSECOND;
00196    }
00197 
00198    void SetSeconds( double seconds )
00199    {
00200       m_ticks = RoundValue(seconds * TICKSPERSECOND);
00201    }
00202 
00203    long GetTicks() const
00204    {
00205       return m_ticks;
00206    }
00207 
00208    void SetTicks( long ticks )
00209    {
00210       m_ticks = ticks;
00211    }
00212 
00213    BOOL IsZero() const
00214    {
00215       return m_ticks == 0L;
00216    }
00217 
00218    float GetFrame( double fps ) const
00219    {
00220       return (float)(GetSeconds() * fps);
00221    }
00222 
00223    int GetFrameInt( double fps ) const
00224    {
00225       return (int)(GetSeconds() * fps + .5);
00226    }
00227 
00228    void SetFrame( double frame, double fps )
00229    {
00230       SetSeconds( frame / fps );
00231    }
00232 
00233    void StepFrame( double fps )
00234    {
00235       m_ticks += RoundValue(1.0/fps * TICKSPERSECOND);
00236    }
00237 
00238    void StepFrames( double frames, double fps )
00239    {
00240       m_ticks += RoundValue(1.0/fps * TICKSPERSECOND * frames);
00241    }
00242 
00243    void SnapToFrame( double fps )
00244    {
00245       long oneframe = RoundValue(1.0/fps * TICKSPERSECOND);
00246       m_ticks += (long)(SIGN(m_ticks) * 0.5 * oneframe);
00247       m_ticks -= m_ticks % oneframe;
00248    }
00249 
00250    void FloorToFrame( double fps )
00251    {
00252       long oneframe = RoundValue(1.0/fps * TICKSPERSECOND);
00253       m_ticks -= m_ticks % oneframe;
00254    }
00255 
00256    void CeilToFrame( double fps )
00257    {
00258       long oneframe = RoundValue(1.0/fps * TICKSPERSECOND);
00259       long modulus = m_ticks % oneframe;
00260       if ( modulus )
00261          m_ticks += oneframe - modulus;
00262    }
00263 
00264    float GetCell( double fps ) const
00265    {
00266       return GetFrame( fps ) + 1.0f;
00267    }
00268 
00269    void SetCell( double cell, double fps )
00270    {
00271       SetFrame( cell-1.0, fps );
00272    }
00273 
00274    String ToString(double fps, int timeunits, BOOL treatasdelta=FALSE) const;
00275 
00276    friend Time operator * ( double n, Time right );
00277    
00278    void SetTagged( BOOL state=TRUE )
00279    {
00280       SetTicks( state ? -1 : 0 );
00281    }
00282 
00283    BOOL IsTagged()
00284    {
00285       return GetTicks() == -1;
00286    }
00287 
00288    void SetMax()
00289    {
00290       SetTicks( MAX_TICKS );
00291    }
00292 
00293    void SetMin()
00294    {
00295       SetTicks( -MAX_TICKS );
00296    }
00297    
00298    void SetMinStep()
00299    {
00300       SetTicks( 1 );
00301    }
00302 
00303    BOOL IsMax()
00304    {
00305       return (m_ticks==MAX_TICKS);
00306    }
00307 
00308    BOOL IsMin()
00309    {
00310       return (m_ticks==-MAX_TICKS);
00311    }
00312 
00313    BOOL IsMinStep()
00314    {
00315       return (m_ticks==-1);
00316    }
00317 };
00318 
00319 inline Time operator * ( double n, Time right )
00320 {
00321    Time result( right );
00322    result *= n;
00323    return result;
00324 }
00325 
00326 inline Time abs( Time time )
00327 {
00328    Time result( time );
00329    result.SetTicks(abs(result.GetTicks()));
00330    return result;
00331 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
