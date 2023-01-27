#pragma once 

#include "Reference.hpp"

namespace YAWN {
    class Component : public Reference {
        friend class Actor;

    public:
        Component() = default;

        Component(const Component&) = delete;

        Component(Component&&) = delete;

        virtual ~Component() = default;

        Component& operator=(const Component&) = delete;

        Component& operator=(Component&&) = delete;

        virtual void Update(float timeStep);

        Actor* Owner() const;

    private:
        Actor* _owner = nullptr;
    };
}