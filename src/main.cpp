#include "GameScene.hpp"
#include "MainMenuScene.hpp"
#include "Scene.hpp"
#include "raylib.h"
#include <memory>
#include <stack>

int main(int argc, const char **argv) {

    InitWindow(500, 800, "Flying rocket game");
    SetTargetFPS(60);

    bool pop = false;
    Scene *toPush = nullptr;
    std::stack<std::unique_ptr<Scene>> sceneStack{};
    sceneStack.emplace(new MainMenuScene{pop, toPush});

    while (!WindowShouldClose() && !sceneStack.empty()) {
        sceneStack.top()->frame();
        if (pop) {
            sceneStack.pop();
            pop = false;
        }
        if (toPush != nullptr) {
            sceneStack.emplace(toPush);
            toPush = nullptr;
        }
    }

    CloseWindow();

    return 0;
}
