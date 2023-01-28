#include <YAWN/Component.hpp>

using namespace YAWN;

void Component::Update(float timeStep) {
}

void Component::Input(const InputEvent& event) {
}

Actor* Component::Owner() const {
    return _owner;
}
