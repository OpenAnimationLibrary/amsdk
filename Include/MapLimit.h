//RC  12/23/1999  \Randy85\Include\MapLimit.h
#pragma once

enum MapLimit {
    ML_1,
    ML_2,
    ML_4,
    ML_8,
    ML_16,
    ML_32,
    ML_64,
    ML_128,
    ML_256,
    ML_512,
    ML_1024,
    ML_2048,
    ML_4096,
    ML_8192
};

HASH_INLINE int MLToInt(const MapLimit &ml) noexcept {
    switch (ml) {
        case ML_1:
            return 1;
        case ML_2:
            return 2;
        case ML_4:
            return 4;
        case ML_8:
            return 8;
        case ML_16:
            return 16;
        case ML_32:
            return 32;
        case ML_64:
            return 64;
        case ML_128:
            return 128;
        case ML_256:
            return 256;
        case ML_512:
            return 512;
        case ML_1024:
            return 1024;
        case ML_2048:
            return 2048;
        case ML_4096:
            return 4096;
        case ML_8192:
            return 8192;
    }
    return 4;
}
