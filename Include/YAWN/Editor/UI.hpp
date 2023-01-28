#pragma once 

#include "../Map.hpp"
#include "../Texture.hpp"
#include "../Managed.hpp"
#include "../GraphicsDevice.hpp"
#include "../Input.hpp"
#include "../Service.hpp"

namespace YAWN {
    class UI : public Service {
    public:
        static Managed<UI> Instance();

    public:
        UI();

        ~UI();

        void Update(float timeStep) override;

        void Input(const InputEvent& event) override;

        void ShowDemo();

    public:
        Id GetCanvasBuffer(int index);

    private:
        Managed<GraphicsDevice> _graphicsDevice = GraphicsDevice::Instance();
        Managed<Texture> _fontTexture;
        Map<int, Id> _canvasBuffers;
    };
}
