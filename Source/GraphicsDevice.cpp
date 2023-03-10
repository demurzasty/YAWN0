#include <YAWN/GraphicsDevice.hpp>

#include "OpenGL/GraphicsDeviceOpenGL.hpp"
using GraphiscDeviceImpl = YAWN::GraphicsDeviceOpenGL;

using namespace YAWN;

const Managed<GraphicsDevice>& GraphicsDevice::Instance() {
    static Managed<GraphicsDevice> instance = new GraphiscDeviceImpl();

    return instance;
}
