id SetFormatFromExtension();
00271    ImageIORegistration  *GetPreferedIIO() { return m_iioreg; };
00272    void SetPreferedIIO( ImageIORegistration *iioreg ) { m_iioreg = iioreg; };
00273 };
00274 
00275 
00276 
00277 class RenderFormatTypePropertyInfo : public TypePropertyInfo
00278 {
00279 public:
00280    RenderFormatTypePropertyInfo( UINT index, char *documentation, UINT stringid, TypeInfo typearray[], UINT count, const Label &label, UINT defaultindex=0, DrawWhen drawwhen=DRAWALWAYS, VisibleWhen visiblewhen=VISIBLEALWAYS, UINT type=0 ) :
00281       TypePropertyInfo( index, documentation, stringid, typearray, count, label, defaultindex, drawwhen, visiblewhen, type )
00282    {}   
00283    
00284    virtual BOOL Save( HashStream &hs, BOOL isforcesave );
00285    virtual int  ParseArg( HashStream &hs, HashStream &ms, LONG id );
00286 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
