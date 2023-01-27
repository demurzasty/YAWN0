#pragma once 

#include "String.hpp"

namespace YAWN {
    template<typename T>
    struct FNV1aTraits;

    template<>
    struct FNV1aTraits<uint32> {
        static constexpr uint32 InitNumber = 0x811c9dc5;
        static constexpr uint32 PrimeNumber = 16777619;
    };

    template<>
    struct FNV1aTraits<uint64> {
        static constexpr uint64 InitNumber = 0xcbf29ce484222325L;
        static constexpr uint64 PrimeNumber = 1099511628211L;
    };

    constexpr usize FNV1a(const char* str, usize count) {
        using Traits = FNV1aTraits<usize>;

        return ((count ? FNV1a(str, count - 1) : Traits::InitNumber) ^ str[count]) * Traits::PrimeNumber;
    }

    template<usize N>
    constexpr usize FNV1a(const char(&str)[N]) {
        return FNV1a(str, N - 1);
    }

    inline usize FNV1a(const String& str) {
        return FNV1a(str.CString(), str.Size());
    }

    constexpr usize operator"" _FNV1a(const char* str, usize count) {
        return FNV1a(str, count);
    }
}
