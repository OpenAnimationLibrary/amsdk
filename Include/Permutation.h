//Yves  11-20-2006  Master14.0\Include\Permutation.h
#pragma once

class Permutation final {
    int n[4] = {0, 1, 2, 3};
public:
    Permutation() noexcept {
        ASSERT(false);
        for (int i = 0; i < 4; ++i) {
            n[i] = i;
        }
    }

    int operator [](const int index) const noexcept {
        ASSERT(index < 4);
        return n[index];
    }

    void Swap(const int i, const int j) noexcept {
        if (i == j)
            return;
        const int t = n[i];
        n[i] = n[j];
        n[j] = t;
    }
};
