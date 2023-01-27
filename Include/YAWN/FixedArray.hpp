#pragma once 

#include "Config.hpp"
#include "Assert.hpp"

namespace YAWN {
    template<typename T, usize VSize>
    class FixedArray {
    public:
        constexpr T& operator[](usize index) {
            Assert(index < VSize);
            return Values[index];
        }

        constexpr const T& operator[](usize index) const {
            Assert(index < VSize);
            return Values[index];
        }

    public:
        T Values[VSize];
    };
}
