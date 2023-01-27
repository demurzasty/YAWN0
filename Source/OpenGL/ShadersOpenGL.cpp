#include "ShadersOpenGL.hpp"

#include "Shaders/Generated/CanvasItem.vert.h"
#include "Shaders/Generated/CanvasItem.frag.h"

using namespace YAWN;

ArrayView<const char> ShadersOpenGL::CanvasItemVertexCode() {
    return CanvasItem_vert;
}

ArrayView<const char> ShadersOpenGL::CanvasItemFragmentCode() {
    return CanvasItem_frag;
}
