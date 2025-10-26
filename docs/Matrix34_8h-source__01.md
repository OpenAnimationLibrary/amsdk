00373 }
00374 
00375 inline Matrix34 YRotateRadians( float anglerad )
00376 {
00377    float ca = (float)cos( anglerad ),
00378          sa = (float)sin( anglerad );
00379    return Matrix34( Vector4(  ca, 0.f,  sa, 0.f ),
00380                     Vector4( 0.f, 1.f, 0.f, 0.f ),
00381                     Vector4( -sa, 0.f,  ca, 0.f ));
00382 }
00383 
00384 inline Matrix34 ZRotateRadians( float anglerad )
00385 {
00386    float ca = (float)cos( anglerad ),
00387          sa = (float)sin( anglerad );
00388    return Matrix34( Vector4(  ca, -sa, 0.f, 0.f ),
00389                     Vector4(  sa,  ca, 0.f, 0.f ),
00390                     Vector4( 0.f, 0.f, 1.f, 0.f ));
00391 }
00392 
00393 // ROTATION CONVERSIONS THAT REQUIRE MATRIX34
00394 
00395 inline RotateVector::RotateVector( const Matrix34 &matrix )
00396 {
00397    end = matrix.GetZAxis();
00398    float y = (float)atan2( end.x, end.z );
00399    float x = (float)atan2( -end.y, (float)sqrt(end.x*end.x + end.z*end.z));
00400    Vector rolldir = matrix.GetYAxis();
00401    rolldir *= YXRotateRadians( y, x ).Transpose();
00402    roll = (float)atan2( -rolldir.x, rolldir.y ) * RADIANS;
00403 }
00404 
00405 inline RotateEuler::RotateEuler( const Matrix34 &matrix )
00406 {
00407    Vector end = matrix.GetZAxis();
00408    y = (float)atan2( end.x, end.z );
00409    x = (float)atan2( -end.y, (float)sqrt(end.x*end.x + end.z*end.z));
00410    Vector rolldir = matrix.GetYAxis();
00411    rolldir *= YXRotateRadians( y, x ).Transpose();
00412    z = (float)atan2( -rolldir.x, rolldir.y ) * RADIANS;
00413    x *= RADIANS;
00414    y *= RADIANS;
00415 }
00416 
00417 #ifdef _SIMD
00418 
00419 inline Matrix34::Matrix34( const Matrix34 &m ) : m_smlmatrix34f( m.m_smlmatrix34f )
00420 {
00421 }
00422 
00423 inline Matrix34 Matrix34::operator * ( const Matrix34 &b ) const 
00424 {
00425    Matrix34 result;
00426    result.m_smlmatrix34f.Multiply(m_smlmatrix34f, b.m_smlmatrix34f);
00427    return result;
00428 }
00429 
00430 inline Vector Matrix34::operator * ( const Vector &v ) const
00431 {
00432    Vector result;
00433    m_smlmatrix34f.TransformPoint( v.m_smlvec3f, result.m_smlvec3f );
00434    return result;
00435 }
00436 
00437 inline Matrix34 Matrix34::Transpose( void ) const
00438 {
00439    Matrix34 temp( *this );
00440    temp.m_smlmatrix34f.Transpose();
00441    temp.InitBottomRow();
00442    return temp;
00443 }
00444 
00445 inline Matrix34 Matrix34::Inverse( void ) const
00446 {
00447    Matrix34 result, source=*this;
00448    result.m_smlmatrix34f.Invert(source.m_smlmatrix34f);  // BUG IN SML, SOURCE SHOULD BE DECLARED CONST
00449    result.InitBottomRow();
00450    return result;
00451 }      
00452 
00453 #else   // not SIMD
00454 
00455 inline Matrix34::Matrix34( const Matrix34 &m )
00456 {
00457    *this = m;
00458 }
00459 
00460 inline Vector Matrix34::operator * ( const Vector &vec ) const
00461 {
00462    return Vector( v[0]|vec, v[1]|vec, v[2]|vec );
00463 }
00464 
00465 inline Matrix34 Matrix34::Transpose( void ) const
00466 {
00467    return Matrix34( Vector4( v[0][0], v[1][0], v[2][0], 0.f ),
00468                     Vector4( v[0][1], v[1][1], v[2][1], 0.f ),
00469                     Vector4( v[0][2], v[1][2], v[2][2], 0.f ));
00470 }
00471 
00472 inline Matrix34 Matrix34::Inverse( void ) const
00473 {
00474    Matrix44 a = ToMatrix44( *this );
00475    return ToMatrix34( a.Inverse() );
00476 }      
00477 
00478 #endif  // not SIMD
00479 
00480 #endif  // __MATRIX34_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
