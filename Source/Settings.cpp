#include <YAWN/Settings.hpp>

using namespace YAWN;

Managed<Settings> Settings::Instance() {
    static Managed<Settings> instance = new Settings();

    return instance;
}

Settings::Settings() {
    SetLowProcessorModeEnabled(false);
    SetWindowTitle("YAWN");
    SetWindowFullscreenEnabled(false);
}

void Settings::SetLowProcessorModeEnabled(bool enabled) {
    Set("LowProcessorModeEnabled", enabled);
}

bool Settings::IsLowProcessorModeEnabled() const {
    return Get("LowProcessorModeEnabled");
}

void Settings::SetWindowTitle(const String& title) {
    Set("WindowTitle", title);
}

const String& Settings::GetWindowTitle() const {
    return Get("WindowTitle");
}

void Settings::SetWindowFullscreenEnabled(bool enabled) {
    Set("WindowFullscreenEnabled", enabled);
}

bool Settings::IsWindowFullscreenEnabled() const {
    return Get("WindowFullscreenEnabled");
}

void Settings::Set(const String& key, const Variant& value) {
    _settings[key] = value;
}

const Variant& Settings::Get(const String& key) const {
    return _settings[key];
}
