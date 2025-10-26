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

# xMac.h

[Go to the documentation of this file.](xMac_8h.md)

<div class="fragment">

``` fragment
00001 /* WP  12/15/97  \will5\include\3rdParty\xMac.h
00002 * @doc
00003 * $Workfile: xMac.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 8 $ $Author: Yury $ $Date: 6/22/97 10:30p $
00013 ************************************************************************/
00014 #ifndef __XMAC_H
00015 #define __XMAC_H
00016 
00017 #ifdef _XMAC_LIB
00018 #define XMAC_API
00019 #define XMAC_CLASS   
00020 #else
00021 #define XMAC_API  AFX_EXT_API
00022 #define XMAC_CLASS   AFX_EXT_CLASS
00023 #endif
00024 
00025 #define _CPX_LIB
00026 // These are just some usefull definitions. Maybe move them sowere else ???
00027 #define FREE_MEMORY(mem)      if(mem) { free(mem); mem = 0; }
00028 #define DELETE_OBJECT(obj)    if(obj) { delete obj; obj = 0; }
00029 #define DELETE_ARRAY(obj)     if(obj) { delete [] obj; obj = 0; }
00030 #define DELETE_GDIOBJ(obj)    if(obj) { DeleteObject(obj); obj = 0; }
00031 
00032 // just in case no one else has included the windows core includes
00033 #include <afxwin.h>         // MFC core and standard components
00034 #include <afxext.h>         // MFC extensions
00035 
00036 #ifdef _OS9
00037 // This is like Windows.h : define the macintosh world.
00038 #include <MsvcMac.h>
00039 #include <macname1.h>
00040 #pragma warning(disable:4121) // disable C4121 warning
00041 //#include  <macos\types.h>
00042 #include <macos\files.h>   // moved by KB
00043 #include <macos\errors.h>  // moved by KB
00044 //#include  <macos\memory.h>
00045 //#include  <macos\controls.h>
00046 #include <macos\resource.h>
00047 //#include  <macos\lowmem.h>
00048 //#include  <macos\adsp.h>
00049 //#include  <macos\adspsecu.h>
00050 #include <macos\aeobject.h>
00051 //#include  <macos\aepackob.h>
00052 //#include  <macos\aeregist.h>
00053 //#include  <macos\aeuserte.h>
00054 //#include  <macos\aiff.h>
00055 #include <macos\aliases.h>
00056 //#include  <macos\appleeve.h>
00057 //#include  <macos\applegui.h>
00058 //#include  <macos\applescr.h>
00059 #include <macos\appletal.h>
00060 //#include  <macos\asdebugg.h>
00061 //#include  <macos\asregist.h>
00062 //#include  <macos\printing.h>
00063 //#include  <macos\balloons.h>
00064 //#include  <macos\codefrag.h>
00065 //#include  <macos\collecti.h>
00066 //#include  <macos\commreso.h>
00067 //#include  <macos\componen.h>
00068 //#include  <macos\conmacro.h>
00069 //#include  <macos\connecti.h>
00070 //#include  <macos\connectt.h>
00071 //#include  <macos\ctlstrip.h>
00072 //#include  <macos\crmseria.h>
00073 //#include  <macos\ctbutili.h>
00074 //#include  <macos\cursorde.h>
00075 //#include  <macos\database.h>
00076 //#include  <macos\desk.h>
00077 //#include  <macos\deskbus.h>
00078 //#include  <macos\devices.h>
00079 #include <macos\dialogs.h>
00080 //#include  <macos\dictiona.h>
00081 //#include  <macos\digitals.h>
00082 //#include  <macos\diskinit.h>
00083 //#include  <macos\disks.h>
00084 //#include  <macos\displays.h>
00085 //#include  <macos\drag.h>
00086 //#include  <macos\editions.h>
00087 //#include  <macos\enet.h>
00088 //#include  <macos\eppc.h>
00089 //#include  <macos\events.h>
00090 //#include  <macos\fenv.h>
00091 //#include  <macos\filetran.h>
00092 //#include  <macos\filetrat.h>
00093 //#include  <macos\filetype.h>
00094 //#include  <macos\finder.h>
00095 //#include  <macos\fixmath.h>
00096 #include <macos\folders.h>
00097 //#include  <macos\fonts.h>
00098 //#include  <macos\fragload.h>
00099 //#include  <macos\fsm.h>
00100 //#include  <macos\gestalt.h>
00101 //#include  <macos\gestalte.h>
00102 //#include  <macos\icons.h>
00103 //#include  <macos\imagecod.h>
00104 //#include  <macos\imagecom.h>
00105 //#include  <macos\intlreso.h>
00106 //#include  <macos\language.h>
00107 //#include  <macos\lists.h>
00108 //#include  <macos\machinee.h>
00109 //#include  <macos\mactcp.h>
00110 //#include  <macos\mediahan.h>
00111 //#include  <macos\menus.h>
00112 //#include  <macos\midi.h>
00113 //#include  <macos\mixedmod.h>
00114 //#include  <macos\movies.h>
00115 //#include  <macos\moviesfo.h>
00116 //#include  <macos\notifica.h>
00117 //#include  <macos\oce.h>
00118 //#include  <macos\oceauthd.h>
00119 //#include  <macos\oceerror.h>
00120 //#include  <macos\ocemail.h>
00121 //#include  <macos\ocemessa.h>
00122 //#include  <macos\ocestddi.h>
00123 //#include  <macos\ocestdml.h>
00124 //#include  <macos\ocetempl.h>
00125 //#include  <macos\osa.h>
00126 //#include  <macos\osacomp.h>
00127 //#include  <macos\osagener.h>
00128 //#include  <macos\osevents.h>
00129 //#include  <macos\osutils.h>
00130 //#include  <macos\packages.h>
00131 //#include  <macos\palettes.h>
00132 //#include  <macos\pictutil.h>
00133 #include <macos\plstring.h>
00134 //#include  <macos\power.h>
00135 //#include  <macos\ppctoolb.h>
00136 //#include  <macos\processe.h>
00137 //#include  <macos\qdoffscr.h>
00138 //#include  <macos\quickdra.h>
00139 //#include  <macos\qdtext.h>
00140 //#include  <macos\quicktim.h>
00141 //#include  <macos\retrace.h>
00142 //#include  <macos\romdefs.h>
00143 //#include  <macos\rtlib.h>
00144 //#include  <macos\scalerty.h>
00145 //#include  <macos\scrap.h>
00146 //#include  <macos\script.h>
00147 //#include  <macos\scsi.h>
00148 //#include  <macos\segload.h>
00149 //#include  <macos\serial.h>
00150 //#include  <macos\sfnttype.h>
00151 //#include  <macos\shutdown.h>
00152 //#include  <macos\slots.h>
00153 //#include  <macos\sound.h>
00154 //#include  <macos\soundcom.h>
00155 //#include  <macos\soundinp.h>
00156 //#include  <macos\speech.h>
00157 #include <macos\standard.h>
00158 //#include  <macos\start.h>
00159 //#include  <macos\terminal.h>
00160 //#include  <macos\terminat.h>
00161 //#include  <macos\textedit.h>
00162 //#include  <macos\textserv.h>
00163 #include <macos\textutil.h>
00164 //#include  <macos\threads.h>
00165 //#include  <macos\timer.h>
00166 //#include  <macos\toolutil.h>
00167 //#include  <macos\translat.h>
00168 //#include  <macos\translae.h>
00169 //#include  <macos\traps.h>
00170 //#include  <macos\tsmte.h>
00171 //#include  <macos\video.h>
00172 //#include  <macos\worldscr.h>
00173 
00174 // Menus.h defines this as a macro. It will conflict with most
00175 // of the world.
00176 #undef GetItem
00177 #undef SetItem
00178 
00179 #pragma warning(default:4121) // renable C4121 warning
00180 #include <macname2.h>
00181 
00182 #endif                   // end of ifdef _OS9
00183 
00184 #include <mmsystem.h>
00185 #include <vfw.h>
00186 
00187 #ifndef _INC_IO
00188 #include <io.h>   
00189 #endif
00190 
00191 #ifndef _INC_DIRECT
00192 #include <direct.h>
00193 #endif
00194 
00195 #ifndef __XMFCEXT_H
00196 #include <xMfcExt.h>
00197 #endif
00198 
00199 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
