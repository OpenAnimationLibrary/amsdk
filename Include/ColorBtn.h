//Dan  7/23/2004  \DanLP115\Include\ColorBtn.h
#pragma once

#include "Exports.h"
#include "DataType.h"
#include "RGBFloat.inl"//member

class SECWellButton;

class PLUGINEXPORT HashColorBtn final {
public:
    SECWellButton *btn{nullptr};

    explicit HashColorBtn(UINT id);
    ~HashColorBtn();

    HashColorBtn(const HashColorBtn &) = delete;
    HashColorBtn(HashColorBtn &&) = delete;
    HashColorBtn &operator=(const HashColorBtn &) = delete;
    HashColorBtn &operator=(HashColorBtn &&) = delete;

    [[nodiscard]] RGBFloat GetColor() const;
    void SetColor(RGBFloat col) const;
    [[nodiscard]] COLORREF GetColorRef() const;
    void SetColorRef(COLORREF col) const;
    [[nodiscard]] UBYTE GetRed() const;
    [[nodiscard]] UBYTE GetGreen() const;
    [[nodiscard]] UBYTE GetBlue() const;
};
