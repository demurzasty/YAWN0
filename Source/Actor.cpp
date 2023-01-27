#include <YAWN/Actor.hpp>
#include <YAWN/Component.hpp>

using namespace YAWN;

void Actor::Update(float timeStep) {
    for (auto&& pair : _components) {
        pair.Second->Update(timeStep);
    }
}

void Actor::AddChild(Managed<Actor> child) {
    Assert(!child->_parent);

    child->_parent = this;
    _children.Add(child);
}

Managed<Actor> Actor::Parent() const {
    return _parent;
}

ArrayView<const Managed<Actor>> Actor::Children() const {
    return _children;
}

void Actor::SetName(const String& name) {
    _name = name;
}

const String& Actor::Name() const {
    return _name;
}
