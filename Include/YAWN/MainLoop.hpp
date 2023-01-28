#pragma once 

#include "Managed.hpp"
#include "Service.hpp"
#include "Array.hpp"

namespace YAWN {
    class MainLoop : public Reference {
    public:
        static const Managed<MainLoop>& Instance();

        void AddService(Managed<Service> service);

        void Update(float timeStep);

        void Input(const InputEvent& event);

    public:
        bool NeedTick = true;

    private:
        Array<Managed<Service>> _services;
    };
}
