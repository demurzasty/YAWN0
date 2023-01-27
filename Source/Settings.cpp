#include <YAWN/Settings.hpp>

using namespace YAWN;

Managed<Settings> Settings::Instance() {
    static Managed<Settings> instance = new Settings();

    return instance;
}

Settings::Settings() {
    SetWindowTitle("YAWN");
    SetWindowFullscreenEnabled(false);
}

void Settings::SetWindowTitle(const String& title) {
    Set("WindowTitle", title);
}

const String& Settings::GetWindowTitle() {
    return Get("WindowTitle");
}

void Settings::SetWindowFullscreenEnabled(bool enabled) {
    Set("WindowFullscreenEnabled", enabled);
}

bool Settings::IsWindowFullscreenEnabled() {
    return Get("WindowFullscreenEnabled");
}

void Settings::Set(const String& key, const Variant& value) {
    _settings[key] = value;
}

Variant& Settings::Get(const String& key) {
    return _settings[key];
}
