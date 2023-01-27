#include "PlatformWin32.hpp"

using namespace YAWN;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static void SetProcessDpiAware() {
	HINSTANCE shCoreDll = LoadLibrary("Shcore.dll");
	if (shCoreDll) {
		enum ProcessDpiAwareness {
			ProcessDpiUnaware = 0,
			ProcessSystemDpiAware = 1,
			ProcessPerMonitorDpiAware = 2
		};

		typedef HRESULT(WINAPI* SetProcessDpiAwarenessFuncType)(ProcessDpiAwareness);
		SetProcessDpiAwarenessFuncType SetProcessDpiAwarenessFunc = reinterpret_cast<SetProcessDpiAwarenessFuncType>(GetProcAddress(shCoreDll, "SetProcessDpiAwareness"));

		if (SetProcessDpiAwarenessFunc) {
			if (SetProcessDpiAwarenessFunc(ProcessSystemDpiAware) != E_INVALIDARG) {
				FreeLibrary(shCoreDll);
				return;
			}
		}

		FreeLibrary(shCoreDll);
	}

	HINSTANCE user32Dll = LoadLibrary("user32.dll");
	if (user32Dll) {
		typedef BOOL(WINAPI* SetProcessDPIAwareFuncType)(void);
		SetProcessDPIAwareFuncType SetProcessDPIAwareFunc = reinterpret_cast<SetProcessDPIAwareFuncType>(GetProcAddress(user32Dll, "SetProcessDPIAware"));

		if (SetProcessDPIAwareFunc) {
			SetProcessDPIAwareFunc();
		}

		FreeLibrary(user32Dll);
	}
}

PlatformWin32::PlatformWin32() {
	SetProcessDpiAware();

	Managed<Settings> settings = Settings::Instance();

	WNDCLASS wc{};
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = &WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = "YAWN";
	RegisterClass(&wc);

	HDC screenDC = GetDC(NULL);
	int32 windowWidth = 1280;
	int32 windowHeight = 720;

	int32 screenWidth = GetDeviceCaps(screenDC, HORZRES);
	int32 screenHeight = GetDeviceCaps(screenDC, VERTRES);

	if (settings->IsWindowFullscreenEnabled()) {
		windowWidth = screenWidth;
		windowHeight = screenHeight;
	}

	int32 left = (screenWidth - windowWidth) / 2;
	int32 top = (screenHeight - windowHeight) / 2;
	ReleaseDC(NULL, screenDC);

	RECT rect;
	rect.left = rect.top = 0;
	rect.right = windowWidth;
	rect.bottom = windowHeight;

	const DWORD style = settings->IsWindowFullscreenEnabled() ?
		WS_VISIBLE | WS_POPUP :
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE;

	int32 width = windowWidth;
	int32 height = windowHeight;

	if (settings->IsWindowFullscreenEnabled()) {
		left = 0;
		top = 0;
		width = screenWidth;
		height = screenHeight;
	} else {
		if (AdjustWindowRect(&rect, style, FALSE)) {
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
	}

	_hwnd = CreateWindow("YAWN", settings->GetWindowTitle().CString(), style, left, top, width, height, NULL, NULL, GetModuleHandle(NULL), this);
	Assert(_hwnd);
}

PlatformWin32::~PlatformWin32() {
	if (Settings::Instance()->IsWindowFullscreenEnabled()) {
		ChangeDisplaySettings(nullptr, 0);
	}

	DestroyWindow(_hwnd);
	UnregisterClass("YAWN", GetModuleHandle(NULL));
}

bool PlatformWin32::IsWindowOpen() const {
    return _open;
}

void PlatformWin32::PollEvents() {
	MSG message;
	while (PeekMessage(&message, _hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

static LARGE_INTEGER GetFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

static LARGE_INTEGER GetTime() {
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time;
}

double PlatformWin32::CurrentTime() const {
	static LARGE_INTEGER frequency = GetFrequency();
	static LARGE_INTEGER initialTime = GetTime();

	LARGE_INTEGER currentTime = GetTime();

	return double((long double)(currentTime.QuadPart - initialTime.QuadPart) / frequency.QuadPart);
}

void* PlatformWin32::WindowHandle() const {
	return _hwnd;
}

void PlatformWin32::Close() {
	_open = false;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_CREATE) {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)(lParam))->lpCreateParams);
	}

	PlatformWin32* platform = hwnd ? reinterpret_cast<PlatformWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)) : NULL;
	if (platform) {
		if (msg == WM_CLOSE) {
			platform->Close();
		}
	}

	if (msg == WM_CLOSE) {
		return 0;
	}

	if ((msg == WM_SYSCOMMAND) && (wParam == SC_KEYMENU)) {
		return 0;
	}

	if (!hwnd) {
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}