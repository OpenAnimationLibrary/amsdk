mally limit m'casts to 1 hop  */
00406 #define IP_DEFAULT_MULTICAST_LOOP  1      /* normally hear sends if a member  */
00407 #define IP_MAX_MEMBERSHIPS         20     /* per socket; must fit in one mbuf */
00408 
00409 /*
00410  * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
00411  */
00412 struct ip_mreq {
00413    struct in_addr  imr_multiaddr;  /* IP multicast address of group */
00414    struct in_addr  imr_interface;  /* local IP address of interface */
00415 };
00416 
00417 /*
00418  * Definitions related to sockets: types, address families, options,
00419  * taken from the BSD file sys/socket.h.
00420  */
00421 
00422 /*
00423  * This is used instead of -1, since the
00424  * SOCKET type is unsigned.
00425  */
00426 #define INVALID_SOCKET  (SOCKET)(~0)
00427 #define SOCKET_ERROR (-1)
00428 
00429 /*
00430  * Types
00431  */
00432 #define SOCK_STREAM     1           /* stream socket */
00433 #define SOCK_DGRAM      2           /* datagram socket */
00434 #define SOCK_RAW     3           /* raw-protocol interface */
00435 #define SOCK_RDM     4           /* reliably-delivered message */
00436 #define SOCK_SEQPACKET  5           /* sequenced packet stream */
00437 
00438 /*
00439  * Option flags per-socket.
00440  */
00441 #define SO_DEBUG     0x0001        /* turn on debugging info recording */
00442 #define SO_ACCEPTCONN   0x0002        /* socket has had listen() */
00443 #define SO_REUSEADDR 0x0004        /* allow local address reuse */
00444 #define SO_KEEPALIVE 0x0008        /* keep connections alive */
00445 #define SO_DONTROUTE 0x0010        /* just use interface addresses */
00446 #define SO_BROADCAST 0x0020        /* permit sending of broadcast msgs */
00447 #define SO_USELOOPBACK  0x0040        /* bypass hardware when possible */
00448 #define SO_LINGER    0x0080        /* linger on close if data present */
00449 #define SO_OOBINLINE 0x0100        /* leave received OOB data in line */
00450 
00451 #define SO_DONTLINGER   (u_int)(~SO_LINGER)
00452 
00453 /*
00454  * Additional options.
00455  */
00456 #define SO_SNDBUF    0x1001        /* send buffer size */
00457 #define SO_RCVBUF    0x1002        /* receive buffer size */
00458 #define SO_SNDLOWAT     0x1003        /* send low-water mark */
00459 #define SO_RCVLOWAT     0x1004        /* receive low-water mark */
00460 #define SO_SNDTIMEO     0x1005        /* send timeout */
00461 #define SO_RCVTIMEO     0x1006        /* receive timeout */
00462 #define SO_ERROR     0x1007        /* get error status and clear */
00463 #define SO_TYPE         0x1008        /* get socket type */
00464 
00465 /*
00466  * TCP options.
00467  */
00468 #ifndef TCP_NODELAY
00469 #define TCP_NODELAY     0x0001
00470 #endif
00471 
00472 /*
00473  * Address families.
00474  */
00475 #define AF_UNSPEC    0        /* unspecified */
00476 #define AF_UNIX         1        /* local to host (pipes, portals) */
00477 #define AF_INET         2        /* internetwork: UDP, TCP, etc. */
00478 #define AF_IMPLINK      3        /* arpanet imp addresses */
00479 #define AF_PUP       4        /* pup protocols: e.g. BSP */
00480 #define AF_CHAOS     5        /* mit CHAOS protocols */
00481 #define AF_NS        6        /* XEROX NS protocols */
00482 #define AF_ISO       7        /* ISO protocols */
00483 #define AF_OSI       AF_ISO      /* OSI is ISO */
00484 #define AF_ECMA         8        /* european computer manufacturers */
00485 #define AF_DATAKIT      9        /* datakit protocols */
00486 #define AF_CCITT     10       /* CCITT protocols, X.25 etc */
00487 #define AF_SNA       11       /* IBM SNA */
00488 #define AF_DECnet    12       /* DECnet */
00489 #define AF_DLI       13       /* Direct data link interface */
00490 #define AF_LAT       14       /* LAT */
00491 #define AF_HYLINK    15       /* NSC Hyperchannel */
00492 #define AF_APPLETALK 16       /* AppleTalk */
00493 #define AF_NETBIOS      17       /* NetBios-style addresses */
00494 
00495 #define AF_MAX       18
00496 
00497 /*
00498  * Structure used by kernel to store most
00499  * addresses.
00500  */
00501 struct sockaddr
00502 {
00503    u_short sa_family;      /* address family */
00504    char  sa_data[14];   /* up to 14 bytes of direct address */
00505 };
00506 
00507 /*
00508  * Structure used by kernel to pass protocol
00509  * information in raw sockets.
00510  */
00511 struct sockproto
00512 {
00513    u_short sp_family;      /* address family */
00514    u_short sp_protocol; /* protocol */
00515 };
00516 
00517 /*
00518  * Protocol families, same as address families for now.
00519  */
00520 #define PF_UNSPEC    AF_UNSPEC
00521 #define PF_UNIX         AF_UNIX
00522 #define PF_INET         AF_INET
00523 #define PF_IMPLINK      AF_IMPLINK
00524 #define PF_PUP       AF_PUP
00525 #define PF_CHAOS     AF_CHAOS
00526 #define PF_NS        AF_NS
00527 #define PF_ISO       AF_ISO
00528 #define PF_OSI       AF_OSI
00529 #define PF_ECMA         AF_ECMA
00530 #define PF_DATAKIT      AF_DATAKIT
00531 #define PF_CCITT     AF_CCITT
00532 #define PF_SNA       AF_SNA
00533 #define PF_DECnet    AF_DECnet
00534 #define PF_DLI       AF_DLI
00535 #define PF_LAT       AF_LAT
00536 #define PF_HYLINK    AF_HYLINK
00537 #define PF_APPLETALK AF_APPLETALK
00538 
00539 #define PF_MAX       AF_MAX
00540 
00541 /*
00542  * Structure used for manipulating linger option.
00543  */
00544 struct linger
00545 {
00546    u_short l_onoff;  /* option on/off */
00547    u_short l_linger; /* linger time */
00548 };
00549 
00550 /*
00551  * Level number for (get/set)sockopt() to apply to socket itself.
00552  */
00553 #define SOL_SOCKET      0xffff        /* options for socket level */
00554 
00555 /*
00556  * Maximum queue length specifiable by listen.
00557  */
00558 #define SOMAXCONN    5
00559 
00560 #define MSG_OOB         0x1          /* process out-of-band data */
00561 #define MSG_PEEK     0x2          /* peek at incoming message */
00562 #define MSG_DONTROUTE   0x4          /* send without using routing tables */
00563 
00564 #define MSG_MAXIOVLEN   16
00565 
00566 /*
00567  * Define constant based on rfc883, used by gethostbyxxxx() calls.
00568  */
00569 #define MAXGETHOSTSTRUCT      1024
00570 
00571 /*
00572  * Define flags to be used with the WSAAsyncSelect() call.
00573  */
00574 #define FD_READ      0x01
00575 #define FD_WRITE  0x02
00576 #define FD_OOB    0x04
00577 #define FD_ACCEPT 0x08
00578 #define FD_CONNECT   0x10
00579 #define FD_CLOSE  0x20
00580 
00581 /*
00582  * All Windows Sockets error constants are biased by WSABASEERR from
00583  * the "normal"
00584  */
00585 #define WSABASEERR           10000
00586 
00587 /*
00588  * Windows Sockets definitions of regular Microsoft C error constants
00589  */
00590 #define WSAEINTR           (WSABASEERR+4)
00591 #define WSAEBADF           (WSABASEERR+9)
00592 #define WSAEACCES          (WSABASEERR+13)
00593 #define WSAEFAULT          (WSABASEERR+14)
00594 #define WSAEINVAL          (WSABASEERR+22)
00595 #define WSAEMFILE          (WSABASEERR+24)
00596 
00597 /*
00598  * Windows Sockets definitions of regular Berkeley error constants
00599  */
00600 #define WSAEWOULDBLOCK     (WSABASEERR+35)
00601 #define WSAEINPROGRESS     (WSABASEERR+36)
00602 #define WSAEALREADY        (WSABASEERR+37)
00603 #define WSAENOTSOCK        (WSABASEERR+38)
00604 #define WSAEDESTADDRREQ    (WSABASEERR+39)
00605 #define WSAEMSGSIZE        (WSABASEERR+40)
00606 #define WSAEPROTOTYPE      (WSABASEERR+41)
00607 #define WSAENOPROTOOPT     (WSABASEERR+42)
00608 #define WSAEPROTONOSUPPORT (WSABASEERR+43)
00609 #define WSAESOCKTNOSUPPORT (WSABASEERR+44)
00610 #define WSAEOPNOTSUPP      (WSABASEERR+45)
00611 #define WSAEPFNOSUPPORT    (WSABASEERR+46)
00612 #define WSAEAFNOSUPPORT    (WSABASEERR+47)
00613 #define WSAEADDRINUSE      (WSABASEERR+48)
00614 #define WSAEADDRNOTAVAIL   (WSABASEERR+49)
00615 #define WSAENETDOWN        (WSABASEERR+50)
00616 #define WSAENETUNREACH     (WSABASEERR+51)
00617 #define WSAENETRESET    (WSABASEERR+52)
00618 #define WSAECONNABORTED    (WSABASEERR+53)
00619 #define WSAECONNRESET      (WSABASEERR+54)
00620 #define WSAENOBUFS         (WSABASEERR+55)
00621 #define WSAEISCONN         (WSABASEERR+56)
00622 #define WSAENOTCONN        (WSABASEERR+57)
00623 #define WSAESHUTDOWN    (WSABASEERR+58)
00624 #define WSAETOOMANYREFS    (WSABASEERR+59)
00625 #define WSAETIMEDOUT    (WSABASEERR+60)
00626 #define WSAECONNREFUSED    (WSABASEERR+61)
00627 #define WSAELOOP        (WSABASEERR+62)
00628 #define WSAENAMETOOLONG    (WSABASEERR+63)
00629 #define WSAEHOSTDOWN    (WSABASEERR+64)
00630 #define WSAEHOSTUNREACH    (WSABASEERR+65)
00631 #define WSAENOTEMPTY    (WSABASEERR+66)
00632 #define WSAEPROCLIM        (WSABASEERR+67)
00633 #define WSAEUSERS       (WSABASEERR+68)
00634 #define WSAEDQUOT       (WSABASEERR+69)
00635 #define WSAESTALE       (WSABASEERR+70)
00636 #define WSAEREMOTE         (WSABASEERR+71)
00637 
00638 /*
00639  * Extended Windows Sockets error constant definitions
00640  */
00641 #define WSASYSNOTREADY     (WSABASEERR+91)
00642 #define WSAVERNOTSUPPORTED (WSABASEERR+92)
00643 #define WSANOTINITIALISED  (WSABASEERR+93)
00644 
00645 /*
00646  * Error return codes from gethostbyname() and gethostbyaddr()
00647  * (when using the resolver). Note that these errors are
00648  * retrieved via WSAGetLastError() and must therefore follow
00649  * the rules for avoiding clashes with error numbers from
00650  * specific implementations or language run-time systems.
00651  * For this reason the codes are based at WSABASEERR+1001.
00652  * Note also that [WSA]NO_ADDRESS is defined only for
00653  * compatibility purposes.
00654  */
00655 
00656 #define h_errno       WSAGetLastError()
00657 
00658 /* Authoritative Answer: Host not found */
00659 #define WSAHOST_NOT_FOUND  (WSABASEERR+1001)
00660 #define HOST_NOT_FOUND     WSAHOST_NOT_FOUND
00661 
00662 /* Non-Authoritative: Host not found, or SERVERFAIL */
00663 #define WSATRY_AGAIN    (WSABASEERR+1002)
00664 #define TRY_AGAIN       WSATRY_AGAIN
00665 
00666 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
00667 #define WSANO_RECOVERY     (WSABASEERR+1003)
00668 #define NO_RECOVERY        WSANO_RECOVERY
00669 
00670 /* Valid name, no data record of requested type */
00671 #define WSANO_DATA         (WSABASEERR+1004)
00672 #define NO_DATA            WSANO_DATA
00673 
00674 /* no address, look for MX record */
00675 #define WSANO_ADDRESS      WSANO_DATA
00676 #define NO_ADDRESS         WSANO_ADDRESS
00677 
00678 /*
00679  * Windows Sockets errors redefined as regular Berkeley error constants
00680  */
00681 #define EWOULDBLOCK        WSAEWOULDBLOCK
00682 #define EINPROGRESS        WSAEINPROGRESS
00683 #define EALREADY        WSAEALREADY
00684 #define ENOTSOCK        WSAENOTSOCK
00685 #define EDESTADDRREQ    WSAEDESTADDRREQ
00686 #define EMSGSIZE        WSAEMSGSIZE
00687 #define EPROTOTYPE         WSAEPROTOTYPE
00688 #define ENOPROTOOPT        WSAENOPROTOOPT
00689 #define EPROTONOSUPPORT    WSAEPROTONOSUPPORT
00690 #define ESOCKTNOSUPPORT    WSAESOCKTNOSUPPORT
00691 #define EOPNOTSUPP         WSAEOPNOTSUPP
00692 #define EPFNOSUPPORT    WSAEPFNOSUPPORT
00693 #define EAFNOSUPPORT    WSAEAFNOSUPPORT
00694 #define EADDRINUSE         WSAEADDRINUSE
00695 #define EADDRNOTAVAIL      WSAEADDRNOTAVAIL
00696 #define ENETDOWN        WSAENETDOWN
00697 #define ENETUNREACH        WSAENETUNREACH
00698 #define ENETRESET       WSAENETRESET
00699 #define ECONNABORTED    WSAECONNABORTED
00700 #define ECONNRESET         WSAECONNRESET
00701 #define ENOBUFS            WSAENOBUFS
00702 #define EISCONN            WSAEISCONN
00703 #define ENOTCONN        WSAENOTCONN
00704 #define ESHUTDOWN       WSAESHUTDOWN
00705 #define ETOOMANYREFS    WSAETOOMANYREFS
00706 #define ETIMEDOUT       WSAETIMEDOUT
00707 #define ECONNREFUSED    WSAECONNREFUSED
00708 #define ELOOP           WSAELOOP
00709 #define ENAMETOOLONG    WSAENAMETOOLONG
00710 #define EHOSTDOWN       WSAEHOSTDOWN
00711 #define EHOSTUNREACH    WSAEHOSTUNREACH
00712 #define ENOTEMPTY       WSAENOTEMPTY
00713 #define EPROCLIM        WSAEPROCLIM
00714 #define EUSERS          WSAEUSERS
00715 #define EDQUOT          WSAEDQUOT
00716 #define ESTALE          WSAESTALE
00717 #define EREMOTE            WSAEREMOTE
00718 
00719 /* Macintosh specific definitions   */
00720 
00721 /* Macintosh host ordering is the same as network ordering  */
00722 #define htonl(hostlong)    ((u_long)(hostlong))
00723 #define htons(hostshort)   ((u_short)(hostshort))
00724 #define ntohl(netlong)     ((u_long)(netlong))
00725 #define ntohs(netshort)    ((u_short)(netshort))
00726 
00727 typedef pascal long (*WSABlockingHookProcPtr)( void );
00728 
00729 enum
00730 {
00731    uppWSABlockingHookInfo = kPascalStackBased
00732       | RESULT_SIZE( SIZE_CODE( sizeof( long ) ) )
00733 };
00734 
00735 /*
00736 #if GENERATINGCFM
00737 
00738 typedef UniversalProcPtr WSABlockingHookUPP;
00739 
00740 #define NewWSABlockingHookProc(userRoutine)  \
00741    (WSABlockingHookUPP) NewRoutineDescriptor((ProcPtr)(userRoutine), uppWSABlockingHookInfo, GetCurrentArchitecture())
00742 
00743 #define CallWSABlockingHookProc(userRoutine) \
00744    CallUniversalProc((UniversalProcPtr)(userRoutine), uppWSABlockingHookInfo)
00745 
00746 #else
00747 */
00748 typedef WSABlockingHookProcPtr WSABlockingHookUPP;
00749 
00750 #define NewWSABlockingHookProc(userRoutine)  \
00751    ((WSABlockingHookUPP) (userRoutine))
00752 
00753 #define CallWSABlockingHookProc(userRoutine) \
00754    (*(userRoutine))()
00755 
00756 //#endif
00757 
00758 #ifdef __cplusplus
00759 extern "C" {
00760 #endif
00761 
00762 /* Socket function prototypes */
00763 
00764 pascal SOCKET  accept( SOCKET s, struct sockaddr *addr, int *addrlen );
00765 pascal int     bind( SOCKET s, struct sockaddr *addr, int namelen );
00766 pascal int     closesocket( SOCKET s );
00767 pascal int     connect( SOCKET s, struct sockaddr *name, int namelen );
00768 pascal int     ioctlsocket( SOCKET s, long cmd, u_long *argp );
00769 pascal int     getpeername( SOCKET s, struct sockaddr *name, int *namelen );
00770 pascal int     getsockname( SOCKET s, struct sockaddr *name, int *namelen );
00771 pascal int     getsockopt( SOCKET s, int level, int optname, char *optval, int *optlen );
00772 pascal u_long  inet_addr( char *cp );
00773 pascal char *  inet_ntoa( struct in_addr in );
00774 pascal int     listen( SOCKET s, int backlog );
00775 pascal int     recv( SOCKET s, char *buf, int len, int flags );
00776 pascal int     recvfrom( SOCKET s, char *buf, int len, int flags, struct sockaddr *from, int *fromlen );
00777 pascal int     select( int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout );
00778 pascal int     send( SOCKET s, char *buf, int len, int flags );
00779 pascal int     sendto( SOCKET s, char *buf, int len, int flags, struct sockaddr *to, int tolen );
00780 pascal int     setsockopt( SOCKET s, int level, int optname, char *optval, int optlen );
00781 pasc