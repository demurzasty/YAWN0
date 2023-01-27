#pragma once 

#include "TypeTraits.hpp"

namespace YAWN {
    template<typename T>
    constexpr T&& Forward(typename RemoveReference<T>::Type& arg) noexcept {
        return (T&&)(arg);
    }

    template<typename T>
    constexpr T&& Forward(typename RemoveReference<T>::Type&& arg) noexcept {
        return (T&&)(arg);
    }

    template<typename T>
    constexpr typename RemoveReference<T>::Type&& Move(T&& arg) noexcept {
        return (typename RemoveReference<T>::Type&&)(arg);
    }

    template<typename T>
    constexpr T Max(const T& a) {
        return a;
    }

    template<typename T, typename... Ts>
    constexpr T Max(const T& a, const T& b, const Ts&... rest) {
        return (a > b) ? Max(a, rest...) : Max(b, rest...);
    }

    template<typename T>
    constexpr T Min(const T& a) {
        return a;
    }

    template<typename T, typename... Ts>
    constexpr T Min(const T& a, const T& b, const Ts&... rest) {
        return (a < b) ? Min(a, rest...) : Min(b, rest...);
    }

    template<typename TFirst, typename TSecond>
    struct Pair {
        TFirst First = TFirst();
        TSecond Second = TSecond();
    };
}
