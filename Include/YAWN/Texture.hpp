#pragma once 

#include "GraphicsResource.hpp"

namespace YAWN {
    class Texture : public GraphicsResource {
    public:
        Texture();

        virtual ~Texture() override;

        virtual void Load(const String& path) override;

        void SetData(int width, int height, const void* pixels);

        int Width() const;

        int Height() const;

    private:
        int _width = 0;
        int _height = 0;
    };
}