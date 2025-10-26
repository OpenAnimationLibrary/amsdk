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

# MacHASP.h

[Go to the documentation of this file.](MacHASP_8h.md)

<div class="fragment">

``` fragment
00001 /******************************************************
00002 *
00003 *  HaspCall.h
00004 *
00005 *  Defines the Interface for C programs to the MacHasp system.
00006 *
00007 *  Copyright Aladdin Knowledge Systems
00008 *
00009 *         
00010 ******************************************************/
00011 
00012 #ifndef  MacHASPCH_def
00013 #define  MacHASPCH_def 1
00014 
00015 
00016 #include "MacHaspErrors.h"
00017 
00018 
00019 /*
00020 *  Valid MacHasp services.
00021 */
00022 #define     SRV_ISHASP              1  /* how many MacHasp on this Mac */
00023 #define     SRV_GET_CODE            2  /* get return code from a MacHasp */
00024 #define     SRV_GET_HASP_TYPE    3  /* get the MacHasp type */
00025 #define  SRV_READ_MEMO           4  /* read a memory byte */
00026 #define  SRV_WRITE_MEMO       5  /* write a memory byte */
00027 #define     SRV_READ_BLOCK       6  /* read memory block */
00028 #define     SRV_WRITE_BLOCK         7  /* write memory block */
00029 #define     SRV_READ_RAM            8  /* read RAM variable */
00030 #define     SRV_WRITE_RAM           9  /* write RAM variable */
00031 #define     SRV_READ_PRIVILEGE   10 /* read privileged area */
00032 #define     SRV_WRITE_PRIVILEGE  11 /* write privileged area */
00033 #define     SRV_MAXNET_STATIONS  12 /* get maximum netHASP stations */
00034 
00035 
00036 /*
00037 *  Valid MacNetHasp services.
00038 */
00039 #define     SRV_NET_LOGIN                       41 /* NetHASP LOGIN*/
00040 #define     SRV_NET_LOGOUT                   42 /* NetHASP LOGOUT*/
00041 #define     SRV_NET_ExLOGOUT                 43 /* NetHASP External LOGOUT*/
00042 #define     SRV_NET_GET_CODE                 44 /* get return code from a MacNetHasp */
00043 #define     SRV_NET_GET_TYPE                 45 /* get MacNetHasp type */
00044 #define  SRV_NET_READ_MEMO                46 /* read a memory byte */
00045 #define  SRV_NET_WRITE_MEMO               47 /* write a memory byte */
00046 #define     SRV_NET_READ_BLOCK               48 /* read memory block */
00047 #define     SRV_NET_WRITE_BLOCK              49 /* write memory block */
00048 #define     SRV_NET_READ_RAM                 50 /* read RAM variable */
00049 #define     SRV_NET_WRITE_RAM                51 /* write RAM variable */
00050 #define     SRV_NET_READ_PRIVILEGE        52 /* read privileged area */
00051 #define     SRV_NET_WRITE_PRIVILEGE       53 /* write privileged area */
00052 #define     SRV_NET_GET_LOGGEDIN          54 /* get number of logged in with the ProgNum and passwords stations */
00053 #define     SRV_NET_GET_ALL_LOGGEDIN      55 /* get number of all logged in programs */
00054 #define     SRV_NET_GET_PROG_INFO            56 /* get network addres of an logged in station */
00055 #define     SRV_NET_SET_IDLE_LIMIT        57 /* Set IdleLimit in minutes for the program */
00056 #define     SRV_NET_CHECK_COMPLETE        60 /* get data after completion of the asynchronies call */
00057 #define     SRV_NET_SET_SERVER_ADDRESS 61 /* sets server's address 
00058                                                                   ServerNet=InputPrm2;
00059                                                                   ServerNode=InputPrm1;
00060                                                                   ServerSocket=MemoAddr;
00061                                                              */
00062 #define     SRV_NET_GET_MONITOR_INFO         62 /* gets information for Monitor */
00063 #define     SRV_NET_GET_MORE_MONITOR_INFO 63 /* gets information for Monitor */
00064 #define     SRV_RELEASE_MONITOR_INFO         64 /* frees monitor info before removing the server */
00065 
00066 #define     SRV_CHECK_FOR_COMPLETE        13       /* Check for completion of pervious asincronic call */
00067 #define     HASP_NOWAIT_BIT               0x80000000L /* Last Service bit must be set for asinc. call */
00068 #define     HASP_FROM_DT_BIT           0x40000000L /* This Service bit must be set for NetMacHASP Calls from Defered Task */
00069 #define     ENV_LOGIN_BIT                 0x00008000L
00070 
00071 
00072 /*
00073 *  RUS services.
00074 */
00075 #define     SRV_RUS_UPDATE                101   /* Update the MacHASP memory */
00076 #define     SRV_RUS_CREATE_PASSW       102 /* Create RUS Passwords */
00077 #define     SRV_RUS_GET_ID                103 /* Get RUS Session ID */
00078 
00079 /*
00080 * Special services.
00081 * For Aladdin's internal usage only!
00082 * Using these services may lead to crashes and
00083 * bizzar behaviour of the system.
00084 */
00085 #define SRV_HASP_USB_RESET             200
00086  
00087 
00088 
00089 /*
00090 * calling function prototype
00091 */
00092 
00093 #ifdef __cplusplus
00094    extern "C" {
00095 #endif
00096 
00097 pascal long MacHasp(long Service, long HaspNum,
00098                long InputPrm1, long InputPrm2,
00099                long MemoAddr, long MemoData, Ptr MemoBuff,
00100                long *ReturnPrm1, long *ReturnPrm2, long *Status);
00101           
00102 #ifdef __cplusplus
00103    }
00104 #endif
00105 
00106 
00107 /*
00108 * Several parameters have different meaning depending on the Service:
00109 *
00110 * InputPrm1,
00111 * InputPrm2 on GET_CODE are seed codes which can be set by the caller
00112 *              to any value in the range (0..16777215)
00113 *         on READ/WRITE MEMO, the caller must set them to the
00114 *              correct passwords (read/write/write privileged area).
00115 * MemoData on WRITE_MEMO: data to be written.
00116 *          on BLOCK services: length of the memo buffer
00117 * ReturnPrm1 on IS_HASP: Number of MacHasps connected
00118 *            on GET_CODE: return code for the first Seed Code
00119 *            on READ_MEMO: value of the memory byte read.
00120 *          on GET_HASP_TYPE: type of the MacHasp.
00121 * ReturnPrm2 on GET_CODE: return code for the second seed code.
00122 *          on GET_HASP_TYPE: size of the MacHasp memory.
00123 *
00124 * Other parameters are used only by specific Services
00125 */ 
00126 
00127 
00128 /*
00129 * Privileged area limits
00130 */
00131 #define        PRIVILEGED_LOW       0
00132 #define        PRIVILEGED_HIGH         9
00133 #define        PRIVILEGED_SIZE         PRIVILEGED_HIGH - PRIVILEGED_LOW + 1 
00134 
00135 /*
00136 * max. number of MacHasps which can be connected to the 
00137 * same computer.
00138 */
00139 #define MAX_ADB      15
00140 #define MAX_USB      127
00141 
00142 #define  MAX_HASP MAX_ADB + MAX_USB
00143 
00144 /*
00145 *  Net-MacHASP - Unlimited Idle Time Set
00146 */
00147 #define  NETHASP_UNLIMITED_IDLE_TIME         0xFFFF      
00148 
00149 /********************************************************
00150 *
00151 * Hasp resource definitions.
00152 *
00153 ********************************************************/
00154 
00155 #define HASP_RESOURCE_NAME "\pHaspResource"  /* filename of the HASP resource */
00156 #define  HASP_RESOURCE_TYPE   'HASP'         /* Type of the HASP resource */
00157 #define  HASP_RESOURCE_ID  128            /* ID of the HASP resource */
00158  
00159 
00160 /*******************************************************
00161 *
00162 * Hasp resource definitions.
00163 *
00164 ********************************************************/
00165 
00166 #define NETH_RESOURCE_NAME "\pNetHaspResource"  /* filename of the NetHASP resource */
00167 #define  NETH_RESOURCE_TYPE   'NETH'         /* Type of the NetHASP resource */
00168 #define  NETH_RESOURCE_ID  128            /* ID of the NetHASP resource */
00169  
00170 
00171 /*
00172 * Declare a pointer to MacHasp(). from this file the call will be made
00173 * through this pointer to the beginning of the resource, which should
00174 * contain the MacHasp body itself.
00175 */
00176  
00177 #ifdef __cplusplus
00178    extern "C" {
00179 #endif
00180 
00181  typedef pascal long (*MacHaspPtr) (long,long,long,long,long,long,
00182                      Ptr, long *,long *,long *);
00183 
00184 
00185 /*
00186 * this function loads the HASP resource (opens resource file if need)
00187 * and stores its address in a MacHaspPtr variable. 
00188 * call it before any calls to MacHasp.
00189 * You call this function only once, unless you call MacHaspClose.
00190 */
00191 pascal short MacHaspInit(void);
00192 
00193 /*
00194 * This function releases the HASP resource from memory.
00195 */
00196 pascal short MacHaspClose(void);
00197 
00198 
00199 /*
00200 * this function loads the NetHASP resource (opens resource file if need)
00201 * and stores its address in a MacHaspPtr variable. 
00202 * call it before any calls to MacHasp.
00203 * You call this function only once, unless you call MacHaspClose.
00204 */
00205 pascal short NetHaspInit(void);
00206 
00207 
00208 /*
00209 * This function releases the HASP resource from memory.
00210 */
00211 pascal short NetHaspClose(void);
00212 
00213 /* 
00214 *  NetHASP Loader function prototype
00215 *
00216 *     pascal   short NetHASPLoad( long *ErrorCode2 , short SendRecieveTime); // returns ErrorCode1
00217 */
00218    
00219 typedef  pascal short (*NHLoader)( long *, short, Handle );
00220  
00221 
00222 
00223 #ifdef __cplusplus
00224    }
00225 #endif
00226 
00227 #define  FAS_UNLIMITED_RT  0xFFFF
00228    
00229 
00230 #endif  // #ifndef   MacHASPCH_def
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
