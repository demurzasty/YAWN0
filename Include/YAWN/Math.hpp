#pragma once 

#include "Assert.hpp"

namespace YAWN {
    class Math {
    public:
        Math() = delete;

        static constexpr float PI = 3.14159265359f;

        static constexpr float TAU = 6.28318530718f;

        static float Sin(float radians);

        static float Cos(float radians);

        static float Tan(float radians);

        static float Atan(float x);

        static float Atan2(float x, float y);

        static float Pow(float x, float y);

        static float Sqrt(float x);

        static float Ceil(float x);

        static float Floor(float x);

        static float Round(float x);

        constexpr float ToDegrees(float radians) {
            return radians * 180.0f / PI;
        }

        constexpr float ToRadians(float degrees) {
            return degrees * PI / 180.0f;
        }

        template<typename T>
        static constexpr T Abs(T x) noexcept {
            return (x < 0) ? -x : x;
        }
        
        template<typename T>
        static constexpr bool IsPowerOfTwo(T x) noexcept {
            return !(x == 0) && !(x & (x - 1));
        }

        template<typename T>
        static constexpr T NextPowerOfTwo(T v) noexcept {
            v--;
            v |= v >> 1;
            v |= v >> 2;
            v |= v >> 4;
            v |= v >> 8;
            v |= v >> 16;
            return ++v;
        }

        template<typename T>
        static constexpr T Align(T size, T align) noexcept {
            return (size + align - 1) & ~(align - 1);
        }

        template<typename T>
        static constexpr T Max(T a, T b) noexcept {
            return (a > b) ? a : b;
        }

        template<typename T>
        static constexpr T Min(T a, T b) noexcept {
            return (a < b) ? a : b;
        }

        template<typename T>
        static constexpr T Clamp(T v, T min, T max) noexcept {
            return Max(Min(v, max), min);
        }
    };
}
