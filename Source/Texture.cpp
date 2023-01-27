#include <YAWN/Texture.hpp>
#include <YAWN/GraphicsDevice.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace YAWN;

Texture::Texture()
    : GraphicsResource(GraphicsDevice::Instance()->CreateTexture()) {
}

Texture::~Texture() {
    GraphicsDevice::Instance()->DestroyTexture(_id);
}

void Texture::Load(const String& path) {
    stbi_uc* pixels = stbi_load(path.CString(), &_width, &_height, nullptr, STBI_rgb_alpha);
    Assert(pixels);

    GraphicsDevice::Instance()->SetTextureData(_id, _width, _height, pixels);

    stbi_image_free(pixels);
}

void Texture::SetData(int width, int height, const void* pixels) {
    GraphicsDevice::Instance()->SetTextureData(_id, width, height, pixels);

    _width = width;
    _height = height;
}

int Texture::Width() const {
    return _width;
}

int Texture::Height() const {
    return _height;
}
