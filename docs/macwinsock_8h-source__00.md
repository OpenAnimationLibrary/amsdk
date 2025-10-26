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

# macwinsock.h

[Go to the documentation of this file.](macwinsock_8h.md)

<div class="fragment">

``` fragment
00001 /* Copyright (c) 1995-1997, Altura Software, Inc. All rights reserved.  */
00002 
00003 /*
00004    winsock.h
00005    
00006    This header file corresponds to version 1.1 of the Windows Sockets
00007    specification.
00008    
00009    Parts of this file Copyright (c) 1982-1986, Regents of the University
00010    of California, Berkeley. All rights reserved. The Berkeley Software
00011    License Agreement specifies the terms and conditions for redistribution.
00012 */
00013 
00014 #ifndef _WINSOCKAPI_
00015 #define _WINSOCKAPI_
00016 
00017 /* Macintosh specific headers */
00018 #if !defined( __TYPES__ )
00019 #include <sys/Types.h>
00020 #endif
00021 
00022 #if !defined( __MIXEDMODE__ )
00023 #include <MixedMode.h>
00024 #endif
00025 
00026 #if !defined( _NMMESSAGE_H_ )
00027 #include "nmmessage.h"
00028 #endif
00029 /* End Macintosh specific headers   */
00030 
00031 /*
00032  * Basic system type definitions, taken from the BSD file sys/types.h.
00033  */
00034 
00035 #ifndef TRUE
00036 #define TRUE 1
00037 #endif
00038 
00039 #ifndef FALSE
00040 #define FALSE 0
00041 #endif
00042 
00043 typedef unsigned char   u_char;
00044 typedef unsigned short  u_short;
00045 typedef unsigned int u_int;
00046 typedef unsigned long   u_long;
00047 
00048 typedef u_int        SOCKET;
00049 
00050 /* Optional defines from Windows */
00051 #if !defined( _NM_NO_MSW_TYPES_ )
00052 
00053 // #if !defined( HANDLE )
00054 //    #define HANDLE    unsigned long
00055 // #endif
00056    
00057    #if !defined( MAKELONG )
00058       #define MAKELONG(loshort,hishort)   \
00059          ((u_long)(((long)hishort << 16) | ((short)loshort & 0xFFFF)))
00060    #endif
00061    
00062    #if !defined( LOWORD )
00063       #define LOWORD(thelong) \
00064          ((u_short)((long) thelong & 0xFFFF))
00065    #endif
00066    
00067    #if !defined( HIWORD )
00068       #define HIWORD(thelong) \
00069          ((u_short)(((long) thelong >> 16) & 0xFFFF))
00070    #endif
00071    
00072 #endif
00073 
00074 /*
00075  * select() uses arrays of SOCKETs. These macros manipulate such arrays.
00076  * FD_SETSIZE may be defined by the user before including this file, but
00077  * the default here should be >= 64.
00078  *
00079  * CAVEAT IMPLEMENTOR AND USER: These macros and types MUST be included
00080  * in winsock.h exactly as shown here.
00081  */
00082 
00083 #ifndef FD_SETSIZE
00084 #define FD_SETSIZE   64
00085 #endif   /* ndef FD_SETSIZE   */
00086 
00087 //typedef struct fd_set
00088 //{
00089 // u_int fd_count;            /* how many are SET? */
00090 // SOCKET   fd_array[FD_SETSIZE];   /* an array of SOCKETs  */
00091 //} fd_set;
00092 
00093 extern pascal int __WSAFDIsSet( SOCKET, fd_set * );
00094 
00095 #define FD_CLR(fd, set) \
00096 do                                              \
00097 {                                               \
00098    u_int __i;                                   \
00099    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++) \
00100    {                                            \
00101       if (((fd_set *)(set))->fd_array[__i] == fd)           \
00102       {                                         \
00103          while (__i < ((fd_set *)(set))->fd_count-1)     \
00104          {                                      \
00105                 ((fd_set *)(set))->fd_array[__i] =          \
00106                     ((fd_set *)(set))->fd_array[__i+1];        \
00107                 __i++;                                \
00108             }                                      \
00109             ((fd_set *)(set))->fd_count--;                  \
00110             break;                                    \
00111         }                                          \
00112     }                                           \
00113 } while ( 0 )
00114 
00115 #define FD_SET(fd, set) \
00116 do                                                    \
00117 {                                                     \
00118    if (((fd_set *)(set))->fd_count < FD_SETSIZE)                  \
00119       ((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++]=fd; \
00120 } while ( 0 )
00121 
00122 #define FD_ZERO(set) (((fd_set *)(set))->fd_count=0)
00123 
00124 #define FD_ISSET(fd, set)  __WSAFDIsSet((SOCKET)fd, (fd_set *)set)
00125 
00126 /*
00127  * Structure used in select() call, taken from the BSD file sys/time.h.
00128  */
00129 
00130 //struct timeval
00131 //{
00132 // long  tv_sec;     /* seconds           */
00133 // long  tv_usec; /* and microseconds  */
00134 //};
00135 
00136 /*
00137  * Operations on timevals
00138  *
00139  * NB: timercmp does not work for >= or <=
00140  */
00141 
00142 #define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
00143 
00144 #define timercmp(tvp, uvp, cmp)  \
00145    ((tvp)->tv_sec cmp (uvp)->tv_sec || \
00146     (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
00147 
00148 #define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0
00149 
00150 /*
00151  * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
00152  *
00153  *
00154  * Ioctl's have the command encoded in the lower word,
00155  * and the size of any in or out parameters in the upper
00156  * word.  The high 2 bits of the upper word are used
00157  * to encode the in/out status of the parameter; for now
00158  * we restrict parameters to at most 128 bytes.
00159  */
00160 
00161 #define IOCPARM_MASK    0x7F            /* parameters must be < 128 bytes */
00162 #define IOC_VOID        0x20000000      /* no parameters */
00163 #define IOC_OUT         0x40000000      /* copy out parameters */
00164 #define IOC_IN          0x80000000      /* copy in parameters */
00165 #define IOC_INOUT       (IOC_IN|IOC_OUT)
00166                                         /* 0x20000000 distinguishes new &
00167                                            old ioctl's */
00168 #define _IO(x,y)        (IOC_VOID|(x<<8)|y)
00169 
00170 #define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
00171 
00172 #define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
00173 
00174 #define FIONREAD    _IOR('f', 127, u_long) /* get # bytes to read */
00175 #define FIONBIO     _IOW('f', 126, u_long) /* set/clear non-blocking i/o */
00176 #define FIOASYNC    _IOW('f', 125, u_long) /* set/clear async i/o */
00177 
00178 /* Socket I/O Controls */
00179 #define SIOCSHIWAT  _IOW('s',  0, u_long)  /* set high watermark */
00180 #define SIOCGHIWAT  _IOR('s',  1, u_long)  /* get high watermark */
00181 #define SIOCSLOWAT  _IOW('s',  2, u_long)  /* set low watermark */
00182 #define SIOCGLOWAT  _IOR('s',  3, u_long)  /* get low watermark */
00183 #define SIOCATMARK  _IOR('s',  7, u_long)  /* at oob mark? */
00184 
00185 /*
00186  * Structures returned by network data base library, taken from the
00187  * BSD file netdb.h.  All addresses are supplied in host order, and
00188  * returned in network order (suitable for use in system calls).
00189  */
00190 
00191 struct hostent
00192 {
00193    char  *h_name;       /* official name of host */
00194    char  **h_aliases;      /* alias list */
00195    short h_addrtype;       /* host address type */
00196    short h_length;         /* length of address */
00197    char  **h_addr_list;    /* list of addresses */
00198 #define h_addr  h_addr_list[0]   /* address, for backward compat */
00199 };
00200 
00201 /*
00202  * It is assumed here that a network number fits in 32 bits.
00203  */
00204 struct netent
00205 {
00206    char  *n_name;    /* official name of net */
00207    char  **n_aliases;   /* alias list */
00208    short n_addrtype;    /* net address type */
00209    u_long   n_net;         /* network # */
00210 };
00211 
00212 struct servent
00213 {
00214    char  *s_name;       /* official service name */
00215    char  **s_aliases;  /* alias list */
00216    short   s_port;             /* port # */
00217    char  *s_proto;         /* protocol to use */
00218 };
00219 
00220 struct protoent
00221 {
00222    char  *p_name;    /* official protocol name */
00223    char  **p_aliases;   /* alias list */
00224    short   p_proto;     /* protocol # */
00225 };
00226 
00227 /*
00228  * Constants and structures defined by the internet system,
00229  * Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
00230  */
00231 
00232 /*
00233  * Protocols
00234  */
00235 #define IPPROTO_IP         0     /* dummy for IP */
00236 #define IPPROTO_ICMP    1     /* control message protocol */
00237 #define IPPROTO_GGP        2     /* gateway^2 (deprecated) */
00238 #define IPPROTO_TCP        6     /* tcp */
00239 #define IPPROTO_PUP        12    /* pup */
00240 #define IPPROTO_UDP        17    /* user datagram protocol */
00241 #define IPPROTO_IDP        22    /* xns idp */
00242 #define IPPROTO_ND         77    /* UNOFFICIAL net disk proto */
00243 
00244 #define IPPROTO_RAW        255      /* raw IP packet */
00245 #define IPPROTO_MAX        256
00246 
00247 /*
00248  * Port/socket numbers: network standard functions
00249  */
00250 #define IPPORT_ECHO        7
00251 #define IPPORT_DISCARD     9
00252 #define IPPORT_SYSTAT      11
00253 #define IPPORT_DAYTIME     13
00254 #define IPPORT_NETSTAT     15
00255 #define IPPORT_FTP         21
00256 #define IPPORT_TELNET      23
00257 #define IPPORT_SMTP        25
00258 #define IPPORT_TIMESERVER  37
00259 #define IPPORT_NAMESERVER  42
00260 #define IPPORT_WHOIS    43
00261 #define IPPORT_MTP         57
00262 
00263 /*
00264  * Port/socket numbers: host specific functions
00265  */
00266 #define IPPORT_TFTP        69
00267 #define IPPORT_RJE         77
00268 #define IPPORT_FINGER      79
00269 #define IPPORT_TTYLINK     87
00270 #define IPPORT_SUPDUP      95
00271 
00272 /*
00273  * UNIX TCP sockets
00274  */
00275 #define IPPORT_EXECSERVER  512
00276 #define IPPORT_LOGINSERVER 513
00277 #define IPPORT_CMDSERVER   514
00278 #define IPPORT_EFSSERVER   520
00279 
00280 /*
00281  * UNIX UDP sockets
00282  */
00283 #define IPPORT_BIFFUDP     512
00284 #define IPPORT_WHOSERVER   513
00285 #define IPPORT_ROUTESERVER 520
00286                               /* 520+1 also used */
00287 
00288 /*
00289  * Ports < IPPORT_RESERVED are reserved for
00290  * privileged processes (e.g. root).
00291  */
00292 #define IPPORT_RESERVED    1024
00293 
00294 /*
00295  * Link numbers
00296  */
00297 #define IMPLINK_IP         155
00298 #define IMPLINK_LOWEXPER   156
00299 #define IMPLINK_HIGHEXPER  158
00300 
00301 /*
00302  * Internet address (old style... should be updated)
00303  */
00304 struct in_addr
00305 {
00306    union
00307    {
00308       struct { u_char s_b1, s_b2, s_b3, s_b4; } S_un_b;
00309       struct { u_short s_w1, s_w2; } S_un_w;
00310       u_long S_addr;
00311    } S_un;
00312 
00313 #define s_addr  S_un.S_addr
00314                         /* can be used for most tcp & ip code */
00315 #define s_host  S_un.S_un_b.s_b2
00316                         /* host on imp */
00317 #define s_net   S_un.S_un_b.s_b1
00318                         /* network */
00319 #define s_imp   S_un.S_un_w.s_w2
00320                         /* imp */
00321 #define s_impno S_un.S_un_b.s_b4
00322                         /* imp # */
00323 #define s_lh   S_un.S_un_b.s_b3
00324                         /* logical host */
00325 };
00326 
00327 /*
00328  * Definitions of bits in internet address integers.
00329  * On subnets, the decomposition of addresses to host and net parts
00330  * is done according to subnet mask, not the masks here.
00331  */
00332 #define IN_CLASSA(i)       (((long)(i) & 0x80000000) == 0)
00333 #define IN_CLASSA_NET         0xff000000
00334 #define IN_CLASSA_NSHIFT      24
00335 #define IN_CLASSA_HOST        0x00ffffff
00336 #define IN_CLASSA_MAX         128
00337 
00338 #define IN_CLASSB(i)       (((long)(i) & 0xc0000000) == 0x80000000)
00339 #define IN_CLASSB_NET         0xffff0000
00340 #define IN_CLASSB_NSHIFT      16
00341 #define IN_CLASSB_HOST        0x0000ffff
00342 #define IN_CLASSB_MAX         65536
00343 
00344 #define IN_CLASSC(i)       (((long)(i) & 0xc0000000) == 0xc0000000)
00345 #define IN_CLASSC_NET         0xffffff00
00346 #define IN_CLASSC_NSHIFT      8
00347 #define IN_CLASSC_HOST        0x000000ff
00348 
00349 #define INADDR_ANY            (u_long)0x00000000
00350 #define INADDR_LOOPBACK       0x7f000001
00351 #define INADDR_BROADCAST      (u_long)0xffffffff   
00352 #define INADDR_NONE           0xffffffff
00353 
00354 /*
00355  * Socket address, internet style.
00356  */
00357 struct sockaddr_in
00358 {
00359    short       sin_family;
00360    u_short        sin_port;
00361    struct in_addr sin_addr;
00362    char        sin_zero[8];
00363 };
00364 
00365 #define WSADESCRIPTION_LEN 256
00366 #define WSASYS_STATUS_LEN  128
00367 
00368 typedef struct WSAData
00369 {
00370    u_short     wVersion;
00371    u_short     wHighVersion;
00372    char     szDescription[WSADESCRIPTION_LEN+1];
00373    char     szSystemStatus[WSASYS_STATUS_LEN+1];
00374    u_short     iMaxSockets;
00375    u_short     iMaxUdpDg;
00376    char     *lpVendorInfo;
00377 } WSADATA;
00378 
00379 typedef WSADATA *LPWSADATA;
00380 
00381 /*
00382  * Options for use with [gs]etsockopt at the IP level.
00383  */
00384 #ifndef IP_OPTIONS
00385 #define IP_OPTIONS   1           /* set/get IP per-packet options */
00386 #endif
00387 
00388 /*
00389  * Multicast support
00390  */
00391 #ifndef IP_TOS
00392    #define  IP_TOS               0x02
00393    #define  IP_TTL               0x03
00394    #define  IP_MULTICAST_IF         0x1010   /* set/get IP multicast interface   */
00395    #define  IP_MULTICAST_TTL     0x1011   /* set/get IP multicast timetolive  */
00396    #define  IP_MULTICAST_LOOP    0x1012   /* set/get IP multicast loopback */
00397    #define  IP_ADD_MEMBERSHIP    0x1013   /* add an IP group membership    */
00398    #define  IP_DROP_MEMBERSHIP      0x1014   /* drop an IP group membership      */
00399 #endif
00400 #define IP_DONTFRAGMENT          0x09  /* set/get IP Don't Fragment flag   */
00401 
00402 /*
00403  * More multicast stuff
00404  */
00405 #define IP_DEFAULT_MULTICAST_TTL   1      /* nor