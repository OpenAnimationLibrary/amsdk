## Detailed Description

Base class for all textures.

To write a texture plug-in for Animation Master you must derive a class from the Texture class provided in "Texture.h". The derivation should look something like this:

<div class="fragment">

``` fragment
class MyCoolTexture : public Texture; 
```

</div>

Once you have declared your new class, you can begin overriding the virtual functions found in the Texture base class or in the <a href="classDLLPlugin.md" class="el">DLLPlugin</a> base class. You will need to override nearly every function in the base classs to have a completely functional new texture.

Definition at line <a href="Texture_8h-source.md#l00016" class="el">16</a> of file <a href="Texture_8h-source.md" class="el">Texture.h</a>.

------------------------------------------------------------------------

