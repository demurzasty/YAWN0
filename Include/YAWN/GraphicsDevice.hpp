#pragma once 

#include "Managed.hpp"
#include "Platform.hpp"
#include "Color.hpp"
#include "Vertex2D.hpp"
#include "Vertex3D.hpp"
#include "ArrayView.hpp"

namespace YAWN {
    class GraphicsDevice : public Reference {
    public:
        static constexpr usize MaxInstanceCount = 0x10000;
        static constexpr usize MaxTextureCount = 0x1000;
        static constexpr usize MaxVertexCount = 0x100000;
        static constexpr usize MaxIndexCount = 0x100000;

    public:
        static Managed<GraphicsDevice> Instance();

    public:
        virtual ~GraphicsDevice() = default;

        virtual Id CreateCanvasBuffer() = 0;

        virtual void DestroyCanvasBuffer(Id id) = 0;

        virtual void SetCanvasBufferCapacity(Id id, usize vertexCapacity, usize indexCapacity) = 0;

        virtual void SetCanvasBufferPrimitives(Id id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const uint32>& indices) = 0;

        virtual void PushCanvasDraw2D(Id canvasBufferId, Id textureId, uint32 indexOffset, uint32 indexCount, uint32 vertexOffset) = 0;

        virtual Id CreateTexture() = 0;

        virtual void DestroyTexture(Id id) = 0;

        virtual void SetTextureData(Id id, int width, int height, const void* pixels) = 0;

        virtual Id CreateMesh() = 0;

        virtual void DestroyMesh(Id id) = 0;

        virtual void SetMeshData(Id id, ArrayView<const Vertex3D> vertices, ArrayView<const uint32> indices) = 0;

        virtual void Present() = 0;

    protected:
        Managed<Platform> _platform = Platform::Instance();
    };
}
