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

# DataValue.h

[Go to the documentation of this file.](DataValue_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  5/25/2004  \DanLP110\Include\DataValue.h
00002 
00003 #define __DATAVALUE_H
00004 
00005 #ifndef __ALLOCATE_H
00006 #include "Allocate.h"
00007 #endif
00008 
00009 class DataValue 
00010 {
00011 public:
00012    BYTE *m_data;
00013    int m_length;
00014    
00015    DataValue()
00016    {
00017       Init();
00018    }
00019    
00020    DataValue(BYTE *data, int length)
00021    {
00022       Init();
00023       SetData(data, length);
00024    }
00025    
00026    DataValue(const DataValue &other)
00027    {
00028       Init();
00029       *this = other;
00030    }
00031    
00032    ~DataValue() 
00033    {
00034       FreeData();
00035    }
00036 
00037    void Init()
00038    {
00039       m_data = NULL;
00040       m_length = 0;
00041    }
00042 
00043    DataValue &operator=( const DataValue &other ) 
00044    {
00045       AllocateData(other.GetLength());
00046       if (m_data)
00047          memcpy(m_data, other.m_data, m_length);
00048       return *this;
00049    }
00050    
00051    int operator == ( const DataValue &other ) const
00052    {
00053       if (GetLength() != other.GetLength())
00054          return 0;
00055          
00056       if (m_length==0)
00057          return 1;
00058 
00059       return (memcmp(m_data, other.m_data, m_length)==0);
00060    }
00061 
00062    void *GetData() { return m_data; }
00063    void SetData(BYTE *data, int length)
00064    {
00065       AllocateData(length);
00066       if (m_data)
00067          memcpy(m_data, data, m_length);
00068    }
00069    int GetLength() const { return m_length; }
00070 
00071    void *AllocateData(int length) { 
00072       if (m_length == length)
00073          return m_data;
00074    
00075       if (m_data)
00076          FreeExt(m_data);
00077    
00078       m_length = 0;   
00079    
00080       if (length)   
00081          m_data = (BYTE *)AllocExt(length);
00082       else 
00083          m_data = NULL;
00084    
00085       if (m_data)   
00086          m_length = length;
00087       
00088       return m_data;
00089    }
00090    
00091    void FreeData()
00092    {
00093       if (m_length) {
00094          FreeExt(m_data);
00095          m_length = 0;
00096          m_data = NULL;
00097       }
00098    }
00099    
00100    BOOL IsEmpty() { return m_length == 0; }
00101 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
