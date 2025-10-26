        ICMapEntryHandle;
00319 
00320 #else
00321 struct ICMapEntry {
00322   short               total_length;
00323   ICFixedLength       fixed_length;
00324   short               version;
00325   OSType              file_type;
00326   OSType              file_creator;
00327   OSType              post_creator;
00328   ICMapEntryFlags     flags;
00329   Str255              extension;
00330   Str255              creator_app_name;
00331   Str255              post_app_name;
00332   Str255              MIME_type;
00333   Str255              entry_name;
00334 };
00335 typedef struct ICMapEntry               ICMapEntry;
00336 typedef ICMapEntry *                    ICMapEntryPtr;
00337 typedef ICMapEntryPtr *                 ICMapEntryHandle;
00338 #endif  /* !OLDROUTINENAMES */
00339 
00340 enum {
00341   kICMapFixedLength             = 22    /* number in fixedLength field*/
00342 };
00343 
00344 enum {
00345   kICMapBinaryBit               = 0,    /* file should be transfered in binary as opposed to text mode*/
00346   kICMapResourceForkBit         = 1,    /* the resource fork of the file is significant*/
00347   kICMapDataForkBit             = 2,    /* the data fork of the file is significant*/
00348   kICMapPostBit                 = 3,    /* post process using post fields*/
00349   kICMapNotIncomingBit          = 4,    /* ignore this mapping for incoming files*/
00350   kICMapNotOutgoingBit          = 5     /* ignore this mapping for outgoing files*/
00351 };
00352 
00353 enum {
00354   kICMapBinaryMask              = 0x00000001, /* file should be transfered in binary as opposed to text mode*/
00355   kICMapResourceForkMask        = 0x00000002, /* the resource fork of the file is significant*/
00356   kICMapDataForkMask            = 0x00000004, /* the data fork of the file is significant*/
00357   kICMapPostMask                = 0x00000008, /* post process using post fields*/
00358   kICMapNotIncomingMask         = 0x00000010, /* ignore this mapping for incoming files*/
00359   kICMapNotOutgoingMask         = 0x00000020 /* ignore this mapping for outgoing files*/
00360 };
00361 
00362 /************************************************************************************************
00363   types and constants for use with kICServices, et. al.
00364  ************************************************************************************************/
00365 typedef short                           ICServiceEntryFlags;
00366 struct ICServiceEntry {
00367   Str255              name;
00368   short               port;
00369   ICServiceEntryFlags  flags;
00370 };
00371 typedef struct ICServiceEntry           ICServiceEntry;
00372 typedef ICServiceEntry *                ICServiceEntryPtr;
00373 typedef ICServiceEntryPtr *             ICServiceEntryHandle;
00374 
00375 enum {
00376   kICServicesTCPBit             = 0,
00377   kICServicesUDPBit             = 1     /* both bits can be set, which means the service is both TCP and UDP, eg daytime*/
00378 };
00379 
00380 enum {
00381   kICServicesTCPMask            = 0x00000001,
00382   kICServicesUDPMask            = 0x00000002 /* both bits can be set, which means the service is both TCP and UDP, eg daytime*/
00383 };
00384 
00385 struct ICServices {
00386   short               count;
00387   ICServiceEntry      services[1];
00388 };
00389 typedef struct ICServices               ICServices;
00390 typedef ICServices *                    ICServicesPtr;
00391 typedef ICServicesPtr *                 ICServicesHandle;
00392 
00393 /************************************************************************************************
00394   default file name, for internal use, overridden by a component resource
00395  ************************************************************************************************/
00396 
00397 #if CALL_NOT_IN_CARBON
00398 #define kICDefaultFileName              "\pInternet Preferences"
00399 #endif  /* CALL_NOT_IN_CARBON */
00400 
00401 /************************************************************************************************
00402   keys
00403  ************************************************************************************************/
00404 /* 
00405     key reserved for use by Internet Config 
00406 */
00407 #define kICReservedKey                  "\pkICReservedKey"
00408 /*
00409     STR# -- formatted, list of Archie servers  
00410 */
00411 #define kICArchieAll                    "\pArchieAll"
00412 /*
00413     PString -- formatted, preferred Archie server   
00414 */
00415 #define kICArchiePreferred              "\pArchiePreferred"
00416 /*
00417     ICCharTable -- Mac-to-Net and Net-to-Mac character translation   
00418 */
00419 #define kICCharacterSet                 "\pCharacterSet"
00420 /*
00421     ICFontRecord -- font used for proportional text   
00422 */
00423 #define kICDocumentFont                 "\pDocumentFont"
00424 /*
00425     ICFileSpec -- where to put newly downloaded files   
00426 */
00427 #define kICDownloadFolder               "\pDownloadFolder"
00428 /*
00429     PString -- user@host.domain, email address of user, ie return address   
00430 */
00431 #define kICEmail                        "\pEmail"
00432 /*
00433     PString -- host.domain, default FTP server   
00434 */
00435 #define kICFTPHost                      "\pFTPHost"
00436 /*
00437     PString -- second level FTP proxy authorisation   
00438 */
00439 #define kICFTPProxyAccount              "\pFTPProxyAccount"
00440 /*
00441     PString -- host.domain   
00442 */
00443 #define kICFTPProxyHost                 "\pFTPProxyHost"
00444 /*
00445     PString -- scrambled, password for FTPProxyUser   
00446 */
00447 #define kICFTPProxyPassword             "\pFTPProxyPassword"
00448 /*
00449     PString -- first level FTP proxy authorisation   
00450 */
00451 #define kICFTPProxyUser                 "\pFTPProxyUser"
00452 /*
00453     PString -- host.domain, default finger server   
00454 */
00455 #define kICFingerHost                   "\pFingerHost"
00456 /*
00457     PString -- host.domain, default Gopher server   
00458 */
00459 #define kICGopherHost                   "\pGopherHost"
00460 /*
00461     PString -- host.domain, see note in Prog Docs   
00462 */
00463 #define kICGopherProxy                  "\pGopherProxy"
00464 /*
00465     PString -- host.domain   
00466 */
00467 #define kICHTTPProxyHost                "\pHTTPProxyHost"
00468 /*
00469     ICAppSpec -- helpers for URL schemes   
00470 */
00471 #define kICHelper                       "\pHelper¥"
00472 /*
00473     PString -- description for URL scheme   
00474 */
00475 #define kICHelperDesc                   "\pHelperDesc¥"
00476 /*
00477     ICAppSpecList -- list of common helpers for URL schemes   
00478 */
00479 #define kICHelperList                   "\pHelperList¥"
00480 /*
00481     PString -- host.domain, Internet Relay Chat server   
00482 */
00483 #define kICIRCHost                      "\pIRCHost"
00484 /*
00485     STR# -- formatted, list of Info-Mac servers   
00486 */
00487 #define kICInfoMacAll                   "\pInfoMacAll"
00488 /*
00489     PString -- formatted, preferred Info-Mac server   
00490 */
00491 #define kICInfoMacPreferred             "\pInfoMacPreferred"
00492 /*
00493     PString -- string LDAP thing   
00494 */
00495 #define kICLDAPSearchbase               "\pLDAPSearchbase"
00496 /*
00497     PString -- host.domain   
00498 */
00499 #define kICLDAPServer                   "\pLDAPServer"
00500 /*
00501     ICFontRecord -- font used for lists of items (eg news article lists)   
00502 */
00503 #define kICListFont                     "\pListFont"
00504 /*
00505     PString -- host for MacSearch queries   
00506 */
00507 #define kICMacSearchHost                "\pMacSearchHost"
00508 /*
00509     PString -- user@host.domain, account from which to fetch mail   
00510 */
00511 #define kICMailAccount                  "\pMailAccount"
00512 /*
00513     TEXT -- extra headers for mail messages   
00514 */
00515 #define kICMailHeaders                  "\pMailHeaders"
00516 /*
00517     PString -- scrambled, password for MailAccount   
00518 */
00519 #define kICMailPassword                 "\pMailPassword"
00520 /*
00521     ICMapEntries -- file type mapping, see documentation   
00522 */
00523 #define kICMapping                      "\pMapping"
00524 /*
00525     PString -- host.domain, NNTP server   
00526 */
00527 #define kICNNTPHost                     "\pNNTPHost"
00528 /*
00529     PString -- host.domain, Network Time Protocol (NTP)   
00530 */
00531 #define kICNTPHost                      "\pNTPHost"
00532 /*
00533     Boolean   
00534 */
00535 #define kICNewMailDialog                "\pNewMailDialog"
00536 /*
00537     Boolean -- how to announce new mail   
00538 */
00539 #define kICNewMailFlashIcon             "\pNewMailFlashIcon"
00540 /*
00541     Boolean   
00542 */
00543 #define kICNewMailPlaySound             "\pNewMailPlaySound"
00544 /*
00545     PString   
00546 */
00547 #define kICNewMailSoundName             "\pNewMailSoundName"
00548 /*
00549     PString -- scrambled, password for NewsAuthUsername   
00550 */
00551 #define kICNewsAuthPassword             "\pNewsAuthPassword"
00552 /*
00553     PString -- user name for authorised news servers   
00554 */
00555 #define kICNewsAuthUsername             "\pNewsAuthUsername"
00556 /*
00557     TEXT -- extra headers for news messages   
00558 */
00559 #define kICNewsHeaders                  "\pNewsHeaders"
00560 /*
00561     STR# -- list of domains not to be proxied   
00562 */
00563 #define kICNoProxyDomains               "\pNoProxyDomains"
00564 /*
00565     PString -- for X-Organization string   
00566 */
00567 #define kICOrganization                 "\pOrganization"
00568 /*
00569     PString -- host.domain, default Ph server   
00570 */
00571 #define kICPhHost                       "\pPhHost"
00572 /*
00573     TEXT -- default response for finger servers   
00574 */
00575 #define kICPlan                         "\pPlan"
00576 /*
00577     ICFontRecord -- font used to print ScreenFont   
00578 */
00579 #define kICPrinterFont                  "\pPrinterFont"
00580 /*
00581     PString -- used to quote responses in news and mail   
00582 */
00583 #define kICQuotingString                "\pQuotingString"
00584 /*
00585     PString -- real name of user   
00586 */
00587 #define kICRealName                     "\pRealName"
00588 /*
00589     PString -- RTSP Proxy Host
00590 */
00591 #define kICRTSPProxyHost                "\pRTSPProxyHost"
00592 /*
00593     PString -- host.domain, SMTP server   
00594 */
00595 #define kICSMTPHost                     "\pSMTPHost"
00596 /*
00597     ICFontRecord -- font used for monospaced text (eg news articles)   
00598 */
00599 #define kICScreenFont                   "\pScreenFont"
00600 /*
00601     ICServices -- TCP and IP port-to-name mapping   
00602 */
00603 #define kICServices                     "\pServices"
00604 /*
00605     TEXT -- append to news and mail messages   
00606 */
00607 #define kICSignature                    "\pSignature"
00608 /*
00609     TEXT -- preferred mailing address   
00610 */
00611 #define kICSnailMailAddress             "\pSnailMailAddress"
00612 /*
00613     PString -- host.domain, remember that host.domain format allows ":port" and " port"  
00614 */
00615 #define kICSocksHost                    "\pSocksHost"
00616 /*
00617     PString -- host.domain, default Telnet address   
00618 */
00619 #define kICTelnetHost                   "\pTelnetHost"
00620 /*
00621     STR# -- formatted, list of UMich servers   
00622 */
00623 #define kICUMichAll                     "\pUMichAll"
00624 /*
00625     PString -- formatted, preferred UMich server   
00626 */
00627 #define kICUMichPreferred               "\pUMichPreferred"
00628 /*
00629     Boolean   
00630 */
00631 #define kICUseFTPProxy                  "\pUseFTPProxy"
00632 /*
00633     Boolean   
00634 */
00635 #define kICUseGopherProxy               "\pUseGopherProxy"
00636 /*
00637     Boolean   
00638 */
00639 #define kICUseHTTPProxy                 "\pUseHTTPProxy"
00640 /*
00641     Boolean -- use PASV command for FTP transfers   
00642 */
00643 #define kICUsePassiveFTP                "\pUsePassiveFTP"
00644 /*
00645     Boolean
00646 */
00647 #define kICUseRTSPProxy                 "\pUseRTSPProxy"
00648 /*
00649     Boolean   
00650 */
00651 #define kICUseSocks                     "\pUseSocks"
00652 /*
00653     PString -- no idea   
00654 */
00655 #define kICWAISGateway                  "\pWAISGateway"
00656 /*
00657     PString -- URL, users default WWW page   
00658 */
00659 #define kICWWWHomePage                  "\pWWWHomePage"
00660 /*
00661     RGBColor -- background colour for web pages   
00662 */
00663 #define kICWebBackgroundColour          "\pWebBackgroundColour"
00664 /*
00665     RGBColor -- colour for read links   
00666 */
00667 #define kICWebReadColor                 "\p646F6777¥WebReadColor"
00668 /*
00669     PString -- URL, users default search page   
00670 */
00671 #define kICWebSearchPagePrefs           "\pWebSearchPagePrefs"
00672 /*
00673     RGBColor -- colour for normal text   
00674 */
00675 #define kICWebTextColor                 "\pWebTextColor"
00676 /*
00677     Boolean -- whether to underline links   
00678 */
00679 #define kICWebUnderlineLinks            "\p646F6777¥WebUnderlineLinks"
00680 /*
00681     RGBColor -- colour for unread links   
00682 */
00683 #define kICWebUnreadColor               "\p646F6777¥WebUnreadColor"
00684 /*
00685     PString -- host.domain, default whois server   
00686 */
00687 #define kICWhoisHost                    "\pWhoisHost"
00688 
00689 /************************************************************************************************
00690 
00691       FUNCTIONS
00692 
00693       What do the annotations after each API mean?
00694       --------------------------------------------
00695 
00696       [r1] Requires IC 1.1 or higher.
00697       [r2] Requires IC 1.2 or higher.
00698       [r3] Requires IC 2.0 or higher.
00699       [r4] Requires IC 2.5 or higher.
00700       
00701       IMPORTANT:
00702 
00703       In IC 2.5, instances automatically use the default configuration.
00704       You no longer need to configure an instance explicitly, except
00705       if your code might run with an older version of IC.  So the following
00706       notes only apply to IC 2.0 and earlier.
00707 
00708       [c1]  You must have specified a configuration before calling this routine.
00709       
00710       [c2]  You must have specified the default configuration before calling this
00711             routine.
00712       
00713       [c3]  You do not need to specify a configuration before calling this routine.
00714       
00715       [b1]  You must be inside a Begin/End pair when calling this routine.
00716       
00717       [b2]  You must be inside a Begin/End read/write pair when calling this routine.
00718       
00719       [b3]  Yo