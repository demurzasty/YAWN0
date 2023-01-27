#pragma once 

#include "Assert.hpp"

namespace YAWN {
    template<typename T>
    struct RemoveReference {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference<T&> {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference<T&&> {
        using Type = T;
    };

    template<typename T>
    struct RemoveConst {
        using Type = T;
    };

    template<typename T>
    struct RemoveConst<const T> {
        using Type = T;
    };

    template<typename T>
    struct RemoveConstReference {
        using Type = typename RemoveConst<typename RemoveReference<T>::Type>::Type;
    };
}
