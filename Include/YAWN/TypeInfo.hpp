#pragma once 

#include "FNV1a.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    namespace Internal {
        template<typename T>
        constexpr usize TypeId() noexcept {
            return FNV1a(YAWN_PRETTY_FUNCTION);
        }
    }

    template<typename T>
    constexpr usize TypeId() noexcept {
        return Internal::TypeId<typename RemoveConstReference<T>::Type>();
    }
}
