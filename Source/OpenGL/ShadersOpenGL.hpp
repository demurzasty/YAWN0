#pragma once 

#include <YAWN/ArrayView.hpp>

namespace YAWN {
    class ShadersOpenGL {
    public:
        static ArrayView<const char> CanvasItemVertexCode();

        static ArrayView<const char> CanvasItemFragmentCode();
    };
}
