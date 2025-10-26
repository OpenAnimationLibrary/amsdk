<div class="tabs">

- [Main Page](index.md)
- <span id="current">[Classes](annotated.md)</span>
- [Files](files.md)
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [Class List](annotated.md)
- [Alphabetical List](classes.md)
- [Class Hierarchy](hierarchy.md)
- [Class Members](functions.md)

</div>

# HModelCache Class Reference

`#include <`<a href="HModel_8h-source.md" class="el"><code>HModel.h</code></a>`>`

Inheritance diagram for HModelCache:

<span class="image placeholder" original-image-src="classHModelCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HModelCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HModelCache:

<span class="image placeholder" original-image-src="classHModelCache__coll__graph.gif" original-image-title="" border="0" usemap="#HModelCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHModelCache-members.md)

<table data-border="0" data-cellpadding="0" data-cellspacing="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td></td>
<td></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFileInfoProperty.md" class="el">HFileInfoProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#5158778c75932b3f5cce79855150386f" class="el">GetFileInfo</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#b092f4dc2c9bdb7c92b4d4b1c90e2c37" class="el">GetAttr</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHModelCache.md" class="el">HModelCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#009a33486a3d230dceeea2e4a7c0fa04" class="el">GetSiblingModelCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHObjectCacheContainer.md" class="el">HObjectCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#5216acd2cfa155ff2e19f6212d57e140" class="el">GetParentObjectCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEPatchModel.md" class="el">IEPatchModel</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#48d1e14b70895baa8e21bb74074152f4" class="el">BuildExportModel</a> (<a href="classIEModelParms.md" class="el">IEModelParms</a> *iemp, const char *modelmapfilename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEPolyModel.md" class="el">IEPolyModel</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#884009ddaf9a12edc15dc05801123d73" class="el">BuildExportModel</a> (<a href="classIEPolyModelParms.md" class="el">IEPolyModelParms</a> *iemp, const char *modelmapfilename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#f70e5f4d9b79352700c45da1ea3910ea" class="el">MergeIEModel</a> (<a href="classIEPatchModel.md" class="el">IEPatchModel</a> *model, const char *name, float peaktolerance, BOOL addgroup, BOOL showprogressbar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#f3c5dcbce604324f929a33f1ea9aa45a" class="el">MergeIEModel</a> (<a href="classIEPolyModel.md" class="el">IEPolyModel</a> *model, const char *name, float peaktolerance, BOOL addgroup, BOOL showprogressbar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHModel.md" class="el">HModel</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#5ae587b117fac3011b74cdcf10606bdd" class="el">NewInstance</a> (<a href="classHChor.md" class="el">HChor</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#0d2a874c7c7e4f27501d024babf73b7e" class="el">SetChanged</a> (BOOL modified=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#dd680dcb93a96827528e1499d8b353cf" class="el">GetHeadSpline</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#9d4e613a9fceb4c9caf20b5b08fbb91b" class="el">CreateSpline</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#54946ba93d9b3b704f8bec9eb695fd66" class="el">DeleteSpline</a> (<a href="classHSpline.md" class="el">HSpline</a> *spline)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#3274cac44dceb79feb800a2740b72cfa" class="el">AttachCPs</a> (<a href="classHCP.md" class="el">HCP</a> *cp1, <a href="classHCP.md" class="el">HCP</a> *cp2)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#04a3514a8a2555882dfaea1e07f22293" class="el">AttachHook</a> (<a href="classHCP.md" class="el">HCP</a> *cp1, <a href="classHCP.md" class="el">HCP</a> *cp2, float s)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#cfd844a8aa1817b4a0da30a7779decd2" class="el">StartSpline</a> (<a href="classVector.md" class="el">Vector</a> *p1, <a href="classVector.md" class="el">Vector</a> *p2)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#0adf64967594d26c3c57a82b12eadaa6" class="el">AddCP</a> (<a href="classHCP.md" class="el">HCP</a> *cp, <a href="classVector.md" class="el">Vector</a> *p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#37d91e56daf6f36c331ffd4742b93c2f" class="el">InsertCP</a> (<a href="classHCP.md" class="el">HCP</a> **cpuplink, <a href="classHCP.md" class="el">HCP</a> *cp, <a href="classVector.md" class="el">Vector</a> *p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#3ca9a1702657494cf758c905c90b125b" class="el">DeleteCP</a> (<a href="classHCP.md" class="el">HCP</a> **cpuplink, <a href="classHCP.md" class="el">HCP</a> *matchcp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#81689c896bfdda6a29b2ca764db49ee2" class="el">BreakSpline</a> (<a href="classHCP.md" class="el">HCP</a> *cp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#29234ade793472034a65bf90f80c9af8" class="el">Make5PointPatch</a> (<a href="classHGroup.md" class="el">HGroup</a> *group)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#eacc9e81ded8f76fa862155959dc467b" class="el">Make5PointPatch</a> (<a href="classHCP.md" class="el">HCP</a> *cp1, <a href="classHCP.md" class="el">HCP</a> *cp2, <a href="classHCP.md" class="el">HCP</a> *cp3, <a href="classHCP.md" class="el">HCP</a> *cp4, <a href="classHCP.md" class="el">HCP</a> *cp5)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#2d35b860c39a26b9b4ec4e5a48bc2662" class="el">CopyExtrude</a> (BOOL extrude, <a href="classHGroupCP.md" class="el">HGroupCP</a> *grouptocopy, <a href="classHGroupCP.md" class="el">HGroupCP</a> **newgroup)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">This function can perform two different operations. It can copy or extrude a group. <a href="#2d35b860c39a26b9b4ec4e5a48bc2662"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHSegmentCache.md" class="el">HSegmentCache</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#0c31ead7f3f8068e74a36881cea3ad61" class="el">AddSegment</a> (<a href="classHBoneCache.md" class="el">HBoneCache</a> *parentbonecache, <a href="classHBoneCache.md" class="el">HBoneCache</a> *afterbonecache, <a href="classString.md" class="el">String</a> &amp;name, COLORREF color)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#a9a22a1f46e5d7b02571fa99cabdb4ae" class="el">CountBones</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#931f4a900a59171fe3089af15a767151" class="el">AddToTemporaryGroup</a> (<a href="classHGroupCP.md" class="el">HGroupCP</a> *gh)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHGroup.md" class="el">HGroup</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#3457f3925a645b56a1071cad97e0c2b8" class="el">CreateGroup</a> (const <a href="classString.md" class="el">String</a> &amp;name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#e7b1da659f4edf4341f82531d66602b5" class="el">FindPatches</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch.md" class="el">HPatch</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#1b363b3b90cae623ff02bec2907d2bed" class="el">FindPatch</a> (<a href="classHCP.md" class="el">HCP</a> *cp1, <a href="classHCP.md" class="el">HCP</a> *cp2, <a href="classHCP.md" class="el">HCP</a> *cp3, <a href="classHCP.md" class="el">HCP</a> *cp4)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch5.md" class="el">HPatch5</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#08c6fbaf2184d17c67eff6f086b5591d" class="el">FindPatch</a> (<a href="classHCP.md" class="el">HCP</a> *cp1, <a href="classHCP.md" class="el">HCP</a> *cp2, <a href="classHCP.md" class="el">HCP</a> *cp3, <a href="classHCP.md" class="el">HCP</a> *cp4, <a href="classHCP.md" class="el">HCP</a> *cp5)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#22831636d94524c0c9e928f70d3c3e70" class="el">GetPatchCount</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch.md" class="el">HPatch</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#186073d066006bb3e7d242730cdaf54f" class="el">GetPatch</a> (UINT index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch5.md" class="el">HPatch5</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#0671af5a7584f064d07b3a2a064edd97" class="el">GetHeadPatch5</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecal.md" class="el">HDecal</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#a02eeaa5a8558bf3b9dc55ac177ca914" class="el">AddDecal</a> (<a href="classHClip.md" class="el">HClip</a> *clipcache=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalContainer.md" class="el">HDecalContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#5d06968c9ed87e4d5a8956df5feb005b" class="el">GetChildDecalContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHGroupContainer.md" class="el">HGroupContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#57fb59ebac9c3df87f0abb9121fabc37" class="el">GetChildGroupContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoneCacheContainer.md" class="el">HBoneCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#c8469212b010d0cff6c7b68988867b3e" class="el">GetChildBoneCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHLightCacheContainer.md" class="el">HLightCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHModelCache.md#99bb574cd972147c2586bf1d5f73f3ca" class="el">GetChildLightCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHSplineContainer.md" class="el">HSplineContainer</a> * </td>
<td 