#pragma once 

#include "Math.hpp"

namespace YAWN {
    class Vector4 {
    public:
        Vector4() noexcept = default;

        explicit constexpr Vector4(float value) noexcept
            : X(value), Y(value), Z(value), W(value) {
        }

        constexpr Vector4(float x, float y, float z, float w) noexcept
            : X(x), Y(y), Z(z), W(w) {
        }

        constexpr float& operator[](usize index) {
            Assert(index < 4);
            return (&X)[index];
        }

        constexpr float operator[](usize index) const {
            Assert(index < 4);
            return (&X)[index];
        }

    public:
        float X, Y, Z, W;
    };
}
