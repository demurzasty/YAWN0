#include <YAWN/Math.hpp>

#include <math.h>

using namespace YAWN;

float Math::Sin(float radians) {
    return sinf(radians);
}

float Math::Cos(float radians) {
    return cosf(radians);
}

float Math::Tan(float radians) {
    return tanf(radians);
}

float Math::Atan(float x) {
    return atanf(x);
}

float Math::Atan2(float x, float y) {
    return atan2f(x, y);
}

float Math::Pow(float x, float y) {
    return powf(x, y);
}

float Math::Sqrt(float x) {
    return sqrtf(x);
}

float Math::Ceil(float x) {
    return ceilf(x);
}

float Math::Floor(float x) {
    return floorf(x);
}

float Math::Round(float x) {
    return roundf(x);
}
