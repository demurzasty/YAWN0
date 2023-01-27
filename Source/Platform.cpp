#include <YAWN/Platform.hpp>

#ifdef _WIN32
#include "Win32/PlatformWin32.hpp"
using PlatformImpl = YAWN::PlatformWin32;
#endif

using namespace YAWN;

Managed<Platform> Platform::Instance() {
    static Managed<Platform> instance = new PlatformImpl();

    return instance;
}
