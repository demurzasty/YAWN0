#pragma once 

#include <YAWN/Managed.hpp>

namespace YAWN {
    class GraphicsContextOpenGL : public Reference {
    public:
        virtual ~GraphicsContextOpenGL() = default;

        virtual void SwapBuffers() = 0;
    };
}