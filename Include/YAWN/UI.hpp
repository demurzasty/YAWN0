#pragma once 

#include "Map.hpp"
#include "Texture.hpp"
#include "Managed.hpp"
#include "GraphicsDevice.hpp"

namespace YAWN {
    class UI : public Reference {
    public:
        static Managed<UI> Instance();

    public:
        UI();

        ~UI();

        void ShowDemo();

    public:
        Id GetCanvasBuffer(int index);

    private:
        Managed<GraphicsDevice> _graphicsDevice = GraphicsDevice::Instance();
        Managed<Texture> _fontTexture;
        Map<int, Id> _canvasBuffers;
    };
}
