#pragma once 

#include "Managed.hpp"
#include "Variant.hpp"

namespace YAWN {
    class Settings : public Reference {
    public:
        static Managed<Settings> Instance();

    public:
        Settings();

        void SetLowProcessorModeEnabled(bool enabled);

        bool IsLowProcessorModeEnabled() const;

        void SetWindowTitle(const String& title);

        const String& GetWindowTitle() const;

        void SetWindowFullscreenEnabled(bool enabled);

        bool IsWindowFullscreenEnabled() const;

        void Set(const String& key, const Variant& value);

        const Variant& Get(const String& key) const;

    private:
        Map<String, Variant> _settings;
    };
}
