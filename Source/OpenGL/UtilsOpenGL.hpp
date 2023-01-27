#pragma once 

#include <YAWN/Config.hpp>

#include <GL/glew.h>

#ifdef _DEBUG
#define glCheck(expr)                                             \
    do {                                                          \
        (expr);                                                   \
        YAWN::UtilsOpenGL::CheckError(__FILE__, __LINE__, #expr); \
    } while (false)
#else
#define glCheck(expr) (expr)
#endif

namespace YAWN {
    class UtilsOpenGL {
    public:
        static void CheckError(const char* path, usize line, const char* expression);
    };
}