 in newID.
01858    * The new profile will be give a new, unique, name.
01859    * This does not switch to the new profile.
01860    */
01861 /*
01862  *  ICDeleteProfile()
01863  *  
01864  *  Availability:
01865  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01866  *    CarbonLib:        in CarbonLib 1.0.2 and later
01867  *    Mac OS X:         in version 10.0 or later
01868  */
01869 EXTERN_API( OSStatus )
01870 ICDeleteProfile(
01871   ICInstance    inst,
01872   ICProfileID   thisID)                                       FIVEWORDINLINE(0x2F3C, 0x0004, 0x002C, 0x7000, 0xA82A);
01873 
01874 
01875 /* [r3] [c1] [b2] 
01876    * This routine deletes the profile specified by
01877    * thisID.  Attempting to delete the current profile
01878    * or the last profile will return error.
01879    */
01880 /************************************************************************************************
01881   NOTHING BELOW THIS DIVIDER IS IN CARBON
01882  ************************************************************************************************/
01883 /* ***** Interrupt Safe Routines *****  */
01884 #if CALL_NOT_IN_CARBON
01885 /*
01886  *  ICRequiresInterruptSafe()
01887  *  
01888  *  Availability:
01889  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01890  *    CarbonLib:        not available
01891  *    Mac OS X:         not available
01892  */
01893 EXTERN_API( OSStatus )
01894 ICRequiresInterruptSafe(ICInstance inst)                      FIVEWORDINLINE(0x2F3C, 0x0000, 0x002D, 0x7000, 0xA82A);
01895 
01896 
01897 /* [r3] [c2] [b3] 
01898    * You must call this routine before calling GetMapEntryInterruptSafe
01899    * to give IC chance to cache the mappings data in memory.  The only
01900    * way to clear this state is to close the instance.  You can not reconfigure
01901    * the instance after calling this routine.
01902    */
01903 /*
01904  *  ICGetMappingInterruptSafe()
01905  *  
01906  *  Availability:
01907  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01908  *    CarbonLib:        not available
01909  *    Mac OS X:         not available
01910  */
01911 EXTERN_API( OSStatus )
01912 ICGetMappingInterruptSafe(
01913   ICInstance   inst,
01914   Ptr *        mappingPref,
01915   long *       mappingPrefSize)                               FIVEWORDINLINE(0x2F3C, 0x0008, 0x002E, 0x7000, 0xA82A);
01916 
01917 
01918 /* [r3] [c2] [b3] 
01919    * Returns the "Mapping" preference in an interrupt safe fashion.
01920    * The preference returned pointer is valid until the next
01921    * non-interrupt safe call to IC.  Typically this API is used
01922    * by software that needs to map extensions to type and creator
01923    * at interrupt time, eg foreign file systems.
01924    */
01925 /*
01926  *  ICGetSeedInterruptSafe()
01927  *  
01928  *  Availability:
01929  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01930  *    CarbonLib:        not available
01931  *    Mac OS X:         not available
01932  */
01933 EXTERN_API( OSStatus )
01934 ICGetSeedInterruptSafe(
01935   ICInstance   inst,
01936   long *       seed)                                          FIVEWORDINLINE(0x2F3C, 0x0004, 0x0030, 0x7000, 0xA82A);
01937 
01938 
01939 /* [r3] [c2] [b3] 
01940    * An interrupt safe version of ICGetSeed.
01941    */
01942 /* ***** Starting Up and Shutting Down *****  */
01943 /*
01944  *  ICCStart()
01945  *  
01946  *  Availability:
01947  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01948  *    CarbonLib:        not available
01949  *    Mac OS X:         not available
01950  */
01951 EXTERN_API( OSStatus )
01952 ICCStart(
01953   ComponentInstance *  inst,
01954   OSType               creator);
01955 
01956 
01957 /* See comment for ICCStart.  */
01958 /*
01959  *  ICCStop()
01960  *  
01961  *  Availability:
01962  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01963  *    CarbonLib:        not available
01964  *    Mac OS X:         not available
01965  */
01966 EXTERN_API( OSStatus )
01967 ICCStop(ComponentInstance inst);
01968 
01969 
01970 /* See comment for ICCStop.  */
01971 /*
01972  *  ICCGetVersion()
01973  *  
01974  *  Availability:
01975  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01976  *    CarbonLib:        not available
01977  *    Mac OS X:         not available
01978  */
01979 EXTERN_API( OSStatus )
01980 ICCGetVersion(
01981   ComponentInstance   inst,
01982   long                whichVersion,
01983   UInt32 *            version)                                FIVEWORDINLINE(0x2F3C, 0x0008, 0x0032, 0x7000, 0xA82A);
01984 
01985 
01986 /* See comment for ICCGetVersion.  */
01987 /* ***** Specifying a Configuration *****  */
01988 /*
01989  *  ICCFindConfigFile()
01990  *  
01991  *  Availability:
01992  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
01993  *    CarbonLib:        not available
01994  *    Mac OS X:         not available
01995  */
01996 EXTERN_API( OSStatus )
01997 ICCFindConfigFile(
01998   ComponentInstance   inst,
01999   short               count,
02000   ICDirSpecArrayPtr   folders)                                FIVEWORDINLINE(0x2F3C, 0x0006, 0x0002, 0x7000, 0xA82A);
02001 
02002 
02003 /* See comment for ICCFindConfigFile.  */
02004 /*
02005  *  ICCFindUserConfigFile()
02006  *  
02007  *  Availability:
02008  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02009  *    CarbonLib:        not available
02010  *    Mac OS X:         not available
02011  */
02012 EXTERN_API( OSStatus )
02013 ICCFindUserConfigFile(
02014   ComponentInstance   inst,
02015   ICDirSpec *         where)                                  FIVEWORDINLINE(0x2F3C, 0x0004, 0x000E, 0x7000, 0xA82A);
02016 
02017 
02018 /* See comment for ICCFindUserConfigFile.  */
02019 /*
02020  *  ICCGeneralFindConfigFile()
02021  *  
02022  *  Availability:
02023  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02024  *    CarbonLib:        not available
02025  *    Mac OS X:         not available
02026  */
02027 EXTERN_API( OSStatus )
02028 ICCGeneralFindConfigFile(
02029   ComponentInstance   inst,
02030   Boolean             searchPrefs,
02031   Boolean             canCreate,
02032   short               count,
02033   ICDirSpecArrayPtr   folders)                                FIVEWORDINLINE(0x2F3C, 0x000A, 0x001E, 0x7000, 0xA82A);
02034 
02035 
02036 /* See comment for ICCGeneralFindConfigFile.  */
02037 /*
02038  *  ICCChooseConfig()
02039  *  
02040  *  Availability:
02041  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02042  *    CarbonLib:        not available
02043  *    Mac OS X:         not available
02044  */
02045 EXTERN_API( OSStatus )
02046 ICCChooseConfig(ComponentInstance inst)                       FIVEWORDINLINE(0x2F3C, 0x0000, 0x0021, 0x7000, 0xA82A);
02047 
02048 
02049 /* See comment for ICCChooseConfig.  */
02050 /*
02051  *  ICCChooseNewConfig()
02052  *  
02053  *  Availability:
02054  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02055  *    CarbonLib:        not available
02056  *    Mac OS X:         not available
02057  */
02058 EXTERN_API( OSStatus )
02059 ICCChooseNewConfig(ComponentInstance inst)                    FIVEWORDINLINE(0x2F3C, 0x0000, 0x0022, 0x7000, 0xA82A);
02060 
02061 
02062 /* See comment for ICCChooseNewConfig.  */
02063 /*
02064  *  ICCGetConfigName()
02065  *  
02066  *  Availability:
02067  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02068  *    CarbonLib:        not available
02069  *    Mac OS X:         not available
02070  */
02071 EXTERN_API( OSStatus )
02072 ICCGetConfigName(
02073   ComponentInstance   inst,
02074   Boolean             longname,
02075   Str255              name)                                   FIVEWORDINLINE(0x2F3C, 0x0006, 0x0023, 0x7000, 0xA82A);
02076 
02077 
02078 /* See comment for ICCGetConfigName.  */
02079 /*
02080  *  ICCGetConfigReference()
02081  *  
02082  *  Availability:
02083  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02084  *    CarbonLib:        not available
02085  *    Mac OS X:         not available
02086  */
02087 EXTERN_API( OSStatus )
02088 ICCGetConfigReference(
02089   ComponentInstance   inst,
02090   ICConfigRefHandle   ref)                                    FIVEWORDINLINE(0x2F3C, 0x0004, 0x001F, 0x7000, 0xA82A);
02091 
02092 
02093 /* See comment for ICCGetConfigReference.  */
02094 /*
02095  *  ICCSetConfigReference()
02096  *  
02097  *  Availability:
02098  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02099  *    CarbonLib:        not available
02100  *    Mac OS X:         not available
02101  */
02102 EXTERN_API( OSStatus )
02103 ICCSetConfigReference(
02104   ComponentInstance   inst,
02105   ICConfigRefHandle   ref,
02106   long                flags)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x0020, 0x7000, 0xA82A);
02107 
02108 
02109 /* See comment for ICCSetConfigReference.  */
02110 /* ***** Private Routines *****
02111  * 
02112  * If you are calling these routines, you are most probably doing something
02113  * wrong.  Please read the documentation for more details.
02114   */
02115 /*
02116  *  ICCSpecifyConfigFile()
02117  *  
02118  *  Availability:
02119  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02120  *    CarbonLib:        not available
02121  *    Mac OS X:         not available
02122  */
02123 EXTERN_API( OSStatus )
02124 ICCSpecifyConfigFile(
02125   ComponentInstance   inst,
02126   FSSpec *            config)                                 FIVEWORDINLINE(0x2F3C, 0x0004, 0x0003, 0x7000, 0xA82A);
02127 
02128 
02129 /* See comment for ICCSpecifyConfigFile.  */
02130 /*
02131  *  ICCRefreshCaches()
02132  *  
02133  *  Availability:
02134  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02135  *    CarbonLib:        not available
02136  *    Mac OS X:         not available
02137  */
02138 EXTERN_API( OSStatus )
02139 ICCRefreshCaches(ComponentInstance inst)                      FIVEWORDINLINE(0x2F3C, 0x0000, 0x002F, 0x7000, 0xA82A);
02140 
02141 
02142 /* See comment for ICCRefreshCaches.  */
02143 /* ***** Getting Information *****  */
02144 /*
02145  *  ICCGetSeed()
02146  *  
02147  *  Availability:
02148  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02149  *    CarbonLib:        not available
02150  *    Mac OS X:         not available
02151  */
02152 EXTERN_API( OSStatus )
02153 ICCGetSeed(
02154   ComponentInstance   inst,
02155   long *              seed)                                   FIVEWORDINLINE(0x2F3C, 0x0004, 0x0004, 0x7000, 0xA82A);
02156 
02157 
02158 /* See comment for ICCGetSeed.  */
02159 /*
02160  *  ICCGetPerm()
02161  *  
02162  *  Availability:
02163  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02164  *    CarbonLib:        not available
02165  *    Mac OS X:         not available
02166  */
02167 EXTERN_API( OSStatus )
02168 ICCGetPerm(
02169   ComponentInstance   inst,
02170   ICPerm *            perm)                                   FIVEWORDINLINE(0x2F3C, 0x0004, 0x000D, 0x7000, 0xA82A);
02171 
02172 
02173 /* See comment for ICCGetPerm.  */
02174 /*
02175  *  ICCDefaultFileName()
02176  *  
02177  *  Availability:
02178  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02179  *    CarbonLib:        not available
02180  *    Mac OS X:         not available
02181  */
02182 EXTERN_API( OSStatus )
02183 ICCDefaultFileName(
02184   ComponentInstance   inst,
02185   Str63               name)                                   FIVEWORDINLINE(0x2F3C, 0x0004, 0x000B, 0x7000, 0xA82A);
02186 
02187 
02188 /* See comment for ICCDefaultFileName.  */
02189 /*
02190  *  ICCGetComponentInstance()
02191  *  
02192  *  Availability:
02193  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02194  *    CarbonLib:        not available
02195  *    Mac OS X:         not available
02196  */
02197 EXTERN_API( OSStatus )
02198 ICCGetComponentInstance(
02199   ComponentInstance    inst,
02200   ComponentInstance *  componentInst);
02201 
02202 
02203 /* See comment for ICCGetComponentInstance.  */
02204 /* ***** Reading and Writing Preferences *****  */
02205 /*
02206  *  ICCBegin()
02207  *  
02208  *  Availability:
02209  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02210  *    CarbonLib:        not available
02211  *    Mac OS X:         not available
02212  */
02213 EXTERN_API( OSStatus )
02214 ICCBegin(
02215   ComponentInstance   inst,
02216   ICPerm              perm)                                   FIVEWORDINLINE(0x2F3C, 0x0002, 0x0005, 0x7000, 0xA82A);
02217 
02218 
02219 /* See comment for ICCBegin.  */
02220 /*
02221  *  ICCGetPref()
02222  *  
02223  *  Availability:
02224  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02225  *    CarbonLib:        not available
02226  *    Mac OS X:         not available
02227  */
02228 EXTERN_API( OSStatus )
02229 ICCGetPref(
02230   ComponentInstance   inst,
02231   ConstStr255Param    key,
02232   ICAttr *            attr,
02233   Ptr                 buf,
02234   long *              size)                                   FIVEWORDINLINE(0x2F3C, 0x0010, 0x0006, 0x7000, 0xA82A);
02235 
02236 
02237 /* See comment for ICCGetPref.  */
02238 /*
02239  *  ICCSetPref()
02240  *  
02241  *  Availability:
02242  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02243  *    CarbonLib:        not available
02244  *    Mac OS X:         not available
02245  */
02246 EXTERN_API( OSStatus )
02247 ICCSetPref(
02248   ComponentInstance   inst,
02249   ConstStr255Param    key,
02250   ICAttr              attr,
02251   Ptr                 buf,
02252   long                size)                                   FIVEWORDINLINE(0x2F3C, 0x0010, 0x0007, 0x7000, 0xA82A);
02253 
02254 
02255 /* See comment for ICCSetPref.  */
02256 /*
02257  *  ICCFindPrefHandle()
02258  *  
02259  *  Availability:
02260  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02261  *    CarbonLib:        not available
02262  *    Mac OS X:         not available
02263  */
02264 EXTERN_API( OSStatus )
02265 ICCFindPrefHandle(
02266   ComponentInstance   inst,
02267   ConstStr255Param    key,
02268   ICAttr *            attr,
02269   Handle              prefh)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x0024, 0x7000, 0xA82A);
02270 
02271 
02272 /* See comment for ICCFindPrefHandle.  */
02273 /*
02274  *  ICCGetPrefHandle()
02275  *  
02276  *  Availability:
02277  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02278  *    CarbonLib:        not available
02279  *    Mac OS X:         not available
02280  */
02281 EXTERN_API( OSStatus )
02282 ICCGetPrefHandle(
02283   ComponentInstance   inst,
02284   ConstStr255Param    key,
02285   ICAttr *            attr,
02286   Handle *            prefh)                                  FIVEWORDINLINE(0x2F3C, 0x000C, 0x001A, 0x7000, 0xA82A);
02287 
02288 
02289 /* See comment for ICCGetPrefHandle.  */
02290 /*
02291  *  ICCSetPrefHandle()
02292  *  
02293  *  Availabilit