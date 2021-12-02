#include "MainMenuScene.hpp"
#include "GameProperties.hpp"
#include "GameScene.hpp"
#include "raylib.h"
#include <functional>

MainMenuScene::MainMenuScene(GameProperties &gameProperties) : Scene(gameProperties) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    buttons.push_back(
        {"Start game",
         {width / 5.0f, height / 3.0f, width * 3 / 5.0f, width / 4.0f},
         [this]() {
             openScene([](GameProperties &gameProperties) {
                 return new GameScene{gameProperties};
             });
         }});

    buttons.push_back({"Exit",
                       {width / 5.0f, height / 3.0f + width / 3.0f,
                        width * 3 / 5.0f, width / 4.0f},
                       [this]() { closeGame(); }});
}

void MainMenuScene::frame() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (Button button : buttons) {
        button.frame();
    }

    EndDrawing();
}
