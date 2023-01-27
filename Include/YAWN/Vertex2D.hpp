#pragma once 

#include "Vector2.hpp"
#include "Color.hpp"

namespace YAWN {
    class Vertex2D {
    public:
        Vertex2D() noexcept = default;

        constexpr Vertex2D(const Vector2& position, const Vector2& uv) noexcept
            : Position(position), UV(uv), Color(Color::White()) {
        }

        constexpr Vertex2D(const Vector2& position, const Vector2& uv, const Color& color) noexcept
            : Position(position), UV(uv), Color(color) {
        }

    public:
        Vector2 Position;
        Vector2 UV;
        Color Color;
    };
}
