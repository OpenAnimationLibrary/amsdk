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

# keyintf.h

[Go to the documentation of this file.](keyintf_8h.md)

<div class="fragment">

``` fragment
00001 /* KB  12/31/01  \Ken90\Include\3rdParty\keyintf.h
00002  * keyintf.h -- KeyObtain(), KeyStatus(), KeyReturn(),
00003  *                KeyEncrypt(), KeyVersion(), KeyIntf3XXX()
00004  *
00005  * (c) 1990-98 Sassafras Software, Inc.
00006  */
00007 
00008 #ifndef  __KEYINTF__
00009 #define __KEYINTF__  0x5000
00010 
00011 #define SC_DETACHABLE   0x01  /* key can be reclaimed by KeyServer (or connection can go down) without affecting program */
00012 #define SC_LOCALZONE 0x02  /* key can be obtained by this client only if client and server are in the same zone */
00013 #define SC_SRVRSPECIFIC 0x04  /* key can be obtained only if server IDs match.  Not applicable to remote function keys */
00014 #define SC_BACKGDWARN   0x08  /* give warnings if program is left in the background for too long */
00015 #define SC_MULTILAUNCH  0x40  /* key can be shared between multiple instances of the program on the same computer */
00016 #define SC_HAVEKEY      0x80  /* key is valid and held by this client (app must quit if SC_HAVEKEY and SC_DETACHABLE are both zero) */
00017 
00018 #define SDV_NOQUIT      0x00200000  /* don't force program to quit if key becomes invalid */
00019 #define SDV_NOPTCH      0x00400000  /* don't patch ExitToShell (program calls KeyReturn) */
00020 #define SDV_DEFER    0x00800000  /* don't post alert message until next SystemTask */
00021 #define  SDV_NOCUST     0x04000000  /* don't post custom message (pass back in custBuffer) */
00022 #define  SDV_NONTFY     0x08000000  /* don't ask if user wants notification (on denial) */
00023 #define SDV_NOINIT      0x10000000  /* don't init managers on key denial (to post message) */
00024 #define SDV_NOPOST      0x20000000  /* don't post messages on key denial */
00025 #define SDV_NOEXIT      0x40000000  /* don't call ExitToShell on key denial */
00026 #define SDV_NOCSUM      0x80000000  /* don't compute checksum before accepting key */
00027 
00028 /* Remote Functions typically use SDV_NOCSUM, SDV_NOEXIT, SDV_NOINIT */
00029 /* INITs typically use SDV_NOCSUM, SDV_NOEXIT, SDV_NOPOST, SDV_NOINIT, SDV_NOPTCH */
00030 
00031 #define KEY_SUCCESS        0
00032 #define KEY_FAILURE        -1
00033 
00034 #define  KEY_FIRSTERR      -10000
00035 #define KEY_NOTAVAIL    -10000   /* key is not available, and user is not on notification queue */
00036 #define KEY_MAXUSERS    -10001   /* the keyserver is already supporting the maximum number of clients */
00037 #define KEY_MAXAPPS        -10002   /* the maximum number of keyed programs are already available */
00038 #define KEY_REMOTEDENY     -10003   /* the remote function has denied this key for reasons only you know */
00039 #define KEY_OLDPROGRAM     -10004   /* the program is too old for this version of the client software */
00040 #define KEY_ONQUEUE        -10005   /* key is not available - client requested to be placed on queue */
00041 #define KEY_NOSELECTION    -10006   /* there is no KeyServer chosen */
00042 #define KEY_OLDCLIENT      -10007   /* the client software is too old to get a key for this program */
00043 #define KEY_NORESPONSE     -10008   /* no response from the server (server WAS found on the network) */
00044 #define KEY_NOREASON    -10009   /* key is not available - no reason was given for denial */
00045 #define KEY_UNKNOWN        -10010   /* unknown response was received from the server */
00046 #define KEY_BADCHKSUM      -10011   /* key received had a diferent checksum than that provided */
00047 #define KEY_IDDIFFERS      -10012   /* this app was keyed by a different KeyServer than the one currently chosen */
00048 #define KEY_AUTHABORT      -10013   /* this app requires authentication (user cancelled authentication) */
00049 #define KEY_NOTAUTHED      -10014   /* this app requires authentication (user failed to type correct password) */
00050 #define KEY_USRUNKNOWN     -10015   /* the user name typed in the chooser (or auth dialog) is not known */
00051 #define KEY_PERMDENIED     -10016   /* the user named is never allowed to log on to the chosen server */
00052 #define KEY_GUESTONLY      -10017   /* the user named is allowed to log on to the chosen server as a guest only */
00053 #define KEY_BADCACHE    -10018   /* the user attempted to use the key from the key cache, but it was improper */
00054 #define KEY_CACHEABORT     -10019   /* there is a key in the cache, but the user cancelled or typed a bad password */
00055 #define KEY_NOTKEYED    -10020   /* returned by KeyStatus if the indicated program is not keyed */
00056 #define KEY_NOTSYSVOLUME   -10021   /* there is a portable key available, but it must be moved to the system volume */
00057 #define KEY_FLOPPYDISKSYS  -10022   /* there is a portable key available, but it canÕt be used when the System is on a floppy */
00058 #define KEY_PKVERSUNKNOWN  -10023   /* there is a portable key available, but itÕs format version is unknown */
00059 #define KEY_FLOPPYDISK     -10024   /* there is a portable key available, but it canÕt be used from a floppy disk */
00060 #define KEY_NOAFPLAUNCH    -10025   /* the program cannot be launched off of an AFP volume */
00061 #define KEY_MUSTAFPLAUNCH  -10026   /* the program must be launched off of an AFP volume */
00062 #define KEY_SERVERNOTFOUND -10027   /* the server could not be found on the network (Windows only) */
00063 #define KEY_NOTQUEUED      -10028   /* key is not available - user did not want to be notified */
00064 #define KEY_LASTERR        -10028
00065 
00066 #define KEY_NOCLIENT    -35      /* KeyAccess was not in the System Folder at startup (generated by glue) */
00067 
00068 #define KEY_HANDLE         unsigned long
00069 #define KEY_RESULT         short
00070 
00071 //#ifdef MACINTINTOSH
00072 #ifdef _OS9
00073 #undef FAR
00074 #define FAR
00075 #define KEY_ROUTINE(type)  pascal type
00076 #endif
00077 
00078 //#ifdef WINDOWS
00079 #ifndef _OS9 
00080 #define KEY_ROUTINE(type)  type WINAPI
00081 #endif
00082 
00083 #ifdef __powerc
00084 #pragma options align=mac68k
00085 #endif
00086 #ifdef WIN32
00087 #pragma pack(push)
00088 #pragma pack(2)
00089 #endif
00090 typedef struct ksrr { 
00091    short length;           /* [out] length of data returned by the remote function */
00092    short reserved;         /* [out] reserved for future use */
00093    long  buffer[145];      /* [out] buffer for data returned by the remote function */
00094 } KSResultRec;
00095 #ifdef __powerc
00096 #pragma options align=reset
00097 #endif
00098 #ifdef WIN32
00099 #pragma pack(pop)
00100 #endif
00101 
00102 #ifdef __cplusplus
00103 extern "C" {
00104 #endif
00105 
00106 KEY_ROUTINE(KEY_RESULT)
00107 KeyObtain (
00108          char FAR *params,    /* [in]     ->256 bytes of data to be sent to KeyServer */
00109          long  appID,         /* [in]     unique (and constant) identifier for app (pre-assigned) */
00110          long  sdvFlags,      /* [in]     flags as detailed above */
00111          short expLength,     /* [in]     expected length of return result */
00112          KSResultRec FAR *result,/* [in]     ->500 byte buffer for results to be received from KeyServer */
00113          unsigned char FAR *name,/* [in]     ->name of program, NULL for default (CurApName) */
00114          long FAR *userLink,     /* [out] unique user link, to be received from KeyServer */
00115          KEY_HANDLE FAR *keyh /* [out] on success, reference for the obtained key */
00116    );
00117 
00118 KEY_ROUTINE(KEY_RESULT)
00119 KeyStatusEx (
00120          KEY_HANDLE keyh,     /* [in]     reference handed back from KeyObtain */
00121          long FAR *flags,     /* [out] low byte = service class.  See above bits for details */
00122          long FAR *foreTime,     /* [out] number of seconds that the keyed app has been in foreground */
00123          long FAR *timeout    /* [out] adsolute time that license (may) expire) */
00124    );
00125 
00126 KEY_ROUTINE(KEY_RESULT)
00127 KeyStatus (
00128          KEY_HANDLE keyh,     /* [in]     reference handed back from KeyObtain */
00129          long FAR *flags,     /* [out] low byte = service class.  See above bits for details */
00130          long FAR *foreTime      /* [out] number of seconds that the keyed app has been in foreground */
00131    );
00132 
00133 KEY_ROUTINE(KEY_RESULT)
00134 KeyUpdate (
00135          KEY_HANDLE keyh,     /* [in]     reference handed back from KeyObtain */
00136          char FAR *params,    /* [in]     ->256 bytes of data to be sent to KeyServer */
00137          KSResultRec FAR *result /* [in/out] ->500 byte buffer for results to be received from KeyServer */
00138    );
00139 
00140 KEY_ROUTINE(KEY_RESULT)
00141 KeyReturn (
00142          KEY_HANDLE keyh         /* [in]     reference handed back from KeyObtain (as return result) */
00143    );
00144 
00145 KEY_ROUTINE(KEY_RESULT)
00146 KeySession (
00147          KEY_HANDLE keyh,     /* [in]     reference handed back from KeyObtain */
00148          long FAR *session    /* [out] session assoctiated with this license */
00149    );
00150 
00151 KEY_ROUTINE(KEY_RESULT)
00152 KeyEncrypt (
00153          char FAR *data,         /* [in/out] data to encrypt the plaintext (encrypted text returned here) */
00154          char FAR *text       /* [in]     plaintext key for encryption (remains intact across call) */
00155    );
00156 
00157 KEY_ROUTINE(KEY_RESULT)
00158 KeyVersion (
00159          short FAR *clientVersion,  /* [out] version of client software (KeyAccess) that is currently running */
00160          short FAR *serverVersion   /* [out] version of server software (KeyServer), if connection is present */
00161    );
00162 
00163 KEY_ROUTINE(KEY_RESULT)
00164 KeyLog (
00165          unsigned char FAR *line    /* [in]     line to write in KeyServerÕs log file (return characters are illegal) */
00166    );
00167 
00168 KEY_ROUTINE(KEY_RESULT)
00169 KeyIntf5000 (
00170          void
00171    );
00172 
00173 #ifdef __cplusplus
00174 }
00175 #endif
00176 
00177 #endif /* __KEYINTF__ */
00178 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
