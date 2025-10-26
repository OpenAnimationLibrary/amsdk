al int     shutdown( SOCKET s, int how );
00782 pascal SOCKET  socket( int af, int type, int protocol );
00783 
00784 /* Database function prototypes */
00785 
00786 pascal struct hostent *    gethostbyaddr( char *addr, int len, int type );
00787 pascal struct hostent *    gethostbyname( char *name );
00788 pascal int              gethostname( char *name, int namelen );
00789 pascal struct servent *    getservbyport( int port, char *proto );
00790 pascal struct servent *    getservbyname( char *name, char *proto );
00791 pascal struct protoent *   getprotobynumber( int proto );
00792 pascal struct protoent *   getprotobyname( char *name );
00793 
00794 /* Microsoft Windows Extension function prototypes */
00795 
00796 pascal int WSAStartup( u_short wVersionRequired, LPWSADATA lpWSAData );
00797 pascal int WSACleanup( void );
00798 
00799 pascal void WSASetLastError( int iError );
00800 pascal int WSAGetLastError( void );
00801 
00802 pascal int WSAIsBlocking( void );
00803 pascal int WSAUnhookBlockingHook( void );
00804 
00805 pascal WSABlockingHookUPP WSASetBlockingHook( WSABlockingHookUPP pprocHook );
00806 pascal int WSACancelBlockingCall( void );
00807 
00808 pascal HANDLE WSAAsyncGetServByName( NMMessageHandler hWnd, u_int wMsg, char *name, char *proto, char *buf, int buflen );
00809 pascal HANDLE WSAAsyncGetServByPort( NMMessageHandler hWnd, u_int wMsg, int port, char *proto, char *buf, int buflen );
00810 pascal HANDLE WSAAsyncGetProtoByName( NMMessageHandler hWnd, u_int wMsg, char *name, char *buf, int buflen );
00811 pascal HANDLE WSAAsyncGetProtoByNumber( NMMessageHandler hWnd, u_int wMsg, int number, char *buf, int buflen );
00812 pascal HANDLE WSAAsyncGetHostByName( NMMessageHandler hWnd, u_int wMsg, char *name, char *buf, int buflen );
00813 pascal HANDLE WSAAsyncGetHostByAddr( NMMessageHandler hWnd, u_int wMsg, char *addr, int len, int type, char *buf, int buflen );
00814 
00815 pascal int WSACancelAsyncRequest( HANDLE lAsyncTaskID );
00816 
00817 pascal int WSAAsyncSelect( SOCKET s, NMMessageHandler hWnd, u_int wMsg, long lEvent );
00818 
00819 #ifdef __cplusplus
00820 }
00821 #endif
00822 
00823 /* Microsoft Windows Extended data types */
00824 typedef struct sockaddr SOCKADDR;
00825 typedef struct sockaddr *PSOCKADDR;
00826 typedef struct sockaddr *LPSOCKADDR;
00827 
00828 typedef struct sockaddr_in SOCKADDR_IN;
00829 typedef struct sockaddr_in *PSOCKADDR_IN;
00830 typedef struct sockaddr_in *LPSOCKADDR_IN;
00831 
00832 typedef struct linger LINGER;
00833 typedef struct linger *PLINGER;
00834 typedef struct linger *LPLINGER;
00835 
00836 typedef struct in_addr IN_ADDR;
00837 typedef struct in_addr *PIN_ADDR;
00838 typedef struct in_addr *LPIN_ADDR;
00839 
00840 typedef struct fd_set FD_SET;
00841 typedef struct fd_set *PFD_SET;
00842 typedef struct fd_set *LPFD_SET;
00843 
00844 typedef struct hostent HOSTENT;
00845 typedef struct hostent *PHOSTENT;
00846 typedef struct hostent *LPHOSTENT;
00847 
00848 typedef struct servent SERVENT;
00849 typedef struct servent *PSERVENT;
00850 typedef struct servent *LPSERVENT;
00851 
00852 typedef struct protoent PROTOENT;
00853 typedef struct protoent *PPROTOENT;
00854 typedef struct protoent *LPPROTOENT;
00855 
00856 typedef struct timeval TIMEVAL;
00857 typedef struct timeval *PTIMEVAL;
00858 typedef struct timeval *LPTIMEVAL;
00859 
00860 /*
00861  * Windows message parameter composition and decomposition
00862  * macros.
00863  *
00864  * WSAMAKEASYNCREPLY is intended for use by the Windows Sockets implementation
00865  * when constructing the response to a WSAAsyncGetXByY() routine.
00866  */
00867 #define WSAMAKEASYNCREPLY(buflen,error)   MAKELONG(buflen,error)
00868 /*
00869  * WSAMAKESELECTREPLY is intended for use by the Windows Sockets implementation
00870  * when constructing the response to WSAAsyncSelect().
00871  */
00872 #define WSAMAKESELECTREPLY(event,error)   MAKELONG(event,error)
00873 /*
00874  * WSAGETASYNCBUFLEN is intended for use by the Windows Sockets application
00875  * to extract the buffer length from the lParam in the response
00876  * to a WSAGetXByY().
00877  */
00878 #define WSAGETASYNCBUFLEN(luParam)     LOWORD(luParam)
00879 /*
00880  * WSAGETASYNCERROR is intended for use by the Windows Sockets application
00881  * to extract the error code from the lParam in the response
00882  * to a WSAGetXByY().
00883  */
00884 #define WSAGETASYNCERROR(luParam)      HIWORD(luParam)
00885 /*
00886  * WSAGETSELECTEVENT is intended for use by the Windows Sockets application
00887  * to extract the event code from the lParam in the response
00888  * to a WSAAsyncSelect().
00889  */
00890 #define WSAGETSELECTEVENT(luParam)     LOWORD(luParam)
00891 /*
00892  * WSAGETSELECTERROR is intended for use by the Windows Sockets application
00893  * to extract the error code from the lParam in the response
00894  * to a WSAAsyncSelect().
00895  */
00896 #define WSAGETSELECTERROR(luParam)     HIWORD(luParam)
00897 
00898 #endif  /* _WINSOCKAPI_ */
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
