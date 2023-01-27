#pragma once 

#include <YAWN/GraphicsDevice.hpp>
#include <YAWN/Arena.hpp>
#include <YAWN/Zone.hpp>

#include "GraphicsContextOpenGL.hpp"
#include "ShadersOpenGL.hpp"
#include "UtilsOpenGL.hpp"

#include <YAWN/Texture.hpp>

namespace YAWN {
    class GraphicsDeviceOpenGL : public GraphicsDevice {
        struct TextureData {
            GLuint Id = 0;
        };

        struct MeshData {
            uint32 VertexOffset = 0;
            uint32 VertexCount = 0;
            uint32 IndexOffset = 0;
            uint32 IndexCount = 0;
        };

        struct CanvasBufferData {
            uint32 VertexOffset = 0;
            uint32 VertexCount = 0;
            uint32 VertexCapacity = 0;
            uint32 IndexOffset = 0;
            uint32 IndexCount = 0;
            uint32 IndexCapacity = 0;
        };

        struct DrawElementsIndirectCommand {
            uint32 IndexCount;
            uint32 InstanceCount;
            uint32 IndexOffset;
            int32 VertexOffset;
            uint32 FirstInstance;
        };

        struct DrawCanvasCommand {
            uint32 IndexOffset;
            uint32 IndexCount;
            uint32 VertexOffset;
            uint32 TextureId;
        };

    public:
        GraphicsDeviceOpenGL();

        ~GraphicsDeviceOpenGL() override;

        Id CreateCanvasBuffer() override;

        void DestroyCanvasBuffer(Id id) override;

        void SetCanvasBufferCapacity(Id id, usize vertexCapacity, usize indexCapacity) override;

        void SetCanvasBufferPrimitives(Id id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const uint32>& indices) override;

        void PushCanvasDraw2D(Id canvasBufferId, Id textureId, uint32 indexOffset, uint32 indexCount, uint32 vertexOffset) override;

        Id CreateTexture() override;

        void DestroyTexture(Id id) override;

        void SetTextureData(Id id, int width, int height, const void* pixels) override;

        Id CreateMesh() override;

        void DestroyMesh(Id id) override;

        void SetMeshData(Id id, ArrayView<const Vertex3D> vertices, ArrayView<const uint32> indices) override;

        void Present() override;

    private:
        GLuint CompileShader(ArrayView<const char> vertexCode, ArrayView<const char> fragmentCode);

        void TestShader(GLuint shaderProgram);

    private:
        Managed<GraphicsContextOpenGL> _context;

        GLuint _samplerBufferId = 0;

        GLuint _drawBufferId = 0;

        GLuint _vertexArrayObjectId = 0;
        GLuint _vertexBufferId = 0;
        GLuint _indexBufferId = 0;

        GLuint _canvasVertexArrayObjectId = 0;
        GLuint _canvasVertexBufferId = 0;
        GLuint _canvasIndexBufferId = 0;

        GLuint _canvasItemProgramId = 0;

        Arena<CanvasBufferData, Id> _canvasBuffers;
        Arena<TextureData, Id> _textures;
        Arena<MeshData, Id> _meshes;
        
        usize _vertexOffset = 0;
        usize _indexOffset = 0;

        usize _canvasVertexOffset = 0;
        usize _canvasIndexOffset = 0;

        Array<DrawCanvasCommand> _canvasDrawCommands;

        Managed<Texture> _texture;
    };
}
