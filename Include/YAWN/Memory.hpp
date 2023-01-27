#pragma once 

#include "Utility.hpp"

namespace YAWN {
    struct NewInPlaceTag {};
}

constexpr void* operator new(YAWN::usize, void* pointer, YAWN::NewInPlaceTag) noexcept {
    return pointer;
}

constexpr void operator delete(void*, void*, YAWN::NewInPlaceTag) noexcept {
}

constexpr void operator delete[](void*, void*, YAWN::NewInPlaceTag) noexcept {
}

namespace YAWN {
    template<typename T, typename... Args>
    constexpr T* ConstructAt(T* pointer, Args&&... args) {
        return ::new (const_cast<void*>(static_cast<const volatile void*>(pointer)), NewInPlaceTag()) T(Forward<Args>(args)...);
    }

    template<typename T>
    constexpr void DestroyAt(T* pointer) {
        pointer->~T();
    }

    template<typename T>
    class AlignedStorage {
    public:
        constexpr T* Data() noexcept {
            return reinterpret_cast<T*>(_data);
        }

        constexpr const T* Data() const noexcept {
            return reinterpret_cast<const T*>(_data);
        }

    private:
        alignas(alignof(T)) unsigned char _data[sizeof(T)];
    };

    template<typename... Ts>
    class AlignedUnion {
    public:
        template<typename T>
        constexpr T* Data() noexcept {
            return reinterpret_cast<T*>(_data);
        }

        template<typename T>
        constexpr const T* Data() const noexcept {
            return reinterpret_cast<const T*>(_data);
        }

    private:
        alignas(alignof(Ts...)) unsigned char _data[Max(sizeof(Ts)...)];
    };
}
