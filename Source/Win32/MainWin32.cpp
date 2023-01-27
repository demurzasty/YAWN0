#include "MainWin32.hpp"

#if defined(_MSC_VER)
INT WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) {
    return Main(__argc, __argv);
}
#else 
INT WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd) {
    return Main(__argc, __argv);
}
#endif
