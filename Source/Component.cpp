#include <YAWN/Component.hpp>

using namespace YAWN;

void Component::Update(float timeStep) {
}

Actor* Component::Owner() const {
    return _owner;
}
