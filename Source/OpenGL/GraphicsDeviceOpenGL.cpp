#include "GraphicsDeviceOpenGL.hpp"

#include <stdio.h>

#ifdef _WIN32
#include "Win32/GraphicsContextOpenGLWin32.hpp"
#endif

using namespace YAWN;

static void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param) {
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}

		return "UNKNOWN";
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}

		return "UNKNOWN";
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}

		return "UNKNOWN";
	}();

	printf("%s, %s, %s, %u: %s\n", src_str, type_str, severity_str, id, message);
}

GraphicsDeviceOpenGL::GraphicsDeviceOpenGL() {
#ifdef _WIN32
    _context = new GraphicsContextOpenGLWin32((HWND)_platform->WindowHandle());
#endif

    glewInit();
	
	Assert(GLEW_ARB_direct_state_access);
	Assert(GLEW_ARB_bindless_texture);

#ifdef _DEBUG
    glCheck(glEnable(GL_DEBUG_OUTPUT));
	glCheck(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
	glCheck(glDebugMessageCallback(&DebugCallback, nullptr));
#endif

	glCheck(glCreateBuffers(1, &_samplerBufferId));
	glCheck(glNamedBufferStorage(_samplerBufferId, sizeof(uint64) * MaxTextureCount, nullptr, GL_DYNAMIC_STORAGE_BIT));
	
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _samplerBufferId);

	glCheck(glCreateBuffers(1, &_drawBufferId));
	glCheck(glNamedBufferStorage(_drawBufferId, sizeof(DrawElementsIndirectCommand) * MaxInstanceCount, nullptr, 0));

	glCheck(glCreateBuffers(1, &_vertexBufferId));
	glCheck(glNamedBufferStorage(_vertexBufferId, sizeof(Vertex3D) * MaxVertexCount, nullptr, GL_DYNAMIC_STORAGE_BIT));

	glCheck(glCreateBuffers(1, &_indexBufferId));
	glCheck(glNamedBufferStorage(_indexBufferId, sizeof(uint32) * MaxIndexCount, nullptr, GL_DYNAMIC_STORAGE_BIT));

	glCheck(glCreateVertexArrays(1, &_vertexArrayObjectId));

	glCheck(glVertexArrayVertexBuffer(_vertexArrayObjectId, 0, _vertexBufferId, 0, sizeof(Vertex3D)));
	glCheck(glVertexArrayElementBuffer(_vertexArrayObjectId, _indexBufferId));

	glCheck(glEnableVertexArrayAttrib(_vertexArrayObjectId, 0));
	glCheck(glEnableVertexArrayAttrib(_vertexArrayObjectId, 1));
	glCheck(glEnableVertexArrayAttrib(_vertexArrayObjectId, 2));

	glCheck(glVertexArrayAttribFormat(_vertexArrayObjectId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Position)));
	glCheck(glVertexArrayAttribFormat(_vertexArrayObjectId, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, UV)));
	glCheck(glVertexArrayAttribFormat(_vertexArrayObjectId, 2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Normal)));

	glCheck(glVertexArrayAttribBinding(_vertexArrayObjectId, 0, 0));
	glCheck(glVertexArrayAttribBinding(_vertexArrayObjectId, 1, 0));
	glCheck(glVertexArrayAttribBinding(_vertexArrayObjectId, 2, 0));

	glCheck(glCreateBuffers(1, &_canvasVertexBufferId));
	glCheck(glNamedBufferStorage(_canvasVertexBufferId, sizeof(Vertex2D) * MaxVertexCount, nullptr, GL_DYNAMIC_STORAGE_BIT));

	glCheck(glCreateBuffers(1, &_canvasIndexBufferId));
	glCheck(glNamedBufferStorage(_canvasIndexBufferId, sizeof(uint32) * MaxIndexCount, nullptr, GL_DYNAMIC_STORAGE_BIT));

	glCheck(glCreateVertexArrays(1, &_canvasVertexArrayObjectId));

	glCheck(glVertexArrayVertexBuffer(_canvasVertexArrayObjectId, 0, _canvasVertexBufferId, 0, sizeof(Vertex2D)));
	glCheck(glVertexArrayElementBuffer(_canvasVertexArrayObjectId, _canvasIndexBufferId));

	glCheck(glEnableVertexArrayAttrib(_canvasVertexArrayObjectId, 0));
	glCheck(glEnableVertexArrayAttrib(_canvasVertexArrayObjectId, 1));
	glCheck(glEnableVertexArrayAttrib(_canvasVertexArrayObjectId, 2));

	glCheck(glVertexArrayAttribFormat(_canvasVertexArrayObjectId, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, Position)));
	glCheck(glVertexArrayAttribFormat(_canvasVertexArrayObjectId, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, UV)));
	glCheck(glVertexArrayAttribFormat(_canvasVertexArrayObjectId, 2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex2D, Color)));

	glCheck(glVertexArrayAttribBinding(_canvasVertexArrayObjectId, 0, 0));
	glCheck(glVertexArrayAttribBinding(_canvasVertexArrayObjectId, 1, 0));
	glCheck(glVertexArrayAttribBinding(_canvasVertexArrayObjectId, 2, 0));
	
	_canvasItemProgramId = CompileShader(ShadersOpenGL::CanvasItemVertexCode(), ShadersOpenGL::CanvasItemFragmentCode());

	glCheck(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
}

GraphicsDeviceOpenGL::~GraphicsDeviceOpenGL() {
	glCheck(glDeleteProgramPipelines(1, &_canvasItemProgramId));

	glCheck(glDeleteVertexArrays(1, &_vertexArrayObjectId));
	glCheck(glDeleteBuffers(1, &_indexBufferId));
	glCheck(glDeleteBuffers(1, &_vertexBufferId));
	glCheck(glDeleteBuffers(1, &_drawBufferId));
	glCheck(glDeleteBuffers(1, &_samplerBufferId));
}

Id GraphicsDeviceOpenGL::CreateCanvasBuffer() {
	return _canvasBuffers.Create();
}

void GraphicsDeviceOpenGL::DestroyCanvasBuffer(Id id) {
	Assert(_canvasBuffers.IsValid(id));

	_canvasBuffers.Destroy(id);
}

void GraphicsDeviceOpenGL::SetCanvasBufferCapacity(Id id, usize vertexCapacity, usize indexCapacity) {
	Assert(_canvasBuffers.IsValid(id));
	Assert(_canvasVertexOffset + vertexCapacity < MaxVertexCount);
	Assert(_canvasIndexOffset + indexCapacity < MaxIndexCount);

	CanvasBufferData& data = _canvasBuffers[id];

	if (vertexCapacity > data.VertexCapacity) {
		data.VertexOffset = uint32(_canvasVertexOffset);
		_canvasVertexOffset += vertexCapacity;
	}

	if (indexCapacity > data.IndexCapacity) {
		data.IndexOffset = uint32(_canvasIndexOffset);
		_canvasIndexOffset += indexCapacity;
	}

	data.VertexCapacity = uint32(vertexCapacity);
	data.IndexCapacity = uint32(indexCapacity);
}

void GraphicsDeviceOpenGL::SetCanvasBufferPrimitives(Id id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const uint32>& indices) {
	Assert(_canvasBuffers.IsValid(id));
	Assert(_canvasVertexOffset + vertices.Size() < MaxVertexCount);
	Assert(_canvasIndexOffset + indices.Size() < MaxIndexCount);

	CanvasBufferData& data = _canvasBuffers[id];

	if (vertices.Size() > data.VertexCapacity) {
		data.VertexOffset = uint32(_canvasVertexOffset);
		data.VertexCapacity = Math::NextPowerOfTwo(uint32(vertices.Size()));
		_canvasVertexOffset += data.VertexCapacity;
	}

	if (indices.Size() > data.IndexCapacity) {
		data.IndexOffset = uint32(_canvasIndexOffset);
		data.IndexCapacity = Math::NextPowerOfTwo(uint32(indices.Size()));
		_canvasIndexOffset += data.IndexCapacity;
	}

	data.VertexCount = uint32(vertices.Size());
	data.IndexCount = uint32(indices.Size());

	glCheck(glNamedBufferSubData(_canvasVertexBufferId, sizeof(Vertex2D) * data.VertexOffset, vertices.SizeInBytes(), vertices.Data()));
	glCheck(glNamedBufferSubData(_canvasIndexBufferId, sizeof(uint32) * data.IndexOffset, indices.SizeInBytes(), indices.Data()));
}

void GraphicsDeviceOpenGL::PushCanvasDraw2D(Id canvasBufferId, Id textureId, uint32 indexOffset, uint32 indexCount, uint32 vertexOffset) {
	Assert(_canvasBuffers.IsValid(canvasBufferId));
	Assert(_textures.IsValid(textureId));

	CanvasBufferData& data = _canvasBuffers[canvasBufferId];

	//glCheck(glNamedBufferSubData(_canvasVertexBufferId, sizeof(Vertex2D) * _canvasVertexOffset, vertices.SizeInBytes(), vertices.Data()));
	//glCheck(glNamedBufferSubData(_canvasIndexBufferId, sizeof(uint32) * _canvasIndexOffset, indices.SizeInBytes(), indices.Data()));

	
	DrawCanvasCommand command;
	command.IndexOffset = data.IndexOffset + indexOffset;
	command.IndexCount = indexCount;
	command.VertexOffset = data.VertexOffset + vertexOffset;
	command.TextureId = uint32(textureId);
	_canvasDrawCommands.Add(command);

	//_canvasVertexOffset += vertices.Size();
	//_canvasIndexOffset += indices.Size();
}

Id GraphicsDeviceOpenGL::CreateTexture() {
    Id id = _textures.Create();

    TextureData& data = _textures[id];
	glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &data.Id));

	// glCheck(glNamedBufferSubData(_samplerBufferId, sizeof(uint64) * usize(id), sizeof(uint64), indices.Data()));

    return id;
}

void GraphicsDeviceOpenGL::DestroyTexture(Id id) {
    Assert(_textures.IsValid(id));

	glCheck(glDeleteTextures(1, &_textures[id].Id));

    _textures.Destroy(id);
}

void GraphicsDeviceOpenGL::SetTextureData(Id id, int width, int height, const void* pixels) {
	Assert(_textures.IsValid(id));

	TextureData& data = _textures[id];

	glCheck(glTextureParameteri(data.Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCheck(glTextureParameteri(data.Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	glCheck(glTextureParameteri(data.Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCheck(glTextureParameteri(data.Id, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	glCheck(glTextureStorage2D(data.Id, 1, GL_RGBA8, width, height));
	glCheck(glTextureSubImage2D(data.Id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels));

	GLuint64 handle;
	glCheck(handle = glGetTextureHandleARB(data.Id));
	glCheck(glMakeTextureHandleResidentARB(handle));

	glCheck(glNamedBufferSubData(_samplerBufferId, sizeof(uint64) * usize(id), sizeof(uint64), &handle));
}

Id GraphicsDeviceOpenGL::CreateMesh() {
	Id id = _meshes.Create();

	//MeshData& data = _meshes[id];
	
	return id;
}

void GraphicsDeviceOpenGL::DestroyMesh(Id id) {
	Assert(_meshes.IsValid(id));
}

void GraphicsDeviceOpenGL::SetMeshData(Id id, ArrayView<const Vertex3D> vertices, ArrayView<const uint32> indices) {
	Assert(_meshes.IsValid(id));
	Assert(_vertexOffset + vertices.Size() <= 0xFFFFFFFF);
	Assert(_indexOffset + indices.Size() <= 0xFFFFFFFF);

	MeshData& data = _meshes[id];
	data.VertexOffset = uint32(_vertexOffset);
	data.VertexCount = uint32(vertices.Size());
	data.IndexOffset = uint32(_indexOffset);
	data.IndexCount = uint32(indices.Size());

	glCheck(glNamedBufferSubData(_vertexBufferId, sizeof(Vertex3D) * data.VertexOffset, sizeof(Vertex3D) * data.VertexCount, vertices.Data()));
	glCheck(glNamedBufferSubData(_indexBufferId, sizeof(uint32) * data.IndexOffset, sizeof(uint32) * data.IndexCount, indices.Data()));

	_vertexOffset += data.VertexCount;
	_indexOffset += data.IndexCount;
}

void GraphicsDeviceOpenGL::Present() {
	glCheck(glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f));
	glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	if (_canvasVertexOffset > 0 && _canvasIndexOffset > 0) {
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		// glEnable(GL_SCISSOR_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glCheck(glBindProgramPipeline(_canvasItemProgramId));

		glCheck(glBindVertexArray(_canvasVertexArrayObjectId));

		for (const DrawCanvasCommand& command : _canvasDrawCommands) {
			glCheck(glDrawElementsBaseVertex(GL_TRIANGLES,
				GLsizei(command.IndexCount),
				GL_UNSIGNED_INT,
				(void*)(intptr_t)(command.IndexOffset * sizeof(uint32)),
				(GLint)command.VertexOffset));
		}

		// glCheck(glDrawElements(GL_TRIANGLES, GLsizei(_canvasIndexOffset), GL_UNSIGNED_INT, nullptr));
	}

    _context->SwapBuffers();

	//_canvasVertexOffset = 0;
	//_canvasIndexOffset = 0;
	_canvasDrawCommands.Clear();
}

GLuint GraphicsDeviceOpenGL::CompileShader(ArrayView<const char> vertexCode, ArrayView<const char> fragmentCode) {
	const char* vertexShaderCode = vertexCode.Data();
	const char* fragmentShaderCode = fragmentCode.Data();

	GLuint vertexShader;
	glCheck(vertexShader = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertexShaderCode));

	GLuint fragmentShader;
	glCheck(fragmentShader = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentShaderCode));

	TestShader(vertexShader);
	TestShader(fragmentShader);

	GLuint programPipeline = 0;
	glCheck(glCreateProgramPipelines(1, &programPipeline));
	glCheck(glUseProgramStages(programPipeline, GL_VERTEX_SHADER_BIT, vertexShader));
	glCheck(glUseProgramStages(programPipeline, GL_FRAGMENT_SHADER_BIT, fragmentShader));

    return programPipeline;
}

void GraphicsDeviceOpenGL::TestShader(GLuint shaderProgram) {
	GLint result, infoLength;
	glCheck(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result));
	glCheck(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLength));
	if (!result && infoLength > 0) {
		Array<char> message(infoLength + 1);
		glCheck(glGetProgramInfoLog(shaderProgram, infoLength, NULL, &message[0]));

		printf("%s\n", message.Data());
	}
}
