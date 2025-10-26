405    m_alpha /= factor;
00406    return *this;
00407 }
00408 
00409 inline YAHalf YAHalf::operator + ( const YAHalf &other )
00410 {
00411    m_luminance += other.m_luminance;
00412    m_alpha += other.m_alpha;
00413    return YAHalf(*this);
00414 }
00415 
00416 inline int YAHalf::operator == ( const YAHalf &other ) const
00417 {
00418    if (m_luminance == other.m_luminance && m_alpha == other.m_alpha)
00419       return TRUE;
00420    return FALSE;
00421 }
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
