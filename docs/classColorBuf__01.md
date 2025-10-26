## Detailed Description

Simple RGB and RGBA color buffer where R, G, B and A are represented by byte values. Same as what is stored in the TGA files.

**Note:**  
ColorBuf is also used to represent depth buffers. The Depth buffer files created by Animation Master are simply a 32-bit Targa (.tga) file. The four color components (Red, Green, Blue, Alpha) and the 4 bytes that make up the 32 bit floating point depth value. Here is a code snipet on how to convert the four bytes into a float.

<div class="fragment">

``` fragment
inline float RGBAToDepth(UBYTE red, UBYTE green, UBYTE blue, UBYTE alpha)
{
   float *fptr;
   DWORD value;

   value = (DWORD)(alpha << 24 | red << 16 | green << 8 | blue);
   fptr = (float *)&value;
   return *fptr;
}
```

</div>

**Note:**  
And ColorBuf is also used to represent normals. Normal buffer files are also a 32-bit Targa file. The four components make up the normal vector of the surface. To calculate normal, z=sqrt(1-X\*X-Y\*Y); Here is a code snipet on how to convert the four bytes into a normal.

<div class="fragment">

``` fragment
inline Vector RGBAToVector(UBYTE red, UBYTE green, UBYTE blue, UBYTE alpha)
{
   signed short value;
   Vector v;

   value = (signed short)(green << 8 | red);
   v.x = (float)value/32768;

   value = (signed short)(alpha << 8 | blue);
   v.y = (float)value/32768;

   // since the vector is normalized, z can be computed
   v.z = sqrt(1-v.x*v.x-v.y*v.y);
   return v;
}
```

</div>

**Note:**  
The FLM is nothing more than a 32 bit TARGA file. So you can use any tga loader to load the image.

Once the TGA is loaded you can use the rbga byte values to get to a floating point value. Here is how:

red : 11, green : 11, blue : 10;

The 4 rgba bytes represent a long in that order.. The first 11 bits are the red component, the second 11 bits are the green component and the last 10 bits are the blue component. You could create a class like this:

<div class="fragment">

``` fragment
class Color {
public:
   union {
      struct {
         ULONG   m_red : 11,
                 m_green: 11,
                 m_blue : 10;
      };
      UBYTE m_r, m_g, m_b, m_a;
   };

};

#define MAXCOLOR33 2047
```

</div>

You could then make a Set(...) member function that would set the m_r, m_g, m_b, m_a values from the TGA file, and a Get member function that would:

<div class="fragment">

``` fragment
Color::Get(float &r, float &g, float &b ) const
{
   r = (float)m_red/MAXCOLOR33;
   g = (float)m_green/MAXCOLOR33;
   b = (float)m_blue/(MAXCOLOR33/2);
}
```

</div>

Definition at line <a href="ColorBuf_8h-source.md#l00039" class="el">39</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.

------------------------------------------------------------------------

