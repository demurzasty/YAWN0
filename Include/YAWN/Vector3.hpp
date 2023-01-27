#pragma once 

#include "Math.hpp"

namespace YAWN {
    class Vector3 {
    public:
        Vector3() noexcept = default;

        explicit constexpr Vector3(float value) noexcept
            : X(value), Y(value), Z(value) {
        }

        constexpr Vector3(float x, float y, float z) noexcept
            : X(x), Y(y), Z(z) {
        }

        constexpr float& operator[](usize index) {
            Assert(index < 3);
            return (&X)[index];
        }

        constexpr float operator[](usize index) const {
            Assert(index < 3);
            return (&X)[index];
        }

    public:
        float X, Y, Z;
    };
}
