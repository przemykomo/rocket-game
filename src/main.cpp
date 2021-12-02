#include "GameProperties.hpp"
#include "MainMenuScene.hpp"
#include "Scene.hpp"
#include "raylib.h"
#include <memory>
#include <stack>

int main(int argc, const char **argv) {

    InitWindow(500, 800, "Flying rocket game");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    {
        GameProperties gameProperties;
        std::stack<std::unique_ptr<Scene>> sceneStack{};
        sceneStack.emplace(new MainMenuScene{gameProperties});

        while (!WindowShouldClose() && !sceneStack.empty() && !gameProperties.shouldClose) {
            sceneStack.top()->frame();
            if (gameProperties.pop) {
                sceneStack.pop();
                gameProperties.pop = false;
            }
            if (gameProperties.toPush != nullptr) {
                sceneStack.emplace(gameProperties.toPush);
                gameProperties.toPush = nullptr;
            }
        }
    }

    CloseWindow();

    return 0;
}
