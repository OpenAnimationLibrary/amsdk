y:
02294  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02295  *    CarbonLib:        not available
02296  *    Mac OS X:         not available
02297  */
02298 EXTERN_API( OSStatus )
02299 ICCSetPrefHandle(
02300   ComponentInstance   inst,
02301   ConstStr255Param    key,
02302   ICAttr              attr,
02303   Handle              prefh)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x001B, 0x7000, 0xA82A);
02304 
02305 
02306 /* See comment for ICCSetPrefHandle.  */
02307 /*
02308  *  ICCCountPref()
02309  *  
02310  *  Availability:
02311  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02312  *    CarbonLib:        not available
02313  *    Mac OS X:         not available
02314  */
02315 EXTERN_API( OSStatus )
02316 ICCCountPref(
02317   ComponentInstance   inst,
02318   long *              count)                                  FIVEWORDINLINE(0x2F3C, 0x0004, 0x0008, 0x7000, 0xA82A);
02319 
02320 
02321 /* See comment for ICCCountPref.  */
02322 /*
02323  *  ICCGetIndPref()
02324  *  
02325  *  Availability:
02326  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02327  *    CarbonLib:        not available
02328  *    Mac OS X:         not available
02329  */
02330 EXTERN_API( OSStatus )
02331 ICCGetIndPref(
02332   ComponentInstance   inst,
02333   long                index,
02334   Str255              key)                                    FIVEWORDINLINE(0x2F3C, 0x0008, 0x0009, 0x7000, 0xA82A);
02335 
02336 
02337 /* See comment for ICCGetIndPref.  */
02338 /*
02339  *  ICCDeletePref()
02340  *  
02341  *  Availability:
02342  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02343  *    CarbonLib:        not available
02344  *    Mac OS X:         not available
02345  */
02346 EXTERN_API( OSStatus )
02347 ICCDeletePref(
02348   ComponentInstance   inst,
02349   ConstStr255Param    key)                                    FIVEWORDINLINE(0x2F3C, 0x0004, 0x000C, 0x7000, 0xA82A);
02350 
02351 
02352 /* See comment for ICCDeletePref.  */
02353 /*
02354  *  ICCEnd()
02355  *  
02356  *  Availability:
02357  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02358  *    CarbonLib:        not available
02359  *    Mac OS X:         not available
02360  */
02361 EXTERN_API( OSStatus )
02362 ICCEnd(ComponentInstance inst)                                FIVEWORDINLINE(0x2F3C, 0x0000, 0x000A, 0x7000, 0xA82A);
02363 
02364 
02365 /* See comment for ICCEnd.  */
02366 /*
02367  *  ICCGetDefaultPref()
02368  *  
02369  *  Availability:
02370  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02371  *    CarbonLib:        not available
02372  *    Mac OS X:         not available
02373  */
02374 EXTERN_API( OSStatus )
02375 ICCGetDefaultPref(
02376   ComponentInstance   inst,
02377   ConstStr255Param    key,
02378   Handle              prefH)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0031, 0x7000, 0xA82A);
02379 
02380 
02381 /* See comment for ICCGetDefaultPref.  */
02382 /* ***** User Interface Stuff *****  */
02383 /*
02384  *  ICCEditPreferences()
02385  *  
02386  *  Availability:
02387  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02388  *    CarbonLib:        not available
02389  *    Mac OS X:         not available
02390  */
02391 EXTERN_API( OSStatus )
02392 ICCEditPreferences(
02393   ComponentInstance   inst,
02394   ConstStr255Param    key)                                    FIVEWORDINLINE(0x2F3C, 0x0004, 0x000F, 0x7000, 0xA82A);
02395 
02396 
02397 /* See comment for ICCEditPreferences.  */
02398 /* ***** URL Handling *****  */
02399 /*
02400  *  ICCLaunchURL()
02401  *  
02402  *  Availability:
02403  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02404  *    CarbonLib:        not available
02405  *    Mac OS X:         not available
02406  */
02407 EXTERN_API( OSStatus )
02408 ICCLaunchURL(
02409   ComponentInstance   inst,
02410   ConstStr255Param    hint,
02411   Ptr                 data,
02412   long                len,
02413   long *              selStart,
02414   long *              selEnd)                                 FIVEWORDINLINE(0x2F3C, 0x0014, 0x0011, 0x7000, 0xA82A);
02415 
02416 
02417 /* See comment for ICCLaunchURL.  */
02418 /*
02419  *  ICCParseURL()
02420  *  
02421  *  Availability:
02422  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02423  *    CarbonLib:        not available
02424  *    Mac OS X:         not available
02425  */
02426 EXTERN_API( OSStatus )
02427 ICCParseURL(
02428   ComponentInstance   inst,
02429   ConstStr255Param    hint,
02430   Ptr                 data,
02431   long                len,
02432   long *              selStart,
02433   long *              selEnd,
02434   Handle              url)                                    FIVEWORDINLINE(0x2F3C, 0x0018, 0x0010, 0x7000, 0xA82A);
02435 
02436 
02437 /* See comment for ICCParseURL.  */
02438 /*
02439  *  ICCCreateGURLEvent()
02440  *  
02441  *  Availability:
02442  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02443  *    CarbonLib:        not available
02444  *    Mac OS X:         not available
02445  */
02446 EXTERN_API( OSStatus )
02447 ICCCreateGURLEvent(
02448   ComponentInstance   inst,
02449   OSType              helperCreator,
02450   Handle              urlH,
02451   AppleEvent *        theEvent)                               FIVEWORDINLINE(0x2F3C, 0x000C, 0x0033, 0x7000, 0xA82A);
02452 
02453 
02454 /* See comment for ICCCreateGURLEvent.  */
02455 /*
02456  *  ICCSendGURLEvent()
02457  *  
02458  *  Availability:
02459  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02460  *    CarbonLib:        not available
02461  *    Mac OS X:         not available
02462  */
02463 EXTERN_API( OSStatus )
02464 ICCSendGURLEvent(
02465   ComponentInstance   inst,
02466   AppleEvent *        theEvent)                               FIVEWORDINLINE(0x2F3C, 0x0004, 0x0034, 0x7000, 0xA82A);
02467 
02468 
02469 /* See comment for ICCSendGURLEvent.  */
02470 /* ***** Mappings Routines *****
02471  * 
02472  * Routines for interrogating mappings database.
02473  * 
02474  * ----- High Level Routines -----
02475   */
02476 /*
02477  *  ICCMapFilename()
02478  *  
02479  *  Availability:
02480  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02481  *    CarbonLib:        not available
02482  *    Mac OS X:         not available
02483  */
02484 EXTERN_API( OSStatus )
02485 ICCMapFilename(
02486   ComponentInstance   inst,
02487   ConstStr255Param    filename,
02488   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0018, 0x7000, 0xA82A);
02489 
02490 
02491 /* See comment for ICCMapFilename.  */
02492 /*
02493  *  ICCMapTypeCreator()
02494  *  
02495  *  Availability:
02496  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02497  *    CarbonLib:        not available
02498  *    Mac OS X:         not available
02499  */
02500 EXTERN_API( OSStatus )
02501 ICCMapTypeCreator(
02502   ComponentInstance   inst,
02503   OSType              fType,
02504   OSType              fCreator,
02505   ConstStr255Param    filename,
02506   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x0010, 0x0019, 0x7000, 0xA82A);
02507 
02508 
02509 /* See comment for ICCMapTypeCreator.  */
02510 /* ----- Mid Level Routines -----  */
02511 /*
02512  *  ICCMapEntriesFilename()
02513  *  
02514  *  Availability:
02515  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02516  *    CarbonLib:        not available
02517  *    Mac OS X:         not available
02518  */
02519 EXTERN_API( OSStatus )
02520 ICCMapEntriesFilename(
02521   ComponentInstance   inst,
02522   Handle              entries,
02523   ConstStr255Param    filename,
02524   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x001C, 0x7000, 0xA82A);
02525 
02526 
02527 /* See comment for ICCMapEntriesFilename.  */
02528 /*
02529  *  ICCMapEntriesTypeCreator()
02530  *  
02531  *  Availability:
02532  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02533  *    CarbonLib:        not available
02534  *    Mac OS X:         not available
02535  */
02536 EXTERN_API( OSStatus )
02537 ICCMapEntriesTypeCreator(
02538   ComponentInstance   inst,
02539   Handle              entries,
02540   OSType              fType,
02541   OSType              fCreator,
02542   ConstStr255Param    filename,
02543   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x0014, 0x001D, 0x7000, 0xA82A);
02544 
02545 
02546 /* See comment for ICCMapEntriesTypeCreator.  */
02547 /* ----- Low Level Routines -----  */
02548 /*
02549  *  ICCCountMapEntries()
02550  *  
02551  *  Availability:
02552  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02553  *    CarbonLib:        not available
02554  *    Mac OS X:         not available
02555  */
02556 EXTERN_API( OSStatus )
02557 ICCCountMapEntries(
02558   ComponentInstance   inst,
02559   Handle              entries,
02560   long *              count)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0012, 0x7000, 0xA82A);
02561 
02562 
02563 /* See comment for ICCCountMapEntries.  */
02564 /*
02565  *  ICCGetIndMapEntry()
02566  *  
02567  *  Availability:
02568  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02569  *    CarbonLib:        not available
02570  *    Mac OS X:         not available
02571  */
02572 EXTERN_API( OSStatus )
02573 ICCGetIndMapEntry(
02574   ComponentInstance   inst,
02575   Handle              entries,
02576   long                index,
02577   long *              pos,
02578   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x0010, 0x0013, 0x7000, 0xA82A);
02579 
02580 
02581 /* See comment for ICCGetIndMapEntry.  */
02582 /*
02583  *  ICCGetMapEntry()
02584  *  
02585  *  Availability:
02586  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02587  *    CarbonLib:        not available
02588  *    Mac OS X:         not available
02589  */
02590 EXTERN_API( OSStatus )
02591 ICCGetMapEntry(
02592   ComponentInstance   inst,
02593   Handle              entries,
02594   long                pos,
02595   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x0014, 0x7000, 0xA82A);
02596 
02597 
02598 /* See comment for ICCGetMapEntry.  */
02599 /*
02600  *  ICCSetMapEntry()
02601  *  
02602  *  Availability:
02603  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02604  *    CarbonLib:        not available
02605  *    Mac OS X:         not available
02606  */
02607 EXTERN_API( OSStatus )
02608 ICCSetMapEntry(
02609   ComponentInstance   inst,
02610   Handle              entries,
02611   long                pos,
02612   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x0015, 0x7000, 0xA82A);
02613 
02614 
02615 /* See comment for ICCSetMapEntry.  */
02616 /*
02617  *  ICCDeleteMapEntry()
02618  *  
02619  *  Availability:
02620  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02621  *    CarbonLib:        not available
02622  *    Mac OS X:         not available
02623  */
02624 EXTERN_API( OSStatus )
02625 ICCDeleteMapEntry(
02626   ComponentInstance   inst,
02627   Handle              entries,
02628   long                pos)                                    FIVEWORDINLINE(0x2F3C, 0x0008, 0x0016, 0x7000, 0xA82A);
02629 
02630 
02631 /* See comment for ICCDeleteMapEntry.  */
02632 /*
02633  *  ICCAddMapEntry()
02634  *  
02635  *  Availability:
02636  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02637  *    CarbonLib:        not available
02638  *    Mac OS X:         not available
02639  */
02640 EXTERN_API( OSStatus )
02641 ICCAddMapEntry(
02642   ComponentInstance   inst,
02643   Handle              entries,
02644   ICMapEntry *        entry)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0017, 0x7000, 0xA82A);
02645 
02646 
02647 /* See comment for ICCAddMapEntry.  */
02648 /* ***** Profile Management Routines *****  */
02649 /*
02650  *  ICCGetCurrentProfile()
02651  *  
02652  *  Availability:
02653  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02654  *    CarbonLib:        not available
02655  *    Mac OS X:         not available
02656  */
02657 EXTERN_API( OSStatus )
02658 ICCGetCurrentProfile(
02659   ComponentInstance   inst,
02660   ICProfileID *       currentID)                              FIVEWORDINLINE(0x2F3C, 0x0004, 0x0025, 0x7000, 0xA82A);
02661 
02662 
02663 /* See comment for ICCGetCurrentProfile.  */
02664 /*
02665  *  ICCSetCurrentProfile()
02666  *  
02667  *  Availability:
02668  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02669  *    CarbonLib:        not available
02670  *    Mac OS X:         not available
02671  */
02672 EXTERN_API( OSStatus )
02673 ICCSetCurrentProfile(
02674   ComponentInstance   inst,
02675   ICProfileID         newID)                                  FIVEWORDINLINE(0x2F3C, 0x0004, 0x0026, 0x7000, 0xA82A);
02676 
02677 
02678 /* See comment for ICCSetCurrentProfile.  */
02679 /*
02680  *  ICCCountProfiles()
02681  *  
02682  *  Availability:
02683  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02684  *    CarbonLib:        not available
02685  *    Mac OS X:         not available
02686  */
02687 EXTERN_API( OSStatus )
02688 ICCCountProfiles(
02689   ComponentInstance   inst,
02690   long *              count)                                  FIVEWORDINLINE(0x2F3C, 0x0004, 0x0027, 0x7000, 0xA82A);
02691 
02692 
02693 /* See comment for ICCCountProfiles.  */
02694 /*
02695  *  ICCGetIndProfile()
02696  *  
02697  *  Availability:
02698  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02699  *    CarbonLib:        not available
02700  *    Mac OS X:         not available
02701  */
02702 EXTERN_API( OSStatus )
02703 ICCGetIndProfile(
02704   ComponentInstance   inst,
02705   long                index,
02706   ICProfileID *       thisID)                                 FIVEWORDINLINE(0x2F3C, 0x0008, 0x0028, 0x7000, 0xA82A);
02707 
02708 
02709 /* See comment for ICCGetIndProfile.  */
02710 /*
02711  *  ICCGetProfileName()
02712  *  
02713  *  Availability:
02714  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02715  *    CarbonLib:        not available
02716  *    Mac OS X:         not available
02717  */
02718 EXTERN_API( OSStatus )
02719 ICCGetProfileName(
02720   ComponentInstance   inst,
02721   ICProfileID         thisID,
02722   Str255              name)                                   FIVEWORDINLINE(0x2F3C, 0x0008, 0x0029, 0x7000, 0xA82A);
02723 
02724 
02725 /* See comment for ICCGetProfileName.  */
02726 /*
02727  *  ICCSetProfileName()
02728  *  
02729  *  Availability:
02730  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02731  *    CarbonLib:        not available
02732  *    Mac OS X:         not available
02733  */
02734 EXTERN_API( OSStatus )
02735 ICCSetProfileName(