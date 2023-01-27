#pragma once 

#include "Config.hpp"

namespace YAWN {
    template<typename...>
    struct Tuple;

    template<typename T0>
    struct Tuple<T0> {
        T0 Value0;
    };

    template<typename T0, typename T1>
    struct Tuple<T0, T1> {
        T0 Value0;
        T1 Value1;
    };

    template<typename T0, typename T1, typename T2>
    struct Tuple<T0, T1, T2> {
        T0 Value0;
        T1 Value1;
        T2 Value2;
    };

    template<typename T0, typename T1, typename T2, typename T3>
    struct Tuple<T0, T1, T2, T3> {
        T0 Value0;
        T1 Value1;
        T2 Value2;
        T3 Value3;
    };

    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    struct Tuple<T0, T1, T2, T3, T4> {
        T0 Value0;
        T1 Value1;
        T2 Value2;
        T3 Value3;
        T4 Value4;
    };

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    struct Tuple<T0, T1, T2, T3, T4, T5> {
        T0 Value0;
        T1 Value1;
        T2 Value2;
        T3 Value3;
        T4 Value4;
        T5 Value5;
    };

    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    struct Tuple<T0, T1, T2, T3, T4, T5, T6> {
        T0 Value0;
        T1 Value1;
        T2 Value2;
        T3 Value3;
        T4 Value4;
        T5 Value5;
        T6 Value6;
    };
}
