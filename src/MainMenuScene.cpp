#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "raylib.h"
#include <functional>

void Button::frame() {
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        DrawRectangle(rec.x, rec.y + 1, rec.width, rec.height, BLUE);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            onClick();
        }
    } else {
        DrawRectangle(rec.x, rec.y + 1, rec.width, rec.height, DARKBLUE);
    }

    DrawRectangleLinesEx(rec, 10, WHITE);
    DrawText(text.c_str(), rec.x + (rec.width - MeasureText(text.c_str(), 36)) / 2, rec.y + (rec.height / 2) - (36 / 2), 36, WHITE);
}

MainMenuScene::MainMenuScene(bool &pop, Scene *&toPush) : Scene(pop, toPush) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    buttons.push_back(
        {"Start game",
         {width / 5.0f, height / 3.0f, width * 3 / 5.0f, width / 4.0f},
         [this]() {
             openScene([](bool &pop, Scene *&toPush) {
                 return new GameScene{pop, toPush};
             });
         }});
}

void MainMenuScene::frame() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (Button button : buttons) {
        button.frame();
    }

    EndDrawing();
}
