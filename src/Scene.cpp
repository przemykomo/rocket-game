#include "Scene.hpp"
#include "GameProperties.hpp"

Scene::Scene(GameProperties &gameProperties) : gameProperties(gameProperties) {}

void Scene::exitScene() { gameProperties.pop = true; }

void Scene::openScene(std::function<Scene *(GameProperties &)> constructor) {
    if (gameProperties.toPush == nullptr) {
        gameProperties.toPush = constructor(gameProperties);
    }
}

void Scene::closeGame() {
    gameProperties.shouldClose = true;
}
