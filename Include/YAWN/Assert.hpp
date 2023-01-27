#pragma once 

#include "Config.hpp"

#ifdef _MSC_VER
#	define YAWN_DEBUG_BREAK() __debugbreak()
#else
#	define YAWN_DEBUG_BREAK() __builtin_trap()
#endif

#ifdef _DEBUG
#define Assert(x) if (!(x)) { YAWN_DEBUG_BREAK(); } else (0)
#else
#define Assert(x) (0)
#endif
