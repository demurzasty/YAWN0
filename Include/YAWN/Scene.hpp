#pragma once 

#include "Actor.hpp"
#include "Input.hpp"
#include "Service.hpp"

namespace YAWN {
    class Scene : public Service {
    public:
        static const Managed<Scene>& Instance();
        
    public:
        void Update(float timeStep);

        void Input(const InputEvent& event);

        const Managed<Actor>& Root() const;

    private:
        void Update(const Managed<Actor>& actor, float timeStep);

        void Input(const Managed<Actor>& actor, const InputEvent& event);

    private:
        Managed<Actor> _root = new Actor();
    };
}
