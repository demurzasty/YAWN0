#include "GraphicsContextOpenGLWin32.hpp"

using namespace YAWN;

GraphicsContextOpenGLWin32::GraphicsContextOpenGLWin32(HWND hwnd)
    : _hwnd(hwnd) {
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	_hdc = GetDC(hwnd);

	int pixelFormat = ChoosePixelFormat(_hdc, &pfd);
	SetPixelFormat(_hdc, pixelFormat, &pfd);

	_hglrc = wglCreateContext(_hdc);
	wglMakeCurrent(_hdc, _hglrc);
}

GraphicsContextOpenGLWin32::~GraphicsContextOpenGLWin32() {
	wglDeleteContext(_hglrc);
	ReleaseDC(_hwnd, _hdc);
}

void GraphicsContextOpenGLWin32::SwapBuffers() {
	::SwapBuffers(_hdc);
}
