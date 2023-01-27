#pragma once 

#if defined __clang__ || defined __GNUC__
#   define YAWN_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#   define YAWN_PRETTY_FUNCTION __FUNCSIG__
#endif

namespace YAWN {
    using int8 = signed char;
    using int16 = signed short;
    using int32 = signed int;
    using int64 = signed long long;

    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long long;

    using usize = decltype(sizeof(void*));
    using isize = decltype(((int*)0) - ((int*)0));

    enum class Id : uint64 {};

    static constexpr Id None = Id(~0);
}
