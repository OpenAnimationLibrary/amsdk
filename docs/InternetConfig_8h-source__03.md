tend to read or read/write.
01112    * Only one writer is allowed per instance.
01113    * Note that this may open resource files that are not closed
01114    * until you call ICEnd.
01115    */
01116 /*
01117  *  ICGetPref()
01118  *  
01119  *  Availability:
01120  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01121  *    CarbonLib:        in CarbonLib 1.0.2 and later
01122  *    Mac OS X:         in version 10.0 or later
01123  */
01124 EXTERN_API( OSStatus )
01125 ICGetPref(
01126   ICInstance         inst,
01127   ConstStr255Param   key,
01128   ICAttr *           attr,
01129   void *             buf,
01130   long *             size)                                    FIVEWORDINLINE(0x2F3C, 0x0010, 0x0006, 0x7000, 0xA82A);
01131 
01132 
01133 /* [c1] [b4] 
01134    * Reads the preference specified by key from the IC database to the
01135    * buffer pointed to by buf and size.
01136    * key must not be the empty string.
01137    * If buf is nil then no data is returned.
01138    * size must be non-negative.
01139    * attr and size are always set on return. On errors (except icTruncatedErr)
01140    * attr is set to ICattr_no_change and size is set to 0.
01141    * size is the actual size of the data.
01142    * attr is set to the attributes associated with the preference.
01143    * If this routine returns icTruncatedErr then the other returned
01144    * values are valid except that only the first size bytes have been
01145    * return. size is adjusted to reflect the true size of the preference.
01146    * Returns icPrefNotFound if there is no preference for the key.
01147    */
01148 /*
01149  *  ICSetPref()
01150  *  
01151  *  Availability:
01152  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01153  *    CarbonLib:        in CarbonLib 1.0.2 and later
01154  *    Mac OS X:         in version 10.0 or later
01155  */
01156 EXTERN_API( OSStatus )
01157 ICSetPref(
01158   ICInstance         inst,
01159   ConstStr255Param   key,
01160   ICAttr             attr,
01161   const void *       buf,
01162   long               size)                                    FIVEWORDINLINE(0x2F3C, 0x0010, 0x0007, 0x7000, 0xA82A);
01163 
01164 
01165 /* [c1] [b4] 
01166    * Sets the preference specified by key from the IC database to the
01167    * value pointed to by buf and size.
01168    * key must not be the empty string.
01169    * size must be non-negative. 
01170    * If buf is nil then the preference value is not set and size is ignored.
01171    * If buf is not nil then the preference value is set to the size
01172    * bytes pointed to by buf.
01173    * If attr is ICattr_no_change then the preference attributes are not set.
01174    * Otherwise the preference attributes are set to attr.
01175    * Returns icPermErr if the previous ICBegin was passed icReadOnlyPerm.
01176    * Returns icPermErr if current attr is locked, new attr is locked and buf <> nil.
01177    */
01178 /*
01179  *  ICFindPrefHandle()
01180  *  
01181  *  Availability:
01182  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01183  *    CarbonLib:        in CarbonLib 1.0.2 and later
01184  *    Mac OS X:         in version 10.0 or later
01185  */
01186 EXTERN_API( OSStatus )
01187 ICFindPrefHandle(
01188   ICInstance         inst,
01189   ConstStr255Param   key,
01190   ICAttr *           attr,
01191   Handle             prefh)                                   FIVEWORDINLINE(0x2F3C, 0x000C, 0x0024, 0x7000, 0xA82A);
01192 
01193 
01194 /* [r2] [c1] [b4] 
01195    * This routine effectively replaces ICGetPrefHandle.
01196    * Reads the preference specified by key from the IC database into
01197    * a handle, prefh.
01198    * key must not be the empty string.
01199    * attr is set to the attributes associated with the preference.
01200    * You must set prefh to a non-nil handle before calling this routine.
01201    * If the preference does not exist, icPrefNotFoundErr is returned.
01202    */
01203 /*
01204  *  ICGetPrefHandle()
01205  *  
01206  *  Availability:
01207  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01208  *    CarbonLib:        in CarbonLib 1.0.2 and later
01209  *    Mac OS X:         in version 10.0 or later
01210  */
01211 EXTERN_API( OSStatus )
01212 ICGetPrefHandle(
01213   ICInstance         inst,
01214   ConstStr255Param   key,
01215   ICAttr *           attr,
01216   Handle *           prefh)                                   FIVEWORDINLINE(0x2F3C, 0x000C, 0x001A, 0x7000, 0xA82A);
01217 
01218 
01219 /* [r1] [c1] [b4] 
01220    * This routine is now obsolete. Use ICFindPrefHandle instead.
01221    * Reads the preference specified by key from the IC database into
01222    * a newly created handle, prefh.
01223    * key must not be the empty string.
01224    * attr is set to the attributes associated with the preference.
01225    * The incoming value of prefh is ignored.
01226    * A new handle is created in the current heap and returned in prefh.
01227    * If the routine returns an error, prefh is set to nil.
01228    * If the preference does not exist, no error is returned and prefh is set
01229    * to an empty handle.
01230    */
01231 /*
01232  *  ICSetPrefHandle()
01233  *  
01234  *  Availability:
01235  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01236  *    CarbonLib:        in CarbonLib 1.0.2 and later
01237  *    Mac OS X:         in version 10.0 or later
01238  */
01239 EXTERN_API( OSStatus )
01240 ICSetPrefHandle(
01241   ICInstance         inst,
01242   ConstStr255Param   key,
01243   ICAttr             attr,
01244   Handle             prefh)                                   FIVEWORDINLINE(0x2F3C, 0x000C, 0x001B, 0x7000, 0xA82A);
01245 
01246 
01247 /* [r1] [c1] [b4] 
01248    * Sets the preference specified by key from the IC database to the
01249    * value contained in prefh.
01250    * key must not be the empty string.
01251    * If prefh is nil then the preference value is not set.
01252    * If buf is not nil then the preference value is set to the data
01253    * contained in it.
01254    * If attr is ICattr_no_change then the preference attributes are not set.
01255    * Otherwise the preference attributes are set to attr.
01256    * Returns icPermErr if the previous ICBegin was passed icReadOnlyPerm.
01257    * Returns icPermErr if current attr is locked, new attr is locked and prefh <> nil.
01258    */
01259 /*
01260  *  ICCountPref()
01261  *  
01262  *  Availability:
01263  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01264  *    CarbonLib:        in CarbonLib 1.0.2 and later
01265  *    Mac OS X:         in version 10.0 or later
01266  */
01267 EXTERN_API( OSStatus )
01268 ICCountPref(
01269   ICInstance   inst,
01270   long *       count)                                         FIVEWORDINLINE(0x2F3C, 0x0004, 0x0008, 0x7000, 0xA82A);
01271 
01272 
01273 /* [c1] [b1] 
01274    * Counts the total number of preferences.
01275    * If the routine returns an error, count is set to 0.
01276    */
01277 /*
01278  *  ICGetIndPref()
01279  *  
01280  *  Availability:
01281  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01282  *    CarbonLib:        in CarbonLib 1.0.2 and later
01283  *    Mac OS X:         in version 10.0 or later
01284  */
01285 EXTERN_API( OSStatus )
01286 ICGetIndPref(
01287   ICInstance   inst,
01288   long         index,
01289   Str255       key)                                           FIVEWORDINLINE(0x2F3C, 0x0008, 0x0009, 0x7000, 0xA82A);
01290 
01291 
01292 /* [c1] [b1] 
01293    * Returns the key of the index'th preference.
01294    * index must be positive.
01295    * Returns icPrefNotFoundErr if index is greater than the total number of preferences.
01296    * If the routine returns an error, key is undefined.
01297    */
01298 /*
01299  *  ICDeletePref()
01300  *  
01301  *  Availability:
01302  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01303  *    CarbonLib:        in CarbonLib 1.0.2 and later
01304  *    Mac OS X:         in version 10.0 or later
01305  */
01306 EXTERN_API( OSStatus )
01307 ICDeletePref(
01308   ICInstance         inst,
01309   ConstStr255Param   key)                                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x000C, 0x7000, 0xA82A);
01310 
01311 
01312 /* [c1] [b2] 
01313    * Deletes the preference specified by key.
01314    * key must not be the empty string.
01315    * Returns icPrefNotFound if the preference specified by key is not present.
01316    */
01317 /*
01318  *  ICEnd()
01319  *  
01320  *  Availability:
01321  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01322  *    CarbonLib:        in CarbonLib 1.0.2 and later
01323  *    Mac OS X:         in version 10.0 or later
01324  */
01325 EXTERN_API( OSStatus )
01326 ICEnd(ICInstance inst)                                        FIVEWORDINLINE(0x2F3C, 0x0000, 0x000A, 0x7000, 0xA82A);
01327 
01328 
01329 /* [c1] [b1] 
01330    * Terminates a preference session, as started by ICBegin.
01331    * You must have called ICBegin before calling this routine.
01332    */
01333 /*
01334  *  ICGetDefaultPref()
01335  *  
01336  *  Availability:
01337  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01338  *    CarbonLib:        in CarbonLib 1.0.2 and later
01339  *    Mac OS X:         in version 10.0 or later
01340  */
01341 EXTERN_API( OSStatus )
01342 ICGetDefaultPref(
01343   ICInstance         inst,
01344   ConstStr255Param   key,
01345   Handle             prefH)                                   FIVEWORDINLINE(0x2F3C, 0x0008, 0x0031, 0x7000, 0xA82A);
01346 
01347 
01348 /* [r4] [c3] [b5] 
01349    * Returns a default preference value for the specified key.  You
01350    * must pass in a valid prefH, which is resized to fit the data.
01351    */
01352 /* ***** User Interface Stuff *****  */
01353 /*
01354  *  ICEditPreferences()
01355  *  
01356  *  Availability:
01357  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01358  *    CarbonLib:        in CarbonLib 1.0.2 and later
01359  *    Mac OS X:         in version 10.0 or later
01360  */
01361 EXTERN_API( OSStatus )
01362 ICEditPreferences(
01363   ICInstance         inst,
01364   ConstStr255Param   key)                                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x000F, 0x7000, 0xA82A);
01365 
01366 
01367 /* [r1] [c1] [b3] 
01368    * Instructs IC to display the user interface associated with editing
01369    * preferences and focusing on the preference specified by key.
01370    * If key is the empty string then no preference should be focused upon.
01371    * You must have specified a configuration before calling this routine.
01372    * You do not need to call ICBegin before calling this routine.
01373    * In the current implementation this launches the IC application
01374    * (or brings it to the front) and displays the window containing
01375    * the preference specified by key.
01376    * It may have a radically different implementation in future
01377    * IC systems.
01378    */
01379 /* ***** URL Handling *****  */
01380 /*
01381  *  ICLaunchURL()
01382  *  
01383  *  Availability:
01384  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01385  *    CarbonLib:        in CarbonLib 1.0.2 and later
01386  *    Mac OS X:         in version 10.0 or later
01387  */
01388 EXTERN_API( OSStatus )
01389 ICLaunchURL(
01390   ICInstance         inst,
01391   ConstStr255Param   hint,
01392   const void *       data,
01393   long               len,
01394   long *             selStart,
01395   long *             selEnd)                                  FIVEWORDINLINE(0x2F3C, 0x0014, 0x0011, 0x7000, 0xA82A);
01396 
01397 
01398 /* [r1] [c1] [b3] 
01399    * Parses a URL out of the specified text and feeds it off to the
01400    * appropriate helper.
01401    * hint indicates the default scheme for URLs of the form "name@address".
01402    * If hint is the empty string then URLs of that form are not allowed.
01403    * data points to the start of the text. It must not be nil.
01404    * len indicates the length of the text. It must be non-negative.
01405    * selStart and selEnd should be passed in as the current selection of
01406    * the text. This selection is given in the same manner as TextEdit,
01407    * ie if selStart = selEnd then there is no selection only an insertion
01408    * point. Also selStart ² selEnd and 0 ² selStart ² len and 0 ² selEnd ² len.
01409    * selStart and selEnd are returned as the bounds of the URL. If the
01410    * routine returns an error then these new boundaries may be
01411    * invalid but they will be close.
01412    * The URL is parsed out of the text and passed off to the appropriate
01413    * helper using the GURL AppleEvent.
01414    */
01415 /*
01416  *  ICParseURL()
01417  *  
01418  *  Availability:
01419  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01420  *    CarbonLib:        in CarbonLib 1.0.2 and later
01421  *    Mac OS X:         in version 10.0 or later
01422  */
01423 EXTERN_API( OSStatus )
01424 ICParseURL(
01425   ICInstance         inst,
01426   ConstStr255Param   hint,
01427   const void *       data,
01428   long               len,
01429   long *             selStart,
01430   long *             selEnd,
01431   Handle             url)                                     FIVEWORDINLINE(0x2F3C, 0x0018, 0x0010, 0x7000, 0xA82A);
01432 
01433 
01434 /* [r1] [c1] [b3] 
01435    * Parses a URL out of the specified text and returns it in a canonical form
01436    * in a handle.
01437    * hint indicates the default scheme for URLs of the form "name@address".
01438    * If hint is the empty string then URLs of that form are not allowed.
01439    * data points to the start of the text. It must not be nil.
01440    * len indicates the length of the text. It must be non-negative.
01441    * selStart and selEnd should be passed in as the current selection of
01442    * the text. This selection is given in the same manner as TextEdit,
01443    * ie if selStart = selEnd then there is no selection only an insertion
01444    * point. Also selStart ² selEnd and 0 ² selStart ² len and 0 ² selEnd ² len.
01445    * selStart and selEnd are returned as the bounds of the URL. If the
01446    * routine returns an error then these new boundaries may be
01447    * invalid but they will be close.
01448    * The incoming url handle must not be nil.  The resulting URL is normalised
01449    * and copied into the url handle, which is resized to fit.
01450    */
01451 /*
01452  *  ICCreateGURLEvent()
01453  *  
01454  *  Availability:
01455  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01456  *    CarbonLib:        in CarbonLib 1.0.2 and later
01457  *    Mac OS X:         in version 10.0 or later
01458  */
01459 EXTERN_API( OSStatus )
01460 ICCreateGURLEvent(
01461   ICInstance    inst,
01462   OSType        helperCreator,
01463   Handle        urlH,
01464   AppleEvent *  theEvent)                                     FIVEWORDINLINE(0x2F3C, 0x000C, 0x0033, 0x7000, 0xA82A);
01465