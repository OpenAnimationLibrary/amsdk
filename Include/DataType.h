//RC  4/24/2002  \HRandy95\Include\DataType.h
#pragma once

#ifndef UBYTE
typedef unsigned char UBYTE; //0 to 255
#endif
#ifndef SBYTE
typedef signed char SBYTE;   //-128 to 127
#endif
#ifndef USHORT
typedef unsigned short USHORT; //0 to 65,535
#endif
#ifndef SSHORT
typedef signed short SSHORT;   //-32,768 to 32,767
#endif
#ifndef BITFIELDS8
typedef unsigned char BITFIELDS8;
#endif
#ifndef BITFIELDS16
typedef unsigned short BITFIELDS16;
#endif
#ifndef BITFIELDS32
typedef unsigned long BITFIELDS32;
#endif
#ifndef FRECT
typedef struct FRECT {
    float left{0.F};
    float top{0.F};
    float right{0.F};
    float bottom{0.F};
} FRECT;
#endif