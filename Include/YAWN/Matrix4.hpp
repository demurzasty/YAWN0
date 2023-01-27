#pragma once 

#include "Math.hpp"
#include "Vector4.hpp"
#include "FixedArray.hpp"

namespace YAWN {
    class Matrix4 {
    public:
        static constexpr Matrix4 Identity() noexcept { return Matrix4(1.0f); }

    public:
        Matrix4() noexcept = default;

        constexpr Matrix4(float scalar) noexcept
            : _data({ 
                scalar, 0.0f, 0.0f, 0.0f,
                0.0f, scalar, 0.0f, 0.0f,
                0.0f, 0.0f, scalar, 0.0f,
                0.0f, 0.0f, 0.0f, scalar
            }) {
        }

        constexpr Matrix4(const Matrix4&) noexcept = default;

        constexpr Matrix4(Matrix4&&) noexcept = default;

        constexpr Matrix4& operator=(const Matrix4&) noexcept = default;

        constexpr Matrix4& operator=(Matrix4&&) noexcept = default;

        constexpr float& operator[](usize index) {
            Assert(index < 16);
            return _data[index];
        }

        constexpr float operator[](usize index) const {
            Assert(index < 16);
            return _data[index];
        }

    public:
        FixedArray<float, 16> _data;
    };
}