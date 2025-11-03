<div class="tabs">

- <span id="current">[Main Page](index.md)</span>
- [Classes](annotated.md)
- [Files](files.md)
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

# A:M SDK v12.0 Documentation

### 1

## <span id="intro" class="anchor">intro</span>

This documentation is a collection of notes collected from previously supplied documentation for previous SDKs that I've adapted to the new SDK, reformatted answer to SDK related questions from Hash Inc and explanations and documentation supplied by other members of the A:M SDK developers community.

## <span id="contributors" class="anchor">People who have contributed explanations,</span>

documentations and source examples (in family name alphabetical order):

Hash Inc

Marcel Bricman  
Steffen Gross  
Yves Poissant  
Mark Thompson  
Dan Tiedy  
Howard Trickey

## <span id="discussion" class="anchor">SDK related Forum</span>

Thanks to all the members of the am-dev discussion group and now the members of the Hash SDK forum who have contributed through questions and answers.

The place where to discuss any SDK related questions is the Hash SDK forum at <http://www.hash.com/forums/index.php> And select the "SDK" forum

Also, Marcel Bricman have setup a sort of forum designed specifically to structure developer notes as they use the classes and functions of the SDK. The forum is structured according to classes::function names. See <http://www.kci-group.com/cgi-bin/gfo/gfo.pl?amsdk>

## <span id="vcsetup" class="anchor">How to setup a Visual C++ project for A:M plugins</span>

See the tutorial provided by Steffen Gross at <http://www.sgross.com/tutorial/plugin_erstellung/create.html>

Currently, developing plugins can be made on a Windows platform and on a Macintosh platform.

On Windows platform, the development environment is Visual C++ v6 or v7 (.NET). For some plugins types, such as some <a href="classImageIO.md" class="el">ImageIO</a> plugins, that must link to the OpenEXR library, VS7 is the only option. Otherwise, VS6 will work just as well.

On Macintosh platform, the development environment is Apple XCode. XCode is free and can be downloaded from the Apple developer connection web site at <http://developer.apple.com/> You will also need to install our MSDEV library that is included in the Mac version of the SDK.

The old way to port plugins to the Macintosh is still valid. This is how Hash proceeds:  
We use the Microsoft VC++ Cross Compiler for Mac. That allows us to take plugins written for Windows, make some changes to the makefile, and recompile them for the Mac. Occasionally, they require a little more work for the cross compiler to digest them, or make Mac API calls when the code calls Windows APIs that aren't in the portability library.

The VC++ Cross compiler for Mac is an old, very old product from Microsoft that is no longer supported nor available. Those who already own it can still use it though.

Also note that you will need a dongle version of A:M in order to be able to debug your plugins. The CD-ROM version of A:M will not run if the debugger is loaded.

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
