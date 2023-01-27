#pragma once 

#include "Config.hpp"

namespace YAWN {
    class Reference {
    public:
        Reference() = default;

        Reference(const Reference&) = delete;

        Reference(Reference&&) = delete;

        virtual ~Reference() = default;

        Reference& operator=(const Reference&) = delete;

        Reference& operator=(Reference&&) = delete;

        void Retain();

        void Release();

        isize UseCount() const;

    private:
        isize _counter = 0;
    };
}
