#include <YAWN/Scene.hpp>

#include <stdio.h>

using namespace YAWN;

const Managed<Scene>& Scene::Instance() {
    static Managed<Scene> instance = new Scene();

    return instance;
}

void Scene::Update(float timeStep) {
    Update(_root, timeStep);
}

void Scene::Input(const InputEvent& event) {
    Input(_root, event);
}

void Scene::Update(const Managed<Actor>& actor, float timeStep) {
    actor->Update(timeStep);

    for (const Managed<Actor>& child : actor->Children()) {
        Update(child, timeStep);
    }
}

void Scene::Input(const Managed<Actor>& actor, const InputEvent& event) {
    actor->Input(event);

    for (const Managed<Actor>& child : actor->Children()) {
        Input(child, event);
    }
}

const Managed<Actor>& Scene::Root() const {
    return _root;
}
