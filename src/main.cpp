#include "raylib.h"
#include "GameScene.hpp"

int main(int argc, const char **argv) {

    InitWindow(500, 800, "Flying rocket game");
    SetTargetFPS(60);

    GameScene gameScene{};

    while (!WindowShouldClose()) {
        gameScene.frame();
    }

    CloseWindow();

    return 0;
}
