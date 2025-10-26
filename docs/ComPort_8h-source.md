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

# ComPort.h

[Go to the documentation of this file.](ComPort_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: ComPort.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 2 $ $Author: Yury $ $Date: 4/28/97 4:37p $
00013 ************************************************************************/
00014 #ifndef __COMPORT_H
00015 #define __COMPORT_H
00016 
00017 //@class    Communication port class.  This class emulates most window's comport 
00018 // functions for the Mac, and passes them on to Windows on the PC
00019 //@base     public   | CObject.
00020 class XMAC_CLASS CPXComPort : public CObject
00021 {
00022 public:
00023    CPXComPort(int port = 1);
00024    ~CPXComPort();
00025 
00026    BOOL     UserConfigure     (void);
00027    BOOL     Configure         (DCB *dcb);
00028    void     CloseConnection      (void);
00029    BOOL     OpenConnection    (void);
00030 
00031    DWORD    SendBuffer        (LPCTSTR buffer, DWORD size);
00032    DWORD    ReadBuffer        (LPCTSTR buffer, DWORD size);
00033 
00034    //@cmember  Size of the read (incoming) buffer
00035    DWORD m_InSize;
00036    //@cmember  Size of the write (outgoing) buffer
00037    DWORD m_OutSize;
00038    //@cmember  Timeouts.
00039    COMMTIMEOUTS      m_TO;
00040 protected:
00041    unsigned char     m_PortNum;
00042    DCB               m_DCB;
00043    HANDLE            m_hDev;
00044 #ifdef _OS9
00045    short          m_inRefNm;              // input reference number 
00046    short          m_outRefNm;             // output reference number
00047    char *            m_inBuf;
00048    char *            m_outBuf;
00049    OSErr SerialHandShake      (void);
00050    OSErr serialOpen        (unsigned char port, short setup);
00051    OSErr openSerialDriver  (unsigned char port);
00052 #endif
00053 };
00054 
00055 
00056 //@class    Communication port configuration dialog.  Emulates the standard
00057 // Windows port configuration dialog.
00058 //@base     public   | CDialog
00059 class XMAC_CLASS xComConfig : public CDialog
00060 {
00061 public:
00062    xComConfig(DCB *pDCB, CWnd* pParent = NULL);   
00063 
00064    CComboBox   m_cStopBits;
00065    CComboBox   m_cParity;
00066    CComboBox   m_cByteSize;
00067    CComboBox   m_cBaudRate;
00068 
00069    DCB            *m_pDCB;
00070    DCB            m_DCB;
00071 
00072    virtual void DoDataExchange(CDataExchange* pDX);    
00073    virtual void OnOK();
00074    virtual BOOL OnInitDialog();
00075    DECLARE_MESSAGE_MAP()
00076 };
00077 
00078 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
