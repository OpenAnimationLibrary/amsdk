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

# HashArra.h

[Go to the documentation of this file.](HashArra_8h.md)

<div class="fragment">

``` fragment
00001 // BC  11/4/2004  \BobL115\Include\HashArra.h
00002 
00003 #ifndef __HASHARRA_H
00004 #define __HASHARRA_H
00005 
00006 #ifndef __ALLOCATE_H
00007 #include "Allocate.h"
00008 #endif
00009 #if defined(_MSC_VER) || defined(_OSX)
00010 #include <new.h>
00011 #else
00012 #ifndef __PLACEMENT_NEW_INLINE
00013 #define __PLACEMENT_NEW_INLINE
00014 inline void *__cdecl operator new(size_t, void *_P)
00015         {return (_P); }
00016 #if     _MSC_VER >= 1200
00017 inline void __cdecl operator delete(void *, void *)
00018    {return; }
00019 #endif
00020 #endif
00021 #endif
00022 
00023 template<class TYPE>
00024 inline void AFXAPI HashConstructElements(TYPE* pElements, int nCount)
00025 {
00026    ASSERT(nCount == 0 ||
00027       AfxIsValidAddress(pElements, nCount * sizeof(TYPE)));
00028 
00029    // first do bit-wise zero initialization
00030    memset((void*)pElements, 0, nCount * sizeof(TYPE));
00031 
00032    // then call the constructor(s)
00033    for (; nCount--; pElements++)
00034       ::new((void*)pElements) TYPE;
00035 }
00036 
00037 template<class TYPE>
00038 inline void AFXAPI HashDestructElements(TYPE* pElements, int nCount)
00039 {
00040    ASSERT(nCount == 0 ||
00041       AfxIsValidAddress(pElements, nCount * sizeof(TYPE)));
00042 
00043    // call the destructor(s)
00044    for (; nCount--; pElements++)
00045       pElements->~TYPE();
00046 }
00047 
00048 template<class TYPE>
00049 inline void ConstructTheElements(TYPE* pElements, int count)
00050 {
00051    memset((void*)pElements, 0, count * sizeof(TYPE));
00052 
00053    for (; count--; pElements++)
00054       ::new((void*)pElements) TYPE;
00055 }
00056 
00057 template<class TYPE>
00058 inline void DestructTheElements(TYPE* pElements, int count)
00059 {
00060    for (; count--; pElements++)
00061       pElements->~TYPE();
00062 }
00063 
00064 template<class TYPE, class ARG_TYPE>
00065 class HashArray 
00066 {
00067 public:
00068    HashArray();
00069 
00070    int GetSize() const;
00071    int GetUpperBound() const;
00072    void SetSize(int newsize, int growby = -1);
00073 
00074    void FreeExtra();
00075    void RemoveAll();
00076 
00077    TYPE GetAt(int index) const;
00078    TYPE& ElementAt(int index);
00079    void SetAt(int index, ARG_TYPE newElement);
00080    void InsertAt(int nIndex, ARG_TYPE newElement, int nCount=1 );
00081    void RemoveAt(int index, int count=1);
00082    
00083    TYPE  operator [] ( int index ) const { return m_data[index]; }
00084    TYPE &operator [] (int index) { return m_data[index]; }
00085 
00086    TYPE* GetArray();
00087 
00088    void SetAtGrow(int index, ARG_TYPE newElement);
00089    int Add(ARG_TYPE newElement);
00090    void Push(ARG_TYPE newElement);
00091    TYPE Pop();
00092    TYPE GetPushed() const;
00093    void SetGranularity(int granularity) { m_growby = granularity; }
00094 
00095 protected:
00096    TYPE* m_data;
00097    int m_size;
00098    int m_maxsize;
00099    int m_growby;
00100 
00101 public:
00102    ~HashArray();
00103 };
00104 
00105 template<class TYPE, class ARG_TYPE>
00106 inline int HashArray<TYPE, ARG_TYPE>::GetSize() const { return m_size; }
00107    
00108 template<class TYPE, class ARG_TYPE>
00109 inline int HashArray<TYPE, ARG_TYPE>::GetUpperBound() const { return m_size-1; }
00110    
00111 template<class TYPE, class ARG_TYPE>
00112 inline void HashArray<TYPE, ARG_TYPE>::RemoveAll() { SetSize(0, -1); }
00113    
00114 template<class TYPE, class ARG_TYPE>
00115 inline TYPE HashArray<TYPE, ARG_TYPE>::GetAt(int index) const { return m_data[index]; }
00116     
00117 template<class TYPE, class ARG_TYPE>
00118 inline TYPE& HashArray<TYPE, ARG_TYPE>::ElementAt(int index) { return m_data[index]; }
00119     
00120 template<class TYPE, class ARG_TYPE>
00121 inline void HashArray<TYPE, ARG_TYPE>::SetAt(int index, ARG_TYPE newElement) { m_data[index] = newElement; }
00122    
00123 template<class TYPE, class ARG_TYPE>
00124 inline TYPE* HashArray<TYPE, ARG_TYPE>::GetArray() { return (TYPE*)m_data; }
00125    
00126 template<class TYPE, class ARG_TYPE>
00127 inline int HashArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
00128 { 
00129    int index = m_size;
00130    SetAtGrow(index, newElement);
00131    return index; 
00132 }
00133 
00134 template<class TYPE, class ARG_TYPE>
00135 HashArray<TYPE, ARG_TYPE>::HashArray()
00136 {
00137    m_data = NULL;
00138    m_size = m_maxsize = m_growby = 0;
00139 }
00140 
00141 template<class TYPE, class ARG_TYPE>
00142 HashArray<TYPE, ARG_TYPE>::~HashArray()
00143 {
00144    if (m_data != NULL) {
00145       DestructTheElements(m_data, m_size);
00146       FreeExt( m_data );
00147    }
00148 }
00149 
00150 template<class TYPE, class ARG_TYPE>
00151 void HashArray<TYPE, ARG_TYPE>::SetSize(int newsize, int growby)
00152 {
00153    if (growby != -1)
00154       m_growby = growby;
00155 
00156    if (newsize == 0) {
00157       if (m_data != NULL) {
00158          DestructTheElements(m_data, m_size);
00159          FreeExt( m_data );
00160          m_data = NULL;
00161       }
00162       m_size = m_maxsize = 0;
00163    }
00164    else if (m_data == NULL) {
00165       m_data = (TYPE*) AllocExt( newsize * sizeof(TYPE));
00166       ConstructTheElements(m_data, newsize);
00167       m_size = m_maxsize = newsize;
00168    }
00169    else if (newsize <= m_maxsize) {
00170       if (newsize > m_size) {
00171          ConstructTheElements(&m_data[m_size], newsize-m_size);
00172       }
00173       else if (m_size > newsize) {
00174          DestructTheElements(&m_data[newsize], m_size-newsize);
00175       }
00176       m_size = newsize;
00177    }
00178    else  {
00179       int growby = m_growby;
00180       if (growby == 0) {
00181          growby = m_size / 8;
00182          growby = (growby < 4) ? 4 : ((growby > 1024) ? 1024 : growby);
00183       }
00184       int newmax;
00185       if (newsize < m_maxsize + growby)
00186          newmax = m_maxsize + growby;
00187       else
00188          newmax = newsize;
00189 
00190       TYPE* newdata = (TYPE*) AllocExt( newmax * sizeof(TYPE));
00191 
00192       memcpy(newdata, m_data, m_size * sizeof(TYPE));
00193 
00194       ConstructTheElements(&newdata[m_size], newsize-m_size);
00195 
00196       FreeExt( m_data );
00197       m_data = newdata;
00198       m_size = newsize;
00199       m_maxsize = newmax;
00200    }
00201 }
00202 
00203 template<class TYPE, class ARG_TYPE>
00204 void HashArray<TYPE, ARG_TYPE>::FreeExtra()
00205 {
00206    if (m_size != m_maxsize) {
00207       TYPE* newdata = NULL;
00208       if (m_size != 0)  {
00209          newdata = (TYPE*) AllocExt( m_size * sizeof(TYPE));
00210          memcpy(newdata, m_data, m_size * sizeof(TYPE));
00211       }
00212 
00213       FreeExt( m_data );
00214       m_data = newdata;
00215       m_maxsize = m_size;
00216    }
00217 }
00218 
00219 template<class TYPE, class ARG_TYPE>
00220 void HashArray<TYPE, ARG_TYPE>::SetAtGrow(int index, ARG_TYPE newElement)
00221 {
00222    if (index >= m_size)
00223       SetSize(index+1, -1);
00224    m_data[index] = newElement;
00225 }
00226 
00227 template<class TYPE, class ARG_TYPE>
00228 void HashArray<TYPE, ARG_TYPE>::InsertAt(int nIndex, ARG_TYPE newElement, int nCount /*=1*/)
00229 {
00230    // YP Comeback: "this" is not a CObject so can not be used with ASSERT_VALID
00231 // ASSERT_VALID(this);
00232    ASSERT(nIndex >= 0);    // will expand to meet need
00233    ASSERT(nCount > 0);     // zero or negative size not allowed
00234 
00235    if (nIndex >= m_size)
00236    {
00237       // adding after the end of the array
00238       SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
00239    }
00240    else
00241    {
00242       // inserting in the middle of the array
00243       int nOldSize = m_size;
00244       SetSize(m_size + nCount, -1);  // grow it to new size
00245       // destroy intial data before copying over it
00246 #if (_MFC_VER > 0x0420)
00247       HashDestructElements<TYPE>(&m_data[nOldSize], nCount);
00248 #else   
00249       HashDestructElements(&m_data[nOldSize], nCount);
00250 #endif   
00251       // shift old data up to fill gap
00252       memmove(&m_data[nIndex+nCount], &m_data[nIndex],
00253          (nOldSize-nIndex) * sizeof(TYPE));
00254 
00255       // re-init slots we copied from
00256 #if (_MFC_VER > 0x0420)
00257       HashConstructElements<TYPE>(&m_data[nIndex], nCount);
00258 #else   
00259       HashConstructElements(&m_data[nIndex], nCount);
00260 #endif   
00261    }
00262 
00263    // insert new value in the gap
00264    ASSERT(nIndex + nCount <= m_size);
00265    while (nCount--)
00266       m_data[nIndex++] = newElement;
00267 }
00268 
00269 template<class TYPE, class ARG_TYPE>
00270 void HashArray<TYPE, ARG_TYPE>::RemoveAt(int index, int count)
00271 {
00272    // just remove a range
00273    int movecount = m_size - (index + count);
00274 
00275 #if (_MFC_VER > 0x0420)
00276    HashDestructElements<TYPE>(&m_data[index], count);
00277 #else   
00278    HashDestructElements(&m_data[index], count);
00279 #endif   
00280    
00281    if (movecount)
00282       memmove(&m_data[index], &m_data[index + count],
00283          movecount * sizeof(TYPE));
00284    m_size -= count;
00285 }
00286 
00287 template<class TYPE, class ARG_TYPE>
00288 inline void HashArray<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
00289 { 
00290    SetAtGrow(m_size, newElement);
00291 }
00292 
00293 template<class TYPE, class ARG_TYPE>
00294 TYPE HashArray<TYPE, ARG_TYPE>::Pop()
00295 {
00296    if (m_size < 1) {
00297       ASSERT(FALSE);
00298       return (TYPE)NULL;
00299    }
00300    TYPE rvalue = m_data[m_size-1];
00301 #if (_MFC_VER > 0x0420)
00302    HashDestructElements<TYPE>(&m_data[m_size-1], 1);
00303 #else   
00304    HashDestructElements(&m_data[m_size-1], 1);
00305 #endif   
00306   
00307    --m_size;
00308    return rvalue;
00309 }
00310 
00311 template<class TYPE, class ARG_TYPE>
00312 inline TYPE HashArray<TYPE, ARG_TYPE>::GetPushed() const { return m_data[m_size-1]; }
00313 
00314 #endif __HASHARRA_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
