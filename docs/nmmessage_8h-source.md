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

# nmmessage.h

[Go to the documentation of this file.](nmmessage_8h.md)

<div class="fragment">

``` fragment
00001 /* Copyright (c) 1995-1997, Altura Software, Inc. All rights reserved.  */
00002 
00003 #if !defined( _NMMESSAGE_H_ )
00004 #define _NMMESSAGE_H_
00005 
00006 #if !defined( __TYPES__ )
00007 #include <sys/Types.h>
00008 #endif
00009 
00010 #if !defined ( __MIXEDMODE__ )
00011 #include <MixedMode.h>
00012 #endif
00013 
00014 typedef unsigned long NMMessageHandler;
00015 
00016 #define NM_INVALID_HANDLER (NMMessageHandler)(0)
00017 
00018 typedef pascal unsigned long (*NMMessageCallbackProcPtr)( NMMessageHandler h, unsigned int msg, unsigned long wParam, unsigned long lParam );
00019 
00020 enum
00021 {
00022    uppNMMessageCallbackProcInfo = kPascalStackBased
00023       | RESULT_SIZE( SIZE_CODE( sizeof( unsigned long ) ) )
00024       | STACK_ROUTINE_PARAMETER( 1, SIZE_CODE( sizeof( NMMessageHandler ) ) )
00025       | STACK_ROUTINE_PARAMETER( 2, SIZE_CODE( sizeof( unsigned int ) ) )
00026       | STACK_ROUTINE_PARAMETER( 3, SIZE_CODE( sizeof( unsigned long ) ) )
00027       | STACK_ROUTINE_PARAMETER( 4, SIZE_CODE( sizeof( unsigned long ) ) )
00028 };
00029 
00030 /*
00031 #if GENERATINGCFM
00032 
00033 typedef UniversalProcPtr NMMessageCallbackUPP;
00034 
00035 #define NewNMMessageCallbackProc(userRoutine)   \
00036    (NMMessageCallbackUPP) NewRoutineDescriptor((ProcPtr)(userRoutine), uppNMMessageCallbackProcInfo, GetCurrentArchitecture())
00037 
00038 #define CallNMMessageCallbackProc(userRoutine, h, msg, wParam, lParam)  \
00039    CallUniversalProc((UniversalProcPtr)(userRoutine), uppNMMessageCallbackProcInfo, (h), (msg), (wParam), (lParam))
00040 
00041 #else
00042 */
00043 typedef NMMessageCallbackProcPtr NMMessageCallbackUPP;
00044 
00045 #define NewNMMessageCallbackProc(userRoutine)   \
00046    ((NMMessageCallbackProcPtr) (userRoutine))
00047 
00048 #define CallNMMessageCallbackProc(userRoutine, h, msg, wParam, lParam)  \
00049    (*(userRoutine))((h), (msg), (wParam), (lParam))
00050 
00051 //#endif
00052 
00053 #if defined( __cplusplus )
00054 extern "C" {
00055 #endif
00056 
00057 pascal Boolean NMInitializeMessages( void );
00058 pascal void NMTerminateMessages( void );
00059 
00060 pascal NMMessageHandler NMCreateMessageHandler( NMMessageCallbackUPP callback, void *refcon, unsigned long reserved );
00061 pascal Boolean NMDestroyMessageHandler( NMMessageHandler h, unsigned long flags );
00062 
00063 pascal void *NMGetMessageHandlerRefCon( NMMessageHandler h );
00064 pascal void NMSetMessageHandlerRefCon( NMMessageHandler h, void *refcon );
00065 
00066 pascal Boolean NMPostMessage( NMMessageHandler h, unsigned int msg, unsigned long wParam, unsigned long lParam );
00067 pascal unsigned long NMSendMessage( NMMessageHandler h, unsigned int msg, unsigned long wParam, unsigned long lParam );
00068 
00069 pascal void NMIdle( void );
00070 
00071 #if defined( __cplusplus )
00072 }
00073 #endif
00074 
00075 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
