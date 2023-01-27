#pragma once 

#include "Actor.hpp"

namespace YAWN {
    class Scene : public Reference {
    public:
        static Managed<Scene> Instance();
        
    public:
        void Update(float timeStep);

        const Managed<Actor>& Root() const;

    private:
        void Update(Managed<Actor> actor, float timeStep);

    private:
        Managed<Actor> _root = new Actor();
    };
}
