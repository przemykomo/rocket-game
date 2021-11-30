#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "raylib.h"

MainMenuScene::MainMenuScene(bool &pop, Scene *&toPush) : Scene(pop, toPush) {}

void MainMenuScene::frame() {
    BeginDrawing();
    ClearBackground(BLUE);

    if (IsKeyPressed(KEY_A)) {
        openScene([](bool &pop, Scene *&toPush) {
            return new GameScene{pop, toPush};
        });
    }

    EndDrawing();
}
