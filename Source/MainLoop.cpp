#include <YAWN/MainLoop.hpp>

using namespace YAWN;

const Managed<MainLoop>& MainLoop::Instance() {
    static Managed<MainLoop> instance = new MainLoop();

    return instance;
}

void MainLoop::AddService(Managed<Service> service) {
    _services.Add(service);
}

void MainLoop::Update(float timeStep) {
    for (Managed<Service>& service : _services) {
        service->Update(timeStep);
    }
}

void MainLoop::Input(const InputEvent& event) {
    NeedTick = true;

    for (Managed<Service>& service : _services) {
        service->Input(event);
    }
}
