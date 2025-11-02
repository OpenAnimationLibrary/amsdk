#pragma once

#include <type_traits>

template<typename Enum>
struct EnableBitMaskOperators
{
    static constexpr bool Enable = false;
};

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> operator|(Enum lhs, Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) | static_cast<std::underlying_type_t<Enum>>(rhs));
}

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> operator&(Enum lhs, Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) & static_cast<std::underlying_type_t<Enum>>(rhs));
}

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> operator^(Enum lhs, Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) ^ static_cast<std::underlying_type_t<Enum>>(rhs));
}

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> operator~(Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    return static_cast<Enum>(~static_cast<std::underlying_type_t<Enum>>(rhs));
}

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> &operator|=(Enum &lhs, Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    lhs = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) | static_cast<std::underlying_type_t<Enum>>(rhs));
    return lhs;
}

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> &operator&=(Enum &lhs, Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    lhs = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) & static_cast<std::underlying_type_t<Enum>>(rhs));
    return lhs;
}

template<typename Enum>
std::enable_if_t<EnableBitMaskOperators<Enum>::Enable, Enum> &operator^=(Enum &lhs, Enum rhs) noexcept {
    static_assert( std::is_enum_v<Enum>, "template parameter is not an enum type");
    lhs = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) ^ static_cast<std::underlying_type_t<Enum>>(rhs));
    return lhs;
}
