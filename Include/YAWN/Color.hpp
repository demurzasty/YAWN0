#pragma once 

#include "Config.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace YAWN {
    class Color {
    public:
        static constexpr Color White() noexcept { return Color(255, 255, 255); }

        static constexpr Color Black() noexcept { return Color(0, 0, 0); }

        static constexpr Color CornflowerBlue() noexcept { return Color(100, 149, 237); }

    public:
        Color() noexcept = default;

        constexpr Color(uint8 r, uint8 g, uint8 b, uint8 a = 255) noexcept
            : R(r), G(g), B(b), A(a) {
        }

        constexpr uint32 ToInteger() const noexcept {
            return R | (G << 8) | (B << 16) | (A << 24);
        }

        constexpr Vector3 ToVector3() const noexcept {
            return Vector3(R / 255.0f, G / 255.0f, B / 255.0f);
        }

        constexpr Vector4 ToVector4() const noexcept {
            return Vector4(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f);
        }

    public:
        uint8 R, G, B, A;
    };
}
