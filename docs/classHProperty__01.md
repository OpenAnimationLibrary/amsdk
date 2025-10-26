## Detailed Description

Father class for all property holder classes.

Classes under HProperty hold the actual property information. In other words, holds the actual values of the property. Since each instance of a plugin holds different values for the same property, the HProperty derived classes should be declared inside the instance and not inside the application as is the case for <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> derived classes

HProperty and its derived classes are used to transfer values between the pluging application and the user interface. Hproperty derived classes only hold the value. Their UI manipulation context is supplied through an associated <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> derived class.

**Note:**  
In order for the HProperty derived class property to show in the property panel of the PWS, the HProperty must be assigned an index through the <a href="classDLLPlugin.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">DLLPlugin::GetPropertyAt</a>.

<!-- -->

**See also:**  
<a href="classHPropertyInfo.md" class="el">HPropertyInfo</a>, <a href="classDLLPlugin.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">DLLPlugin::GetPropertyAt</a>

Definition at line <a href="HPropert_8h-source.md#l00082" class="el">82</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

