#pragma once 

#include "Managed.hpp"
#include "String.hpp"

namespace YAWN {
    class Resource : public Reference {
    public:
        virtual ~Resource() override = default;

        virtual void Load(const String& path) = 0;
    };
}
