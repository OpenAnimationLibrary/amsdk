u do not need to be inside a Begin/End pair when calling this routine.
00720       
00721       [b4]  If you are getting or setting multiple preferences, you should make this
00722             call inside a Begin/End pair. If you do not make this call inside a Begin/End
00723             pair, the call will automatically do it for you.
00724       
00725       [b5]  It is illegal to call this routine inside a Begin/End pair.
00726 
00727  ************************************************************************************************/
00728 
00729 /* ***** Starting Up and Shutting Down *****  */
00730 /*
00731  *  ICStart()
00732  *  
00733  *  Availability:
00734  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00735  *    CarbonLib:        in CarbonLib 1.0.2 and later
00736  *    Mac OS X:         in version 10.0 or later
00737  */
00738 EXTERN_API( OSStatus )
00739 ICStart(
00740   ICInstance *  inst,
00741   OSType        signature);
00742 
00743 
00744 /* Call this at application initialisation. Set signature to a value
00745    * which has been regsitered with DTS to allow for future expansion
00746    * of the IC system. Returns inst as a connection to the IC system.
00747    */
00748 /*
00749  *  ICStop()
00750  *  
00751  *  Availability:
00752  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00753  *    CarbonLib:        in CarbonLib 1.0.2 and later
00754  *    Mac OS X:         in version 10.0 or later
00755  */
00756 EXTERN_API( OSStatus )
00757 ICStop(ICInstance inst);
00758 
00759 
00760 /* [b5] 
00761    * Call this at application initialisation, after which inst
00762    * is no longer valid connection to IC.
00763    */
00764 /*
00765  *  ICGetVersion()
00766  *  
00767  *  Availability:
00768  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00769  *    CarbonLib:        in CarbonLib 1.0.2 and later
00770  *    Mac OS X:         in version 10.0 or later
00771  */
00772 EXTERN_API( OSStatus )
00773 ICGetVersion(
00774   ICInstance   inst,
00775   long         whichVersion,
00776   UInt32 *     version)                                       FIVEWORDINLINE(0x2F3C, 0x0008, 0x0032, 0x7000, 0xA82A);
00777 
00778 
00779 /* [r4] [c3] [b3] 
00780    * Returns the version of Internet Config.  Pass kICComponentVersion
00781    * to get the version as previously returned by GetComponenVerson.
00782    * Pass kICNumVersion to get a NumVersion structure.
00783    */
00784 /* ***** Specifying a Configuration *****  */
00785 #if CALL_NOT_IN_CARBON
00786 /*
00787  *  ICFindConfigFile()
00788  *  
00789  *  Availability:
00790  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00791  *    CarbonLib:        not available
00792  *    Mac OS X:         not available
00793  */
00794 EXTERN_API( OSStatus )
00795 ICFindConfigFile(
00796   ICInstance          inst,
00797   short               count,
00798   ICDirSpecArrayPtr   folders)                                FIVEWORDINLINE(0x2F3C, 0x0006, 0x0002, 0x7000, 0xA82A);
00799 
00800 
00801 /* [b5] 
00802    * Call to configure this connection to IC.
00803    * Set count as the number of valid elements in folders.
00804    * Set folders to a pointer to the folders to search.
00805    * Setting count to 0 and folders to nil is OK.
00806    * Searches the specified folders and then the Preferences folder
00807    * in a unspecified manner.
00808    */
00809 /*
00810  *  ICFindUserConfigFile()
00811  *  
00812  *  Availability:
00813  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00814  *    CarbonLib:        not available
00815  *    Mac OS X:         not available
00816  */
00817 EXTERN_API( OSStatus )
00818 ICFindUserConfigFile(
00819   ICInstance   inst,
00820   ICDirSpec *  where)                                         FIVEWORDINLINE(0x2F3C, 0x0004, 0x000E, 0x7000, 0xA82A);
00821 
00822 
00823 /* [r1] [b5] 
00824    * Similar to ICFindConfigFile except that it only searches the folder
00825    * specified in where.  If the input parameters are valid the routine
00826    * will always successful configure the instance, creating an
00827    * empty configuration if necessary
00828    * For use with double-clickable preference files.
00829    */
00830 /*
00831  *  ICGeneralFindConfigFile()
00832  *  
00833  *  Availability:
00834  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00835  *    CarbonLib:        not available
00836  *    Mac OS X:         not available
00837  */
00838 EXTERN_API( OSStatus )
00839 ICGeneralFindConfigFile(
00840   ICInstance          inst,
00841   Boolean             searchPrefs,
00842   Boolean             canCreate,
00843   short               count,
00844   ICDirSpecArrayPtr   folders)                                FIVEWORDINLINE(0x2F3C, 0x000A, 0x001E, 0x7000, 0xA82A);
00845 
00846 
00847 /* [r2] [b5] 
00848    * Call to configure this connection to IC.
00849    * This routine acts as a more general replacement for
00850    * ICFindConfigFile and ICFindUserConfigFile.
00851    * Set search_prefs to true if you want it to search the preferences folder.
00852    * Set can_create to true if you want it to be able to create a new config.
00853    * Set count as the number of valid elements in folders.
00854    * Set folders to a pointer to the folders to search.
00855    * Setting count to 0 and folders to nil is OK.
00856    * Searches the specified folders and then optionally the Preferences folder
00857    * in a unspecified manner.
00858    */
00859 /*
00860  *  ICChooseConfig()
00861  *  
00862  *  Availability:
00863  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00864  *    CarbonLib:        not available
00865  *    Mac OS X:         not available
00866  */
00867 EXTERN_API( OSStatus )
00868 ICChooseConfig(ICInstance inst)                               FIVEWORDINLINE(0x2F3C, 0x0000, 0x0021, 0x7000, 0xA82A);
00869 
00870 
00871 /* [r2] [b5] 
00872    * Requests the user to choose a configuration, typically using some
00873    * sort of modal dialog. If the user cancels the dialog the configuration
00874    * state will be unaffected.
00875    */
00876 /*
00877  *  ICChooseNewConfig()
00878  *  
00879  *  Availability:
00880  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00881  *    CarbonLib:        not available
00882  *    Mac OS X:         not available
00883  */
00884 EXTERN_API( OSStatus )
00885 ICChooseNewConfig(ICInstance inst)                            FIVEWORDINLINE(0x2F3C, 0x0000, 0x0022, 0x7000, 0xA82A);
00886 
00887 
00888 /* [r2] [b5] 
00889    * Requests the user to create a new configuration, typically using some
00890    * sort of modal dialog. If the user cancels the dialog the configuration
00891    * state will be unaffected.
00892    */
00893 #endif  /* CALL_NOT_IN_CARBON */
00894 
00895 /*
00896  *  ICGetConfigName()
00897  *  
00898  *  Availability:
00899  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00900  *    CarbonLib:        in CarbonLib 1.0.2 and later
00901  *    Mac OS X:         in version 10.0 or later
00902  */
00903 EXTERN_API( OSStatus )
00904 ICGetConfigName(
00905   ICInstance   inst,
00906   Boolean      longname,
00907   Str255       name)                                          FIVEWORDINLINE(0x2F3C, 0x0006, 0x0023, 0x7000, 0xA82A);
00908 
00909 
00910 /* [r2] [c1] [b3] 
00911    * Returns a string that describes the current configuration at a user
00912    * level. Set longname to true if you want a long name, up to 255
00913    * characters, or false if you want a short name, typically about 32
00914    * characters.
00915    * The returned string is for user display only. If you rely on the
00916    * exact format of it, you will conflict with any future IC
00917    * implementation that doesn't use explicit preference files.
00918    */
00919 #if CALL_NOT_IN_CARBON
00920 /*
00921  *  ICGetConfigReference()
00922  *  
00923  *  Availability:
00924  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00925  *    CarbonLib:        not available
00926  *    Mac OS X:         not available
00927  */
00928 EXTERN_API( OSStatus )
00929 ICGetConfigReference(
00930   ICInstance          inst,
00931   ICConfigRefHandle   ref)                                    FIVEWORDINLINE(0x2F3C, 0x0004, 0x001F, 0x7000, 0xA82A);
00932 
00933 
00934 /* [r2] [c1] [b3] 
00935    * Returns a self-contained reference to the instance's current
00936    * configuration.
00937    * ref must be a valid non-nil handle and it will be resized to fit the
00938    * resulting data.
00939    */
00940 /*
00941  *  ICSetConfigReference()
00942  *  
00943  *  Availability:
00944  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00945  *    CarbonLib:        not available
00946  *    Mac OS X:         not available
00947  */
00948 EXTERN_API( OSStatus )
00949 ICSetConfigReference(
00950   ICInstance          inst,
00951   ICConfigRefHandle   ref,
00952   long                flags)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0020, 0x7000, 0xA82A);
00953 
00954 
00955 /* [r2] [b5] 
00956    * Reconfigures the instance using a configuration reference that was
00957    * got using ICGetConfigReference reference. Set the
00958    * icNoUserInteraction_bit in flags if you require that this routine
00959    * not present a modal dialog. Other flag bits are reserved and should
00960    * be set to zero.
00961    * ref must not be nil.
00962    */
00963 /* ***** Private Routines *****
00964  * 
00965  * If you are calling these routines, you are most probably doing something
00966  * wrong.  Please read the documentation for more details.
00967   */
00968 /*
00969  *  ICSpecifyConfigFile()
00970  *  
00971  *  Availability:
00972  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00973  *    CarbonLib:        not available
00974  *    Mac OS X:         not available
00975  */
00976 EXTERN_API( OSStatus )
00977 ICSpecifyConfigFile(
00978   ICInstance   inst,
00979   FSSpec *     config)                                        FIVEWORDINLINE(0x2F3C, 0x0004, 0x0003, 0x7000, 0xA82A);
00980 
00981 
00982 /* [b5] 
00983    * For use only by the IC application.
00984    * If you call this routine yourself, you will conflict with any
00985    * future IC implementation that doesn't use explicit preference files.
00986    */
00987 /*
00988  *  ICRefreshCaches()
00989  *  
00990  *  Availability:
00991  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
00992  *    CarbonLib:        not available
00993  *    Mac OS X:         not available
00994  */
00995 EXTERN_API( OSStatus )
00996 ICRefreshCaches(ICInstance inst)                              FIVEWORDINLINE(0x2F3C, 0x0000, 0x002F, 0x7000, 0xA82A);
00997 
00998 
00999 /* [r3] [c1] [b3] 
01000    * For use only by the IC application.
01001    * If you call this routine yourself, you will conflict with any
01002    * future IC implementation that doesn't use explicit preference files.
01003    */
01004 /* ***** Getting Information *****  */
01005 #endif  /* CALL_NOT_IN_CARBON */
01006 
01007 /*
01008  *  ICGetSeed()
01009  *  
01010  *  Availability:
01011  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01012  *    CarbonLib:        in CarbonLib 1.0.2 and later
01013  *    Mac OS X:         in version 10.0 or later
01014  */
01015 EXTERN_API( OSStatus )
01016 ICGetSeed(
01017   ICInstance   inst,
01018   long *       seed)                                          FIVEWORDINLINE(0x2F3C, 0x0004, 0x0004, 0x7000, 0xA82A);
01019 
01020 
01021 /* [c3] [b3] 
01022    * Returns the current seed for the IC prefs database.
01023    * This seed changes each time a non-volatile preference is changed.
01024    * You can poll this to determine if any cached preferences change.
01025    */
01026 /*
01027  *  ICGetPerm()
01028  *  
01029  *  Availability:
01030  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01031  *    CarbonLib:        in CarbonLib 1.0.2 and later
01032  *    Mac OS X:         in version 10.0 or later
01033  */
01034 EXTERN_API( OSStatus )
01035 ICGetPerm(
01036   ICInstance   inst,
01037   ICPerm *     perm)                                          FIVEWORDINLINE(0x2F3C, 0x0004, 0x000D, 0x7000, 0xA82A);
01038 
01039 
01040 /* [c3] [b3] 
01041    * Returns the access permissions currently associated with this instance.
01042    * While applications normally know what permissions they have,
01043    * this routine is designed for use by override components.
01044    */
01045 #if CALL_NOT_IN_CARBON
01046 /*
01047  *  ICDefaultFileName()
01048  *  
01049  *  Availability:
01050  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01051  *    CarbonLib:        not available
01052  *    Mac OS X:         not available
01053  */
01054 EXTERN_API( OSStatus )
01055 ICDefaultFileName(
01056   ICInstance   inst,
01057   Str63        name)                                          FIVEWORDINLINE(0x2F3C, 0x0004, 0x000B, 0x7000, 0xA82A);
01058 
01059 
01060 /* [c3] [b3] 
01061    * Returns the default file name for IC preference files.
01062    * Applications should never need to call this routine.
01063    * If you rely on information returned by this routine yourself,
01064    * you may conflict with any future IC implementation that doesn't use
01065    * explicit preference files.
01066    * The component calls this routine to set up the default IC file name.
01067    * This allows this operation to be intercepted by a component that has
01068    * captured us. It currently gets it from the component resource file.
01069    * The glue version is hardwired to "Internet Preferences".
01070    */
01071 /*
01072  *  ICGetComponentInstance()
01073  *  
01074  *  Availability:
01075  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01076  *    CarbonLib:        not available
01077  *    Mac OS X:         not available
01078  */
01079 EXTERN_API( OSStatus )
01080 ICGetComponentInstance(
01081   ICInstance           inst,
01082   ComponentInstance *  componentInst);
01083 
01084 
01085 /* [c3] [b3] 
01086    * Returns noErr and the connection to the IC component,
01087    * if we're using the component.
01088    * Returns badComponenInstance and nil if we're operating with glue.
01089    */
01090 /* ***** Reading and Writing Preferences *****  */
01091 #endif  /* CALL_NOT_IN_CARBON */
01092 
01093 /*
01094  *  ICBegin()
01095  *  
01096  *  Availability:
01097  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01098  *    CarbonLib:        in CarbonLib 1.0.2 and later
01099  *    Mac OS X:         in version 10.0 or later
01100  */
01101 EXTERN_API( OSStatus )
01102 ICBegin(
01103   ICInstance   inst,
01104   ICPerm       perm)                                          FIVEWORDINLINE(0x2F3C, 0x0002, 0x0005, 0x7000, 0xA82A);
01105 
01106 
01107 /* [c1] [b5] 
01108    * Starting reading or writing multiple preferences.
01109    * A call to this must be balanced by a call to ICEnd.
01110    * Do not call WaitNextEvent between these calls.
01111    * The perm specifies whether you in