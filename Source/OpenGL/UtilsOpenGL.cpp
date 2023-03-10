#include "UtilsOpenGL.hpp"

#include <stdio.h>

using namespace YAWN;

void UtilsOpenGL::CheckError(const char* path, usize line, const char* expression) {
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR) {
        const char* filename = path;

        for (const char* p = filename; *p; ++p) {
            if (*p == '/' || *p == '\\') {
                filename = p + 1;
            }
        }

        const char* error = "Unknown error";
        const char* description = "No description";

        switch (errorCode) {
            case GL_INVALID_ENUM: {
                error = "GL_INVALID_ENUM";
                description = "An unacceptable value has been specified for an enumerated argument.";
                break;
            }

            case GL_INVALID_VALUE: {
                error = "GL_INVALID_VALUE";
                description = "A numeric argument is out of range.";
                break;
            }

            case GL_INVALID_OPERATION: {
                error = "GL_INVALID_OPERATION";
                description = "The specified operation is not allowed in the current state.";
                break;
            }

            case GL_STACK_OVERFLOW: {
                error = "GL_STACK_OVERFLOW";
                description = "This command would cause a stack overflow.";
                break;
            }

            case GL_STACK_UNDERFLOW: {
                error = "GL_STACK_UNDERFLOW";
                description = "This command would cause a stack underflow.";
                break;
            }

            case GL_OUT_OF_MEMORY: {
                error = "GL_OUT_OF_MEMORY";
                description = "There is not enough memory left to execute the command.";
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION: {
                error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                description = "The object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\".";
                break;
            }
        }

        fprintf(stderr,
            "An internal OpenGL call failed in %s:%zu.\n  Expression:\n    %s\n  Description:\n    %s\n    %s\n\n",
            filename, line, expression, error, description);
    }
}