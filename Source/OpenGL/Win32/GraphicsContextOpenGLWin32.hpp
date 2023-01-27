#pragma once 

#include "../GraphicsContextOpenGL.hpp"

#include <Windows.h>

namespace YAWN {
    class GraphicsContextOpenGLWin32 : public GraphicsContextOpenGL {
    public:
        GraphicsContextOpenGLWin32(HWND hwnd);

        ~GraphicsContextOpenGLWin32() override;

        void SwapBuffers() override;

    private:
        HWND _hwnd = nullptr;
        HDC _hdc = nullptr;
        HGLRC _hglrc = nullptr;
    };
}
