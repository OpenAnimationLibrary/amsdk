
02736   ComponentInstance   inst,
02737   ICProfileID         thisID,
02738   ConstStr255Param    name)                                   FIVEWORDINLINE(0x2F3C, 0x0008, 0x002A, 0x7000, 0xA82A);
02739 
02740 
02741 /* See comment for ICCSetProfileName.  */
02742 /*
02743  *  ICCAddProfile()
02744  *  
02745  *  Availability:
02746  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02747  *    CarbonLib:        not available
02748  *    Mac OS X:         not available
02749  */
02750 EXTERN_API( OSStatus )
02751 ICCAddProfile(
02752   ComponentInstance   inst,
02753   ICProfileID         prototypeID,
02754   ICProfileID *       newID)                                  FIVEWORDINLINE(0x2F3C, 0x0008, 0x002B, 0x7000, 0xA82A);
02755 
02756 
02757 /* See comment for ICCAddProfile.  */
02758 /*
02759  *  ICCDeleteProfile()
02760  *  
02761  *  Availability:
02762  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02763  *    CarbonLib:        not available
02764  *    Mac OS X:         not available
02765  */
02766 EXTERN_API( OSStatus )
02767 ICCDeleteProfile(
02768   ComponentInstance   inst,
02769   ICProfileID         thisID)                                 FIVEWORDINLINE(0x2F3C, 0x0004, 0x002C, 0x7000, 0xA82A);
02770 
02771 
02772 /* See comment for ICCDeleteProfile.  */
02773 /* ***** Interrupt Safe Routines *****  */
02774 /*
02775  *  ICCRequiresInterruptSafe()
02776  *  
02777  *  Availability:
02778  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02779  *    CarbonLib:        not available
02780  *    Mac OS X:         not available
02781  */
02782 EXTERN_API( OSStatus )
02783 ICCRequiresInterruptSafe(ComponentInstance inst)              FIVEWORDINLINE(0x2F3C, 0x0000, 0x002D, 0x7000, 0xA82A);
02784 
02785 
02786 /* See comment for ICCRequiresInterruptSafe.  */
02787 /*
02788  *  ICCGetMappingInterruptSafe()
02789  *  
02790  *  Availability:
02791  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02792  *    CarbonLib:        not available
02793  *    Mac OS X:         not available
02794  */
02795 EXTERN_API( OSStatus )
02796 ICCGetMappingInterruptSafe(
02797   ComponentInstance   inst,
02798   Ptr *               mappingPref,
02799   long *              mappingPrefSize)                        FIVEWORDINLINE(0x2F3C, 0x0008, 0x002E, 0x7000, 0xA82A);
02800 
02801 
02802 /* See comment for ICCGetMappingInterruptSafe.  */
02803 /*
02804  *  ICCGetSeedInterruptSafe()
02805  *  
02806  *  Availability:
02807  *    Non-Carbon CFM:   in InternetConfig 2.5 and later
02808  *    CarbonLib:        not available
02809  *    Mac OS X:         not available
02810  */
02811 EXTERN_API( OSStatus )
02812 ICCGetSeedInterruptSafe(
02813   ComponentInstance   inst,
02814   long *              seed)                                   FIVEWORDINLINE(0x2F3C, 0x0004, 0x0030, 0x7000, 0xA82A);
02815 
02816 
02817 /* See comment for ICCGetSeedInterruptSafe.  */
02818 #endif  /* CALL_NOT_IN_CARBON */
02819 
02820 #if CALL_NOT_IN_CARBON
02821 
02822 /************************************************************************************************
02823   component selectors
02824  ************************************************************************************************/
02825 
02826 enum {
02827   kICCStart                     = 0,
02828   kICCStop                      = 1,
02829   kICCGetVersion                = 50,
02830   kICCFindConfigFile            = 2,
02831   kICCFindUserConfigFile        = 14,
02832   kICCGeneralFindConfigFile     = 30,
02833   kICCChooseConfig              = 33,
02834   kICCChooseNewConfig           = 34,
02835   kICCGetConfigName             = 35,
02836   kICCGetConfigReference        = 31,
02837   kICCSetConfigReference        = 32,
02838   kICCSpecifyConfigFile         = 3,
02839   kICCRefreshCaches             = 47,
02840   kICCGetSeed                   = 4,
02841   kICCGetPerm                   = 13,
02842   kICCDefaultFileName           = 11,
02843   kICCBegin                     = 5,
02844   kICCGetPref                   = 6,
02845   kICCSetPref                   = 7,
02846   kICCFindPrefHandle            = 36,
02847   kICCGetPrefHandle             = 26,
02848   kICCSetPrefHandle             = 27,
02849   kICCCountPref                 = 8,
02850   kICCGetIndPref                = 9,
02851   kICCDeletePref                = 12,
02852   kICCEnd                       = 10,
02853   kICCGetDefaultPref            = 49,
02854   kICCEditPreferences           = 15,
02855   kICCLaunchURL                 = 17,
02856   kICCParseURL                  = 16,
02857   kICCCreateGURLEvent           = 51,
02858   kICCSendGURLEvent             = 52,
02859   kICCMapFilename               = 24,
02860   kICCMapTypeCreator            = 25,
02861   kICCMapEntriesFilename        = 28,
02862   kICCMapEntriesTypeCreator     = 29,
02863   kICCCountMapEntries           = 18,
02864   kICCGetIndMapEntry            = 19,
02865   kICCGetMapEntry               = 20,
02866   kICCSetMapEntry               = 21,
02867   kICCDeleteMapEntry            = 22,
02868   kICCAddMapEntry               = 23,
02869   kICCGetCurrentProfile         = 37,
02870   kICCSetCurrentProfile         = 38,
02871   kICCCountProfiles             = 39,
02872   kICCGetIndProfile             = 40,
02873   kICCGetProfileName            = 41,
02874   kICCSetProfileName            = 42,
02875   kICCAddProfile                = 43,
02876   kICCDeleteProfile             = 44,
02877   kICCRequiresInterruptSafe     = 45,
02878   kICCGetMappingInterruptSafe   = 46,
02879   kICCGetSeedInterruptSafe      = 48,
02880   kICCFirstSelector             = kICCStart,
02881   kICCLastSelector              = 52
02882 };
02883 
02884 /************************************************************************************************
02885   component selector proc infos
02886  ************************************************************************************************/
02887 
02888 enum {
02889   kICCStartProcInfo             = 1008,
02890   kICCStopProcInfo              = 240,
02891   kICCGetVersionProcInfo        = 4080,
02892   kICCFindConfigFileProcInfo    = 3824,
02893   kICCFindUserConfigFileProcInfo = 1008,
02894   kICCGeneralFindConfigFileProcInfo = 58864L,
02895   kICCChooseConfigProcInfo      = 240,
02896   kICCChooseNewConfigProcInfo   = 240,
02897   kICCGetConfigNameProcInfo     = 3568,
02898   kICCGetConfigReferenceProcInfo = 1008,
02899   kICCSetConfigReferenceProcInfo = 4080,
02900   kICCSpecifyConfigFileProcInfo = 1008,
02901   kICCRefreshCachesProcInfo     = 240,
02902   kICCGetSeedProcInfo           = 1008,
02903   kICCGetPermProcInfo           = 1008,
02904   kICCDefaultFileNameProcInfo   = 1008,
02905   kICCGetComponentInstanceProcInfo = 1008,
02906   kICCBeginProcInfo             = 496,
02907   kICCGetPrefProcInfo           = 65520L,
02908   kICCSetPrefProcInfo           = 65520L,
02909   kICCFindPrefHandleProcInfo    = 16368,
02910   kICCGetPrefHandleProcInfo     = 16368,
02911   kICCSetPrefHandleProcInfo     = 16368,
02912   kICCCountPrefProcInfo         = 1008,
02913   kICCGetIndPrefProcInfo        = 4080,
02914   kICCDeletePrefProcInfo        = 1008,
02915   kICCEndProcInfo               = 240,
02916   kICCGetDefaultPrefProcInfo    = 4080,
02917   kICCEditPreferencesProcInfo   = 1008,
02918   kICCLaunchURLProcInfo         = 262128L,
02919   kICCParseURLProcInfo          = 1048560L,
02920   kICCCreateGURLEventProcInfo   = 16368,
02921   kICCSendGURLEventProcInfo     = 1008,
02922   kICCMapFilenameProcInfo       = 4080,
02923   kICCMapTypeCreatorProcInfo    = 65520L,
02924   kICCMapEntriesFilenameProcInfo = 16368,
02925   kICCMapEntriesTypeCreatorProcInfo = 262128L,
02926   kICCCountMapEntriesProcInfo   = 4080,
02927   kICCGetIndMapEntryProcInfo    = 65520L,
02928   kICCGetMapEntryProcInfo       = 16368,
02929   kICCSetMapEntryProcInfo       = 16368,
02930   kICCDeleteMapEntryProcInfo    = 4080,
02931   kICCAddMapEntryProcInfo       = 4080,
02932   kICCGetCurrentProfileProcInfo = 1008,
02933   kICCSetCurrentProfileProcInfo = 1008,
02934   kICCCountProfilesProcInfo     = 1008,
02935   kICCGetIndProfileProcInfo     = 4080,
02936   kICCGetProfileNameProcInfo    = 4080,
02937   kICCSetProfileNameProcInfo    = 4080,
02938   kICCAddProfileProcInfo        = 4080,
02939   kICCDeleteProfileProcInfo     = 1008,
02940   kICCRequiresInterruptSafeProcInfo = 240,
02941   kICCGetMappingInterruptSafeProcInfo = 4080,
02942   kICCGetSeedInterruptSafeProcInfo = 1008
02943 };
02944 
02945 /************************************************************************************************
02946   component identifiers
02947  ************************************************************************************************/
02948 
02949 enum {
02950   kICComponentType              = FOUR_CHAR_CODE('PREF'),
02951   kICComponentSubType           = FOUR_CHAR_CODE('ICAp'),
02952   kICComponentManufacturer      = FOUR_CHAR_CODE('JPQE')
02953 };
02954 
02955 /************************************************************************************************
02956   The following type is now obsolete.
02957   If you're using it, please switch to ComponentInstance or ICInstance.
02958  ************************************************************************************************/
02959 
02960 #if OLDROUTINENAMES
02961 typedef ComponentInstance               internetConfigurationComponent;
02962 
02963 #endif  /* OLDROUTINENAMES */
02964 
02965 #endif  /* CALL_NOT_IN_CARBON */
02966 
02967 /************************************************************************************************
02968   old names for stuff declared above
02969  ************************************************************************************************/
02970 
02971 #if OLDROUTINENAMES
02972 
02973 typedef long                            ICError;
02974 
02975 enum {
02976   ICattr_no_change              = (unsigned long)(kICAttrNoChange),
02977   ICattr_locked_bit             = kICAttrLockedBit,
02978   ICattr_locked_mask            = kICAttrLockedMask,
02979   ICattr_volatile_bit           = kICAttrVolatileBit,
02980   ICattr_volatile_mask          = kICAttrVolatileMask,
02981   icNoUserInteraction_bit       = kICNoUserInteractionBit,
02982   icNoUserInteraction_mask      = kICNoUserInteractionMask,
02983   ICfiletype                    = kICFileType,
02984   ICcreator                     = kICCreator
02985 };
02986 
02987 /*
02988     ICFileInfo was originally used to define the format of a key.
02989     That key was removed, but we forgot to remove ICFileInfo.
02990     I hope to remove it entirely, but for the moment it's available
02991     if you define OLDROUTINENAMES.
02992 */
02993 struct ICFileInfo {
02994   OSType              fType;
02995   OSType              fCreator;
02996   Str63               name;
02997 };
02998 typedef struct ICFileInfo               ICFileInfo;
02999 typedef ICFileInfo *                    ICFileInfoPtr;
03000 typedef ICFileInfoPtr *                 ICFileInfoHandle;
03001 
03002 enum {
03003   ICfile_spec_header_size       = kICFileSpecHeaderSize
03004 };
03005 
03006 enum {
03007   ICmap_binary_bit              = kICMapBinaryBit,
03008   ICmap_binary_mask             = kICMapBinaryMask,
03009   ICmap_resource_fork_bit       = kICMapResourceForkBit,
03010   ICmap_resource_fork_mask      = kICMapResourceForkMask,
03011   ICmap_data_fork_bit           = kICMapDataForkBit,
03012   ICmap_data_fork_mask          = kICMapDataForkMask,
03013   ICmap_post_bit                = kICMapPostBit,
03014   ICmap_post_mask               = kICMapPostMask,
03015   ICmap_not_incoming_bit        = kICMapNotIncomingBit,
03016   ICmap_not_incoming_mask       = kICMapNotIncomingMask,
03017   ICmap_not_outgoing_bit        = kICMapNotOutgoingBit,
03018   ICmap_not_outgoing_mask       = kICMapNotOutgoingMask,
03019   ICmap_fixed_length            = kICMapFixedLength
03020 };
03021 
03022 enum {
03023   ICservices_tcp_bit            = kICServicesTCPBit,
03024   ICservices_tcp_mask           = kICServicesTCPMask,
03025   ICservices_udp_bit            = kICServicesUDPBit,
03026   ICservices_udp_mask           = kICServicesUDPMask
03027 };
03028 
03029 /*    This definitions are a) very long, and b) don't conform
03030     to Mac OS standards for naming constants, so I've put
03031     them in only if you're using OLDROUTINENAMES.  Please switch
03032     to the new names given above.
03033 */
03034 enum {
03035   internetConfigurationComponentType = FOUR_CHAR_CODE('PREF'), /* the component type */
03036   internetConfigurationComponentSubType = FOUR_CHAR_CODE('ICAp'), /* the component subtype */
03037   internetConfigurationComponentInterfaceVersion0 = 0x00000000, /* IC >= 1.0 */
03038   internetConfigurationComponentInterfaceVersion1 = 0x00010000, /* IC >= 1.1 */
03039   internetConfigurationComponentInterfaceVersion2 = 0x00020000, /* IC >= 1.2 */
03040   internetConfigurationComponentInterfaceVersion3 = 0x00030000, /* IC >= 2.0 */
03041                                         /* current version number is version 3 */
03042   internetConfigurationComponentInterfaceVersion = internetConfigurationComponentInterfaceVersion3
03043 };
03044 
03045 #endif  /* OLDROUTINENAMES */
03046 
03047 
03048 #if PRAGMA_STRUCT_ALIGN
03049     #pragma options align=reset
03050 #elif PRAGMA_STRUCT_PACKPUSH
03051     #pragma pack(pop)
03052 #elif PRAGMA_STRUCT_PACK
03053     #pragma pack()
03054 #endif
03055 
03056 #ifdef PRAGMA_IMPORT_OFF
03057 #pragma import off
03058 #elif PRAGMA_IMPORT
03059 #pragma import reset
03060 #endif
03061 
03062 #ifdef __cplusplus
03063 }
03064 #endif
03065 
03066 #endif /* __INTERNETCONFIG__ */
03067 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
