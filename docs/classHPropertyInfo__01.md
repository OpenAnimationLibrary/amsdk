## Detailed Description

Father class for all property UI contexts.

Classes under HPropertyInfo are used to supply a UI context for corresponding <a href="classHProperty.md" class="el">HProperty</a> classes to be set and manipulated by the user in the PWS. Since the UI context is the same for each instance which uses the same property, the HPropertyInfo derived classes should be declared inside the application class. In other words inside the InitInstance of the CWinApp derived class.

**Note:**  
In order for the HPropertyInfo derived classes and their associated <a href="classHProperty.md" class="el">HProperty</a> derived classes property to show in the property panel of the PWS, the associated <a href="classHProperty.md" class="el">HProperty</a> must be assigned an index through the <a href="classDLLPlugin.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">DLLPlugin::GetPropertyAt</a>.

<!-- -->

**See also:**  
<a href="classHProperty.md" class="el">HProperty</a>, <a href="classDLLPlugin.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">DLLPlugin::GetPropertyAt</a>

Definition at line <a href="HPropert_8h-source.md#l00023" class="el">23</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

