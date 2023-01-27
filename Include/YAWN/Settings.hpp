#pragma once 

#include "Managed.hpp"
#include "Variant.hpp"

namespace YAWN {
    class Settings : public Reference {
    public:
        static Managed<Settings> Instance();

    public:
        Settings();

        void SetWindowTitle(const String& title);

        const String& GetWindowTitle();

        void SetWindowFullscreenEnabled(bool enabled);

        bool IsWindowFullscreenEnabled();

        void Set(const String& key, const Variant& value);

        Variant& Get(const String& key);

    private:
        Map<String, Variant> _settings;
    };
}
