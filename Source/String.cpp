#include <YAWN/String.hpp>

#include <string.h>

using namespace YAWN;

String::String(const char* string) {
    if (string) {
        _size = strlen(string);
        _string = new char[_size + 1];
        strcpy(_string, string);
    }
}

String::String(const String& string)
    : _size(string._size) {
    if (string._string) {
        _string = new char[_size + 1];
        strcpy(_string, string._string);
    }
}

String::String(String&& string) noexcept
    : _size(string._size), _string(string._string) {
    string._size = 0;
    string._string = nullptr;
}

String::~String() {
    delete[] _string;
}

String& String::operator=(const String& string) {
    if (string._size > _size) {
        delete[] _string;
        _string = new char[string._size + 1];
    }

    _size = string._size;

    if (string._string) {
        strcpy(_string, string._string);
    }

    return *this;
}

String& String::operator=(String&& string) noexcept {
    delete[] _string;

    _size = string._size;
    _string = string._string;

    string._size = 0;
    string._string = nullptr;

    return *this;
}

bool String::operator==(const String& string) const noexcept {
    return strcmp(CString(), string.CString()) == 0;
}

bool String::operator!=(const String& string) const noexcept {
    return strcmp(CString(), string.CString()) != 0;
}

bool String::operator>(const String& string) const noexcept {
    return strcmp(CString(), string.CString()) > 0;
}

bool String::operator>=(const String& string) const noexcept {
    return strcmp(CString(), string.CString()) >= 0;
}

bool String::operator<(const String& string) const noexcept {
    return strcmp(CString(), string.CString()) < 0;
}

bool String::operator<=(const String& string) const noexcept {
    return strcmp(CString(), string.CString()) <= 0;
}

const char* String::CString() const {
    return _string ? _string : "";
}

usize String::Size() const {
    return _size;
}
