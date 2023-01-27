#include <YAWN/Scene.hpp>

using namespace YAWN;

Managed<Scene> Scene::Instance() {
    static Managed<Scene> instance = new Scene();

    return instance;
}

void Scene::Update(float timeStep) {
    Update(_root, timeStep);
}

void Scene::Update(Managed<Actor> actor, float timeStep) {
    actor->Update(timeStep);

    for (const Managed<Actor>& child : actor->Children()) {
        Update(child, timeStep);
    }
}

const Managed<Actor>& Scene::Root() const {
    return _root;
}
