#pragma once 

#include "Managed.hpp"
#include "Input.hpp"

namespace YAWN {
    class Service : public Reference {
    public:
        virtual ~Service() = default;

        virtual void Update(float timeStep);

        virtual void Input(const InputEvent& event);
    };
}
