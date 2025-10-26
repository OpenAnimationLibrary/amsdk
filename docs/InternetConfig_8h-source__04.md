 
01466 
01467 /* [r4] [c1] [b3] 
01468    * Creates a GURL Apple event, targetted at the application whose creator
01469    * code is helperCreator, with a direct object containing the URL text from urlH.
01470    */
01471 /*
01472  *  ICSendGURLEvent()
01473  *  
01474  *  Availability:
01475  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01476  *    CarbonLib:        in CarbonLib 1.0.2 and later
01477  *    Mac OS X:         in version 10.0 or later
01478  */
01479 EXTERN_API( OSStatus )
01480 ICSendGURLEvent(
01481   ICInstance    inst,
01482   AppleEvent *  theEvent)                                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x0034, 0x7000, 0xA82A);
01483 
01484 
01485 /* [r4] [c1] [b3] 
01486    * Sends theEvent to the target application.
01487    */
01488 /* ***** Mappings Routines *****
01489  * 
01490  * Routines for interrogating mappings database.
01491  * 
01492  * ----- High Level Routines -----
01493   */
01494 /*
01495  *  ICMapFilename()
01496  *  
01497  *  Availability:
01498  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01499  *    CarbonLib:        in CarbonLib 1.0.2 and later
01500  *    Mac OS X:         in version 10.0 or later
01501  */
01502 EXTERN_API( OSStatus )
01503 ICMapFilename(
01504   ICInstance         inst,
01505   ConstStr255Param   filename,
01506   ICMapEntry *       entry)                                   FIVEWORDINLINE(0x2F3C, 0x0008, 0x0018, 0x7000, 0xA82A);
01507 
01508 
01509 /* [r1] [c1] [b4] 
01510    * Takes the name of an incoming file and returns the most appropriate
01511    * mappings database entry, based on its extension.
01512    * filename must not be the empty string.
01513    * Returns icPrefNotFoundErr if no suitable entry is found.
01514    */
01515 /*
01516  *  ICMapTypeCreator()
01517  *  
01518  *  Availability:
01519  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01520  *    CarbonLib:        in CarbonLib 1.0.2 and later
01521  *    Mac OS X:         in version 10.0 or later
01522  */
01523 EXTERN_API( OSStatus )
01524 ICMapTypeCreator(
01525   ICInstance         inst,
01526   OSType             fType,
01527   OSType             fCreator,
01528   ConstStr255Param   filename,
01529   ICMapEntry *       entry)                                   FIVEWORDINLINE(0x2F3C, 0x0010, 0x0019, 0x7000, 0xA82A);
01530 
01531 
01532 /* [r1] [c1] [b4] 
01533    * Takes the type and creator (and optionally the name) of an outgoing
01534    * file and returns the most appropriate mappings database entry.
01535    * The filename may be either the name of the outgoing file or
01536    * the empty string.
01537    * Returns icPrefNotFoundErr if no suitable entry found.
01538    */
01539 /* ----- Mid Level Routines -----  */
01540 /*
01541  *  ICMapEntriesFilename()
01542  *  
01543  *  Availability:
01544  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01545  *    CarbonLib:        in CarbonLib 1.0.2 and later
01546  *    Mac OS X:         in version 10.0 or later
01547  */
01548 EXTERN_API( OSStatus )
01549 ICMapEntriesFilename(
01550   ICInstance         inst,
01551   Handle             entries,
01552   ConstStr255Param   filename,
01553   ICMapEntry *       entry)                                   FIVEWORDINLINE(0x2F3C, 0x000C, 0x001C, 0x7000, 0xA82A);
01554 
01555 
01556 /* [r1] [c1] [b3] 
01557    * Takes the name of an incoming file and returns the most appropriate
01558    * mappings database entry, based on its extension.
01559    * entries must be a handle to a valid IC mappings database preference.
01560    * filename must not be the empty string.
01561    * Returns icPrefNotFoundErr if no suitable entry is found.
01562    */
01563 /*
01564  *  ICMapEntriesTypeCreator()
01565  *  
01566  *  Availability:
01567  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01568  *    CarbonLib:        in CarbonLib 1.0.2 and later
01569  *    Mac OS X:         in version 10.0 or later
01570  */
01571 EXTERN_API( OSStatus )
01572 ICMapEntriesTypeCreator(
01573   ICInstance         inst,
01574   Handle             entries,
01575   OSType             fType,
01576   OSType             fCreator,
01577   ConstStr255Param   filename,
01578   ICMapEntry *       entry)                                   FIVEWORDINLINE(0x2F3C, 0x0014, 0x001D, 0x7000, 0xA82A);
01579 
01580 
01581 /* [r1] [c1] [b3] 
01582    * Takes the type and creator (and optionally the name) of an outgoing
01583    * file and returns the most appropriate mappings database entry.
01584    * entries must be a handle to a valid IC mappings database preference.
01585    * The filename may be either the name of the outgoing file or
01586    * the empty string.
01587    * Returns icPrefNotFoundErr if no suitable entry found.
01588    */
01589 /* ----- Low Level Routines -----  */
01590 /*
01591  *  ICCountMapEntries()
01592  *  
01593  *  Availability:
01594  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01595  *    CarbonLib:        in CarbonLib 1.0.2 and later
01596  *    Mac OS X:         in version 10.0 or later
01597  */
01598 EXTERN_API( OSStatus )
01599 ICCountMapEntries(
01600   ICInstance   inst,
01601   Handle       entries,
01602   long *       count)                                         FIVEWORDINLINE(0x2F3C, 0x0008, 0x0012, 0x7000, 0xA82A);
01603 
01604 
01605 /* [r1] [c1] [b3] 
01606    * Counts the number of entries in the mappings database.
01607    * entries must be a handle to a valid IC mappings database preference.
01608    * count is set to the number of entries.
01609    */
01610 /*
01611  *  ICGetIndMapEntry()
01612  *  
01613  *  Availability:
01614  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01615  *    CarbonLib:        in CarbonLib 1.0.2 and later
01616  *    Mac OS X:         in version 10.0 or later
01617  */
01618 EXTERN_API( OSStatus )
01619 ICGetIndMapEntry(
01620   ICInstance    inst,
01621   Handle        entries,
01622   long          index,
01623   long *        pos,
01624   ICMapEntry *  entry)                                        FIVEWORDINLINE(0x2F3C, 0x0010, 0x0013, 0x7000, 0xA82A);
01625 
01626 
01627 /* [r1] [c1] [b3] 
01628    * Gets the index'th entry in the mappings database.
01629    * entries must be a handle to a valid IC mappings database preference.
01630    * index must be in the range from 1 to the number of entries in the database.
01631    * The value of pos is ignored on input. pos is set to the position of
01632    * the index'th entry in the database and is suitable for passing back
01633    * into ICSetMapEntry.
01634    * Does not return any user data associated with the entry.
01635    */
01636 /*
01637  *  ICGetMapEntry()
01638  *  
01639  *  Availability:
01640  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01641  *    CarbonLib:        in CarbonLib 1.0.2 and later
01642  *    Mac OS X:         in version 10.0 or later
01643  */
01644 EXTERN_API( OSStatus )
01645 ICGetMapEntry(
01646   ICInstance    inst,
01647   Handle        entries,
01648   long          pos,
01649   ICMapEntry *  entry)                                        FIVEWORDINLINE(0x2F3C, 0x000C, 0x0014, 0x7000, 0xA82A);
01650 
01651 
01652 /* [r1] [c1] [b3] 
01653    * Returns the entry located at position pos in the mappings database.
01654    * entries must be a handle to a valid IC mappings database preference.
01655    * pos should be 0 to get the first entry. To get the subsequent entries, add
01656    * entry.total_size to pos and iterate.
01657    * Does not return any user data associated with the entry.
01658    */
01659 /*
01660  *  ICSetMapEntry()
01661  *  
01662  *  Availability:
01663  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01664  *    CarbonLib:        in CarbonLib 1.0.2 and later
01665  *    Mac OS X:         in version 10.0 or later
01666  */
01667 EXTERN_API( OSStatus )
01668 ICSetMapEntry(
01669   ICInstance          inst,
01670   Handle              entries,
01671   long                pos,
01672   const ICMapEntry *  entry)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x0015, 0x7000, 0xA82A);
01673 
01674 
01675 /* [r1] [c1] [b3] 
01676    * Sets the entry located at position pos in the mappings database.
01677    * entries must be a handle to a valid IC mappings database preference.
01678    * pos should be either a value returned from ICGetIndMapEntry or a value
01679    * calculated using ICGetMapEntry.
01680    * entry is a var parameter purely for stack space reasons. It is not
01681    * modified in any way.
01682    * Any user data associated with the entry is unmodified.
01683    */
01684 /*
01685  *  ICDeleteMapEntry()
01686  *  
01687  *  Availability:
01688  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01689  *    CarbonLib:        in CarbonLib 1.0.2 and later
01690  *    Mac OS X:         in version 10.0 or later
01691  */
01692 EXTERN_API( OSStatus )
01693 ICDeleteMapEntry(
01694   ICInstance   inst,
01695   Handle       entries,
01696   long         pos)                                           FIVEWORDINLINE(0x2F3C, 0x0008, 0x0016, 0x7000, 0xA82A);
01697 
01698 
01699 /* [r1] [c1] [b3] 
01700    * Deletes the mappings database entry at pos.
01701    * entries must be a handle to a valid IC mappings database preference.
01702    * pos should be either a value returned from ICGetIndMapEntry or a value
01703    * calculated using ICGetMapEntry.
01704    * Also deletes any user data associated with the entry.
01705    */
01706 /*
01707  *  ICAddMapEntry()
01708  *  
01709  *  Availability:
01710  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01711  *    CarbonLib:        in CarbonLib 1.0.2 and later
01712  *    Mac OS X:         in version 10.0 or later
01713  */
01714 EXTERN_API( OSStatus )
01715 ICAddMapEntry(
01716   ICInstance          inst,
01717   Handle              entries,
01718   const ICMapEntry *  entry)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0017, 0x7000, 0xA82A);
01719 
01720 
01721 /* [r1] [c1] [b3] 
01722    * Adds an entry to the mappings database.
01723    * entries must be a handle to a valid IC mappings database preference.
01724    * The entry is added to the end of the entries database.
01725    * No user data is added.
01726    */
01727 /* ***** Profile Management Routines *****  */
01728 /*
01729  *  ICGetCurrentProfile()
01730  *  
01731  *  Availability:
01732  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01733  *    CarbonLib:        in CarbonLib 1.0.2 and later
01734  *    Mac OS X:         in version 10.0 or later
01735  */
01736 EXTERN_API( OSStatus )
01737 ICGetCurrentProfile(
01738   ICInstance     inst,
01739   ICProfileID *  currentID)                                   FIVEWORDINLINE(0x2F3C, 0x0004, 0x0025, 0x7000, 0xA82A);
01740 
01741 
01742 /* [r3] [c1] [b3] 
01743    * Returns the profile ID of the current profile.
01744    */
01745 /*
01746  *  ICSetCurrentProfile()
01747  *  
01748  *  Availability:
01749  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01750  *    CarbonLib:        in CarbonLib 1.0.2 and later
01751  *    Mac OS X:         in version 10.0 or later
01752  */
01753 EXTERN_API( OSStatus )
01754 ICSetCurrentProfile(
01755   ICInstance    inst,
01756   ICProfileID   newID)                                        FIVEWORDINLINE(0x2F3C, 0x0004, 0x0026, 0x7000, 0xA82A);
01757 
01758 
01759 /* [r3] [c1] [b3] 
01760    * Sets the current profile to the profile specified in newProfile.
01761    */
01762 /*
01763  *  ICCountProfiles()
01764  *  
01765  *  Availability:
01766  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01767  *    CarbonLib:        in CarbonLib 1.0.2 and later
01768  *    Mac OS X:         in version 10.0 or later
01769  */
01770 EXTERN_API( OSStatus )
01771 ICCountProfiles(
01772   ICInstance   inst,
01773   long *       count)                                         FIVEWORDINLINE(0x2F3C, 0x0004, 0x0027, 0x7000, 0xA82A);
01774 
01775 
01776 /* [r3] [c1] [b1] 
01777    * Returns the total number of profiles.
01778    */
01779 /*
01780  *  ICGetIndProfile()
01781  *  
01782  *  Availability:
01783  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01784  *    CarbonLib:        in CarbonLib 1.0.2 and later
01785  *    Mac OS X:         in version 10.0 or later
01786  */
01787 EXTERN_API( OSStatus )
01788 ICGetIndProfile(
01789   ICInstance     inst,
01790   long           index,
01791   ICProfileID *  thisID)                                      FIVEWORDINLINE(0x2F3C, 0x0008, 0x0028, 0x7000, 0xA82A);
01792 
01793 
01794 /* [r3] [c1] [b1] 
01795    * Returns the profile ID of the index'th profile.  index must be positive.
01796    * Returns icProfileNotFoundErr if index is greater than the total number
01797    * of profiles.
01798    */
01799 /*
01800  *  ICGetProfileName()
01801  *  
01802  *  Availability:
01803  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01804  *    CarbonLib:        in CarbonLib 1.0.2 and later
01805  *    Mac OS X:         in version 10.0 or later
01806  */
01807 EXTERN_API( OSStatus )
01808 ICGetProfileName(
01809   ICInstance    inst,
01810   ICProfileID   thisID,
01811   Str255        name)                                         FIVEWORDINLINE(0x2F3C, 0x0008, 0x0029, 0x7000, 0xA82A);
01812 
01813 
01814 /* [r3] [c1] [b3] 
01815    * Returns the name of a profile given its ID.  The name may not uniquely
01816    * identify the profile.  [That's what the profile ID is for!]  The name
01817    * is assumed to be in the system script.
01818    */
01819 /*
01820  *  ICSetProfileName()
01821  *  
01822  *  Availability:
01823  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01824  *    CarbonLib:        in CarbonLib 1.0.2 and later
01825  *    Mac OS X:         in version 10.0 or later
01826  */
01827 EXTERN_API( OSStatus )
01828 ICSetProfileName(
01829   ICInstance         inst,
01830   ICProfileID        thisID,
01831   ConstStr255Param   name)                                    FIVEWORDINLINE(0x2F3C, 0x0008, 0x002A, 0x7000, 0xA82A);
01832 
01833 
01834 /* [r3] [c1] [b3] 
01835    * This routine sets the name of the specified profile.  Profile names
01836    * need not be unique.  The name should be in the system script.
01837    */
01838 /*
01839  *  ICAddProfile()
01840  *  
01841  *  Availability:
01842  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01843  *    CarbonLib:        in CarbonLib 1.0.2 and later
01844  *    Mac OS X:         in version 10.0 or later
01845  */
01846 EXTERN_API( OSStatus )
01847 ICAddProfile(
01848   ICInstance     inst,
01849   ICProfileID    prototypeID,
01850   ICProfileID *  newID)                                       FIVEWORDINLINE(0x2F3C, 0x0008, 0x002B, 0x7000, 0xA82A);
01851 
01852 
01853 /* [r3] [c1] [b2] 
01854    * If prototypeID = kICNilProfileID, this routine
01855    * creates a default profile, otherwise it creates a
01856    * profile by cloning the prototype profile.  The ID
01857    * of the new profile is returned