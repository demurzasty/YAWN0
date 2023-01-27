#pragma once 

#include "Config.hpp"

namespace YAWN {
    class String {
    public:
        String() = default;

        String(const char* string);

        String(const String& string);

        String(String&& string) noexcept;

        ~String();

        String& operator=(const String&);

        String& operator=(String&&) noexcept;

        bool operator==(const String& string) const noexcept;

        bool operator!=(const String& string) const noexcept;

        bool operator>(const String& string) const noexcept;

        bool operator>=(const String& string) const noexcept;

        bool operator<(const String& string) const noexcept;

        bool operator<=(const String& string) const noexcept;

        const char* CString() const;

        usize Size() const;

    public:
        const char* begin() const noexcept { return CString(); }

        const char* end() const noexcept { return CString() + Size(); }

    private:
        char* _string = nullptr;
        usize _size = 0;
    };
}
