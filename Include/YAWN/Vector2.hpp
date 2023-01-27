#pragma once 

#include "Math.hpp"

namespace YAWN {
    class Vector2 {
    public:
        static constexpr Vector2 Zero() noexcept { return Vector2(0.0f, 0.0f); }

        static constexpr Vector2 One() noexcept{ return Vector2(1.0f, 1.0f); }

        static constexpr Vector2 AxisX() noexcept{ return Vector2(1.0f, 0.0f); }

        static constexpr Vector2 AxisY() noexcept{ return Vector2(0.0f, 1.0f); }

    public:
        static constexpr float Dot(const Vector2& a, const Vector2& b) noexcept {
            return a.X * b.X + a.Y * b.Y;
        }

        static constexpr float LengthSquared(const Vector2& v) noexcept {
            return Dot(v, v);
        }

        static inline float Length(const Vector2& v) {
            return Math::Sqrt(LengthSquared(v));
        }

        static inline Vector2 Normalize(const Vector2& v) {
            return v / Length(v);
        }

        static inline float Distance(const Vector2& a, const Vector2& b) {
            return Length(b - a);
        }

        static inline Vector2 Direction(const Vector2& from, const Vector2& to) {
            return Normalize(to - from);
        }

        static inline Vector2 MoveTowards(const Vector2& from, const Vector2& to, float delta) {
            return from + Direction(from, to) * Math::Min(Distance(from, to), delta);
        }
        
    public:
        Vector2() noexcept = default;

        explicit constexpr  Vector2(float value) noexcept
            : X(value), Y(value) {
        }

        constexpr Vector2(float x, float y) noexcept
            : X(x), Y(y) {
        }

        constexpr Vector2 operator+(const Vector2& other) const noexcept {
            return Vector2(X + other.X, Y + other.Y);
        }

        constexpr Vector2 operator-(const Vector2& other) const noexcept {
            return Vector2(X - other.X, Y - other.Y);
        }

        constexpr Vector2 operator*(const Vector2& other) const noexcept {
            return Vector2(X * other.X, Y * other.Y);
        }

        constexpr Vector2 operator/(const Vector2& other) const noexcept {
            return Vector2(X / other.X, Y / other.Y);
        }

        constexpr Vector2 operator+(float scalar) const noexcept {
            return Vector2(X + scalar, Y + scalar);
        }

        constexpr Vector2 operator-(float scalar) const noexcept {
            return Vector2(X - scalar, Y - scalar);
        }

        constexpr Vector2 operator*(float scalar) const noexcept {
            return Vector2(X * scalar, Y * scalar);
        }

        constexpr Vector2 operator/(float scalar) const noexcept {
            return Vector2(X / scalar, Y / scalar);
        }

        constexpr float& operator[](usize index) {
            Assert(index < 2);
            return (&X)[index];
        }

        constexpr float operator[](usize index) const {
            Assert(index < 2);
            return (&X)[index];
        }

    public:
        float X, Y;
    };
}
