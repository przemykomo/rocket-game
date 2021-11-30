#include "Scene.hpp"

Scene::Scene(bool &pop, Scene *&toPush) : pop{pop}, toPush{toPush} {}

void Scene::exitScene() { pop = true; }

void Scene::openScene(std::function<Scene *(bool &, Scene *&)> constructor) {
    if (toPush == nullptr) {
        toPush = constructor(pop, toPush);
    }
}
