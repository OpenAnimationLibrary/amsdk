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

# HDynamicCategoryProperty Class Reference

Property used to dynamically group several other related properties into a group. Used by HXT type plugins. [More...](#_details)

|     |
|-----|
|     |

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Property used to dynamically group several other related properties into a group. Used by HXT type plugins.

The main difference between this class and the <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a> is HDynamicCategoryProperties know how to recreate themselves when an object like a model gets loaded.

HDynamicCategoryProperties are used in HXT plugins. For instance if you look at MyProperties plugin. This plugin allows you to add properties to any object in Animation Master. So lets say I added a property to a <a href="classHGroup.md" class="el">HGroup</a> called "Friction". The Property Fiction resides under a HDynamicPropertyCategory (plugin property) passed into the Entry Point :

<div class="fragment">

``` fragment
extern "C" __declspec(dllexport) BOOL HxtOnAddProperties(HTreeObject *htreeobject, HDynamicCategoryProperty *pluginproperty, UINT index)
```

</div>

When the model is saved it saves enough information so when the model is reloaded the property will be recreated even if the computer does not have the HXT plugin.

**Note:**  
For any plugin deriving off of <a href="classDLLPlugin.md" class="el">DLLPlugin</a>, always use <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a> because the <a href="classTexture.md" class="el">Texture</a>, <a href="classVolumetric.md" class="el">Volumetric</a>, <a href="classTurbulence.md" class="el">Turbulence</a>, ..., plugins create (new) their HProperties in their constructor.

<!-- -->

**See also:**  
<a href="classHCategoryProperty.md" class="el">HCategoryProperty</a>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Dox/SDK/Comments/<a href="Property_8dox.md" class="el">Property.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
