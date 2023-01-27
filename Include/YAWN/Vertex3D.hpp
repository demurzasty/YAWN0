#pragma once 

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace YAWN {
    class Vertex3D {
    public:
        Vertex3D() noexcept = default;

        constexpr Vertex3D(const Vector3& position, const Vector2& uv, const Vector3& normal) noexcept
            : Position(position), UV(uv), Normal(normal) {
        }

    public:
        Vector3 Position;
        Vector2 UV;
        Vector3 Normal;
    };
}
