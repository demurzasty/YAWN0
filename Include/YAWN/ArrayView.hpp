#pragma once 

#include "Array.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    template<typename T>
    class ArrayView {
    public:
        constexpr ArrayView() = default;

        constexpr ArrayView(T* data, usize size)
            : _data(data), _size(size) {
        }

        template<usize N>
        constexpr ArrayView(T(&data)[N])
            : _data(data), _size(N) {
        }

        ArrayView(Array<typename RemoveConst<T>::Type>& array)
            : _data(array.Data()), _size(array.Size()) {
        }

        ArrayView(const Array<typename RemoveConst<T>::Type>& array)
            : _data(array.Data()), _size(array.Size()) {
        }

        constexpr T* Data() noexcept {
            return _data;
        }

        constexpr const T* Data() const noexcept {
            return _data;
        }

        constexpr usize Size() const noexcept {
            return _size;
        }

        constexpr usize SizeInBytes() const noexcept {
            return _size * sizeof(T);
        }

    public:
        T* begin() noexcept { return Data(); }
        const T* begin() const noexcept { return Data(); }

        T* end() noexcept { return Data() + Size(); }
        const T* end() const noexcept { return Data() + Size(); }

    private:
        T* _data = nullptr;
        usize _size = 0;
    };
}
