#pragma once 

#include <YAWN/Platform.hpp>
#include <YAWN/Settings.hpp>
#include <YAWN/MainLoop.hpp>

#include <Windows.h>

namespace YAWN {
    class PlatformWin32 : public Platform {
    public:
        PlatformWin32();

        ~PlatformWin32() override;

        bool IsWindowOpen() const override;

        void PollEvents() override;

        double CurrentTime() const override;

        void* WindowHandle() const override;

        void Close();

    private:
        Managed<Settings> _settings = Settings::Instance();

        HWND _hwnd = NULL;
        bool _open = true;
    };
}
