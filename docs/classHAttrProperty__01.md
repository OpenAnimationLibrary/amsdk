## Detailed Description

This is where the surface attributes are stored. Initially, the HAttrProperties are filled with the surpace properties as entered by the user in the PWS "Surface" properties. Then, the HAttrProperty is filled with the values that came back from the previous plugins's Evaluate calls. It is up to you whether you combine with what's there or strictly overwrite the contents.

All Get... functions will always return a pointer to a property. To determine if the property have a value you must call the property's <a href="classHProperty.md#bbdda942caac43d3abb79c31ec881793" class="el">IsNull()</a> function.

Definition at line <a href="HPropert_8h-source.md#l00233" class="el">233</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.

------------------------------------------------------------------------

